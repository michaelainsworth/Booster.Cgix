#ifndef BOOSTER_CGIX_PERCENT_CODER_HPP_INCLUDED
#define BOOSTER_CGIX_PERCENT_CODER_HPP_INCLUDED

#include <system_error>
#include <iterator>
#include <booster/cgix/hex_coder.hpp>
#include <booster/cgix/error.hpp>
#include <iostream>

namespace booster
{
    namespace cgix
    {
        
        // =====================================================================
        // Class: percent_coder
        // =====================================================================
        
        // Encodes and decodes strings according to percent encoding rules
        // (RFC3986). Percent encoding is also known as URL encoding.
        
        class percent_coder {
        public:
            
            // Returns whether the character is reserved.
            bool is_reserved(char c);
            
            // Returns whether the character is unreserved.
            bool is_unreserved(char c);
            
            // Returns whether the character is unsafe.
            bool is_unsafe(const unsigned char& c);
            
            // Returns whether s is a percent-encoded string. Any reserved or
            // unsafe characters present will return false. Otherwise true. In this sense,
            // isEncoded performs a strict check. If allosPlus is true, a plus found
            // will be ignore, even though it is reserved.
            bool is_encoded(const std::string& s, bool allowPlus = true);
            
            // Encodes all reserved and unsafe characters in the string.
            // If usePlus is true, this method will not encode the <space> character,
            // but will rather replace it with a "+" character.
            std::string encode(const std::string& unencoded, bool use_plus = true);
            
            // Decodes all percent encoded values back into characters.
            std::string decode(const std::string& encoded, bool allow_plus = true);
            
            // This is the generic
            template<typename InputIterator, typename OutputIterator>
            void encode(InputIterator it, InputIterator end, OutputIterator back_inserter, bool use_plus);
            
            template<typename InputIterator, typename OutputIterator>
            std::error_condition decode(InputIterator it, InputIterator end, OutputIterator back_inserter, bool allow_plus);
            
        };
        
        template<typename InputIterator, typename OutputIterator>
        void percent_coder::encode(InputIterator it, InputIterator end, OutputIterator back_inserter, bool use_plus) {
            
            hex_coder he;
            std::string hex;
            
            while (it != end) {
                char c = *it;
                
                if (' ' == c && use_plus) {
                    *back_inserter = '+';
                    ++back_inserter;
                } else if (is_reserved(c) || is_unsafe(c)) {
                    if (' ' == c && use_plus) {
                        *back_inserter = '+';
                        ++back_inserter;
                    } else {
                        *back_inserter = '%';
                        ++back_inserter;
                        
                        hex = he.to_hex(c);
                        for (std::string::size_type i = 0, s = hex.length(); i < s; ++i) {
                            *back_inserter = hex[i];
                            ++back_inserter;
                        }
                    }
                } else {
                    *back_inserter = c;
                    ++back_inserter;
                }
                
                ++it;
            }
        }
        
        template<typename InputIterator, typename OutputIterator>
        std::error_condition percent_coder::decode(InputIterator it, InputIterator end, OutputIterator back_inserter, bool allow_plus) {
            
            hex_coder he;
            std::error_condition e;
            
            while (it != end) {
                char c = *it;
                if ('+' == c && allow_plus) {
                    *back_inserter = ' ';
                    ++back_inserter;
                } else if (c == '%') {
                    typename std::iterator_traits<InputIterator>
                        ::difference_type i = std::distance(it, end);
                    
                    if (i < 2) {
                        return error::percent_sequence_invalid;
                    }
                    
                    InputIterator it1 = it, it2 = it;
                    ++it1;
                    ++it2;
                    ++it2;
                    
                    if (!he.is_hex(*it1) || !he.is_hex(*it2)) {
                        return error::percent_sequence_invalid;
                    }
                    
                    std::string hex_chars;
                    hex_chars += *it1;
                    hex_chars += *it2;
                    
                    e = he.to_char(hex_chars, c);
                    if (e) {
                        return e;
                    }
                    
                    *back_inserter = c;
                    ++back_inserter;
                    
                    ++it;
                    ++it;
                } else {
                    *back_inserter = c;
                    ++back_inserter;
                }
                
                ++it;
            }
            
            return error::ok;
        }
        
    }
}

#endif // BOOSTER_CGIX_PERCENT_CODER_HPP_INCLUDED
