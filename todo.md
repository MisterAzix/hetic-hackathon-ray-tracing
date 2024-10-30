# Backlog Raytracer

## 1. Configuration initiale
- [x] Créer la structure du projet
- [x] Mettre en place l'environnement de développement
- [x] Créer les classes de base (Point, Vecteur)
- [x] Implémenter les opérations mathématiques vectorielles de base

## 2. Structures fondamentales
- [x] Implémenter la classe Scene
	- background 
	- foreground
- [x] coordoné des objet *on going*
- [x] Implémenter la classe Camera
	- projection plan
	- distance par rapport au plan 
	- dim (xy) = resolution 
- [x] Créer la classe Image pour le stockage du résultat
	-  done ? 
- [ ] Implémenter les structures de couleur (RGB) ? *on going* (Doriane)

## 3. Objets géométriques basiques
- [x] Implémenter la classe abstraite Objet 
- [x] Implémenter la classe Sphere *on going*
  - [x] Calcul d'intersection rayon-sphère *on going*
  - [x] Calcul de la normale au point d'intersection
- [X] Implémenter la classe Plan
- [x] Implémenter la classe Triangle
  - [x] Calcul d'intersection rayon-triangle
  - [x] Gestion des coordonnées barycentriques

## 4. Algorithme de base du raytracer
- [x] Implémenter la fonction principale lancerDeRayons()
- [x] Implémenter la génération des rayons primaires
- [x] Implémenter la recherche d'intersection la plus proche *on going*
- [x] Gérer la couleur de fond (background)

## 5. Éclairage et ombres
- [ ] Implémenter la classe Source Lumineuse
- [ ] Implémenter le calcul de la lumière diffuse (loi de Lambert)
- [ ] Ajouter la gestion des rayons d'ombre *on going*
- [ ] Implémenter la lumière ambiante basique *on going*

## 6. Réflexions
- [x] Implémenter le calcul du rayon réfléchi
  - [x] Formule de réflexion: R = I - 2(N·I)N
- [x] Gérer la récursivité des rayons réfléchis
- [x] Implémenter les coefficients de réflexion des matériaux
- [ ] Ajouter la limite de profondeur de récursion

## 7. Réfractions
- [ ] Implémenter le calcul du rayon réfracté (loi de Snell)
- [ ] Gérer les indices de réfraction des matériaux
- [ ] Implémenter la gestion de la réflexion totale
- [ ] Gérer la récursivité des rayons transmis

## 8. Matériaux
- [ ] Créer la classe Matériau
- [ ] Implémenter les propriétés de surface (diffusion, réflexion, transmission)
- [ ] Ajouter les indices de réfraction
- [ ] Gérer les coefficients de Fresnel

## 9. Optimisations
### 9.1 Optimisations géométriques
- [ ] Implémenter les boîtes englobantes (Bounding Boxes)
- [ ] Créer la structure de voxels
- [ ] Implémenter l'algorithme de parcours des voxels

### 9.2 Optimisations des calculs
- [ ] Mettre en place le multi-threading
- [ ] Optimiser les calculs d'intersection
- [ ] Implémenter la projection préalable pour les rayons primaires

## 10. Fonctionnalités avancées
- [ ] Ajouter le support pour les textures
- [ ] Implémenter l'antialiasing
- [ ] Ajouter la profondeur de champ
- [ ] Implémenter les effets de caustique basiques

(optional)
## 11. Interface utilisateur
- [ ] Créer une interface pour charger les scènes
- [ ] Ajouter les contrôles de caméra
- [ ] Implémenter la prévisualisation en temps réel
- [ ] Ajouter les options de rendu (résolution, profondeur de récursion)

## 13. Documentation
- [ ] Documenter l'architecture du système
- [ ] Créer des guides d'utilisation
- [ ] Documenter les formules mathématiques utilisées
- [ ] Créer des exemples de scènes
