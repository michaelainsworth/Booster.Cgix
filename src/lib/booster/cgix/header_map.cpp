#include <booster/cgix/header_map.hpp>
#include <booster/cgix/error_condition.hpp>
#include <unistd.h>
using namespace std;

extern "C" {
    extern char** environ;
}

namespace booster {
    namespace cgix {

        header_map::header_map() {
            // TODO: This should use Booster.Environment.
            typedef header_map::key_string_type key_string_type;
            typedef header_map::value_string_type value_string_type;
            
            size_t i = 0;
            while (environ && environ[i]) {
                value_string_type pair = environ[i];
                value_string_type::size_type pos = pair.find("=");
                key_string_type name;
                value_string_type value;
                
                if (value_string_type::npos == pos) {
                    name = key_string_type(pair.c_str(), pair.length());
                } else {
                    name = key_string_type(pair.c_str(), pos);
                    value = value_string_type(pair.c_str() + pos + 1);
                }
                
                if (name.find("HTTP_") == 0) {
                    key_string_type::size_type pos = name.find('_');
                    while (pos != key_string_type::npos) {
                        name[pos] = '-';
                        pos = name.find('_', pos + 1);
                    }
                    
                    headers_.insert(make_pair(name, value));
                }
            }
        }
        
        bool header_map::is_set(const key_string_type& name) const {
            return headers_.find(name) != headers_.end();
        }
        
        header_map::value_string_type header_map::get(const key_string_type& name) const {
            if (!is_set(name)) {
                throw system_error(static_cast<int>(error::http_header_not_set), get_error_category());
            }
            
            return headers_.find(name)->second;
        }
    
    }
}
