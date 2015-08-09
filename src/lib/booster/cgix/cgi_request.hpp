#ifndef BOOSTER_CGIX_CGI_REQUEST_HPP_INCLUDED
#define BOOSTER_CGIX_CGI_REQUEST_HPP_INCLUDED

#include <booster/cgix/request.hpp>
#include <booster/cgix/query.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: cgi_request
        // =====================================================================
        
        // The cgi_request class represents an HTTP request that the web server
        // sends to the application via the CGI gateway.
        
        class cgi_request : public request {
        public:
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            cgi_request();
            virtual ~cgi_request();
            
            // -----------------------------------------------------------------
            // Main methods
            // -----------------------------------------------------------------
            
            virtual std::string method() const;
            virtual std::string uri() const;
            virtual std::string query_string() const;
            virtual ci_string content_type() const;
            virtual std::string document_root() const;
            virtual std::string gateway_interface() const;
            virtual std::string path() const;
            virtual std::string path_ext() const;
            virtual std::string path_info() const;
            virtual std::string path_translated() const;
            virtual std::string remote_address() const;
            virtual uint16_t remote_port() const;
            virtual std::string script_filename() const;
            virtual std::string script_name() const;
            virtual std::string server_address() const;
            virtual uint16_t server_port() const;
            virtual std::string server_admin() const;
            virtual std::string server_name() const;
            virtual std::string server_protocol() const;
            virtual std::string server_signature() const;
            virtual std::string server_software() const;
            virtual uint64_t content_length() const;
            virtual std::istream& input_stream() const;
            virtual const query& get_query() const;
            virtual const header_map& headers() const;
            virtual const cookie_map& cookies() const;
            
        private:
            
            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
            query query_;
            header_map headers_;
            cookie_map cookies_;
            
        };
        
    }
}


#endif // #ifndef BOOSTER_CGIX_CGI_REQUEST_HPP_INCLUDED
