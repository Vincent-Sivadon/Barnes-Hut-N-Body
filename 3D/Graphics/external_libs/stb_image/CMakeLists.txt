add_library(
    stb_image STATIC
    stb_image.h
    stb_image.cpp
    )

# Set include directory for the other files to call it
target_include_directories(stb_image PUBLIC .)
