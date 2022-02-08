#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>


void cleanScreen() {
	system("cls");
}


void countUpTo(int n) {
	std::chrono::milliseconds timespan(7);
	for (int i = 0; i < n; i++) {
		cleanScreen();
		std::cout << i;
		std::this_thread::sleep_for(timespan);
	}
}