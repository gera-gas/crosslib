export projdir=`pwd`

mkdir -p build
cd build

$projdir/tools/xilinx_env.sh

cmake  -Wno-dev -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$projdir/config/xilinx-powerpc.cmake ..
cmake --build .
make install

cd ..
