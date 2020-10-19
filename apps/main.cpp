#include <type_traits>
#include <iostream>

#include "chord.h"

int main() {
    using namespace absinthe;
    static_assert(std::is_same_v<absinthe::move_tone_forward<absinthe::tone<3>, 5>::type, absinthe::tone<8>>);
    /*
    static_assert(std::is_same_v<
        decltype(absinthe::make_scale_on_tone<absinthe::tone<0>, absinthe::major_scale>{}())
        , std::tuple<C, D, E, F, G, A, B, C>>);
    */
    
    // static_assert(std::is_same_v<
    //     absinthe::intervals_sum<std::tuple<>, interval<2>, interval<2>, interval<1>, interval<2>, interval<2>, interval<2>, interval<1>>::type,
    //     std::tuple<interval<2>, interval<4>, interval<5>, interval<7>, interval<9>, interval<11>, interval<12>>
    // >);
 //   std::apply([](auto... ts){ ((std::cout << ts << "\n"), ...) << std::endl;}, intervals_sum<0, std::tuple<interval<2>>, interval<2>, interval<2>, interval<1>, interval<2>, interval<2>, interval<2>, interval<1>>::type{});

    std::apply([](auto... ts){ ((std::cout << ts << "\n"), ...) << std::endl;}, absinthe::make_scale_on_tone<absinthe::tone<3>, absinthe::major_scale>{}());

}