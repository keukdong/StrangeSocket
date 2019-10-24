#include <iostream>
#include "../../StrangeNet/Include/StrangeNet.h"
#include <thread>
#include <chrono>

// 외부참조
#pragma comment(lib, "StrangeNet.lib")

int main()
{
	try
	{
		std::cout << "StrangeNet World!\n";
		CSocket socket(SocketType::TCP);

		std::cout << "BindAnyPort!\n";
		socket.BindAnyPort();

		std::cout << "Close Socket!\n";
		socket.Close();

		// https://jacking.tistory.com/988
		std::chrono::duration<double> sec(1);
		std::this_thread::sleep_for(sec);

	}
	catch (std::exception& e)
	{
		std::cout << "Exception : " << e.what() <<std::endl;
	}

	return 0;
}

