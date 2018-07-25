#include <RandomNumberGenerator.h>

using Dist = std::uniform_int_distribution<int>;

int RandomNumberGenerator::GenerateRandom(int low, int high)
{
	static std::default_random_engine re{};

	static Dist uid{};
	return uid(re, Dist::param_type{ low,high });
}
