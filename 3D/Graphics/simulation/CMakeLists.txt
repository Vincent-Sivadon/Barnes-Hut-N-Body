# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(simulation)

# Créé des variables avec les fichiers à compiler
file(GLOB SRCS
	"src/*.cpp"
)

file(GLOB HEADERS
	"include/*.h"
)

add_library(simulation ${SRCS} ${HEADERS})
target_link_libraries(simulation glad glm m)
target_include_directories(simulation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")