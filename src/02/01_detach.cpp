#include <thread>

void do_something(int* i) { (*i)++; }
void oops();

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
    func my_func(&some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();  // 不等待线程结束
}  // 分离线程可能还在运行


/**
 * @brief 
 * 如果子线程中有变量的指针或者引用，那么可能会访问已经销毁的变量，引发错误
 */
