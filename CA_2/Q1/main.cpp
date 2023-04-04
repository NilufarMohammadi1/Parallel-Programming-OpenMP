#include 	"stdio.h"
#include 	"sys/time.h"
#include	"unistd.h"
#include	"stdlib.h"
#include	"omp.h"

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
	float max_serial = fVec1[0];
	int max_index_serial = 0;

	for(int i = 1; i < VECTOR_SIZE; i++)
		if(fVec1[i] > max_serial)
		{
			max_serial = fVec1[i];
			max_index_serial = i;
		}
	gettimeofday(&end, NULL);
	time1 = end.tv_usec - start.tv_usec;

	// Paralle implementation
	
	gettimeofday(&start, NULL);

	float max_parallel = fVec1[0];
	int max_index_parallel = 0;
	int i;

	#pragma omp parallel shared(max_parallel, max_index_parallel, fVec1) private(i)
	{
		#pragma omp for
			for (i = 1; i < VECTOR_SIZE; i++)
				if(fVec1[i] > max_parallel)
				{
					max_parallel = fVec1[i];
					max_index_parallel = i;
				}

	} 
	
	/*-- End of parallel region --*/			
	
	gettimeofday(&end, NULL);
	time2 = end.tv_usec - start.tv_usec;

	printf ("\nSerial Max = %f , index = %d\n", max_serial, max_index_serial);
	printf ("Parallel Max = %f", max_parallel);
	printf (", index = %d\n", max_index_parallel);
	printf ("Serial Run time = %ld u seconds\n", time1);
	printf ("Parallel Run time = %ld u seconds\n", time2);
	printf ("Speedup = %f\n\n", (float) (time1)/(float) time2);

	return 0;
}
