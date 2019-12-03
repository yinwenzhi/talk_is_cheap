

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// --------------------- 
// 作者：艾露米婭娜 
// 来源：CSDN 
// 原文：https://blog.csdn.net/qq_17308321/article/details/80714560 
// 版权声明：本文为博主原创文章，转载请附上博文链接！


typedef struct _date {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}date;


typedef struct _gps_info {
	double latitude; //经度
	double longitude; //纬度
	int latitude_degree; //度
	int latitude_cent; //分
	int latitude_second; //秒
	int longitude_degree; //度
	int longitude_cent; //分
	int longitude_second; //秒
	double speed; //速度
	double direction; //航向
	double height; //海拔高度
	int satellite; //卫星编号
	char ns;
	char ew;
	date time;
}gps_info;

void data_filter(char *buf, char *str)
{

	int count = 0;
	int j = 0;
	int i = 0;
	printf("i = %d : ", i);
	while (str[count] != '\0')
	{
		if (str[count] != ',')
		{
			
			//buf[i][j] = str[count];
			* (buf +i*128 +j) = str[count];
			//printf("buf[%d][%d] = %c  ", i,j, str[count]);
			
			printf("%c", str[count]);
			j++;
		}
		else
		{
			
			*(buf + i * 128 + j) = '\0';
			i++;
			j = 0;
			printf(" \n");
			printf("i = %d : ", i);
			
		}
		++count;

	}
	*(buf + i * 128 + j) = '\0';

	// buf[count] = '\0';  

}

// GPRMC解析函数

// GPRMC包含了几乎我需要的所有信息,位置时间,地面速率等等
/**
* @gprmc_analysis
*
* @brief 解析gprmc
*
* @param[out] p
* 输出到p指向的结构体
* @param[in] str
* 包含逗号的原始字符串.
*
* @return
* SUCCESS 0
* FAILURE <0.
*/

int gprmc_analysis(gps_info *p, char *str)
{
	//unsigned char *str2 = str;
	//printf("str[0]= %c", &str[3]);

	char buf[32][128];
	int i;
	if (str[5] != 'C') //非GPRMC
	{
		return -1;
	}
	if (str[18] != 'A') //无效数据
	{
		return -2;
	}
	data_filter( * buf, str);
	printf(" \n ");
	for (i = 0; i < 12; i++)
	{
		printf("buf[%d]= %s \n ",i, buf[i]);
	}
	printf("\n");
	p->ns = buf[4][0];
	p->ew = buf[6][0]; //经度半球
	p->latitude = atof(buf[3]);
	p->longitude = atof(buf[5]); //经纬度
	p->latitude_degree = (int)p->latitude / 100; //转换成度分秒
	p->latitude_cent = (int)(p->latitude - p->latitude_degree * 100);
	p->latitude_second = (int)(((p->latitude - p->latitude_degree * 100) - p->latitude_cent) * 60);
	p->longitude_degree = (int)p->longitude / 100; //转换成度分秒
	p->longitude_cent = (int)(p->longitude - p->longitude_degree * 100);
	p->longitude_second = (int)(((p->longitude - p->longitude_degree * 100) - p->longitude_cent) * 60);
	p->speed = atof(buf[7]); //地面速率
	p->speed *= 1.85;
	p->direction = atof(buf[8]); //航向
	p->time.year = (buf[9][4] - '0') * 10 + buf[9][5] - '0'; //时间
	p->time.month = (buf[9][2] - '0') * 10 + buf[9][3] - '0';
	p->time.day = (buf[9][0] - '0') * 10 + buf[9][1] - '0';
	p->time.hour = (buf[1][0] - '0') * 10 + buf[1][1] - '0';
	p->time.minute = (buf[1][2] - '0') * 10 + buf[1][3] - '0';
	p->time.second = (buf[1][4] - '0') * 10 + buf[1][5] - '0';
	return 0;
}


// GPGGA解析函数

// GPGGA用来获取海拔高度和卫星编号.

/**
* @gpgga_analysis
*
* @brief 解析gpgga
*
* @param[out] p
* 输出到p指向的结构体
* @param[in] str
* 包含逗号的原始字符串.
*
* @return
* SUCCESS 0
* FAILURE -1.
*/
int gpgga_analysis(gps_info *p, char *str)
{
	char buf[32][128];
	int i;
	if (str[4] != 'G')
	{
		return -1;
	}
	data_filter(*buf, str);
	for (i = 0; i < 13; i++)
	{
		printf("%s ", buf[i]);
	}
	printf("\n");
	p->height = atof(buf[9]);
	p->satellite = atoi(buf[7]);
	return 0;
}


int main()
{
	char tmp[128] = "$GPRMC,092927.000,A,2235.9058,N,4546.40891,E,31.14,74.11,150618,,N*49";
	char tmp2[128] = "$GPGGA,092927.000,2235.9058,N,11400.0518,E,2,9,1.03,53.1,M,-2.4,M,0.0,0*6B";
	gps_info gps_st;
	memset(&gps_st, 0, sizeof(gps_st));
	gprmc_analysis(&gps_st, tmp);
	gpgga_analysis(&gps_st, tmp2);
	printf("%c %c\n", gps_st.ns, gps_st.ew);
	printf("%d度%d分%d秒\n", gps_st.latitude_degree, gps_st.latitude_cent, gps_st.latitude_second);
	printf("%d度%d分%d秒\n", gps_st.longitude_degree, gps_st.longitude_cent, gps_st.longitude_second);
	printf("%lf %lf\n", gps_st.speed, gps_st.direction);
	printf("%d年%d月%d日%d时%d分%d秒\n", gps_st.time.year, gps_st.time.month, gps_st.time.day, gps_st.time.hour, gps_st.time.minute, gps_st.time.second);
	printf("海拔高度 %lf, 卫星编号 %d", gps_st.height, gps_st.satellite);
	return 0;
}




