#include "booster/cgix/cookie.hpp"

#include "booster/cgix/percent_coder.hpp"
#include <sstream>

namespace booster {
    
    namespace cgix {
        
        cookie::cookie(const string_type& name, const string_type& value) : name_(name), value_(value), domain_(""), path_("/"), secure_(false), http_only_(false), seconds_(0) {}
        
        cookie::cookie(const string_type& name, const string_type& value, bool secure, bool http_only,
                       duration seconds) : name_(name), value_(value), domain_(""), path_("/"), secure_(secure),
        http_only_(http_only), seconds_(seconds) {}
        
        cookie::cookie(const string_type& name, const string_type& value, duration seconds)
        : name_(name), value_(value), domain_(""), path_("/"), secure_(false), http_only_(false), seconds_(seconds) {}
        
        cookie::cookie(const string_type& name, const string_type& value, const string_type& domain, const string_type& path, bool secure, bool http_only, duration seconds) : name_(name), value_(value), domain_(domain),
        path_ (path), secure_(secure), http_only_(http_only), seconds_(seconds) {}
        
        const cookie::string_type& cookie::name() const {
            return name_;
        }
        
        const cookie::string_type& cookie::value() const {
            return value_;
        }
        
        const cookie::string_type& cookie::domain() const {
            return domain_;
        }
        
        const cookie::string_type& cookie::path() const {
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
        
        cookie::operator string_type() const {
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
            
            return str.str();
        }
        
    }
    
}
