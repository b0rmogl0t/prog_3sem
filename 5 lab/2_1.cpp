#include <iostream>
#include <tuple>


template<int n = 0, typename Func, class... argsT>
void apply(std::tuple<argsT...>& t, Func f) {
    if constexpr (n < sizeof... (argsT)) {
        f(std::get<n>(t));
        apply<n+1, Func, argsT...>(t, f);
    }
}


int main() {
    std::tuple<int, double, long long, char> t(1, 3.14, 10000203, 'a');

    std::cout << "Printing tuple:" << std::endl;

    apply(t, [](const auto& val) {
        std::cout << val << std::endl;
    });

    std::cout << std::endl;

    std::cout << "+= 1 all elements of tuple." << std::endl;

    apply(t, [](auto& val){
        val += 1;
    });

    std::cout << std::endl;

    std::cout << "Printing tuple:" << std::endl;
    apply(t, [](const auto& val) {
        std::cout << val << std::endl;
    });

    return 0;
}