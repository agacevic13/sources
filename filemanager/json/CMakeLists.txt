# Minimalna verzija CMake-a koja je potrebna
cmake_minimum_required(VERSION 3.10)

# Ime projekta
project(json C)

# Postavi GCC kao kompajler
set(CMAKE_C_COMPILER gcc)

# Uključi sve zaglavne fajlove iz trenutnog direktorijuma
include_directories(${CMAKE_json_DIR})

# Dodaj izvorne fajlove
set(json
    cJSON.c
    # Dodaj test.c ovde
)

add_library(json_lib STATIC ${json})

target_link_libraries(json_lib PRIVATE ${CMAKE_CURRENT_json_DIR})

# Specifične zastavice za GCC kompajler
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

# Linkovanje sa potrebnim bibliotekama ako ih ima (npr. math.h, ali ovde nije potrebno)
# target_link_libraries(calculator m)
