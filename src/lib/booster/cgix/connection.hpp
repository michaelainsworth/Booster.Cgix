#ifndef BOOSTER_CGIX_CONNECTION_HPP_INCLUDED
#define BOOSTER_CGIX_CONNECTION_HPP_INCLUDED

#include <memory>

namespace booster {
    namespace cgix {
        
        class request;
        class response;
        
        // =====================================================================
        // Class: connection
        // =====================================================================
        
        // The connection class represents a link between the application and
        // the web server, and contains std::shared_ptr objects pointing to a
        // request and response object.
        
        class connection {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::shared_ptr<request> request_shared_ptr;
            typedef std::shared_ptr<response> response_shared_ptr;
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            // The default constructor initializes the request_ and response_
            // member variables with null pointers. This is be used by gateways
            // to return an "uninitialized connection", which causes the loop in
            // application::run() to return false.
            
            connection();
            
            // The constructor with a request and response object specified
            // initializes the request_ and response_ member variables with
            // these values.
            
            connection(request_shared_ptr request, response_shared_ptr response);
            
            // -----------------------------------------------------------------
            // Accessors
            // -----------------------------------------------------------------

            // The operator bool() method returns false if either the request_
            // or response_ member variables are uninitialized. Otherwise, this
            // method returns true. This function returns true for objects
            // created with the default constructor, and can be used to
            // determine whether connection processing should continue.
            
            operator bool() const;
            
            // The request() method returns the request associated with the
            // connection. If the connection is uninitialized, this method
            // throws a std::system_error.
            
            request& request();
            
            // The response() method returns the response associated with the
            // connection. If the connection is uninitialized, this method
            // throws a std::system_error.
            
            response& response();
            
        private:

            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
            request_shared_ptr request_;
            response_shared_ptr response_;
            
        };
        
    }
    
}

#endif // #ifndef BOOSTER_CGIX_CONNECTION_HPP_INCLUDED
