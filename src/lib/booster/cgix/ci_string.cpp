#include <booster/cgix/ci_string.hpp>

namespace booster {
    namespace cgix {
        
        bool ci_char_traits::eq( char c1, char c2 ) {
            return toupper(c1) == toupper(c2);
        }
        
        bool ci_char_traits::lt(char c1, char c2) {
            return toupper(c1) < toupper(c2);
        }
        
        bool ci_char_traits::ne( char c1, char c2 ) {
            return toupper(c1) != toupper(c2);
        }
        
        int ci_char_traits::compare(const char* s1, const char* s2, size_t n) {
            for (size_t i = 0; i < n; ++i) {
                char a = toupper(s1[0]), b = toupper(s2[0]);
                
                if (a < b) {
                    return -1;
                } else if (a > b) {
                    return 1;
                }
            }
            
            return 0;
        }
        
        const char* ci_char_traits::find( const char* s, int n, char a ) {
            while( n-- > 0 && toupper(*s) != toupper(a) ) {
                ++s;
            }
            return s;
        }
    };
    
}

