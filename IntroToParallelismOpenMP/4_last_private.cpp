#include <stdio.h>
#include <omp.h>

void last_private()
{
	/*
	A variable can also be marked as lastprivate, in which the variable’s state in
	the last loop iteration in parallel-for or the last section in the parallel region is
	assigned to the variable in the master thread after the parallel region.
	*/
	int a, i;
	#pragma omp parallel for num_threads(4) lastprivate(a)
	for(i = 0; i<16; ++i)
	{
		a = omp_get_thread_num();
	}
	printf("%d\n", a); //printed value is 3, since iteration 15 is performed in thread 3.
}
int main()
{
	last_private();
	return 0;
}