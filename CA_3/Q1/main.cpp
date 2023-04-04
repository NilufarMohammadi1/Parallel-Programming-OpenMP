#include 	"stdio.h"
#include 	"sys/time.h"
#include	"unistd.h"
#include	"stdlib.h"
#include	"pthread.h"

#define		VECTOR_SIZE		  	1048576 // 2^20 

typedef struct {
	float *array;
	int start_index;
	int end_index;
}Thread_Params;

typedef struct {
	float maximum;
	int maximum_index;
}Thread_Results;

void *find_max(void *arg)
{
   Thread_Params *input_params = (Thread_Params *)arg;
   float *array = input_params->array;
   int start_index = input_params->start_index;
   int end_index = input_params->end_index;

   float max_parallel = array[start_index];
   float max_index_parallel = start_index;

   for (int i = start_index + 1; i < end_index; i++)
	 if(array[i] > max_parallel)
	 {
		max_parallel = array[i];
		max_index_parallel = i;
	 }

   Thread_Results* result = new Thread_Results;
   result->maximum = max_parallel;
   result->maximum_index = max_index_parallel;

   pthread_exit(result);
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
	float max_parallel;
	int max_index_parallel;

    pthread_t t_h1;
    pthread_t t_h2;
    pthread_t t_h3;
    pthread_t t_h4;        
   
    Thread_Params thread_1_params;
    Thread_Params thread_2_params;
    Thread_Params thread_3_params;
    Thread_Params thread_4_params;    

    thread_1_params.array = fVec1;
    thread_1_params.start_index = 0;
    thread_1_params.end_index = (VECTOR_SIZE / 4) - 1;

    thread_2_params.array = fVec1;
    thread_2_params.start_index = VECTOR_SIZE / 4;
    thread_2_params.end_index = (VECTOR_SIZE / 2) - 1;

    thread_3_params.array = fVec1;
    thread_3_params.start_index = VECTOR_SIZE / 2;
    thread_3_params.end_index = ((3 * VECTOR_SIZE) / 4) - 1;

    thread_4_params.array = fVec1;
    thread_4_params.start_index = (3 * VECTOR_SIZE) / 4;
    thread_4_params.end_index = VECTOR_SIZE - 1;        


	pthread_create(&t_h1, NULL, find_max, (void *)&thread_1_params);
	pthread_create(&t_h2, NULL, find_max, (void *)&thread_2_params);
	pthread_create(&t_h3, NULL, find_max, (void *)&thread_3_params);
	pthread_create(&t_h4, NULL, find_max, (void *)&thread_4_params);		

    void *t_h1_result;
    void *t_h2_result;
    void *t_h3_result;          
    void *t_h4_result;    

	pthread_join(t_h1, &t_h1_result);
    pthread_join(t_h2, &t_h2_result); 
    pthread_join(t_h3, &t_h3_result); 
    pthread_join(t_h4, &t_h4_result);      

    Thread_Results *result_th[4]; 

    result_th[0] = (Thread_Results *) t_h1_result; 
    result_th[1] = (Thread_Results *) t_h2_result; 
    result_th[2] = (Thread_Results *) t_h3_result; 
    result_th[3] = (Thread_Results *) t_h4_result;
    
    max_parallel = result_th[0]->maximum;
    max_index_parallel = result_th[0]->maximum_index;
	for(int i = 0; i < 3; i++)
		if(result_th[i]->maximum > max_parallel)
		{
			max_parallel = result_th[i]->maximum;
			max_index_parallel = result_th[i]->maximum_index;
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
