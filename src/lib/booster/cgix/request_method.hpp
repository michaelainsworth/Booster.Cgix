#ifndef BOOSTER_CGIX_REQUEST_METHOD_HPP_INCLUDED
#define BOOSTER_CGIX_REQUEST_METHOD_HPP_INCLUDED

#include <string>

namespace booster
{
namespace cgix
{

enum class request_method : char
{
    get,
    head,
    post,
    put,
    delete_,
    trace,
    connect,
    options,
    custom
};

std::string request_method_to_string(request_method method);

request_method string_to_request_method(const std::string& str);

}
}


#endif // #ifndef BOOSTER_CGIX_REQUEST_METHOD_HPP_INCLUDED
