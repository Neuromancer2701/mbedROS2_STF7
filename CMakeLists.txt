cmake_minimum_required(VERSION 3.5)
project(mbed_os_example_blinky)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_definitions(-DTARGET_NUCLEO_F767ZI)
set(SOURCE_FILES main.cpp)

include_directories(mbed-os
        mbed-os/docs
        mbed-os/features
        mbed-os/features/frameworks
        mbed-os/features/frameworks/greentea-client
        mbed-os/features/frameworks/greentea-client/greentea-client
        mbed-os/features/frameworks/greentea-client/source
        mbed-os/features/frameworks/unity
        mbed-os/features/frameworks/unity/source
        mbed-os/features/frameworks/unity/unity
        mbed-os/features/frameworks/utest
        mbed-os/features/frameworks/utest/source
        mbed-os/features/frameworks/utest/utest
        mbed-os/features/mbedtls
        mbed-os/features/mbedtls/importer
        mbed-os/features/mbedtls/inc
        mbed-os/features/mbedtls/inc/mbedtls
        mbed-os/features/mbedtls/src
        mbed-os/features/net
        mbed-os/features/net/FEATURE_IPV4
        mbed-os/features/net/FEATURE_IPV4/lwip-interface
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip-eth -I.
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip-eth/arch
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip-eth/arch/TARGET_STM
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip-sys
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip-sys/arch
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/api
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/core
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/core/ipv4
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/core/snmp
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/include
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/include/ipv4
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/include/ipv4/lwip
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/include/lwip
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/include/netif
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/netif
        mbed-os/features/net/FEATURE_IPV4/lwip-interface/lwip/netif/ppp
        mbed-os/features/net/network-socket
        mbed-os/features/net/network-socket/DnsQuery
        mbed-os/features/storage
        mbed-os/hal
        mbed-os/hal/api
        mbed-os/hal/common
        mbed-os/hal/hal
        mbed-os/hal/hal/storage_abstraction
        mbed-os/hal/targets
        mbed-os/hal/targets/cmsis
        mbed-os/hal/targets/cmsis/TARGET_STM
        mbed-os/hal/targets/cmsis/TARGET_STM/TARGET_STM32F7
        mbed-os/hal/targets/cmsis/TARGET_STM/TARGET_STM32F7/TARGET_NUCLEO_F767ZI
        mbed-os/hal/targets/cmsis/TARGET_STM/TARGET_STM32F7/TARGET_NUCLEO_F767ZI/TOOLCHAIN_GCC_ARM
        mbed-os/hal/targets/cmsis/TOOLCHAIN_GCC
        mbed-os/hal/targets/hal
        mbed-os/hal/targets/hal/TARGET_STM
        mbed-os/hal/targets/hal/TARGET_STM/TARGET_STM32F7
        mbed-os/hal/targets/hal/TARGET_STM/TARGET_STM32F7/TARGET_NUCLEO_F767ZI
        mbed-os/rtos
        mbed-os/rtos/rtos
        mbed-os/rtos/rtx
        mbed-os/rtos/rtx/TARGET_CORTEX_M
        mbed-os/rtos/rtx/TARGET_CORTEX_M/TARGET_RTOS_M4_M7
        mbed-os/rtos/rtx/TARGET_CORTEX_M/TARGET_RTOS_M4_M7/TOOLCHAIN_GCC)


add_executable(mbed_os_example_blinky ${SOURCE_FILES})