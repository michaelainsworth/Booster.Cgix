#include "booster/cgix/request_method.hpp"

namespace booster
{
namespace cgix
{

std::string request_method_to_string(request_method method) {
    if (request_method::get == method) {
        return "GET";
    } else if (request_method::head == method) {
        return "HEAD";
    } else if (request_method::post == method) {
        return "POST";
    } else if (request_method::put == method) {
        return "PUT";
    } else if (request_method::delete_ == method) {
        return "DELETE";
    } else if (request_method::trace == method) {
        return "TRACE";
    } else if (request_method::connect == method) {
        return "CONNECT";
    } else if (request_method::options == method) {
        return "OPTIONS";
    } else {
        return "";
    }
}

request_method string_to_request_method(const std::string& str) {
    if ("GET" == str) {
        return request_method::get;
    } else if ("HEAD" == str) {
        return request_method::head;
    } else if ("POST" == str) {
        return request_method::post;
    } else if ("PUT" == str) {
        return request_method::put;
    } else if ("DELETE" == str) {
        return request_method::delete_;
    } else if ("TRACE" == str) {
        return request_method::trace;
    } else if ("CONNECT" == str) {
        return request_method::connect;
    } else if ("OPTIONS" == str) {
        return request_method::options;
    } else {
        return request_method::custom;
    }
}

}
}
