@set PROJDIR=%~dp0%

@md build
@cd build

cmake -Wno-dev -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=%PROJDIR%config/msp430.cmake ..
cmake --build .
make install

@cd ..
@pause
