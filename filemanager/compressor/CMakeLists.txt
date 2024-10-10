# Minimalna verzija CMake-a koja je potrebna
cmake_minimum_required(VERSION 3.10)

# Ime projekta
project(json C)

# Postavi GCC kao kompajler
set(CMAKE_C_COMPILER gcc)

# Uključi sve zaglavne fajlove iz trenutnog direktorijuma
include_directories(${CMAKE_compressor_DIR})

# Dodaj izvorne fajlove
set(compressor
    miniz.c
    miniz_tdef.c
    miniz_tinfl.c
    input.c
    # Dodaj test.c ovde
)

# Kreiraj izvršni fajl pod imenom "calculator"
#add_executable(miniz ${SOURCES})

add_library(compressor_lib STATIC ${compressor})
target_include_directories(compressor_lib PUBLIC ${CMAKE_CURRENT_compressor_DIR})

# Specifične zastavice za GCC kompajler
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

# Linkovanje sa potrebnim bibliotekama ako ih ima (npr. math.h, ali ovde nije potrebno)
# target_link_libraries(calculator m)
