@set PROJDIR=%~dp0%

@md build
@cd build

cmake -Wno-dev -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=%PROJDIR%config/gcc.cmake .. -DBUILD_DEMO=TRUE
cmake --build .
make install

@cd ..
@pause
