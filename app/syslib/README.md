## syslib
Library for system creation.

### multitask
Modules for creation multitask application.
* [pseudo thread](../demo/src/demo_pt.c) -- Pseudo thread control modules.
* [fixlock](../demo/src/demo_fixlock.c) -- Simple and fast non-blocking lock-free mechanism. Fixlock it's a fixing limit objects for synchronize. May be used for multi thread control and CPUs interaction through shared memory.

### hal
Hardware Abstraction Level (HAL). Example [here](src/hal/README.md#hal_uart_anchor).

### crc
Cyclic redundancy check functions.

### crypto
Cryptography functions.

### proto
Various protocols implementation.

### ui
Simple user interfaces implementation.
* [ui_input](src/ui/README.md#ui_input_anchor) -- Various user input helper through TTY (TeraTerm on Windows or Minicom on Linux).
* [ui_menu](src/ui/README.md#ui_menu_anchor) -- Various user menu helper through TTY (TeraTerm on Windows or Minicom on Linux).  
