#ifndef BOOSTER_CGIX_COOKIE_HPP_INCLUDED
#define BOOSTER_CGIX_COOKIE_HPP_INCLUDED

#include <string>

namespace booster {
    namespace cgix {
        
        
        // TODO: A class for handling dates according the RFCs mentioned in the cookie document.
        
        class cookie {
        public:
            
            typedef unsigned long long duration;
            
            // Lifecycle
            cookie(const std::string& name, const std::string& value);
            cookie(const std::string& name, const std::string& value, duration seconds);
            cookie(const std::string& name, const std::string& value, bool secure, bool http_only, duration seconds);
            cookie(const std::string& name, const std::string& value, const std::string& domain, const std::string& path, bool secure, bool http_only, duration seconds);
            
            // Accessors
            const std::string& name() const;
            const std::string& value() const;
            const std::string& domain() const;
            const std::string& path() const;
            duration seconds() const;
            bool is_secure() const;
            bool is_http_only() const;
            
            // Output
            operator std::string() const;
            
        private:
            
            std::string name_;
            std::string value_;
            std::string domain_;
            std::string path_;
            bool secure_;
            bool http_only_;
            duration seconds_;
            
        };
        
        
    }
}

#endif // BOOSTER_CGIX_COOKIE_HPP_INCLUDED
