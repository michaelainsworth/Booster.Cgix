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
            if (!is_ctl(c[0]) || is_lws(c, length)) return true;
            return false;
        }
        
        size_t header::is_lws(const char *c, size_t length) {
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
        
        std::error_condition header::from_string(header& h, const std::string& header_string) {
            
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
                
                h.name_ = std::string(&header_string[0], i);
                h.value_ = std::string(&header_string[i+1], header_string.length() - i - 1);
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
                size_t l = is_lws(&h.value_[0], h.value_.length());
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
        
        header::header(const std::string& name, const std::string& value) : name_(name), value_(value) {}
        
        header::operator std::string() const {
            return name_ + ": " + value_;
        }
        
        // Accessors
        const std::string& header::name() const {
            return name_;
        }
        
        const std::string& header::value() const {
            return value_;
        }
        
        // Entity headers
        header allow(const std::string& value) {
            return header("Allow", value);
        }
        
        header content_encoding(const std::string& value) {
            return header("Content-Encoding", value);
        }
        
        header content_language(const std::string& value) {
            return header("Content-Language", value);
        }
        
        header content_length(const std::string& value) {
            return header("Content-Length", value);
        }
        
        header content_location(const std::string& value) {
            return header("Content-Location", value);
        }
        
        header content_md5(const std::string& value) {
            return header("Content-MD5", value);
        }
        
        header content_range(const std::string& value) {
            return header("Content-Range", value);
        }
        
        header content_type(const std::string& value) {
            return header("Content-Type", value);
        }
        
        header expires(const std::string& value) {
            return header("Expires", value);
        }
        
        header last_modified(const std::string& value) {
            return header("Last-Modified", value);
        }
        
        
        // General headers
        header connection(const std::string& value) {
            return header("Connection", value);
        }
        
        header date(const std::string& value) {
            return header("Date", value);
        }
        
        header pragma(const std::string& value) {
            return header("Pragma", value);
        }
        
        header trailer(const std::string& value) {
            return header("Trailer", value);
        }
        
        header transfer_encoding(const std::string& value) {
            return header("Transfer-Encoding", value);
        }
        
        header upgrade(const std::string& value) {
            return header("Upgrade", value);
        }
        
        header via(const std::string& value) {
            return header("Via", value);
        }
        
        header warning(const std::string& value) {
            return header("Warning", value);
        }
        
        
        // Request headers
        header accept(const std::string& value) {
            return header("Accept", value);
        }
        
        header accept_charset(const std::string& value) {
            return header("Accept-Charset", value);
        }
        
        header accept_encoding(const std::string& value) {
            return header("Accept-Encoding", value);
        }
        
        header accept_language(const std::string& value) {
            return header("Accept-Language", value);
        }
        
        header authorization(const std::string& value) {
            return header("Authorization", value);
        }
        
        header cache_control(const std::string& value) {
            return header("Cache-Control", value);
        }
        
        header expect(const std::string& value) {
            return header("Expect", value);
        }
        
        header from(const std::string& value) {
            return header("From", value);
        }
        
        header host(const std::string& value) {
            return header("Host", value);
        }
        
        header if_match(const std::string& value) {
            return header("If-Match", value);
        }
        
        header if_modified_since(const std::string& value) {
            return header("If-Modified-Since", value);
        }
        
        header if_none_match(const std::string& value) {
            return header("If-None-Match", value);
        }
        
        header if_range(const std::string& value) {
            return header("If-Range", value);
        }
        
        header if_unmodified_since(const std::string& value) {
            return header("If-Unmodified-Since", value);
        }
        
        header max_forwards(const std::string& value) {
            return header("Max-Forwards", value);
        }
        
        header proxy_authorization(const std::string& value) {
            return header("Proxy-Authorization", value);
        }
        
        header range(const std::string& value) {
            return header("Range", value);
        }
        
        header referer(const std::string& value) {
            return header("Referer", value);
        }
        
        header te(const std::string& value) {
            return header("TE", value);
        }
        
        header user_agent(const std::string& value) {
            return header("User-Agent", value);
        }
        
        
        // Response headers
        header accept_ranges(const std::string& value) {
            return header("Accept-Ranges", value);
        }
        
        header age(const std::string& value) {
            return header("Age", value);
        }
        
        header etag(const std::string& value) {
            return header("ETag", value);
        }
        
        header location(const std::string& value) {
            return header("Location", value);
        }
        
        header proxy_authenticate(const std::string& value) {
            return header("Proxy-Authenticate", value);
        }
        
        header retry_after(const std::string& value) {
            return header("Retry-After", value);
        }
        
        header server(const std::string& value) {
            return header("Server", value);
        }
        
        header vary(const std::string& value) {
            return header("Vary", value);
        }
        
        header www_authenticate(const std::string& value) {
            return header("WWW-Authenticate", value);
        }
        
    } }
