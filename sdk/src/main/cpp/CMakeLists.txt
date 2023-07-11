cmake_minimum_required(VERSION 3.10.2)

message("CMAKE_SYSTEM_VERSION:" ${CMAKE_SYSTEM_VERSION})
set(CMAKE_VERBOSE_MAKEFILE on)

project("rpc4Android")


include_directories(${CMAKE_SOURCE_DIR}/third)


add_library(openssl-crypto STATIC IMPORTED)

set_target_properties(openssl-crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libcrypto.a)

add_library(openssl-ssl STATIC IMPORTED)

set_target_properties(openssl-ssl PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libssl.a)

add_library(cryptopp STATIC IMPORTED)
set_target_properties(cryptopp PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI}/libcryptopp.a)

add_library(protobuf STATIC IMPORTED)

set_target_properties(protobuf PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libprotobuf.a)

file(GLOB envelop_cpp "${CMAKE_CURRENT_SOURCE_DIR}/envelop/*.cpp")
file(GLOB sig_cpp "${CMAKE_CURRENT_SOURCE_DIR}/sig/*.cpp")

file(GLOB envelop_h "${CMAKE_CURRENT_SOURCE_DIR}/envelop/*.h")
file(GLOB sig_h "${CMAKE_CURRENT_SOURCE_DIR}/sig/*.h")

file(GLOB proto_cpp "${CMAKE_CURRENT_SOURCE_DIR}/third/proto/*.cc")

add_library(
        rpc4Android
        SHARED
        ${envelop_cpp}
        ${sig_cpp}
        ${proto_cpp}
        ${CMAKE_CURRENT_SOURCE_DIR}/src_envelop_Envelop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src_sig_sig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/jni_tools.cpp

)
target_include_directories(
        rpc4Android
        PRIVATE
        ${envelop_h}
        ${sig_h}
        ${CMAKE_CURRENT_SOURCE_DIR}/src_envelop_Envelop.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src_sig_sig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/jni_tools.h
)


find_library(
        log-lib
        log)

target_link_libraries(
        rpc4Android
        ${log-lib} openssl-ssl openssl-crypto protobuf cryptopp
)