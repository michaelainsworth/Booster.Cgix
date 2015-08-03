#include <booster/cgix/cookie_map.hpp>
#include <booster/cgix/percent_coder.hpp>
#include <booster/cgix/header.hpp>
#include <booster/cgix/error.hpp>

namespace booster {
    namespace cgix {
     
        std::error_condition cookie_map::from_string(cookie_map& cookies, const string_type& cookie_string) {
            percent_coder pe;
            std::error_condition e;
            map_type string_map;
            
            for (string_type::size_type i = 0, s = cookie_string.length(); i < s; ++i) {
                if (header::lws_length(&cookie_string[i], s - i)) {
                    i += header::lws_length(&cookie_string[i], s - i);
                } else if (header::is_token(cookie_string[i])) {
                    string_type::size_type start = i;
                    while (i < s && header::is_token(cookie_string[i])) ++i;
                    
                    string_type name = cookie_string.substr(start, i - start);
                    if (cookie_string[i] == ';') {
                        string_map[name] = "";
                    } else if (cookie_string[i] == '=') {
                        string_type value;
                        
                        ++i;
                        if (i >= s) {
                            return error::cookie_string_end_unexpected;
                        }
                        
                        if (cookie_string[i] == '"') {
                            ++i;
                            if (i >= s) {
                                return error::cookie_string_quote_end_unexpected;
                            }
                            
                            while (i < s && cookie_string[i] != '"') {
                                if (cookie_string[i] == '\\' && i < s - 1 && cookie_string[i + 1] == '"') {
                                    value += '"';
                                    ++i;
                                } else {
                                    value += cookie_string[i];
                                }
                                ++i;
                            }
                            
                            string_type value_to_add;
                            e = pe.decode(value_to_add, value);
                            if (!e) {
                                return e;
                            }
                            string_map[name] = value_to_add;
                            
                        } else {
                            start = i;
                            while (i < s && header::is_token(cookie_string[i])) {
                                ++i;
                            }
                            value = cookie_string.substr(start, i - start);
                            
                            string_type value_to_add;
                            e = pe.decode(value_to_add, value);
                            if (!e) {
                                return e;
                            }
                            string_map[name] = value_to_add;
                        }
                        
                        if (i < s) {
                            if (cookie_string[i] != ';') {
                                return error::cookie_string_pair_separator_invalid;
                            }
                            ++i;
                            
                            if (i < s && header::lws_length(&cookie_string[i], s - i)) {
                                i += header::lws_length(&cookie_string[i], s - i);
                            }
                        }
                        
                    } else {
                        return error::cookie_string_pair_separator_invalid;
                    }
                } else {
                    return error::cookie_string_char_unexpected;
                }
            }
            
            cookies.cookies_ = string_map;
            return error::ok;
        }
        
        bool cookie_map::is_set(const string_type& name) const {
            return cookies_.find(name) != cookies_.end();
        }
        
        cookie_map::string_type cookie_map::get(const string_type& name) const {
            map_type::const_iterator it = cookies_.find(name), end = cookies_.end();
            if (it == end) {
                return "";
            }
            
            return it->second;
        }
        
        void cookie_map::set(const cookie& ck) {
            cookies_[ck.name()] = ck;
        }
        
        cookie_map::const_iterator cookie_map::begin() const {
            return cookies_.begin();
        }
        
        cookie_map::const_iterator cookie_map::end() const {
            return cookies_.end();
        }
        
    }
}
