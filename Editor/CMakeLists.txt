cmake_minimum_required(VERSION 3.10)

set(PROJECT_N "FeintEditor")
project(${PROJECT_N} VERSION 1.0)

set(CMAKE_CXX_FLAGS "-fpermissive -std=c++14")
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp 
    
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Player.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_MarisaRocket_small.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_BaseEnemy.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/GuardianShield.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/EnemyBulletBase.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_BulletBase.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/GlobalValueClass.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/Gohei_Rod.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/SealingAmulet.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Marisa_Star_Trail_Manager.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Marisa_Luminous_Strike_Launcher.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/SpellcardSelector.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_BulletStraight.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Marisa_Luminous_Strike.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_MarisaStar.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Marisa_Luminous_Charge.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Marisa_Laser_trail.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_PlayerAccessory.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_MarisaStarSpawner.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Player_Sun_Manager.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/SpellcardIcon.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/Yin_Yang_Orb.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Marisa_MasterSpark.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_MasterSpark_Wave.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Reimu_Demon_Binding.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Reimu_Fantasy_Seal_Obj.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/LabelItem.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Marisa_Star_Trail.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/Yin_Yang_Orb_Ex.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_MarisaLaser.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_SpriteObject.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_CollectableItem.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_HomingBullet.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_ReimuWave.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Orreries_Sun.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/ExplosionRing.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Non_Direction_Laser.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/KanjiEffectManager.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/KanjiEffect.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/EnemyGuardian.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Lua_Boss_Manager.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Lua_Boss_State.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Lua_Boss.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/FairyBase.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/KanjiEffectrObject.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_EnemyBasic.pp
    ${PROJECT_SOURCE_DIR}/../GC3/src/EnemyAmplifier.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/ScoreItem.cpp
    ${PROJECT_SOURCE_DIR}/../GC3/src/PowerItem.cpp
   

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


set(FEINTGINE_include_dir "E:/template/GC_port/Feintgine/src")
set(FEINTGINE_lib_dir "E:/template/GC_port/Feintgine/build")

set(GC3_include_dr "E:/template/GC_port/GC3/src")

set(GLEW_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")

#set(GLEW_include_dir_amend "E:/template/adaptation/glew/mingw64-x86_64-glew-2.1.0-1.src/glew-2.1.0/include/")
#set(GLEW_lib_dir "E:/template/adaptation/glew/mingw64-x86_64-glew-2.1.0-1.src/glew-2.1.0/lib/Release/Win32")
set(GLEW_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

set(CEGUI_include_dir  "E:/template/GC_port/Feintgine_GC_deps/include" )
# set(CEGUI_include_dir_amend "E:/template/adaptation/cegui_2/cegui-0.8.7/build_mw/cegui/include") # amend
set(CEGUI_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")
set(SDL_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(SDL_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")


set(SDL_TTF_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(SDL_TTF_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

set(SDL_net_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(SDL_net_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

# set(SDL_mixer_dir     "E:/template/adaptation/SDL2_mixer-2.6.3/x86_64-w64-mingw32/include/")
# set(SDL_mixer_lib_dir "E:/template/adaptation/SDL2_mixer-2.6.3/x86_64-w64-mingw32/lib")
set(SDL_mixer_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(SDL_mixer_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")
#set(SDL_include_dir_amend "C:/Program Files (x86)/SDL2/include/SDL2") suspect

set(PROTOBUF_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(PROTOBUF_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

set(LUA_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(LUA_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

set(FREETYPE_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(FREETYPE_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

set(FREEIMAGE_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(FREEIMAGE_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

set(ASSIMP_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
#set(ASSIMP_config_dir "E:/template/adaptation/assimp/build_mw/include")
set(ASSIMP_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

set(STB_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")


set(BOX2D_include_dir "E:/template/GC_port/Feintgine_GC_deps/include")
set(BOX2D_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

set(SQLITE_lib_dir "E:/template/GC_port/Feintgine_GC_deps/lib")

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
include_directories(${BOX2D_include_dir})

include_directories(${GC3_include_dr})

include_directories(${INCLUDES} ${FEINTGINE_include_dir} ${PROJECT_SOURCE_DIR}/include/)

add_executable(${PROJECT_N} ${SRCS})



target_include_directories(${PROJECT_N} PUBLIC include)

# target_link_libraries(${PROJECT_N} ${SDL_lib_dir}/libSDL2.a ${SDL_lib_dir}/libSDL2main.a  ${GLEW_lib_dir}/glew32s.lib ${CEGUI_lib_dir}/libCEGUIBase-0.dll.a ${CEGUI_lib_dir}/libCEGUIOpenGLRenderer-0.dll.a ${FREETYPE_lib_dir}/libfreetype.a ${PROTOBUF_lib_dir}/libprotobuf.a  ${PROTOBUF_lib_dir}/libprotoc.a ${SDL_net_lib_dir}/libSDL2_net.dll.a ${SDL_TTF_lib_dir}/libSDL2_ttf.a  ${SDL_mixer_lib_dir}/libSDL2_mixer.a  ${LUA_lib_dir}/liblua53.a ${FREEIMAGE_lib_dir}/libFreeImage.a ${ASSIMP_lib_dir}/libassimp.dll.a ${BOX2D_lib_dir}/libbox2d.a  ${FEINTGINE_lib_dir}/libFeintgine.a )  


target_link_libraries(${PROJECT_N}   ${FEINTGINE_lib_dir}/libFeintgine.a ${GLEW_lib_dir}/libglew32.dll.a  ${SDL_lib_dir}/libSDL2.dll.a  ${SDL_lib_dir}/libSDL2main.a  ${CEGUI_lib_dir}/libCEGUIBase-0.dll.a ${CEGUI_lib_dir}/libCEGUIOpenGLRenderer-0.dll.a  ${CEGUI_lib_dir}/libCEGUIExpatParser.dll.a ${SQLITE_lib_dir}/libsqlite3.a ${LUA_lib_dir}/liblua53.a  ${FREETYPE_lib_dir}/libfreetype.a ${PROTOBUF_lib_dir}/libprotobuf.a  ${PROTOBUF_lib_dir}/libprotoc.a ${PROTOBUF_lib_dir}/libprotobuf-lite.a ${SDL_net_lib_dir}/libSDL2_net.dll.a  ${FREEIMAGE_lib_dir}/libFreeImage.a ${ASSIMP_lib_dir}/libassimp.dll.a ${BOX2D_lib_dir}/libbox2d.a  ${SDL_mixer_lib_dir}/libSDL2_mixer.dll.a  ${SDL_TTF_lib_dir}/libSDL2_ttf.dll.a  libopengl32.a libbz2.a -municode )  
