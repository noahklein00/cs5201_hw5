#include "nTrix.h"
#include "PID.h"
#include "lander.h"
#include "filter.h"
#include "dummy.h"
#include "lowPass.h"
#include "kalman.h"
#include <ctime>
#include <random>

float gaussian(const float mean);

int main()
{
	try
	{
		dummy<float> dum_filt;
		lander dum_land(.1, {0,0,0}, 3.141593/8.0);
		nVect<float> dum_state({0,0,0});

		lowPass<float> low_filt(.1, 10, dum_state);
		lander low_land(.1, {0,0,0}, 3.141593/8.0);
		nVect<float> low_state({0,0,0});

		kalman<float> kal_filt({{1,(.5 * .1),0},{0,1,.1},{0,0,0}},
													 {{0,0,0},{0,0,0},{0,0,-4.0/100000.0}},
												 	 {0,0,0},
												 	 {{1,0,0},{0,1,0},{0,0,1}},
												 	 {{0,0,0},{0,0,0},{0,0,0}},
												 	 {{.25,0,0},{0,.25,0},{0,0,.25}}, //.25
												 	 {{1,0,0},{0,1,0},{0,0,1}});
		lander kal_land(.1, {0,0,0}, 3.141593/8);
		nVect<float> kal_state({0,0,0});

		lowPass<float> comb_low_filt(.1, 10, dum_state);
		kalman<float> comb_kal_filt({{1,(.5 * .1),0},{0,1,.1},{0,0,0}},
													 {{0,0,0},{0,0,0},{0,0,-4.0/100000.0}},
												 	 {0,0,0},
												 	 {{1,0,0},{0,1,0},{0,0,1}},
												 	 {{0,0,0},{0,0,0},{0,0,0}},
												 	 {{.25,0,0},{0,.25,0},{0,0,.25}}, //.25
												 	 {{1,0,0},{0,1,0},{0,0,1}});
		lander comb_land(.1, {0,0,0}, 3.141593/8.0);
		nVect<float> comb_state({0,0,0});

		for(int i = 0; i < 2000; ++i)
		{
			dum_state = dum_land(dum_state);
			// std::cout << "clean state: " << dum_state << std::endl;
			dum_state[0] = gaussian(dum_state[0]);
			dum_state[1] = gaussian(dum_state[1]);
			dum_state[2] = gaussian(dum_state[2]);
			dum_state = dum_filt(dum_state);
			//
			low_state = low_land(low_state);
			// std::cout << "clean state: " << low_state << std::endl;
			low_state[0] = gaussian(low_state[0]);
			low_state[1] = gaussian(low_state[1]);
			low_state[2] = gaussian(low_state[2]);
			low_state = low_filt(low_state);

			kal_state = kal_land(kal_state);
			kal_state[0] = gaussian(kal_state[0]);
			kal_state[1] = gaussian(kal_state[1]);
			kal_state[2] = gaussian(kal_state[2]);
			kal_state = kal_filt(kal_state, kal_land.getSignal());

			comb_state = comb_land(comb_state);
			comb_state[0] = gaussian(comb_state[0]);
			comb_state[1] = gaussian(comb_state[1]);
			comb_state[2] = gaussian(comb_state[2]);
			comb_state = comb_low_filt(comb_state);
			comb_state = comb_kal_filt(comb_state, comb_land.getSignal());

			std::cout << "time: " << i << " " << dum_land << " " << low_land
				<< " " << kal_land << " " << comb_land << std::endl;
		}
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

float gaussian(const float mean)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	float sample;
  std::normal_distribution<float> dist(mean, mean * .025);
  return dist(gen);
}
