#include <booster/cgix/response.hpp>
#include <booster/cgix/error_condition.hpp>
using namespace std;

namespace booster {
    namespace cgix {
        
        response::response() : are_headers_sent_(false), status_(response_status::ok) {}
        
        response::~response() {}
        
        response_status response::response_status() const {
            return status_;
        }
        
        response& response::operator <<(enum response_status status) {
            if (are_headers_sent_) {
                throw std::system_error(error::http_headers_already_sent);
            }
            
            status_ = status;
            return *this;
        }
        
        bool response::are_headers_sent() const {
            return are_headers_sent_;
        }
        
        const header_map& response::headers() const {
            return headers_;
        }
        
        response& response::operator <<(const header& hdr) {
            if (are_headers_sent_) {
                throw std::system_error(error::http_headers_already_sent);
            }
            
            headers_.set(hdr.name(), hdr.value());
            return *this;
        }
        
        void response::send_headers() {
            if (are_headers_sent_) {
                throw std::system_error(error::http_headers_already_sent);
            }
            
            cout << "Status: " << static_cast<int>(status_) << "\r\n";
            for (header_map::const_iterator it = headers_.begin(), end = headers_.end(); it != end; ++it) {
                cout << it->first.c_str() << ": " << it->second.c_str() << "\r\n";
            }
            for (cookie_map::const_iterator it = cookies_.begin(), end = cookies_.end(); it != end; ++it) {
                cout << "Set-Cookie: " << cookie::string_type(it->second).c_str() << "\r\n";
            }
            cout << "\r\n";
            are_headers_sent_ = true;
        }
        
        const cookie_map& response::cookies() const {
            return cookies_;
        }
        
        response& response::operator <<(const cookie& ck) {
            if (are_headers_sent_) {
                throw std::system_error(error::http_headers_already_sent);
            }
            
            cookies_.set(ck);
            return *this;
        }
        
        std::ostream& response::out() {
            if (!are_headers_sent_) {
                send_headers();
            }
            
            return cout;
        }
        
    }
}
