#include <mutex>
#include <climits>
#include <stdexcept>

class hierarchical_mutex {
    std::mutex internal_mutex;
    uint64_t const hierarchy_value;
    uint64_t previous_hierarchy_value;

    static thread_local uint64_t this_thread_hierarchy_value;

    void check_for_hierarchy_violation() {
        if (this_thread_hierarchy_value <= hierarchy_value) {
            throw std::logic_error("mutex hierarchy vialated");
        }
    }

    void update_hierarchy_value() {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }

    void lock() {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }

    void unlock() {
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }

    bool try_lock() {
        check_for_hierarchy_violation();
        if (!internal_mutex.try_lock()) {
            return false;
        }
        update_hierarchy_value();
        return true;
    }

public:
    explicit hierarchical_mutex(uint64_t value) : hierarchy_value(value), previous_hierarchy_value(0) {}
};

thread_local uint64_t hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

int main() {
    hierarchical_mutex m1(42);
    hierarchical_mutex m2(2000);
    return 0;
}
