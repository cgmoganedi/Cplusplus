#include <stdio.h>
#include <omp>

void make_reduction()
{
	/*
	A variable can also be specified as a reduction variable, which is a private
	variable, but at the end of the parallel region its final value in each thread is
	combined using a specific operation such as summation and assigned to the
	variable in the master thread after the parallel region. For example:
	*/
	int a;
	#pragma omp parallel num_threads(4) reduction(+:a)
	{
		a = omp_get_thread_num();
	}
	printf("%d", a); // printed value is 0+1+2+356
}

int main()
{
	make_reduction();
	return 0;
}