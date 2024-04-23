cmake_minimum_required(VERSION 3.10)

set(PROJECT_N "FeintEditor")
project(${PROJECT_N} VERSION 1.0)

set(CMAKE_CXX_FLAGS "-fpermissive -std=c++17")
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
    ${PROJECT_SOURCE_DIR}/../GC3/src/BackGroundMap.cpp
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
    ${PROJECT_SOURCE_DIR}/../GC3/src/F_Komachi_Souls_Object.cpp

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

set(GC3_include_dir  ${PROJECT_SOURCE_DIR}/../GC3/src)

set(DEPS_include_dir  ${PROJECT_SOURCE_DIR}/../Feintgine_GC_deps/include)
set(DEPS_lib_dir  ${PROJECT_SOURCE_DIR}/../Feintgine_GC_deps/lib)


include_directories(${DEPS_include_dir} ${GC3_include_dir})

include_directories(${INCLUDES} ${FEINTGINE_include_dir} ${PROJECT_SOURCE_DIR}/include/)

add_executable(${PROJECT_N} ${SRCS})



target_include_directories(${PROJECT_N} PUBLIC include)

# target_link_libraries(${PROJECT_N} ${SDL_lib_dir}/libSDL2.a ${SDL_lib_dir}/libSDL2main.a  ${GLEW_lib_dir}/glew32s.lib ${CEGUI_lib_dir}/libCEGUIBase-0.dll.a ${CEGUI_lib_dir}/libCEGUIOpenGLRenderer-0.dll.a ${FREETYPE_lib_dir}/libfreetype.a ${PROTOBUF_lib_dir}/libprotobuf.a  ${PROTOBUF_lib_dir}/libprotoc.a ${SDL_net_lib_dir}/libSDL2_net.dll.a ${SDL_TTF_lib_dir}/libSDL2_ttf.a  ${SDL_mixer_lib_dir}/libSDL2_mixer.a  ${LUA_lib_dir}/liblua53.a ${FREEIMAGE_lib_dir}/libFreeImage.a ${ASSIMP_lib_dir}/libassimp.dll.a ${BOX2D_lib_dir}/libbox2d.a  ${FEINTGINE_lib_dir}/libFeintgine.a )  


target_link_libraries(${PROJECT_N}   ${FEINTGINE_lib_dir}/libFeintgine.a ${DEPS_lib_dir}/libglew32.dll.a  ${DEPS_lib_dir}/libSDL2.dll.a  ${DEPS_lib_dir}/libSDL2main.a  ${DEPS_lib_dir}/libCEGUIBase-0.dll.a ${DEPS_lib_dir}/libCEGUIOpenGLRenderer-0.dll.a  ${DEPS_lib_dir}/libCEGUIExpatParser.dll.a ${DEPS_lib_dir}/libsqlite3.a ${DEPS_lib_dir}/liblua53.a  ${DEPS_lib_dir}/libfreetype.a ${DEPS_lib_dir}/libprotobuf.a  ${DEPS_lib_dir}/libprotoc.a ${DEPS_lib_dir}/libprotobuf-lite.a ${DEPS_lib_dir}/libSDL2_net.dll.a  ${DEPS_lib_dir}/libFreeImage.a ${DEPS_lib_dir}/libassimp.dll.a ${DEPS_lib_dir}/libbox2d.a  ${DEPS_lib_dir}/libSDL2_mixer.dll.a  ${DEPS_lib_dir}/libSDL2_ttf.dll.a ${DEPS_lib_dir}/libnanogui.dll.a  ${DEPS_lib_dir}/libasync++.dll.a  libopengl32.a libbz2.a -municode )  
