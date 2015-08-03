#include "booster/cgix/request.hpp"
#include "booster/cgix/environment.hpp"

#include <iostream>

namespace booster {
    namespace cgix {
        
        const std::string request::get("GET");
        const std::string request::head("HEAD");
        const std::string request::post("POST");
        const std::string request::put("PUT");
        const std::string request::delete_("DELETE");
        const std::string request::trace("TRACE");
        const std::string request::connect("CONNECT");
        const std::string request::options("OPTIONS");
        
        request::~request() {}
        
    }
}
