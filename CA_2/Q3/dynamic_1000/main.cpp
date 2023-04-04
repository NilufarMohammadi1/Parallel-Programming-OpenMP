#include <stdio.h>
#include <math.h>
#include <sys/time.h> 
#include <sys/resource.h>  
#include <omp.h>

double timeGetTime() 
{     
  struct timeval time;     
  struct timezone zone;     
  gettimeofday(&time, &zone);     
  return time.tv_sec + time.tv_usec*1e-6; 
}  


const long int VERYBIG = 100000;

int main( void )
{
  int i;
  long int j, k, sum;
  double sumx, sumy, total, z;
  double starttime, starttime_thread, elapsedtime_serial;
  double elapsedtime_parallel[6];
  double elapsedtime_thread[4] = {0};
  // ---------------------------------------------------------------------
  // Output a start message
  printf( "Serial timing for %ld iterations \n\n", VERYBIG );

  // repeat experiment several times
  for( i=0; i<1; i++ ){
    // get starting time
    starttime = timeGetTime();
    // reset check sum and total
    sum = 0;
    total = 0.0;
    for( int j=0; j<VERYBIG; j++ ){
        // increment check sum
        sum += 1;
        
        // Calculate first arithmetic series
        sumx = 0.0;
        for( k=0; k<j; k++ )
          sumx = sumx + (double)k;

        // Calculate second arithmetic series
        sumy = 0.0;
        for( k=j; k>0; k-- )
          sumy = sumy + (double)k;

        if( sumx > 0.0 )total = total + 1.0 / sqrt( sumx );
        if( sumy > 0.0 )total = total + 1.0 / sqrt( sumy );
    }
    
    // get ending time and use it to determine elapsed time
    elapsedtime_serial = timeGetTime() - starttime;

    // report elapsed time
    printf("Time Elapsed Serial %10d mSecs Total=%lf Check Sum = %ld\n",
                    (int)(elapsedtime_serial * 1000), total, sum );
  }

  // ---------------------------------------------------------------------

  // Output a start message
  printf( "\nOpenMP Parallel Timings for %ld iterations \n\n", VERYBIG );

  // repeat experiment several times
  for( i=0; i<6; i++ )
  {
    // get starting time
    starttime = timeGetTime();
    // reset check sum and total
    sum = 0;
    total = 0.0;
    
    // Work loop, do some work by looping VERYBIG times
    #pragma omp parallel for     \
      num_threads (4) \
      private( sumx, sumy, k )   \
      reduction( +: sum, total ) \
      schedule( dynamic, 1000 )

      for( int j=0; j<VERYBIG; j++ )
      {
        starttime_thread = timeGetTime();

        // increment check sum
        sum += 1;
         
        // Calculate first arithmetic series
        sumx = 0.0;
        for( k=0; k<j; k++ )
         sumx = sumx + (double)k;

        // Calculate second arithmetic series
        sumy = 0.0;
        for( k=j; k>0; k-- )
          sumy = sumy + (double)k;

        if( sumx > 0.0 )total = total + 1.0 / sqrt( sumx );
        if( sumy > 0.0 )total = total + 1.0 / sqrt( sumy );

        elapsedtime_thread[omp_get_thread_num()] += (timeGetTime() - starttime_thread);     
      }

    // get ending time and use it to determine elapsed time
    elapsedtime_parallel[i] = timeGetTime() - starttime;

  }

  double sum_of_parallel_elapsedtime = 0;
  
  for(int n = 0; n < 6; n++)
    sum_of_parallel_elapsedtime += elapsedtime_parallel[n];

  double mean_parallel_elapsed_time = sum_of_parallel_elapsedtime/6;

  // report each thread elapsed time
  printf("Time Elapsed thread 0 %10d mSecs\n",
                   (int)(elapsedtime_thread[0] * 1000));

  printf("Time Elapsed thread 1 %10d mSecs\n",
                   (int)(elapsedtime_thread[1] * 1000));
  
  printf("Time Elapsed thread 2 %10d mSecs\n",
                   (int)(elapsedtime_thread[2] * 1000));
  
  printf("Time Elapsed thread 3 %10d mSecs\n",
                   (int)(elapsedtime_thread[3] * 1000));

  // report mean parallel elapsed time
  printf("Time Elapsed Parallel %10d mSecs Total=%lf Check Sum = %ld\n\n",
                   (int)(mean_parallel_elapsed_time * 1000), total, sum );

  printf("Speedup = %f\n\n", (float) (elapsedtime_serial)/(float) mean_parallel_elapsed_time);

  // return integer as required by function header
  return 0;
}

