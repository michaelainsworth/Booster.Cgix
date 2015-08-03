#include <booster/cgix/error.hpp>

namespace booster {
    namespace cgix {
        
        const char* error_category::name() const noexcept(true) {
            return "Booster.Cgix";
        }
        
        std::string error_category::message(int ev) const noexcept(true) {
            switch (static_cast<error>(ev)) {
                case error::ok:
                    return "OK";
                case error::hex_sequence_too_short:
                    return "The hex sequence specified was too short.";
                case error::hex_character_invalid:
                    return "The hex character specified was invalid.";
                case error::percent_sequence_invalid:
                    return "The percent-encoded hex sequence was invalid.";
                case error::cookie_string_end_unexpected:
                    return "The end of the cookie string was encountered unexpectedly.";
                case error::cookie_string_quote_end_unexpected:
                    return "The end of the cookie string quoted value was encountered unexpectedly.";
                case error::cookie_string_pair_separator_invalid:
                    return "The cookie string pair separator was not valid.";
                case error::cookie_string_char_unexpected:
                    return "The cookie string contained an expected character.";
                case error::http_header_malformed:
                    return "The HTTP header string was malformed.";
                case error::http_header_not_set:
                    return "The HTTP header specified does not exist.";
                case error::http_headers_already_sent:
                    return "The HTTP headers have already been sent.";
                case error::session_file_directory_invalid:
                    return "The file session storage directory does not exist or was not a directory.";
                case error::implementation_required:
                    return "The functionality specified must be implemented by users of the library.";
                case error::connection_not_initialized:
                    return "The connection to the server has not yet been initialized.";
                default:
                    return "An unknown error occurred.";
            }
        }
        
        const error_category& get_error_category() {
            static error_category ec;
            return ec;
        }
        
        std::error_code make_error_code(error e) {
            return std::error_code(static_cast<int>(e), get_error_category());
        }
        
        std::error_condition make_error_condition(error e) {
            return std::error_condition(static_cast<int>(e), get_error_category());
        }

        
    }
}
