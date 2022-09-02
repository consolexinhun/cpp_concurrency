#include <mutex>

class some_data {
    int a;
    std::string b;
public:
    void do_something() {}
};

class data_wrapper {
    some_data data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func) {
        std::lock_guard<std::mutex> l(m);
        func(data);
    }
};

some_data* unprotected;
data_wrapper x;

void malicious_function(some_data& protected_data);
void foo();

int main() {
    foo();
    return 0;
}

void malicious_function(some_data& protected_data) {
    unprotected = &protected_data;
}
void foo() {
    x.process_data(malicious_function);
    unprotected->do_something();
}
