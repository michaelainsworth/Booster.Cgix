#ifndef BOOSTER_CGIX_ROUTE_HPP_INCLUDED
#define BOOSTER_CGIX_ROUTE_HPP_INCLUDED

#include <functional>

namespace booster {
    namespace cgix {
        
        class connection;
        
        // =====================================================================
        // Class: route
        // =====================================================================
        //
        // The route class is responsible for encapsulating a 'condition'
        // function and a 'handler' function, both represented using the
        // std::function class template.
        //
        // The 'condition' function accepts a reference to a connection object
        // and returns true if the handler should be invoked and false if the
        // handler should not be invoked.
        //
        // The 'handler' function accepts a reference to a connection object
        // but does not return a value. It should use the values in the request
        // object (such as request headers, cookies, the request body, etc) to
        // send information back to the client (e.g., headers, cookies, HTML,
        // JSON-encoded content, etc).
        class route {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::function<bool(connection&)> condition_function;
            typedef std::function<void(connection&)> handler_function;

            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            route(condition_function condition, handler_function handler);
            
            // -----------------------------------------------------------------
            // Public functions
            // -----------------------------------------------------------------
            
            // This method returns the result of the condition function. That
            // is, it returns true if the connection could be processed by the
            // handler function.
            
            bool does_match(connection& con);
            
            // If the condition function returns false, the handle_if_match()
            // function will return false. If the condition function returns
            // true, the handler function will be invoked and true will be
            // returned.
            
            bool handle_if_match(connection& con);
            
        protected:
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
            condition_function condition_;
            handler_function handler_;
            
        };

    }
}

#endif // #ifndef BOOSTER_CGIX_ROUTE_HPP_INCLUDED
