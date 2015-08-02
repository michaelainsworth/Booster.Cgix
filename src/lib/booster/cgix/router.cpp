#include <booster/cgix/router.hpp>

namespace booster
{
    namespace cgix
    {
        
        router::router(const basic_route_ptr_vector& routes) : routes_(routes) {}
            
        bool router::delegate(connection& con) {
            for (auto &r : routes_) {
                if (r->handle_if_match(con)) {
                    return true;
                }
            }
            
            return false;
        }
        
        route& router::on(request_method method, const std::string& uri) {
            
        }
        
        route& router::on(request_method method, const std::regex& pattern) {
            
        }
        
    }
}


