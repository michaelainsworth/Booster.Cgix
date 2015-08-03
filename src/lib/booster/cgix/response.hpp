#ifndef BOOSTER_CGIX_RESPONSE_HPP_INCLUDED
#define BOOSTER_CGIX_RESPONSE_HPP_INCLUDED

#include <iostream>
#include <booster/cgix/header.hpp>
#include <booster/cgix/cookie.hpp>
#include <booster/cgix/cookie_map.hpp>
#include <booster/cgix/header_map.hpp>
#include <boost/noncopyable.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: response
        // =====================================================================
        
        // The response class encapsulates the mechanism by which the
        // application returns data to the web server according to the gateway
        // specified (e.g., CGI, SCI).
        //
        // The response class is an abstract base class, as each gateway should
        // implement a derived version of it.
        //
        // The class is privately derived from boost::noncopyable, as the only
        // place that a response is created should be in the gateway class (with
        // memory managed by the connection class).
        
        class response : private boost::noncopyable {
        public:
            
            // -----------------------------------------------------------------
            // Constants
            // -----------------------------------------------------------------
            
            // The constants below represent status codes to be sent back to
            // the browser.
            
            enum status_type {
                continue_ = 100,
                switching_protocols = 101,
                ok = 200,
                created = 201,
                accepted = 202,
                non_authoritative_information = 203,
                no_content = 204,
                reset_content = 205,
                partial_content = 206,
                multiple_choices = 300,
                moved_permanently = 301,
                moved_temporarily = 302,
                see_other = 303,
                not_modified = 304,
                use_proxy = 305,
                unused = 306,
                temporary_redirect = 307,
                bad_request = 400,
                unauthorized = 401,
                payment_required = 402,
                forbidden = 403,
                not_found = 404,
                method_not_allowed = 405,
                not_acceptable = 406,
                proxy_authentication_required = 407,
                request_time_out = 408,
                conflict = 409,
                gone = 410,
                length_required = 411,
                precondition_failed = 412,
                request_entity_too_large = 413,
                request_uri_too_large = 414,
                unsupported_media_type = 415,
                requested_range_not_satisfiable = 416,
                expectation_failed = 417,
                internal_server_error = 500,
                not_implemented = 501,
                bad_gateway = 502,
                service_unavailable = 503,
                gateway_time_out = 504,
                http_version_not_supported = 505,
                unknown = 999
            };

            // -----------------------------------------------------------------
            // Utility
            // -----------------------------------------------------------------
            
            // The methods below handle the conversion between HTTP status codes
            // and strings.
            
            std::string status_to_string(status_type status);
            
            status_type string_to_status(const std::string& status);
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------

            // The response destructor is pure virtual to force derived classes
            // to implement.

            virtual ~response() = 0;
            
            // -----------------------------------------------------------------
            // Main methods
            // -----------------------------------------------------------------
            
            virtual status_type status() const = 0;
            virtual response& operator <<(status_type status) = 0;
            
            virtual bool are_headers_sent() const = 0;
            virtual const header_map& headers() const = 0;
            virtual response& operator <<(const header& hdr) = 0;
            virtual void send_headers() = 0;
            
            virtual const cookie_map& cookies() const = 0;
            virtual response& operator <<(const cookie& ck) = 0;
            
            virtual std::ostream& out() = 0;
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_RESPONSE_HPP_INCLUDED
