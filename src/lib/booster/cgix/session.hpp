#ifndef BOOSTER_CGIX_SESSION_HPP_INCLUDED
#define BOOSTER_CGIX_SESSION_HPP_INCLUDED

#include <string>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/cookie_map.hpp>
#include <booster/cgix/error.hpp>
#include <booster/cgix/session_backend.hpp>
#include <booster/cgix/request.hpp>
#include <booster/cgix/response.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Functions
        // =====================================================================
        
        // The encode_session_data() template function returns a string
        // encoding of the session data specified.
        //
        // The default implementation throws a std::system_error, as this
        // function should be specialised for the session data type being
        // encoded.
        
        template<typename T>
        session_backend::encoded_type encode_session_data(const T& data) {
            throw std::system_error(error::implementation_required);
        }

        // The decode_session_data() template function returns a programmer-
        // defined data type from a string encoding.
        //
        // The default implementation throws a std::system_error, as this
        // function should be specialised for the session data type being
        // decoded.
        
        template<typename T>
        T decode_session_data(const session_backend::encoded_type& encoded) {
            throw std::system_error(error::implementation_required);
        }
        
        // =====================================================================
        // Class: session
        // =====================================================================
        
        // The session template class is a container for programmer-defined
        // session data.
        //
        // The programmer-defined session data is typically a struct with public
        // members. The members of the object can be accessed using the star
        // operator and arrow operator (* and ->).
        //
        // The session class should not be derived. Rather, it should be used
        // purely as a container.
        //
        // Note that the saving and loading of session objects is not performed
        // by the session class itself, but rather by a session_backend object
        // passed in the constructor. This allows different backends (e.g., a
        // filesystem or an SQL database) to be used as appropriate.
        //
        // The lifetime of the session_backend object must exceed that of the
        // session object.
        
        template<typename T>
        class session {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::string session_id_type;
            typedef T  data_type;
            typedef T& reference_type;
            typedef T* pointer_type;

            // -----------------------------------------------------------------
            // Constructor
            // -----------------------------------------------------------------
            
            // The constructor uses the session_backend object to determine
            // whether the connection object contains a cookie identifying a
            // valid session, and if so, loads the session.
            
            session(connection& con, session_backend& backend);
            
            // -----------------------------------------------------------------
            // Persistence
            // -----------------------------------------------------------------
            
            // The save() function calls session_traits<T>::to_string() to
            // encode the session data as a string. It then calls the save()
            // function on the session_backend object in order to persist the
            // session to permanent backend.
            
            void save();
            
            // -----------------------------------------------------------------
            // Accessors
            // -----------------------------------------------------------------
            
            // The session_id() function returns the ID for the session.
            
            session_id_type session_id() const;
            
            // -----------------------------------------------------------------
            // Data accessors
            // -----------------------------------------------------------------
            
            // The star operator returns a reference to the session data.
            
            reference_type operator *();
            
            // The pointer operator returns the address of the session data.
            
            pointer_type operator ->();

            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
        private:
            
            session_id_type session_id_;
            session_backend& backend_;
            data_type data_;
            
        };
        
        // =====================================================================
        // Implementation: session
        // =====================================================================
        
        template<typename T>
        session<T>::session(connection& con, session_backend& backend)
            : backend_(backend) {
            
                const request& req = con.get_request();
                const cookie_map& cookies = req.cookies();
                response& resp = con.get_response();
                
                if (resp.are_headers_sent()) {
                    throw std::system_error(error::http_headers_already_sent);
                }
                
                bool create_new_session = false;
                
                std::string session_cookie_name = backend_.session_cookie_name();
                
                if (!cookies.is_set(session_cookie_name)) {
                    create_new_session = true;
                } else {
                    session_id_ = cookies.get(session_cookie_name);
                    if (!backend_.is_session_id_valid(session_id_)) {
                        create_new_session = true;
                    } else {
                        if (!backend_.has_session(session_id_)) {
                            create_new_session = true;
                        } else {
                            if (backend_.is_session_expired(session_id_)) {
                                create_new_session = true;
                            }
                        }
                    }
                }
                
                if (create_new_session) {
                    session_id_ = backend_.generate_session_id();
                    while (backend_.has_session(session_id_)) {
                        session_id_ = backend_.generate_session_id();
                    }
                    
                    resp << cookie(session_cookie_name, session_id_);
                } else {
                    session_backend::encoded_type encoded;
                    encoded = backend_.load_encoded_session(session_id_);
                    data_ = decode_session_data<T>(encoded);
                }
        }
        
        template<typename T>
        void session<T>::save() {
            session_backend::encoded_type encoded;
            encoded = encode_session_data(data_);
            
            backend_.save_encoded_session(session_id_, encoded);
        }
        
        template<typename T>
        typename session<T>::session_id_type session<T>::session_id() const {
            return session_id_;
        }
        
        template<typename T>
        typename session<T>::reference_type session<T>::operator *() {
            return data_;
        }
        
        template<typename T>
        typename session<T>::pointer_type session<T>::operator ->() {
            return &data_;
        }

        
    }
}

#endif // #ifndef BOOSTER_CGIX_SESSION_HPP_INCLUDED
