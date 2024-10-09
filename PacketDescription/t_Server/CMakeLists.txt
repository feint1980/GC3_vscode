cmake_minimum_required(VERSION 3.2)
project("Chat Example")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x -l sqlite3")
#set (GCC_COMPILE_FLAGS "-fpermissive")



#set(CMAKE_CXX_FLAGS "${GCC_COMPILE_FLAGS}" "-fpermissive")

set(RAKNETLIBDIR /root/codes/RakNet/Lib/RakNetLibStatic)
set(RAKNETDIR /root/codes/RakNet)
set(RAKNETHEADERFILES /root/codes/RakNet/Source)
set(RAKNET_COMMON_LIBS ${RAKNETLIBDIR}/libRakNetLibStatic.a)

include_directories(${RAKNETDIR} ${RAKNETHEADERFILES} ./i ${RAKNETLIBDIR}) 
#include(${RAKNETDIR}/CmakeIncludes/CmakeMacros.txt ${RAKNETDIR}/CmakeIncludes/FindMacros.txt)


add_executable(RIMM_Server "main.cpp" "ServerHandler.cpp" "FileTransferHost.cpp" "DataBaseHandler.cpp")

#set_target_properties(ChatClient "-fpermissive")


find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
	target_compile_options(ChatClient PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
	target_link_libraries(RIMM_Server "${CMAKE_THREAD_LIBS_INIT}")
endif()


target_link_libraries(RIMM_Server ${RAKNET_COMMON_LIBS})

