
#include<stdio.h>
#include "myLog.h"

int main()
{
	LOGINIT();
	for (int i = 0; i < 1000; i++)
	{
		LOGE("%f .....%d ", 12563.0 * i, i);

	}
	LOGEnd();
	getchar();
    return 0;
}

