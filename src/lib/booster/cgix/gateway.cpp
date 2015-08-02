#include <booster/cgix/gateway.hpp>
#include <booster/cgix/request.hpp>
#include <booster/cgix/response.hpp>

namespace booster
{
    namespace cgix
    {

        bool gateway::get_connection(connection& con) {
            static int i = 0;
            
            if (i > 0) {
                return false;
            }
            
            con.set(new request(), new response());
            ++i;
            return true;
        }
        
    }
}
