#!/usr/bin/env bash

return_code=0
for exe in $(find ./exe/ -name '*_test'); do
    echo -e "\n>>> RUNNING '$exe' <<<"
    "$exe"
    last_return_code=$?
    return_code=$(($return_code | $last_return_code))
    echo ">>> test returned code: $last_return_code <<<"
done

exit $return_code
