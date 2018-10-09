#include <stdio.h>
#include <omp.h>

void thread_private()
{
	/*
	The programmer can also instruct the OpenMP runtime to retain the
	variable state in each individual thread, even between parallel regions,
	using the “threadprivate” direction option. Threadprivate variables must
	be allocated as global or static variables, and the threadprivate directive
	must be used as a standalone directive. For example:
	*/
	static int a; // threadprivate variables must be global
	
	//threadprivate() must be used as a standalone OMP directive
	#pragma omp threadprivate(a) 
	
	//first parallel region sets four seperate 'versions' of a variable
	#pragma omp parallel num_threads(4) 
	{
		a = omp_get_thread_num();
	}
	//second parallel region recalls the first four 'versions' of a variable
	#pragma omp parallel num_threads(4)
	{
		printf("%d\n", a);
	}
	
	/*
	Threadprivate variables can be initialized using the “copyin” directive
	option, as shown below.
	*/
	a = 1;
	#pragma omp threadprivate(a)
	
	#pragma omp parallel num_threads(4) copyin(a)
	{
		a+=omp_get_thread_num(); // initial value of a=1
	}
}

int main()
{
	thread_private();
	return 0;
}