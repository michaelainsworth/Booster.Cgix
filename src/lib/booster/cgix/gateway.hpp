#ifndef BOOSTER_CGIX_GATEWAY_HPP_INCLUDED
#define BOOSTER_CGIX_GATEWAY_HPP_INCLUDED

#include <booster/cgix/connection.hpp>
#include <boost/noncopyable.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: gateway
        // =====================================================================
        
        // The gateway class is an abstract base class used to encapsulate
        // communication between the application and the web server.
        
        class gateway : private boost::noncopyable {
        public:
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            // The destructor is pure virtual, as the gateway class is intended
            // to be a base class for specific CGI protocols (e.g., CGI, SCGI).
            
            virtual ~gateway() = 0;

            // -----------------------------------------------------------------
            // Connection methods
            // -----------------------------------------------------------------
            
            // The get_connection() method must be implemented by derived
            // classes.
            //
            // This method either returns an initialized connection to be
            // processed by the application, or an uninitialized connection,
            // meaning there are no more client requests and the application
            // should terminate. An uninitialized connection can be returned
            // using the connection's default constructor.
            
            virtual connection get_connection() = 0;
            
            // The is_threaded() function is used to inform the application
            // class whether the gateway supports multiple concurrent
            // connections to the web server. If this method returns true in
            // derived classes, then all connection handling functions are
            // called in a separate thread.
            
            virtual bool is_threaded() = 0;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_GATEWAY_HPP_INCLUDED
