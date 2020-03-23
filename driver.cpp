#include "nTrix.h"
#include <ctime>

int main()
{
	try
	{
		int start_s = clock();
		//nTrix<int> noah({{1,2,3},{4,5,6},{7,8,9}});
		nTrix<int> noah({{1,2,3}});
		nVect<int> mama({1,2,3});
		//nTrix<int> sean({{1,2},{3,4},{5,6}});
	  nTrix<int> sean(mama);

		std::cout << noah * 6 << std::endl;
		//std::cout << -sean << std::endl;

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
	return 0;
}
