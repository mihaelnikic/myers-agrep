#!/usr/bin/env bash

#!/usr/bin/env bash

function get_values_from_file() {
    pattern="$1";k="$2";file="$3";
    parent_path="$4"
    error_file="$5"
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
    agrep_out="$("$parent_path/agrep" "$pattern" "$k" "$file")"
    edlib_out="$("$parent_path/tests/edlib" "$pattern" "$k" "$file")"
    if [[ "$agrep_out" == "$edlib_out" ]]; then
        echo "$file":Same
    else
        echo "$file":Differ
        if [[ "$error_file" != "" ]]; then
            echo "====================" >> "$error_file"
            echo "File name: $file" >> "$error_file"
            echo "agrep output:" >> "$error_file"
            echo "$agrep_out" >> "$error_file"
            echo "--------------------" >> "$error_file"
            echo "edlib output:" >> "$error_file"
            echo "$edlib_out" >> "$error_file"
            echo "--------------------" >> "$error_file"
            echo "difference:" >> "$error_file"
            diff --suppress-common-lines <(echo -e "$agrep_out") <(echo -e "$edlib_out") >> "$error_file"
        fi
     #   echo 'agrep_out:'
     #   echo "$agrep_out"
     #   echo 'edlib_out'
     #   echo "$edlib_out"
     #   echo "end"
    fi
}

function get_values() {
    pattern="$1";k="$2";file_or_folder="$3";
    parent_path="$4"
    error_file="$5"
    if [[ -d "$file_or_folder" ]]; then
        find "$file_or_folder" \( -name "*.parsed" -or -name "*.chars" \) -print0 | while read -d $'\0' file
        do
            result=$(get_values_from_file  "$pattern" "$k" "$file" "$parent_path" "$error_file")
            echo "$result"
        done
    else
        result=$(get_values_from_file "$pattern" "$k" "$file_or_folder" "$parent_path" "$error_file")
        echo "$result"
    fi
}

current_path="$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )"
parent_path="$(dirname "$current_path")"


if [ "$#" -lt 3 ]; then
    (>&2 echo "Expected three arguments: [pattern] [k] [samples folder/sample file] [OPTIONAL error_file]!")
    exit 1
fi
result=$(get_values "$1" "$2" "$3" "$parent_path" "$4")
echo "$result"
valid="$(("$(echo "$result" | egrep "Same"| wc -l)"))"
total="$(("$(echo "$result" | wc -l)"))"
echo "Accuracy $valid / $total = $(bc <<< "scale=2; "$valid*100"/"$total"")%"
#python3 "$parent_path/tests/plotter.py" "$result" "Duljina teksta"