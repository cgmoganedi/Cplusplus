#include <stdio.h>
#include <omp.h>

void atomic_sections()
{
	/*
	An atomic operation is guaranteed to be performed on one thread at any
	given moment in time. In this sense they are indivisible, much like actual
	atoms. In concept they are identical to critical sections, but atomic sections
	can only ensure exclusivity for a single assignment operation, so they are
	used only for SINGLE STATEMENTS. Their advantage is that they have lower
	overhead than critical sections.
	Atomic operations are specified as pragmas, for example:
	*/
	int a = 0;
	#pragma omp parallel num_threads(4)
	{
		#pragma omp atomic
			a++;
	}
	
	printf("%d\n", a); //printed value is always 4
}

int main()
{
	atomic_sections();
	return 0;
}