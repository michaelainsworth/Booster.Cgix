#include <booster/cgix/percent_coder.hpp>
#include <booster/cgix/hex_coder.hpp>
#include <booster/cgix/error.hpp>

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
        
        std::string percent_coder::encode(const std::string& unencoded, bool use_plus) {
            std::string encoded;
            encode(unencoded.begin(), unencoded.end(), std::back_inserter(encoded), use_plus);
            return encoded;
        }
        
        std::string percent_coder::decode(const std::string& encoded, bool allow_plus) {
            std::string decoded;
            std::error_condition e;
            e = decode(encoded.begin(), encoded.end(), std::back_inserter(decoded), allow_plus);
            if (e) {
                throw std::system_error(e.value(), e.category());
            }
            return decoded;
        }
        
    }
}
