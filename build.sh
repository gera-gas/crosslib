PROJDIR=`pwd`

mkdir -p build
cd build

cmake -Wno-dev -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$PROJDIR/config/gcc.cmake ..
cmake --build .
make install

cd ..

