#ifndef BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED
#define BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED

#include <map>
#include <string>
#include <system_error>
#include <booster/cgix/cookie.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: cookie_map
        // =====================================================================
        
        // The cookie_map class represents a set of cookies.
        
        class cookie_map {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::string string_type;
            typedef std::map<string_type,string_type> map_type;
            typedef map_type::const_iterator const_iterator;
            
            // -----------------------------------------------------------------
            // Serialization
            // -----------------------------------------------------------------
            
            // The from_string() function is used to load the cookie map from
            // the value of "Cookie" HTTP header.
            
            static std::error_condition from_string(cookie_map& cookies, const string_type& cookie_string);
            
            // -----------------------------------------------------------------
            // Accessors and mutators
            // -----------------------------------------------------------------
            
            // The functions below allow access to and modification of the
            // cookies.
            
            bool is_set(const string_type& name) const;
            string_type get(const string_type& name) const;
            void set(const cookie& ck);
            
            // -----------------------------------------------------------------
            // Traversal
            // -----------------------------------------------------------------
            
            // The begin() and end() methods below allow the cookie_map class
            // to be used with functions that operate on iterators.
            
            const_iterator begin() const;
            const_iterator end() const;
            
        private:
            
            map_type cookies_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_COOKIE_MAP_HPP_INCLUDED
