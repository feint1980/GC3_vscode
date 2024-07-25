cmake_minimum_required(VERSION 3.0.0)
project(new_project VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB TARGET_SRC "./src/*.cpp")

set(CMAKE_CXX_FLAGS "-fpermissive -std=c++17 -O3")

set(Generic_include_dir ${PROJECT_SOURCE_DIR}/../Feintgine/include)

set(DEPS_include_dir  ${PROJECT_SOURCE_DIR}/../Feintgine_GC_deps/include)
set(DEPS_lib_dir  ${PROJECT_SOURCE_DIR}/../Feintgine_GC_deps/lib)

include_directories(${DEPS_include_dir} ${Generic_include_dir})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_library(Feintgine STATIC
    ${TARGET_SRC}
)

target_link_libraries(Feintgine ${DEPS_lib_dir}/libSDL2.a ${DEPS_lib_dir}/libSDL2main.a  ${DEPS_lib_dir}/glew32s.lib ${DEPS_lib_dir}/libCEGUIBase-0.dll.a ${DEPS_lib_dir}/libCEGUIOpenGLRenderer-0.dll.a  ${DEPS_lib_dir}/libCEGUIExpatParser.dll.a ${DEPS_lib_dir}/libfreetype.a ${DEPS_lib_dir}/libprotobuf.a  ${DEPS_lib_dir}/libprotoc.a ${DEPS_lib_dir}/libprotobuf-lite.a   ${DEPS_lib_dir}/libSDL2_net.dll.a ${DEPS_lib_dir}/libSDL2_ttf.dll.a   ${DEPS_lib_dir}/libSDL2_mixer.dll.a  ${DEPS_lib_dir}/liblua53.a ${DEPS_lib_dir}/libFreeImage.a ${DEPS_lib_dir}/libassimp.dll.a ${DEPS_lib_dir}/libnanogui.dll.a libopengl32.a )


