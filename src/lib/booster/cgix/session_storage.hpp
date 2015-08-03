#ifndef BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED
#define BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED

#include <string>
#include <booster/cgix/error.hpp>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: session_storage
        // =====================================================================
        
        // The session_storage class is a base template class that is
        // responsible for managing sessions, including:
        //
        // - determining if a session exists.
        // - determining if an existing session has been expired.
        // - generating session IDs
        //
        // Note that the session_storage class is NOT responsible for encoding
        // and decoding the session object itself. The boost serialization
        // library is responsible for this. The A template parameter represents
        // the boost serialization archive type (e.g., a binary archive or a
        // text archive).
        
        class session_storage {
        public:
            
            // -----------------------------------------------------------------
            // Typedefs
            // -----------------------------------------------------------------
            
            typedef std::string string_type;
            
            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            virtual ~session_storage() {};
            
            // -----------------------------------------------------------------
            // Session ID functions
            // -----------------------------------------------------------------
            
            // The session_cookie_name() function returns a string to be used to
            // identify session cookies. This method does not need to be
            // overridden by base classes.
            
            virtual string_type session_cookie_name() const {
                return "SESSION";
            }
            
            // The generate_session_id() function must be implemented by derived
            // classes in order to generate new session IDs.
            //
            // Note that this method does not need to generate a unique session
            // ID, as the calling code will test it's existance by calling the
            // has_session() function.
            
            virtual string_type generate_session_id() = 0;
            
            // The is_session_id_valid() function must be implemented by derived
            // classes in order to determine if a session ID is valid.
            //
            // The reason this method exists is that the web browser could send
            // a phony session ID in order to exploit vulnerabilities. E.g., if
            // a file-based session_storage object is used, and session files
            // are stored in the `/tmp` directory, then the user could specify
            // a session of `../passwd` in an attemp to read the contents of the
            // password file. This function is a protection against such
            // attempts.
            
            virtual bool is_session_id_valid(const string_type& session_id) = 0;
            
            // -----------------------------------------------------------------
            // Session management functions
            // -----------------------------------------------------------------
            
            // The has_session() function must be implemented by derived classes
            // in order to determine whether the session ID specified exists in
            // the storage.
            //
            // Note that this function does not need to determine whether the
            // session has expired, only that it exists.
            
            virtual bool has_session(const string_type& session_id) = 0;
            
            // The is_session_expired() function must be implemented by derived
            // classes in order to determine whether the session ID specified
            // has expired.
            //
            // Note that this function will only be called when has_session()
            // returns true.
            
            virtual bool is_session_expired(const string_type& session_id) = 0;
            
            // -----------------------------------------------------------------
            // Session serialization functions
            // -----------------------------------------------------------------
            
            template<typename T>
            void load(const string_type& session_id, T& t);
            
            template<typename T>
            void save(const string_type& session_id, T& t);
            
        };
        
        template<typename T>
        void session_storage::load(const string_type& session_id, T& t) {
            // TODO: Use session_traits for serialization and deserialization.
            throw std::system_error(error::implementation_required);
        }
        
        template<typename T>
        void session_storage::save(const string_type& session_id, T& t) {
            throw std::system_error(error::implementation_required);
        }
        
    }
}

#endif // #ifndef BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED
