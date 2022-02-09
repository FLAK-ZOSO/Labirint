#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>


void countUpTo(int n) {
	std::chrono::milliseconds timespan(7);
	for (int i = 0; i < n; i++) {
		system("cls");
		std::cout << i;
		std::this_thread::sleep_for(timespan);
	}
}