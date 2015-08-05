#include <booster/cgix/router.hpp>
#include <booster/cgix/request.hpp>

namespace booster {
    namespace cgix {
        
        router& router::on(const route::condition_function& condition,
                           const route::handler_function& handler) {
            routes_.push_back(route(condition, handler));
            return *this;
        }
        
        void router::clear() {
            routes_.clear();
        }
        
        router::~router() {}

        bool router::delegate(connection con, bool execute_handler) {
            for (auto &r : routes_) {
                if (r.does_match(con)) {
                    if (execute_handler) {
                        return r.handle_if_match(con);
                    } else {
                        return true;
                    }
                }
            }
            
            return false;
        }

        router& router::on(const std::string& method, const std::string& uri,
                           const route::handler_function& handler) {
            return on([method, uri](connection& con) -> bool {
                const request& req = con.request();
                return (req.method() == method && req.uri() == uri);
            }, handler);
        }
        
        router& router::on(const std::string& method, const std::regex& pattern,
                   const route::handler_function& handler) {
            return on([method, pattern](connection& con) -> bool {
                const request& req = con.request();
                return req.method() == method && std::regex_match(req.uri(), pattern);
            }, handler);
        }
        
    }
}


