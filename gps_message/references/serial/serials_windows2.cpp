//https://www.cnblogs.com/konglongdanfo/p/9135253.html

#include "stdafx.h"
#include "Serial.h"

CSerial::CSerial()
{
    m_pnReusecount = NULL;
    m_hCom = NULL;
    m_hEventRecv = NULL;
    m_hEventSend = NULL;
    m_strCom = _T("");
    m_dwBaudRate = 9600;
    m_byteSize = 8;
    m_byteCheck = NOPARITY;
    m_byteStop = ONESTOPBIT;
    m_bSync = TRUE;
    m_bIsFirst = TRUE;
    //缓冲区变量初始化
    m_dwInQueue = 1024;
    m_dwOutQueue = 1024;
    //超时变量初始化
    COMMTIMEOUTS timeout = {MAXDWORD, 0, 0, 50, 1000};
    m_Timeouts = timeout;
}

CSerial::CSerial(
    CString strCom,
    DWORD dwBaudRate,
    BYTE byteSize,
    BYTE byteCheck,
    BYTE byteStop,
    BOOL bSync)
{
    m_pnReusecount = NULL;
    m_hCom = NULL;
    m_hEventRecv = NULL;
    m_hEventSend = NULL;
    m_strCom = strCom;
    m_dwBaudRate = dwBaudRate;
    m_byteSize = byteSize;
    m_byteCheck = byteCheck;
    m_byteStop = byteStop;
    m_bSync = bSync;
    m_bIsFirst = TRUE;
    //缓冲区变量初始化
    m_dwInQueue = 1024;
    m_dwOutQueue = 1024;
    //超时变量初始化
    COMMTIMEOUTS timeout = {MAXDWORD, 0, 0, 50, 1000};
    m_Timeouts = timeout;
    m_nInitResult = InitCom();
}

CSerial::~CSerial()
{
    if (m_pnReusecount)
    {
        (* m_pnReusecount)--;
        if( 0 >= *m_pnReusecount )
        {
            CloseCom();
            delete m_pnReusecount;
        }
    }
}

void CSerial::CloseCom()
{
    if ( m_hEventRecv )
    {
        CloseHandle(m_hEventRecv);
        m_hEventRecv = NULL;
    }
    if ( m_hEventSend )
    {
        CloseHandle(m_hEventSend);
        m_hEventSend = NULL;
    }
    if ( m_hCom )
    {
        CloseHandle(m_hCom);
        m_hCom = NULL;
    }
}

int CSerial::InitCom()
{
    if ( m_strCom == _T("") ) return 0;//如果串口传入为空，则进行串口初始化
    if ( m_hCom )
    {
        CloseHandle(m_hCom);
    }
    if ( m_bSync )
    {
        m_hCom = CreateFile(m_strCom, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    }
    else
    {
        m_hCom = CreateFile(m_strCom, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, NULL);
    }
    if ( m_hCom == INVALID_HANDLE_VALUE )//串口打开失败
    {
        m_hCom = NULL;
        return 2;
    }
    //设置缓冲区大小，默认为1024;
    SetupComm(m_hCom, m_dwInQueue, m_dwOutQueue);
    //超时设置
    SetCommTimeouts(m_hCom, &m_Timeouts);
    //配置串口
    DCB dcb;
    GetCommState(m_hCom, &dcb);
    dcb.BaudRate = m_dwBaudRate;
    dcb.ByteSize = m_byteSize;
    dcb.Parity = m_byteCheck;
    dcb.StopBits = m_byteStop;
    SetCommState(m_hCom, &dcb);
    PurgeComm(m_hCom, PURGE_TXABORT|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_RXCLEAR);
    if ( m_bIsFirst )
    {
        m_pnReusecount = new int;
        * m_pnReusecount = 1;
        m_bIsFirst = FALSE;
    }
    return 1;
}

void CSerial::ClearError()
{
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    ClearCommError(m_hCom, &dwErrorFlags, &ComStat);
    PurgeComm(m_hCom, PURGE_TXABORT|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_RXCLEAR);
    if ( m_hEventRecv ) ResetEvent(m_hEventRecv);
    if ( m_hEventSend ) ResetEvent(m_hEventSend);
}

DWORD CSerial::WriteData(unsigned char *pBuffer, DWORD dwLength, DWORD dwTimeout)
{
    if ( !m_hCom ) return MAXDWORD;
    DWORD dwToWrite = dwLength;
    DWORD dwWritten = 0;
    BOOL bWrite;
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    ClearCommError(m_hCom, &dwErrorFlags, &ComStat);
    PurgeComm(m_hCom, PURGE_TXABORT|PURGE_TXCLEAR);
    if ( m_bSync )//同步
    {
        bWrite =WriteFile(m_hCom, pBuffer, dwToWrite, &dwWritten, NULL);
        if ( bWrite )
        {
            return dwWritten;
        }
        else
        {
            return MAXDWORD;
        }
    }
    else//异步
    {
        OVERLAPPED osWrite;
        memset(&osWrite, 0, sizeof(OVERLAPPED));
        if ( !m_hEventSend )
        {
            m_hEventSend = CreateEvent(NULL, TRUE, FALSE, NULL);//这个事件必须为手动复位
        }
        osWrite.hEvent = m_hEventSend;
        bWrite = WriteFile(m_hCom, pBuffer, dwToWrite, &dwWritten, &osWrite);
        if ( !bWrite && (ERROR_IO_PENDING == GetLastError()) )//串口写操作未完成
        {
            GetOverlappedResult(m_hCom, &osWrite, &dwWritten, TRUE);//等待写操作完成，这里暂时使用这种操作方式
            PurgeComm(m_hCom, PURGE_TXABORT|PURGE_TXCLEAR);
            ResetEvent(m_hEventSend);
            return dwWritten;
        }
        else if ( !bWrite )//串口写入错误
        {
            ClearCommError( m_hCom, &dwErrorFlags, &ComStat );
            PurgeComm(m_hCom, PURGE_TXABORT|PURGE_TXCLEAR);
            return MAXDWORD;
        }
        return dwWritten;
    }
}

DWORD CSerial::ReadData(unsigned char *pBuffer, DWORD dwLength, DWORD dwTimeout)
{
    if ( !m_hCom ) return MAXDWORD;
    DWORD dwRead;
    DWORD dwReadTrue = 0;
    BOOL bRead;
    //清除错误标志
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    ClearCommError(m_hCom, &dwErrorFlags, &ComStat);
    dwRead = (dwLength <= ComStat.cbInQue)?dwLength:ComStat.cbInQue;
    if ( !dwRead ) return MAXDWORD;//输入缓存区里面没有内容
    if ( m_bSync )//同步
    {
        bRead = ReadFile(m_hCom, pBuffer, dwRead, &dwReadTrue, NULL);
        if ( bRead )
        {
            return dwReadTrue;
        }
        else
        {
            return MAXDWORD;
        }
    }
    else//异步
    {
        OVERLAPPED osRead;
        memset(&osRead, 0, sizeof(OVERLAPPED));
        if ( !m_hEventRecv )
        {
            m_hEventRecv = CreateEvent(NULL, TRUE, FALSE, NULL);//这个事件必须为手动复位
        }
        osRead.hEvent = m_hEventRecv;
        bRead = ReadFile(m_hCom, pBuffer, dwRead, &dwReadTrue, &osRead);
        if ( !bRead && (ERROR_IO_PENDING == GetLastError()) )//读操作未完成
        {
            GetOverlappedResult(m_hCom, &osRead, &dwReadTrue, TRUE);//等待读操作完成，暂时这样操作
            PurgeComm(m_hCom, PURGE_RXABORT|PURGE_RXCLEAR);
            ResetEvent(m_hEventRecv);
            return dwReadTrue;
        }
        else if ( !bRead )
        {
            ClearCommError(m_hCom, &dwErrorFlags, &ComStat);
            PurgeComm(m_hCom, PURGE_RXABORT|PURGE_RXCLEAR);
            return MAXDWORD;
        }
        return dwReadTrue;
    }
}

void CSerial::Purge(DWORD dwFlags)
{
    PurgeComm(m_hCom, dwFlags);
}

int CSerial::SetComString(CString strCom)
{
    CString strTemp = m_strCom;
    m_strCom = strCom;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_strCom = strTemp;
        return -1;
    }
    return 0;
}

int CSerial::SetBaudRate(DWORD dwBaudRate)
{
    DWORD dwTemp = m_dwBaudRate;
    m_dwBaudRate = dwBaudRate;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_dwBaudRate = dwTemp;
        return -1;
    }
    return 0;
}

int CSerial::SetByteSize(BYTE byteSize)
{
    BYTE byteTemp = m_byteSize;
    m_byteSize = byteSize;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_byteSize = byteTemp;
        return -1;
    }
    return 0;
}

int CSerial::SetCheck(BYTE byteCheck)
{
    BYTE byteTemp = m_byteCheck;
    m_byteCheck = byteCheck;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_byteCheck = byteTemp;
        return -1;
    }
    return 0;
}

int CSerial::SetStopBit(BYTE byteStopBit)
{
    BYTE byteTemp = m_byteStop;
    m_byteStop = byteStopBit;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_byteStop = byteTemp;
        return -1;
    }
    return 0;
}

int CSerial::SetSync(BOOL bSync)
{
    BOOL bTemp = m_bSync;
    m_bSync = bSync;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_bSync = bTemp;
        return -1;
    }
    return 0;
}

int CSerial::SetInQue(DWORD dwInQue)
{
    DWORD dwTemp = m_dwInQueue;
    m_dwInQueue = dwInQue;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_dwInQueue = dwTemp;
        return -1;
    }
    return 0;
}

int CSerial::SetOutQue(DWORD dwOutQue)
{
    DWORD dwTemp = m_dwOutQueue;
    m_dwOutQueue = dwOutQue;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_dwOutQueue = dwTemp;
        return -1;
    }
    return 0;
}

int CSerial::SetTimeouts(COMMTIMEOUTS timeouts)
{
    COMMTIMEOUTS timeoutTemp = m_Timeouts;
    m_Timeouts = timeouts;
    m_nInitResult = InitCom();
    if ( 1 != m_nInitResult )
    {
        m_Timeouts = timeoutTemp;
        return -1;
    }
    return 0;
}

CString CSerial::GetComString()
{
    return m_strCom;
}

DWORD CSerial::GetBaudRate()
{
    return m_dwBaudRate;
}

BYTE CSerial::GetByteSize()
{
    return m_byteSize;
}

BYTE CSerial::GetCheck()
{
    return m_byteCheck;
}

BYTE CSerial::GetStopBit()
{
    return m_byteStop;
}

BOOL CSerial::GetSync()
{
    return m_bSync;
}

DWORD CSerial::GetInQue()
{
    return m_dwInQueue;
}

DWORD CSerial::GetOutQue()
{
    return m_dwOutQueue;
}

int CSerial::GetComStatus()
{
    return m_nInitResult;
}

