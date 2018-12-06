#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

if [ $# -lt 2 ]; then
    exit 1
fi

prg="$1"
input="$2"

./${prg} < ${input}
