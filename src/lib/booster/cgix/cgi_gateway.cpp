#include <booster/cgix/cgi_gateway.hpp>
#include <booster/cgix/request.hpp>
#include <booster/cgix/response.hpp>

namespace booster {
    namespace cgix {
        
        connection cgi_gateway::get_connection() {
            static int i = 0;
            
            if (i > 0) {
                return connection();
            }

            // TODO: Rename to cgi_request and cgi_response.
            return connection(new request(), new response());
            ++i;
        }
        
        bool cgi_gateway::is_threaded() {
            return false;
        }
        
    }
}
