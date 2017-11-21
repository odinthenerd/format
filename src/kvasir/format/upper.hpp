#pragma once
#include "kvasir/abcd/abcd.hpp"
#include <utility>

namespace kvasir {
    namespace format {
        template<typename Abilities, char B, char E, char O>
        struct char_replace{
            template<typename>
            using f = void; //no public interface
			constexpr char operator()(const char c){
				return (c>=B && c<=E)? c-(B-O):c;
			}
			template<typename It>
			std::pair<It,bool> operator()(const char c, It begin, It end){
				if (c>=B && c<=E){
					*begin++ = c-(B-O);
					return {begin, true};
				}
				return {begin, false};
			}
        };

		namespace detail{
			struct make_upper{};
			template<typename B>
			struct pair_char_range_public : B{
				std::pair<char*, char*> process(std::pair<char*, char*> in) {
					using namespace kvasir::abcd;
					auto it = in.first;
					for (; it < in.second; it++) {
						B::for_each(ability<make_upper>, [&](auto& a) {*it = a(*it); });
					}
					return { it,in.second };
				}
			};
		}

		using to_upper_EN = char_replace<abcd::abilities_t<format::detail::make_upper>,'a', 'z', 'A'>;


        using pair_char_range = ::kvasir::abcd::interface_t<detail::pair_char_range_public>;
    }
}