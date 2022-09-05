#include <mutex>

class some_big_object {};

void swap(some_big_object& lhs, some_big_object& rhs) {}

class X {
    some_big_object some_detail;
    mutable std::mutex m;

public:
    explicit X(some_big_object const& sd) : some_detail(sd) {}

    friend void swap(X& lhs, X& rhs);
};


void swap(X&lhs, X&rhs) {
    if (&lhs == &rhs) {
        return;
    }

    std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
    std::lock(lhs.m, rhs.m);
    swap(lhs.some_detail, rhs.some_detail);
}

int main() {
    return 0;
}
