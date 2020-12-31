C语言 HTTP 下载文件 2012-05-05 03:09:10

       C语言 HTTP协议下载文件，实现断点续传，socket通讯，目前只支持ip和port方式连接，有兴趣的读者可完善域名方式。
      代码分为 http.c： 实现http协议下载文件 ，socket.c： 封装linux socket函数，移植时只需修改socket.c中的函数即可。
     希望对大家有帮助，本人亲测可用！
http.c
//http.c
//作者：王振
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "socket.h"
#include "http.h"


#define MAX_RECV_SIZE    1440//硬件单包最大的接收字节数
char g_host[URL_LEN];
char g_ip[URL_LEN+1];//ip/域名
char g_port[5+1];

char g_buf_send[4*1024];//发送数据暂存区
char g_buf_recv[10*1024];//接收数据暂存区

BreakPoint_ST g_break_point;

/*
功能:判断断点有效性,现在校验url是否一致
参数:
返回:
>0---------有效,已下载文件大小
-1----------无效
*/
int Get_Breakpoint_Available(BreakPoint_ST *breakpoint,char *url,char *file_crc)
{
    
    //判断断点是否有效,后续加入文件校验码
    if((memcmp(breakpoint->url,url,strlen(url))== 0)&&(breakpoint->recv_size== MAX_RECV_SIZE))
        return breakpoint->download_size;
    else
    {
        return -1;
    }
    
}


/*
功能:判断要下载文件是否存在断点
参数:
filename---要下载的文件名
file_crc----服务器返回下载文件的校验码
返回:
0---------无断点
>0--------有断点,已下载文件大小
*/
int Get_Breakpoint(char *url,char *filename,char *file_crc)
{
    char filename_bp[64];
    int fd = -1;
    int ret;
    BreakPoint_ST break_point;
    
    //断点文件名 filename+bp
    sprintf(filename_bp,"%s.bp",filename);

    //检测是否存在filename断点文件
    fd = open(filename_bp,O_RDONLY,S_IRUSR|S_IWUSR);
    if(fd == -1)
    {    
        #ifdef DEBUG_HTTP
        printf("no exsit %s\n",filename_bp);
        #endif
        return 0;
    }

    //存在断点
    ret = read(fd,&break_point,sizeof(break_point));
    if(ret != sizeof(break_point))
    {
        perror("ERR:Get_Breakpoint read");
        exit(-1);
    }

    close(fd);

    //判断断点是否有效
    ret = Get_Breakpoint_Available(&break_point,url,file_crc);
    if(ret > 0)
        return ret;
    else
    {
        
        printf("%s not available\n",filename_bp);
        remove(filename);
        remove(filename_bp);
        return 0;
        
    }
}

/*
功能:保存断点信息,文件名filename.bp
参数:
filename---要下载的文件名
file_crc----服务器返回下载文件的校验码
返回:
0---------成功
>0--------有断点,已下载文件大小
*/
int Save_Breakpoint(char *url,char *filename,int download_size,char *file_crc)
{
    int fd;
    BreakPoint_ST breakpoint;
    char filename_bp[128];//断点信息文件名，包含路径

    sprintf(filename_bp,"%s.bp",filename);
    /* 创建目的文件 */
    if((fd=open(filename_bp,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))==-1)
    {
        fprintf(stderr,"Open %s Error：%s\n",filename_bp,strerror(errno));
        exit(1);
    }
    memset(&breakpoint,0x0,sizeof(breakpoint));
    strcpy(breakpoint.url,url);
    //strcpy(breakpoint.crc,file_crc);
    strcpy(breakpoint.filename,filename);
    breakpoint.download_size = download_size;
    breakpoint.recv_size= MAX_RECV_SIZE;
    
    //xu tioa zheng wei fen ci xie ru
    if(write(fd,&breakpoint,sizeof(breakpoint)) != sizeof(breakpoint))
    {
        perror("ERR:Save_Breakpoint");
        exit(1);
    }

    close(fd);

    return 0;



}

/*
功能:保存文件,追加写
参数:
返回:
0---------成功
*/

int Save_File(char *filebuf,int filelength,char *filename)
{
    int fd;
    /* 创建目的文件追加写 */
    if((fd=open(filename,O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR))==-1)
    {
        fprintf(stderr,"Open %s Error：%s\n",filename,strerror(errno));
        exit(1);
    }
    //xu tioa zheng wei fen ci xie ru
    if(write(fd,filebuf,filelength) != filelength)
    {
        perror("ERR:Save_File");
        exit(1);
    }

    close(fd);

    return 0;


}

 
int HTTP_GetResponseCode(void)
{
 
 
}

 /*
功能:读取http返回的协议实体主体长度
参数:
revbuf--------接收到的返回值
返回值:
>=0---------内容(实体主体)的长度
-1-----------数据返回错误
*/
int HTTP_GetRecvLength(char *revbuf)
{
    char *p1 = NULL;
    int HTTP_Body = 0;//内容体长度
    int HTTP_Head = 0;//HTTP 协议头长度


    HTTP_Body = HTTP_GetContentLength(revbuf);
    if(HTTP_Body == -1)
        return -1;

    p1=strstr(revbuf,"\r\n\r\n");
    if(p1==NULL)
        return -1;
    else
    {
        HTTP_Head = p1- revbuf +4;// 4是\r\n\r\n的长度
        return HTTP_Body+HTTP_Head;
    }


}


/*
功能:读取http返回的Content-Length长度
参数:
revbuf--------接收到的数据
返回值:
>=0---------Content-Length长度
-1-----------数据返回错误
*/
int HTTP_GetContentLength(char *revbuf)
{
    char *p1 = NULL, *p2 = NULL;
    int HTTP_Body = 0;//内容体长度

    p1 = strstr(revbuf,"Content-Length");
    if(p1 == NULL)
        return -1;
    else
    {
        p2 = p1+strlen("Content-Length")+ 2;
        HTTP_Body = atoi(p2);
        return HTTP_Body;
    }

}

 /*
 功能:
 参数:
 sockfd--------接收到的返回值
 返回值:
 >0---------接收到长度
 -1----------失败
 =0---------服务端断开连接
 注:内部接收缓冲10k
 */

int HTTP_Recv(int sockfd,char *buf_recv)
{
    int ret;
    int recvlen=0;
    int downloadlen = 0;
    //int contentlen=0;
    char buf_recv_tmp[10*1024+1];
    
    memset(buf_recv_tmp,0x0,sizeof(buf_recv_tmp));
    while(1)
    {
        ret = Recv(sockfd,buf_recv_tmp+recvlen,sizeof(buf_recv_tmp)-1,0);

        if(ret <= 0)//下载失败
        {
            perror("ERR:recv fail");
            return ret;
        }
    
    
        if(recvlen == 0)
        {
            #ifdef DEBUG_HTTP_RECV
            printf("recv len = %d\n", ret);
             printf("recv = %s\n", buf_recv_tmp);
            #endif
            //获取需要下载长度;
            downloadlen = HTTP_GetRecvLength(buf_recv_tmp);


            #ifdef DEBUG_HTTP_RECV
            printf("downloadlen = %d\n",downloadlen);
            #endif
        }

        recvlen += ret;
        #ifdef DEBUG_HTTP_RECV
        printf("total recvlen = %d\n",recvlen);
        #endif

        if(downloadlen == recvlen)//下载完成
            break;


    }
    memcpy(buf_recv,buf_recv_tmp,downloadlen);
    return recvlen;

}

/*
功能:获取下载url中的文件名,最后一个/后的字符
参数:
返回值:
0-----------成功
-1----------失败
注:内部接收缓冲10k
*/

int HTTP_GetFileName(char *url,char *filename)
{
    //提取url中最后一个/后的内容
    int len;
    int i;

    len = strlen(url);
    for(i=len-1;i>0;i--)
    {
        if(url[i] == '/')
            break;
    }
    if(i == 0)//下载地址错误
    {
        printf("url not contain '/'\n");
        return -1;
    }
    else
    {
    
        strcpy(filename,url+i+1);
        #ifdef DEBUG_HTTP
        printf("filename=%s\n",filename);
        #endif
        return 0;
    }
}

/*
功能:获取下载url中的路径,第一个/后的字符
参数:
返回值:
0-----------成功
-1----------失败
注:url ex "http://host:port/path"
*/
int HTTP_GetPath(char *url,char *path)
{
    char *p;

    p = strstr(url,"http://");
    if(p == NULL)
    {
        p = strchr(url,'/');
        if(p == NULL)
            return -1;
        else
        {
            strcpy(path,p);
            return 0;
        }
    }
    else
    {
        p = strchr(url+strlen("http://"),'/');
        if(p == NULL)
            return -1;
        else
        {
            strcpy(path,p);
            return 0;
        }
    }

}
/*
功能:获取下载url中的ip和port,ip支持域名,端口默认为80
参数:
返回值:
1-----------域名式
2-----------ip port式
-1----------失败
注:url ex "http://host:port/path"
*/

int HTTP_Get_IP_PORT(char *url,char *ip,char *port)
{
    char *p = NULL;
    int offset = 0;
    char DOMAIN_NAME[128];

    p = strstr(url,"http://");
    if(p == NULL)
    {
        offset = 0;
    }
    else
    {
        offset = strlen("http://");
    }

    p = strchr(url+offset,'/');
    if(p == NULL)
    {
        printf("url:%s format error\n",url);
        return -1;
        
    }
    else
    {

        memset(DOMAIN_NAME,0x0,sizeof(DOMAIN_NAME));
        memcpy(DOMAIN_NAME,url+offset,(p-url-offset));
        p = strchr(DOMAIN_NAME,':');
        if(p == NULL)
        {
            strcpy(ip,DOMAIN_NAME);
            strcpy(port,"80");
            //printf("ip %p,port %p\n",ip,port);
            
            #ifdef DEBUG_HTTP
            printf("ip=%s,port=%s\n",ip,port);//debug info
            #endif
            return 1;

        }
        else
        {    
            *p = '\0';

            strcpy(ip,DOMAIN_NAME);
            strcpy(port,p+1);
            
            #ifdef DEBUG_HTTP
            printf("ip=%s,port=%s\n",ip,port);//debug info
            #endif
            return 2;

        }


        return 0;
    }
    
}
void Package_Url_Get_File(char *path, char *range)
{
    char buf[64];
    memset(g_buf_send,0x0,sizeof(g_buf_send));        
    sprintf(g_buf_send, "GET %s",path);

    
    //HTTP/1.1\r\n 前面需要一个空格
    strcat(g_buf_send," HTTP/1.1\r\n");
    strcat(g_buf_send, "Host: ");
    strcat(g_buf_send, g_host);
    //strcat(g_buf_send, ":");
    //strcat(g_buf_send, PORT);
    
    sprintf(buf, "\r\nRange: bytes=%s",range);
    strcat(g_buf_send,buf);
    strcat(g_buf_send, "\r\nKeep-Alive: 200");
    strcat(g_buf_send,"\r\nConnection: Keep-Alive\r\n\r\n");
    

}

int Package_Url_Get_FileSize(char *url)
{
    
    memset(g_buf_send,0x0,sizeof(g_buf_send));        
    sprintf(g_buf_send, "HEAD %s",url);

        //HTTP/1.1\r\n 前面需要一个空格
    strcat(g_buf_send," HTTP/1.1\r\n");
    strcat(g_buf_send, "Host: ");
    strcat(g_buf_send, g_host);
    //strcat(g_buf_send, ":");
    //strcat(g_buf_send, PORT);
    strcat(g_buf_send,"\r\nConnection: Keep-Alive\r\n\r\n");

    return 0;
}


int HTTP_GetFileSize(int sockfd,char *path)
{
    int ret = -1;
    char buf_recv_tmp[10*1024+1];

    Package_Url_Get_FileSize(path);
#ifdef DEBUG_HTTP
    printf("send = %s \n",g_buf_send);
#endif

    Send(sockfd, g_buf_send, strlen(g_buf_send), 0);

    memset(buf_recv_tmp,0x0,sizeof(buf_recv_tmp));                                                
    ret = Recv(sockfd,buf_recv_tmp,sizeof(buf_recv_tmp)-1,0);
#ifdef DEBUG_HTTP
    printf("recv len = %d\n", ret);
    printf("recv = %s\n", buf_recv_tmp);
#endif
    if(ret <= 0)
    {
        perror("ERR:recv fail GetFileSize()");
        return -1;

    }
    ret = HTTP_GetContentLength(buf_recv_tmp);
    if(ret <= 0)
        return -1;
    else
        return ret;


}




/*
功能:分段下载文件
参数:
返回值:
>0----------已下载文件大小(不包含上次下载)
-1----------失败
*/
int HTTP_GetFile(int sockfd,char *path,int filelength,int download_size,char *filebuf)
{
    int count;
    char range[32];
    int i;
    int j = 0;//成功下载次数
    int ret = -1;
    char *p = NULL;
    int download_index;//下载开始索引

    count = (filelength%MAX_RECV_SIZE)?(filelength/MAX_RECV_SIZE +1):(filelength/MAX_RECV_SIZE);

    download_index = download_size/MAX_RECV_SIZE;

    for(i=download_index;i<count;i++)
    {
        //if(i == 20)//测试断点
            //break;


        if((i == (count-1))&&(filelength%MAX_RECV_SIZE))
            sprintf(range,"%d-%d",i*MAX_RECV_SIZE,filelength-1);
        else
            sprintf(range,"%d-%d",i*MAX_RECV_SIZE,(i+1)*MAX_RECV_SIZE-1);


        Package_Url_Get_File(path,range);
        #ifdef DEBUG_HTTP
         printf("send = %s \n",g_buf_send);
        #endif
         Send(sockfd, g_buf_send, strlen(g_buf_send), 0);

        /*需改为提取http 返回协议头和协议体总长,然后定长接收*/
        memset(g_buf_recv,0x0,sizeof(g_buf_recv));                                             
        ret = HTTP_Recv(sockfd,g_buf_recv);
        if(ret < 0)
            break;
        if(ret == 0 )//服务端断开连接
        {
            sockfd = Socket_Connect(g_ip,g_port);
             i--;
            continue;
        }
        /*提取协议体数据,保存在filebuf中*/
        p = strstr(g_buf_recv,"\r\n\r\n");
        if(p == NULL)//jia ru duan dian baocun
        {
            printf("ERR:g_buf_recv not contain end flag\n");
            break;
        }
         else
         {
             memcpy(filebuf+j*MAX_RECV_SIZE,p+4,MAX_RECV_SIZE);
             j++;

         }
    }
    if(i == count)
        return (filelength-download_size);
    else
        return (i*MAX_RECV_SIZE-download_size);
}

/*
功能:HTTP下载文件
参数:
返回值:
0----------下载完成
-1---------失败
-2---------部分下载完成
注:保存文件到bin所在目录
*/
int HTTP_DownloadFile(char *url,char *save_path)
{
    int ret;
    int sockfd;
    int filesize;
    int download_size;
    char filename[FILENAME_LEN+1];
    char filename_bp[FILENAME_LEN+3+1];
    char *filebuf;
    char save_file_path[FILENAME_LEN+1];//保存下载文件的路径+文件名

    char path[PATH_LEN+1];//url中的path

    //提取ip和port或url(url 暂不实现,需要gethostbyname linux)
    ret = HTTP_Get_IP_PORT(url,g_ip,g_port);
    if(ret == -1)
        return -1;
    else
    {
        sprintf(g_host,"%s:%s",g_ip,g_port);
    }
    //提取下载文件名
    ret = HTTP_GetFileName(url,filename);
    if(ret == -1)
        return -1;

    ret = HTTP_GetPath(url,path);
    if(ret == -1)
        return -1;
    //sleep(3);//debug info
    //建立连接
    sockfd = Socket_Connect(g_ip,g_port);

    //获取下载文件总大小
    filesize = HTTP_GetFileSize(sockfd,path);
    if(filesize == -1)
        return -1;
    //#ifdef DEBUG_HTTP
    printf("http need download size %d\n",filesize);
    //#endif
    //malloc分配存储文件空间
    filebuf = (char *)malloc(filesize);
    if(filebuf == NULL)
    {
        perror("malloc filebuf fail");
        return -1;
    }
    else
        memset(filebuf,0x0,filesize);

    download_size = Get_Breakpoint(url,filename,NULL);
    #ifdef DEBUG_HTTP
    printf("breakpoint download_size=%d\n",download_size);//debug info
    sleep(3);//debug info
    #endif
    //分段下载文件
    ret = HTTP_GetFile(sockfd,path,filesize,download_size,filebuf);
    Close(sockfd);
    if(ret < 0)
    {
        free(filebuf);
        return -1;
    }
    else
    {

        sprintf(save_file_path,"%s%s",save_path,filename);
        
        #ifdef DEBUG_HTTP
        printf("save_path=%s\n",save_path);
        printf("filename=%s\n",filename);
        printf("save_file_path=%s\n",save_file_path);
        printf("download_size = %d\n",ret);
        #endif
        Save_File(filebuf,ret,save_file_path);
        free(filebuf);
        if((ret+download_size) == filesize)//全部下载完成
        {
            sprintf(filename_bp,"%s.bp",filename);
            remove(filename_bp);
            
     printf("download success\n");
            return 0;
        }
        else//部分下载完成
        {
            printf("part download success\n");
            //保存断点信息
            Save_Breakpoint(url,save_file_path,ret+download_size,NULL);
            return -2;
        }
    }

}
socket.c 
//socket.c
//作者：王振

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include "socket.h"

int Connect(int fd, struct sockaddr *addr, socklen_t len)
{
    int result;
    if ((result = connect(fd, addr, len)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Socket_Connect(char *ip,char *port)
{
    struct sockaddr_in addr;

    int sockfd;
    int len;

    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);//127.0.0.1为本机ip
    addr.sin_port = htons(atoi(port));
    len = sizeof(addr);
        
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    Connect(sockfd, (struct sockaddr*)&addr, len);
    return sockfd;

}


/*
功能:向socketfd发送数据,内部实现了循环发送len长度
参数:
sockfd 是代表你与远程程序连接的套接字描述符。
msg 是一个指针，指向你想发送的信息的地址。
len 是你想发送信息的长度。
flags 发送标记。一般都设为0
返回:
0-------- 成功
退出---失败
修改:
备注:
王振
*/
int Send(int sockfd, char *sendbuf, int len, int flags)
{
    int sendlen = 0;
    int ret = -1;

    while(sendlen < len)
    {
        ret = send(sockfd, sendbuf+sendlen, len-sendlen, flags);
        if(-1 == ret)
        {
            perror("send");
            exit(EXIT_FAILURE);
        }
        else
            sendlen += ret;

    }

    return 0;

}

int Close(int sockfd)
{
    return close(sockfd);
    

}
int Recv(int sockfd, char *recvbuf, int len, int flags)
{
    int recv_len;

    if ((recv_len = recv(sockfd, recvbuf, len, flags)) < 0)
    {
        perror("recv error");
        exit(EXIT_FAILURE);
    }

    return recv_len;
}