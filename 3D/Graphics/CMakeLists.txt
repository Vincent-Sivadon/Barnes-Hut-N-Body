cmake_minimum_required(VERSION 3.12)
project(NBODY VERSION 0.1.0) 

include(CTest)
enable_testing()
#add_subdirectory(tests)

find_package(glfw3 REQUIRED)

add_subdirectory(external_libs)
add_subdirectory(mylib)
add_subdirectory(simulation)

set(LIBS
    mylib
    simulation
    glfw
    glad
    stb_image
    glm
    assimp
    imgui
    )


# ============================================= GENERATION DES EXECUTABLES =============================================
# récupération de tout les fichiers sources
file( GLOB SRCS "*.cpp" )
# pour chacun de ces fichiers sources
foreach( source ${SRCS} )
    # passage de path absolu à relatif
    string( REPLACE ".cpp" "" source_name ${source} )
    string( REPLACE ${CMAKE_SOURCE_DIR}/ "" source_name ${source_name} )
    # on créé l'executable
    add_executable( ${source_name} ${source} )
    # on link les librairies
    target_link_libraries( ${source_name} ${LIBS} )
    # flags de compilation
    target_compile_options(${source_name} PUBLIC -g)
endforeach( source ${TEST_SRCS} )