#ifndef BOOSTER_CGIX_COOKIE_HPP_INCLUDED
#define BOOSTER_CGIX_COOKIE_HPP_INCLUDED

#include <string>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: cookie
        // =====================================================================
        
        // The cookie class represents cookies sent from the application to the
        // web server (via the "Set-Cookie" HTTP header).
        //
        // Note that cookies must have a name and a value, but can also have:
        //
        // - A duration in seconds. If the web browser does not send a request
        //   before this time frame expires, the browser will not send the cookie
        //   upon the next request.
        // - A secure flag. If this is set, the cookie will only be sent back
        //   to the web server when an HTTPS secured connection is used.
        // - The domain on which the cookie should be used.
        // - The path on which the cookie should be used (defaults to "/").
        //
        // Note that cookies sent from the web server (originally, the web
        // browser) to the application simply provide cookies as strings. The
        // cookie class is not used for incoming cookies, only outgoing cookies.
        
        class cookie {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef unsigned long long duration;
            typedef std::string string_type;
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            // The various constructors for the cookie class creates the cookie
            // with the required name and value properties, or with the
            // additional optional properties.
            
            cookie(const string_type& name, const string_type& value);
            cookie(const string_type& name, const string_type& value, duration seconds);
            cookie(const string_type& name, const string_type& value, bool secure, bool http_only, duration seconds);
            cookie(const string_type& name, const string_type& value, const string_type& domain, const string_type& path, bool secure, bool http_only, duration seconds);
            
            // -----------------------------------------------------------------
            // Accessors
            // -----------------------------------------------------------------
            
            const string_type& name() const;
            const string_type& value() const;
            const string_type& domain() const;
            const string_type& path() const;
            duration seconds() const;
            bool is_secure() const;
            bool is_http_only() const;
            operator string_type() const;
            
        private:
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
            string_type name_;
            string_type value_;
            string_type domain_;
            string_type path_;
            bool secure_;
            bool http_only_;
            duration seconds_;
            
        };
        
        
    }
}

#endif // BOOSTER_CGIX_COOKIE_HPP_INCLUDED
