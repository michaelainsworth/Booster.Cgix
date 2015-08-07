#include <booster/cgix/header_map.hpp>
#include <booster/cgix/error.hpp>
#include <unistd.h>
using namespace std;

extern "C" {
    extern char** environ;
}

namespace booster {
    namespace cgix {

        header_map::header_map() {
            size_t i = 0;
            while (environ && environ[i]) {
                value_string_type pair = environ[i];
                value_string_type::size_type pos = pair.find("=");
                name_string_type name;
                value_string_type value;
                
                if (value_string_type::npos == pos) {
                    name = name_string_type(pair.c_str(), pair.length());
                } else {
                    name = name_string_type(pair.c_str(), pos);
                    value = value_string_type(pair.c_str() + pos + 1);
                }
                
                if (name.find("HTTP_") == 0) {
                    name_string_type::size_type pos = name.find('_');
                    while (pos != name_string_type::npos) {
                        name[pos] = '-';
                        pos = name.find('_', pos + 1);
                    }
                    
                    headers_.insert(make_pair(name, value));
                }
                
                ++i;
            }
        }
        
        header_map::const_iterator header_map::begin() const {
            return headers_.begin();
        }
        
        header_map::const_iterator header_map::end() const {
            return headers_.end();
        }
        
        bool header_map::is_set(const name_string_type& name) const {
            return headers_.find(name) != headers_.end();
        }
        
        header_map::value_string_type header_map::get(const name_string_type& name) const {
            if (!is_set(name)) {
                throw system_error(static_cast<int>(error::http_header_not_set), get_error_category());
            }
            
            return headers_.find(name)->second;
        }
        
        void header_map::set(const name_string_type& name, const value_string_type& value) {
            headers_[name] = value;
        }
        
        void header_map::unset(const name_string_type& name) {
            map_type::iterator it = headers_.find(name), end = headers_.end();
            if (it != end) {
                headers_.erase(it);
            }
        }
    
    }
}
