#include <booster/cgix/connection.hpp>
#include <booster/cgix/error.hpp>
#include <booster/cgix/request.hpp>
#include <booster/cgix/response.hpp>

namespace booster {
    namespace cgix {
        
        connection::connection() {}
        
        connection::connection(request_shared_ptr request, response_shared_ptr response) :
            request_(request), response_(response) {}
        
        connection::operator bool() const {
            return request_ && response_;
        }
        
        request& connection::request() {
            if (!request_) {
                throw std::system_error(error::connection_not_initialized);
            }
            
            return *request_;
        }
        
        response& connection::response() {
            if (!response_) {
                throw std::system_error(error::connection_not_initialized);
            }
            
            return *response_;
        }
        
    }
}
