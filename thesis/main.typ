#import "title_page.typ": *

#set document(author: "Patrik Novák", title: "XY Plotter")
#set text(lang: "cs")
#set heading(numbering: "1.1")

#show heading: set text(
  fill: rgb("#0065BD"),
  font: "New Computer Modern Sans"
)  // 0 101 189



#set page(
    numbering: "1",
    number-align: center,
  )
  
#title_page(
  title: "XY Plotter",
  faculty: "Fakulta elektrotechnická",
  author: "Patrik Novák",
  supervisor: "Doc. Ing. Stanislav Vítek, Ph.D."
)

= Poděkování

= Abstrakt

= Abstract



#outline()

= Úvod

= Požadavky

== Funkční požadavky

+ Plotter bude možno ovládat pomocí G-Code.
+ Plotter bude možno používat s již dostupnýmy generátory G-Code.
+ Konstrukce Plotteru bude využívat 3D tištěných dílů.
+ Plotter bude mít kinematiku typu CoreXY.
+ Jako MCU bude použito RPi Pico nebo jiná MCU založená na čipu RP2040.
+ Firmware bude psán v C/C++ s využitím Pico C/C++ SDK.
+ Kreslící plocha plotteru bude alespoň 30x20 cm.
+ Stroj bude kreslit s přesností alespoň jednoho milimetru.

== Nefunkční požadavky

+ Plotter bude sestaven ze součástek, které jsou běžně dostupné.
+ Plotter bude designován tak, aby jeho konstrukce byla jednoduchá na složení i údržbu.

= Seznam komponent

#figure(
  table(
    columns: (6cm, 2cm),
    inset: 5pt,
    align: (left, center),
    [*Položka*], [*Počet*],
    "RPi Pico", "1",
    "Krokový motor Nema 17, 0.4 Nm", "2",
    "Servo MG90", "1",
  ),
  caption: "Seznam komponent",
)

Běžné komponenty jako kondenzátory, desky plošných spojů zde uvedeny nejsou.

= Technologie

== PWM
kapitolka o tom, co je to vlastne PWM a jak jsem pocital hodnoty pro pouziti se servem MG90 nesmi chybet

== G-Code
zde pojednam o tom co to vlastne je G-Code. Pridam trochu historie a popisu jak ho vyuzivam ve sve praci.

== 3D tisk
Letmy popis technologie 3D tisku jako takove a uvedl bych jakym zpusobem ji pouzivam ve sve praci. Je to docela dulezita soucast konstrukce a jeden z mych pozadavku

== Pico C/C++ SDK
== Picoprobe

= Konstrukce

Tady bude par slov ke konstrukci. Jake komponenty a materialy jsem pouzil a proc. Potom zde rozeberu proc jsem zvolil CoreXY kinematiku a porovnam s klasickou.


= Firmware

zde bude popsana implementace klicovych features

+ parsovac G-Codes
+ planovac pohybu
+ a dalsi...

= Závěr
