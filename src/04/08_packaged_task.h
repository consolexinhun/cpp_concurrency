#include <string>
#include <vector>
#include <future>

template<>
class packaged_task<std::string(std::vector<char>*, int)> {
public:
    template<typename Callable>
    explicit packaged_task(Callable&& f);

    std::future<std::string> get_future();

    void operator() (std::vector<char>*, int);
};

/* 这一段代码不完整，编辑器会提示错误 */
