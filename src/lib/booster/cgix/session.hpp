#ifndef BOOSTER_CGIX_SESSION_HPP_INCLUDED
#define BOOSTER_CGIX_SESSION_HPP_INCLUDED

#include <string>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/cookie_map.hpp>
#include <booster/cgix/error_condition.hpp>

namespace booster {
    namespace cgix {
        
        class session_storage;
        
        template<typename T>
        class basic_session {
        public:
            
            typedef std::string string_type;
            typedef T  data_type;
            typedef T* pointer_type;
            typedef T& reference_type;
            
            
            // TODO: Add a constructor with default session storage (e.g., file_session_storage
            basic_session(connection& con, session_storage& storage);
            
            reference_type operator *();
            pointer_type operator ->();
            
        private:
            
            session_storage *storage_;
            data_type data_;
            
        };
        
        template<typename T>
        basic_session<T>::basic_session(connection& con, session_storage& storage)
            : storage_(&storage) {
            
                const request& req = con.request();
                const cookie_map& cookies = req.cookies();
                response& resp = con.response();
                
                if (resp.are_headers_sent()) {
                    throw std::system_error(error::http_headers_already_sent);
                }
                
                bool create_new_session = false;
                
                string_type session_cookie_name = storage_->session_cookie_name();
                
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
                    resp << cookie(session_cookie_name, session_id);
                } else {
                    storage_->load(data_);
                }
        }
        
        template<typename T>
        typename basic_session<T>::reference_type basic_session<T>::operator *() {
            return data_;
        }
        
        template<typename T>
        typename basic_session<T>::pointer_type basic_session<T>::operator ->() {
            return &data_;
        }

        
    }
}

#endif // #ifndef BOOSTER_CGIX_SESSION_HPP_INCLUDED
