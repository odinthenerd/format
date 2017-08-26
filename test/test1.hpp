#include "../src/kvasir/format/format.hpp"

namespace test1{
    using namespace kvasir;

    template<typename T>
    struct test_make_upper{
        void test(){
            optional(this,abcd::ability<format::detail::make_upper>,[](auto&){},[]{});
        }
    };

    using ot = abcd::wrap_trivial_public_interface<test_make_upper>;

    int run() {
        auto fmt1 = abcd::combine(format::pair_char_range{}, format::to_upper_EN{});
        char c[] = "sdfg";
        fmt1.process(std::make_pair(std::begin(c),std::end(c)));

        auto fmt2 = abcd::combine(ot{}, format::to_upper_EN{});
        fmt2.test();

        auto fmt3 = abcd::combine(ot{});
        fmt3.test();

        return 0;
    }
}