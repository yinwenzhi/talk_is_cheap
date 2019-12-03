
// //串口相关的头文件  
// #include<stdio.h>      /*标准输入输出定义*/  
// #include<stdlib.h>     /*标准函数库定义*/  
// #include<unistd.h>     /*Unix 标准函数定义*/  
// #include<sys/types.h>   
// #include<sys/stat.h>     
// #include<fcntl.h>      /*文件控制定义*/  
// #include<termios.h>    /*PPSIX 终端控制定义*/  
// #include<errno.h>      /*错误号定义*/  
// #include<string.h>  

// # include "serials_linux.h"
   
// struct termio
// {   unsigned short  c_iflag;    /* 输入模式标志 */    
//     unsigned short  c_oflag;        /* 输出模式标志 */    
//     unsigned short  c_cflag;        /* 控制模式标志*/ 
//     unsigned short  c_lflag;        /* local mode flags */  
//     unsigned char  c_line;          /* line discipline */   
//     unsigned char  c_cc[NCC];    /* control characters */
// };

// // 构造函数，需要传入串口号。其他参数都有默然值。如果需要更改的话，可以通过Setxx()函数来设置相应的参数；
// CSerial::CSerial()
// {
//     // m_pnReusecount = NULL;
//     // m_hCom = NULL;
//     // m_hEventRecv = NULL;
//     // m_hEventSend = NULL;
//     // m_strCom = _T("");
//     // m_dwBaudRate = 9600;
//     // m_byteSize = 8;
//     // m_byteCheck = NOPARITY;
//     // m_byteStop = ONESTOPBIT;
//     // m_bSync = TRUE;
//     // m_bIsFirst = TRUE;
//     // //缓冲区变量初始化
//     // m_dwInQueue = 1024;
//     // m_dwOutQueue = 1024;
//     // //超时变量初始化
//     // COMMTIMEOUTS timeout = {MAXDWORD, 0, 0, 50, 1000};
//     // m_Timeouts = timeout;
// }

// CSerial::OpenSerial()
// {
//     int fd;
//     /*以读写方式打开串口*/
//     fd = open( "/dev/ttyS0", O_RDWR);
//     if (-1 == fd){ 
//     /* 不能打开串口一*/ 
//     perror(" 提示错误！");
// }

// CSerial::SetSerial()
// {
//     /**
//     *@brief  设置串口通信速率
//     *@param  fd     类型 int  打开串口的文件句柄
//     *@param  speed  类型 int  串口速度
//     *@return  void
//     */
//     int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
//             B38400, B19200, B9600, B4800, B2400, B1200, B300, };
//     int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300, 38400,  
//             19200,  9600, 4800, 2400, 1200,  300, };
//     void set_speed(int fd, int speed){
//         int   i; 
//         int   status; 
//         struct termios   Opt;
//         tcgetattr(fd, &Opt); 
//         for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) { 
//             if  (speed == name_arr[i]) {     
//             tcflush(fd, TCIOFLUSH);     
//             cfsetispeed(&Opt, speed_arr[i]);  
//             cfsetospeed(&Opt, speed_arr[i]);   
//             status = tcsetattr(fd1, TCSANOW, &Opt);  
//             if  (status != 0) {        
//                 perror("tcsetattr fd1");  
//                 return;     
//             }
//             tcflush(fd,TCIOFLUSH);   
//             }  
//         }
//     }
// }
