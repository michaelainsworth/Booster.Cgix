#ifndef BOOSTER_CGIX_CGI_RESPONSE_HPP_INCLUDED
#define BOOSTER_CGIX_CGI_RESPONSE_HPP_INCLUDED

#include <booster/cgix/response.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: cgi_response
        // =====================================================================
        
        // The cgi_response class is used by the cgi_gateway class to send a
        // response to the web server using the CGI protocol.
        
        class cgi_response : public response {
        public:
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            cgi_response();
            virtual ~cgi_response();

            // -----------------------------------------------------------------
            // Main methods
            // -----------------------------------------------------------------
            
            virtual status_type status() const;
            virtual response& operator <<(enum status_type status);
            
            virtual bool are_headers_sent() const;
            virtual const header_map& headers() const;
            virtual response& operator <<(const header& hdr);
            virtual void send_headers();
            
            virtual const cookie_map& cookies() const;
            virtual response& operator <<(const cookie& ck);
            
            virtual std::ostream& out();
            
        private:
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
            bool are_headers_sent_;
            status_type status_;
            header_map headers_;
            cookie_map cookies_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_CGI_RESPONSE_HPP_INCLUDED
