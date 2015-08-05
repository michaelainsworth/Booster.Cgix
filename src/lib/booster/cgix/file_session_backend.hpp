#ifndef BOOSTER_CGIX_FILE_SESSION_BACKEND_HPP_INCLUDED
#define BOOSTER_CGIX_FILE_SESSION_BACKEND_HPP_INCLUDED

#include <booster/cgix/session_backend.hpp>
#include <fstream>
#include <cassert>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: file_session_backend
        // =====================================================================
        
        // The file_session_backend class is used to save and load session data
        // from the filesystem.
        
        class file_session_backend : public session_backend {
        public:

            // -----------------------------------------------------------------
            // Lifecycle
            // -----------------------------------------------------------------
            
            // The various constructors takes a timeout for session lifetimes,
            // a prefix for sessions (e.g., "myapp_sess_") and a directory in
            // which the session files are located (e.g., "/tmp").
            //
            // If the timeout_in_seconds is less than or equal to 0, then
            // sessions do not timeout. The default is 3600.
            //
            // If the file prefix is not specified, a value of "cpp_sess_" is
            // used.
            //
            // If a directory is not specified, it defaults to "/tmp".
            
            file_session_backend();
            
            file_session_backend(double timeout_in_seconds);
            
            file_session_backend(double timeout_in_seconds,
                                 const string_type& file_prefix);
            
            file_session_backend(double timeout_in_seconds,
                                 const string_type& file_prefix,
                                 const string_type& directory);
            
            virtual ~file_session_backend();
            
            // -----------------------------------------------------------------
            // Session ID functions
            // -----------------------------------------------------------------
            
            // Session IDs generated from the file_session_backend class are
            // 32 characters long and consist of the characters a-z (lowercase)
            // and 0-9.
            
            virtual string_type generate_session_id();
            
            virtual bool is_session_id_valid(const string_type& session_id);
            
            // -----------------------------------------------------------------
            // Session management functions
            // -----------------------------------------------------------------
            
            virtual bool has_session(const string_type& session_id);
            
            virtual bool is_session_expired(const string_type& session_id);
            
            // -----------------------------------------------------------------
            // Session saving/loading functions
            // -----------------------------------------------------------------
            
            virtual encoded_type
            load_encoded_session(const string_type& session_id);
            
            virtual void save_encoded_session(const string_type& session_id,
                                              const encoded_type& encoded);

            // -----------------------------------------------------------------
            // Variables
            // -----------------------------------------------------------------
            
        private:
            
            double timeout_;
            string_type prefix_, dir_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_FILE_SESSION_BACKEND_HPP_INCLUDED
