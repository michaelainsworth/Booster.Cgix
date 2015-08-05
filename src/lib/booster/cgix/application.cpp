#include <booster/cgix/application.hpp>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/request.hpp>
#include <list>
#include <thread>
#include <memory>

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
            
            typedef std::shared_ptr<std::thread> thread_shared_ptr;
            typedef std::list<thread_shared_ptr> thread_list;
            
            thread_list threads;
            
            while ((con = gw_.get_connection())) {
                if (is_threaded) {
                    thread_shared_ptr thread(new std::thread(std::bind(delegator, con)));
                    threads.push_back(thread);
                } else {
                    delegator(con);
                }
            }
            
            // TODO: The list of thread might grow VERY large by the time it
            // gets to this point. For this reason, it might be worth doing a
            // clean up, or using an alternative strategy to wait for all
            // threads to finish.
            
            for (auto& thread : threads) {
                thread->join();
            }
        }
        
    }
}

