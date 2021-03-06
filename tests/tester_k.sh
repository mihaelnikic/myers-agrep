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
    ts_edlib=$(date +%s%N);
    size_edlib="$("$time_op" --format="%M" "$parent_path/tests/edlib" "$pattern" "$k" "$file" 2>&1 >/dev/null)";
    tt_edlib=$(( ($(date +%s%N) - $ts)/1000000));
    echo "$k;$size;$tt|$k;$size_edlib;$tt_edlib"
}
function get_values() {
    sample_file="$1";pattern="$2";ks="$3";
    parent_path="$4"
    for k in $ks; do
        result=$(get_values_from_file  "$pattern" "$k" "$sample_file" "$parent_path")
        echo "$result"
    done
}

current_path="$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )"
parent_path="$(dirname "$current_path")"

if [ "$#" -lt 3 ]; then
    ( >&2 echo "Expected at least three arguments: [sample file] [pattern] [k1] .. [kn])" )
    exit 1
fi
sample_file="$1"; shift
pattern="$1"; shift
ks="$@"
result=$(get_values "$sample_file" "$pattern" "$ks" "$parent_path")
#echo "$result"
python3 "$parent_path/tests/plotter.py" "$result" "Maksimalna udaljenost k"