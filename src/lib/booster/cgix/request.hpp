#ifndef BOOSTER_CGIX_REQUEST_HPP_INCLUDED
#define BOOSTER_CGIX_REQUEST_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <boost/noncopyable.hpp>
#include <booster/cgix/ci_string.hpp>
#include <booster/cgix/header_map.hpp>
#include <booster/cgix/cookie_map.hpp>

namespace booster {
    namespace cgix {
        
        class query;
        
        // =====================================================================
        // Class: request
        // =====================================================================
        
        // The request class represents an HTTP request.
        //
        // Each gateway (e.g., CGI, SCGI) should implement a class derived from
        // the request class.
        
        class request : private boost::noncopyable {
        public:
            
            // -----------------------------------------------------------------
            // Static members
            // -----------------------------------------------------------------
            
            // The members below represent the various HTTP request methods.
            // E.g., "GET", "POST", "PUT", etc.
            
            static const std::string get;
            static const std::string head;
            static const std::string post;
            static const std::string put;
            static const std::string delete_;
            static const std::string trace;
            static const std::string connect;
            static const std::string options;
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            // The destructor for the request class is pure virtual, as the
            // class is meant to be derived.
            
            virtual ~request() = 0;
            
            // -----------------------------------------------------------------
            // Main methods
            // -----------------------------------------------------------------
            
            // The methods below expose information about the request useful
            // for processing it.
            
            virtual std::string method() const = 0;
            virtual std::string uri() const = 0;
            virtual std::string query_string() const = 0;
            virtual ci_string content_type() const = 0;
            virtual std::string document_root() const = 0;
            virtual std::string gateway_interface() const = 0;
            virtual std::string path() const = 0;
            virtual std::string path_ext() const = 0;
            virtual std::string path_info() const = 0;
            virtual std::string path_translated() const = 0;
            virtual std::string remote_address() const = 0;
            virtual uint16_t remote_port() const = 0;
            virtual std::string script_filename() const = 0;
            virtual std::string script_name() const = 0;
            virtual std::string server_address() const = 0;
            virtual uint16_t server_port() const = 0;
            virtual std::string server_admin() const = 0;
            virtual std::string server_name() const = 0;
            virtual std::string server_protocol() const = 0;
            virtual std::string server_signature() const = 0;
            virtual std::string server_software() const = 0;
            virtual uint64_t content_length() const = 0;
            virtual std::istream& input_stream() const = 0;
            virtual const query& get_query() const = 0;
            virtual const header_map& headers() const = 0;
            virtual const cookie_map& cookies() const = 0;
            
        };
        
    }
}


#endif // #ifndef BOOSTER_CGIX_REQUEST_HPP_INCLUDED
