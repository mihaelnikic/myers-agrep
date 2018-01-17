#!/usr/bin/env bash

function get_values_from_file() {
    pattern="$1";k="$2";file="$3";
    parent_path="$4"
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
            # linux
            time_op="/usr/bin/time"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
            # Mac OSX
            time_op="gtime"
    else
        (>&2 echo "OS not supported!")
        exit 1
    fi
    ts=$(date +%s%N);
    size="$("$time_op" --format="%M" "$parent_path/agrep" "$pattern" "$k" "$file" 2>&1 >/dev/null)";
    tt=$(( ($(date +%s%N) - $ts)/1000000));
    len=$(($(cat "$file" | wc -c)))
    ts_edlib=$(date +%s%N);
    size_edlib="$("$time_op" --format="%M" "$parent_path/tests/edlib" "$pattern" "$k" "$file" 2>&1 >/dev/null)";
    tt_edlib=$(( ($(date +%s%N) - $ts)/1000000));
    echo "$len;$size;$tt|$len;$size_edlib;$tt_edlib"
}
function get_values() {
    pattern="$1";k="$2";file_or_folder="$3";
    parent_path="$4"
    if [[ -d "$file_or_folder" ]]; then
        find "$file_or_folder" \( -name "*.parsed" -or -name "*.chars" \) -print0 | while read -d $'\0' file
        do
            result=$(get_values_from_file  "$pattern" "$k" "$file" "$parent_path")
            echo "$result"
        done
    else
        result=$(get_values_from_file "$pattern" "$k" "$file_or_folder" "$parent_path")
        echo "$result"
    fi
}

current_path="$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )"
parent_path="$(dirname "$current_path")"


if [ "$#" -ne 3 ]; then
    (>&2 echo "Expected three arguments: [pattern] [k] [samples folder/sample file]!")
    exit 1
fi
result=$(get_values "$1" "$2" "$3" "$parent_path")
#echo "$result"
python3 "$parent_path/tests/plotter.py" "$result" "Duljina teksta"