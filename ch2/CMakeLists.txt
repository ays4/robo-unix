#project(robo_unix_ch2 C)
project(robo_unix C)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -D_XOPEN_SOURCE")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_C_STANDARD 11)

add_executable(daemon daemon.c)
add_executable(command_interpreter command_interpreter.c)