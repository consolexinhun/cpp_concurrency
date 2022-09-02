#include <thread>

class joining_thread {
    std::thread t;

public:
    joining_thread() noexcept = default;

    template<typename Callable, typename ...Args>
    explicit joining_thread(Callable&& func, Args&& ...args):
        t(std::forward<Callable>(func), std::forward<Args>(args)...) {}
    explicit joining_thread(std::thread t_) noexcept: t(std::move(t_)) {}
    joining_thread(joining_thread&& other) noexcept: t(std::move(other.t)) {}
    joining_thread& operator=(joining_thread&& other) noexcept {
        if (joinable()) {
            join();
        }
        t = std::move(other.t);
        return *this;
    }

    void swap(joining_thread& other) noexcept {
        t.swap(other.t);
    }

    std::thread::id get_id() const noexcept {
        return t.get_id();
    }

    bool joinable() const noexcept {
        return t.joinable();
    }

    void join() {
        t.join();
    }

    void detech() {
        t.detach();
    }

    std::thread& as_thread() noexcept {
        return t;
    }

    const std::thread& as_thread() const noexcept {
        return t;
    }
};
