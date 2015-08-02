#ifndef BOOSTER_CGIX_CGI_GATEWAY_HPP_INCLUDED
#define BOOSTER_CGIX_CGI_GATEWAY_HPP_INCLUDED

#include <booster/cgix/gateway.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: cgi_gateway
        // =====================================================================
        
        // The cgi_gateway class encapsulates a CGI connection between the
        // application and the web server.
        
        class cgi_gateway : public gateway {
        public:
            
            // -----------------------------------------------------------------
            // Connection methods
            // -----------------------------------------------------------------
            
            // The get_connection() method returns an initialized connection
            // the first time it is called, and an uninitialized connection for
            // every subsequent call.
            
            virtual connection get_connection();
            
            // This method returns false, as the CGI gateway only returns a
            // single connection before exiting.
            
            virtual bool is_threaded();
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_CGI_GATEWAY_HPP_INCLUDED
