#include <stdio.h>
#include <cmath>
#include <omp.h>
#include <chrono>

using namespace std::chrono;

double f(double x)
{
	//the function of interest
	return sin(x);
}

double relative_error(double actual, double calculated)
{
	double diff = actual - calculated;
	
	if ( diff < 0)
		diff *= -1;
		
	return diff/actual;
}

void timer()
{
	auto t0 = high_resolution_clock::now();
	//event here
	auto t1 = high_resolution_clock::now();
	
	auto diff = duration_cast<nanoseconds>(t1-t0).count();
}

long double get_integral(double x_0, double x_n, long n)
{
	double x;
	long double delta = ( x_n - x_0) / n;
	long double area = 0;
	
	//remove atomic and use #pragma parallel reduction(area, +)
	#pragma parallel num_thread(4)
	for(x = x_0; x <= x_n - delta; x += delta)
	{
		#pragma omp atomic
			area += f(x) * delta + 0.5 * (f(x) - f(x + delta)) * delta;
	}
	return area;
}

int main(void)
{
	double ans, a, b;
	a = 0;
	b = 2;
	ans = get_integral(a, b, 50000000);
	printf("The area under the curve is: %f\n", ans);
	return 0;
}
