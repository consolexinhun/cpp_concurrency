#include <thread>

void do_something(int* i) { (*i)++; }
void oops();
void do_something_in_current_thread() {}

class scoped_thread {
    std::thread t;
public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_)) {
        if (!t.joinable()) {
            throw std::logic_error("no thread");
        }
    }
    ~scoped_thread() {
        t.join();
    }
    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;
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

void oops() {
    int some_local_state = 0;
    scoped_thread t(std::thread(func(&some_local_state)));
    do_something_in_current_thread();
}

/**
 * @brief 
 * 转移线程所有权
 */
