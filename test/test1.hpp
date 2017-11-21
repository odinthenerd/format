#include "../src/kvasir/format/format.hpp"
#include <type_traits>
#include <functional>
#include <map>


#include <tuple>

auto t = std::tuple<int,bool,bool,bool>{};

struct tuple_end{};

auto p = std::map<tuple_end,int>{};


template<std::size_t N, bool empty, typename E, typename B>
struct tuple_element : B {
    E element;
    template<typename T, typename...Ts>
    tuple_element(T e, Ts...args) : B{args...}, element{e}{};
    E& get(){
        return element;
    }
};

template<std::size_t N, typename E, typename B>
struct tuple_element<N,true,B,E> : B{
    template<typename T, typename...Ts>
    tuple_element(T e, Ts...args) : B{args...}{};
    E get(){
        return E{};
    }
};

template<typename T>
constexpr bool is_empty = false;

template<bool B>
struct make_bases {  //break recursion
    template<std::size_t N, bool empty, typename E, typename...Ts>
    using f = tuple_element<N,empty,E,tuple_end>;
};

template<typename T, typename U>
int f1(T&& arg1, U&& arg2){
    return *arg1 - *arg2;
}

template<typename T, typename U>
int f2(T&& arg1,U&& arg2){
    void* p[] = {static_cast<void*>(&arg1),static_cast<void*>(&arg2)};
    return f1(std::forward<U>(*static_cast<U*>(p[1])),std::forward<T>(*static_cast<T*>(p[0])));
}

template<>
struct make_bases<true> {
//    template<std::size_t N, bool empty, typename E, typename T, typename...Ts>
//    using f = tuple_element<N,empty,E,typename make_base<(sizeof...(Ts)>1)>::template f<N+1,is_empty<T>,T,Ts...>>;
};

template<typename T1, typename T2, typename T3>
struct tuple : tuple_element<0,true,T1,tuple_element<1,false,T1,tuple_element<2,true,T1,tuple_end>>>{
    template<typename...Ts>
    tuple(Ts...args):tuple_element<0,true,T1,tuple_element<1,false,T1,tuple_element<2,true,T1,tuple_end>>>(args...){}
};
 
template<std::size_t N>
struct geter{
    template<bool empty, typename E, typename B>
    tuple_element<N,empty,B,E>* get(tuple_element<N,empty,B,E>* in){
        return in;
    }
};

template<std::size_t N, typename T>
auto get(T& t){
    static_cast<decltype(geter<N>::template get(&t))>(&t)->get();
}


template<typename Abilities, typename N, typename A>
struct arena_t{
    std::aligned_storage_t<N::value,A::value> data;
};

struct allocation_t{};

template<std::size_t N, std::size_t A>
constexpr arena_t<allocation_t,::kvasir::mpl::int_<N>,::kvasir::mpl::int_<A>> arena;

namespace test1{
    using namespace kvasir;

    template<typename B>
    struct test_make_upper : B{
        void test(){
            B::optional(abcd::ability<format::detail::make_upper>,[](auto&){},[]{});
        }
    };



    using ot = abcd::wrap_trivial_public_interface<test_make_upper>;

    int run() {
        auto fmt1 = abcd::combine(format::pair_char_range{}, format::to_upper_EN{});
        char c[] = "sdfg";
        fmt1.process(std::make_pair(std::begin(c),std::end(c)));

        auto fmt2 = abcd::combine(abcd::interface<test_make_upper>, format::to_upper_EN{});
        fmt2.test();

        auto fmt3 = abcd::combine(abcd::interface<test_make_upper>);
        fmt3.test();

        return 0;
    }
}