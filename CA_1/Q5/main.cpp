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

	// LOAD 2 frames
	Mat frame_1 = imread("CA01__Image__01.png", IMREAD_GRAYSCALE);
	Mat frame_2 = imread("CA01__Image__02.png", IMREAD_GRAYSCALE);

	unsigned int NCOLS = frame_1.cols;
	unsigned int NROWS = frame_1.rows;

	// Create output images
	Mat out_img_serial  (frame_1.rows, frame_1.cols, CV_8U) ;
	Mat out_img_parallel  (frame_1.rows, frame_1.cols, CV_8U) ;		

	// Pointer to the frames (Matrix of pixels)
	unsigned char *_frame_1;
	unsigned char *_frame_2;
	unsigned char *out_image_serial_data;	

	_frame_1  = (unsigned char *) frame_1.data;
	_frame_2  = (unsigned char *) frame_2.data;
	out_image_serial_data = (unsigned char *) out_img_serial.data;

	// Serial implementation
	gettimeofday(&start, NULL);
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++)
			if (*(_frame_1 + row * NCOLS + col) > *(_frame_2 + row * NCOLS + col))
				*(out_image_serial_data + row * NCOLS + col) = *(_frame_1+ row * NCOLS + col) - *(_frame_2 + row * NCOLS + col);
			else
				*(out_image_serial_data + row * NCOLS + col) = *(_frame_2 + row * NCOLS + col) - *(_frame_1 + row * NCOLS + col);
	gettimeofday(&end, NULL);
	time1 = end.tv_usec - start.tv_usec;

	__m128i *Frame_1;
	__m128i *Frame_2;	
	__m128i *pRes;
	__m128i m1, m2, m3;

	Frame_1 = (__m128i *) frame_1.data;
	Frame_2 = (__m128i *) frame_2.data;
	pRes = (__m128i *) out_img_parallel.data;	

	// Parallel implementation
	gettimeofday(&start, NULL);
	for (int i = 0; i < NROWS; i++)
		for (int j = 0; j < NCOLS / 16; j++)
		{
			m1 = _mm_loadu_si128(Frame_1 + i * NCOLS/16 + j) ;
			m2 = _mm_loadu_si128(Frame_2 + i * NCOLS/16 + j) ;  
			m3 = _mm_abs_epi8 (_mm_sub_epi8(m1, m2));
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