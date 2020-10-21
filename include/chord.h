#include <vector>
#include <string>
#include <tuple>
#include <boost/hana.hpp>

namespace absinthe {

template <class... Ts>
class progression {};

class natural {};
class sharp {};
class flat {};

template <int Height>
class tone : public std::integral_constant<int, Height>
{};


using C = tone<0>;
using Csharp = tone<1>;
using D = tone<2>;
using Dsharp = tone<3>;
using E = tone<4>;
using F = tone<5>;
using Fsharp = tone<6>;
using G = tone<7>;
using Gsharp = tone<8>;
using A = tone<9>;
using Asharp = tone<10>;
using B = tone<11>;

template <class Tone, unsigned N>
class move_tone_forward
{
public:
    using type = tone<(Tone::value + N) % 12>;
};

template <class Tone, unsigned N>
using move_tone_forward_t = move_tone_forward<Tone, N>::type;

template<int N>
class interval : public std::integral_constant<int, N> {};

template <class... Intervals>
class abstract_scale {
public:
    static constexpr long long unsigned size = sizeof...(Intervals);
    using intervals = std::tuple<Intervals...>;
};

template <size_t Index, class Container, class Head, class... Tail>
class intervals_sum;

template <size_t Index, class Head, class Tail1, class... Tails, class... ContainerType>
class intervals_sum<Index, std::tuple<ContainerType...>, Head, Tail1, Tails...> {
public:
    using type = intervals_sum<Index + 1, std::tuple<ContainerType..., interval<std::tuple_element_t<Index, std::tuple<ContainerType...>>::value + Tail1::value>>, Tail1, Tails...>::type;
};

template <size_t Index, class Head, class Tail,  class... ContainerType>
class intervals_sum<Index, std::tuple<ContainerType...>, Head, Tail> {
public:
    using type = std::tuple<ContainerType..., interval<std::tuple_element_t<Index, std::tuple<ContainerType...>>::value + Tail::value>>;
};

template <size_t Index, class Container, class Head, class... Tail>
using intervals_sum_t = intervals_sum<Index, Container, Head, Tail...>::type;

template <class Intervals>
class replace_intervals_to_tones;

template <template<class...> class T, class... Ts>
class replace_intervals_to_tones<T<Ts...>> {
public:
    using type = T<tone<Ts::value>...>;
};

template <class Tone, class Intervals>
class move_multiple_tones_forward;

template <class Tone, template<class...> class T, class... Ts>
class move_multiple_tones_forward<Tone, T<Ts...>> {
public:
    using type = T<move_tone_forward_t<Tone, Ts::value>...>;
};

template <class Head, class Tup>
class append_target;

template <class Head, template <class...> class Tup, class... Ts>
class append_target<Head, Tup<Ts...>> {
public:
    using type = Tup<Head, Ts...>;
};

template <class Tup, class Head>
using append_target_t = append_target<Tup, Head>::type;

template <class Tone, class Intervals>
using move_multiple_tones_forward_t = move_multiple_tones_forward<Tone, Intervals>::type;

template <class Tone, class AbstractScale>
class make_scale_on_tone;

template <class Tone, class Interval, class... Intervals>
class make_scale_on_tone<Tone, abstract_scale<Interval, Intervals...>> {
public:
    using type = append_target_t<Tone, move_multiple_tones_forward_t<Tone, intervals_sum_t<0, std::tuple<Interval>, Interval, Intervals...>>>;
};

using major_scale = abstract_scale<interval<2>, interval<2>, interval<1>, interval<2>, interval<2>, interval<2>, interval<1>>;



template <class... Intervals>
class chord {
public:
    static constexpr long long unsigned size = sizeof...(Intervals);
    using intervals = std::tuple<Intervals...>;
};

using major_triad = chord<interval<0>, interval<4>, interval<7>>;
using minor_triad = chord<interval<0>, interval<3>, interval<7>>;


} // absinthe