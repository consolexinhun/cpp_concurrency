#include <thread>

void some_function() {}
void some_other_function(int) {}

std::thread f();
std::thread g();

int main() {
    std::thread t1 = f();
    t1.join();
    std::thread t2 = g();
    t2.join();
    return 0;
}

std::thread f() {
    void some_function();
    return std::thread(some_function);
}

std::thread g() {
    void some_other_function(int);
    std::thread t(some_other_function, 42);
    return t;
}

/**
 * @brief 
 * 线程所有权在函数外可以转移
 */
