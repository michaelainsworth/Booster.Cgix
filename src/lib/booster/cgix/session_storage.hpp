#ifndef BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED
#define BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED

#include <string>

namespace booster {
    namespace cgix {
        
        // TODO: Finish storage implementation, including obtaining session ID, etc, from request.
        template<typename S>
        class session_storage_base {
        public:
            
            template<typename T>
            void load(const S& session_id, T& t) {}
            
            template<typename T>
            void save(const S& session_id, const T& t) {}
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED
