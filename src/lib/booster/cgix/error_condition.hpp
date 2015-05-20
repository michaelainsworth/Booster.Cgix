#ifndef BOOSTER_CGIX_ERROR_CONDITION_HPP_INCLUDED
#define BOOSTER_CGIX_ERROR_CONDITION_HPP_INCLUDED

#include <system_error>
#include <string>

namespace booster {
    namespace cgix {
        
        // TODO: Rename this file to just error.{hpp,cpp}
        
        class error_category;
        
        enum class error {
            ok = 0,
            hex_sequence_too_short,
            hex_character_invalid,
            percent_sequence_invalid,
            cookie_string_end_unexpected,
            cookie_string_quote_end_unexpected,
            cookie_string_pair_separator_invalid,
            cookie_string_char_unexpected,
            http_header_malformed,
            http_header_not_set,
            http_headers_already_sent
        };
        
        const error_category& get_error_category();
        
        std::error_code make_error_code(error e);
        std::error_condition make_error_condition(error e);
        
        class error_category : public std::error_category {
        public:
            
            const char* name() const noexcept(true);
            std::string message(int ev) const noexcept(true);
            
        };
        
    }
}

namespace std {
    
    template<> struct is_error_code_enum<booster::cgix::error> : public std::true_type {};
    template<> struct is_error_condition_enum<booster::cgix::error> : public std::true_type {};
    
}

#endif // #ifndef BOOSTER_CGIX_ERROR_CONDITION_HPP_INCLUDED

