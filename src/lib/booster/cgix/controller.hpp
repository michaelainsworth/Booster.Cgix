#ifndef BOOSTER_CGIX_CONTROLLER_HPP_INCLUDED
#define BOOSTER_CGIX_CONTROLLER_HPP_INCLUDED

#include <booster/cgix/router.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: controller
        // =====================================================================
        
        // The controller class is an (optional) class used to group request
        // handler functions together.
        //
        // For example, if you have a forum system, with users, forums, threads
        // and posts, you might put all the thread-related functionality
        // (creating threads, replying to threads, deleting threads, etc)
        // in a dedicated controller in order make your code cleaner.
        //
        // You can add controller's to a class derived from the application
        // class by calling application::add_controller().
        
        class controller : protected router {
        public:

            // -----------------------------------------------------------------
            // Friends
            // -----------------------------------------------------------------
            
            friend class application;
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            // The destructor is pure-virtual because, the programs should
            // implement a derived class.
            
            virtual ~controller() = 0;
            
            // -----------------------------------------------------------------
            // Routing
            // -----------------------------------------------------------------
            
        protected:
            
            // The setup_routes() method is used by derived classes to map
            // router condition functions to router handler functions by
            // repeatedly calling the on() variety of functions.
            
            virtual void setup_routes();
            
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_CONTROLLER_HPP_INCLUDED