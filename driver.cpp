#include "nTrix.h"
#include "PID.h"
#include "lander.h"
#include "filter.h"
#include <ctime>
#include <random>

int main()
{
	try
	{
		//int start_s = clock();
		lander moon(.1, {0,0,0}, 3.141593/8);
		nVect<float> state({0,0,0});
		std::random_device rd;
		std::mt19937 gen(rd());
		float sample;
		std::normal_distribution<float> dist(5.0,1.0);
		float original;
		float altered;
		int array[100] = {0};

		for(int i = 0; i < 2000; ++i)
		{
			state = moon(state);
			//std::cout << "original: " << state[0] << std::endl;
			original = state[0];
			std::normal_distribution<float> dist(state[0], state[0] * .25);
			state[0] = dist(gen);
			//std::cout << "with noise: " << state[0] << std::endl;
			altered = state[0];
			//std::cout << "time: " << i << " " << moon << std::endl;
			array[(int)((std::abs(altered - original)/original) * 100)]++;

		}

		for(int i = 0; i < 100; ++i)
		{
			std::cout << "percent: " << i << " frequency: " << array[i] << std::endl;
		}
		//int stop_s = clock();
		//std::cout << "time: " << (stop_s - start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;
	}
	catch(std::domain_error& e)
	{
		std::cerr << "Exception caught, index out of range: "
			<< e.what() << std::endl;
	}
	catch(std::invalid_argument& e)
	{
		std::cerr << "Invalid operation of matrices of 2"
			<< " different sizes" << std::endl;
	}
	catch(std::range_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
