projdir=`pwd`

mkdir -p build
cd build

$projdir/tools/xilinx/xilinx_env.sh

cmake  -Wno-dev -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$projdir/config/xilinx-powerpc.cmake ..
cmake --build .
make install

cd ..
