# Minimalna verzija CMake-a koja je potrebna
cmake_minimum_required(VERSION 3.10)

# Ime projekta
project(filemanager C)

# Postavi GCC kao kompajler
#set(CMAKE_C_COMPILER gcc)

# Uključi sve zaglavne fajlove iz trenutnog direktorijuma
include_directories(${CMAKE_filemanager_DIR})

#dodaj subdirectories
add_subdirectory(compressor)
add_subdirectory(json)

set(EXECUTABLE_SOURCES
    main.c
    
)

add_executable(file_manager ${EXECUTABLE_SOURCES})

target_link_libraries(file_manager PRIVATE compressor_lib)
target_link_libraries(file_manager PRIVATE json_lib)


# Specifične zastavice za GCC kompajler
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

# Linkovanje sa potrebnim bibliotekama ako ih ima (npr. math.h, ali ovde nije potrebno)
# target_link_libraries(calculator m)
