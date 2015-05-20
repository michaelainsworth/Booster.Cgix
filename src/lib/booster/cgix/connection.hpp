#ifndef BOOSTER_CGIX_CONNECTION_HPP_INCLUDED
#define BOOSTER_CGIX_CONNECTION_HPP_INCLUDED

#include <booster/cgix/request.hpp>
// TODO: Re-enable
//#include <booster/cgix/response.hpp>
#include <memory>

namespace booster {
    namespace cgix {
        
        class request;
        class response;
        
        class connection {
        public:
            
            typedef std::shared_ptr<request> request_shared_ptr;
            typedef std::shared_ptr<response> response_shared_ptr;
            
            connection(request* req, response* resp);
            
            const request& request() const;
            response& response() const;
            
        private:
            
            request_shared_ptr request_;
            response_shared_ptr response_;
            
        };
        
    }
    
}

#endif // #ifndef BOOSTER_CGIX_CONNECTION_HPP_INCLUDED
