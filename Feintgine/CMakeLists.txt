cmake_minimum_required(VERSION 3.0.0)
project(new_project VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB TARGET_SRC "./src/*.cpp" )

set(CMAKE_CXX_FLAGS "-fpermissive -std=c++14")

set(Generic_include_dir "E:/template/GC_port/Feintgine/include")

set(GLEW_include_dir "E:/template/adaptation/glew/mingw64-x86_64-glew-2.1.0-1.src/glew-2.1.0/include/GL")

set(GLEW_include_dir_amend "E:/template/adaptation/glew/mingw64-x86_64-glew-2.1.0-1.src/glew-2.1.0/include/")
#set(GLEW_lib_dir "E:/template/adaptation/glew/mingw64-x86_64-glew-2.1.0-1.src/glew-2.1.0/lib/Release/Win32")
set(GLEW_lib_dir "E:/template/adaptation/glew2/glew/build/cmake/build/lib")

set(CEGUI_include_dir  "E:/template/adaptation/cegui_2/cegui-0.8.7/cegui/include" )
set(CEGUI_include_dir_amend "E:/template/adaptation/cegui_2/cegui-0.8.7/build_mw/cegui/include") # amend
set(CEGUI_lib_dir "E:/template/adaptation/cegui_2/cegui-0.8.7/build_mw/lib")
set(SDL_include_dir "C:/Program Files (x86)/SDL2/include")
set(SDL_lib_dir "E:/template/adaptation/SDL2-2.0.16/build_mw")


set(SDL_TTF_include_dir "E:/template/adaptation/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include")
set(SDL_TTF_lib_dir "E:/template/adaptation/SDL2_ttf-2.20.2/x86_64-w64-mingw32/lib")

set(SDL_net_include_dir "C:/Program Files\ (x86)/SDL2_net/include")
set(SDL_net_lib_dir "C:/Program Files (x86)/SDL2_net/lib")

# set(SDL_mixer_dir     "E:/template/adaptation/SDL2_mixer-2.6.3/x86_64-w64-mingw32/include/")
# set(SDL_mixer_lib_dir "E:/template/adaptation/SDL2_mixer-2.6.3/x86_64-w64-mingw32/lib")
set(SDL_mixer_dir     "E:/template/adaptation/SDL2_mixer-2.0.0/x86_64-w64-mingw32/include")
set(SDL_mixer_lib_dir "E:/template/adaptation/SDL2_mixer-2.0.0/x86_64-w64-mingw32/lib")
set(SDL_include_dir_amend "C:/Program Files\ (x86)/SDL2/include/SDL2")

set(PROTOBUF_include_dir "C:/Program Files (x86)/protobuf/include")
set(PROTOBUF_lib_dir "C:/Program Files (x86)/protobuf/lib")

set(LUA_include_dir "E:/template/adaptation/lua-5.3_Win32_mingw4_lib/include")
set(LUA_lib_dir "E:/template/adaptation/lua-5.3_Win32_mingw4_lib/")

set(FREETYPE_include_dir "C:/Program Files (x86)/freetype/include/freetype2")
set(FREETYPE_lib_dir "C:/Program Files (x86)/freetype/lib")

set(FREEIMAGE_include_dir "C:/Program\ Files\ (x86)/FreeImage/include")
set(FREEIMAGE_lib_dir "E:/template/adaptation/FreeImage/build_mw3")

set(ASSIMP_include_dir "E:/template/adaptation/assimp/include")
set(ASSIMP_config_dir "E:/template/adaptation/assimp/build_mw/include")
set(ASSIMP_lib_dir "E:/template/adaptation/assimp/build_mw/lib")

set(STB_include_dir "E:/template/adaptation/stb")

include_directories(${SDL_include_dir})
include_directories(${GLEW_include_dir})
include_directories(${GLEW_include_dir_amend})
include_directories(${SDL_mixer_dir})
include_directories(${SDL_include_dir_amend})
include_directories(${Generic_include_dir})
include_directories(${PROTOBUF_include_dir})
include_directories(${CEGUI_include_dir})
include_directories(${CEGUI_include_dir_amend})
include_directories(${SDL_net_include_dir})
include_directories(${LUA_include_dir})
include_directories(${FREETYPE_include_dir})
include_directories(${FREEIMAGE_include_dir})
include_directories(${SDL_TTF_include_dir})
include_directories(${ASSIMP_include_dir})
include_directories(${ASSIMP_config_dir})
include_directories(${STB_include_dir})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_library(Feintgine STATIC
    ${TARGET_SRC}
)

target_link_libraries(Feintgine ${SDL_lib_dir}/libSDL2.a ${SDL_lib_dir}/libSDL2main.a  ${GLEW_lib_dir}/glew32s.lib ${CEGUI_lib_dir}/libCEGUIBase-0.dll.a ${CEGUI_lib_dir}/libCEGUIOpenGLRenderer-0.dll.a  ${CEGUI_lib_dir}/libCEGUIExpatParser.dll.a ${FREETYPE_lib_dir}/libfreetype.a ${PROTOBUF_lib_dir}/libprotobuf.a  ${PROTOBUF_lib_dir}/libprotoc.a ${PROTOBUF_lib_dir}/libprotobuf-lite.a   ${SDL_net_lib_dir}/libSDL2_net.dll.a ${SDL_TTF_lib_dir}/libSDL2_ttf.a  ${SDL_mixer_lib_dir}/libSDL2_mixer.a  ${LUA_lib_dir}/liblua53.a ${FREEIMAGE_lib_dir}/libFreeImage.a ${ASSIMP_lib_dir}/libassimp.dll.a libopengl32.a )


