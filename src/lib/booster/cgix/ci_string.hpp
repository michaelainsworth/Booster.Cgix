#ifndef BOOSTER_CGIX_CI_STRING_HPP_INCLUDED
#define BOOSTER_CGIX_CI_STRING_HPP_INCLUDED

#include <string>

namespace booster {
    namespace cgix {
        
        class ci_char_traits : public std::char_traits<char> {
        public:
            
            static bool eq( char c1, char c2 );
            static bool lt(char c1, char c2);
            static bool ne( char c1, char c2 );
            static int compare(const char* s1, const char* s2, size_t n);
            static const char* find( const char* s, int n, char a );
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_CI_STRING_HPP_INCLUDED