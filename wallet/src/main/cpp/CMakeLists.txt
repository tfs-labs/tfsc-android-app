cmake_minimum_required(VERSION 3.10.2)

message("CMAKE_SYSTEM_VERSION:" ${CMAKE_SYSTEM_VERSION})
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_BUILD_TYPE Release)

project("rpc4Android")


include_directories(${CMAKE_SOURCE_DIR}/third)


#添加预编译库

add_library(openssl-crypto STATIC IMPORTED)

set_target_properties(openssl-crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libcrypto.a)

add_library(openssl-ssl STATIC IMPORTED)

set_target_properties(openssl-ssl PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libssl.a)

add_library(cryptopp STATIC IMPORTED)
set_target_properties(cryptopp PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI}/libcryptopp.a)

add_library(protobuf STATIC IMPORTED)

set_target_properties(protobuf PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libprotobuf.a)


#添加目标库
file(GLOB envelop_cpp "${CMAKE_CURRENT_SOURCE_DIR}/envelop/*.cpp")
file(GLOB sig_cpp "${CMAKE_CURRENT_SOURCE_DIR}/sig/*.cpp")
file(GLOB api_cpp "${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp")
file(GLOB evmone_cpp "${CMAKE_CURRENT_SOURCE_DIR}/evmone/*.cpp")

file(GLOB envelop_h "${CMAKE_CURRENT_SOURCE_DIR}/envelop/*.h")
file(GLOB sig_h "${CMAKE_CURRENT_SOURCE_DIR}/sig/*.h")
file(GLOB api_h "${CMAKE_CURRENT_SOURCE_DIR}/api/*.h")
file(GLOB evmone_h "${CMAKE_CURRENT_SOURCE_DIR}/evmone/*.h")
file(GLOB evmone_hpp "${CMAKE_CURRENT_SOURCE_DIR}/evmone/*.hpp")

file(GLOB proto_cpp "${CMAKE_CURRENT_SOURCE_DIR}/third/proto/*.cc")

add_library(
        rpc4Android
        SHARED
        ${envelop_cpp}
        ${sig_cpp}
        ${api_cpp}
        ${evmone_cpp}
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
        ${api_h}
        ${evmone_h}
        ${evmone_hpp}
        ${CMAKE_CURRENT_SOURCE_DIR}/src_envelop_Envelop.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src_sig_sig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/jni_tools.h
)





#查找android log库
find_library(
        log-lib
        log)


#编译关联目标库
target_link_libraries(
        rpc4Android
        ${log-lib} openssl-ssl openssl-crypto protobuf cryptopp
)