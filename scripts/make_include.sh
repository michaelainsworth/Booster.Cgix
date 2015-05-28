#!/bin/bash

d=$(dirname "$0")/../src/lib/booster/cgix
t="$d/cgix.hpp"

echo "#ifndef BOOSTER_CGIX_CGIX_HPP_INCLUDED" > "$t"
echo "#define BOOSTER_CGIX_CGIX_HPP_INCLUDED" >> "$t"
echo >> "$t"

ls "$d/"*.hpp | grep -v cgix.hpp | while read l ; do
    echo "$l" | awk -F / '{print "#include <"$6"/"$7"/"$8">";}'
done >> "$t"
echo >> "$t"

echo "#endif // #ifndef BOOSTER_CGIX_CGIX_HPP_INCLUDED" >> "$t"
echo >> "$t"

