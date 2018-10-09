#include <stdio.h>
#include <omp.h>
void critical_sections()
{
	/*
	Critical sections are implemented as pragmas. Only one thread can execute
	code in a critical section at any time, meaning that a thread that encounters a
	critical section will wait to enter until all threads executing or waiting on the
	critical section have exited it. This creates a serialization effect and causes a
	loss in parallelism, so the use of critical sections should be minimized to
	maximize performance.
	
	Critical sections are necessary when threads perform read-modify-write
	operations on shared variables. In the following example, the parallel region
	manipulates a shared variable named “place” that is used to determine the
	order in which each thread reaches that place in the code. Since the shared
	variable is incremented, this section is marked as a critical section. This
	way, only one thread can execute this code at one time, avoiding any data
	sharing errors. In this example, the entire parallel section is in a critical sec-
	tion, which makes the use of the parallel region redundant since this would
	not allow any of the threads to execute in parallel.
	*/
	int place = 0;
	#pragma omp parallel num_threads(4)
	{
		#pragma omp critical (mycritsec)
		{
			place++;
			printf("thread %d finished in position %d\n",
				omp_get_thread_num(), place);
		}
	}
	printf("parallel region ended\n");
	
	/*
	Compile this example with the option “-fopenmp.” When executed, the
	master thread, thread 0, always reaches the critical section first but the
	worker threads reach the print in different orderings each run. Also notice
	that the print statement that is immediately after the parallel section will
	always print after all worker threads finish.
	*/
}

int main()
{
	critical_sections();
	return 0;
}