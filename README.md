# <div align="center"> <ins>Bibliothèque SenseoUno :</ins> </div>

## <div align=justify>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Bibliothèque pour le pilotage d'une machine à café Senseo à partir d'une carte Arduino Uno. <ins>Attention :</ins> la bibliothèque fonctionne *uniquement* pour les microcontrôleurs basés sur l'Arduino Uno.</div>

#### <div align=justify>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<ins>Note :</ins> La bibliothèque est implémentée pour être utilisée à partir d'une carte Arduino Uno. Elle est faite pour être plus rapide que la bibliothèque Arduino lors de l'exécution du programme, d'où sa non-portabilité. En revanche, le référencement aux différents ports et registres est masqué par la bibliothèque. L'utilisateur "classique" ne sera donc pas dépaysé, et pourra coder son programme comme n'importe quel programme Arduino. Le code sera plus rapide pour les fonctions de la bibliothèque utiisées, mais ce gain de rapidité implique que la bibliothèque n'est pas utilisable sur toutes les cartes. Bien que ce ne soit pas à l'ordre du jour, d'autres bibliothèques du même type pourraient cependant voir le jour tôt ou tard afin de pouvoir exporter le code sur d'autres cartes.</div>
<div align=justify>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;L'implémentation de la bibliothèque est disponible dans les fichiers sources : SenseoUno.h et SenseoUno.cpp.

### Table des matières :
- [Introduction](#Introduction-)
- [1. Déclarer l'instance de classe SenseoUno](#1-déclarer-linstance-de-classe-senseouno-)
- [2. Piloter une ledRGB, une simple led, ou trois leds en lieu et place d'une led RGB](#2-piloter-une-ledrgb-une-simple-led-ou-trois-leds-en-lieu-et-place-dune-led-rgb-)
- [3. Les boutons-poussoirs (BP)](#3-les-boutons-poussoirs-bp-)
- [4. Les éléments de puissance | Pompe et résistance chauffante](#4-les-éléments-de-puissance--pompe-et-résistance-chauffante-)
- [5. Le / les capteurs de niveau d'eau](#5-le--les-capteurs-de-niveau-deau-)
- [6. Le capteur de température](#6-le-capteur-de-température-)
- [7. La communication série, par exemple pour un module Bluetooth](#7-la-communication-série-par-exemple-pour-un-module-bluetooth-)
- [8. Le ou les chronos](#8-le-ou-les-chronos-)
- [9. La mise en veille](#9-la-mise-en-veille-)
- [10. L'écriture en mémoire EEPROM](#10-lécriture-en-mémoire-eeprom-)
- [11. La liste des sketches d'exemple](#11-la-liste-des-sketches-dexemple-)

### Introduction :
<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La bibliothèque est basée sur un shield réalisé dans un cadre pédagogique. Ce shield offre des possibilités pour le pilotage d'un machine à café Senseo. Ces possibilités sont les suivantes :
* Pilotage d'une résistance chauffante 230V via relais.
* Pilotage d'une pompe 230V via relais.
* Utilisation de trois boutons-poussoirs NO.
* Vérifications de niveaux d'eau via capteurs à effet Hall : soit un seul niveau, soit deux niveaux (une tasse ou deux tasses).
* Une seule LED de type RGB, ou une seule LED à couleur unique. Il n'y a qu'une seule LED sur la plupart modèles Senseo. <ins>Note :</ins> il est possible de détourner les méthodes de la led RGB pour gérer trois leds à couleur unique. Voir les explications des différentes méthodes qui se situent plus loin dans ce document.
* Un capteur de température analogique de type NTC.
* Un module bluetooth utilisable via les broches UART du microcontrôleur (les broches Rx et Tx).
* Des fonctionnalités internes au microcontrôleur / à la carte Arduino Uno. Parmi ces fonctionnalités, citons seulement ici l'écriture en mémoire morte EEPROM. La mémoire EEPROM peut être utilisée pour stocker des informations comme le nombre de cycles de production. À partir de ce comptage du nombre de cycles, on pourra apporter une fonctionnalité de type rappel de détartrage et de nettoyage de la machine.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La bibliothèque part de cette configuration. Le code généré permet avant tout de piloter une machine Senseo avec ce shield, mais il est possible d'utiliser la bibliothèque pour programmer à parti d'autres configurations que la notre. Reprécisons que la bibliothèque ne fonctionne que sur les microcontrôleurs AtMega328 et ses variantes (AtMega328P, AtMega328P-PU, etc), ainsi que sur les AtMega168 et ses variantes. La bibliothèque est de type P.O.O (Programmation Orientée Objet). En P.O.O, les fonctions sont appelées méthodes, et l'objet à partir duquel elles sont utilisées se nomme instance. Typiquement pour les utilisateurs d'Arduino, une ligne de code comme *Serial.begin(9600)* est de type P.O.O. L'instance se nomme *Serial* et représente la communication série de l'Arduino Uno. Sur cette instance, on peut utiliser une fonction dédiée, une méthode qui s'appelle *begin()* et qui prend come paramètre le nombre de bauds, ici 9600. Cette bibliothèque fonctionne sur ce même principe. On va voir qu'on peut l'utiliser de plusieurs façons. Nous avons intégré quelques sketchs d'exemples pour illustrer comment s'en servir. Dans ce qui suit, nous présentons toutes les méthodes utilisables par l'utilisateur à partir d'une instance que nous avons nommée *Senseo* (et qui peut bien entendu être appelée différemment). Comme son nom l'indique, cette instance représente la machine à café que l'on souhaite programmer. Sur la Senseo, on va vouloir commander ses différents composants. Il faudra faire des actions comme : des activations / désactivations de composants (pompe, résistance chauffante, etc), des détections d'appui sur des boutons-poussoirs, des lectures et écritures analogiques pour lire une température ou activer une led RGB, etc. Voici, à partir d'une liste de composants ou fonctionnalités, ce que la bibliothèque permet de faire...

### 1. Déclarer l'instance de classe SenseoUno :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La bibliothèque propose deux façons de créer une instance de classe SenseoUno. Il y a deux sketches d'exemples "shield_settings.ino" et "custom_settings.ino" illustrant ces deux possibilités. Précisons que dans tous les cas de figure, l'instance doit être créée globalement en haut de sketch. Si l'instance est déclarée dans la fonction setup() ou dans la fonction loop() (ou dans une autre fonction), elle ne pourra pas être utilisée ailleurs. Hors l'utilisateur aura *a priori* besoin d'avoir accès à l'instance partout dans le sketch. Voici la première possibilité :
* SenseoUno *MaSenseo*;

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Cette première possibilité configure par défaut la machine à café sur base du shield. Notons que cette ligne de code est minimaliste puisque deux termes seulement sont utilisés. Le premier terme est le nom de la classe, qui correspond à un "type" ; le second terme est le nom de l'instance, qui correspond au nom de la "variable" de "type" SenseoUno. C'est un peu comme déclarer une variable : on déclare d'abord le type (int, float, char, etc) et puis le nom de la variable. Nous verrons à la fin de cette première partie la configuration faite par défaut dans le cas du shield. Mais l'utilisateur peut très bien vouloir faire sa propre configuration. C'est la raison pour laquelle il existe une seconde possibilité pour créer son instance de classe SenseoUno. La voici :
* SenseoUno *MachineSenseo*(EMPTY_INSTANCE);
* SenseoUno *Senseo*(SHIELD_INSTANCE);

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Cette seconde possibilité permet de créer une instance sous deux variantes. La première variante est une instance vide à configurer entièrement ; dans ce cas il faut renseigner la macro EMPTY_INSTANCE (ou la valeur 0 ou false) lors de la déclaration. La seconde variante est un synonyme de la première possibilité : elle configure par défaut l'instance sur base du shield. Dans ce cas, on peut soit utiliser la première variante, soit utiliser la seconde en renseignant la macro SHIELD_INSTANCE (ou la valeur 1 ou true).

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La configuration par défaut du shield se concentre uniquement sur les éléments essentiels. Ces éléments sont (1) la pompe déclarée sur la broche 6 ; (2) la résistance chauffante déclarée sur la broche 5 ; (3) le capteur de température déclaré sur la broche A0 ; (4) les trois boutons-poussoirs déclarés sur les broches 2, 3 et 4 ; (5) la led RGB déclarée sur les broches 9, 10 et 11 ; (6) un premier capteur de niveau d'eau sur la broche 7, et un second capteur de niveau d'eau sur la broche 8 ; (7) une configuration pour la communication série (par exemple via un module bluetooth) sur les broches 0 (RX) et 1 (TX) ; (8) la configuration de la mémoire EEPROM. 
<br /><ins>Note :</ins> la communication série de cette bibliothèque fonctionne comme la bibliothèque Serial. Par défaut, le nombre de bauds est de 9600.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La librairie ne configure pas tout par défaut, et quelques options sont à implémenter par l'utilisateur, shield ou non. Ces éléments sont les chronos et le mode de mise en veille. Les points 8 et 9 de ce document expliquent comment intégrer ces fonctionnalités dans le programme principal. Le point 10 reprend également une liste de tous les sketches d'exemple et de ce à quoi ils servent. L'utilisateur peut retourner vers cette liste pour savoir quels sketches d'exemple ouvrir pour découvrir l'utilisation des différentes fonctionnalités.

### 2. Piloter une ledRGB, une simple led, ou trois leds en lieu et place d'une led RGB :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Une machine Senseo contient en général un seul voyant lumineux, à partir duquel il renseigne un ensemble d'informations à l'utilisateur. Ces informations peuvent être diverses : indiquer à l'utilisateur que l'eau est prête et qu'il n'a plus qu'à choisir le nombre de tasses qu'il veut servir, indiquer au contraire que l'eau est toujours en train de chauffer, indiquer qu'il est temps de faire un détartrage, etc. Ce composant est donc essentiel, et la librairie propose plusieurs méthodes pour l'utiliser. Notons que la librairie permet de configurer et piloter soit une simple led, soit une led RGB (ou un ensemble de trois leds). La bibliothèque ne permet pas de configurer et commander deux leds, ou plus d'une led RGB, ou plus de trois leds.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Plusieurs cas de figure ont été envisagés. Soit l'utilisateur utilise une seule led, soit il utilise une led RGB. Notons que la led RGB consiste en trois leds ayant chacune une couleur différente. L'utilisateur peut donc utiliser une led RGB ou trois leds différentes. Pour la led RGB (ou une équivalence mise en place par l'utilisateur avec trois leds), deux possibilités pour la commande. La commande peut se faire en mode digital ou en mode analogique. Le mode digital permet deux états sur la led : soit elle est allumée soit elle est éteinte. Le mode analogique permet sur une led RGB de faire varier les intensités et couleurs, et donc de produire un panel de couleurs plus large. Par contre, le mode PWM implique que la led RGB occupe trois broches PWM sur l'Arduino Uno. Le choix ne peut pas être fait au hasard, puisque ces broches sont au nombre de six. Le mode PWM pour la led RGB implique qu'elle occupe trois broches parmi les suivantes : 3, 5, 6, 9, 10, 11. Les broches PWM sont signalées par un tilde (~) sur l'Arduino Uno.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Les premières méthodes sont à utiliser lors de l'initialisation, dans la fonction setup(). Elles permettent de sélectionner les broches sur lesquelles la simple led ou la led RGB est utilisée. Elles permettent aussi de la configurer soit en sortie digitale, soit en sortie analogique. Voici les trois méthodes utilisables pour la configuration du voyant lumineux choisi par l'utilisateur (rappelons que l'instance basée sur notre shield configure par défaut le voyant lumineux comme une led RGB en mode analogique, et qu'il n'y a pas besoin d'utiliser une de ces méthodes) :
* *Senseo*.setLed(led) | Pour configurer une seule led en sortie digitale sur l'instance Senseo.
* *Senseo*.setRGB(ledRouge, ledVerte, ledBleue) | Pour configurer 3 leds ou une led RGB en sorties digitales sur l'instance Senseo.
* *Senseo*.setAnalogRGB(ledRouge, ledVerte, ledBleue) | Pour configurer 3 leds ou une led RGB en sorties PWM sur l'instance Senseo.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Les méthodes qui suivent sont utilisables lors de l'exécution du programme principal, dans la fonction loop(). Elles permettent d'allumer et d'éteindre une simple led ; d'allumer et d'éteindre une led RGB initialisée en mode digital ; d'allumer et d'éteindre en mode analogique une led RGB (ou un ensemble de trois leds). Les méthodes renseignées ici ne fonctionneront pas toutes selon la configuration faite au préalable. Impossible par exemple d'activer en mode analogique une led RGB configurée en mode digital (ou raccordée à des broches non-PWM). Impossible aussi d'activer en mode digital une led RGB configurée en mode analogique. Idem pour la simple led, et la liste pourrait continuer ainsi.
* *Senseo*.activateLed() | Pour activer la led unique renseignée dans l'instance Senseo.
* *Senseo*.shutdownLed() | Pour désactiver la led unique renseignée dans l'instance Senseo.
* *Senseo*.activateRGB(rouge, vert, bleu) | Pour activer la led RGB en mode digital. Cette méthode demande une valeur booléenne pour chacune des leds : la valeur 1 signifie allumage de la led ; la valeur 0 signifie extinction de la led.
* *Senseo*.shutdownRGB() | Pour désactiver la led RGB en mode digital.
* *Senseo*.activateR() | Pour activer en digital la led rouge de la led RGB.
* *Senseo*.activateG() | Pour activer en digital la led verte de la led RGB.
* *Senseo*.activateB() | Pour activer en digital la led bleue de la led RGB.
* *Senseo*.shutdownR() | Pour désactiver en digital la led rouge de la led RGB.
* *Senseo*.shutdownG() | Pour désactiver en digital la led verte de la led RGB.
* *Senseo*.shutdownB() | Pour désactiver en digital la led bleue de la led RGB.
* *Senseo*.analogWriteRGB(valR, valG, valB) | Pour activer la led RGB en mode analogique PWM. Cette méthode demande une valeur entre 0 et 255 pour chacune des leds. Cette méthode permet de générer un éclairage de la led avec un large panel de couleurs.
* *Senseo*.analogShutdownRGB() | Pour désactiver la led RGB en mode analogique PWM.

### 3. Les boutons-poussoirs (BP) :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Une machine à café Senseo dispose de trois boutons-poussoirs. Un BP central et deux autres BP. Le BP central sert (*a minima*) à lancer le cycle de pompage et chauffage de l'eau ; les deux autres servent à sélectionner le nombre de tasses à servir (soit une tasse soit deux tasses). Ils sont eux aussi essentiels à la machine à café.
<br /><ins>Note :</ins> Il est recommandé de bien réfléchir à l'endroit où l'on place les boutons-poussoirs. La bibliothèque offre la possibilité d'intégrer un mode de mise en veille. Il sera possible d'activer et de faire sortir la machine de la mise en veille grâce (entre autres) à un appui sur un BP. Pour pouvoir faire cela, la librairie prévoit que l'utilisateur installe au minimum un des boutons-poussoirs sur l'une de ces broches de l'Arduino Uno : 0, 1, 2, 3, 4, 5, 6, 7.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il y a une méthode permettant de configurer les boutons-poussoirs, qui doit être utilisée durant l'initialisation dans la fonction setup(). Cette méthode permet de déclarer les broches sur lesquelles les BP vont être lus. Elle les déclare aussi automatiquement en entrée digitale. Notons que l'instance basée sur notre shield configure par défaut les 3 boutons-poussoirs sur les broches 2, 3 et 4 ; dans ce cas, cette méthode n'a donc pas besoin d'être utilisée.
* *Senseo*.set3Buttons(BP1, BP2, BP_central) | Pour configurer les 3 BP de la machine sur l'instance Senseo.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il y a enfin trois méthodes permettant de lire les états des boutons-poussoirs. Elles permettent de lire l'état d'un BP parmi les trois. Ces méthodes retournent une valeur booléenne en fonction du résultat de la lecture :
* *Senseo*.readButton1C() | Pour lire l'état du bouton-poussoir pour une tasse --> 1 si état haut, 0 si état bas.
* *Senseo*.readButton2C() | Pour lire l'état du bouton-poussoir pour deux tasses --> 1 si état haut, 0 si état bas.
* *Senseo*.readButtonMain() | Pour lire l'état du bouton-poussoir central --> 1 si état haut, 0 si état bas.

### 4. Les éléments de puissance | Pompe et résistance chauffante :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Une machine Senseo intègre nécessairement une pompe pour faire circuler l'eau, et une résistance chauffante pour chauffer l'eau à température. Ces deux éléments sont des éléments de puissance (ils fonctionnent avec une tension alternative, en général 230V). La librairie permet de les configurer et de les piloter comme de simples sorties digitales (soit activés, soit désactivés).

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La configuration se fait durant l'initialisation dans la fonction setup(), et peut se faire via trois méthodes. Soit une méthode pour configurer les deux en même temps, soit une méthode pour la pompe et une méthode pour la résistance chauffante. Pour chacune de ces méthodes, il faut renseigner la ou les broches sur lesquelles sont raccordés la pompe et la résistance chauffante. Elles font automatiquement la configuration de la ou des broches renseignées en sorties digitales. Sur l'instance basée sur le shield, la configuration est déjà faite par défaut et ces méthodes n'ont pas besoin d'être utilisées.
* *Senseo*.setPower(pompe, resChauffante) | Pour configurer en sorties digitales la pompe et la résistance chauffante sur l'instance Senseo.
* *Senseo*.setPump(pompe) | Pour configurer en sortie digitale la pompe sur l'instance Senseo.
* *Senseo*.setHeat(resChauffante) | Pour configurer en sortie digitale la résistance chauffante sur l'instance Senseo.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il y a quatre méthodes : une première pour l'activation de la pompe, une deuxième pour la désactivation de la pompe, une troisième pour l'activation de la résistance chauffante, une quatrième pour la désactivation de la résistance chauffante.
* *Senseo*.activatePump() | Pour activer la pompe.
* *Senseo*.shutdownPump() | Pour désactiver la pompe.
* *Senseo*.activateHeat() | Pour activer la résistance chauffante.
* *Senseo*.shutdownHeat() | Pour désactiver la résistance chauffante.

### 5. Le / les capteurs de niveau d'eau :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Une machine Senseo dispose forcément de capteurs de niveau d'eau. La plupart du temps, ces capteurs sont de type digital. Soit le niveau est assez élevé, soit il n'est pas assez élevé. La librairie procède de la même façon, et permet d'utiliser des capteurs de niveau d'eau de type tout ou rien (TOR). Selon les modèles, le nombre de capteurs peut varier entre un et deux. Deux capteurs permettent de détecter deux niveaux d'eau, un niveau pour une simple tasse et un niveau pour deux tasses. La librairie permet de faire les deux.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il faut configurer le ou les capteurs dans l'initialisation, donc dans la fonction setup(). Deux méthodes sont possibles : soit une méthode pour déclarer la broche d'un unique capteur de niveau, soit une méthode pour déclarer les deux broches utilisées pour les deux capteurs de niveau. Chacune de ces méthodes les configure comme des entrées digitales. Rappelons que l'instance basée sur le shield fait la configuration sur base du shield, et que dans ce cas il n'est pas nécessaire d'utiliser ces méthodes.
* *Senseo*.setLevels(niveau1, niveau2) | Pour configurer en entrées digitales les deux capteurs de niveau d'eau, pour une tasse et pour deux tasses, sur l'instance Senseo.
* *Senseo*.setLevel(niveau) | Pour configurer en entrée digitale un capteur de niveau d'eau sur l'instance Senseo.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Au sein du programme, on peut ensuite utiliser une ou deux méthodes (selon la configuration faite) pour lire les états des capteurs et donc détecter si les niveaux d'eau sont assez élevés ou non. Notons que si la configuration a été faite pour un capteur unique, la librairie prévoit une seule méthode *Senseo*.readLvl() ; il vaut mieux ne pas utiliser les autres méthodes. De même, si la configuration a été faite pour deux capteurs, il vaut mieux utiliser les méthodes associées et ne pas utiliser la méthode prévue pour un capteur unique.
* *Senseo*.readLvl() | Pour lire l'état du capteur de niveau d'eau. Cette fonction est utilisée lorsqu'il n'y a qu'un seul capteur de niveau d'eau sur la machine.
* *Senseo*.readLvl1() | Pour lire l'état du capteur de niveau d'eau pour une tasse. Cette fonction est utilisée lorsqu'il y a deux capteurs de niveau d'eau sur la machine.
* *Senseo*.readLvl2() | Pour lire l'état du capteur de niveau d'eau pour deux tasses. Cette fonction est utilisée lorsqu'il y a deux capteurs de niveau d'eau sur la machine.

<ins>Note :</ins> Les méthodes *Senseo*.readLvl() et *Senseo*.readLvl1() sont des synonymes. Ces deux méthodes s'appliquent à la même broche, qui est à la fois la seule broche déclarée avec la méthode *Senseo*.setLevel() et la première broche déclarée avec la méthode *Senseo*.setLevels(niveau1, niveau2). Dans le cas de la configuration basée sur le shield, la broche commune à ces deux méthodes est la broche 7.

### 6. Le capteur de température :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Lorsque la résistance chauffante est active, la température de l'eau augmente. Il faut pouvoir arrêter la résistance chauffante lorsque la température a atteint un certain seuil (en général autour de 95°C). Il faut pour cela un capteur de température, qui est en général un capteur analogique. La librairie permet de configurer et récupérer les valeurs d'un seul capteur analogique. Il existe plusieurs modèles de machine Senseo, et tous les modèles n'auront pas nécessairement les mêmes sortes de capteurs de température. Voilà pourquoi la bibliothèque ne saurait renseigner directement les valeurs en degrés. Elle retourne par contre une valeur analogique entre 0 et 1023. La méthode préconisée est de partir de cette valeur pour définir un seuil vers lequel la température n'est ni trop élevée ni trop faible.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il faut commencer par configurer le capteur analogique lors de l'initialisation dans la fonction setup(). Pour cela, on utilise une méthode par laquelle on renseigne la broche sur laquelle est raccordé le capteur. La méthode se charge ensuite de configurer la broche en entrée analogique. Notons que le capteur doit forcément être branché sur une des broches analogiques suivantes de l'Arduino Uno : A0, A1, A2, A3, A4, A5. Notons ensuite que la configuration est faite par défaut dans le cas de l'instance basée sur le shield, et qu'il n'est pas nécessaire dans ce cas d'utiliser cette méthode.
* *Senseo*.setTempSensor(captTemp) | Pour configurer en entrée analogique un capteur de température sur l'instance Senseo.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;On peut ensuite utiliser l'une des deux méthodes suivantes pour lire la valeur analogique du capteur de température. Notons que cette valeur peut être de type int ou de type float. L'utilisateur peut donc stocker la valeur dans une variable de type int ou de type float.
* *Senseo*.readTemp() | Pour lire la valeur analogique en 10-bits du capteur de température. Cette méthode retourne une valeur flottante / réelle entre 0 et 1023 correspondant à la température mesurée par le capteur.
* *Senseo*.readTemp(valeurTemp) | Pour lire la valeur analogique en 10-bits du capteur de température. Cette méthode demande une variable flottante / réelle en argument. Elle y stocke une valeur entre 0 et 1023 correspondant à la température mesurée par le capteur.

### 7. La communication série, par exemple pour un module Bluetooth :

### 8. Le ou les chronos :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Les chronos ont été implémentés dans la bibliothèque afin de se passer des fonctions daly() et millis() de la bibliothèque Arduino. Chacune présente ses inconvénients : la fonction delay() est certes simple à utiliser, mais elle bloque le programme durant ce temps et elle n'est donc pas très pratique. La fonction millis() n'est pas bloquante mais son utilisation pour une fonctionnalité similaire à la fonction delay() requiert au minimum deux variables de type long. Par ailleurs, elle n'est pas toujours très simple d'utilisation et peut porter à l'erreur. Les chronos implémentés ici ont pour but d'être à la fois simples d'utilisation et de ne pas bloquer le programme.

 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Concrètement, nous avons mis en place deux chronomètres. Chacun d'eux fonctionne de la même façon, et on peut utiliser les deux ou un seul (ou aucun). Néanmoins, pour pouvoir y faire appel, l'utilisateur doit utiliser l'une de ces deux macros de façon globale, c'est-à-dire dans aucune fonction (par exemple juste en-dessous du #include <SenseoUno.h>) :
 * CHRONO_ENABLE | Cette macro est nécessaire pour pouvoir utiliser les chronos de la bibliothèque SenseoUno. Il faut la déclarer de façon globale, sinon l'utilisateur aura des problèmes et messages d'erreur. La macro appelle un service d'interruption qui permet de créer et d'incrémenter les chronos.
 * CHRONOS_ENABLE | Cette macro fait exactement la même chose que la macro CHRONO_ENABLE, il n'y a que l'écriture qui change. Puisque l'utilisateur peut appeler un ou deux chronos, il pourrait ne plus savoir si le nom de la macro à appeler doit être singulier ou pluriel.

 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Ensuite, lors de la fonction setup(), l'utilisateur termine la configuration des chronos. La configuration consiste simplement à appeler une méthode pour le chrono unique, ou deux méthodes pour les deux chronos (une méthode par chrono). Dans cette méthode, l'utilisateur renseigne la valeur en millisecondes (qui va de 0 à 60000, maximum 60 secondes) du chrono. La configuration se fait avec les méthodes suivantes :
 * *Senseo*.startChrono(valeur) | Méthode utilisée dans le cas où l'on n'utilise qu'un seul chrono. Cette méthode demande une valeur entre 0 et 60000. La valeur correspond au nombre de millisecondes à partir duquel le chrono va s'activer.
 * *Senseo*.startChrono1(valeur1) | Méthode utilisée dans le cas où l'on souhaite configurer le premier chrono. Cette méthode demande une valeur entre 0 et 60000. La valeur correspond au nombre de millisecondes à partir duquel le premier chrono va s'activer.
 * *Senseo*.startChrono2(valeur2) | Méthode utilisée dans le cas où l'on souhaite configurer le deuxième chrono. Cette méthode demande une valeur entre 0 et 60000. La valeur correspond au nombre de millisecondes à partir duquel le deuxième chrono va s'activer.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Enfin, durant le programme principal, la fonction loop(), l'utilisateur va pouvoir utiliser des méthodes pour vérifier si le chrono est activé. Le chrono est activé lorsque le décompte à partir de la valeur est arrivé à 0 ou est inférieur. Il s'apparente à une alarme qui sonne lorsque l'heure à sonner, et qui ne s'arrête de sonner pendant un long moment. L'utilisateur va pouvoir vérifier si le chrono est activé grâce aux méthodes suivantes :
* *Senseo*.isCountdown() | Vérifie si la valeur déclarée par l'utilisateur dans la méthode *Senseo*.startChrono(valeur) a été atteinte ou dépassée. Si oui, elle retourne true ou 1 et elle réinitialise le chrono qui recommence à compter à partir de la valeur déclarée par l'utilisateur ; si non, elle retourne false ou 0.
* *Senseo*.isCountdown1() | Vérifie si la valeur déclarée par l'utilisateur dans la méthode *Senseo*.startChrono1(valeur1) a été atteinte ou dépassée. Si oui, elle retourne true ou 1 et elle réinitialise le chrono qui recommence à compter à partir de la valeur déclarée par l'utilisateur ; si non, elle retourne false ou 0.
* *Senseo*.isCountdown2() | Vérifie si la valeur déclarée par l'utilisateur dans la méthode *Senseo*.startChrono2(valeur2) a été atteinte ou dépassée. Si oui, elle retourne true ou 1 et elle réinitialise le chrono qui recommence à compter à partir de la valeur déclarée par l'utilisateur ; si non, elle retourne false ou 0.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il est important de comprendre que si l'utilisateur ne fait pas de vérification avec les méthodes qu'on vient de citer, les chronos continuent de s'incrémenter. C'est l'utilisateur qui les réinitialise en appelant la méthode. La méthode retourne une valeur booléenne : true ou 1 si le décompte a été atteint ou dépassé ; false ou 0 si le décompte n'a pas encore été atteint. Si la méthode retourne true ou 1, elle réinitialise automatiquement le chrono vérifié à la valeur déclarée par l'utilisateur. À cet instant, le chrono recommence à compter à partir de la valeur fixée par l'utilisateur.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Voyons enfin les dernières méthodes que l'utilisateur pourrait vouloir utiliser concernant les chronos. Ces méthodes permettent de réinitialiser le ou les chronos désirés sans devoir attendre qu'il ait atteint ou dépassé la valeur de décompte. Il y a également deux méthodes pour arrêter les chronos (c'est-à-dire non pas les mettre en pause ou sur stop, mais les éteindre). Pour les relancer, il faudra les réinitialiser avec une méthode de type *Senseo*.startChrono(valeur). Voici ces méthodes :
* *Senseo*.resetChrono() | Permet de réinitialiser le chrono, qui va recommencer à compter à partir de la valeur fixée par l'utilisateur avec la méthode *Senseo*.startChrono(valeur).
* *Senseo*.resetChronos() | Permet de réinitialiser les chronos, qui vont recommencer à compter à partir des valeurs fixées par l'utilisateur avec les méthodes *Senseo*.startChrono1(valeur1) et *Senseo*.startChrono1(valeur1).
* *Senseo*.resetChrono1() | Permet de réinitialiser le premier chrono, qui va recommencer à compter à partir de la valeur fixée par l'utilisateur avec la méthode *Senseo*.startChrono1(valeur1).
* *Senseo*.resetChrono2() | Permet de réinitialiser le deuxième chrono, qui va recommencer à compter à partir de la valeur fixée par l'utilisateur avec la méthode *Senseo*.startChrono2(valeur2).
* *Senseo*.stopChrono() | Permet d'éteindre le chrono configuré (ou les chronos, cette méthode fait la même chose que la méthode *Senseo*.stopChronos()). Le chrono est alors déréglé, et pour le refaire fonctionner il faudra le reconfigurer avec la méthode *Senseo*.startChrono(valeur).
* *Senseo*.stopChronos() | Permet d'éteindre le chrono configuré (ou les chronos, cette méthode fait la même chose que la méthode *Senseo*.stopChronos()). Le chrono est alors déréglé, et pour le refaire fonctionner il faudra le reconfigurer avec les méthodes *Senseo*.startChrono1(valeur1) et *Senseo*.startChrono2(valeur2).

### 9. La mise en veille :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Le mode veille est prévu pour faire des économies d'énergie. Cela permet de désactiver un maximum d'éléments du microcontrôleur. La réactivation se fera alors par un appui sur un bouton-poussoir de la machine. Cette fonctionnalité peut s'activer au bout d'un temps défini et à un (ou plusieurs) endroit spécifique du programme. Ce temps et ces endroits sont définis par le programmeur. La rentrée en mode veille a cependant un inconvénient : lorsqu'on en sort, beaucoup de réglages faits précédemment (convertisseur analogique-numérique, chronos, etc) doivent être réitérés. Pour contrer ce problème, une solution est de faire un reset interne du microcontrôleur. Par le reset interne, le microcontrôleur relance son programme depuis le départ et refait tute la configuration faite durant l'initialisation. Nous utilisons pour cela une méthode qui est présentée au paragraphe suivant.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il existe une seule méthode pour le mode veille. Cette méthode doit être associée à une macro déclarée de façon globale (tout en haut du programme et en-dehors de toute fonction). La méthode peut prendre un seul argument, deux arguments, trois arguments, ou aucun argument. Le premier argument sert à définir la façon dont on veut détecter une sortie du mode veille. Le deuxième argument sert à définir les broches à partir desquelles on souhaite pouvoir sortir du mode veille. Le troisième argument sert à indiquer si on souhaite ou non faire un reset automatique lors de l'appel de la fonction. On présente un peu plus loin un tableau décrivant les configurations possibles de cette méthode. En attendant, voici les configurations possibles :
* *Senseo*.sleep() | Démarre le mode veille configuré par défaut en mode 1 (voir tableau ci-dessous). Ce mode permet une sortie du mode veille par détection d'un front montant sur la broche D2 ou sur la broche D3, et ne fait aucun reset automatique.
* *Senseo*.sleep(mode_détection, broche_détection, reset_ou_non) | Démarre le mode veille avec trois possibilités de configuration : la méthode de détection de sortie du mode veille, la ou les broches via lesquelles on va pouvoir sortir du mode veille, et enfin la présence ou l'absence d'un reset automatique.
* *Senseo*.internal_reset() | Permet de faire un reset du microcontrôleur. Cette méthode a été pensée en lien avec la sortie du mode veille, mais peut très bien être utilisée ailleurs dans le programme et indépendamment du mode veille.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Quelques mots avant de voir le tableau récapitulatif des macros.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;L'utilisation de la méthode ne suffit pas. Il faut obligatoirement ajouter une macro de façon globale en début de programme. La macro est nécessaire au fonctionnement du mode veille. Il y a plusieurs macros globales possibles, pour différents modes d'utilisation. Au sein de la méthode il y a trois arguments permettant de faire la configuration. Pour chacun de ces arguments on liste également les macros à inscrire tel quel dans la méthode *Senseo*.sleep(), le but étant de montrer les possibilités de configuration et de simplifier l'usage et la lisibilité du code.
| Mode d'utilisation : | Macro à utiliser dans le programme : | Où utiliser la macro :                       | Fonctionnalité :                                          |
| :-----------------:  | :----------------------------------: | :-----------------------------------------:  | :-------------------------------------------------------: |
| Mode 1               | SENSEO_SLEEP                         | Tout en haut du programme, macro globale     | Active une sortie du mode veille par les broches D2 et D3 |
| Mode 1               | SENSEO_SLEEP_1                       | Tout en haut du programme, macro globale     | Active une sortie du mode veille par les broches D2 et D3 |
| Mode 1               | WAKE_UP_1                            | Méthode *Senseo*.sleep(), deuxième argument  | Active une sortie du mode veille par les broches D2 et D3 |
| Mode 2               | SENSEO_SLEEP_2                       | Tout en haut du programme, macro globale     | Active une sortie du mode veille par la broche D2         |
| Mode 2               | WAKE_UP_2                            | Méthode *Senseo*.sleep(), deuxième argument  | Active une sortie du mode veille par la broche D2         |
| Mode 3               | SENSEO_SLEEP_3                       | Tout en haut du programme, macro globale     | Active une sortie du mode veille par la broche D3         |
| Mode 3               | WAKE_UP_3                            | Méthode *Senseo*.sleep(), deuxième argument  | Active une sortie du mode veille par la broche D3         |
| /                    | SENSEO_RISING                        | Méthode *Senseo*.sleep(), premier argument   | Permet de sortir du mode veille par un front montant      |
| /                    | SENSEO_FALLING                       | Méthode *Senseo*.sleep(), premier argument   | Permet de sortir du mode veille par un front descendant   |
| /                    | SENSEO_LOW                           | Méthode *Senseo*.sleep(), premier argument   | Permet de sortir du mode veille par un état bas           |
| /                    | SENSEO_CHANGE                        | Méthode *Senseo*.sleep(), premier argument   | Permet de sortir du mode veille par un changement d'état  |
| /                    | NO_RESET                             | Méthode *Senseo*.sleep(), troisième argument | N'active pas le reset à la sortie du mode veille          |
| /                    | AUTO_RESET                           | Méthode *Senseo*.sleep(), troisième argument | Active le reset à la sortie du mode veille                |

### 10. L'écriture en mémoire EEPROM :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;L'écriture en mémoire EEPROM permet de conserver des informations même lorsque le microcontrôleur n'est plus alimenté. Elle peut être utile notamment pour conserver en mémoire le nombre de cycles exécutés depuis le dernier détartrage. On peut alors fixer une valeur à partir de laquelle on informera l'utilisateur qu'il est temps de lancer un cycle de détartrage. Pour l'écriture en EEPROM, on suppose qu'il n'est pas nécessaire d'avoir des fonctionnalités très avancées. Aussi proposons-nous des méthodes basiques pour la lecture, l'écriture et l'adressage. Elles sont au nombre de quatre :
* *Senseo*.set_memory_address(adresse) | Permet de fixer l'adresse à laquelle on va se rendre pour lire et/ou écrire un octet (donc une valeur comprise entre 0 et 255). Chaque instance de type SenseoUno a une adresse par défaut qui vaut 0. Si cette adresse convient à l'utilisateur et qu'il n'a besoin que d'un seul octet de donnée, il n'aura jamais besoin d'utiliser cette méthode.
* *Senseo*.get_memory_address() | Permet de récupérer l'adresse actuelle utilisée pour la lecture / écriture en EEPROM.
* *Senseo*.save_cups(valeur) | Permet de sauvegarder une nouvelle valeur dans la mémoire EEPROM à l'adresse fixée par l'utilisateur (ou à l'adresse par défaut).
* *Senseo*.get_cups() | Permet de récupérer la valeur (dans un type entier) stockée dans la mémoire EEPROM à l'adresse fixée par l'utilisateur (ou à l'adresse par défaut).

### 11. La liste des sketches d'exemple :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Dans le dossier examples de cette librairie, nous avons écrit quelques sketchs pour la configuration et l'utilisation de la bibliothèque. Ces sketchs sont accessibles directement depuis l'IDE Arduino, dans l'onglet du menu déroulant Fichier->Exemples->SenseoUno. Voici une liste des sketchs présents et ce qu'ils permettent de faire :
* *custom_settings.ino* | Illustre comment créer et configurer une instance vide de la classe SenseoUno.
* *EEPROM.ino* | Montre comment écrire et lire dans la mémoire EEPROM avec une instance de la classe SenseoUno.
* *ledRGB_PWM.ino* | Montre comment utiliser une led RGB en mode PWM.
* *read_temperature.ino* | Montre comment récupérer une valeur analogique en 10-bits sur un capteur analogique (comme par exemple un capteur de température).
* *shield_settings.ino* | Illustre comment créer une instance de la classe SenseoUno basée sur le shield.
* *single_chrono.ino* | Cet exemple montre comment déclarer, configurer et utiliser un chrono unique.
* *two_chronos.ino* | Cet exemple montre comment déclarer, configurer et utiliser les deux chronos de la librairie.
* *sleep_no_autoreset.ino* | Cet exemple montre comment activer le mode veille sans faire de reset automatique avec une instance SenseoUno.
* *Senseo_autoreset.ino* | Cet exemple montre comment activer le mode veille avec un reset automatique via une instance SenseoUno.


</div>
