#include <thread>

void do_something(int* i);
void oops();
void do_something_in_current_thread() {}

class thread_guard {
    std::thread &t;
public:
    explicit thread_guard(std::thread& t_) : t(t_) {}
    ~thread_guard() {
        if (t.joinable()) {
            t.join();
        }
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

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
    thread_guard g(t);
    do_something_in_current_thread();
}

/**
 * @brief 
 * 析构函数中 join()，即使主线程异常发生，也会调用析构
 */
