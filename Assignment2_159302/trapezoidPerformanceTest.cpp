#include <iostream>
#include <chrono>
#include <stdlib.h> 
#include <time.h>
#include <algorithm>

typedef enum {regular_trapezoid, left_trapezoid, right_trapezoid} trapz_type;

class TrapezoidFunction 
{
	friend class TrapezoidFunction2;
	trapz_type tp;
	float a, b, c, d, l_slope, r_slope;
public:
	TrapezoidFunction() {}
	TrapezoidFunction(float x1, float x2, float x3, float x4, trapz_type type);
	float operator()(float x);
};

float TrapezoidFunction::operator()(float x)
{
	switch (tp)
	{
	case regular_trapezoid:
		if ((x <= a) || (x >= d))
			return 0.0f;
		if (x <= b)
			return l_slope * (x - a);
		if (x >= c)
			return  r_slope * (x - d);
		return 1.0f;
	case left_trapezoid:
		if (x <= a)
			return 1.0f;
		if (x >= b)
			return 0.0f;
		return r_slope * (x - b);


	case right_trapezoid:
		if (x <= a)
			return 0.0f;
		if (x >= b)
			return 1.0f;
		return l_slope * (x - a);
	} 

	return 0.0;  /* should't get to this point */
}

TrapezoidFunction::TrapezoidFunction(float x1, float x2, float x3, float x4, trapz_type type)
{
	a = x1;
	b = x2;
	c = x3;
	d = x4;
	tp = type;
	switch (tp) {

	case regular_trapezoid:
		l_slope = 1.0f / (b - a);
		r_slope = 1.0f / (c - d);
		break;

	case left_trapezoid:
		r_slope = 1.0f / (a - b);
		l_slope = 0.0f;
		break;

	case right_trapezoid:
		l_slope = 1.0f / (b - a);
		r_slope = 0.0f;
		break;
	}
}

class TrapezoidFunction2 
{
	float a, b, c, d, l_slope, r_slope;
public:
	TrapezoidFunction2() {}
	TrapezoidFunction2(const TrapezoidFunction& trap);
	float operator()(float x);
};

float TrapezoidFunction2::operator()(float x)
{
	if ((x <= a) || (x >= d))
		return 0.0f;
	if (x <= b)
		return l_slope * (x - a);
	if (x >= c)
		return  r_slope * (x - d);
	return 1.0f;
}

TrapezoidFunction2::TrapezoidFunction2(const TrapezoidFunction& trap)
{
	l_slope = trap.l_slope;
	r_slope = trap.r_slope;
	switch (trap.tp) {

	case regular_trapezoid:
		a = trap.a;
		b = trap.b;
		c = trap.c;
		d = trap.d;
		break;

	case left_trapezoid:
		a = std::numeric_limits<float>::lowest();
		b = std::numeric_limits<float>::lowest();
		c = trap.a;
		d = trap.b;
		break;

	case right_trapezoid:
		a = trap.a;
		b = trap.b;
		c = std::numeric_limits<float>::max();
		d = std::numeric_limits<float>::max();
		break;
	}
}

int main()
{
	srand(time(nullptr));
	constexpr unsigned int length = 10000u;
	TrapezoidFunction trapezoidFunctions[length];
	auto random = [](){return (rand() % 300) / 100.0f;};
	for(unsigned int i = 0u; i != length; ++i)
	{
		float values[] = {random(), random(), random(), random()};
		std::sort(std::begin(values), std::end(values));
		new(&trapezoidFunctions[i]) TrapezoidFunction(values[0], values[1],
			values[2], values[3], (trapz_type)(rand() % 3u));
	}
	TrapezoidFunction2 trapezoidFunction2s[length];
	for(unsigned int i = 0u; i != length; ++i)
	{
		new(&trapezoidFunction2s[i]) TrapezoidFunction2(trapezoidFunctions[i]);
	}
	float inputs[length];
	for(unsigned int i = 0u; i != length; ++i)
	{
		inputs[i] = random();
	}
	
	auto start2 = std::chrono::high_resolution_clock::now();
	float sum2 = 0.0f;
	for(unsigned int i = 0u; i != length; ++i)
	{
		sum2 += trapezoidFunction2s[i](inputs[i]);
	}
	auto end2 = std::chrono::high_resolution_clock::now();
	
	auto start1 = std::chrono::high_resolution_clock::now();
	float sum1 = 0.0f;
	for(unsigned int i = 0u; i != length; ++i)
	{
		sum1 += trapezoidFunctions[i](inputs[i]);
	}
	auto end1 = std::chrono::high_resolution_clock::now();
	
	std::cout << "time 1: " << ((std::chrono::duration<double>)(end1 - start1)).count()
		<< " sum 1: " << sum1 
		<< " time 2: " << ((std::chrono::duration<double>)(end2 - start2)).count() 
		<< " sum 2: " << sum2;
}