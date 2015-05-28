#include <booster/cgix/file_session_storage.hpp>
#include <boost/filesystem.hpp>

namespace booster {
    namespace cgix {
        
        namespace fs = boost::filesystem;
        
        // TODO: Finish this file.
        
        file_session_storage::file_session_storage(const string_type& directory, const string_type& file_prefix, double timeout_in_seconds) : dir_(directory), prefix_(file_prefix), timeout_(timeout_in_seconds) {
            fs::path path(dir_);
            if (!fs::exists(dir_) || !fs::is_directory(dir_)) {
                throw std::system_error(error::session_file_directory_invalid);
            }
        }
        
        file_session_storage::~file_session_storage() {}
        
        bool file_session_storage::has_session(const string_type& session_id) {
            fs::path p(dir_ + "/" + prefix_ + session_id);
            return fs::exists(p) && fs::is_regular_file(p);
        }
        
        bool file_session_storage::is_session_expired(const string_type& session_id) {
            fs::path p(dir_ + "/" + prefix_ + session_id);
            std::time_t last_updated = fs::last_write_time(p);
            std::time_t now = std::time(NULL);
            double diff = difftime(now, last_updated);
            return diff > timeout_;
        }
        
        file_session_storage::string_type file_session_storage::generate_session_id() {
            string_type chars("abcdefghijklmnopqrstuvwxyz0123456789");
            string_type session_id;
            std::srand(std::time(0));
            
            while (true) {
                session_id = "";
                
                for (string_type::size_type i = 0, l = chars.length(), max = 16; i < max; ++i) {
                    int rand = std::rand() % l;
                    session_id += chars.substr(rand, 1);
                }
                
                fs::path p(dir_ + "/" + prefix_ + session_id);
                if (!fs::exists(p)) {
                    break;
                }
            }
            
            return session_id;
        }
        
    }
}
