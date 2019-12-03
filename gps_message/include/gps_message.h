
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


class GpsMessage
{
    private:

    public:
        GpsMessage();
        // ~GpsMessage();
        void data_filter(char *buf, char *str);
        int gprmc_analysis(gps_info *p, char *str);
        int gpgga_analysis(gps_info *p, char *str);
		char * assemble(gps_info *p,char* assembled);
};