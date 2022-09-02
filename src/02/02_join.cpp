#include <thread>

void do_something(int* i);
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

void do_something(int* i) {
    (*i)++;
}

void oops() {
    int some_local_state = 0;
    func my_func(&some_local_state);
    std::thread t(my_func);
    try {
        do_something_in_current_thread();
    } catch(...) {
        t.join();
        throw;
    }

    t.join();
}

/**
 * @brief 
 * 在异常处理时调用 join() ，确保异常发生时不会跳过 join()
 */
