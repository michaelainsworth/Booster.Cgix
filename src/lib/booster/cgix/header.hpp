#ifndef BOOSTER_CGIX_HEADER_HPP_INCLUDED
#define BOOSTER_CGIX_HEADER_HPP_INCLUDED

#include <cstddef>
#include <string>
#include <booster/cgix/error_condition.hpp>

namespace booster
{
    namespace cgix
    {
        
        class header {
        public:
            
            // Utility
            static bool is_char(char c);
            static bool is_ctl(char c);
            static bool is_separator(char c);
            static bool is_sp(char c);
            static bool is_ht(char c);
            static bool is_token(char c);
            static bool is_text(const char *c, size_t length);
            
            // Returns 0 for no LWS or >0 for the no. of LWS characters to replace with a space.
            static std::size_t is_lws(const char *c, size_t length);
            static std::size_t is_reverse_lws(const char *c, size_t length);
            static std::error_condition from_string(header& h, const std::string& header_string);
            
            // Lifecycle
            header(const std::string& name, const std::string& value);
            
            // Accessors
            const std::string& name() const;
            const std::string& value() const;
            
            // Conversion
            operator std::string() const;
            
        private:
            
            std::string name_;
            std::string value_;
            
        };
        
        // Entity headers
        header allow(const std::string& value);
        
        header content_encoding(const std::string& value);
        
        header content_language(const std::string& value);
        
        header content_length(const std::string& value);
        
        header content_location(const std::string& value);
        
        header content_md5(const std::string& value);
        
        header content_range(const std::string& value);
        
        header content_type(const std::string& value);
        
        header expires(const std::string& value);
        
        header last_modified(const std::string& value);
        
        
        // General headers
        header connection(const std::string& value);
        
        header date(const std::string& value);
        
        header pragma(const std::string& value);
        
        header trailer(const std::string& value);
        
        header transfer_encoding(const std::string& value);
        
        header upgrade(const std::string& value);
        
        header via(const std::string& value);
        
        header warning(const std::string& value);
        
        
        // Request headers
        header accept(const std::string& value);
        
        header accept_charset(const std::string& value);
        
        header accept_encoding(const std::string& value);
        
        header accept_language(const std::string& value);
        
        header authorization(const std::string& value);
        
        header cache_control(const std::string& value);
        
        header expect(const std::string& value);
        
        header from(const std::string& value);
        
        header host(const std::string& value);
        
        header if_match(const std::string& value);
        
        header if_modified_since(const std::string& value);
        
        header if_none_match(const std::string& value);
        
        header if_range(const std::string& value);
        
        header if_unmodified_since(const std::string& value);
        
        header max_forwards(const std::string& value);
        
        header proxy_authorization(const std::string& value);
        
        header range(const std::string& value);
        
        header referer(const std::string& value);
        
        header te(const std::string& value);
        
        header user_agent(const std::string& value);
        
        
        // Response headers
        header accept_ranges(const std::string& value);
        
        header age(const std::string& value);
        
        header etag(const std::string& value);
        
        header location(const std::string& value);
        
        header proxy_authenticate(const std::string& value);
        
        header retry_after(const std::string& value);
        
        header server(const std::string& value);
        
        header vary(const std::string& value);
        
        header www_authenticate(const std::string& value);
        
    }
}

#endif // BOOSTER_CGIX_HEADER_HPP_INCLUDED
