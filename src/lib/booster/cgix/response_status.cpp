#include "booster/cgix/response_status.hpp"

namespace booster
{
    namespace cgix
    {
        
        std::string response_status_to_string(response_status status) {
            if (response_status::continue_ == status) {
                return "Continue";
            } else if (response_status::switching_protocols == status) {
                return "Switching Protocols";
            } else if (response_status::ok == status) {
                return "OK";
            } else if (response_status::created == status) {
                return "Created";
            } else if (response_status::accepted == status) {
                return "Accepted";
            } else if (response_status::non_authoritative_information == status) {
                return "Non-Authoritative Information";
            } else if (response_status::no_content == status) {
                return "No Content";
            } else if (response_status::reset_content == status) {
                return "Reset Content";
            } else if (response_status::partial_content == status) {
                return "Partial Content";
            } else if (response_status::multiple_choices == status) {
                return "Multiple Choices";
            } else if (response_status::moved_permanently == status) {
                return "Moved Permanently";
            } else if (response_status::moved_temporarily == status) {
                return "Moved Temporarily";
            } else if (response_status::see_other == status) {
                return "See Other";
            } else if (response_status::not_modified == status) {
                return "Not Modified";
            } else if (response_status::use_proxy == status) {
                return "Use Proxy";
            } else if (response_status::unused == status) {
                return "Unused";
            } else if (response_status::temporary_redirect == status) {
                return "Temporary Redirect";
            } else if (response_status::bad_request == status) {
                return "Bad Request";
            } else if (response_status::unauthorized == status) {
                return "Unauthorized";
            } else if (response_status::payment_required == status) {
                return "Payment Required";
            } else if (response_status::forbidden == status) {
                return "Forbidden";
            } else if (response_status::not_found == status) {
                return "Not Found";
            } else if (response_status::method_not_allowed == status) {
                return "Method Not Allowed";
            } else if (response_status::not_acceptable == status) {
                return "Not Acceptable";
            } else if (response_status::proxy_authentication_required == status) {
                return "Proxy Authentication Required";
            } else if (response_status::request_time_out == status) {
                return "Request Time-out";
            } else if (response_status::conflict == status) {
                return "Conflict";
            } else if (response_status::gone == status) {
                return "Gone";
            } else if (response_status::length_required == status) {
                return "Length Required";
            } else if (response_status::precondition_failed == status) {
                return "Precondition Failed";
            } else if (response_status::request_entity_too_large == status) {
                return "Request Entity Too Large";
            } else if (response_status::request_uri_too_large == status) {
                return "Request-URI Too Large";
            } else if (response_status::unsupported_media_type == status) {
                return "Unsupported Media Type";
            } else if (response_status::requested_range_not_satisfiable == status) {
                return "Requested Range Not Satisfiable";
            } else if (response_status::expectation_failed == status) {
                return "Expectation Failed";
            } else if (response_status::internal_server_error == status) {
                return "Internal Server Error";
            } else if (response_status::not_implemented == status) {
                return "Not Implemented";
            } else if (response_status::bad_gateway == status) {
                return "Bad Gateway";
            } else if (response_status::service_unavailable == status) {
                return "Service Unavailable";
            } else if (response_status::gateway_time_out == status) {
                return "Gateway Time-out";
            } else if (response_status::http_version_not_supported == status) {
                return "HTTP Version not supported";
            } else {
                return "";
            }
        }
        
        
        response_status string_to_response_status(const std::string& str) {
            if ("Continue" == str) {
                return response_status::continue_;
            } else if ("Switching Protocols" == str) {
                return response_status::switching_protocols;
            } else if ("OK" == str) {
                return response_status::ok;
            } else if ("Created" == str) {
                return response_status::created;
            } else if ("Accepted" == str) {
                return response_status::accepted;
            } else if ("Non-Authoritative Information" == str) {
                return response_status::non_authoritative_information;
            } else if ("No Content" == str) {
                return response_status::no_content;
            } else if ("Reset Content" == str) {
                return response_status::reset_content;
            } else if ("Partial Content" == str) {
                return response_status::partial_content;
            } else if ("Multiple Choices" == str) {
                return response_status::multiple_choices;
            } else if ("Moved Permanently" == str) {
                return response_status::moved_permanently;
            } else if ("Moved Temporarily" == str) {
                return response_status::moved_temporarily;
            } else if ("See Other" == str) {
                return response_status::see_other;
            } else if ("Not Modified" == str) {
                return response_status::not_modified;
            } else if ("Use Proxy" == str) {
                return response_status::use_proxy;
            } else if ("Unused" == str) {
                return response_status::unused;
            } else if ("Temporary Redirect" == str) {
                return response_status::temporary_redirect;
            } else if ("Bad Request" == str) {
                return response_status::bad_request;
            } else if ("Unauthorized" == str) {
                return response_status::unauthorized;
            } else if ("Payment Required" == str) {
                return response_status::payment_required;
            } else if ("Forbidden" == str) {
                return response_status::forbidden;
            } else if ("Not Found" == str) {
                return response_status::not_found;
            } else if ("Method Not Allowed" == str) {
                return response_status::method_not_allowed;
            } else if ("Not Acceptable" == str) {
                return response_status::not_acceptable;
            } else if ("Proxy Authentication Required" == str) {
                return response_status::proxy_authentication_required;
            } else if ("Request Time-out" == str) {
                return response_status::request_time_out;
            } else if ("Conflict" == str) {
                return response_status::conflict;
            } else if ("Gone" == str) {
                return response_status::gone;
            } else if ("Length Required" == str) {
                return response_status::length_required;
            } else if ("Precondition Failed" == str) {
                return response_status::precondition_failed;
            } else if ("Request Entity Too Large" == str) {
                return response_status::request_entity_too_large;
            } else if ("Request-URI Too Large" == str) {
                return response_status::request_uri_too_large;
            } else if ("Unsupported Media Type" == str) {
                return response_status::unsupported_media_type;
            } else if ("Requested Range Not Satisfiable" == str) {
                return response_status::requested_range_not_satisfiable;
            } else if ("Expectation Failed" == str) {
                return response_status::expectation_failed;
            } else if ("Internal Server Error" == str) {
                return response_status::internal_server_error;
            } else if ("Not Implemented" == str) {
                return response_status::not_implemented;
            } else if ("Bad Gateway" == str) {
                return response_status::bad_gateway;
            } else if ("Service Unavailable" == str) {
                return response_status::service_unavailable;
            } else if ("Gateway Time-out" == str) {
                return response_status::gateway_time_out;
            } else if ("HTTP Version not supported" == str) {
                return response_status::http_version_not_supported;
            } else {
                return response_status::unknown;
            }
        }
        
    }
}
