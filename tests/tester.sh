#!/usr/bin/env bash

if [[ "$OSTYPE" == "linux-gnu" ]]; then
        /usr/bin/time
elif [[ "$OSTYPE" == "darwin"* ]]; then
        # Mac OSX
        gtime
else
    (>2 echo "OS nije podrzan!")
fi