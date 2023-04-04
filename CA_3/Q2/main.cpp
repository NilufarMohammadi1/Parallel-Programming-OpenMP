#include 	"stdio.h"
#include 	"sys/time.h"
#include	   "unistd.h"
#include	   "stdlib.h"
#include	   "pthread.h"

#define		VECTOR_SIZE		  	1048576 // 2^20 

typedef struct {
	float *array;
	int start_index;
	int end_index;
}Thread_Params;

int partitioning_serial(float *array, int start_index, int end_index)
{
	float pivot = array[end_index];

	int pivot_index = start_index;

	for(int i = start_index; i < end_index; i++)
	{
		if(array[i] <= pivot)
		{
			float temp = array[pivot_index];
			array[pivot_index] = array[i];
			array[i] = temp;
			pivot_index++;
		}
	}
	float temp = array[pivot_index];
	array[pivot_index] = array[end_index];
	array[end_index] = temp;

	return pivot_index;
}

void quick_sort_serial(float *array, int start_index, int end_index)
{
	if(start_index >= end_index)
		return;

	int pivot_index = partitioning_serial(array, start_index, end_index);

	quick_sort_serial(array, start_index, pivot_index - 1);

	quick_sort_serial(array, pivot_index + 1, end_index);
}

int partitioning_parallel(float *array, int start_index, int end_index)
{
	float pivot = array[start_index];

	int pivot_index = start_index;

	for(int i = start_index; i < end_index; i++)
	{
	   //printf("%f, %f\n", pivot, array[i]);
		if(array[i] <= pivot)
		{
			float temp = array[pivot_index];
			array[pivot_index] = array[i];
			array[i] = temp;
			pivot_index++;	
		}
	}

	float temp = array[pivot_index];
	array[pivot_index] = array[end_index];
	array[end_index] = temp;

	return pivot_index;
}

void *quick_sort_parallel(void *arg)
{

   Thread_Params *input_params = (Thread_Params *)arg;
   float *array = input_params->array;
   int start_index = input_params->start_index;
   int end_index = input_params->end_index;

	if(start_index >= end_index)
		return NULL;
  
	int pivot_index = partitioning_parallel(array, start_index, end_index);

   pthread_t t_h1;
   pthread_t t_h2;
   
   Thread_Params thread_1_params;
   Thread_Params thread_2_params;

   thread_1_params.array = array;
   thread_1_params.start_index = start_index;
   thread_1_params.end_index = pivot_index - 1;

   thread_2_params.array = array;
   thread_2_params.start_index = pivot_index + 1;
   thread_2_params.end_index = end_index;
   //printf("%f\n",array[0]);

   pthread_create(&t_h1, NULL, quick_sort_parallel, (void *)&thread_1_params);
   pthread_create(&t_h2, NULL, quick_sort_parallel, (void *)&thread_2_params);

   pthread_join(t_h1, NULL);
   pthread_join(t_h2, NULL);   

   pthread_exit(NULL);
}

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

   float copy_of_fVec1[VECTOR_SIZE];
   for(int i = 0; i < VECTOR_SIZE; i++)
    	copy_of_fVec1[i] = fVec1[i];

	// Serial implementation

	gettimeofday(&start, NULL);

	quick_sort_serial(fVec1, 0, VECTOR_SIZE);

	gettimeofday(&end, NULL);

	time1 = end.tv_usec - start.tv_usec;

	// Paralle implementation
	
	gettimeofday(&start, NULL);

	Thread_Params thread_params;

	thread_params.array = copy_of_fVec1;
	thread_params.start_index = 0;
	thread_params.end_index = VECTOR_SIZE;

	quick_sort_parallel((void *)&thread_params);
	
	/*-- End of parallel region --*/			
	
	gettimeofday(&end, NULL);

	time2 = end.tv_usec - start.tv_usec;

	printf ("Serial Run time = %ld u seconds\n", time1);
	printf ("Parallel Run time = %ld u seconds\n", time2);
	printf ("Speedup = %ld\n\n",  (time1)/ time2);

	return 0;
}
