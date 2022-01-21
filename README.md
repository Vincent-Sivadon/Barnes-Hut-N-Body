# Barnes-Hut-N-Body

# Simulation 3D (OpenGL)
![GL](nbodyShort.gif "GL")

![GL2](nbody.gif "GL2")

Video capturée pour la simulation de 20 000 corps.

# Simulation 2D (SDL)
![10000](10000bodies.gif "10000")
Vidéo capturée pour la simulation de 10 000 corps réparti uniformément.

# Structure du dépôt

### 2D
  - nbody0.c : code de base 2D
  - nbodyASM.c : version assembleur des fonctions principales
  - nbodySOA.c : version SOA + optimisations
  - QUAD
  	- codes relatifs à l'implémentation 2D de l'approximation de Barnes-Hut
  - bin
    - contient les executables une fois compilés
  - data
    - data_processing : scripts de traitement de données
    - files : données
  - makefile : à lire pour la liste des cibles

### 3D
  - 0
    - code de base 3D
  - OCTREE : 
    - codes relatifs à l'implémentation 2D de l'approximation de Barnes-Hut
   - Graphics
     - codes relatifs à la visualisation 3D sous OpenGL : LIRE le CMakeLists.txt pour plus d'informations
   - SOA
     - version SOA + optimisations
   - data
     - data_processing : scripts de traitement de données
     - files : données