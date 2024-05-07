#!/bin/bash
# run from project root

_VCPKG_PATH="tooling/vcpkg"

./${_VCPKG_PATH}/bootstrap-vcpkg.sh
./${_VCPKG_PATH}/vcpkg install