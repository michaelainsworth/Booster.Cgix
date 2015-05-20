#ifndef BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED
#define BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED

#include <map>
#include <string>
#include <system_error>

namespace booster {
    namespace cgix {
        
        class cookie_map {
        public:
            
            typedef std::string string_type;
            typedef std::map<string_type,string_type> map_type;
            
            static std::error_condition from_string(cookie_map& cookies, const string_type& cookie_string);
            
            bool has(const string_type& name) const;
            string_type get(const string_type& name) const;
            
        private:
            
            map_type cookies_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED
