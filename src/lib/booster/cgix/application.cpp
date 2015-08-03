#include <booster/cgix/application.hpp>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/request.hpp>
#include <vector>
#include <thread>

namespace booster {
    namespace cgix {

        application::application(gateway& gw) : gw_(gw) {}
        
        application::~application() {}
        
        void application::setup_routes() {}
        
        void application::clear_routes() {
            clear();
            controllers_.clear();
        }
        
        void application::run() {
            clear_routes();
            setup_routes();
            
            bool is_threaded = gw_.is_threaded();
            connection con;
            
            auto delegator = [this](connection con){
                if (!this->delegate(con, true)) {
                    this->connection_not_handled(con);
                }
            };
            
            while ((con = gw_.get_connection())) {
                if (is_threaded) {
                    std::thread(std::bind(delegator, con)).detach();
                } else {
                    delegator(con);
                }
            }
            
            // TODO: If threaded, wait for all threads to join!
        }
        
    }
}

