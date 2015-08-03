#include <booster/cgix/route.hpp>

namespace booster {
    namespace cgix {

        route::route(condition_function condition, handler_function handler) :
            condition_(condition), handler_(handler) {}
        
        bool route::does_match(connection& con) {
            return condition_(con);
        }
        
        bool route::handle_if_match(connection& con) {
            if (!condition_(con)) {
                return false;
            }
            
            handler_(con);
            return true;
        }
        
    }
}
