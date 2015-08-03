#include "booster/cgix/request.hpp"
#include "booster/cgix/environment.hpp"

#include <iostream>

namespace booster
{
    namespace cgix
    {
        
        const std::string request::get("GET");
        const std::string request::head("HEAD");
        const std::string request::post("POST");
        const std::string request::put("PUT");
        const std::string request::delete_("DELETE");
        const std::string request::trace("TRACE");
        const std::string request::connect("CONNECT");
        const std::string request::options("OPTIONS");
        
        request::request() {
            std::string cookies_string = environment::get("HTTP_COOKIE");
            if (cookies_string.length()) {
                std::error_condition e = cookie_map::from_string(cookies_, cookies_string);
                
                if (!e) {
                    throw std::system_error(e.value(), e.category());
                }
            }
            
            // TODO: Refactor the parse_headers() call above.
        }
        
        std::string request::method() const {
            return environment::get("REQUEST_METHOD");
        }
        
        std::string request::uri() const {
            return environment::get("REQUEST_URI");
        }
        
        std::string request::query_string() const {
            return environment::get("QUERY_STRING");
        }
        
        ci_string request::content_type() const {
            std::string content_type = environment::get("CONTENT_TYPE");
            return ci_string(content_type.c_str(), content_type.length());
        }
        
        std::string request::document_root() const {
            return environment::get("DOCUMENT_ROOT");
        }
        
        std::string request::gateway_interface() const {
            return environment::get("GATEWAY_INTERFACE");
        }
        
        std::string request::path() const {
            return environment::get("PATH");
        }
        
        std::string request::path_ext() const {
            return environment::get("PATH_EXT");
        }
        
        std::string request::path_info() const {
            return environment::get("PATH_INFO");
        }
        
        std::string request::path_translated() const {
            return environment::get("PATH_TRANSLATED");
        }
        
        std::string request::remote_address() const {
            return environment::get("REMOTE_ADDR");
        }
        
        uint16_t request::remote_port() const {
            return (uint16_t)stoul(environment::get("REMOTE_PORT"));
        }
        
        std::string request::script_filename() const {
            return environment::get("SCRIPT_FILENAME");
        }
        
        std::string request::script_name() const {
            return environment::get("SCRIPT_NAME");
        }
        
        std::string request::server_address() const {
            return environment::get("SERVER_ADDRESS");
        }
        
        uint16_t request::server_port() const {
            return (uint16_t)stoul(environment::get("SERVER_PORT"));
        }
        
        std::string request::server_admin() const {
            return environment::get("SERVER_ADMIN");
        }
        
        std::string request::server_name() const {
            return environment::get("SERVER_NAME");
        }
        
        std::string request::server_protocol() const {
            return environment::get("SERVER_PROTOCOL");
        }
        
        std::string request::server_signature() const {
            return environment::get("SERVER_SIGNATURE");
        }
        
        std::string request::server_software() const {
            return environment::get("SERVER_SOFTWARE");
        }
        
        uint64_t request::content_length() const {
            return (uint64_t)stoull(environment::get("CONTENT_LENGTH"));
        }
        
        std::istream& request::input_stream() const {
            return std::cin;
        }
        
        const header_map& request::headers() const {
            return headers_;
        }
        
        const cookie_map& request::cookies() const {
            return cookies_;
        }
        
        
        
    }
}
