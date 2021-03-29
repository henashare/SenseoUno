# <div align="center"> <ins>Bibliothèque SenseoUno :</ins> </div>

## <div align=justify>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Bibliothèque pour le pilotage d'une machine à café Senseo à partir d'une carte Arduino Uno. <ins>Attention :</ins> la bibliothèque fonctionne *uniquement* pour les microcontrôleurs basés sur l'Arduino Uno.</div>

#### <div align=justify>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<ins>Note :</ins> La bibliothèque est implémentée pour être utilisée à partir d'une carte Arduino Uno. Elle est faite pour être plus rapide que la bibliothèque Arduino lors de l'exécution du programme, d'où sa non-portabilité. En revanche, le référencement aux différents ports et registres est masqué par la bibliothèque. L'utilisateur "classique" ne sera donc pas dépaysé, et pourra coder son programme comme n'importe quel programme Arduino. Le code sera plus rapide pour les fonctions de la bibliothèque utiisées, mais ce gain de rapidité implique que la bibliothèque n'est pas utilisable sur toutes les cartes. Bien que ce ne soit pas à l'ordre du jour, d'autres bibliothèques du même type pourraient cependant voir le jour tôt ou tard afin de pouvoir exporter le code sur d'autres cartes.</div>
<div align=justify>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;L'implémentation de la bibliothèque est disponible dans les fichiers sources : SenseoUno.h et SenseoUno.cpp.

<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La bibliothèque est basée sur un shield réalisé dans un cadre pédagogique. Ce shield offre les possibilités suivantes :
* Pilotage d'une résistance chauffante 230V via relais.
* Pilotage d'une pompe 230V via relais.
* Utilisation de trois boutons-poussoirs NO.
* Vérifications de niveaux d'eau via capteurs à effet Hall : soit un seul niveau, soit deux niveaux (une tasse ou deux tasses).
* Une seule LED de type RGB, ou une seule LED à couleur unique. Il n'y a qu'une seule LED sur la plupart modèles Senseo. <ins>Note :</ins> il est possible de détourner les méthodes de la led RGB pour gérer trois leds à couleur unique. Voir les explications des différentes méthodes qui se situent plus loin dans ce document.
* Un capteur de température analogique de type NTC.
* Un module bluetooth utilisable via les broches UART du microcontrôleur (les broches Rx et Tx).

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La bibliothèque part de cette configuration. Le code généré permet avant tout de piloter une machine Senseo avec ce shield, mais il est possible d'utiliser la bibliothèque pour programmer à parti d'autres configurations que la notre. Reprécisons que la bibliothèque ne fonctionne que sur les microcontrôleurs AtMega328 et ses variantes (AtMega328P, AtMega328P-PU, etc), ainsi que sur les AtMega168 et ses variantes. La bibliothèque est de type P.O.O (Programmation Orientée Objet). En P.O.O, les fonctions sont appelées méthodes, et l'objet à partir duquel elles sont utilisées se nomme instance. Typiquement pour les utilisateurs d'Arduino, une ligne de code comme *Serial.begin(9600)* est de type P.O.O. L'instance se nomme *Serial* et représente la communication série de l'Arduino Uno. Sur cette instance, on peut utiliser une fonction dédiée, une méthode qui s'appelle *begin()* et qui prend come paramètre le nombre de bauds, ici 9600. Cette bibliothèque fonctionne sur ce même principe. On va voir qu'on peut l'utiliser de plusieurs façons. Nous avons intégré quelques sketchs d'exemples pour illustrer comment s'en servir. Dans ce qui suit, nous présentons toutes les méthodes utilisables par l'utilisateur à partir d'une instance que nous avons nommée *Senseo* (et qui peut bien entendu être appelée différemment). Comme son nom l'indique, cette instance représente la machine à café que l'on souhaite programmer. Sur la Senseo, on va vouloir commander ses différents composants. Il faudra faire des actions comme : des activations / désactivations de composants (pompe, résistance chauffante, etc), des détections d'appui sur des boutons-poussoirs, des lectures et écritures analogiques pour lire une température ou activer une led RGB, etc. Voici, à partir d'une liste de composants ou fonctionnalités, ce que la bibliothèque permet de faire...

### 1. Déclarer l'instance de classe SenseoUno :

### 2. Piloter une ledRGB, une simple led, ou trois leds en lieu et place d'une led RGB :
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Une machine Senseo contient en général un seul voyant lumineux, à partir duquel il renseigne un ensemble d'informations à l'utilisateur. Ces informations peuvent être diverses : indiquer à l'utilisateur que l'eau est prête et qu'il n'a plus qu'à choisir le nombre de tasses qu'il veut servir, indiquer au contraire que l'eau est toujours en train de chauffer, indiquer qu'il est temps de faire un détartrage, etc. Ce composant est donc essentiel, et la librairie propose plusieurs méthodes pour l'utiliser. Notons que la librairie permet de configurer et piloter soit une simple led, soit une led RGB (ou un ensemble de trois leds). La bibliothèque ne permet pas de configurer et commander deux leds, ou plus d'une led RGB, ou plus de trois leds.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Plusieurs cas de figure ont été envisagés. Soit l'utilisateur utilise une seule led, soit il utilise une led RGB. Notons que la led RGB consiste en trois leds ayant chacune une couleur différente. L'utilisateur peut donc utiliser une led RGB ou trois leds différentes. Pour la led RGB (ou une équivalence mise en place par l'utilisateur avec trois leds), deux possibilités pour la commande. La commande peut se faire en mode digital ou en mode analogique. Le mode digital permet deux états sur la led : soit elle est allumée soit elle est éteinte. Le mode analogique permet sur une led RGB de faire varier les intensités et couleurs, et donc de produire un panel de couleurs plus large. Par contre, le mode PWM implique que la led RGB occupe trois broches PWM sur l'Arduino Uno. Le choix ne peut pas être fait au hasard, puisque ces broches sont au nombre de six. Le mode PWM pour la led RGB implique qu'elle occupe trois broches parmi les suivantes : 3, 5, 6, 9, 10, 11. Les broches PWM sont signalées par un tilde (~) sur l'Arduino Uno.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Les premières méthodes sont à utiliser lors de l'initialisation, dans la fonction setup(). Elles permettent de sélectionner les broches sur lesquelles la simple led ou la led RGB est utilisée. Elles permettent aussi de la configurer soit en sortie digitale, soit en sortie analogique. Voici les trois méthodes utilisables pour la configuration du voyant lumineux choisi par l'utilisateur (rappelons que l'instance basée sur notre shield configure par défaut le voyant lumineux comme une led RGB en mode analogique) :
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

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il y a une méthode permettant de configurer les boutons-poussoirs. Cette méthode permet de déclarer les broches sur lesquelles les BP vont être lus. Elle les déclare aussi automatiquement en entrée digitale :
* *Senseo*.set3Buttons(BP1, BP2, BP_central) | Pour configurer les 3 BP de la machine sur l'instance Senseo.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Il y a enfin trois méthodes permettant de lire les états des boutons-poussoirs. Elles permettent de lire l'état d'un BP parmi les trois. Ces méthodes retournent une valeur booléenne en fonction du résultat de la lecture :
* *Senseo*.readButton1C() | Pour lire l'état du bouton-poussoir pour une tasse --> 1 si état haut, 0 si état bas.
* *Senseo*.readButton2C() | Pour lire l'état du bouton-poussoir pour deux tasses --> 1 si état haut, 0 si état bas.
* *Senseo*.readButtonMain() | Pour lire l'état du bouton-poussoir central --> 1 si état haut, 0 si état bas.

### 4. Les éléments de puissance | Pompe et résistance chauffante :
* *Senseo*.setPower(pompe, resChauffante) | Pour configurer en sorties digitales la pompe et la résistance chauffante sur l'instance Senseo.
* *Senseo*.setPump(pompe) | Pour configurer en sortie digitale la pompe sur l'instance Senseo.
* *Senseo*.setHeat(resChauffante) | Pour configurer en sortie digitale la résistance chauffante sur l'instance Senseo.
* *Senseo*.setLevels(niveau1, niveau2) | Pour configurer en entrées digitales les deux capteurs de niveau d'eau, pour une tasse et pour deux tasses, sur l'instance Senseo.
* *Senseo*.setLevel(niveau) | Pour configurer en entrée digitale un capteur de niveau d'eau sur l'instance Senseo.
* *Senseo*.setTempSensor(captTemp) | Pour configurer en entrée analogique un capteur de température sur l'instance Senseo.
* *Senseo*.readLvl() | Pour lire l'état du capteur de niveau d'eau. Cette fonction est utilisée lorsqu'il n'y a qu'un seul capteur de niveau d'eau sur la machine.
* *Senseo*.readLvl1() | Pour lire l'état du capteur de niveau d'eau pour une tasse. Cette fonction est utilisée lorsqu'il y a deux capteurs de niveau d'eau sur la machine.
* *Senseo*.readLvl2() | Pour lire l'état du capteur de niveau d'eau pour deux tasses. Cette fonction est utilisée lorsqu'il y a deux capteurs de niveau d'eau sur la machine.
* *Senseo*.readTemp() | Pour lire la valeur analogique en 10-bits du capteur de température. Cette méthode retourne une valeur flottante / réelle entre 0 et 1023 correspondant à la température mesurée par le capteur.
* *Senseo*.readTemp(valeurTemp) | Pour lire la valeur analogique en 10-bits du capteur de température. Cette méthode demande une variable flottante / réelle en argument. Elle y stocke une valeur entre 0 et 1023 correspondant à la température mesurée par le capteur.
* *Senseo*.activatePump() | Pour activer la pompe.
* *Senseo*.shutdownPump() | Pour désactiver la pompe.
* *Senseo*.activateHeat() | Pour activer la résistance chauffante.
* *Senseo*.shutdownHeat() | Pour désactiver la résistance chauffante.


&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Dans le dossier examples de cette librairie, nous avons écrit quelques sketchs pour la configuration et l'utilisation de la bibliothèque. Ces sketchs sont accessibles directement depuis l'IDE Arduino, dans l'onglet du menu déroulant Fichier->Exemples->SenseoUno. Voici une liste des sketchs présents et ce qu'ils permettent de faire :
* shield_settings.ino | Sketch de configuration minimale sur base des raccordements du shield à partir duquel la bibliothèque a été implémentée. Pour un raccordement différent, voir le sketch "custom_settings.ino".
* custom_settings.ino | Sketch de configuration personnalisé. Exemple recommandé pour voir comment faire une configuration complète. Si la configuration est la même que sur le shield à partir duquel la bibliothèque a été implémentée, une simple déclaration de l'instance de classe SenseoUno est suffisante. Dans ce cas, voir l'exemple "shield_settings.ino".


</div>
