
### How to build
```
mkdir build_debug
cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug -DPICO_BOARD=pico ..
make -j4
```

### How to debug with openocd

In one terminal start OpenOCD
```
sudo openocd -f interface/cmsis-dap.cfg -c "adapter speed 5000" -f target/rp2040.cfg -s tcl
```

In another start `arm-none-eabi-gdb`

Inside debugger:
```
target remote localhost:3333  # only needed when started for the first time
load [file]
monitor reset init

# Now standard gdb commands
c
b
n
watch
print
```
