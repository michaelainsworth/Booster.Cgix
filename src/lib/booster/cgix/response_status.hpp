#ifndef BOOSTER_CGIX_RESPONSE_STATUS_HPP_INCLUDED
#define BOOSTER_CGIX_RESPONSE_STATUS_HPP_INCLUDED

#include <string>

namespace booster
{
    namespace cgix
    {
        
        enum class response_status : unsigned short
        {
            continue_ = 100,
            switching_protocols = 101,
            ok = 200,
            created = 201,
            accepted = 202,
            non_authoritative_information = 203,
            no_content = 204,
            reset_content = 205,
            partial_content = 206,
            multiple_choices = 300,
            moved_permanently = 301,
            moved_temporarily = 302,
            see_other = 303,
            not_modified = 304,
            use_proxy = 305,
            unused = 306,
            temporary_redirect = 307,
            bad_request = 400,
            unauthorized = 401,
            payment_required = 402,
            forbidden = 403,
            not_found = 404,
            method_not_allowed = 405,
            not_acceptable = 406,
            proxy_authentication_required = 407,
            request_time_out = 408,
            conflict = 409,
            gone = 410,
            length_required = 411,
            precondition_failed = 412,
            request_entity_too_large = 413,
            request_uri_too_large = 414,
            unsupported_media_type = 415,
            requested_range_not_satisfiable = 416,
            expectation_failed = 417,
            internal_server_error = 500,
            not_implemented = 501,
            bad_gateway = 502,
            service_unavailable = 503,
            gateway_time_out = 504,
            http_version_not_supported = 505,
            unknown = 999
        };
            
        std::string response_status_to_string(response_status status);
        
        response_status string_to_response_status(const std::string& str);
        
    }
}
    
    
#endif // #ifndef BOOSTER_CGIX_RESPONSE_STATUS_HPP_INCLUDED
