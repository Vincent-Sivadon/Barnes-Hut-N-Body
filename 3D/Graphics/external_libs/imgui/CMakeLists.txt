# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(imgui)

# Créé des variables avec les fichiers à compiler
file(GLOB SRCS
	"src/*.cpp"
)

file(GLOB HEADERS
	"include/*.h"
)

add_library(imgui SHARED ${SRCS} ${HEADERS})
target_link_libraries(imgui)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")