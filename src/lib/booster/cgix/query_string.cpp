#include <booster/cgix/query_string.hpp>
#include <booster/cgix/string_exploder.hpp>
#include <booster/cgix/percent_coder.hpp>
#include <vector>

namespace booster {
    namespace cgix {
        
        query_string::query_string() {}
        
        query_string::query_string(const string_type& value) {
            string_exploder exploder;
            string_exploder::vector_type parts;
            exploder.explode(value, "&", parts);
            
            percent_coder pe;
            
            for (auto& part : parts) {
                
                string_exploder::vector_type pair;
                exploder.explode(part, "=", pair, 2);
                
                string_type k = pair[0], v = pair.size() > 1 ? pair[1] : "";
                string_type kk, vv;
                
                pe.decode(kk, k);
                pe.decode(vv, v);
                
                values_[kk] = vv;
            }
        }
            
        bool query_string::has(const string_type& name) const {
            return values_.find(name) != values_.end();
        }

        query_string::string_type query_string
        ::operator[](const string_type& name) const {
            if (!has(name)) {
                return "";
            }
            
            return values_.find(name)->second;
        }

    }
}
