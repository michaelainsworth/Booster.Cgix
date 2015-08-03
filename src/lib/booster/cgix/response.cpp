#include <booster/cgix/response.hpp>
#include <booster/cgix/error_condition.hpp>
using namespace std;

namespace booster {
    namespace cgix {

        response::~response() {}
        
        std::string response::status_to_string(status_type status) {
            if (continue_ == status) {
                return "Continue";
            } else if (switching_protocols == status) {
                return "Switching Protocols";
            } else if (ok == status) {
                return "OK";
            } else if (created == status) {
                return "Created";
            } else if (accepted == status) {
                return "Accepted";
            } else if (non_authoritative_information == status) {
                return "Non-Authoritative Information";
            } else if (no_content == status) {
                return "No Content";
            } else if (reset_content == status) {
                return "Reset Content";
            } else if (partial_content == status) {
                return "Partial Content";
            } else if (multiple_choices == status) {
                return "Multiple Choices";
            } else if (moved_permanently == status) {
                return "Moved Permanently";
            } else if (moved_temporarily == status) {
                return "Moved Temporarily";
            } else if (see_other == status) {
                return "See Other";
            } else if (not_modified == status) {
                return "Not Modified";
            } else if (use_proxy == status) {
                return "Use Proxy";
            } else if (unused == status) {
                return "Unused";
            } else if (temporary_redirect == status) {
                return "Temporary Redirect";
            } else if (bad_request == status) {
                return "Bad Request";
            } else if (unauthorized == status) {
                return "Unauthorized";
            } else if (payment_required == status) {
                return "Payment Required";
            } else if (forbidden == status) {
                return "Forbidden";
            } else if (not_found == status) {
                return "Not Found";
            } else if (method_not_allowed == status) {
                return "Method Not Allowed";
            } else if (not_acceptable == status) {
                return "Not Acceptable";
            } else if (proxy_authentication_required == status) {
                return "Proxy Authentication Required";
            } else if (request_time_out == status) {
                return "Request Time-out";
            } else if (conflict == status) {
                return "Conflict";
            } else if (gone == status) {
                return "Gone";
            } else if (length_required == status) {
                return "Length Required";
            } else if (precondition_failed == status) {
                return "Precondition Failed";
            } else if (request_entity_too_large == status) {
                return "Request Entity Too Large";
            } else if (request_uri_too_large == status) {
                return "Request-URI Too Large";
            } else if (unsupported_media_type == status) {
                return "Unsupported Media Type";
            } else if (requested_range_not_satisfiable == status) {
                return "Requested Range Not Satisfiable";
            } else if (expectation_failed == status) {
                return "Expectation Failed";
            } else if (internal_server_error == status) {
                return "Internal Server Error";
            } else if (not_implemented == status) {
                return "Not Implemented";
            } else if (bad_gateway == status) {
                return "Bad Gateway";
            } else if (service_unavailable == status) {
                return "Service Unavailable";
            } else if (gateway_time_out == status) {
                return "Gateway Time-out";
            } else if (http_version_not_supported == status) {
                return "HTTP Version not supported";
            } else {
                return "";
            }
        }
        
        
        response::status_type response::string_to_status(const std::string& str) {
            if ("Continue" == str) {
                return continue_;
            } else if ("Switching Protocols" == str) {
                return switching_protocols;
            } else if ("OK" == str) {
                return ok;
            } else if ("Created" == str) {
                return created;
            } else if ("Accepted" == str) {
                return accepted;
            } else if ("Non-Authoritative Information" == str) {
                return non_authoritative_information;
            } else if ("No Content" == str) {
                return no_content;
            } else if ("Reset Content" == str) {
                return reset_content;
            } else if ("Partial Content" == str) {
                return partial_content;
            } else if ("Multiple Choices" == str) {
                return multiple_choices;
            } else if ("Moved Permanently" == str) {
                return moved_permanently;
            } else if ("Moved Temporarily" == str) {
                return moved_temporarily;
            } else if ("See Other" == str) {
                return see_other;
            } else if ("Not Modified" == str) {
                return not_modified;
            } else if ("Use Proxy" == str) {
                return use_proxy;
            } else if ("Unused" == str) {
                return unused;
            } else if ("Temporary Redirect" == str) {
                return temporary_redirect;
            } else if ("Bad Request" == str) {
                return bad_request;
            } else if ("Unauthorized" == str) {
                return unauthorized;
            } else if ("Payment Required" == str) {
                return payment_required;
            } else if ("Forbidden" == str) {
                return forbidden;
            } else if ("Not Found" == str) {
                return not_found;
            } else if ("Method Not Allowed" == str) {
                return method_not_allowed;
            } else if ("Not Acceptable" == str) {
                return not_acceptable;
            } else if ("Proxy Authentication Required" == str) {
                return proxy_authentication_required;
            } else if ("Request Time-out" == str) {
                return request_time_out;
            } else if ("Conflict" == str) {
                return conflict;
            } else if ("Gone" == str) {
                return gone;
            } else if ("Length Required" == str) {
                return length_required;
            } else if ("Precondition Failed" == str) {
                return precondition_failed;
            } else if ("Request Entity Too Large" == str) {
                return request_entity_too_large;
            } else if ("Request-URI Too Large" == str) {
                return request_uri_too_large;
            } else if ("Unsupported Media Type" == str) {
                return unsupported_media_type;
            } else if ("Requested Range Not Satisfiable" == str) {
                return requested_range_not_satisfiable;
            } else if ("Expectation Failed" == str) {
                return expectation_failed;
            } else if ("Internal Server Error" == str) {
                return internal_server_error;
            } else if ("Not Implemented" == str) {
                return not_implemented;
            } else if ("Bad Gateway" == str) {
                return bad_gateway;
            } else if ("Service Unavailable" == str) {
                return service_unavailable;
            } else if ("Gateway Time-out" == str) {
                return gateway_time_out;
            } else if ("HTTP Version not supported" == str) {
                return http_version_not_supported;
            } else {
                return unknown;
            }
        }
        
    }
}
