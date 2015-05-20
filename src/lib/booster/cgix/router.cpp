#include <booster/cgix/router.hpp>

namespace booster
{
    namespace cgix
    {
        
        router::router(const std::initializer_list<basic_route*> routes) : routes_(routes) {}
            
        bool router::delegate(connection& con) {
            for (auto &r : routes_) {
                if (r->handle_if_match(con)) {
                    return true;
                }
            }
            
            return false;
        }
        
    }
}


