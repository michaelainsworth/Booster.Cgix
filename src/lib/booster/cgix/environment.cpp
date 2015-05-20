#include "booster/cgix/environment.hpp"
#include <cstdlib>

using namespace std;

namespace booster
{
    namespace cgix
    {
        
        bool environment::is_set(const std::string& name){
            const char *e = getenv(name.c_str());
            return e ? true : false;
        }
        
        void environment::unset(const std::string& name) {
            unsetenv(name.c_str());
        }
        
        std::string environment::get(const std::string& name){
            const char *e = getenv(name.c_str());
            return e ? string(e) : "";
        }
        
        void environment::set(const std::string& name, const std::string& value){
            
            setenv(name.c_str(), value.c_str(), true);
        }
        
    }
}

