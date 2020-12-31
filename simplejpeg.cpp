 
//simplejpegenc.h

/*
 这是一个简单的jpeg编码程序，支持1：1：1采样的baseline彩色jpeg，输入只能是24bit的BMP文件
 代码结构只求能说明各步骤过程，并不做特别的优化，效率较为一般。
*/
#ifndef __JENC__
#define __JENC__

#include <string>
#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "jpeg.h"
#include "jpegformat.h"

using namespace std;

class JEnc
{
public:
 // bmFile:输入文件
 // jpgFile:输出文件
 // Q:质量
 void Invoke(string bmFile, string jpgFile, long Q)
 {
  FILE* pFile;            // 输入文件句柄

  if ((pFile = fopen(bmFile.c_str(),"rb")) == NULL)   // 打开文件
  { 
   throw("open bmp file error.");   
  }

  // 获取jpeg编码需要的bmp数据结构，jpeg要求数据缓冲区的高和宽为8或16的倍数(视采样方式而定)
  BMBUFINFO bmBuffInfo = GetBMBuffSize(pFile);    
  imgWidth = bmBuffInfo.imgWidth;     // 图像宽
  imgHeight = bmBuffInfo.imgHeight;    // 图像高
  buffWidth = bmBuffInfo.buffWidth;    // 缓冲宽
  buffHeight = bmBuffInfo.buffHeight;    // 缓冲高
  size_t buffSize = buffHeight * buffWidth * 3; // 缓冲长度，因为是24bits,所以*3
  BYTE* bmData = new BYTE[buffSize];    // 申请内存空间
  GetBMData(pFile, bmData, bmBuffInfo);   // 获取数据
  fclose(pFile);         // 关闭文件

  //=====================================
  // 计算编码需要的缓冲区，RGB信号需要别分别编码，所以需要3个缓冲区，这里只是1：1：1所以是一样大
  size_t yuvBuffSize = buffWidth * buffHeight; 
  BYTE* pYBuff = new BYTE[yuvBuffSize];
  BYTE* pUBuff = new BYTE[yuvBuffSize];
  BYTE* pVBuff = new BYTE[yuvBuffSize];
  // 将RGB信号转换为YUV信号
  BGR2YUV111(bmData,pYBuff,pUBuff,pVBuff);
  // 将信号分割为8x8的块
  DivBuff(pYBuff, buffWidth, buffHeight, DCTSIZE, DCTSIZE );  
  DivBuff(pUBuff, buffWidth, buffHeight, DCTSIZE, DCTSIZE );  
  DivBuff(pVBuff, buffWidth, buffHeight, DCTSIZE, DCTSIZE );  

  SetQuantTable(std_Y_QT,YQT, Q);         // 设置Y量化表
  SetQuantTable(std_UV_QT,UVQT, Q);        // 设置UV量化表  
  InitQTForAANDCT();            // 初始化AA&N需要的量化表
  pVLITAB=VLI_TAB + 2047;                             // 设置VLI_TAB的别名
  BuildVLITable();            // 计算VLI表  

  pOutFile = fopen(jpgFile.c_str(),"wb");

  // 写入各段
  WriteSOI();              
  WriteAPP0();
  WriteDQT();
  WriteSOF();
  WriteDHT();
  WriteSOS();

  // 计算Y/UV信号的交直分量的huffman表，这里使用标准的huffman表，并不是计算得出，缺点是文件略长，但是速度快
  BuildSTDHuffTab(STD_DC_Y_NRCODES,STD_DC_Y_VALUES,STD_DC_Y_HT);
  BuildSTDHuffTab(STD_AC_Y_NRCODES,STD_AC_Y_VALUES,STD_AC_Y_HT);
  BuildSTDHuffTab(STD_DC_UV_NRCODES,STD_DC_UV_VALUES,STD_DC_UV_HT);
  BuildSTDHuffTab(STD_AC_UV_NRCODES,STD_AC_UV_VALUES,STD_AC_UV_HT);

  // 处理单元数据
  ProcessData(pYBuff,pUBuff,pVBuff);  
  WriteEOI();

  fclose(pOutFile);
  delete[] bmData;
 }

private:

 FILE* pOutFile;
 int buffWidth;
 int buffHeight;
 int imgWidth;
 int imgHeight;


 // 获取BMP文件输出缓冲区信息
 BMBUFINFO GetBMBuffSize(FILE* pFile)
 {
  BITMAPFILEHEADER bmHead;       //文件头信息块 
  BITMAPINFOHEADER bmInfo;       //图像描述信息块
  BMBUFINFO   bmBuffInfo;
  UINT colSize = 0;
  UINT rowSize = 0;

  fseek(pFile,0,SEEK_SET);       //将读写指针指向文件头部
  fread(&bmHead,sizeof(bmHead),1,pFile);    //读取文件头信息块
  fread(&bmInfo,sizeof(bmInfo),1,pFile);    //读取位图信息块

  // 计算填充后列数，jpeg编码要求缓冲区的高和宽为8或16的倍数
  if (bmInfo.biWidth % 8 == 0)
  {
   colSize = bmInfo.biWidth;
  }
  else
  {
   colSize = bmInfo.biWidth + 8 - (bmInfo.biWidth % 8);
  }

  // 计算填充后行数
  if (bmInfo.biHeight % 8 == 0)
  {
   rowSize = bmInfo.biHeight;
  }
  else
  {
   rowSize = bmInfo.biHeight + 8 - (bmInfo.biHeight % 8);
  }

  bmBuffInfo.BitCount = 24;
  bmBuffInfo.buffHeight = rowSize;   // 缓冲区高
  bmBuffInfo.buffWidth = colSize;    // 缓冲区宽
  bmBuffInfo.imgHeight = bmInfo.biHeight;  // 图像高
  bmBuffInfo.imgWidth = bmInfo.biWidth;  // 图像宽

  return bmBuffInfo;
 }

 // 获取图像数据
 void GetBMData(FILE* pFile, BYTE* pBuff, BMBUFINFO buffInfo)
 { 
  BITMAPFILEHEADER bmHead;       // 文件头信息块 
  BITMAPINFOHEADER bmInfo;       // 图像描述信息块
  size_t    dataLen  = 0;    // 文件数据区长度
  long    alignBytes = 0;     // 为对齐4字节需要补足的字节数 
  UINT    lineSize  = 0;  

  fseek(pFile,0,SEEK_SET);       // 将读写指针指向文件头部
  fread(&bmHead,sizeof(bmHead),1,pFile);    // 读取文件头信息块
  fread(&bmInfo,sizeof(bmInfo),1,pFile);    // 读取位图信息块

  //计算对齐的字节数
  alignBytes = (((bmInfo.biWidth * bmInfo.biBitCount) + 31) & ~31) / 8L
   - (bmInfo.biWidth * bmInfo.biBitCount) / 8L; // 计算图象文件数据段行补齐字节数  

  //计算数据缓冲区长度        
  lineSize = bmInfo.biWidth * 3;      
  // 因为bmp文件数据是倒置的所以从最后一行开始读
  for (int i = bmInfo.biHeight - 1; i >= 0; --i)
  {   
   fread(&pBuff[buffInfo.buffWidth * i * 3],lineSize,1,pFile);   
   fseek(pFile,alignBytes,SEEK_CUR);             // 跳过对齐字节            
  }  
 }

 // 转换色彩空间BGR-YUV,111采样
 void BGR2YUV111(BYTE* pBuf, BYTE* pYBuff, BYTE* pUBuff, BYTE* pVBuff)
 {
  DOUBLE tmpY   = 0;         //临时变量
  DOUBLE tmpU   = 0;
  DOUBLE tmpV   = 0;
  BYTE tmpB   = 0;       
  BYTE tmpG   = 0;
  BYTE tmpR   = 0;
  UINT i    = 0;
  size_t elemNum = _msize(pBuf) / 3;  //缓冲长度

  for (i = 0; i < elemNum; i++)
  {
   tmpB = pBuf[i * 3];
   tmpG = pBuf[i * 3 + 1];
   tmpR = pBuf[i * 3 + 2];
   tmpY = 0.299 * tmpR + 0.587 * tmpG + 0.114 * tmpB;
   tmpU = -0.1687 * tmpR - 0.3313 * tmpG + 0.5 * tmpB + 128;
   tmpV = 0.5 * tmpR - 0.4187 * tmpG - 0.0813 * tmpB + 128;
   //if(tmpY > 255){tmpY = 255;}     //输出限制
   //if(tmpU > 255){tmpU = 255;}
   //if(tmpV > 255){tmpV = 255;}
   //if(tmpY < 0){tmpY = 0;}  
   //if(tmpU < 0){tmpU = 0;}  
   //if(tmpV < 0){tmpV = 0;}
   pYBuff[i] = tmpY;           //放入输入缓冲
   pUBuff[i] = tmpU;
   pVBuff[i] = tmpV;
  }
 }

 //********************************************************************
 // 方法名称:DivBuff 
 // 最后修订日期:2003.5.3 
 //
 // 参数说明:
 // lpBuf:输入缓冲,处理后的数据也存储在这里
 // width:缓冲X方向长度
 // height:缓冲Y方向长度
 // xLen:X方向切割长度
 // yLen:Y方向切割长度
 //********************************************************************
 void DivBuff(BYTE* pBuf,UINT width,UINT height,UINT xLen,UINT yLen)
 {
  UINT xBufs   = width / xLen;             //X轴方向上切割数量
  UINT yBufs   = height / yLen;            //Y轴方向上切割数量
  UINT tmpBufLen  = xBufs * xLen * yLen;           //计算临时缓冲区长度
  BYTE* tmpBuf  = new BYTE[tmpBufLen];           //创建临时缓冲
  UINT i    = 0;               //临时变量
  UINT j    = 0;
  UINT k    = 0; 
  UINT n    = 0;
  UINT bufOffset  = 0;               //切割开始的偏移量

  for (i = 0; i < yBufs; ++i)               //循环Y方向切割数量
  {
   n = 0;                   //复位临时缓冲区偏移量
   for (j = 0; j < xBufs; ++j)              //循环X方向切割数量  
   {   
    bufOffset = yLen * xLen * i * xBufs + j * xLen;        //计算单元信号块的首行偏移量  
    for (k = 0; k < yLen; ++k)             //循环块的行数
    {
     memcpy(&tmpBuf[n],&pBuf[bufOffset],xLen);        //复制一行到临时缓冲
     n += xLen;                //计算临时缓冲区偏移量
     bufOffset += width;              //计算输入缓冲区偏移量
    }
   }
   memcpy(&pBuf[i * tmpBufLen],tmpBuf,tmpBufLen);         //复制临时缓冲数据到输入缓冲
  } 
  delete[] tmpBuf;                 //删除临时缓冲
 } 

 //********************************************************************
 // 方法名称:SetQuantTable 
 //
 // 方法说明:根据所需质量设置量化表
 //
 // 参数说明:
 // std_QT:标准量化表
 // QT:输出量化表
 // Q:质量参数
 //********************************************************************
 // 根据所需质量设置量化表
 void SetQuantTable(const BYTE* std_QT,BYTE* QT, int Q)
 {
  INT tmpVal = 0;                  //临时变量
  DWORD i    = 0; 

  if (Q < 1) Q = 1;               //限制质量系数
  if (Q > 100) Q = 100;

  //非线性映射 1->5000, 10->500, 25->200, 50->100, 75->50, 100->0
  if (Q < 50)
  {
   Q = 5000 / Q;
  }
  else
  {
   Q = 200 - Q * 2;
  }

  for (i = 0; i < DCTBLOCKSIZE; ++i)
  {
   tmpVal = (std_QT[i] * Q + 50L) / 100L;

   if (tmpVal < 1)                 //数值范围限定
   {
    tmpVal = 1L;
   }
   if (tmpVal > 255)
   {
    tmpVal = 255L;
   }
   QT[FZBT[i]] = static_cast<BYTE>(tmpVal);
  } 
 }

 //为float AA&N IDCT算法初始化量化表
 void InitQTForAANDCT()
 {
  UINT i = 0;           //临时变量
  UINT j = 0;
  UINT k = 0; 

  for (i = 0; i < DCTSIZE; i++)  //初始化亮度信号量化表
  {
   for (j = 0; j < DCTSIZE; j++)
   {
    YQT_DCT[k] = (FLOAT) (1.0 / ((DOUBLE) YQT[FZBT[k]] *
     aanScaleFactor[i] * aanScaleFactor[j] * 8.0));       
    ++k;
   }
  } 

  k = 0;
  for (i = 0; i < DCTSIZE; i++)  //初始化色差信号量化表
  {
   for (j = 0; j < DCTSIZE; j++)
   {
    UVQT_DCT[k] = (FLOAT) (1.0 / ((DOUBLE) UVQT[FZBT[k]] *
     aanScaleFactor[i] * aanScaleFactor[j] * 8.0));       
    ++k;
   }
  } 
 }

 //写文件开始标记
 void WriteSOI(void)
 { 
  fwrite(&SOITAG,sizeof(SOITAG),1,this->pOutFile);
 }
 //写APP0段
 void WriteAPP0(void)
 {
  JPEGAPP0 APP0;
  APP0.segmentTag  = 0xE0FF;
  APP0.length    = 0x1000;
  APP0.id[0]    = 'J';
  APP0.id[1]    = 'F';
  APP0.id[2]    = 'I';
  APP0.id[3]    = 'F';
  APP0.id[4]    = 0;
  APP0.ver     = 0x0101;
  APP0.densityUnit = 0x00;
  APP0.densityX   = 0x0100;
  APP0.densityY   = 0x0100;
  APP0.thp     = 0x00;
  APP0.tvp     = 0x00;
  fwrite(&APP0,sizeof(APP0),1,this->pOutFile);
 }

 //写入DQT段
 void WriteDQT(void)
 {
  UINT i = 0;
  JPEGDQT_8BITS DQT_Y;
  DQT_Y.segmentTag = 0xDBFF;
  DQT_Y.length   = 0x4300;
  DQT_Y.tableInfo  = 0x00;
  for (i = 0; i < DCTBLOCKSIZE; i++)
  {
   DQT_Y.table[i] = YQT[i];
  }    
  fwrite(&DQT_Y,sizeof(DQT_Y),1,this->pOutFile);

  DQT_Y.tableInfo  = 0x01;
  for (i = 0; i < DCTBLOCKSIZE; i++)
  {
   DQT_Y.table[i] = UVQT[i];
  }
  fwrite(&DQT_Y,sizeof(DQT_Y),1,this->pOutFile); 
 }

 //写入SOF段
 void WriteSOF(void)
 {
  JPEGSOF0_24BITS SOF;
  SOF.segmentTag = 0xC0FF;
  SOF.length   = 0x1100;
  SOF.precision  = 0x08;
  SOF.height   = Intel2Moto(USHORT(this->imgHeight));
  SOF.width    = Intel2Moto(USHORT(this->imgWidth)); 
  SOF.sigNum   = 0x03;
  SOF.YID     = 0x01; 
  SOF.QTY     = 0x00;
  SOF.UID     = 0x02;
  SOF.QTU     = 0x01;
  SOF.VID     = 0x03;
  SOF.QTV     = 0x01;
  SOF.HVU     = 0x11;
  SOF.HVV     = 0x11;
  /*switch (this->SamplingType)
  {
  case 1:
  SOF.HVY   = 0x11;
  break;

  case 2:
  SOF.HVY   = 0x12;
  break;

  case 3:
  SOF.HVY   = 0x21;
  break;

  case 4:
  SOF.HVY   = 0x22;
  break;
  }*/
  SOF.HVY   = 0x11;
  fwrite(&SOF,sizeof(SOF),1,this->pOutFile);
 }

 //写入DHT段
 void WriteDHT(void)
 {
  UINT i = 0;

  JPEGDHT DHT;
  DHT.segmentTag = 0xC4FF;
  DHT.length   = Intel2Moto(19 + 12);
  DHT.tableInfo  = 0x00;
  for (i = 0; i < 16; i++)
  {
   DHT.huffCode[i] = STD_DC_Y_NRCODES[i + 1];
  } 
  fwrite(&DHT,sizeof(DHT),1,this->pOutFile);
  for (i = 0; i <= 11; i++)
  {
   WriteByte(STD_DC_Y_VALUES[i]);  
  }  
  //------------------------------------------------
  DHT.tableInfo  = 0x01;
  for (i = 0; i < 16; i++)
  {
   DHT.huffCode[i] = STD_DC_UV_NRCODES[i + 1];
  }
  fwrite(&DHT,sizeof(DHT),1,this->pOutFile);
  for (i = 0; i <= 11; i++)
  {
   WriteByte(STD_DC_UV_VALUES[i]);  
  } 
  //----------------------------------------------------
  DHT.length   = Intel2Moto(19 + 162);
  DHT.tableInfo  = 0x10;
  for (i = 0; i < 16; i++)
  {
   DHT.huffCode[i] = STD_AC_Y_NRCODES[i + 1];
  }
  fwrite(&DHT,sizeof(DHT),1,this->pOutFile);
  for (i = 0; i <= 161; i++)
  {
   WriteByte(STD_AC_Y_VALUES[i]);  
  }  
  //-----------------------------------------------------
  DHT.tableInfo  = 0x11;
  for (i = 0; i < 16; i++)
  {
   DHT.huffCode[i] = STD_AC_UV_NRCODES[i + 1];
  }
  fwrite(&DHT,sizeof(DHT),1,this->pOutFile); 
  for (i = 0; i <= 161; i++)
  {
   WriteByte(STD_AC_UV_VALUES[i]);  
  } 
 }

 //写入SOS段
 void WriteSOS(void)
 {
  JPEGSOS_24BITS SOS;
  SOS.segmentTag   = 0xDAFF;
  SOS.length    = 0x0C00;
  SOS.sigNum    = 0x03;
  SOS.YID     = 0x01;
  SOS.HTY     = 0x00;
  SOS.UID     = 0x02;
  SOS.HTU     = 0x11;
  SOS.VID     = 0x03;
  SOS.HTV     = 0x11;
  SOS.Se     = 0x3F;
  SOS.Ss     = 0x00;
  SOS.Bf     = 0x00;
  fwrite(&SOS,sizeof(SOS),1,this->pOutFile); 
 }
 //写入文件结束标记
 void WriteEOI(void)
 {
  fwrite(&EOITAG,sizeof(EOITAG),1,this->pOutFile);
 }


 // 将高8位和低8位交换
 USHORT Intel2Moto(USHORT val)
 {
  BYTE highBits = BYTE(val / 256);
  BYTE lowBits = BYTE(val % 256);

  return lowBits * 256 + highBits;
 }

 //写1字节到文件
 void WriteByte(BYTE val)
 {   
  fwrite(&val,sizeof(val),1,this->pOutFile);
 }

 // 生成标准Huffman表
 void BuildSTDHuffTab(BYTE* nrcodes,BYTE* stdTab,HUFFCODE* huffCode)
 {
  BYTE i     = 0;             //临时变量
  BYTE j     = 0;
  BYTE k     = 0;
  USHORT code   = 0; 

  for (i = 1; i <= 16; i++)
  { 
   for (j = 1; j <= nrcodes[i]; j++)
   {   
    huffCode[stdTab[k]].code = code;
    huffCode[stdTab[k]].length = i;
    ++k;
    ++code;
   }
   code*=2;
  } 

  for (i = 0; i < k; i++)
  {
   huffCode[i].val = stdTab[i];  
  }
 }

 // 处理DU(数据单元)
 void ProcessDU(FLOAT* lpBuf,FLOAT* quantTab,HUFFCODE* dcHuffTab,HUFFCODE* acHuffTab,SHORT* DC)
 {
  BYTE i    = 0;              //临时变量
  UINT j    = 0;
  SHORT diffVal = 0;                //DC差异值  
  BYTE acLen  = 0;               //熵编码后AC中间符号的数量
  SHORT sigBuf[DCTBLOCKSIZE];              //量化后信号缓冲
  ACSYM acSym[DCTBLOCKSIZE];              //AC中间符号缓冲 

  FDCT(lpBuf);                 //离散余弦变换

  for (i = 0; i < DCTBLOCKSIZE; i++)            //量化操作
  {          
   sigBuf[FZBT[i]] = (lpBuf[i] * quantTab[i] + 16384.5) - 16384;  
  }
  //-----------------------------------------------------
  //对DC信号编码，写入文件
  //DPCM编码 
  diffVal = sigBuf[0] - *DC;
  *DC = sigBuf[0];
  //搜索Huffman表，写入相应的码字
  if (diffVal == 0)
  {  
   WriteBits(dcHuffTab[0]);  
  }
  else
  {   
   WriteBits(dcHuffTab[pVLITAB[diffVal]]);  
   WriteBits(BuildSym2(diffVal));    
  }
  //-------------------------------------------------------
  //对AC信号编码并写入文件
  for (i = 63; (i > 0) && (sigBuf[i] == 0); i--) //判断ac信号是否全为0
  {
   //注意，空循环
  }
  if (i == 0)                //如果全为0
  {
   WriteBits(acHuffTab[0x00]);           //写入块结束标记  
  }
  else
  { 
   RLEComp(sigBuf,&acSym[0],acLen);         //对AC运行长度编码 
   for (j = 0; j < acLen; j++)           //依次对AC中间符号Huffman编码
   {   
    if (acSym[j].codeLen == 0)          //是否有连续16个0
    {   
     WriteBits(acHuffTab[0xF0]);         //写入(15,0)    
    }
    else
    {
     WriteBits(acHuffTab[acSym[j].zeroLen * 16 + acSym[j].codeLen]); //
     WriteBits(BuildSym2(acSym[j].amplitude));    
    }   
   }
   if (i != 63)              //如果最后位以0结束就写入EOB
   {
    WriteBits(acHuffTab[0x00]);          
   }
  }
 }

 //********************************************************************
 // 方法名称:ProcessData 
 //
 // 方法说明:处理图像数据FDCT-QUANT-HUFFMAN
 //
 // 参数说明:
 // lpYBuf:亮度Y信号输入缓冲
 // lpUBuf:色差U信号输入缓冲
 // lpVBuf:色差V信号输入缓冲
 //********************************************************************
 void ProcessData(BYTE* lpYBuf,BYTE* lpUBuf,BYTE* lpVBuf)
 { 
  size_t yBufLen = _msize(lpYBuf);           //亮度Y缓冲长度
  size_t uBufLen = _msize(lpUBuf);           //色差U缓冲长度          
  size_t vBufLen = _msize(lpVBuf);           //色差V缓冲长度
  FLOAT dctYBuf[DCTBLOCKSIZE];            //Y信号FDCT编码临时缓冲
  FLOAT dctUBuf[DCTBLOCKSIZE];            //U信号FDCT编码临时缓冲 
  FLOAT dctVBuf[DCTBLOCKSIZE];            //V信号FDCT编码临时缓冲 
  UINT mcuNum   = 0;             //存放MCU的数量 
  SHORT yDC   = 0;             //Y信号的当前块的DC
  SHORT uDC   = 0;             //U信号的当前块的DC
  SHORT vDC   = 0;             //V信号的当前块的DC 
  BYTE yCounter  = 0;             //YUV信号各自的写入计数器
  BYTE uCounter  = 0;
  BYTE vCounter  = 0;
  UINT i    = 0;             //临时变量              
  UINT j    = 0;                 
  UINT k    = 0;
  UINT p    = 0;
  UINT m    = 0;
  UINT n    = 0;
  UINT s    = 0; 

  mcuNum = (this->buffHeight * this->buffWidth * 3)
   / (DCTBLOCKSIZE * 3);         //计算MCU的数量

  for (p = 0;p < mcuNum; p++)        //依次生成MCU并写入
  {
   yCounter = 1;//MCUIndex[SamplingType][0];   //按采样方式初始化各信号计数器
   uCounter = 1;//MCUIndex[SamplingType][1];
   vCounter = 1;//MCUIndex[SamplingType][2];

   for (; i < yBufLen; i += DCTBLOCKSIZE)
   {
    for (j = 0; j < DCTBLOCKSIZE; j++)
    {
     dctYBuf[j] = FLOAT(lpYBuf[i + j] - 128);
    }   
    if (yCounter > 0)
    {    
     --yCounter;
     ProcessDU(dctYBuf,YQT_DCT,STD_DC_Y_HT,STD_AC_Y_HT,&yDC);     
    }
    else
    {
     break;
    }
   }  
   //------------------------------------------------------------------  
   for (; m < uBufLen; m += DCTBLOCKSIZE)
   {
    for (n = 0; n < DCTBLOCKSIZE; n++)
    {
     dctUBuf[n] = FLOAT(lpUBuf[m + n] - 128);
    }    
    if (uCounter > 0)
    {    
     --uCounter;
     ProcessDU(dctUBuf,UVQT_DCT,STD_DC_UV_HT,STD_AC_UV_HT,&uDC);         
    }
    else
    {
     break;
    }
   }  
   //-------------------------------------------------------------------  
   for (; s < vBufLen; s += DCTBLOCKSIZE)
   {
    for (k = 0; k < DCTBLOCKSIZE; k++)
    {
     dctVBuf[k] = FLOAT(lpVBuf[s + k] - 128);
    }
    if (vCounter > 0)
    {
     --vCounter;
     ProcessDU(dctVBuf,UVQT_DCT,STD_DC_UV_HT,STD_AC_UV_HT,&vDC);        
    }
    else
    {
     break;
    }
   }  
  } 
 }

 // 8x8的浮点离散余弦变换
 void FDCT(FLOAT* lpBuff)
 {
  FLOAT tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  FLOAT tmp10, tmp11, tmp12, tmp13;
  FLOAT z1, z2, z3, z4, z5, z11, z13;
  FLOAT* dataptr;
  int ctr;

  /* 第一部分，对行进行计算 */
  dataptr = lpBuff;
  for (ctr = DCTSIZE-1; ctr >= 0; ctr--)
  {
   tmp0 = dataptr[0] + dataptr[7];
   tmp7 = dataptr[0] - dataptr[7];
   tmp1 = dataptr[1] + dataptr[6];
   tmp6 = dataptr[1] - dataptr[6];
   tmp2 = dataptr[2] + dataptr[5];
   tmp5 = dataptr[2] - dataptr[5];
   tmp3 = dataptr[3] + dataptr[4];
   tmp4 = dataptr[3] - dataptr[4];

   /* 对偶数项进行运算 */    
   tmp10 = tmp0 + tmp3; /* phase 2 */
   tmp13 = tmp0 - tmp3;
   tmp11 = tmp1 + tmp2;
   tmp12 = tmp1 - tmp2;

   dataptr[0] = tmp10 + tmp11; /* phase 3 */
   dataptr[4] = tmp10 - tmp11;

   z1 = (tmp12 + tmp13) * (0.707106781); /* c4 */
   dataptr[2] = tmp13 + z1; /* phase 5 */
   dataptr[6] = tmp13 - z1;

   /* 对奇数项进行计算 */
   tmp10 = tmp4 + tmp5; /* phase 2 */
   tmp11 = tmp5 + tmp6;
   tmp12 = tmp6 + tmp7;

   z5 = (tmp10 - tmp12) * ( 0.382683433); /* c6 */
   z2 = (0.541196100) * tmp10 + z5; /* c2-c6 */
   z4 = (1.306562965) * tmp12 + z5; /* c2+c6 */
   z3 = tmp11 * (0.707106781); /* c4 */

   z11 = tmp7 + z3;  /* phase 5 */
   z13 = tmp7 - z3;

   dataptr[5] = z13 + z2; /* phase 6 */
   dataptr[3] = z13 - z2;
   dataptr[1] = z11 + z4;
   dataptr[7] = z11 - z4;

   dataptr += DCTSIZE; /* 将指针指向下一行 */
  }

  /* 第二部分，对列进行计算 */
  dataptr = lpBuff;
  for (ctr = DCTSIZE-1; ctr >= 0; ctr--)
  {
   tmp0 = dataptr[DCTSIZE*0] + dataptr[DCTSIZE*7];
   tmp7 = dataptr[DCTSIZE*0] - dataptr[DCTSIZE*7];
   tmp1 = dataptr[DCTSIZE*1] + dataptr[DCTSIZE*6];
   tmp6 = dataptr[DCTSIZE*1] - dataptr[DCTSIZE*6];
   tmp2 = dataptr[DCTSIZE*2] + dataptr[DCTSIZE*5];
   tmp5 = dataptr[DCTSIZE*2] - dataptr[DCTSIZE*5];
   tmp3 = dataptr[DCTSIZE*3] + dataptr[DCTSIZE*4];
   tmp4 = dataptr[DCTSIZE*3] - dataptr[DCTSIZE*4];

   /* 对偶数项进行运算 */    
   tmp10 = tmp0 + tmp3; /* phase 2 */
   tmp13 = tmp0 - tmp3;
   tmp11 = tmp1 + tmp2;
   tmp12 = tmp1 - tmp2;

   dataptr[DCTSIZE*0] = tmp10 + tmp11; /* phase 3 */
   dataptr[DCTSIZE*4] = tmp10 - tmp11;

   z1 = (tmp12 + tmp13) * (0.707106781); /* c4 */
   dataptr[DCTSIZE*2] = tmp13 + z1; /* phase 5 */
   dataptr[DCTSIZE*6] = tmp13 - z1;

   /* 对奇数项进行计算 */
   tmp10 = tmp4 + tmp5; /* phase 2 */
   tmp11 = tmp5 + tmp6;
   tmp12 = tmp6 + tmp7;

   z5 = (tmp10 - tmp12) * (0.382683433); /* c6 */
   z2 = (0.541196100) * tmp10 + z5; /* c2-c6 */
   z4 = (1.306562965) * tmp12 + z5; /* c2+c6 */
   z3 = tmp11 * (0.707106781); /* c4 */

   z11 = tmp7 + z3;  /* phase 5 */
   z13 = tmp7 - z3;

   dataptr[DCTSIZE*5] = z13 + z2; /* phase 6 */
   dataptr[DCTSIZE*3] = z13 - z2;
   dataptr[DCTSIZE*1] = z11 + z4;
   dataptr[DCTSIZE*7] = z11 - z4;

   ++dataptr;   /* 将指针指向下一列 */
  }
 }

 //********************************************************************
 // 方法名称:WriteBits 
 //
 // 方法说明:写入二进制流
 //
 // 参数说明:
 // value:AC/DC信号的振幅
 //********************************************************************
 void WriteBits(HUFFCODE huffCode)
 {  
  WriteBitsStream(huffCode.code,huffCode.length); 
 }
 void WriteBits(SYM2 sym)
 {
  WriteBitsStream(sym.amplitude,sym.codeLen); 
 }

 //********************************************************************
 // 方法名称:WriteBitsStream 
 //
 // 方法说明:写入二进制流
 //
 // 参数说明:
 // value:需要写入的值
 // codeLen:二进制长度
 //********************************************************************
 void WriteBitsStream(USHORT value,BYTE codeLen)
 { 
  CHAR posval;//bit position in the bitstring we read, should be<=15 and >=0 
  posval=codeLen-1;
  while (posval>=0)
  {
   if (value & mask[posval])
   {
    bytenew|=mask[bytepos];
   }
   posval--;bytepos--;
   if (bytepos<0) 
   { 
    if (bytenew==0xFF)
    {
     WriteByte(0xFF);
     WriteByte(0);
    }
    else
    {
     WriteByte(bytenew);
    }
    bytepos=7;bytenew=0;
   }
  }
 }

 //********************************************************************
 // 方法名称:RLEComp 
 //
 // 方法说明:使用RLE算法对AC压缩,假设输入数据1,0,0,0,3,0,5 
 //     输出为(0,1)(3,3)(1,5),左位表示右位数据前0的个数
 //          左位用4bits表示,0的个数超过表示范围则输出为(15,0)
 //          其余的0数据在下一个符号中表示.
 //
 // 参数说明:
 // lpbuf:输入缓冲,8x8变换信号缓冲
 // lpOutBuf:输出缓冲,结构数组,结构信息见头文件
 // resultLen:输出缓冲长度,即编码后符号的数量
 //********************************************************************
 void RLEComp(SHORT* lpbuf,ACSYM* lpOutBuf,BYTE &resultLen)
 {  
  BYTE zeroNum     = 0;       //0行程计数器
  UINT EOBPos      = 0;       //EOB出现位置 
  const BYTE MAXZEROLEN = 15;          //最大0行程
  UINT i        = 0;      //临时变量
  UINT j        = 0;

  EOBPos = DCTBLOCKSIZE - 1;          //设置起始位置，从最后一个信号开始
  for (i = EOBPos; i > 0; i--)         //从最后的AC信号数0的个数
  {
   if (lpbuf[i] == 0)           //判断数据是否为0
   {
    --EOBPos;            //向前一位
   }
   else              //遇到非0，跳出
   {
    break;                   
   }
  }

  for (i = 1; i <= EOBPos; i++)         //从第二个信号，即AC信号开始编码
  {
   if (lpbuf[i] == 0 && zeroNum < MAXZEROLEN)     //如果信号为0并连续长度小于15
   {
    ++zeroNum;   
   }
   else
   {   
    lpOutBuf[j].zeroLen = zeroNum;       //0行程（连续长度）
    lpOutBuf[j].codeLen = ComputeVLI(lpbuf[i]);    //幅度编码长度
    lpOutBuf[j].amplitude = lpbuf[i];      //振幅      
    zeroNum = 0;           //0计数器复位
    ++resultLen;           //符号数量++
    ++j;             //符号计数
   }
  } 
 }

 //********************************************************************
 // 方法名称:BuildSym2 
 //
 // 方法说明:将信号的振幅VLI编码,返回编码长度和信号振幅的反码
 //
 // 参数说明:
 // value:AC/DC信号的振幅
 //********************************************************************
 SYM2 BuildSym2(SHORT value)
 {
  SYM2 Symbol;  

  Symbol.codeLen = ComputeVLI(value);              //获取编码长度
  Symbol.amplitude = 0;
  if (value >= 0)
  {
   Symbol.amplitude = value;
  }
  else
  {
   Symbol.amplitude = SHORT(pow(2,Symbol.codeLen)-1) + value;  //计算反码
  }

  return Symbol;
 }


 //返回符号的长度
 BYTE ComputeVLI(SHORT val)
 { 
  BYTE binStrLen = 0;
  val = abs(val); 
  //获取二进制码长度   
  if(val == 1)
  {
   binStrLen = 1;  
  }
  else if(val >= 2 && val <= 3)
  {
   binStrLen = 2;
  }
  else if(val >= 4 && val <= 7)
  {
   binStrLen = 3;
  }
  else if(val >= 8 && val <= 15)
  {
   binStrLen = 4;
  }
  else if(val >= 16 && val <= 31)
  {
   binStrLen = 5;
  }
  else if(val >= 32 && val <= 63)
  {
   binStrLen = 6;
  }
  else if(val >= 64 && val <= 127)
  {
   binStrLen = 7;
  }
  else if(val >= 128 && val <= 255)
  {
   binStrLen = 8;
  }
  else if(val >= 256 && val <= 511)
  {
   binStrLen = 9;
  }
  else if(val >= 512 && val <= 1023)
  {
   binStrLen = 10;
  }
  else if(val >= 1024 && val <= 2047)
  {
   binStrLen = 11;
  }

  return binStrLen;
 }

 //********************************************************************
 // 方法名称:BuildVLITable 
 //
 // 方法说明:生成VLI表
 //
 // 参数说明:
 //********************************************************************
 void BuildVLITable(void)
 {
  int i   = 0;

  for (i = 0; i < DC_MAX_QUANTED; ++i)
  {
   pVLITAB[i] = ComputeVLI(i);
  }

  for (i = DC_MIN_QUANTED; i < 0; ++i)
  {
   pVLITAB[i] = ComputeVLI(i);
  }
 }
};

#endif // __JENC__

 


//Jpeg.h

typedef struct tagBMBUFINFO
{
    UINT imgWidth;
    UINT imgHeight;
 UINT buffWidth;
 UINT buffHeight;
    WORD BitCount;
    BYTE padSize;    
}BMBUFINFO;

// DCT转换尺寸
static const BYTE DCTSIZE = 8;
// DCT转换块长度
static const BYTE DCTBLOCKSIZE = 64;  

//Huffman码结构
typedef struct tagHUFFCODE
{
 WORD code;  // huffman 码字
 BYTE length;  // 编码长度
 WORD val;   // 码字对应的值
}HUFFCODE;
//AC信号中间符号结构
typedef struct tagACSYM
{
 BYTE zeroLen;  //0行程
 BYTE codeLen;  //幅度编码长度
 SHORT amplitude;//振幅
}ACSYM;

//DC/AC 中间符号2描述结构
typedef struct tagSYM2
{
 SHORT amplitude;//振幅
 BYTE codeLen;  //振幅长度(二进制形式的振幅数据的位数)
}SYM2;

// 存放VLI表
BYTE VLI_TAB[4096];
BYTE* pVLITAB;                        //VLI_TAB的别名,使下标在-2048-2048

// 存放2个量化表
BYTE YQT[DCTBLOCKSIZE]; 
BYTE UVQT[DCTBLOCKSIZE]; 
// 存放2个FDCT变换要求格式的量化表
FLOAT YQT_DCT[DCTBLOCKSIZE];
FLOAT UVQT_DCT[DCTBLOCKSIZE];
//存放4个Huffman表
HUFFCODE STD_DC_Y_HT[12];
HUFFCODE STD_DC_UV_HT[12];
HUFFCODE STD_AC_Y_HT[256];
HUFFCODE STD_AC_UV_HT[256];

static BYTE bytenew=0; // The byte that will be written in the JPG file
static CHAR bytepos=7; //bit position in the byte we write (bytenew)
//should be<=7 and >=0
static USHORT mask[16]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};

static const DOUBLE aanScaleFactor[8] = {1.0, 1.387039845, 1.306562965, 1.175875602,
1.0, 0.785694958, 0.541196100, 0.275899379};

//量化后DC范围在-2^11 - 2^11 - 1之间,量化后AC范围在-2^10 - 2^10 - 1之间
static const INT AC_MAX_QUANTED = 1023;   //量化后AC的最大值
static const INT AC_MIN_QUANTED = -1024;   //量化后AC的最小值
static const INT DC_MAX_QUANTED = 2047;   //量化后DC的最大值
static const INT DC_MIN_QUANTED = -2048;   //量化后DC的最小值


//标准亮度信号量化模板
const static BYTE std_Y_QT[64] = 
{
 16, 11, 10, 16, 24, 40, 51, 61,
  12, 12, 14, 19, 26, 58, 60, 55,
  14, 13, 16, 24, 40, 57, 69, 56,
  14, 17, 22, 29, 51, 87, 80, 62,
  18, 22, 37, 56, 68, 109,103,77,
  24, 35, 55, 64, 81, 104,113,92,
  49, 64, 78, 87, 103,121,120,101,
  72, 92, 95, 98, 112,100,103,99
};

//标准色差信号量化模板
const static BYTE std_UV_QT[64] = 
{
 17, 18, 24, 47, 99, 99, 99, 99,
  18, 21, 26, 66, 99, 99, 99, 99,
  24, 26, 56, 99, 99, 99, 99, 99,
  47, 66, 99 ,99, 99, 99, 99, 99,
  99, 99, 99, 99, 99, 99, 99, 99,
  99, 99, 99, 99, 99, 99, 99, 99,
  99, 99, 99, 99, 99, 99, 99, 99,
  99, 99, 99, 99, 99, 99, 99, 99
};

//正向 8x8 Z变换表
const static BYTE FZBT[64] =
{
 0, 1, 5, 6, 14,15,27,28,
  2, 4, 7, 13,16,26,29,42,
  3, 8, 12,17,25,30,41,43,
  9, 11,18,24,31,40,44,53,
  10,19,23,32,39,45,52,54,
  20,22,33,38,46,51,55,60,
  21,34,37,47,50,56,59,61,
  35,36,48,49,57,58,62,63 
};

//色彩空间系数常量,依次是411,111,211采样的系数,211采样的2种方式的系数相同
static const FLOAT COLORSPACECOEF[4][3] = {{1,0.25,0.25},{1,1,1},{1,0.5,0.5},{1,0.5,0.5}};
//MCU中各型号分量出现的比率
static const BYTE MCUIndex[4][3] = {{4,1,1},{1,1,1},{2,1,1},{2,1,1}};

// 标准Huffman表 (cf. JPEG standard section K.3) 
static BYTE STD_DC_Y_NRCODES[17]={0,0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0};
static BYTE STD_DC_Y_VALUES[12]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

static BYTE STD_DC_UV_NRCODES[17]={0,0,3,1,1,1,1,1,1,1,1,1,0,0,0,0,0};
static BYTE STD_DC_UV_VALUES[12]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

static BYTE STD_AC_Y_NRCODES[17]={0,0,2,1,3,3,2,4,3,5,5,4,4,0,0,1,0X7D };
static BYTE STD_AC_Y_VALUES[162]= {
 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
  0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
  0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
  0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
  0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
  0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
  0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
  0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
  0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
  0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
  0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
  0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
  0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
  0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
  0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
  0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
  0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
  0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
  0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
  0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
  0xf9, 0xfa };

 static BYTE STD_AC_UV_NRCODES[17]={0,0,2,1,2,4,4,3,4,7,5,4,4,0,1,2,0X77};
 static BYTE STD_AC_UV_VALUES[162]={
  0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
   0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
   0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
   0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
   0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
   0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
   0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
   0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
   0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
   0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
   0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
   0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
   0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
   0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
   0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
   0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
   0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
   0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
   0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
   0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
   0xf9, 0xfa };  


//Jpegformat.h

//文件开始,开始标记为0xFFD8
const static WORD SOITAG = 0xD8FF;

//文件结束,结束标记为0xFFD9
const static WORD EOITAG = 0xD9FF;

//JFIF APP0段结构
#pragma pack(push,1)
typedef struct tagJPEGAPP0
{
 WORD segmentTag;  //APP0段标记，必须为FFE0
 WORD length;    //段长度，一般为16，如果没有缩略图
 CHAR id[5];     //文件标记 "JFIF" + "/0"
 WORD ver;      //文件版本，一般为0101或0102
 BYTE densityUnit; //密度单位，0=无单位 1=点数/英寸 2=点数/厘米
 WORD densityX;   //X轴方向密度,通常写1
 WORD densityY;   //Y轴方向密度,通常写1
 BYTE thp;     //缩略图水平像素数,写0
 BYTE tvp;     //缩略图垂直像素数,写0
}JPEGAPP0;// = {0xE0FF,16,'J','F','I','F',0,0x0101,0,1,1,0,0};
#pragma pack(pop)

//JFIF APPN段结构
#pragma pack(push,1)
typedef struct tagJPEGAPPN
{
 WORD segmentTag;  //APPn段标记，从FFE0 - FFEF n=0-F
 WORD length;    //段长度   
}JPEGAPPN;
#pragma pack(pop)  

//JFIF DQT段结构(8 bits 量化表)
#pragma pack(push,1)
typedef struct tagJPEGDQT_8BITS
{
 WORD segmentTag;  //DQT段标记，必须为0xFFDB
 WORD length;    //段长度,这里是0x4300
 BYTE tableInfo;  //量化表信息
 BYTE table[64];  //量化表(8 bits)
}JPEGDQT_8BITS;
#pragma pack(pop)

//JFIF DQT段结构(8 bits 量化表)
#pragma pack(push,1)
typedef struct tagJPEGDQT_16BITS
{
 WORD segmentTag;  //DQT段标记，必须为0xFFDB
 WORD length;    //段长度，这里是0x8300
 BYTE tableInfo;  //量化表信息
 WORD table[64];   //量化表(16 bits)
}JPEGDQT_16BITS;
#pragma pack(pop)

//JFIF SOF0段结构(真彩)，其余还有SOF1-SOFF
#pragma pack(push,1)
typedef struct tagJPEGSOF0_24BITS
{
 WORD segmentTag;  //SOF段标记，必须为0xFFC0
 WORD length;    //段长度，真彩图为17，灰度图为11
 BYTE precision;  //精度，每个信号分量所用的位数，基本系统为0x08
 WORD height;    //图像高度
 WORD width;     //图像宽度
 BYTE sigNum;   //信号数量，真彩JPEG应该为3，灰度为1
 BYTE YID;     //信号编号，亮度Y
 BYTE HVY;     //采样方式，0-3位是垂直采样，4-7位是水平采样
 BYTE QTY;     //对应量化表号
 BYTE UID;     //信号编号，色差U
 BYTE HVU;     //采样方式，0-3位是垂直采样，4-7位是水平采样
 BYTE QTU;     //对应量化表号
 BYTE VID;     //信号编号，色差V
 BYTE HVV;     //采样方式，0-3位是垂直采样，4-7位是水平采样
 BYTE QTV;     //对应量化表号
}JPEGSOF0_24BITS;// = {0xC0FF,0x0011,8,0,0,3,1,0x11,0,2,0x11,1,3,0x11,1};
#pragma pack(pop)

//JFIF SOF0段结构(灰度)，其余还有SOF1-SOFF
#pragma pack(push,1)
typedef struct tagJPEGSOF0_8BITS
{
 WORD segmentTag;  //SOF段标记，必须为0xFFC0
 WORD length;    //段长度，真彩图为17，灰度图为11
 BYTE precision;  //精度，每个信号分量所用的位数，基本系统为0x08
 WORD height;    //图像高度
 WORD width;     //图像宽度
 BYTE sigNum;   //信号数量，真彩JPEG应该为3，灰度为1
 BYTE YID;     //信号编号，亮度Y
 BYTE HVY;     //采样方式，0-3位是垂直采样，4-7位是水平采样
 BYTE QTY;     //对应量化表号 
}JPEGSOF0_8BITS;// = {0xC0FF,0x000B,8,0,0,1,1,0x11,0};
#pragma pack(pop)

//JFIF DHT段结构
#pragma pack(push,1)
typedef struct tagJPEGDHT
{
 WORD segmentTag;  //DHT段标记，必须为0xFFC4
 WORD length;    //段长度
 BYTE tableInfo;  //表信息，基本系统中 bit0-3 为Huffman表的数量，bit4 为0指DC的Huffman表 为1指AC的Huffman表，bit5-7保留，必须为0
 BYTE huffCode[16];//1-16位的Huffman码字的数量，分别存放在数组[1-16]中
 //BYTE* huffVal;  //依次存放各码字对应的值
}JPEGDHT;
#pragma pack(pop)

// JFIF SOS段结构（真彩）
#pragma pack(push,1)
typedef struct tagJPEGSOS_24BITS
{
 WORD segmentTag;  //SOS段标记，必须为0xFFDA
 WORD length;    //段长度，这里是12
 BYTE sigNum;   //信号分量数，真彩图为0x03,灰度图为0x01
 BYTE YID;     //亮度Y信号ID,这里是1
 BYTE HTY;     //Huffman表号，bit0-3为DC信号的表，bit4-7为AC信号的表
 BYTE UID;     //亮度Y信号ID,这里是2
 BYTE HTU;
 BYTE VID;     //亮度Y信号ID,这里是3
 BYTE HTV;
 BYTE Ss;     //基本系统中为0
 BYTE Se;     //基本系统中为63
 BYTE Bf;     //基本系统中为0
}JPEGSOS_24BITS;// = {0xDAFF,0x000C,3,1,0,2,0x11,3,0x11,0,0x3F,0};
#pragma pack(pop)

// JFIF SOS段结构（灰度）
#pragma pack(push,1)
typedef struct tagJPEGSOS_8BITS
{
 WORD segmentTag;  //SOS段标记，必须为0xFFDA
 WORD length;    //段长度，这里是8
 BYTE sigNum;   //信号分量数，真彩图为0x03,灰度图为0x01
 BYTE YID;     //亮度Y信号ID,这里是1
 BYTE HTY;     //Huffman表号，bit0-3为DC信号的表，bit4-7为AC信号的表  
 BYTE Ss;     //基本系统中为0
 BYTE Se;     //基本系统中为63
 BYTE Bf;     //基本系统中为0
}JPEGSOS_8BITS;// = {0xDAFF,0x0008,1,1,0,0,0x3F,0};
#pragma pack(pop) 

// JFIF COM段结构
#pragma pack(push,1)
typedef struct tagJPEGCOM
{
 WORD segmentTag;  //COM段标记，必须为0xFFFE
 WORD length;    //注释长度
}JPEGCOM;
#pragma pack(pop) 


///Main.cpp

#include <iostream>
#include "jenc.h"

using namespace std;

int main(int argc, char* argv[])
{
 if (argc <= 1)
 {
  cout << "please input bmp filename." << endl;
  return 0;
 }

 string fileName = string(argv[1]);
 string outFile = fileName.substr(0,fileName.find_last_of('.'));
 outFile = outFile + ".jpg";

 JEnc enc;
 enc.Invoke(fileName, outFile,100);
 cout << outFile << endl;
 getchar();
 return 0;
}
 