#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <chrono>
#include <cstdio>

template<typename T>
class threadsafe_queue {
    std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;

public:
    void push(T new_value) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }

    void wait_and_pop(T* value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] {
            return !data_queue.empty();
        });
        *value = data_queue.front();
        data_queue.pop();
    }
};

bool more_data_to_prepare() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return true;
}

struct data_chunk {};

data_chunk prepare_data() { return data_chunk(); }

void process(data_chunk&) {}

bool is_last_chunk(data_chunk&) { return false; }

void data_preparation();

void data_processing();

threadsafe_queue<data_chunk> data_queue;

int main() {
    std::thread t1(data_preparation);
    std::thread t2(data_processing);
    t1.join();
    t2.join();
    return 0;
}

void data_preparation() {
    while (more_data_to_prepare()) {
        const data_chunk data = prepare_data();
        data_queue.push(data);
        puts("ok");
    }
}

void data_processing() {
    while (true) {
        data_chunk data;
        data_queue.wait_and_pop(&data);
        process(data);
        puts("consume");
        if (is_last_chunk(data)) {
            break;
        }
    }
}
