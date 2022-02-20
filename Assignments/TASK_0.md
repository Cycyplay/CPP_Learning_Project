# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?

-- Il faut appuyer sur la touche 'c'.

Comment faire pour quitter le programme ?

-- Il faut utiliser la touche 'x' ou 'q'.

A quoi sert la touche 'F' ?

-- La touche 'F' sert à activer/désactiver le mode plein écran.

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?

-- L'avion va atterrir, effectuer le débarquement de ses passagers, l'embarquement des nouveaux puis décoller. Il fait ça en boucle.

Quelles informations s'affichent dans la console ?

-- La console affiche les différentes action en cours d'un appareil grâce au nom de l'avion.

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

-- Tous les avions font les mêmes actions, mais attendent de pouvoir faire une action si il n'y a pas de place.

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

-- La liste des classes est:
- AircraftType : représente un type d'avion. Contient son image et ses différentes rapidité de déplacement.
- Aircraft : représente un avion. Contient les états d'un avion (position, vitesse...).
- AirportType : représente un type d'aéroport. Contient les positions des points d'intérêts d'un aéroport et la liste de ses pistes d'atterrisage. 
- Airport : représente un aéroport. Contient son type, ainsi que des références sur ces points d'intérêts.
- Point2D : représente des points sur deux axes.
- Point3D : représente des points sur trois axes.
- Terminal : représente un terminal de l'aéroport. Gère les avions qui sont au terminal.
- TowerSimulation : Représente la simulation. Classe principale du programme.
- Waypoint : indique l'état d'un avion.
- Runway : piste d'atterrisage.
- Tower : tour de contrôle. Gère les instructions pour les avions.

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

- Tower
  - `WaypointQueue get_instructions(Aircraft& aircraft);` : produit les instructions pour un avion. Peut le rapprocher de l'aéroport, sinon réserve un terminal pour faire atterrir l'avion. Peut ausi le faire redécoller si besoin. 
  - `void arrived_at_terminal(const Aircraft& aircraft);` : effectue les actions d'arrivée à un terminal pour l'avion aircraft.
- Aircraft
  - `const std::string& get_flight_num() const;` : Renvoie le numéro de vol de l'avion.
  - `float distance_to(const Point3D& p) const;` : Renvoie la distance de l'avion par rapport à un point donné.
  - `void display() const override;` : affiche l'avion à sa position.
  - `void move() override;` :  déplace l'avion dans la scène.
- Airport
  - `Tower& get_tower();` : renvoie la tour de contrôle associée à l'aéroport.
  - `void display() const override;` : affiche l'aéroport 
  - `void move() override;` : incrémente le progrès de service de chaque terminal attribué.
- Terminal
  - `bool in_use() const;` : renvoie si un terminal est utilisé par un avion ou non.
  - `bool is_servicing() const;` : renvoie si un terminal est encore en service.
  - `void assign_craft(const Aircraft& aircraft);` : assigne un avion au terminal.
  - `void start_service(const Aircraft& aircraft);` : commence le service d'un terminal 
  - `void finish_service();` : termine le service d'un terminal
  - `void move() override;` : incrémente le service d'un terminal.

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?

La classe Tower avec get_instructions, la classe waypoint qui représente des points de contrôle par lesquels doit passer un avion.

Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.

-- Le conteneur de la librairie standard choisi est deque. Il permet une insertion et une suppression très rapide au début et à la fin de la structure de données.

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

-- Si on met le framerate à 0, le programme s'arrête. (division par 0). 

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

-- On peut savoir que l'on peut supprimer un avion quand il ne possède plus de waypoint et qu'il a déjà atteri.\
Dans la fonction get_instructions de tower.cpp, cela correspond au bloc conditionel où est écrit le commentaire "get a path for the craft to start".\
Il n'est pas sûr de procéder au retrait de l'avion dans cette fonction car il la fonction move est appeler via un iterator sur le unordered_set move_queue. Quand on erase un élément, on finit par en sauter un élément de l'itérable.
Il faudrait donc transmettre l'information à la méthode timer et ensuite retirer les avions après être sorti de l'iterator.
J'ai donc changé la signature de la fonction move pour qu'elle renvoie un bool pour savoir si l'objet peut encore se déplacer ou non.


1) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
