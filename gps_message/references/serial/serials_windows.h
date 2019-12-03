//CSerial类头文件
//https://www.cnblogs.com/konglongdanfo/p/9135253.html  
#pragma once

class CSerial
{
public:
    CSerial();
    CSerial(
        CString strCom,
        DWORD dwBaudRate = 9600,
        BYTE byteSize = 8,
        BYTE byteCheck = NOPARITY,
        BYTE byteStop = ONESTOPBIT,
        BOOL bSync = FALSE);
    ~CSerial();
    inline CSerial(const CSerial &com)
    {
        m_hCom = com.m_hCom;
        m_hEventSend = com.m_hEventSend;
        m_hEventRecv = com.m_hEventRecv;
        m_bSync = com.m_bSync;
        m_bIsFirst = com.m_bIsFirst;
        m_strCom = com.m_strCom;
        m_dwBaudRate = com.m_dwBaudRate;
        m_byteSize = com.m_byteSize;
        m_byteCheck = com.m_byteCheck;
        m_byteStop = com.m_byteStop;
        m_dwInQueue = com.m_dwInQueue;
        m_dwOutQueue = com.m_dwOutQueue;
        m_Timeouts = com.m_Timeouts;
        m_nInitResult = com.m_nInitResult;
        m_pnReusecount = com.m_pnReusecount;
        if ( m_pnReusecount )
        {
            (* m_pnReusecount)++;
        }
    }
    inline CSerial & operator = (const CSerial &com)
    {
        m_hCom = com.m_hCom;
        m_hEventSend = com.m_hEventSend;
        m_hEventRecv = com.m_hEventRecv;
        m_bSync = com.m_bSync;
        m_bIsFirst = com.m_bIsFirst;
        m_strCom = com.m_strCom;
        m_dwBaudRate = com.m_dwBaudRate;
        m_byteSize = com.m_byteSize;
        m_byteCheck = com.m_byteCheck;
        m_byteStop = com.m_byteStop;
        m_dwInQueue = com.m_dwInQueue;
        m_dwOutQueue = com.m_dwOutQueue;
        m_Timeouts = com.m_Timeouts;
        m_nInitResult = com.m_nInitResult;
        m_pnReusecount = com.m_pnReusecount;
        if ( m_pnReusecount )
        {
            (* m_pnReusecount)++;
        }
        return * this;
    }
private:
    int *m_pnReusecount;
    BOOL m_bIsFirst;         //是否是第一次成功打开串口
    HANDLE m_hCom;           //串口句柄
    HANDLE m_hEventSend;     //发送数据事件
    HANDLE m_hEventRecv;     //接收数据事件

    BOOL m_bSync;            //同步传输还是异步传输,TRUE则为同步，FALSE为异步,默认为异步

    CString m_strCom;        //串口端口
    DWORD m_dwBaudRate;      //波特率
    BYTE m_byteSize;         //数据位
    BYTE m_byteCheck;        //校验方式
    BYTE m_byteStop;         //停止位

    DWORD m_dwInQueue;       //串口输入缓冲区     
    DWORD m_dwOutQueue;     //串口输出缓冲区
    //超时相关变量
    COMMTIMEOUTS m_Timeouts;

    int m_nInitResult;
public:
    DWORD WriteData(unsigned char *pBuffer, DWORD dwLength, DWORD dwTimeout = 1000);  //dwTimeout为占位符，暂时未用，返回，MAXDWORD表示写入错误
    DWORD ReadData(unsigned char *pBuffer, DWORD dwLength, DWORD dwTimeout = 1000);   //dwTimeout为占位符，暂时未用，返回，MAXDWORD表示读取错误
    void CloseCom();
    int InitCom();//返回1，表示没有错误，返回其他表示错误
    void ClearError();
    void Purge(DWORD dwFlags);

    int SetComString(CString strCom);
    int SetBaudRate(DWORD dwBaudRate);
    int SetByteSize(BYTE byteSize);
    int SetCheck(BYTE byteCheck);
    int SetStopBit(BYTE byteStopBit);
    int SetSync(BOOL bSync);
    int SetInQue(DWORD dwInQue);
    int SetOutQue(DWORD dwOutQue);
    int SetTimeouts(COMMTIMEOUTS timeouts);


    CString GetComString();
    DWORD GetBaudRate();
    BYTE GetByteSize();
    BYTE GetCheck();
    BYTE GetStopBit();
    BOOL GetSync();
    DWORD GetInQue();
    DWORD GetOutQue();
    int GetComStatus();//InitCom的返回值,观察串口是否打开成功,0表示没有串口名称，1表示打开成功，MAXINI32表示串口打开错误
};
