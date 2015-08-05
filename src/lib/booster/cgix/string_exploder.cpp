#include <booster/cgix/string_exploder.hpp>

namespace booster {
    namespace cgix {

        // -----------------------------------------------------------------
        // Main methods
        // -----------------------------------------------------------------
        
        // The explode() function splits the string into multiple strings
        // using the delimiter, and storing the results in container
        // specified.
        
        void string_exploder
        ::explode(const string_type& imploded,
                  const string_type& delimiter,
                  vector_type& items,
                  size_t limit) {
            
            string_type part;
            
            if (imploded.length() == 0) {
                return;
            }
            
            size_t pos, lastPos = 0, count = 0;
            while (true) {
                if (!limit && count >= limit) {
                    break;
                }
                
                pos = imploded.find(delimiter, lastPos);
                if (pos == string_type::npos) {
                    items.push_back(imploded.substr(lastPos));
                    ++count;
                    break;
                } else {
                    if (!limit && count == limit - 1) {
                        items.push_back(imploded.substr(lastPos));
                        ++count;
                        break;
                    } else {
                        items.push_back(imploded.substr(lastPos, pos - lastPos));
                        ++count;
                    }
                }
            }
        }
        
        // The implode() function joins the elements together
        // using the delimiter specified.
        
        string_exploder::string_type string_exploder
        ::implode(const string_type& delimiter,
                  const vector_type& items) {
            
            string_type str("");
            if (items.empty()) return str;
            
            size_t i = 0;
            for (auto& item : items) {
                str += item;
                if (i != 0) {
                    str += delimiter;
                }
                
                ++i;
            }
            
            return str;
        }

    }
}
