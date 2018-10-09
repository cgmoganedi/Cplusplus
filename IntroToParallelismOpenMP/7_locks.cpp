#include <stdio.h>
#include <omp.h>

void use_locks()
{
	/*
	Locks provide a similar functionality as critical sections. Locks are specified
	as functions, so the programmer would call omp_set_lock() to mark the
	beginning of a critical section and omp_unset_lock() to mark its end. Locks
	have an associated handle that the programmer must declare and initialize in
	the master thread before use.
	*/
	int a = 0;
	omp_lock_t mylock;
	omp_init_lock(&mylock);
	
	#pragma omp parallel num_threads(4)
	//for(int k = 0; k < 4; ++k)
	{
		omp_set_lock(&mylock);
		a++;
		omp_unset_lock(&mylock);
	}
	printf("%d\n", a);// printed value is always 4
}

int main()
{
	use_locks();
	return 0;
}