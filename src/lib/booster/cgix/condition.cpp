#include "booster/cgix/condition.hpp"

namespace booster
{
    namespace cgix
    {
        
        condition::~condition() {}
        
        bool condition::operator()(const booster::cgix::request& req) {
            return false;
        }
        
    }
}

