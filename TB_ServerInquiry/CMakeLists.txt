cmake_minimum_required(VERSION 3.10)

set(PROJECT_N TB_ServerInquiry)
project(${PROJECT_N} VERSION 1.0)

set(CMAKE_CXX_FLAGS "-fpermissive -std=c++17 -municode -m32")
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/../PacketDescription/NetworkPacket.cpp

)

# a macro that gets all of the header containing directories. 
MACRO(header_directories return_list includes_base_folder extention )
    FILE(GLOB_RECURSE new_list ${includes_base_folder}/*.${extention})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

# using said macro.
header_directories(INCLUDES ${PROJECT_SOURCE_DIR}/include/ hpp)

message("src files:")
foreach(file ${SRCS})
        message(STATUS ${file})
endforeach()

message("include directories:")
foreach(dir ${INCLUDES})
        message(STATUS ${dir})
endforeach()


set(FEINTGINE_include_dir  ${PROJECT_SOURCE_DIR}/../Feintgine/src)
set(FEINTGINE_lib_dir ${PROJECT_SOURCE_DIR}/../Feintgine/build)

set(DEPS_include_dir  ${PROJECT_SOURCE_DIR}/../Feintgine_GC_deps/include)
set(DEPS_lib_dir  ${PROJECT_SOURCE_DIR}/../Feintgine_GC_deps/lib)

set(Packet_include_dir  ${PROJECT_SOURCE_DIR}/../PacketDescription/)

include_directories(${DEPS_include_dir} ${Packet_include_dir})

include_directories(${INCLUDES} ${FEINTGINE_include_dir} ${PROJECT_SOURCE_DIR}/include/)



add_executable(${PROJECT_N} ${SRCS})

target_include_directories(${PROJECT_N} PUBLIC include)

target_link_libraries(${PROJECT_N} ${FEINTGINE_lib_dir}/libFeintgine.a  ${DEPS_lib_dir}/libsqlite3.a ${DEPS_lib_dir}/liblua53.a  ${DEPS_lib_dir}/libprotobuf.a  ${DEPS_lib_dir}/libprotoc.a ${DEPS_lib_dir}/libprotobuf-lite.a  ${DEPS_lib_dir}/libRakNetLibStatic.a ${DEPS_lib_dir}/mbedtls/libmbedcrypto.a ${DEPS_lib_dir}/mbedtls/libmbedtls.a ${DEPS_lib_dir}/mbedtls/libmbedx509.a  ${DEPS_lib_dir}/mbedtls/libp256m.a  ${DEPS_lib_dir}/mbedtls/libeverest.a  libbz2.a libws2_32.a -municode -lbcrypt )  
