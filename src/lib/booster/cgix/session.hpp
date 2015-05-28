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
            data_type data_;
            
        };
        
        template<typename T, const char* SessionCookieName>
        session<T,SessionCookieName>::session(connection& con, session_storage& storage)
            : storage_(&storage) {
            
                const request& req = con.request();
                cookie_map& cookies = request.cookies();
                response& resp = con.response();
                
                if (resp.are_headers_sent()) {
                    throw std::system_error(error::http_headers_already_sent, get_error_category());
                }
                
                bool create_new_session = false;
                
                if (!cookies.is_set(session_cookie_name)) {
                    create_new_session = true;
                } else {
                    string_type session_id = cookies.get(session_cookie_name);
                    if (!storage_->has_session(session_id)) {
                        create_new_session = true;
                    } else {
                        if (storage_->is_session_expired(session_id)) {
                            create_new_session = true;
                        }
                    }
                }
                
                if (create_new_session) {
                    string_type session_id = storage_->generate_session_id();
                    response << cookie(session_cookie_name, session_id);
                } else {
                    storage_->load(t_);
                }
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
