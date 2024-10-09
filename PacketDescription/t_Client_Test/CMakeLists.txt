cmake_minimum_required(VERSION 3.2)
project("Chat Example")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")


set(RAKNETLIBDIR /root/codes/RakNet/Lib/RakNetLibStatic)
set(RAKNETDIR /root/codes/RakNet)
set(RAKNETHEADERFILES /root/codes/RakNet/Source)
set(RAKNET_COMMON_LIBS ${RAKNETLIBDIR}/libRakNetLibStatic.a)

include_directories(${RAKNETDIR} ${RAKNETHEADERFILES} ./i ${RAKNETLIBDIR}) 


add_executable(RIMM_Client_Test "main.cpp" "ClientHandler.cpp" "ClientDownloadHandler.cpp")



find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
	target_compile_options(RIMM_Client_Test PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
	target_link_libraries(RIMM_Client_Test "${CMAKE_THREAD_LIBS_INIT}")
endif()


target_link_libraries(RIMM_Client_Test ${RAKNET_COMMON_LIBS})

