#include "booster/cgix/condition_uri_regex.hpp"
#include "booster/cgix/request.hpp"

namespace booster
{
namespace cgix
{

condition_uri_regex::condition_uri_regex(const std::regex& re) : re_ { re } {}

bool condition_uri_regex::operator ()(const request& request) {
    return std::regex_match(request.uri(), re_);
}

}
}

