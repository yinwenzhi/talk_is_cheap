#include <io.h>
#include <sys/stat.h>
#include <direct.h>
#include <iostream>
#include <fstream>
#include "Log.h"  
Log::Log()
	:m_bEnabled(true)
{
}
 
Log::~Log()
{
}
bool Log::checkFileExist(const string & strName)
{
	// if(_access(strPath.data(),0)==0)
	// 	return true;
	// else
	// 	return false;
	fstream _file;
    _file.open(strName,ios::in);
    if(!_file)
    {
    	std::cout<<strName<<"not existed";
		return false;
    }
    else
    {
    	std::cout<<strName<<"existed";
		return true;
    }

}
bool Log::Open(string sFileName)
{
	//以输出方式打开文件，如果没有文件，那么生成空文件；如果有文件，那么在文件尾追加。写文件的时候是文件指针指向文件末尾。
	m_tOLogFile.open(sFileName.c_str(), ios_base::out | ios_base::app);

	if (!m_tOLogFile)
	{
		
		printf("open %s failed",sFileName);
		perror("because");
		return false;
	}
 
	return true;
}

void Log::Close()
{
	if (m_tOLogFile.is_open())
	{
		m_tOLogFile.close();
	}
}
 
bool Log::CommonLogInit(string name)
{
	time_t tNowTime;
	time(&tNowTime);
 
	tm* tLocalTime = localtime(&tNowTime);
 
	//得到日期的字符串  
	string sDateStr = ValueToStr(tLocalTime->tm_year + 1900) + "-" +
		ValueToStr(tLocalTime->tm_mon + 1) + "-" +
		ValueToStr(tLocalTime->tm_mday);
	// string filename = "Log\\"+name + sDateStr + ".txt";
	// if (!checkFileExist(filename))
	// {
	// 	printf("mkdir %s :",filename);
	// 	_mkdir(filename.c_str());
	// }
	return Open( name + sDateStr + ".txt");
}
 
void Log::Enable()
{
	m_bEnabled = true;
}
 
void Log::Disable()
{
	m_bEnabled = false;
}
 
//得到当前时间的字符串  
string Log::GetTimeStr()
{
	time_t tNowTime;
	time(&tNowTime);
 
	tm* tLocalTime = localtime(&tNowTime);
 
	//"2011-07-18 23:03:01 ";  
	string strFormat = "%Y-%m-%d %H:%M:%S ";
 
	char strDateTime[30] = { '\0' };
	strftime(strDateTime, 30, strFormat.c_str(), tLocalTime);
 
	string strRes = strDateTime;
 
	return strRes;
}