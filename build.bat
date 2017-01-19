@set PROJDIR=%~dp0%

@md build
@cd build

@call %PROJDIR%tools/xilinx_env.bat

cmake -Wno-dev -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=%PROJDIR%config/xilinx-powerpc.cmake ..
cmake --build .
make install

@cd ..
@pause
