# CPP Learning Project
## Rapport

### Les choix de l'architecture

L'architecture du projet suit les TASK et questions obligatoires. Aucune question facultative/optionnelle n'a été traitée. Il n'y a pas d'énorme écart avec ce qui est demandé.

### Situations bloquantes

Lors de la réalisation du projet, j'ai été confronté à deux problèmes majeurs. Le premier sur l'ownership les aircrafts et le second sur les variadic templates.

Pour l'ownership des aircrafts, j'avais oublié l'existence des unique_ptr ce qui rendait la chose bien plus compliquée. J'ai été débloqué par ma chargée de TP. De plus, j'ai eu des soucis de libération de terminaux lors de la suppression d'un avion. Pour bien les libérer, j'ai rajouté une gestion de libération dans le destructeur des avions.

Pour les variadic templates, qui sont la dernière notion vu en cours, je n'ai pas réussi à faire des constructeurs de copies pour faire fonctionner le constructeur par défaut. Les templates fonctionnent mais pas avec un nombre de paramètres variables. 

### Appréciations du projet

Le projet est très visuel et donc agréable pour comprendre si notre code fonctionne ou non. On est loin du debogage des erreurs de segmentations en C. La décomposition du projet en TASK et en questions guidées permet une appréhension simplefiée des problèmes.

Au delà du côté visuel, la principale source de frustration vient du langage. Même si le projet permet d'appliquer les notions vu en cours, les particularités du langage restent assez difficiles à maîtriser.

### Apprentissage

N'ayant jamais fait de C++, beaucoup de notions uniques au langage ont été apprises en parallèle du cours. Les tasks étant en adéquations avec les chapitres, cela permet de bien se rendre compte de l'application des fonctionnalités. 
Cependant, je ne sais pas si les notions apprises seront une évidence si je dois recoder en C++. Je pense que la durée de "manipulation" du langage est plutôt courte pour estimer pouvoir se débrouiller facilement dans ce langage.
