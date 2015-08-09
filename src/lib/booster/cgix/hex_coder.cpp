#include <booster/cgix/hex_coder.hpp>
#include <booster/cgix/error.hpp>
#include <sstream>

namespace booster
{
    namespace cgix
    {
        
        bool hex_coder::is_hex(char c) {
            return char_category::not_hex != get_char_category(c);
        }
        
        hex_coder::char_category hex_coder::get_char_category(char c) {
            if (c >= '0' && c <= '9') return char_category::digit;
            if (c >= 'a' && c <= 'f') return char_category::alpha_lower;
            if (c >= 'A' && c <= 'F') return char_category::alpha_upper;
            return char_category::not_hex;
        }
        
        std::string hex_coder::to_hex(char c, const std::string& prefix) {
            std::stringstream ss;
            ss.flags(std::ios::hex);
            ss.fill('0');
            ss.width(2);
            ss << std::uppercase << static_cast<int>(c);
            
            return prefix + ss.str();
        }
        
        std::error_condition hex_coder::to_char(const std::string& s, char& c) {
            std::string::size_type i = 0, l = s.size();
            if (2 > l) {
                return error::hex_sequence_too_short;
            }
            
            char cs[] { 0, 0, 0 };
            for (; i < l && i < 2; ++i) {
                cs[i] = s[i];
                switch (get_char_category(cs[i])) {
                    case char_category::digit:
                        cs[i] = cs[i] - 48;
                        break;
                    case char_category::alpha_lower:
                        cs[i] = cs[i] - 87;
                        break;
                    case char_category::alpha_upper:
                        cs[i] = cs[i] - 55;
                        break;
                    case char_category::not_hex:
                    default:
                        return error::hex_character_invalid;
                }
            }
            
            cs[0] = cs[0] << 4;
            c = cs[0] + cs[1];
            
            return error::ok;
        }
        
    }
}

