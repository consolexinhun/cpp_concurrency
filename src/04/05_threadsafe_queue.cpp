#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <chrono>
#include <cstdio>

#include "05_threadsafe_queue.h"

bool more_data_to_prepare() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
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
        /* 01 */
        // data_chunk data;
        // data_queue.wait_and_pop(&data);
        // process(data);
        // puts("consume");
        // if (is_last_chunk(data)) {
        //     break;
        // }

        /* 02 */
        // std::shared_ptr<data_chunk> data = data_queue.wait_and_pop();
        // process(*data);
        // puts("consume");

        /* 03 */
        // data_chunk data;
        // bool ret = data_queue.try_pop(&data);
        // if (ret) {
        //     puts("consume");
        // }

        /* 04 */
        std::shared_ptr<data_chunk> data = data_queue.try_pop();
        if (data != nullptr) {
            puts("consume");
        }
    }
}
