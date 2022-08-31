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

// pstree -lp 进程pid

/* 正在运行的程序，查看线程栈帧
sudo gdb
attach 进程pid
thread apply all bt 
 */
