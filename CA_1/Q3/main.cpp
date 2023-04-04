#include 	"stdio.h"
#include 	"sys/time.h"
#include 	"x86intrin.h"

#define		VECTOR_SIZE		  	1048576 // 2^20 

int main (void)
{
	struct timeval start, end;
	long time1, time2;

	float *fVec1;
	fVec1 = new float [VECTOR_SIZE];

	if (!fVec1) {
		printf ("Memory allocation error!!\n");
		return 1;
	}
	// Initialize vectors with random numbers
	for (long i = 0; i < VECTOR_SIZE; i++)
		fVec1[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100.0));

	// Serial implementation
	gettimeofday(&start, NULL);
	float min_serial = fVec1[0];
	int min_index_serial = 0;

	for(int i = 1; i < VECTOR_SIZE; i++)
		if(fVec1[i] < min_serial)
		{
			min_serial = fVec1[i];
			min_index_serial = i;
		}
	gettimeofday(&end, NULL);
	time1 = end.tv_usec - start.tv_usec;

	// Paralle implementation
	__m128 vec, min_vector;
	gettimeofday(&start, NULL);
	min_vector = _mm_loadu_ps (&fVec1[0]);
	for (long i = 1; i < VECTOR_SIZE; i+=4) {
		vec = _mm_loadu_ps (&fVec1[i]);
		min_vector = _mm_min_ps (min_vector, vec);
	}
	int mins[4];
	mins[0] = _mm_extract_ps(min_vector, 0);
	mins[1] = _mm_extract_ps(min_vector, 1);
	mins[2] = _mm_extract_ps(min_vector, 2);
	mins[3] = _mm_extract_ps(min_vector, 3);
	int min_parallel = mins[0];
	int min_index_parallel = 0;
	for(int i = 1; i < 4; i++)
	{
		if(mins[i] < min_parallel)
		{
			min_parallel = mins[i];
			min_index_parallel = 3 - i;
		}
	}
	int temp = 0;	
	for(int k = 0; k < VECTOR_SIZE; k += 4)
	{
		if(fVec1[k + min_index_parallel] == min_serial)
			temp = k;
	}
	min_index_parallel = temp + min_index_parallel;				
	gettimeofday(&end, NULL);
	time2 = end.tv_usec - start.tv_usec;

	printf ("\nSerial Min = %f , index = %d\n", min_serial, min_index_serial);
	printf ("Parallel Min = %f", min_parallel);
	printf (", index = %d\n", min_index_parallel);
	printf ("Serial Run time = %ld u secods\n", time1);
	printf ("Parallel Run time = %ld u secods\n", time2);
	printf ("Speedup = %f\n\n", (float) (time1)/(float) time2);

	return 0;
}
