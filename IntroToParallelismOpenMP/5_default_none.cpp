#include <stdio.h>
#include <omp.h>

void default_none()
{
	/*
	Three threads are spawned in the first parallel region. The default(none)
	option changes the default scope for all externally declared variables
	from shared to none. This is a safety feature that causes the compiler to gen-
	erate an error on any line in the parallel region that changes an externally
	declared variable whose scope was not explicitly specified in the directive
	options.
	*/
	/*
	Also note the shorthand notation for the parallel region sections, in which
	the “ omp parallel ” and “ omp sections ” directives are combined into a sin-
	gle directive “ omp parallel sections. ” Thread groups within each paral-
	lel section are numbered starting at 0. As a result, in this example,
	omp_get_thread_num() function would return 0 in each thread so individ-
	ual constants in each section differentiate the behavior of each thread.
	The final state of variables a and b in each thread are 10, 11, and 12, respec-
	tively, demonstrating the initialization of the variable a. The printed value of
	b is 12, as assigned in the last section.
	Four threads are spawned in the second parallel region. The final state of
	variable c in each thread is 0, 1, 2, and 3. Because c is marked as a summa-
	tion reduction variable, the printed value of c is 11, calculated as the sum of
	these values as well as the initial value of c.
	*/
	int a = 10, b = 1,c = 5;
	
	#pragma omp parallel sections firstprivate(a) lastprivate(b) default(none)
	{
		#pragma omp section
			b = 0+a;
		
		#pragma omp section
			b = 1+a;
		
		#pragma omp section
			b = 2+a;
	}
	#pragma omp parallel num_threads(4) reduction(+:c)
		c = omp_get_thread_num();
	
	printf("a = %d, b = %d, c = %d\n",a,b,c); // a = 10, b = 12, c = 11
}

int main()
{
	default_none();
	return 0;
}