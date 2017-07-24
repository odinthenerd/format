#pragma once
#include "../../../abcd/src/kvasir/abcd/abcd.hpp"
#include <utility>

namespace kvasir {
    namespace format {
        template<char B, char E, char O>
        struct char_replace{
            template<typename>
            using f = void; //no public interface
            constexpr char operator()(char c){
                return (c>=B && c<=E)? c-(B-O):c;
            }
        };

		using to_upper_EN = char_replace<'a', 'z', 'A'>;

        namespace detail{
			struct make_upper{};
            template<typename T>
            struct pair_char_range_public{
				std::pair<char*, char*> process(std::pair<char*, char*> in) {
					using namespace kvasir::abcd;
					auto it = in.first;
					for (; it < in.second; it++) {
						for_each(access<T>(this), capability_t<make_upper>{}, [&](auto& a) {*it = a(*it); });
					}
					return { it,in.second };
				}
            };
        }
        using pair_char_range = ::kvasir::abcd::wrap_trivial_public_interface<detail::pair_char_range_public>;
    }
	namespace abcd {
		template<char B, char E, char D>
		struct has_capability<format::char_replace<B, E, D>, format::detail::make_upper> :std::true_type {};
	}
}