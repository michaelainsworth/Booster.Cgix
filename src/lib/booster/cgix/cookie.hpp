#ifndef BOOSTER_CGIX_COOKIE_HPP_INCLUDED
#define BOOSTER_CGIX_COOKIE_HPP_INCLUDED

#include <string>

namespace booster {
    namespace cgix {
        
        
        // TODO: A class for handling dates according the RFCs mentioned in the cookie document.
        
        class cookie {
        public:
            
            typedef unsigned long long duration;
            typedef std::string string_type;
            
            // Lifecycle
            cookie(const string_type& name, const string_type& value);
            cookie(const string_type& name, const string_type& value, duration seconds);
            cookie(const string_type& name, const string_type& value, bool secure, bool http_only, duration seconds);
            cookie(const string_type& name, const string_type& value, const string_type& domain, const string_type& path, bool secure, bool http_only, duration seconds);
            
            // Accessors
            const string_type& name() const;
            const string_type& value() const;
            const string_type& domain() const;
            const string_type& path() const;
            duration seconds() const;
            bool is_secure() const;
            bool is_http_only() const;
            
            // Output
            operator string_type() const;
            
        private:
            
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
