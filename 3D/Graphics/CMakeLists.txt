string(ASCII 27 ESCAPE)
message("${ESCAPE}[1;36m")
message(" =================================== BUILD ===================================")
message("
    Pour constuire le projet :  
    ```
        mkdir build  
        cd build  
        cmake ..  
    ```
    Pour construire tout les exectuables : `make`  

")
message(" ======================== LISTE DES EXECUTABLES ET MACRO ========================")
message("
    ## Liste des executables
    Tout les executables vont être dans le répertoire build.  
    * nbody   : simulation 3D graphique du problème des N-Corps
")
message(" ============================== STRUCTURE DU PROJET ==============================")
message("
    La hiérarchie est la suivante :
    * simulation : librairie qui permet la mise à jour des positions des corps
        * box          : notions relatives aux boites 3D
        * init         : initialisation de la simulation (vitesses et matrices de model)
        * octree       : code relatifs aux octree
        * simulation   : calculs sur les positions
        les headers sont dans le dossier include, et les implémentations dans le dossier src
    * external_libs    : code source et build des librairies externes nécessaires au code
        * glad
        * glm
        * imgui
        * stb_image
    * mylib            : librairie d'abstraction des concepts liés à OpenGL
    * resources        : contient le modèle d'un cube
    * shaders          : programme graphique GPU lié à la visualisation
")
message(" ============================== ATTENTION ==============================")
message("
    Librairies externes dont le code source n'est pas présent dans le dossier (à venir)
        - glfw     (gestion de la fenêtre)
        - assimp   (gestion des modèles)
")
message("${ESCAPE}[0m")




cmake_minimum_required(VERSION 3.12)
project(NBODY VERSION 0.1.0) 


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