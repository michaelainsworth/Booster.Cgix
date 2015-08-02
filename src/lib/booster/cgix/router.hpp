#ifndef BOOSTER_CGIX_ROUTER_HPP_INCLUDED
#define BOOSTER_CGIX_ROUTER_HPP_INCLUDED

#include <vector>
#include <type_traits>
#include <initializer_list>
#include <booster/cgix/connection.hpp>
#include <booster/cgix/request_method.hpp>
#include <booster/cgix/handler.hpp>
#include <booster/cgix/basic_route.hpp>
#include <regex>

namespace booster
{
    namespace cgix
    {
        
        class route;
        // TODO: Remove
        class condition{};
        
        class router {
        public:
            
//            router(const basic_route_ptr_vector& routes);
  
            template<typename T, typename... Args>
            route& on(Args... args);
            
            route& on(request_method method, const std::string& uri);
            route& on(request_method method, const std::regex& pattern);

        private:
            
            router(const router& rhs) = delete;
            router& operator =(const router& rhs) = delete;
            
//            basic_route_ptr_vector routes_;
            
            
        };
        
        template<typename T, typename... Args>
        route& router::on(Args... args) {
            static_assert(std::is_base_of<T, condition>::value, "The first template parameter to the `router::on()` method must be a class derived from `condition`.");
            
            // TODO: Save this in internal vector.
            T* t = new T(args...);
            return *t;
        }
        
    }
}


#endif // #ifndef BOOSTER_CGIX_ROUTER_HPP_INCLUDED

