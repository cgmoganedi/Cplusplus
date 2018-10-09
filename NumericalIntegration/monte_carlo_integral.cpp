#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cmath>

using namespace std::chrono;

#define frand() ((double) rand() / (RAND_MAX+1.0))

double f(double x)
{
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
	//work
	auto t1 = high_resolution_clock::now();
	auto diff = duration_cast<nanoseconds>(t1-t0).count();
}

double random(double a, double b)
{
	return a + frand() * (b-a);
}


struct point
{
	double x, y;
	point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	point(double a, double b, double min_y, double max_y)
	{
		this->x = random(a, b);
		this->y = random(min_y, max_y);
	}
};

long double get_integral(double a, double b, double max_y)
{
	unsigned long long i, points_below = 0, num_of_part = 7000000;//7000000000;
	
	#pragma omp parallel for num_threads(4)
	for(i = 0; i < num_of_part; ++i)
	{
		point rand_point(a, b, 0, max_y);
		
		if ( rand_point.y <= f(rand_point.x) )
		{
			#pragma omp atomic
				points_below++;
		}
	}
	
	double perc = (long double)points_below/num_of_part;
	double total_rect_area = ((b - a)*(max_y-0));
	
	return perc * total_rect_area;
}

int main(void)
{
	double a, b, max_y;
	a = 0;
	b = 2;
	max_y = 1;
	double area = get_integral(a, b, max_y);
	printf("Area under curve: %lf\n", area);
	return 0;
}