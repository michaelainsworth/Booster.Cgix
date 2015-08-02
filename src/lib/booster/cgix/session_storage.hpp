#ifndef BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED
#define BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED

#include <string>
#include <booster/cgix/error_condition.hpp>

namespace booster {
    namespace cgix {
        
        class session_storage {
        public:
            
            typedef std::string string_type;
            
            virtual ~session_storage() {};
            
            virtual string_type session_cookie_name() const {
                return "SESSION";
            }
            
            virtual bool has_session(const string_type& session_id) = 0;
            virtual bool is_session_expired(const string_type& session_id) = 0;
            virtual string_type generate_session_id() = 0;
            
            template<typename T>
            void load(const string_type& session_id, T& t);
            
            template<typename T>
            void save(const string_type& session_id, T& t);
            
        };
        
        template<typename T>
        void session_storage::load(const string_type& session_id, T& t) {
            throw std::system_error(error::implementation_required);
        }
        
        template<typename T>
        void session_storage::save(const string_type& session_id, T& t) {
            throw std::system_error(error::implementation_required);
        }
        
    }
}

#endif // #ifndef BOOSTER_CGIX_SESSION_STORAGE_HPP_INCLUDED
