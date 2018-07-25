#pragma once 

#include <random>
#include <functional>
#include <ctime>

class RandomNumberGenerator
{
public:
	// http://www.stroustrup.com/C++11FAQ.html#std-random
	static int GenerateRandom(int low, int high);
};