#ifndef BOOSTER_CGIX_ROUTER_HPP_INCLUDED
#define BOOSTER_CGIX_ROUTER_HPP_INCLUDED

#include <vector>
#include <type_traits>
#include <initializer_list>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/route.hpp>
#include <regex>
#include <boost/noncopyable.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: router
        // =====================================================================
        //
        // The router class is responsible for delegating connections to the
        // appropriate handlers.
        
        class router : private boost::noncopyable {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::vector<route> route_vector;
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            // The destructor for the router class is virtual because other
            // classes (e.g., the application class) can derive from it.
            
            virtual ~router();
            
            // -----------------------------------------------------------------
            // Core routing functions
            // -----------------------------------------------------------------
            
            // The method below is the primary mechanism of adding a route.
            // It simply accepts the condition and handler functions.
            //
            // The return value of the on() method is the router itself,
            // allowing routes to be chained together.
            
            router& on(const route::condition_function& condition,
                       const route::handler_function& handler);
            
            // The clear() method removes all the existing routes.
            
            void clear();
            
            // The delegate method loops through each of the routes and calling
            // the condition function to determine if the route can handle the
            // request. If it can handle the request, and execute_handler is
            // true, the handler will be called and true will be returned. If it
            // can handle the request but execute_handler is false, true is
            // returned but the handler is not executed. If no condition
            // functions return true, this function returns false.
            
            bool delegate(connection con, bool execute_handler);
            
            // -----------------------------------------------------------------
            // Convenience routing functions
            // -----------------------------------------------------------------
            
            // This method takes a request method, a URI and a handler function.
            // The handler function will be called if both the request method
            // and URI supplied match that in the request object.
            //
            // For example, this method could be used to map a HTTP "GET"
            // request to "/mything" to a certain function.
            
            router& on(const std::string& method, const std::string& uri,
                       const route::handler_function& handler);
            
            // This method takes a request method, a regular expression and a
            // handler function. The handler function will be called if the
            // request method matches that in the request object, and the
            // regular expression pattern matches the request object's URI.
            //
            // For example, this method can be used to map a HTTP "PUT" request
            // to "^/user/[0-9]+/profile$".
            
            router& on(const std::string& method, const std::regex& pattern,
                       const route::handler_function& handler);
            
        private:
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
            route_vector routes_;
            
        };
        
    }
}


#endif // #ifndef BOOSTER_CGIX_ROUTER_HPP_INCLUDED

