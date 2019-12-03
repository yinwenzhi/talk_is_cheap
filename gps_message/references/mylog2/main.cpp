#include "Log.h"  
 
int main()
{
	Log mainLog;
	string a = "log";
	mainLog.CommonLogInit(a);
 
	mainLog << mainLog.GetTimeStr() << "这里是需要自己输入的信息" << endl;
	printf("writ log");
}