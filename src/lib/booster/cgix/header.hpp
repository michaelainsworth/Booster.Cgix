#ifndef BOOSTER_CGIX_HEADER_HPP_INCLUDED
#define BOOSTER_CGIX_HEADER_HPP_INCLUDED

#include <cstddef>
#include <string>
#include <booster/cgix/error.hpp>
#include <booster/cgix/ci_string.hpp>

namespace booster
{
    namespace cgix
    {
        
        // =====================================================================
        // Class: header
        // =====================================================================
        
        // The header class encapsulates HTTP headers.
        //
        // The header class can be used to send HTTP headers to the web server
        // (finally to the web browser) via the response class.
        //
        // It provides convenience functions for creating headers (e.g.,
        // header::content_type("application/json").
        
        class header {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::basic_string<char, ci_char_traits> name_string_type;
            typedef std::string value_string_type;
            
            // -----------------------------------------------------------------
            // Utility
            // -----------------------------------------------------------------
            
            // The functions below are used in parsing headers.
            
            static bool is_char(char c);
            static bool is_ctl(char c);
            static bool is_separator(char c);
            static bool is_sp(char c);
            static bool is_ht(char c);
            static bool is_token(char c);
            static bool is_text(const char *c, size_t length);
            
            // Returns 0 for no LWS or >0 for the no. of LWS characters to replace with a space.
            static std::size_t lws_length(const char *c, size_t length);
            static std::size_t is_reverse_lws(const char *c, size_t length);
            static std::error_condition from_string(header& h, const value_string_type& header_string);
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            header(const name_string_type& name, const value_string_type& value);
            
            // -----------------------------------------------------------------
            // Accessors
            // -----------------------------------------------------------------
            
            // Returns the name of the header, e.g., "content-type".
            //
            // This is returned as a case-insensitive string. This means you can
            // compare headers more easily. E.g.:
            //
            //    if (h.name() == "content-type") { ... }
            
            const name_string_type& name() const;
            
            // Returns the value of the header.
            //
            // Note that while HTTP header names are case insensitive, HTTP
            // header values are not necessarily case sensitive, hence this
            // function returning a regular std::string.
            
            const value_string_type& value() const;
            
            // The conversion operator to the string type creates a
            // fully-formed HTTP header. E.g.:
            //
            //    content-type: application/json
            //
            // This allows it to be used internally by the response classes
            // in sending the final header to the web browser.
            
            operator value_string_type() const;
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
        private:
            
            name_string_type name_;
            value_string_type value_;
            
            // =================================================================
            // Factory functions
            // =================================================================
            
            // The functions below are used as a convenience method of creating
            // HTTP headers. E.g., instead of:
            //
            //    resp << header("content-type", "application/json");
            //
            // You can use:
            //
            //    resp << header::content_type("application/json");
            //
            // Using such convenience functions will likely reduce the number
            // of typos.
            
        public:

            // -----------------------------------------------------------------
            // Entity headers
            // -----------------------------------------------------------------
            
            static header allow(const value_string_type& value);
            
            static header content_encoding(const value_string_type& value);
            
            static header content_language(const value_string_type& value);
            
            static header content_length(const value_string_type& value);
            
            static header content_location(const value_string_type& value);
            
            static header content_md5(const value_string_type& value);
            
            static header content_range(const value_string_type& value);
            
            static header content_type(const value_string_type& value);
            
            static header expires(const value_string_type& value);
            
            static header last_modified(const value_string_type& value);
            

            // -----------------------------------------------------------------
            // General headers
            // -----------------------------------------------------------------
            
            static header connection(const value_string_type& value);
            
            static header date(const value_string_type& value);
            
            static header pragma(const value_string_type& value);
            
            static header trailer(const value_string_type& value);
            
            static header transfer_encoding(const value_string_type& value);
            
            static header upgrade(const value_string_type& value);
            
            static header via(const value_string_type& value);
            
            static header warning(const value_string_type& value);
            
            // -----------------------------------------------------------------
            // Request headers
            // -----------------------------------------------------------------
            
            static header accept(const value_string_type& value);
            
            static header accept_charset(const value_string_type& value);
            
            static header accept_encoding(const value_string_type& value);
            
            static header accept_language(const value_string_type& value);
            
            static header authorization(const value_string_type& value);
            
            static header cache_control(const value_string_type& value);
            
            static header expect(const value_string_type& value);
            
            static header from(const value_string_type& value);
            
            static header host(const value_string_type& value);
            
            static header if_match(const value_string_type& value);
            
            static header if_modified_since(const value_string_type& value);
            
            static header if_none_match(const value_string_type& value);
            
            static header if_range(const value_string_type& value);
            
            static header if_unmodified_since(const value_string_type& value);
            
            static header max_forwards(const value_string_type& value);
            
            static header proxy_authorization(const value_string_type& value);
            
            static header range(const value_string_type& value);
            
            static header referer(const value_string_type& value);
            
            static header te(const value_string_type& value);
            
            static header user_agent(const value_string_type& value);
            
            // -----------------------------------------------------------------
            // Response headers
            // -----------------------------------------------------------------
            
            static header accept_ranges(const value_string_type& value);
            
            static header age(const value_string_type& value);
            
            static header etag(const value_string_type& value);
            
            static header location(const value_string_type& value);
            
            static header proxy_authenticate(const value_string_type& value);
            
            static header retry_after(const value_string_type& value);
            
            static header server(const value_string_type& value);
            
            static header vary(const value_string_type& value);
            
            static header www_authenticate(const value_string_type& value);
            
        };

    }
}

#endif // BOOSTER_CGIX_HEADER_HPP_INCLUDED
