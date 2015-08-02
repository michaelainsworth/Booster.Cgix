#include <booster/cgix/application.hpp>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/request.hpp>

namespace booster
{
    namespace cgix
    {

        application::application(gateway& gw) : gw_(gw) {}
        
        application::~application() {}
        
        void application::run() {
            router r(get_routes());
            connection con;
            
            while (gw_.get_connection(con)) {
                if (!r.delegate(con)) {
                    request_unhandled(con);
                }
            }
        }
        
        basic_route* application::connect(request_method method, const std::string& request_uri) {
            // TODO: Finish
            auto c = [method, request_uri](connection& con) -> bool {
                return con.request().method() == method && con.request().uri() == request_uri;
            };
            
            auto h = [](connection& con) -> void {
                
            };
            
            return new route<bool(*)(connection&),void(*)(connection&)>(c, h);
        }
        
    }
}

