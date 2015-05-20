#ifndef BOOSTER_CGIX_CONDITION_HPP_INCLUDED
#define BOOSTER_CGIX_CONDITION_HPP_INCLUDED

namespace booster {
    namespace cgix {
        
        class request;
        
        // TODO: Put common conditions in here.
        
        class condition
        {
        public:
            
            virtual ~condition();
            virtual bool operator ()(const request& request) = 0;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_CONDITION_HPP_INCLUDED

