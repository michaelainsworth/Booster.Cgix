#ifndef BOOSTER_CGIX_RESPONSE_HPP_INCLUDED
#define BOOSTER_CGIX_RESPONSE_HPP_INCLUDED

#include <iostream>
#include <booster/cgix/response_status.hpp>
#include <booster/cgix/header.hpp>
#include <booster/cgix/cookie.hpp>
#include <booster/cgix/cookie_map.hpp>
#include <booster/cgix/header_map.hpp>

namespace booster {
    namespace cgix {
        
        class response {
        public:
            
            response();
            virtual ~response();
            
            virtual response_status response_status() const;
            virtual response& operator <<(enum response_status status);
            
            virtual bool are_headers_sent() const;
            virtual const header_map& headers() const;
            virtual response& operator <<(const header& hdr);
            virtual void send_headers();
            
            virtual const cookie_map& cookies() const;
            virtual response& operator <<(const cookie& ck);
            
            virtual std::ostream& out();
            
        private:
            
            // Variables
            bool are_headers_sent_;
            enum response_status status_;
            header_map headers_;
            cookie_map cookies_;
            
        };
        
    }
}

#endif // #ifndef BOOSTER_CGIX_RESPONSE_HPP_INCLUDED
