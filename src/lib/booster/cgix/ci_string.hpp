#ifndef BOOSTER_CGIX_CI_STRING_HPP_INCLUDED
#define BOOSTER_CGIX_CI_STRING_HPP_INCLUDED

#include <string>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: ci_char_traits
        // =====================================================================
        
        // This class allows the creation of case_insensitive strings using
        // std::basic_string. It also supports common std::string traits.
        
        class ci_char_traits : public std::char_traits<char> {
        public:
            
            static bool eq( char c1, char c2 );
            static bool lt(char c1, char c2);
            static bool ne( char c1, char c2 );
            static int compare(const char* s1, const char* s2, size_t n);
            static const char* find( const char* s, int n, char a );
            
        };
        
        typedef std::basic_string<char, ci_char_traits> ci_string;
        
    }
}

#endif // #ifndef BOOSTER_CGIX_CI_STRING_HPP_INCLUDED