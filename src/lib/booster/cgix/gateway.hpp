#ifndef BOOSTER_CGIX_GATEWAY_HPP_INCLUDED
#define BOOSTER_CGIX_GATEWAY_HPP_INCLUDED

#include <booster/cgix/error_condition.hpp>
#include <booster/cgix/connection.hpp>

namespace booster
{
    namespace cgix
    {
        
        class gateway {
        public:
            
            virtual ~gateway();
            
            virtual bool get_connection(connection& con);
            
        private:
            
            gateway(const gateway& rhs) = delete;
            gateway& operator =(const gateway& rhs) = delete;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_GATEWAY_HPP_INCLUDED
