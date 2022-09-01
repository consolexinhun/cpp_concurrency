#include <thread>
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <numeric>

using std::cout;
using std::endl;

template<typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init);

int main() {
    std::vector<int> vi;
    for (int i = 0; i < 10; i++) {
        vi.push_back(i);
    }
    int sum = parallel_accumulate(vi.begin(), vi.end(), 5);
    cout << "sum = " << sum << endl;

    std::vector<double> vd;
    for (int i = 0; i < 10; i++) {
        vd.push_back(1.1 * i);
    }
    double sum_double = parallel_accumulate(vd.begin(), vd.end(), 5.0);
    cout << "sum_double = " << sum_double << endl;
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    if (length == 0) {
        return init;
    }

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;  // 其实就是向上取整
    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = std::min(hardware_threads > 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);  // 因为还有一个主线程
    Iterator block_start = first;
    for (unsigned long i = 0; i < num_threads-1; i++) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads-1]);  // 剩下还有一部分

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}