#include <stdio.h>
#include <opencv-3.3.1-dev/opencv2/core.hpp>
#include <opencv-3.3.1-dev/opencv/highgui.h>
#include <opencv-3.3.1-dev/opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv )
{
   //判断输入参数个数是否合法
   if ( argc != 2 )
   {
	   printf("start :");
	   printf("usage: DisplayImage.out <Image_Path>\n");
	   return -1;
   }
    //读入图像
	Mat image;
	image = imread( argv[1], 1 );
	//判断输入路径下图像是否存在
	if ( !image.data )
	{
		printf("No image data \n");
		return -1;
	}
	//新建一个窗口显示图像
	namedWindow("Display Image", WINDOW_AUTOSIZE );
	imshow("Display Image", image);
	waitKey(0);
	return 0;
}

