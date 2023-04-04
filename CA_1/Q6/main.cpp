#include <iostream>
#include "sys/time.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "x86intrin.h"

using namespace cv;
using namespace std;

int main( )
{
	struct timeval start, end;
	long time1, time2;

	// LOAD images
	Mat img_1 = imread("CA01__Image__01.png", IMREAD_GRAYSCALE);
	Mat img_2 = imread("CA01__Image__02.png", IMREAD_GRAYSCALE);

	unsigned int NCOLS = img_1.cols;
	unsigned int NROWS = img_1.rows;

	// Create output images
	Mat out_img_serial  (img_1.rows, img_1.cols, CV_8U) ;
	Mat out_img_parallel  (img_1.rows, img_1.cols, CV_8U) ;	

	// Pointer to the image data (Matrix of pixels)
	unsigned char *img_1_data;
	unsigned char *img_2_data;
	unsigned char *out_image_serial_data;

	img_1_data  = (unsigned char *) img_1.data;
	img_2_data  = (unsigned char *) img_2.data;	
	out_image_serial_data = (unsigned char *) out_img_serial.data;

	// Serial implementation
	gettimeofday(&start, NULL);
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++)
			*(out_image_serial_data + row * NCOLS + col) = (*img_1_data) + (0.25 * (*img_2_data));
	gettimeofday(&end, NULL);
	time1 = end.tv_usec - start.tv_usec;

	__m128i *pImg_1;
	__m128i *pImg_2;	
	__m128i *pRes;
	__m128i m1, m2, m3;
	__m128 alfa = _mm_set1_ps(0.25f);

	pImg_1 = (__m128i *) img_1.data;
	pImg_2 = (__m128i *) img_2.data;	
	pRes = (__m128i *) out_img_parallel.data;

	// Parallel implementation
	gettimeofday(&start, NULL);
	for (int i = 0; i < NROWS; i++)
		for (int j = 0; j < NCOLS / 16; j++)
		{
			m1 = _mm_loadu_si128(pImg_1 + i * NCOLS/16 + j) ;
			m2 = _mm_loadu_si128(pImg_2 + i * NCOLS/16 + j) ;  
			m3 = _mm_add_epi8 (m1, (__m128i)_mm_mul_ps((__m128)m2, alfa));
			_mm_storeu_si128 (pRes + i * NCOLS/16 + j, m3);
		}
	gettimeofday(&end, NULL);
	time2 = end.tv_usec - start.tv_usec;

	//DISPLAY images
	namedWindow( "serial output", WINDOW_AUTOSIZE ); 	// Create a window for display.
	imshow( "serial output", out_img_serial); 				// Show our image inside it.
	namedWindow( "parallel output", WINDOW_AUTOSIZE ); 	// Create a window for display.
	imshow( "parallel output", out_img_parallel ); 				// Show our image inside it.

	waitKey(0);                       					// Wait for a keystroke in the window

	printf ("Serial Run time = %ld \n", time1);
	printf ("Parallel Run time = %ld \n", time2);
	printf ("Speedup = %4.2f\n", (float) (time1)/(float) time2);	
    return 0;
}
