#include <booster/cgix/file_session_backend.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>

#define SESSION_CHARS "abcdefghijklmnopqrstuvwxyz0123456789"
#define SESSION_LENGTH 32

namespace booster {
    namespace cgix {
        
        namespace fs = boost::filesystem;
        
        void constructor_test(const std::string& dir) {
            if (!fs::exists(dir)) {
                fs::create_directories(dir);
            } else if (!fs::is_directory(dir)) {
                throw std::system_error(error::session_file_directory_invalid);
            }
        }
        
        file_session_backend::file_session_backend() :
        timeout_(3600), prefix_(""), dir_("/tmp") {
            constructor_test(dir_);
        }

        file_session_backend::file_session_backend(double timeout_in_seconds) :
        timeout_(timeout_in_seconds), prefix_(""), dir_("/tmp") {
            constructor_test(dir_);
        }
        
        file_session_backend::file_session_backend
        (double timeout_in_seconds,
         const string_type& file_prefix
         ) : timeout_(timeout_in_seconds), prefix_(file_prefix), dir_("/tmp") {
            constructor_test(dir_);
        }
        
        file_session_backend::file_session_backend
        (double timeout_in_seconds,
         const string_type& file_prefix,
         const string_type& directory
         ) : timeout_(timeout_in_seconds), prefix_(file_prefix), dir_(directory) {
            constructor_test(dir_);
        }
        
        // -----------------------------------------------------------------
        // Session ID functions
        // -----------------------------------------------------------------
        
        file_session_backend::string_type file_session_backend::generate_session_id() {
            string_type chars = SESSION_CHARS;
            string_type session_id;
            std::srand(std::time(NULL));
            
            for (size_t i = 0, s = SESSION_LENGTH, r = chars.length(); i < s; ++i) {
                int pos = std::rand() % r;
                session_id += chars[pos];
            }
            
            return session_id;
        }
        
        bool file_session_backend
        ::is_session_id_valid(const string_type& session_id) {
            size_t s = session_id.size();
            if (s != SESSION_LENGTH) {
                return false;
            }
            
            string_type chars = SESSION_CHARS;
            for (size_t i = 0; i < s; ++i) {
                if (string_type::npos == chars.find(session_id[i])) {
                    return false;
                }
            }
            
            return true;
        }
        
        // -----------------------------------------------------------------
        // Session management functions
        // -----------------------------------------------------------------
        
        bool file_session_backend
        ::has_session(const string_type& session_id) {
            fs::path p(dir_ + "/" + prefix_ + session_id);
            return fs::exists(p) && fs::is_regular_file(p);
        }
        
        bool file_session_backend
        ::is_session_expired(const string_type& session_id) {
            fs::path p(dir_ + "/" + prefix_ + session_id);
            
            std::time_t last_updated = fs::last_write_time(p);
            std::time_t now = std::time(NULL);
            double diff = difftime(now, last_updated);
            return diff > timeout_;
        }
        
        // -----------------------------------------------------------------
        // Session saving/loading functions
        // -----------------------------------------------------------------
        
        file_session_backend::encoded_type file_session_backend
        ::load_encoded_session(const string_type& session_id) {
            string_type path(dir_ + "/" + prefix_ + session_id);
            std::ifstream fin(path.c_str());
            std::ios::pos_type pos;
            fin.seekg(0, std::ios::end);
            pos = fin.tellg();
            std::vector<char> data;
            data.reserve(pos);
            fin.seekg(0, std::ios::beg);
            fin.read(&data[0], pos);
            fin.close();
            
            return encoded_type(&data[0], pos);
        }
        
        void file_session_backend
        ::save_encoded_session(const string_type& session_id,
                               const encoded_type& encoded) {
            string_type path(dir_ + "/" + prefix_ + session_id);
            std::ofstream fout(path.c_str());
            fout.write(encoded.c_str(), encoded.length());
            fout.close();
        }
        
    }
}
