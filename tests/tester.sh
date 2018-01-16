#!/usr/bin/env bash

function get_size_and_time() {
    pattern="$1";k="$2";file="$3"
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
           # size="$(/usr/bin/time --format="%M" ./agrep "$pattern" "$k" "$file" 2>&1 >/dev/null)";
            ts=$(date +%s%N);
            size="$(/usr/bin/time --format="%M" ./agrep "$pattern" "$k" "$file" 2>&1 >/dev/null)";
            tt=$(( ($(date +%s%N) - $ts)/1000000));
            echo "$tt;$size"

    elif [[ "$OSTYPE" == "darwin"* ]]; then
            # Mac OSX
            gtime -v
            ts=$(date +%s%N);
            size="$(gtime --format="%M" ./agrep "$pattern" "$k" "$file" 2>&1 >/dev/null)";
            tt=$(( ($(date +%s%N) - $ts)/1000000));
            echo "$tt;$size"
    else
        (>2 echo "OS not supported!")
        exit 1
    fi
}
if [ "$#" -ne 3 ]; then
    (2> echo "Expected three arguments: ([pattern] [k] [samples folder]) or ([sample file] [k] [pattern])!")
    exit 1
fi
pattern="$1";k="$2";file_or_folder="$3"
if [[ -d "$file_or_folder" ]]; then
    find "$file_or_folder" -name "*.parsed" -print0 | while read -d $'\0' file
    do
        result=$(get_size_and_time "$pattern" "$k" "$file")
        echo "$file;$result"
    done
else
    result=$(get_size_and_time "$pattern" "$k" "$file_or_folder")
    echo "$file_or_folder;$result"
fi