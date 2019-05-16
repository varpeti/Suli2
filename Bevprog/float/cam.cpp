#include <highgui.h>
#include "cv.h"

using namespace cv;


int main()
{
	namedWindow("a");
	VideoCapture cap(0);

	Mat a,b,c;
	char k = 32;
	while (k!=27){
		cap >> b;
		cvtColor(b, b, COLOR_BGR2GRAY);
        GaussianBlur(b, b, Size(9,9), 1.5, 1.5);
        Canny(b, b, 0, 30, 7);
		imshow("a",b);
		k = waitKey(1);
	}
} 