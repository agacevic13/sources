# Minimalna verzija CMake-a koja je potrebna
cmake_minimum_required(VERSION 3.10)

# Ime projekta
project(json C)

# Postavi GCC kao kompajler
set(CMAKE_C_COMPILER gcc)

# Uključi sve zaglavne fajlove iz trenutnog direktorijuma

# Dodaj izvorne fajlove
set(compressor
    miniz.c
    miniz_tdef.c
    miniz_tinfl.c
    input.c
    # Dodaj test.c ovde
)

add_library(compressor_lib STATIC ${compressor})


# Specifične zastavice za GCC kompajler
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

# Linkovanje sa potrebnim bibliotekama ako ih ima (npr. math.h, ali ovde nije potrebno)
# target_link_libraries(calculator m)
