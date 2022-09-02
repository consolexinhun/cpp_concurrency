#include <mutex>

class hierarchical_mutex {
public:
    explicit hierarchical_mutex(unsigned level) {}

    void lock() {}
    void unlock() {}
};

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);
hierarchical_mutex other_mutex(6000);
/* 
如果已经对一个实例上锁，那么只能获取更低级实例上的锁
 */

// 不会对任何互斥量上锁
int do_low_level_stuff() { return 42; }

// 会对 low_level_mutex 上锁
int low_level_func() {
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
    return do_low_level_stuff();
}

void high_level_stuff(int some_param) {}

// high_level_mutex 比 low_level_mutex 更高级
void high_level_func() {
    std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
    high_level_stuff(low_level_func());
}

void do_other_stuff() {}
void other_stuff() {
    high_level_func();
    do_other_stuff();
}

// 遵守规则，运行没问题
void thread_a() { high_level_func(); }

// 运行失败
void thread_b() {
    std::lock_guard<hierarchical_mutex> lk(other_mutex);
    other_stuff();
}

int main() {
    return 0;
}
