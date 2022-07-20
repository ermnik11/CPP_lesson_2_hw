mkdir build

export ROOT_DIR=$(pwd)

cd build

cmake -DROOT_DIR="${ROOT_DIR}" \
    -DPATCH_VERSION=${{ github.run_number }} \
..

cmake --build .
cmake --build . --target package