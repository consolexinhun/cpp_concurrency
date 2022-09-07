#include <deque>
#include <cstddef>

template<typename T, typename Container = std::deque<T>>
class queue {
public:
    explicit queue(const Container&);
    explicit queue(Container&& = Container());
    queue(queue&& q);  // 移动构造

    template<typename Alloc>
    explicit queue(const Alloc&);

    template<typename Alloc>
    queue(const Container&, const Alloc&);

    template<typename Alloc>
    queue(Container&&, const Alloc&);

    template<typename Alloc>
    queue(queue&&, const Alloc&);

    queue& operator=(queue&& q);  // 移动赋值
    void swap(queue&& q);

    bool empty() const;
    typedef typename std::deque<T>::size_type size_type;

    size_type size() const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void push(const T& x);
    void push(T&& x);
    void pop();
};

int main() {
    return 0;
}
