#include "booster/cgix/cookie.hpp"

#include "booster/cgix/percent_coder.hpp"
#include <sstream>

namespace booster {
    
    namespace cgix {
        
        cookie::cookie(const std::string& name, const std::string& value) : name_(name), value_(value), domain_(""), path_("/"), secure_(false), http_only_(false), seconds_(0) {}
        
        cookie::cookie(const std::string& name, const std::string& value, bool secure, bool http_only,
                       duration seconds) : name_(name), value_(value), domain_(""), path_("/"), secure_(secure),
        http_only_(http_only), seconds_(seconds) {}
        
        cookie::cookie(const std::string& name, const std::string& value, duration seconds)
        : name_(name), value_(value), domain_(""), path_("/"), secure_(false), http_only_(false), seconds_(seconds) {}
        
        cookie::cookie(const std::string& name, const std::string& value, const std::string& domain, const std::string& path, bool secure, bool http_only, duration seconds) : name_(name), value_(value), domain_(domain),
        path_ (path), secure_(secure), http_only_(http_only), seconds_(seconds) {}
        
        const std::string& cookie::name() const {
            return name_;
        }
        
        const std::string& cookie::value() const {
            return value_;
        }
        
        const std::string& cookie::domain() const {
            return domain_;
        }
        
        const std::string& cookie::path() const {
            return path_;
        }
        
        bool cookie::is_secure() const {
            return secure_;
        }
        
        bool cookie::is_http_only() const {
            return http_only_;
        }
        
        cookie::duration cookie::seconds() const {
            return seconds_;
        }
        
        cookie::operator std::string() const {
            percent_coder pe;
            
            std::ostringstream str;
            str << pe.encode(name_) << "=" << pe.encode(value_);
            if (!domain_.empty()) {
                str << "; Domain=" << domain_;
            }
            if (!path_.empty()) {
                str << "; Path=" << path_;
            }
            if (0 != seconds_) {
                str << "; Max-Age=" << seconds_;
            }
            if (secure_) str << "; Secure";
            if (http_only_) str << "; HttpOnly";
            
            return "Set-Cookie: " + str.str();
        }
        
    }
    
}
