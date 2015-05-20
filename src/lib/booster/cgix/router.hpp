#ifndef BOOSTER_CGIX_ROUTER_HPP_INCLUDED
#define BOOSTER_CGIX_ROUTER_HPP_INCLUDED

#include <vector>
#include <initializer_list>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/route.hpp>

namespace booster
{
    namespace cgix
    {
        
        class router {
        public:
            
            typedef std::vector<basic_route*> route_vector;
            
            router(const std::initializer_list<basic_route*> routes);
            
            bool delegate(connection& con);
            
        private:
            
            router(const router& rhs) = delete;
            router& operator =(const router& rhs) = delete;
            
            route_vector routes_;
            
            
        };
        
    }
}


#endif // #ifndef BOOSTER_CGIX_ROUTER_HPP_INCLUDED

