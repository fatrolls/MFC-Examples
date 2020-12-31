// g711Decode.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"


#include <windows.h>//这个头文件要放在最前面，否则会提示有些东西找不到，一般提示是102个错误，个人经验
#include <stdio.h>
#include <stdlib.h>
#include "g711.h"


#include <mmsystem.h>
#include <dsound.h>



//声明引用库
#pragma   comment(lib,"winmm.lib")
#pragma   comment(lib,"dsound.lib")  
#pragma   comment(lib,"dxguid.lib")



HRESULT hr;//返回的结果句柄
DWORD g_dwNextWriteOffset ;

LPDIRECTSOUNDBUFFER8 g_lpDSBuffer8=NULL; //DS的官方缓冲变量
LPDIRECTSOUNDNOTIFY8 g_lpDSNotify=0; //DS的通告位

LPDIRECTSOUND8 g_pDsd=0; //DS的变量
DSBUFFERDESC dsBufDesc;//DS的缓冲描述--用来设置DS缓冲的相关属性
LPDIRECTSOUNDBUFFER lpBuffer;//DS的缓冲

#define buffer_size 800 //定义播放的每一片缓冲都是800个字节
#define MAX_AUDIO_BUF 4 //播放缓冲的通知索引
#define BUFFERNOTIFYSIZE buffer_size/*8192*//*192000*/ //缓冲通知位置的大小，请参见DirectSound应用程序开发快速入门
#define SAMPLE_RATE      8000/*44100*/ //pcm 的采样率  8k
#define N_CHANNEL          1/*2*/   //PCM 声道数 单通道
#define BITS_PER_SAMPLE    16  //每个采样点的比特数

DSBPOSITIONNOTIFY g_arrayPosNotify[MAX_AUDIO_BUF];//设置通知位置标志的数组
HANDLE g_event[MAX_AUDIO_BUF];//DS事件的句柄

HANDLE g_decodeEvent;//自己定义的一个事件，主要用来检测当DS播放完一个缓冲向读内存的解压程序发送一个有信号的标志位，然后解压程序就可以把
                    //解压得到的数据往buffer2中拷贝
HANDLE g_playEvent;//自己定义的一个事件，主要用来告知buffer2中是不是新数据，如果是新数据，那么拷到DS的播放缓冲中去
HANDLE g_hPlay=NULL;

char g_copyBuf[buffer_size];
char g_decodeBuf[buffer_size];

BOOL g_bPlaying = FALSE; //是否正在播放标志位

int ProcessBuffer(LPDIRECTSOUNDBUFFER8 g_pDSBuffer8, char *buffer);//缓冲填写函数声明


//播放线程
DWORD WINAPI PlayPCMThread(LPVOID lpParame)
{
	g_bPlaying = TRUE;
	DWORD res=5;
	LPVOID lplockbuf;
	DWORD len;
	int flag=1;
	//因为没什么数据好送，所以我先期把BUFFERNOTIFYSIZE*3大小的缓冲memset为0
	g_lpDSBuffer8->Lock(0,BUFFERNOTIFYSIZE*3,&lplockbuf,&len,NULL,NULL,0);
	memset(lplockbuf,0x0,len);
	g_lpDSBuffer8->Unlock(lplockbuf,len,NULL,0);
	g_lpDSBuffer8->SetCurrentPosition(0);
	//循环放，放g_lpDSBuffer8自己的缓存，一定要循环放
	g_lpDSBuffer8->Play(0,0,DSBPLAY_LOOPING);
//	g_lpDSBuffer8->Play(0,0,0);

	g_dwNextWriteOffset=BUFFERNOTIFYSIZE*3;//当然要改写g_dwNextWriteOffset的偏移位置了
	while(g_bPlaying)//如果还可以放，还有得放的话，就继续填DS的缓冲
	{
		res = WaitForMultipleObjects (MAX_AUDIO_BUF, g_event, FALSE, INFINITE);
		if((res >=WAIT_OBJECT_0)&&(res <=WAIT_OBJECT_0+3))//播放完一个，要求填缓冲 
		{
		    //printf("res=%d\n",res);
			SetEvent(g_decodeEvent);//把g_hEvent_nsl事件置为有信号--说明DS放完一个缓冲区了，那个unpack_input的工作又可以继续了
			flag=ProcessBuffer(g_lpDSBuffer8,g_copyBuf);//此函数实现了从copyBuf中拷了BUFFERNOTIFYSIZE个字节到g_pDSBuffer8中去
			res=5;
			if(flag==0)  g_bPlaying=false;
		}
	}
	return 1;
}

/*
 * Unpack input codes and pass them back as bytes.
 * Returns 1 if there is residual input, returns -1 if eof, else returns 0.
 */
int
unpack_input(
	unsigned char		*code,
	int			bits)
{
	static unsigned int	in_buffer = 0;
	static int		in_bits = 0;
	unsigned char		in_byte;

	if (in_bits < bits) {
		if (fread(&in_byte, sizeof (char), 1, stdin) != 1) {
			*code = 0;
			return (-1);
		}
		in_buffer |= (in_byte << in_bits);
		in_bits += 8;
	}
	*code = in_buffer & ((1 << bits) - 1);
	in_buffer >>= bits;
	in_bits -= bits;
	return (in_bits > 0);
}




int main(int argc, char* argv[])
{
	if( argc < 2 )
	{
		printf("Usage:\n");
		printf("g711Decode.exe filename a --G711A\n") ;
		printf("g711Decode.exe filename u --G711U\n") ;
		return 0 ;
	}
	SetConsoleTitle("G.711 audio file DecodeAndPlay");//设置窗口名称
	if (FAILED(hr =DirectSoundCreate8(NULL,&g_pDsd,NULL)))
		return false;
	if (FAILED(hr=g_pDsd->SetCooperativeLevel(FindWindow(NULL,"G.711 audio file DecodeAndPlay"),DSSCL_NORMAL)))
	{
		return false;
	}
	printf("G.711 audio file is playing now......\n");
	memset(&dsBufDesc,0,sizeof(dsBufDesc));
	dsBufDesc.dwSize=sizeof(dsBufDesc);
	dsBufDesc.dwFlags=DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY |DSBCAPS_GETCURRENTPOSITION2;
	dsBufDesc.dwBufferBytes=MAX_AUDIO_BUF*BUFFERNOTIFYSIZE; 
	dsBufDesc.lpwfxFormat=(WAVEFORMATEX*)malloc(sizeof(WAVEFORMATEX));
	dsBufDesc.lpwfxFormat->wFormatTag=WAVE_FORMAT_PCM; /* format type */  
	(dsBufDesc.lpwfxFormat)->nChannels=N_CHANNEL; /* number of channels (i.e. mono, stereo...) */         
	(dsBufDesc.lpwfxFormat)->nSamplesPerSec=SAMPLE_RATE; /* sample rate */    
	(dsBufDesc.lpwfxFormat)->nAvgBytesPerSec=SAMPLE_RATE*(BITS_PER_SAMPLE/8)*N_CHANNEL; /* for buffer estimation */    
	(dsBufDesc.lpwfxFormat)->nBlockAlign=(BITS_PER_SAMPLE/8)*N_CHANNEL; /* block size of data */       
	(dsBufDesc.lpwfxFormat)->wBitsPerSample=BITS_PER_SAMPLE; /* number of bits per sample of mono data */    
	(dsBufDesc.lpwfxFormat)->cbSize=0;	


	//创建DirectSound辅助缓冲区
	if(DS_OK != (hr=(g_pDsd->CreateSoundBuffer(&dsBufDesc,&lpBuffer,NULL))))
	{   
		switch(hr)
		{
			case DSERR_ALLOCATED:printf("DSERR_ALLOCATED\n");break;
			case DSERR_BADFORMAT:printf("DSERR_BADFORMAT\n");break;
				/*		case DSERR_BUFFERTOOSMALL:printf("DSERR_BUFFERTOOSMALL\n");break;*/
			case DSERR_CONTROLUNAVAIL:printf("DSERR_CONTROLUNAVAIL\n");break;
				/*		case DSERR_DS8_REQUIRED:printf("DSERR_DS8_REQUIRED\n");break;*/
			case DSERR_INVALIDCALL:printf("DSERR_INVALIDCALL\n");break;
			case DSERR_INVALIDPARAM:printf("DSERR_INVALIDPARAM\n");break;
			case DSERR_NOAGGREGATION:printf("DSERR_NOAGGREGATION\n");break;
			case DSERR_OUTOFMEMORY:printf("DSERR_OUTOFMEMORY\n");break;
			case DSERR_UNINITIALIZED:printf("DSERR_UNINITIALIZED\n");break;
			case DSERR_UNSUPPORTED:printf("DSERR_UNSUPPORTED\n");break;
		}
		return FALSE;
	}

	if (FAILED(hr =(lpBuffer->QueryInterface(IID_IDirectSoundBuffer8,(LPVOID*)&g_lpDSBuffer8))))
	{
		return false;
	}
	lpBuffer->Release();

	//设置DirectSound通知机制
	if(FAILED(hr=(g_lpDSBuffer8->QueryInterface(IID_IDirectSoundNotify,(LPVOID*)&g_lpDSNotify))))
	{
		switch(hr)
		{
			case E_NOINTERFACE:printf("E_NOINTERFACE hr\n");break;
			default:printf("an unknow error hr,%d\n",hr);break;
		}
		return false ;
	}

	for(int i =0;i<MAX_AUDIO_BUF;i++)
	{
		g_arrayPosNotify[i].dwOffset =i*BUFFERNOTIFYSIZE;
		g_event[i]=::CreateEvent(NULL,false,false,NULL);//默认安全级别，自动控制，初始为无信号，默认系统对象名
		g_arrayPosNotify[i].hEventNotify=g_event[i];
	}	
	g_lpDSNotify->SetNotificationPositions(MAX_AUDIO_BUF,g_arrayPosNotify);
	g_lpDSNotify->Release();

	//初始化buf
	memset(g_decodeBuf,0,buffer_size);
	memset(g_copyBuf,0,buffer_size);


	FILE * inpf;
	FILE * outf;

	inpf = fopen(argc == 2 ? argv[0] : argv[1], "rb");
	if( inpf == NULL )
	{
		printf("G.711 file cant open\n");
		return 1 ;
	}
	outf = fopen("nemozhu.pcm", "wb");
	int nFileType = stricmp( argc == 2 ? argv[1] : argv[2] , "a" ) == 0 ? 8 : 0 ;
	int	out_size =2;


	unsigned char* Buf;
	Buf = (unsigned char*)calloc(1024, sizeof(char));
	int nalLen = 0;
	int sumLen=0;

    //自己添加一个事件的变量
	g_decodeEvent = ::CreateEvent(NULL,TRUE,TRUE,NULL);//默认安全级别，人工控制，初始为有信号，默认系统对象名

	g_playEvent = ::CreateEvent(NULL,TRUE,FALSE,NULL);//默认安全级别，人工控制，初始为无信号，默认系统对象名

	//创建一个play的线程
	g_hPlay=CreateThread(0,0,PlayPCMThread,NULL,NULL,NULL);//如果调用失败，那么返回值是NULL

	while(!feof(inpf))
	{
		nalLen =fread(Buf,1,1,inpf);
		int iLinear =0 ;
		if( nFileType == 0 )
			iLinear = ulaw2linear(Buf[0]); //g711u
		else
			iLinear = alaw2linear(Buf[0]); //g711a

		memcpy(g_decodeBuf+sumLen,&iLinear,out_size);//拷贝到buf
		fwrite(&iLinear,1,out_size,outf);//写到文件

		sumLen +=out_size;
		if (sumLen>=buffer_size-1)
		{
			sumLen =0;
		    WaitForSingleObject(g_decodeEvent,INFINITE);//无限等待g_hEvent_nsl有信号
			memcpy(g_copyBuf,g_decodeBuf,buffer_size);

			SetEvent(g_playEvent);
			//if(buffer2_ready==true) {memcpy(buffer2,buffer1,buffer_size);buffer2_ready=false;}
			ResetEvent(g_decodeEvent);//把g_hEvent_nsl 设置为无信号状态   
		}

	}
	
	if(inpf)
		fclose(inpf);

	if(outf)
		fclose(outf);

	g_bPlaying=false;

	printf("The audio file is end ! \n");

	return 0;
}


//一个处理缓冲的函数，主要用于一旦有个缓冲播放完了之后，就往DS的该写缓冲的地方写入一个缓冲
int ProcessBuffer(LPDIRECTSOUNDBUFFER8 g_lpDSBuffer8, char *buffer)
{
	VOID* pDSLockedBuffer = NULL;
	VOID* pDSLockedBuffer2 = NULL;
	DWORD dwDSLockedBufferSize;
	DWORD dwDSLockedBufferSize2;
	HRESULT hr; 
	hr=g_lpDSBuffer8->Lock(g_dwNextWriteOffset,BUFFERNOTIFYSIZE,&pDSLockedBuffer,&dwDSLockedBufferSize, &pDSLockedBuffer2,&dwDSLockedBufferSize2,0);
	if(hr == DSERR_BUFFERLOST)
	{
		//DS变量重启一遍
		g_lpDSBuffer8->Restore();
		//重新lock一遍
        g_lpDSBuffer8->Lock(g_dwNextWriteOffset,BUFFERNOTIFYSIZE,&pDSLockedBuffer,&dwDSLockedBufferSize,&pDSLockedBuffer2,&dwDSLockedBufferSize2,0);
	}
	if(SUCCEEDED(hr))
	{
	       //if(buffer2_new==false) printf("buffer2_new====false\n");
		   //else printf("buffer2_new=============true\n");
		WaitForSingleObject(g_playEvent,500);//等到buffer2中变为新数据，但是最多等500ms
		memcpy((BYTE*)pDSLockedBuffer,buffer,buffer_size);//然后把buffer中的数据拷给DS的lockbuffer，注意这里buffer=copybuffer
		ResetEvent(g_playEvent);//重新把g_playEvent设置为无信号，也就是说copybuffer的数据不是新数据
		g_dwNextWriteOffset+=dwDSLockedBufferSize;
		g_dwNextWriteOffset %= (BUFFERNOTIFYSIZE * MAX_AUDIO_BUF);//实现一个类似循环缓冲的地方
		hr = g_lpDSBuffer8->Unlock(pDSLockedBuffer,dwDSLockedBufferSize,pDSLockedBuffer2,dwDSLockedBufferSize2);//unlock这一片缓冲，准备被播放
	}
	return 1;
}
