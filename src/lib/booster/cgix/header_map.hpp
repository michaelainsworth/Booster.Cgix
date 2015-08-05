#ifndef BOOSTER_CGIX_HEADER_MAP_HPP_INCLUDED
#define BOOSTER_CGIX_HEADER_MAP_HPP_INCLUDED

#include <map>
#include <booster/cgix/error.hpp>
#include <booster/cgix/ci_string.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: header_map
        // =====================================================================
        
        // The header_map class represents a set of HTTP headers.
        //
        // It essentially wraps a std::map of strings.
        
        class header_map {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------

            typedef std::basic_string<char, ci_char_traits> name_string_type;
            typedef std::string value_string_type;
            typedef std::map<name_string_type,value_string_type> map_type;
            typedef map_type::const_iterator const_iterator;
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            header_map();

            // -----------------------------------------------------------------
            // Accessors and mutators
            // -----------------------------------------------------------------
            
            // The methods below allow access to and modification of the headers
            // in the collection.
            
            bool is_set(const name_string_type& name) const;
            value_string_type get(const name_string_type& name) const;
            void set(const name_string_type& name, const value_string_type& value);
            void unset(const name_string_type& name);
            
            // -----------------------------------------------------------------
            // Traversal
            // -----------------------------------------------------------------
            
            // The begin() and end() methods allow operations that use
            // iterators.
            
            const_iterator begin() const;
            const_iterator end() const;
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
        private:
            
            map_type headers_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_HEADER_MAP_HPP_INCLUDED
