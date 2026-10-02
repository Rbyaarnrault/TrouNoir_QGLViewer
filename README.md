# 🌌 Black Hole Particle Simulation - C++ & OpenGL

[![C++](https://img.shields.io/badge/C++-11%2B-blue.svg)](https://isocpp.org/)
[![OpenGL](https://img.shields.io/badge/OpenGL-3.3-green.svg)](https://www.opengl.org/)
[![libQGLViewer](https://img.shields.io/badge/libQGLViewer-2.7.2-orange.svg)](http://libqglviewer.com/)
[![Status](https://img.shields.io/badge/Status-Completed-success.svg)]()

Un moteur de simulation physique temps réel codé en C++ développant un système de particules soumis à des champs de forces tridimensionnels. Le projet simule le comportement cinématique de 10 000 particules interagissant avec une singularité (trou noir) sous la forme d'un typhon.

🎬 **[Voir la démonstration vidéo du projet sur YouTube](https://youtu.be/vOe1TDQWrso)**

<a href="https://youtu.be/vOe1TDQWrso">
  <img src="https://img.youtube.com/vi/vOe1TDQWrso/maxresdefault.jpg" alt="Démonstration Vidéo Trou Noir" width="600"/>
</a>

## 🎯 Objectifs Techniques

Ce projet a été développé avec une approche technique forte, axée sur la résolution de problèmes mathématiques et l'optimisation mémoire :
- Implémentation from scratch d'un moteur physique (Lois de Newton, Intégration d'Euler).
- Calcul matriciel et vectoriel dans un espace 3D.
- Gestion optimisée de la mémoire via le design pattern *Object Pooling* pour garantir un framerate élevé sans *Garbage Collection* ou allocations dynamiques lourdes.

## ⚙️ Fonctionnalités & Implémentation Mathématique

### 1. Champs de Forces Combinés
Le système calcule la force nette appliquée à chaque particule en combinant deux vecteurs distincts :
- **Un Puits Gravitationnel (Sink) :** Force d'attraction linéaire pointant vers le centre de la singularité.
- **Un Vortex :** Force centrifuge calculée à partir du produit vectoriel (`^`) entre l'axe d'ordonnée (Y) et le vecteur de direction, générant le mouvement de giration.

```cpp
// Normalisation et calcul vectoriel du vortex
directionVortex.normalize();
Vec axeY(0.0f, 1.0f, 0.0f);
Vec forceVortex = (axeY ^ directionVortex) * intensVortex;

### 2. Intégration Numérique & Cinématique
Le mouvement est calculé à chaque frame (dt = 0.014f) en respectant la seconde loi de Newton ($a = \frac{\Sigma F}{m}$). Un coefficient d'amortissement (damping) de 0.94 dissipe l'énergie pour forcer les particules à orbiter en spirale plongeante vers l'horizon des événements

```cpp
// Seconde loi de Newton
Vec acc = sommeForce / particules[i].masse; 
particules[i].vitesseCour += acc * dt;

// Application du frottement spatial et limitation de vélocité
particules[i].vitesseCour *= 0.94f;
if (particules[i].vitesseCour.norm() > vitesseMax) {
    // Clamping de la vitesse
}
```

### 3. Génération Procédurale Biaisée & Object Pooling
Plutôt que d'instancier et de détruire des objets, les particules franchissant l'horizon des événements sont instantanément réinitialisées au sommet du typhon.
Les caractéristiques physiques (masse et spectre colorimétrique) sont attribuées via une fonction de distribution cubique, favorisant massivement l'apparition de poussières légères face aux objets lourds.

```cpp
// Biais probabiliste cubique pour une distribution asymétrique des masses
float r = (float)rand() / RAND_MAX;
particules[i].masse = 0.1f + (r * r * r) * 4.0f;
```

### 🛠️ Dépendances & Compilation
Ce projet requiert :
- C++ Compilateurs
- Qt(Core, Gui, OpenGL)
- libQGLViewer

Une fois le Répertoire télécharger, il faut le posititioner dans:
`libQGLViewer-main\examples`.

Ensuite, Si vous voulez récréer les dépendances, le makefile, il faut faire:

```bash
qmake
```
puis
```bash
make
```
L'éxecution se fait via ce nom (ou autre si vous l'avez changé dans le .pro)
```bash
./trounoir 
```

### 👨‍💻 À propos de l'auteur
Étudiant avec un profil de "faiseur", passionné par la résolution de problèmes algorithmiques, le développement logiciel et l'informatique graphique concrète.

Recherche active : Actuellement à la recherche d'un stage de fin d'études dans la région de Tours ou de Châteauroux (Animation 2D/3D graphique(Modélisation, Rigging, squellettes...) , Conception et Développement Logiciel C++/Java/Python). N'hésitez pas à me contacter si vous recherchez un profil curieux et motivé pour s'investir dans des workflows de production réels.