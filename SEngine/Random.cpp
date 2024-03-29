#include <ctime>
#include "Random.h"

namespace gasolinn
{
	Random Random::rand;

	Random::Random() :iIndex(0)
	{
		ResetSeed();
	}

	Random::Random(const unsigned long seed) : iIndex(0)
	{
		SetSeed(seed);
	}

	unsigned long Random::Next()
	{
		unsigned long a, b, c, d;
		a = ulState[iIndex];
		c = ulState[(iIndex + 13) & 15];
		b = a^c ^ (a << 16) ^ (c << 15);
		c = ulState[(iIndex + 9) & 15];
		c ^= (c >> 11);
		a = ulState[iIndex] = b^c;
		d = a ^ ((a << 5) & 0xda442d20ul);
		iIndex = (iIndex + 15) & 15;
		a = ulState[iIndex];
		ulState[iIndex] = a^b^d ^ (a << 2) ^ (b << 18) ^ (c << 28);
		return ulState[iIndex];
	}

	float Random::NextFloat()
	{
		unsigned long r = Next();
		return (float)r / 0xFFFFFFFF;
	}

	unsigned long Random::NextInt(int max)
	{
		if (max == 0) return 0;
		return rand.Next() % max;
	}

	unsigned long Random::NextInt(int min, int max)
	{
		if (min == max) return rand.Next() % max;
		if (min == 0 || max == 0) return 0;
		return rand.Next() % (max - min) + min;
	}

	unsigned long Random::GetSeed() const
	{
		return ulSeed;
	}

	void Random::SetSeed(unsigned long seed)
	{
		ulSeed = seed;
		iIndex = 0;

		for (int i = 0; i < 16; i++)
		{
			ulState[i] = seed;
			seed = (seed << 2) | ((seed >> 30) & 0x4);
		}
	}

	void Random::ResetSeed()
	{
		SetSeed((unsigned long)time(NULL));
	}
}