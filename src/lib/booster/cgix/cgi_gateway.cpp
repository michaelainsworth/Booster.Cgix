#include <booster/cgix/cgi_gateway.hpp>
#include <booster/cgix/cgi_request.hpp>
#include <booster/cgix/cgi_response.hpp>

namespace booster {
    namespace cgix {
        
        connection cgi_gateway::get_connection() {
            static int i = 0;
            
            if (i > 0) {
                return connection();
            }
            
            ++i;

            connection::request_shared_ptr request(new cgi_request());
            connection::response_shared_ptr response(new cgi_response());
            
            return connection(request, response);
            
        }
        
        bool cgi_gateway::is_threaded() {
            return false;
        }
        
    }
}
