<<<<<<< HEAD
# Getting started with Blinky on mbed OS

This is a very simple guide, reviewing the steps required to get Blinky working on an mbed OS platform.

Please install [mbed CLI](https://github.com/ARMmbed/mbed-cli#installing-mbed-cli).

## Get the example application!

From the command line, import the example:

```
mbed import mbed-os-example-blinky
cd mbed-os-example-blinky
```

### Now compile

Invoke `mbed compile` specifying the name of your platform and your favorite toolchain (`GCC_ARM`, `ARM`, `IAR`). For example, for the ARM Compiler 5:

export PATH=$PATH:/opt/gcc-arm-none-eabi/bin/

```
mbed toolchain GCC_ARM
mbed target nucleo_f767zi
mbed compile
```
Your PC may take a few minutes to compile your code. At the end you should get the following result:

```
[snip]
+----------------------------+-------+-------+------+
| Module                     | .text | .data | .bss |
+----------------------------+-------+-------+------+
| Misc                       | 13939 |    24 | 1372 |
| core/hal                   | 16993 |    96 |  296 |
| core/rtos                  |  7384 |    92 | 4204 |
| features/FEATURE_IPV4      |    80 |     0 |  176 |
| frameworks/greentea-client |  1830 |    60 |   44 |
| frameworks/utest           |  2392 |   512 |  292 |
| Subtotals                  | 42618 |   784 | 6384 |
+----------------------------+-------+-------+------+
Allocated Heap: unknown
Allocated Stack: unknown
Total Static RAM memory (data + bss): 7168 bytes
Total RAM memory (data + bss + heap + stack): 7168 bytes
Total Flash memory (text + data + misc): 43402 bytes
Image: .\.build\K64F\ARM\mbed-os-example-blinky.bin
```



## Troubleshooting

1. Make sure `mbed-cli` is working correctly and its version is greater than `0.8.9`

 ```
 mbed --version
 ```

 If not, you can update it easily:

 ```
 pip install mbed-cli --upgrade
 ```
