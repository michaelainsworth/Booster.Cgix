#ifndef BOOSTER_CGIX_CONDITION_URI_REGEX_HPP_INCLUDED
#define BOOSTER_CGIX_CONDITION_URI_REGEX_HPP_INCLUDED

#include <booster/cgix/condition.hpp>
#include <regex>

namespace booster
{
    namespace cgix
    {
        
        class condition_uri_regex : public condition {
        public:
            
            condition_uri_regex(const std::regex& re);
            
            virtual bool operator ()(const request& request);
            
        private:
            std::regex re_;
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_CONDITION_URI_REGEX_HPP_INCLUDED

