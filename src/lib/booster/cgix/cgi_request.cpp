#include <booster/cgix/cgi_request.hpp>
#include <booster/cgix/environment.hpp>
#include <iostream>

namespace booster {
    namespace cgix {
        
        cgi_request::cgi_request() {
            std::string cookies_string = environment::get("HTTP_COOKIE");
            if (cookies_string.length()) {
                std::error_condition e = cookie_map::from_string(cookies_, cookies_string);
                
                if (!e) {
                    throw std::system_error(e.value(), e.category());
                }
            }
            
            // TODO: Refactor the parse_headers() call above.
        }
        
        std::string cgi_request::method() const {
            return environment::get("REQUEST_METHOD");
        }
        
        std::string cgi_request::uri() const {
            return environment::get("REQUEST_URI");
        }
        
        std::string cgi_request::query_string() const {
            return environment::get("QUERY_STRING");
        }
        
        ci_string cgi_request::content_type() const {
            std::string content_type = environment::get("CONTENT_TYPE");
            return ci_string(content_type.c_str(), content_type.length());
        }
        
        std::string cgi_request::document_root() const {
            return environment::get("DOCUMENT_ROOT");
        }
        
        std::string cgi_request::gateway_interface() const {
            return environment::get("GATEWAY_INTERFACE");
        }
        
        std::string cgi_request::path() const {
            return environment::get("PATH");
        }
        
        std::string cgi_request::path_ext() const {
            return environment::get("PATH_EXT");
        }
        
        std::string cgi_request::path_info() const {
            return environment::get("PATH_INFO");
        }
        
        std::string cgi_request::path_translated() const {
            return environment::get("PATH_TRANSLATED");
        }
        
        std::string cgi_request::remote_address() const {
            return environment::get("REMOTE_ADDR");
        }
        
        uint16_t cgi_request::remote_port() const {
            return (uint16_t)stoul(environment::get("REMOTE_PORT"));
        }
        
        std::string cgi_request::script_filename() const {
            return environment::get("SCRIPT_FILENAME");
        }
        
        std::string cgi_request::script_name() const {
            return environment::get("SCRIPT_NAME");
        }
        
        std::string cgi_request::server_address() const {
            return environment::get("SERVER_ADDRESS");
        }
        
        uint16_t cgi_request::server_port() const {
            return (uint16_t)stoul(environment::get("SERVER_PORT"));
        }
        
        std::string cgi_request::server_admin() const {
            return environment::get("SERVER_ADMIN");
        }
        
        std::string cgi_request::server_name() const {
            return environment::get("SERVER_NAME");
        }
        
        std::string cgi_request::server_protocol() const {
            return environment::get("SERVER_PROTOCOL");
        }
        
        std::string cgi_request::server_signature() const {
            return environment::get("SERVER_SIGNATURE");
        }
        
        std::string cgi_request::server_software() const {
            return environment::get("SERVER_SOFTWARE");
        }
        
        uint64_t cgi_request::content_length() const {
            return (uint64_t)stoull(environment::get("CONTENT_LENGTH"));
        }
        
        std::istream& cgi_request::input_stream() const {
            return std::cin;
        }
        
        const header_map& cgi_request::headers() const {
            return headers_;
        }
        
        const cookie_map& cgi_request::cookies() const {
            return cookies_;
        }
        
        
        
    }
}
