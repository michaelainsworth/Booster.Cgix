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

            // TODO: Rename to cgi_request and cgi_response.
            // TODO: The constructor for the connection should accept shared
            // pointers in the case where one might throw (e.g., due to memory
            // constraints).
            return connection(new cgi_request(), new cgi_response());
            ++i;
        }
        
        bool cgi_gateway::is_threaded() {
            return false;
        }
        
    }
}
