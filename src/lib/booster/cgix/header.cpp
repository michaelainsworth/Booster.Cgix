#include <booster/cgix/header.hpp>
#include <sstream>

namespace booster
{
    namespace cgix
    {
        
        // Utility
        
        bool header::is_ctl(char c) {
            // ctl            = <any US-ASCII control character
            //                  (octets 0 - 31) and DEL (127)>
            
            return (c >= 0 && c <= 31) || c == 127;
        }
        
        bool header::is_separator(char c) {
            //separators     = "(" | ")" | "<" | ">" | "@"
            //                | "," | ";" | ":" | "\" | <">
            //                | "/" | "[" | "]" | "?" | "="
            //                | "{" | "}" | sp | ht
            return (c == '(' || c == ')' || c == '<' || c == '>' || c == '@' ||
                    c == ',' || c == ';' || c == ':' || c == '\\' || c == '"' ||
                    c == '/' || c == '[' || c == ']' || c == '?' || c == '=' ||
                    c == '{' || c == '}' || is_sp(c) || is_ht(c));
        }
        
        bool header::is_sp(char c) {
            return c == 32;
        }
        
        bool header::is_ht(char c) {
            return c == 9;
        }
        
        bool header::is_token(char c) {
            // token          = 1*<any CHAR except ctls or separators>
            return !is_ctl(c) && !is_separator(c);
        }
        
        bool header::is_text(const char *c, size_t length) {
            //text           = <any OCTET except ctls,
            //but including lws>
            if (!is_ctl(c[0]) || lws_length(c, length)) return true;
            return false;
        }
        
        size_t header::lws_length(const char *c, size_t length) {
            //lws            = [CRLF] 1*( sp | ht )
            if (length < 3) return 0;
            if (c[0] == '\r' && c[1] == '\n' && (is_sp(c[2]) || is_ht(c[2]))) {
                size_t i = 3;
                for (; i < length; ++i) {
                    if (!is_sp(c[i]) && !is_ht(c[i])) {
                        break;
                    }
                }
                return i;
            } else {
                return 0;
            }
        }
        
        size_t header::is_reverse_lws(const char *c, size_t length) {
            //lws            = [CRLF] 1*( sp | ht )
            if (length < 3) return 0;
            if (!is_sp(c[length - 1]) && !is_ht(c[length - 1])) return 0;
            
            int r = 1;
            for (int i = length - 2; i >= 0; --i) {
                if (is_sp(c[i]) || is_ht(c[i])) continue;
                else if (c[i] == '\n' && i > 0 && c[i - 1] == '\r') {
                    ++r;
                } else {
                    break;
                }
            }
            
            return r;
        }
        
        std::error_condition header::from_string(header& h, const value_string_type& header_string) {
            
            //message-header = field-name ":" [ field-value ]
            //field-name     = token
            //field-value    = *( field-content | lws )
            //field-content  = <the OCTETs making up the field-value
            //and consisting of either *text or combinations
            //of token, separators, and quoted-string>
            
            for (size_t i = 0, s = header_string.size(); i < s; ++i) {
                while (i < s && is_token(header_string[i])) {
                    ++i;
                }
                
                if (i == 0) {
                    return error::http_header_malformed;
                }
                
                if (header_string[i] != ':') {
                    return error::http_header_malformed;
                }
                
                h.name_ = name_string_type(&header_string[0], i);
                h.value_ = value_string_type(&header_string[i+1], header_string.length() - i - 1);
                break;
            }
            
            // Trim leading whitespace
            if (h.value_.length()) {
                size_t i = 0;
                for (; i < h.value_.length(); ++i) {
                    if (std::isspace(h.value_[i])) continue;
                    break;
                }
                if (i) {
                    h.value_ = h.value_.substr(i);
                }
            }
            
            // Trim leading lws
            if (h.value_.length()) {
                size_t l = lws_length(&h.value_[0], h.value_.length());
                if (l) {
                    h.value_ = h.value_.substr(l - 1);
                }
            }
            
            // Trim trailing lws
            if (h.value_.length()) {
                size_t l = is_reverse_lws(&h.value_[h.value_.length() - 1], h.value_.length() - 1);
                if (l) {
                    h.value_ = h.value_.substr(0, h.value_.length() - l + 1);
                }
            }
            
            // Trim trailing space.
            if (h.value_.length()) {
                size_t i = h.value_.length();
                for (; i > 0; --i) {
                    if (std::isspace(h.value_[i - 1])) continue;
                    break;
                }
                if (i != h.value_.length()) {
                    h.value_ = h.value_.substr(0, i);
                }
            }
            
            // Strip inner whitespace.
            if (h.value_.length()) {
                std::ostringstream ss;
                for (size_t i = 0, s = h.value_.length(); i < s; ++i) {
                    if (std::isspace(h.value_[i])) {
                        ss << " ";
                        while (std::isspace(h.value_[i])) ++i;
                        --i;
                    } else if ('"' == h.value_[i]) {
                        ss << h.value_[i];
                        ++i;
                        while (i < s) {
                            if (h.value_[i] == '\\' && i < s - 1 && h.value_[i + 1] == '"') {
                                ss << "\\\"";
                                ++i;
                            } else if (h.value_[i] == '"') {
                                ss << '"';
                                break;
                            } else {
                                ss << h.value_[i];
                            }
                            
                            ++i;
                        }
                    } else {
                        ss << h.value_[i];
                    }
                }
                
                h.value_ = ss.str();
            }
            
            return error::ok;
        }
        
        // Lifecycle
        
        header::header(const name_string_type& name, const value_string_type& value) : name_(name), value_(value) {}
        
        header::operator value_string_type() const {
            value_string_type str(name_.c_str(), name_.length());
            for (value_string_type::size_type i = 0, l = str.length(); i < l; ++i) {
                str[i] = std::tolower(str[i]);
            }
            
            return str + ": " + value_;
        }
        
        // Accessors
        const header::name_string_type& header::name() const {
            return name_;
        }
        
        const header::value_string_type& header::value() const {
            return value_;
        }
        
        // Entity headers
        header header::allow(const value_string_type& value) {
            return header("Allow", value);
        }
        
        header header::content_encoding(const value_string_type& value) {
            return header("Content-Encoding", value);
        }
        
        header header::content_language(const value_string_type& value) {
            return header("Content-Language", value);
        }
        
        header header::content_length(const value_string_type& value) {
            return header("Content-Length", value);
        }
        
        header header::content_location(const value_string_type& value) {
            return header("Content-Location", value);
        }
        
        header header::content_md5(const value_string_type& value) {
            return header("Content-MD5", value);
        }
        
        header header::content_range(const value_string_type& value) {
            return header("Content-Range", value);
        }
        
        header header::content_type(const value_string_type& value) {
            return header("Content-Type", value);
        }
        
        header header::expires(const value_string_type& value) {
            return header("Expires", value);
        }
        
        header header::last_modified(const value_string_type& value) {
            return header("Last-Modified", value);
        }
        
        
        // General headers
        header header::connection_header(const value_string_type& value) {
            return header("Connection", value);
        }
        
        header header::date(const value_string_type& value) {
            return header("Date", value);
        }
        
        header header::pragma(const value_string_type& value) {
            return header("Pragma", value);
        }
        
        header header::trailer(const value_string_type& value) {
            return header("Trailer", value);
        }
        
        header header::transfer_encoding(const value_string_type& value) {
            return header("Transfer-Encoding", value);
        }
        
        header header::upgrade(const value_string_type& value) {
            return header("Upgrade", value);
        }
        
        header header::via(const value_string_type& value) {
            return header("Via", value);
        }
        
        header header::warning(const value_string_type& value) {
            return header("Warning", value);
        }
        
        
        // Request headers
        header header::accept(const value_string_type& value) {
            return header("Accept", value);
        }
        
        header header::accept_charset(const value_string_type& value) {
            return header("Accept-Charset", value);
        }
        
        header header::accept_encoding(const value_string_type& value) {
            return header("Accept-Encoding", value);
        }
        
        header header::accept_language(const value_string_type& value) {
            return header("Accept-Language", value);
        }
        
        header header::authorization(const value_string_type& value) {
            return header("Authorization", value);
        }
        
        header header::cache_control(const value_string_type& value) {
            return header("Cache-Control", value);
        }
        
        header header::expect(const value_string_type& value) {
            return header("Expect", value);
        }
        
        header header::from(const value_string_type& value) {
            return header("From", value);
        }
        
        header header::host(const value_string_type& value) {
            return header("Host", value);
        }
        
        header header::if_match(const value_string_type& value) {
            return header("If-Match", value);
        }
        
        header header::if_modified_since(const value_string_type& value) {
            return header("If-Modified-Since", value);
        }
        
        header header::if_none_match(const value_string_type& value) {
            return header("If-None-Match", value);
        }
        
        header header::if_range(const value_string_type& value) {
            return header("If-Range", value);
        }
        
        header header::if_unmodified_since(const value_string_type& value) {
            return header("If-Unmodified-Since", value);
        }
        
        header header::max_forwards(const value_string_type& value) {
            return header("Max-Forwards", value);
        }
        
        header header::proxy_authorization(const value_string_type& value) {
            return header("Proxy-Authorization", value);
        }
        
        header header::range(const value_string_type& value) {
            return header("Range", value);
        }
        
        header header::referer(const value_string_type& value) {
            return header("Referer", value);
        }
        
        header header::te(const value_string_type& value) {
            return header("TE", value);
        }
        
        header header::user_agent(const value_string_type& value) {
            return header("User-Agent", value);
        }
        
        
        // Response headers
        header header::accept_ranges(const value_string_type& value) {
            return header("Accept-Ranges", value);
        }
        
        header header::age(const value_string_type& value) {
            return header("Age", value);
        }
        
        header header::etag(const value_string_type& value) {
            return header("ETag", value);
        }
        
        header header::location(const value_string_type& value) {
            return header("Location", value);
        }
        
        header header::proxy_authenticate(const value_string_type& value) {
            return header("Proxy-Authenticate", value);
        }
        
        header header::retry_after(const value_string_type& value) {
            return header("Retry-After", value);
        }
        
        header header::server(const value_string_type& value) {
            return header("Server", value);
        }
        
        header header::vary(const value_string_type& value) {
            return header("Vary", value);
        }
        
        header header::www_authenticate(const value_string_type& value) {
            return header("WWW-Authenticate", value);
        }
        
    } }
