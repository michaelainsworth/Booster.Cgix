#include <booster/cgix/percent_coder.hpp>
#include <booster/cgix/hex_coder.hpp>
#include <booster/cgix/error_condition.hpp>

namespace booster {
    
    namespace cgix {
        
        bool percent_coder::is_reserved(char c) {
            static std::string reserved("!*'();:@&=+$,/?#[]");
            return reserved.find(c) != std::string::npos;
        }
        
        bool percent_coder::is_unreserved(char c) {
            static std::string unreserved("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~");
            return unreserved.find(c) != std::string::npos;
        }
        
        bool percent_coder::is_unsafe(const unsigned char& c) {
            static std::string unsafe(" \"<>#%{}|\\^[]`");
            return unsafe.find(c) != std::string::npos;
        }
        
        bool percent_coder::is_encoded(const std::string& s, bool allow_plus) {
            hex_coder he;
            size_t size = s.size();
            char c;
            for (size_t i = 0; i < size; ++i) {
                c = s[i];
                if (is_reserved(c)) {
                    if ('+' != c || ('+' == c && !allow_plus)) {
                        return false;
                    } // else ignore
                } else if ('%' == c) {
                    if (i >= size - 2) return false;
                    if (!he.is_hex(s[i+1]) || !he.is_hex(s[i+2])) return false;
                } else if (is_unsafe(c)) {
                    return false;
                }
            }
            
            return true;
        }
        
        std::string percent_coder::encode(const std::string& s, bool use_plus) {
            std::string ret;
            ret.reserve(s.size());
            hex_coder he;
            
            size_t size = s.size();
            unsigned char c;
            for (size_t i = 0; i < size; ++i) {
                c = s[i];
                if (' ' == c && use_plus) {
                    ret += '+';
                } else if (is_reserved(c) || is_unsafe(c)) {
                    if (use_plus && ' ' == c) {
                        ret += '+';
                    } else {
                        ret += "%";
                        ret += he.to_hex(c);
                    }
                } else {
                    ret += c;
                }
            }
            
            return ret;
        }
        
        std::error_condition percent_coder::decode(std::string& output, const std::string& s, bool use_plus) {
            hex_coder he;
            std::error_condition e;
            
            size_t size = s.size();
            char c;
            for (size_t i = 0; i < size; ++i) {
                c = s[i];
                if ('+' == c && use_plus) {
                    output += ' ';
                } else if (c == '%') {
                    bool is_encoded_char = i < size - 2 && he.is_hex(s[i + 1]) && he.is_hex(s[i + 2]);
                    if (is_encoded_char) {
                        std::string hex_char = s.substr(i+1, 2);
                        e = he.to_char(hex_char, c);
                        if (!e) {
                            return e;
                        }
                        
                        output += c;
                        i += 2;
                    } else {
                        return error::percent_sequence_invalid;
                    }
                } else {
                    output += c;
                }
            }
            
            return error::ok;
        }
        
    }
}
