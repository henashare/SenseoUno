# <div align="center"> <ins>Bibliothèque SenseoUno :</ins> </div>

## <div align=justify>Bibliothèque pour le pilotage d'une machine à café Senseo à partir d'une carte Arduino Uno. <ins>Attention :</ins> la bibliothèque fonctionne *uniquement* pour les microcontrôleurs basés sur l'Arduino Uno.</div>

### <div align=justify><ins>Note :</ins> La bibliothèque est implémentée pour être utilisée à partir d'une carte Arduino Uno. Elle est faite pour être plus rapide que la bibliothèque Arduino lors de l'exécution du programme, d'où sa non-portabilité. En revanche, le référencement aux différents ports et registres est masqué par la bibliothèque. L'utilisateur "classique" ne sera donc pas dépaysé, et pourra coder son programme comme n'importe quel programme Arduino. Le code sera plus rapide pour les fonctions de la bibliothèque utiisées, mais ce gain de rapidité implique que la bibliothèque n'est pas utilisable sur toutes les cartes. Bien que ce ne soit pas à l'ordre du jour, d'autres bibliothèques du même type pourraient cependant voir le jour tôt ou tard afin de pouvoir exporter le code sur d'autres cartes.</div>
<div align=justify>
L'implémentation de la bibliothèque est disponible dans les fichiers sources : SenseoUno.h et SenseoUno.cpp.

La bibliothèque est basée sur un shield réalisé dans un cadre pédagogique. Ce shield offre les possibilités suivantes :
* Pilotage d'une résistance chauffante 230V via relais.
* Pilotage d'une pompe 230V via relais.
* Utilisation de trois boutons-poussoirs NO.
* Vérifications de niveaux d'eau via capteurs à effet Hall : soit un seul niveau, soit deux niveaux (une tasse ou deux tasses).
* Une seule LED de type RGB, ou une seule LED à couleur unique. Il n'y a qu'une seule LED sur la plupart modèles Senseo. <ins>Note :</ins> il est possible de détourner les méthodes de la led RGB pour gérer trois leds à couleur unique. Voir les explications des différentes méthodes qui se situent plus loin dans ce document.
* Un capteur de température analogique de type NTC.
* Un module bluetooth utilisable via les broches UART du microcontrôleur (les broches Rx et Tx).

La bibliothèque part de cette configuration. Le code généré permet avant tout de piloter une machine Senseo avec ce shield, mais il est possible d'utiliser la bibliothèque pour d'autres configurations. Reprécisons que la bibliothèque ne fonctionne que sur les microcontrôleurs AtMega328 et ses variantes (AtMega328P, AtMega328P-PU, etc), ainsi que sur les AtMega168 et ses variantes. La bibliothèque est de type P.O.O (Programmation Orientée Objet). On peut l'implémenter de plusieurs façons. Voir les sketchss dans le dossier "examples" de ce répertoire. Les deux sketchs "shield_settings.ino" et "default_settings.ino" montrent deux façons de configurer la machine. Par configurer, on veut dire définir les entrées et sorties. Deux possibilités, soit le shield est bien identique à celui utilisé pour l'implémentation de la bibliothèque, soit on utilise une autre configuration matérielle. Dans le premier cas, la configuration est minimale (voir le sketch "shield_settings.ino") ; dans le second cas, voir le sketch "custom_settings.ino". Ce sketch présente les méthodes utilisables dans la fonction setup() pour la configuration. Ici, nous présentons toutes les méthodes utilisables par l'utilisateur à partir d'une instance de classe déclarée en début de sketch. Appelons cette instance <style>Senseo{color:DarkOrange;}</style>. Sur cette instance, les méthodes utilisables sont les suivantes :
* Senseo.setRGB(ledRouge, ledVerte, ledBleue) | Pour configurer 3 leds ou une led RGB en sorties digitales sur l'instance Senseo.
* Senseo.setAnalogicRGB(ledRouge, ledVerte, ledBleue) | Pour configurer 3 leds ou une led RGB en sorties PWM sur l'instance Senseo.
* Senseo.setLed(led) | Pour configurer une seule led en sortie digitale sur l'instance Senseo.
* Senseo.set3Buttons(BP1, BP2, BP_central) | Pour configurer les 3 BP de la machine sur l'instance Senseo.
* Senseo.setPower(pompe, resChauffante) | Pour configurer en sorties digitales la pompe et la résistance chauffante sur l'instance Senseo.
* Senseo.setPump(pompe) | Pour configurer en sortie digitale la pompe sur l'instance Senseo.
* Senseo.setHeat(resChauffante) | Pour configurer en sortie digitale la résistance chauffante sur l'instance Senseo.
* Senseo.setLevels(niveau1, niveau2) | Pour configurer en entrées digitales les deux capteurs de niveau d'eau, pour une tasse et pour deux tasses, sur l'instance Senseo.
* Senseo.setLevel(niveau) | Pour configurer en entrée digitale un capteur de niveau d'eau sur l'instance Senseo.
* Senseo.setTempSensor(captTemp) | Pour configurer en entrée analogique un capteur de température sur l'instance Senseo.
* Senseo.readButton1C() | Pour lire l'état du bouton-poussoir pour une tasse.
* Senseo.readButton2C() | Pour lire l'état du bouton-poussoir pour deux tasses.
* Senseo.readButtonMain() | Pour lire l'état du bouton-poussoir central.
* Senseo.readLvl() | Pour lire l'état du capteur de niveau d'eau. Cette fonction est utilisée lorsqu'il n'y a qu'un seul capteur de niveau d'eau sur la machine.
* Senseo.readLvl1() | Pour lire l'état du capteur de niveau d'eau pour une tasse. Cette fonction est utilisée lorsqu'il y a deux capteurs de niveau d'eau sur la machine.
* Senseo.readLvl2() | Pour lire l'état du capteur de niveau d'eau pour deux tasses. Cette fonction est utilisée lorsqu'il y a deux capteurs de niveau d'eau sur la machine.
* Senseo.readTemp() | Pour lire la valeur analogique en 10-bit du capteur de température. Cette méthode retourne une valeur flottante / réelle entre 0 et 1023 correspondant à la température mesurée par le capteur.
* Senseo.readTemp(valeurTemp) | Pour lire la valeur analogique en 10-bit du capteur de température. Cette méthode demande une variable flottante / réelle en argument. Elle y stocke une valeur entre 0 et 1023 correspondant à la température mesurée par le capteur.
* Senseo.activatePump() | Pour activer la pompe.
* Senseo.shutdownPump() | Pour désactiver la pompe.
* Senseo.activateHeat() | Pour activer la résistance chauffante.
* Senseo.shutdownHeat() | Pour désactiver la résistance chauffante.
* Senseo.activateLed() | Pour activer la led unique renseignée dans l'instance Senseo.
* Senseo.shutdownLed() | Pour désactiver la led unique renseignée dans l'instance Senseo.
* Senseo.activateRGB(rouge, vert, bleu) | Pour activer la led RGB. Cette méthode demande une valeur booléenne pour chacune des leds : la valeur 1 signifie allumage de la led ; la valeur 0 signifie extinction de la led.
* Senceo.shutdownRGB() | Pour désactiver la led RGB.
* Senseo.activateR() | Pour activer en digital la led rouge de la led RGB.
* Senseo.activateG() | Pour activer en digital la led verte de la led RGB.
* Senseo.activateB() | Pour activer en digital la led bleue de la led RGB.
* Senseo.shutdownR() | Pour désactiver en digital la led rouge de la led RGB.
* Senseo.shutdownG() | Pour désactiver en digital la led verte de la led RGB.
* Senseo.shutdownB() | Pour désactiver en digital la led bleue de la led RGB.
* Senseo.analogWriteRGB(valR, valG, valB) | Pour activer la led RGB en mode analogique PWM. Cette méthode demande une valeur entre 0 et 255 pour chacune des leds. Cette méthode permet de générer un éclairage de la led avec un large panel de couleurs.
* Senseo.analogEndRGB() | Pour désactiver la led RGB en mode analogique PWM.

Dans le dossier examples de cette librairie, voici une liste des sketchs présents et ce qu'ils permettent de faire :
* shield_settings.ino | 
* custom_settings.ino | 


</div>
