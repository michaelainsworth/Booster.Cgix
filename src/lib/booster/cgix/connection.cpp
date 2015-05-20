#include <booster/cgix/connection.hpp>

namespace booster {
    namespace cgix {
        
        // TODO: Change this to ref actual response.
        connection::connection(class request* req, class response* resp) : request_(req), response_(0) {}
        
        const request& connection::request() const {
            return *request_;
        }
        
        response& connection::response() const {
            return *response_;
        }
        
    }
}
