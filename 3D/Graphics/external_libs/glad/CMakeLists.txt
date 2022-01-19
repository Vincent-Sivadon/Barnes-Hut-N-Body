add_library(
    glad SHARED
    glad.h
    glad.c
    )

# Set include directory for the other files to call it
target_include_directories(glad PUBLIC .)
