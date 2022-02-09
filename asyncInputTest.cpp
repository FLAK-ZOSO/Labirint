#include <iostream>
#include <thread>
#include <future>

int main() {
    // Enable standard literals as 2s and ""s.
    using namespace std::literals;

    // Execute lambda asyncronously.
    auto f = std::async(std::launch::async, [] {
        auto s = ""s;
        if (std::cin >> s) return s;
    });

    // Continue execution in main thread.
    while(f.wait_for(0.1s) != std::future_status::ready) {
        std::cout << "still waiting..." << std::endl;
    }

    std::cout << "Input was: " << f.get() << std::endl;
}