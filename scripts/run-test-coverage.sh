#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

if [ $# -lt 5 ]; then
    exit 1
fi

prg="$1"
input="$2"
coverage_cmd="$3"
coverage_args="$4"
coverage_report_path="$5"

$coverage_cmd ${coverage_args} ${coverage_report_path} ./${prg} < ${input}
