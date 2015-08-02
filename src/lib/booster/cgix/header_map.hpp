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
            
            typedef std::basic_string<char, ci_char_traits> name_string_type;
            typedef std::string value_string_type;
            typedef std::map<name_string_type,value_string_type> map_type;
            typedef map_type::const_iterator const_iterator;
            
            const_iterator begin() const;
            const_iterator end() const;
            
            bool is_set(const name_string_type& name) const;
            value_string_type get(const name_string_type& name) const;
            void set(const name_string_type& name, const value_string_type& value);
            void unset(const name_string_type& name);
            
        private:
            
            map_type headers_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_HEADER_MAP_HPP_INCLUDED