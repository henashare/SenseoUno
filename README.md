# <div align="center"> Bibliothèque *SenseoUno* </div>
## Bibliothèque pour le pilotage d'une machine à café Senseo à partir d'un Arduino Uno.
## La bibliothèque fonctionne *uniquement* pour les microcontrôleurs basés sur l'Arduino Uno.

L'implémentation de la bibliothèque est disponible dans les fichiers sources : SenseoUno.h et SenseoUno.cpp.

La bibliothèque est basée sur un shield réalisé dans un cadre pédagogique. Ce shield offre les possibilités suivantes :
* Pilotage d'une résistance chauffante 230V via relais.
* Pilotage d'une pompe 230V via relais.
* Utilisation de trois boutons-poussoirs NO.
* Vérifications de niveaux d'eau via capteurs à effet Hall : soit un seul niveau, soit deux niveaux (une tasse ou deux tasses).
* Une LED de type RGB, ou trois LEDs à couleur unique.
* Un capteur de température analogique de type NTC.
* Un module bluetooth utilisable via les broches UART du microcontrôleur (les broches Rx et Tx).

La bibliothèque part de cette configuration. Le code généré permet avant tout de piloter une machine Senseo avec ce shield, mais il est possible d'utiliser la bibliothèque pour d'autres configurations. Reprécisons que la bibliothèque ne fonctionne que sur les microcontrôleurs AtMega328 et ses variantes (AtMega328P, AtMega328P-PU, etc), ainsi que sur les AtMega168 et ses variantes. La bibliothèque est de type P.O.O (Programmation Orientée Objet). Voir le sketch dans le dossier "examples" de ce répertoire.
