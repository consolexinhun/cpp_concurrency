#include <thread>
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

using std::cout;
using std::endl;

void do_work(unsigned id) { cout << id << endl; }

void f();

int main() {
    f();
    return 0;
}

void f() {
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < 20; i++) {
        threads.push_back(std::thread(do_work, i));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}