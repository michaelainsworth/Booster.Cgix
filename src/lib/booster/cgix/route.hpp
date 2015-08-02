#ifndef BOOSTER_CGIX_ROUTE_HPP_INCLUDED
#define BOOSTER_CGIX_ROUTE_HPP_INCLUDED

#include <booster/cgix/connection.hpp>
#include <booster/cgix/request_method.hpp>
#include <type_traits>

namespace booster {
    namespace cgix {
        
        class basic_route {
        public:
            
            virtual ~basic_route();
            virtual bool handle_if_match(connection& con) = 0;
            
        };
     
        template<typename C, typename H>
        class route {
        public:
            
            typedef C condition_type;
            typedef H handler_type;
            
            route(condition_type condition, handler_type handler);
            virtual ~route();
            
            virtual bool handle_if_match(connection& con) const;
            
        protected:
            
            condition_type condition_;
            handler_type handler_;
            
        };
        
        template<typename C, typename H>
        route<C,H>::route(condition_type condition, handler_type handler) :
            condition_(condition), handler_(handler) {}
        
        template<typename C, typename H>
        route<C,H>::~route() {}
        
        template<typename C, typename H>
        bool route<C,H>::handle_if_match(connection& con) const {
            if (condition_(con.request())) {
                handler_(con);
                return true;
            }
            
            return false;
        }
        
    }
}

#endif // #ifndef BOOSTER_CGIX_ROUTE_HPP_INCLUDED
