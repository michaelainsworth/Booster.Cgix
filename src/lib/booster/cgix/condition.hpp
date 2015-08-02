#ifndef BOOSTER_CGIX_CONDITION_HPP_INCLUDED
#define BOOSTER_CGIX_CONDITION_HPP_INCLUDED

namespace booster {
    namespace cgix {
        
        class request;

        class condition
        {
        public:
            
            virtual ~condition() = 0;
            virtual bool operator ()(const request& request);
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_CONDITION_HPP_INCLUDED

