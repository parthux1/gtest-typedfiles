BUILD_DIR=build

cmake -B ${BUILD_DIR} -S .
make -C ${BUILD_DIR}