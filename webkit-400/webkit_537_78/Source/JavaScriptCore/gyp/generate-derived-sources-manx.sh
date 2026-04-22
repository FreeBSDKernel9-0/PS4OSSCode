#!/bin/bash

set -o errexit
set -o xtrace

jobs=$(../../../Tools/Scripts/num-cpus)
export DERIVED_SOURCES_DIR="$1"
export SRCROOT="$PWD/.."

mkdir -p "${DERIVED_SOURCES_DIR}/JavaScriptCore/docs"
cd "${DERIVED_SOURCES_DIR}/JavaScriptCore"

rm -f JavaScriptCore
/bin/ln -sf "${SRCROOT}" JavaScriptCore
export JavaScriptCore="JavaScriptCore"

make --no-builtin-rules -f "JavaScriptCore/DerivedSources.make" -j $jobs
