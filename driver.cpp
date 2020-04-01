#include "nTrix.h"
#include "PID.h"
#include "lander.h"
#include <ctime>

int main()
{
	try
	{
		int start_s = clock();
		//nTrix<int> noah({{1,2,3},{4,5,6},{7,8,9}});
		//nTrix<float> noah({{4,-1,0,2},{3,5,-2,1},{0,7,0,-1},{4,0,3,0}});
		lander moon(.1, {0,0,0}, 3.141593/8);
		nVect<float> state({0,0,0});

		//std::cout << noah.invert() << std::endl;
		for(int i = 0; i < 2000; ++i)
		{
			state = moon(state);
			std::cout << "time: " << i << " " << moon << std::endl;
		}

		int stop_s = clock();
		std::cout << "time: " << (stop_s - start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;
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
