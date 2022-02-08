#include <iostream>
#include <chrono>
#include <ctime>


int main() {
	std::chrono::time_point<std::chrono::system_clock> start, end;

    char mossa;
	start = std::chrono::system_clock::now();
	std::cin >> mossa;
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << elapsed_seconds.count() << "s\n";
}
