#ifndef BOOSTER_CGIX_ENVIRONMENT_HPP_INCLUDED
#define BOOSTER_CGIX_ENVIRONMENT_HPP_INCLUDED

#include <string>

namespace booster {
    namespace cgix {
        
        // =====================================================================
        // Class: environment
        // =====================================================================
        
        // The environment class is simply used to encapsulate access to
        // environment variables.
        //
        // This class is used by the cgi_request class in order to return
        // information sent to the application by the web server.
        
        class environment
        {
        public:
            
            static bool is_set(const std::string& name);
            static void unset(const std::string& name);
            static std::string get(const std::string& name);
            static void set(const std::string& name, const std::string& value);
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_ENVIRONMENT_HPP_INCLUDED
