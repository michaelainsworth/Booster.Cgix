#ifndef BOOSTER_CGIX_REQUEST_HPP_INCLUDED
#define BOOSTER_CGIX_REQUEST_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <booster/cgix/header_map.hpp>
#include <booster/cgix/cookie_map.hpp>
#include <booster/cgix/request_method.hpp>

namespace booster {
    namespace cgix {
        
        class request {
        public:
            
            // Lifecycle
            request();
            virtual ~request();
            
            // Basic informational methods
            virtual request_method method() const;
            virtual std::string method_string() const;
            virtual std::string uri() const;
            virtual std::string query_string() const;
            virtual std::string content_type() const;
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
            
            virtual const header_map& headers() const;
            virtual const cookie_map& cookies() const;
            
        private:
            
            // Private copy constructor.
            request(const request&) = delete;
            request& operator =(const request&) = delete;
            
            header_map headers_;
            cookie_map cookies_;
            
        };
        
    }
}


#endif // #ifndef BOOSTER_CGIX_REQUEST_HPP_INCLUDED
