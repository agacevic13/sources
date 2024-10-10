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
#add_subdirectory(json)

set(EXECUTABLE_SOURCES
    json/main.c
    json/cjson.c
)

add_executable(my_executable ${EXECUTABLE_SOURCES})

target_link_libraries(my_executable PRIVATE compressor_lib)
# Kreiraj izvršni fajl pod imenom "calculator"
#add_executable(filemanager ${SOURCES})

# Specifične zastavice za GCC kompajler
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

# Linkovanje sa potrebnim bibliotekama ako ih ima (npr. math.h, ali ovde nije potrebno)
# target_link_libraries(calculator m)
