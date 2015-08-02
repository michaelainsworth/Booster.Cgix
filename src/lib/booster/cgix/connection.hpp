#ifndef BOOSTER_CGIX_CONNECTION_HPP_INCLUDED
#define BOOSTER_CGIX_CONNECTION_HPP_INCLUDED

#include <memory>

namespace booster {
    namespace cgix {
        
        class request;
        class response;
        
        class connection {
        public:
            
            friend class gateway;
            
            connection();
            ~connection();
            
            const request& request() const;
            response& response() const;
            
        private:
            
            connection(const connection& rhs) = delete;
            connection& operator =(const connection& rhs) = delete;
            
            // To be accessed by gateway.
            void set(class request* req, class response* resp);
            void clear();
            
            class request* req_;
            class response* resp_;
            
        };
        
    }
    
}

#endif // #ifndef BOOSTER_CGIX_CONNECTION_HPP_INCLUDED
