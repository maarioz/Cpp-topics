#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

// RAND_MAX == 2147483647

// https://en.cppreference.com/w/cpp/numeric/random
// https://github.com/effolkronium/random
// https://en.wikipedia.org/wiki/Cryptographically-secure_pseudorandom_number_generator

namespace rng {
	std::mt19937_64 mersenne{ static_cast<std::mt19937_64::result_type>(std::time(nullptr)) };
} // namespace rng

int getRandomNumberBetween(int min, int max) {
	static constexpr double fraction = 1.0 / (RAND_MAX + 1.0);

	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

int getMersenneBetween(int min, int max) {
	std::uniform_int_distribution die{ min, max };
	return die(rng::mersenne);
}

int main(int argc, char* argv[]) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::rand();

	// Basic rng.

	for (int i = 0; i < 30; ++i) { 
		std::cout << getRandomNumberBetween(1,10) << '\n';
	}

	//  Mersenne Twister. 

	for (int i = 0; i < 30; ++i) { 
		std::cout << getMersenneBetween(1,10) << '\n';
	}

	return 0;
}


