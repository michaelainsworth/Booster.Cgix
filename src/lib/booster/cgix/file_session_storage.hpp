#ifndef BOOSTER_CGIX_FILE_SESSION_STORAGE_HPP_INCLUDED
#define BOOSTER_CGIX_FILE_SESSION_STORAGE_HPP_INCLUDED

#include <booster/cgix/session_storage.hpp>
#include <fstream>
#include <cassert>

namespace booster {
    namespace cgix {
        
        class file_session_storage : public session_storage {
        public:
            
            // TODO: Timeout.
            file_session_storage(const string_type& directory, const string_type& file_prefix, double timeout_in_seconds);
            virtual ~file_session_storage();
            
            virtual bool has_session(const string_type& session_id);
            virtual bool is_session_expired(const string_type& session_id);
            virtual string_type generate_session_id();
            
            template<typename T>
            void load(const string_type& session_id, T& t);
            
            template<typename T>
            void save(const string_type& session_id, T& t);
            
        private:
            
            string_type dir_, prefix_;
            double timeout_;
            
        };
        
        template<typename T>
        void file_session_storage::load(const string_type& session_id, T& t) {
            // TODO: Consistent use of asserts.
            assert(has_session(session_id) && !is_session_expired(session_id));
            
            std::ifstream fin(string_type(dir_ + "/" + prefix_ + session_id).c_str());
            fin.read(static_cast<char*>(&t), sizeof(t));
        }
        
        template<typename T>
        void file_session_storage::save(const string_type& session_id, T& t) {
            std::ofstream fout(string_type(dir_ + "/" + prefix_ + session_id).c_str());
            fout.write(static_cast<char*>(&t), sizeof(t));
        }
        
    }
}

#endif // #ifndef BOOSTER_CGIX_FILE_SESSION_STORAGE_HPP_INCLUDED
