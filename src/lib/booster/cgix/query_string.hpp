#ifndef BOOSTER_CGIX_QUERY_STRING_HPP_INCLUDED
#define BOOSTER_CGIX_QUERY_STRING_HPP_INCLUDED

#include <boost/lexical_cast.hpp>
#include <map>
#include <string>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: query_string
        // =====================================================================
        
        // The query_string class encapsulates a map of string key/value pairs.
        
        class query_string {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::string string_type;
            typedef std::map<string_type, string_type> map_type;
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            // The default constructor creates an empty query string with no
            // keys and no values.
            
            query_string();
            
            // The string-based constructor parses value, populating the query
            // string with keys and values as appropriate.
            
            query_string(const string_type& value);
            
            // -----------------------------------------------------------------
            // Accessors
            // -----------------------------------------------------------------
            
            // The has() function returns whether or not the named value exists.
            
            bool has(const string_type& name) const;
            
            // The operator[] function returns the named value specified, or an
            // empty string if the value does not exist.
            
            string_type operator[](const string_type& name) const;

            // -----------------------------------------------------------------
            // Type detection and conversion
            // -----------------------------------------------------------------
            
            // The is() template function returns whether or not the named value
            // is of the type specified.
            
            template<typename T>
            bool is(const string_type& name) const;
            
            // The get() template function returns the the named value as the
            // type specified.
            
            template<typename T>
            T get(const string_type& name, const T& default_value) const;
            
            template<typename T>
            void set(const string_type& name, const T& value);
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
        private:
            
            map_type values_;
            
        };
        
        // =====================================================================
        // Implementation: query_string
        // =====================================================================
        
        template<typename T>
        bool query_string::is(const string_type& name) const {
            if (!has(name)) {
                return false;
            }
            
            string_type value = values_.find(name)->second;
            
            try {
                T return_value = boost::lexical_cast<T>(value);
                return true;
            } catch (boost::bad_lexical_cast&) {
                return false;
            }
        }
        
        template<typename T>
        T query_string::get(const string_type& name, const T& default_value) const {
            if (!has(name)) {
                return default_value;
            }
            
            string_type value = values_.find(name)->second;
            return boost::lexical_cast<T>(value);
        }
        
        template<typename T>
        void query_string::set(const string_type& name, const T& value) {
            if (has(name)) {
                values_.erase(values_.find(name));
            }
            
            values_insert(
                          std::make_pair(name,
                                         boost::lexical_cast<string_type>(value)
                                         )
                          );
        }
        
    }
}

#endif // #ifndef BOOSTER_CGIX_QUERY_STRING_HPP_INCLUDED