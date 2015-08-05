#ifndef BOOSTER_CGIX_APPLICATION_HPP_INCLUDED
#define BOOSTER_CGIX_APPLICATION_HPP_INCLUDED

#include <vector>
#include <boost/noncopyable.hpp>
#include <booster/cgix/router.hpp>
#include <booster/cgix/gateway.hpp>
#include <booster/cgix/controller.hpp>

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
        
        class application : protected router {
        private:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::shared_ptr<controller> controller_shared_ptr;
            typedef std::vector<controller_shared_ptr>
                controller_shared_ptr_vector;

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
            //
            // You can also call add_controller, if you want to add a collection
            // of routes that are logically grouped into a controller.
            
            virtual void setup_routes();
            
            // The clear_routes() function clears all the routes added to the
            // application with the on() family of functions. It also clears
            // the controllers added to the application with the
            // add_controller() template function.
            
            void clear_routes();
            
            // The add_controller() method is used to add controllers to an
            // application. Controllers group related handler functions
            // together.
            //
            // The controller's setup_routes() function is called when the
            // controller is added to the appliation, meaning that the
            // controller can be delegated to immediately.
            //
            // The C template parameter is the name of the controller class,
            // while the Args variadic template parameter are the arguments
            // to be passed to the controller's constructor.
            
            template<typename C, typename... Args>
            application& add_controller(Args... args);
            
        public:
            
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
            
            gateway& gw_;
            controller_shared_ptr_vector controllers_;
        
        };
        
        template<typename C, typename... Args>
        application& application::add_controller(Args... args) {
            static_assert(std::is_base_of<controller, C>::value, "The booster::cgix::application::add_controller() template function must be passed a controller class name as the first argument.");
            
            controller_shared_ptr ctrl(new C(args...));
            ctrl->setup_routes();
            controllers_.push_back(ctrl);
            
            on([ctrl](connection con) -> bool {
                return ctrl->delegate(con, false);
            }, [ctrl](connection con) {
                ctrl->delegate(con, true);
            });
            
            return *this;
        }
    }
}

#endif // #ifndef BOOSTER_CGIX_APPLICATION_HPP_INCLUDED
