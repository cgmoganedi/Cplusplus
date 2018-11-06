#include <stdio.h>
#include <omp.h>

void heavy_computation()
{
	#pragma omp parallel
	{
		// code to be executed in each thread
	}
	
	#pragma omp parallel
		
		#pragma omp sections
		{
			#pragma omp section
			{
				// code executed in first thread
				printf ("id = %d, \n", omp_get_thread_num());
			}
			
			#pragma omp section
			{
				// code executed in second thread
				printf ("id = %d, \n", omp_get_thread_num());
			}
		}
	
	int a = 1;
	/*
	Private variables are local to each thread, such that changes to the variable
	are only visible to the thread making the change and the variable state is
	destroyed when the thread is destroyed. Each thread has a local copy of the
	variable, so it does whatever it wants with it, without affecting other threads.
	Private scope is illustrated in the next example, in which the updates to the
	private variable are lost after the parallel region.
	*/
	#pragma omp parallel num_threads(2) private(a)
	{
		a = 2; // value will be destroyed at the end
	}
	printf("%d\n", a); // printed value is 1
}

void first_private()
{
	int a = 10;
	/*
	Variables can also be marked as “firstprivate” in which the OpenMP
	runtime initializes the variable in the parallel region the same way as it
	would for shared variables, that is, using the variable’s state prior to the
	parallel region.
	*/	
	#pragma omp parallel num_threads(4) firstprivate(a)
	{
		a += omp_get_thread_num(); //initial value of a = 1 for each thread
		printf("%d\n", a);
	}
}

int main()
{
	heavy_computation();
	first_private();
	return 0;
}
