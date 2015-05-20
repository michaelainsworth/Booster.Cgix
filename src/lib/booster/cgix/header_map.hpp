#ifndef BOOSTER_CGIX_HEADER_MAP_HPP_INCLUDED
#define BOOSTER_CGIX_HEADER_MAP_HPP_INCLUDED

// TODO: Work out what to do re noexcept specs.

#include <map>
#include <booster/cgix/error_condition.hpp>
#include <booster/cgix/ci_string.hpp>

namespace booster {
    namespace cgix {
        
        class header_map {
        public:
            
            header_map();
            
            typedef std::basic_string<char, ci_char_traits> key_string_type;
            typedef std::string value_string_type;
            typedef std::map<key_string_type,value_string_type> map_type;
            
            bool is_set(const key_string_type& name) const;
            value_string_type get(const key_string_type& name) const;
            
        private:
            
            map_type headers_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_HEADER_MAP_HPP_INCLUDED