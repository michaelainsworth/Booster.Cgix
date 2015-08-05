#ifndef BOOSTER_CGIX_STRING_EXPLODER_HPP_INCLUDED
#define BOOSTER_CGIX_STRING_EXPLODER_HPP_INCLUDED

#include <string>
#include <vector>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: string_exploder
        // =====================================================================
        
        // The string_exploder class splits strings into a container of
        // strings.

        class string_exploder {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::string string_type;
            typedef std::vector<string_type> vector_type;
            
            // -----------------------------------------------------------------
            // Main methods
            // -----------------------------------------------------------------
            
            // The explode() function splits the string into multiple strings
            // using the delimiter, and storing the results in container
            // specified.
            
            void explode(const string_type& imploded,
                         const string_type& delimiter,
                         vector_type& items, size_t limit = 0);

            // The implode() function joins the elements together
            // using the delimiter specified.
            
            string_type implode(const string_type& delimiter,
                                const vector_type& items);
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_STRING_EXPLODER_HPP_INCLUDED