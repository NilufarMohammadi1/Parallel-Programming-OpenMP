#include 	"stdio.h"
#include 	"sys/time.h"
#include 	"x86intrin.h"
#include    "math.h"

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
	float sum_serial = 0.0; 
	float mean_serial = 0.0;
	float standard_deviation_serial = 0.0;
	float sum_result[4];

	sum_result[0] = sum_result[1] = sum_result[2] = sum_result[3] = 0.0;
	for (long i = 0; i < VECTOR_SIZE; i+=4)
		sum_result[0] += fVec1[i];
	for (long i = 0; i < VECTOR_SIZE; i+=4)
		sum_result[1] += fVec1[i + 1];
	for (long i = 0; i < VECTOR_SIZE; i+=4)
		sum_result[2] += fVec1[i + 2];
	for (long i = 0; i < VECTOR_SIZE; i+=4)
		sum_result[3] += fVec1[i + 3];
	sum_serial = sum_result[0] + sum_result[1] + sum_result[2] + sum_result[3];
	mean_serial = sum_serial / VECTOR_SIZE;

	sum_result[0] = sum_result[1] = sum_result[2] = sum_result[3] = 0.0;
	for (long i = 0; i < VECTOR_SIZE; i+=4)
		sum_result[0] += ((fVec1[i] - mean_serial) * (fVec1[i] - mean_serial));
	for (long i = 0; i < VECTOR_SIZE; i+=4)
		sum_result[1] += ((fVec1[i + 1] - mean_serial) * (fVec1[i + 1] - mean_serial));
	for (long i = 0; i < VECTOR_SIZE; i+=4)
		sum_result[2] += ((fVec1[i + 2] - mean_serial) * (fVec1[i + 2] - mean_serial));
	for (long i = 0; i < VECTOR_SIZE; i+=4)
		sum_result[3] += ((fVec1[i + 3] - mean_serial) * (fVec1[i + 3] - mean_serial));
	sum_serial = sum_result[0] + sum_result[1] + sum_result[2] + sum_result[3];
	standard_deviation_serial = sqrt(sum_serial / VECTOR_SIZE);

	gettimeofday(&end, NULL);
	time1 = end.tv_usec - start.tv_usec;

	// Paralle implementation
	__m128 vec, vector_size, sum_vector, mean_vector, standard_deviation_vector;

	float mean_parallel, standard_deviation_parallel;

	gettimeofday(&start, NULL);
	sum_vector = _mm_set1_ps(0.0f);
	vector_size = _mm_set1_ps(1048576.0f);
	for (long i = 0; i < VECTOR_SIZE; i+=4) {
		vec   = _mm_loadu_ps (&fVec1[i]);
		sum_vector   = _mm_add_ps (sum_vector, vec); 
	}
	sum_vector = _mm_hadd_ps (sum_vector, sum_vector);
	sum_vector = _mm_hadd_ps (sum_vector, sum_vector);
	mean_vector = _mm_div_ps (sum_vector, vector_size);
	mean_parallel = _mm_cvtss_f32(mean_vector);

	sum_vector = _mm_set1_ps(0.0f);
	for (long i = 0; i < VECTOR_SIZE; i+=4) {
		vec = _mm_loadu_ps (&fVec1[i]);
		vec = _mm_sub_ps (vec, mean_vector);
		vec = _mm_mul_ps (vec, vec);
		sum_vector   = _mm_add_ps (sum_vector, vec); 
	}
	sum_vector = _mm_hadd_ps (sum_vector, sum_vector);
	sum_vector = _mm_hadd_ps (sum_vector, sum_vector);
	mean_vector = _mm_div_ps (sum_vector, vector_size);
	standard_deviation_parallel = _mm_cvtss_f32(_mm_sqrt_ps (mean_vector));	

	gettimeofday(&end, NULL);
	time2 = end.tv_usec - start.tv_usec;

	printf ("\nSerial Mean = %f \n", mean_serial);
	printf ("Parallel Mean = %f \n", mean_parallel);
	printf ("Serial Standard Deviation = %f \n", standard_deviation_serial);
	printf ("Parallel Standard Deviation = %f \n", standard_deviation_parallel);	
	printf ("Serial Run time = %ld u secods\n", time1);
	printf ("Parallel Run time = %ld u secods\n", time2);
	printf ("Speedup = %f\n\n", (float) (time1)/(float) time2);

	return 0;
}
