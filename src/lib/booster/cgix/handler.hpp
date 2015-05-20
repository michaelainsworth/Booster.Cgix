#ifndef BOOSTER_CGIX_HANDLER_HPP_INCLUDED
#define BOOSTER_CGIX_HANDLER_HPP_INCLUDED

namespace booster
{
    namespace cgix
    {
        
        class request;
        class response;
        
        class handler {
        public:
            
            virtual ~handler();
            virtual void handle_request(const request& request, response& response) = 0;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_HANDLER_HPP_INCLUDED

