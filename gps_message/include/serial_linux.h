//串口相关的头文件  
#include<stdio.h>      /*标准输入输出定义*/  
#include<stdlib.h>     /*标准函数库定义*/  
#include<unistd.h>     /*Unix 标准函数定义*/  
#include<sys/types.h>   
#include<sys/stat.h>     
#include<fcntl.h>      /*文件控制定义*/  
#include<termios.h>    /*PPSIX 终端控制定义*/  
#include<errno.h>      /*错误号定义*/  
#include<string.h>  

   
//宏定义  
#define FALSE  -1  
#define TRUE   0  


class SerialLinux
{
    public:
        SerialLinux();
        SerialLinux(
            int fd ,
            const char* port = "/dev/ttyS0",
            unsigned long dwBaudRate = 9600
            // String strCom,
            // BYTE byteSize = 8,
            // BYTE byteCheck = NOPARITY,
            // BYTE byteStop = ONESTOPBIT,
            // BOOL bSync = FALSE
            );
        ~SerialLinux();
        inline SerialLinux(const SerialLinux &com)
        {
            
        }
        int Serial_Open(int fd,char* port);
        void Serial_Close(int fd);
        bool Serial_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);
        int Serial_Init(int fd, int speed,int flow_ctrl,int databits,int stopbits,int parity);  
        int Serial_Recv(int fd, char *rcv_buf,int data_len);
        int Serial_Send(int fd, char *send_buf,int data_len);

    private:

    public:
  
};