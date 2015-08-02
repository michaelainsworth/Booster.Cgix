#ifndef BOOSTER_CGIX_APPLICATION_HPP_INCLUDED
#define BOOSTER_CGIX_APPLICATION_HPP_INCLUDED

#include <vector>
#include <booster/cgix/gateway.hpp>
#include <booster/cgix/router.hpp>

namespace booster
{
    namespace cgix
    {
        
        class application {
        public:
            
            typedef std::vector<basic_route*> basic_route_ptr_vector;
            
            application(gateway& gw);
            virtual ~application() = 0;
            
            virtual void run();
            
        protected:
            
            virtual basic_route* connect(request_method method, const std::string& request_uri);

            virtual basic_route_ptr_vector get_routes() = 0;
            virtual void request_unhandled(connection& con) = 0;
            
            gateway& gw_;
            
        private:
            
            application(const application& rhs) = delete;
            application& operator =(const application& rhs) = delete;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_APPLICATION_HPP_INCLUDED
