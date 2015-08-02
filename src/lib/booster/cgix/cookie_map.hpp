#ifndef BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED
#define BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED

#include <map>
#include <string>
#include <system_error>
#include <booster/cgix/cookie.hpp>

namespace booster {
    namespace cgix {
        
        class cookie_map {
        public:
            
            typedef std::string string_type;
            typedef std::map<string_type,string_type> map_type;
            typedef map_type::const_iterator const_iterator;
            
            static std::error_condition from_string(cookie_map& cookies, const string_type& cookie_string);
            
            bool is_set(const string_type& name) const;
            string_type get(const string_type& name) const;
            void set(const cookie& ck);
            
            const_iterator begin() const;
            const_iterator end() const;
            
        private:
            
            map_type cookies_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED
