#define BOOSTER_TEST_DYN_LINK
#define BOOSTER_TEST_MODULE session
#include <booster/test/unit_test.hpp>
#include <string>
#include "booster/cgix/request.hpp"
using namespace booster::cgix;

struct session_data
{
    unsigned int user_key = 0;
    unsigned int request_count = 0;
};

BOOSTER_AUTO_TEST_CASE(session)
{
    typedef session<session_data, std::string> my_session_type;
    
    my_session_type session
    {
        
    };
    
    
}
