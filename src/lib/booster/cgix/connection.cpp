#include <booster/cgix/connection.hpp>
#include <booster/cgix/error_condition.hpp>
#include <booster/cgix/request.hpp>
#include <booster/cgix/response.hpp>

namespace booster {
    namespace cgix {
        
        connection::connection() : req_(0), resp_(0) {}
        
        connection::~connection() {
            clear();
        }
        
        void connection::clear() {
            if (req_) {
                delete req_;
                req_ = 0;
            }
            
            if (resp_) {
                delete resp_;
                resp_ = 0;
            }
        }
        
        const request& connection::request() const {
            if (!req_) {
                throw std::system_error(error::connection_not_initialized);
            }
            
            return *req_;
        }
        
        response& connection::response() const {
            if (!resp_) {
                throw std::system_error(error::connection_not_initialized);
            }
            
            return *resp_;
        }
        
        void connection::set(class request* req, class response* resp) {
            clear();
            
            req_ = req;
            resp_ = resp;
        }
        
    }
}
