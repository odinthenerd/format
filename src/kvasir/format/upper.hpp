#pragma once
#include <kvasir/abcd/abcd.hpp>

namespace kvasir {
    namespace format {
        template<char B, char E, char O>
        struct char_replace{
            template<typename>
                    using f = void; //no public interface
            constexpr operator()(char c){
                return (c>=B && c<=E)? c-(B-O):c;
            }
        };

        namespace detail{
            template<typename T>
            struct pair_range_public{

            };
        }
        using pair_range = abcd::wrap_trival_public_interface<detail::pair_range_public>;
    }
}