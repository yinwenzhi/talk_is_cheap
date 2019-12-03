#include <stdio.h>
#include "include/serial_linux.h"
#include "include/gps_message.h"


int main(int argc, char **argv)  
{  
    int fd;                            //文件描述符  
    int err;                           //返回调用函数的状态  
    int len;                          
    int i;  
    char rcv_buf[128];         
    char send_buf[20]="tiger john";
    //设置日志
    
    SerialLinux SL;
    if(argc != 3)  
    {  
        printf("Usage: %s /dev/ttySn 0(send data)/1 (receive data) \n",argv[0]);  
        return FALSE;  
    }  
    fd = SL.Serial_Open(fd,argv[1]); //打开串口，返回文件描述符  
    do
    {  
        err = SL.Serial_Init(fd,19200,0,8,1,'N');  
        printf("Set Port Exactly!\n");  
    }while(FALSE == err || FALSE == fd);  
     
    if(0 == strcmp(argv[2],"0"))  // strcmp 比较两个字符串 相等返回0 
    {  
        for(i = 0;i < 10;i++)  
        {  
             len = SL.Serial_Send(fd,send_buf,10);  
            if(len > 0)  
                printf(" %d time send %d data successful\n",i,len); 
                

            else  
                printf("send data failed!\n");  
                            
            sleep(2);  
        }  
        SL.Serial_Close(fd);               
    }  
    else  
    {                                        
        while (1) //循环读取数据  
        {    
            len = SL.Serial_Recv(fd, rcv_buf,99);  
              if(len > 0)  
            {  
                rcv_buf[len] = '\0';  
                printf("receive data is %s\n",rcv_buf);  
                printf("len = %d\n",len); 
                GpsMessage GM;
                gps_info gps_st;
                memset(&gps_st, 0, sizeof(gps_st));
                GM.gprmc_analysis(&gps_st, rcv_buf);
                GM.gpgga_analysis(&gps_st, rcv_buf);
                // GM.echo();

                //日志
                // int main()
                // {
                Log mainLog;
                string a = "log";
                mainLog.CommonLogInit(a);
            
                mainLog << mainLog.GetTimeStr() << "这里是需要自己输入的信息" << endl;
                printf("writ log");
                // }
            }  
            else  
            {  
                printf("cannot receive data\n");  
            }  
            sleep(2);  
        }              
        SL.Serial_Close(fd);   
    }  
}  


  