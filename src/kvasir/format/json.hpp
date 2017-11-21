#pragma once
#include "kvasir/abcd/abcd.hpp"
#include <utility>
#include <kvasir/mpl/mpl.hpp>

namespace kvasir {
    namespace format {
		namespace json {
			struct output_field{};
			template<typename T, T M>
			struct number_field {
				constexpr char* _name;
				char* operator()(char* it) {
					auto n = _name;
					*it++ = '"';
					while (*n != '\0') {
						*it++ = *n++;
					}
					for (const char c:{'"',':','"'}) {
						*it++ = c;
					}

					*it++ = '"';
				}
			};
		}
    }
	namespace abcd{
		template<typename T, T M>
		struct has_ability<format::json::number_field<T,M>,format::json::output_field> : mpl::true_{};
	}
}