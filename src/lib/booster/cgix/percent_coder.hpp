#ifndef BOOSTER_CGIX_PERCENT_CODER_HPP_INCLUDED
#define BOOSTER_CGIX_PERCENT_CODER_HPP_INCLUDED

#include <system_error>

namespace booster
{
    namespace cgix
    {
        
        // TODO: The decode() and encode() functions should also work on streams.
        
        /**
         * @brief Encodes and decodes strings according to percent encoding rules (RFC3986).
         *
         * Percent encoding is also known as URL encoding.
         */
        class percent_coder {
        public:
            
            /**
             * @brief Returns whether the character is reserved.
             */
            bool is_reserved(char c);
            
            /**
             * @brief Returns whether the character is unreserved.
             */
            bool is_unreserved(char c);
            
            /**
             * @brief Returns whether the character is unsafe.
             */
            bool is_unsafe(const unsigned char& c);
            
            /**
             * @brief Returns whether s is a percent-encoded string. Any reserved or
             * unsafe characters present will return false. Otherwise true. In this sense,
             * isEncoded performs a strict check. If allosPlus is true, a plus found
             * will be ignore, even though it is reserved.
             */
            bool is_encoded(const std::string& s, bool allowPlus = true);
            
            /**
             * @brief Encodes all reserved and unsafe characters in the string.
             *
             * If usePlus is true, this method will not encode the <space> character,
             * but will rather replace it with a "+" character.
             */
            std::string encode(const std::string& s, bool use_plus = true);
            
            
            /**
             * @brief Decodes all percent encoded values back into characters.
             */
            std::error_condition decode(std::string& output, const std::string& s, bool use_plus = true);
            
        };
        
    }
}

#endif // BOOSTER_CGIX_PERCENT_CODER_HPP_INCLUDED
