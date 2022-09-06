#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <chrono>
#include <cstdio>

bool more_data_to_prepare() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return true;
}

struct data_chunk {};

data_chunk prepare_data() { return data_chunk(); }

void process(data_chunk&) {}

bool is_last_chunk(data_chunk&) { return false; }

std::mutex m;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation();

void data_processing();

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
        std::lock_guard<std::mutex> lk(m);
        data_queue.push(data);
        data_cond.notify_one();
        puts("ok");
    }
}

void data_processing() {
    while (true) {
        std::unique_lock<std::mutex> lk(m);
        data_cond.wait(lk, [] {
            return !data_queue.empty();
        });
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        process(data);
        puts("consume");
        if (is_last_chunk(data)) {
            break;
        }
    }
}
