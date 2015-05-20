#ifndef BOOSTER_CGIX_HEX_CODER_HPP_INCLUDED
#define BOOSTER_CGIX_HEX_CODER_HPP_INCLUDED

#include <system_error>
#include <string>

namespace booster
{
    namespace cgix
    {
        
        class hex_coder {
        public:
            
            enum class char_category
            {
                not_hex,
                alpha_lower,
                alpha_upper,
                digit
            };
            
            bool is_hex(char c);
            std::string to_hex(char c, const std::string& prefix = "");
            std::error_condition to_char(const std::string& s, char& c);
            char_category get_char_category(char c);
            
        };
        
        
    }
}

#endif // BOOSTER_CGIX_HEX_CODER_HPP_INCLUDED
