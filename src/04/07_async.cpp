#include <string>
#include <future>
#include <cstdio>

struct X {
    void foo(int, const std::string&) {}
    std::string bar(const std::string&) { return "bar"; }
};

X x;

// 调用 p->foo(42, hello) p 是指向 x 的指针
std::future<void> f1 = std::async(&X::foo, &x, 42, "hello");
// 调用 tempx.bar(goodbyte) tempx 是 x 的拷贝
std::future<std::string> f2 = std::async(&X::bar, x, "goodbye");

struct Y {
    double operator()(double p) { return p+1; }
};

Y y;

// 调用 tempy(3.141) tempy 通过 Y 的移动构造函数得到
std::future<double> f3 = std::async(Y(), 3.141);
// 调用 y(2.718)
std::future<double> f4 = std::async(std::ref(y), 2.718);

X baz(const X& x) { return x; }
// 调用 baz(x)
std::future<X> f44 = std::async(baz, std::ref(x));

class move_only {
public:
    move_only() {}
    move_only(move_only&&) {}
    move_only(const move_only&) = delete;
    move_only& operator=(move_only&& x) { return x; }
    move_only& operator=(const move_only&) = delete;

    void operator()() {}
};
// 调用 tmp() , tmp 是通过 std::move(move_only())构造得到的
std::future<void> f5 = std::async(move_only());

// 在新线程上执行
std::future<double> f6 = std::async(std::launch::async, Y(), 1.2);
// 在 wait 或 get 时执行
std::future<X> f7 = std::async(std::launch::deferred, baz, std::ref(x));
// 实现选择的方式
std::future<X> f8 = std::async(std::launch::deferred | std::launch::async, baz, std::ref(x));

std::future<X> f9 = std::async(baz, std::ref(x));

int main() {
    f7.wait();  // 调用延迟函数

    printf("%.2f\n", f6.get());
    return 0;
}
