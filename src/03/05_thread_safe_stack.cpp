#include "04_thread_safe_stack.h"

#include <iostream>

using std::cout;
using std::endl;

const char* empty_stack::what() const throw() {
    return "empty stack!";
}

template<typename T>
threadsafe_stack<T>::threadsafe_stack() : data(std::stack<T>()) {}

template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;  // 在构造函数中执行拷贝
}

template<typename T>
void threadsafe_stack<T>::push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
}

template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
        throw empty_stack();
    }

    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
    data.pop();
    return res;
}

template<typename T>
void threadsafe_stack<T>::pop(T& value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
        throw empty_stack();
    }

    value = data.top();
    data.pop();
}

template<typename T>
bool threadsafe_stack<T>::empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
}

int main() {
    threadsafe_stack<int> s;
    s.push(5);
    s.pop();
    s.push(1);
    if (!s.empty()) {
        int x;
        s.pop(x);
        cout << x << endl;
    }
    return 0;
}
