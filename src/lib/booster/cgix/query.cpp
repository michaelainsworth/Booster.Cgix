#include <booster/cgix/query.hpp>
#include <booster/cgix/string_exploder.hpp>
#include <booster/cgix/percent_coder.hpp>
#include <vector>

namespace booster {
    namespace cgix {
        
        query::query() {}
        
        query::query(const string_type& value) {
            string_exploder exploder;
            string_exploder::vector_type parts;
            exploder.explode(value, "&", parts);
            
            percent_coder pe;
            
            for (auto& part : parts) {
                
                string_exploder::vector_type pair;
                exploder.explode(part, "=", pair, 2);
                
                string_type k = pair[0], v = pair.size() > 1 ? pair[1] : "";
                string_type kk, vv;
                
                kk = pe.decode(k);
                vv = pe.decode(v);
                
                values_[kk] = vv;
            }
        }
            
        bool query::has(const string_type& name) const {
            return values_.find(name) != values_.end();
        }

        query::string_type query
        ::operator[](const string_type& name) const {
            if (!has(name)) {
                return "";
            }
            
            return values_.find(name)->second;
        }

    }
}
