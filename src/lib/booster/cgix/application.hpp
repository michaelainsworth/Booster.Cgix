#ifndef BOOSTER_CGIX_APPLICATION_HPP_INCLUDED
#define BOOSTER_CGIX_APPLICATION_HPP_INCLUDED

#include <vector>
#include <boost/noncopyable.hpp>
#include <booster/cgix/router.hpp>
#include <booster/cgix/gateway.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: application
        // =====================================================================

        // The application class is a special type of router.
        //
        // Each program using the Booster.Cgix library should write a class that
        // derives from this application class. The derived class should call
        // the protected on() methods (of the router class) within the
        // setup_routes() method.
        
        class application : private boost::noncopyable, protected router {
        public:
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------

            // The constructor accepts a single argument - the gateway that
            // obtains connections.
            
            application(gateway& gw);
            
            // The destructor is pure virtual, because the application class
            // must be used as a base class.
            
            virtual ~application() = 0;
            
            // -----------------------------------------------------------------
            // Routing
            // -----------------------------------------------------------------
            
        protected:
            
            // The setup_routes() method is used by derived classes to map
            // router condition functions to router handler functions by
            // repeatedly calling the on() variety of functions.
            
            virtual void setup_routes();
            
        public:
            
            // TODO: add_controller() for controllers dedicated to a single
            // area of functionality?
            
            // -----------------------------------------------------------------
            // Main methods
            // -----------------------------------------------------------------
            
            // The run() function calls get_connection() on the gateway in a
            // loop, delegating each connection to the appropriate handler, or
            // calling connection_not_handled() if the request was not handled.
            //
            // The loop finishes when the gateway's get_connection() function
            // returns an uninitialised connection.
            
            void run();
            
        protected:
            
            // The connection_not_handled() function must be implemented by
            // derived classes to handle requests that are no specifically
            // handled elsewhere.
            //
            // This is a pure virtual function, and needs to be implemented by
            // derived classes.
            
            virtual void connection_not_handled(connection& con) = 0;
            
        private:
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
          
            // TODO: I don't know about the gateway as a member variable -
            // how should threads (e.g., via scgi) be abstracted? If this is
            // the case, what is the difference between a 'controller' and an
            // 'application'? Perhaps the gateway could have an "is_threaded()"
            // function?
            
            gateway& gw_;
        
        };
    }
}

#endif // #ifndef BOOSTER_CGIX_APPLICATION_HPP_INCLUDED
