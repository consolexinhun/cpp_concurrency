#include "07_joining_thread.h"

void do_something(int* i) { (*i)++; }
void oops();
void do_something_in_current_thread() {}

struct func {
    int* i;
    explicit func(int* i_): i(i_) {}
    void operator()() {
        for (unsigned j = 0; j < 1000000; j++) {
            do_something(i);  //
        }
    }
};

int main() {
    oops();
    return 0;
}

void oops() {
    int some_local_state = 0;
    joining_thread th(std::thread(func(&some_local_state)));
    do_something_in_current_thread();
}
