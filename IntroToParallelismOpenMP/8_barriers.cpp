#include <stdio.h>
#include <omp.h>

void use_barriers()
{
	/*
	A barrier is a point in the parallel region in which all threads must reach
	before any thread may proceed further. Barriers are useful for splitting up
	various phases of a parallel operation because threads will always experi-
	ence load imbalance.
	For example, in a video processing application, multiple threads will process
	the pixels in the frame in parallel, but all threads must complete before mov-
	ing to the next frame.
	
	Barriers are specified as pragmas, as shown in the example below:
	*/
	int a;
	#pragma omp parallel num_threads(4)
	{
		if(omp_get_thread_num() != 2)
			a = omp_get_thread_num();
			
		#pragma omp barrier
		if(omp_get_thread_num() == 2)
			a = omp_get_thread_num();
	}
	
	printf("%d\n", a); //printed value is always 2
}

int main()
{
	use_barriers();
	return 0;
}