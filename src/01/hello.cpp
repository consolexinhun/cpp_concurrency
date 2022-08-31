#include <iostream>
#include <thread>
#include <chrono>

void hello();

int main() {
    std::thread t(hello);
    t.join();
}

void hello() {
    std::cout << "Hello Concurrent World\n"; 
    std::this_thread::sleep_for(std::chrono::seconds(1000));
}
