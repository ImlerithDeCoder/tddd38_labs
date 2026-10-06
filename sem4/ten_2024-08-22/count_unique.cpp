#include <type_traits>

template <typename... Ts>
struct Pack
{
    static constexpr std::size_t size = sizeof...(Ts);
};

template <typename... Ts>
struct Count_Unique {
    static constexpr std::size_t value = 0;
};

template <typename First, typename... Rest>
struct Count_Unique<First, Rest...>
{
    static constexpr bool duplicate = (std::is_same_v<First, Rest> || ...);
    
    // uses the struct itself recursively
    static constexpr std::size_t value = duplicate ? Count_Unique<Rest...>::value : 1 + Count_Unique<Rest...>::value;
};



int main()
{
    static_assert( Count_Unique<>::value == 0 );
    static_assert( Count_Unique<int, int, int>::value == 1 );
    static_assert( Count_Unique<int, float, int, bool>::value == 3 );
    static_assert( Count_Unique<int, int, int, float>::value == 2 );
    static_assert( Count_Unique<float, int, int, int>::value == 2 );
}