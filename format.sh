#!/bin/bash

find . -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' -o -name '*.cc' \) \
    -not -path "./subprojects/*" \
    -not -path "./build/*" \
    | xargs clang-format -i
