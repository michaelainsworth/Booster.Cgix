#ifndef BOOSTER_CGIX_SESSION_HPP_INCLUDED
#define BOOSTER_CGIX_SESSION_HPP_INCLUDED

#include <string>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/cookie_map.hpp>
#include <booster/cgix/error_condition.hpp>

namespace booster {
    namespace cgix {
        
        static const char* default_session_cookie_name;
        
        class session_storage;
        
        template<typename T, const char* SessionCookieName = default_session_cookie_name>
        class session {
        public:
            
            typedef T data_type;
            typedef std::string string_type;
            static const char* session_cookie_name = SessionCookieName;
            
            // TODO: Add a constructor with default session storage (e.g., file_session_storage
            session(connection& con, session_storage& storage);
            
            T& operator *();
            T* operator ->();
            
        private:
            
            session_storage *storage_;
            T t_;
            
        };
        
        template<typename T, const char* SessionCookieName>
        session<T,SessionCookieName>::session(connection& con, session_storage& storage)
            : storage_(&storage) {
                
                // TODO: If response headers already sent, throw!
            
                const request& req = con.request();
                cookie_map& cookies = request.cookies();
                response& resp = con.response();
                
                if (resp.are_headers_sent()) {
                    throw std::system_error(error::http_headers_already_sent, get_error_category());
                }
                
                if (!cookies.is_set(session_cookie_name)) {
                    string_type session_id = storage_->generate_session_id(session_cookie_name);
                    response << cookie(session_cookie_name, session_id);
                }
                //cookie_map::string_type
        }
        
        template<typename T, const char* SessionCookieName>
        T* session<T,SessionCookieName>::operator ->() {
            return &t_;
        }
        
        template<typename T, const char* SessionCookieName>
        T& session<T,SessionCookieName>::operator ->() {
            return &t_;
        }

        
    }
}

#endif // #ifndef BOOSTER_CGIX_SESSION_HPP_INCLUDED
