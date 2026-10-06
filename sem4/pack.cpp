#include <type_traits>
#include <cassert>

template <typename... Ts>
class Pack {};

template <typename T, typename First, typename... Ts>
bool contains(Pack<First, Ts...> pack) {
    return std::is_same_v<T, First> || contains<T>(Pack<Ts...>{});
}

template <typename T>
bool contains(Pack<>) {
    return false;
}


template <typename T, typename... Ts>
int index_of(Pack<Ts...> pack) {
    return contains<T>(pack) ? index_of_helper<T>(pack) : -1;
}

template <typename T, typename First, typename... Ts>
int index_of_helper(Pack<First, Ts...> pack) {
    return std::is_same_v<T, First> ? 0 : 1 + index_of<T>(Pack<Ts...>{});
}

template <typename T>
int index_of(Pack<>) {
    return -1;
}

int main() {
    Pack<int, float, char> pack{};
    assert(contains<int>(pack) == true);
    assert(contains<bool>(pack) == false);
    assert(index_of<int>(pack) == 0);
    assert(index_of<char>(pack) == 2);
    assert(index_of<bool>(pack) == -1);
}