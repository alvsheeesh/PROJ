# Sprint 04 — Estabilización

- **Fechas:** 2026-11-12 → 2026-11-25 (alargado el 19, al aplazarse la entrega al 26)
- **Objetivo:** el prototipo funciona por Quest Link desde una build de Windows, fuera del editor, sin funcionalidades nuevas, con el rendimiento medido en la build, la documentación al día y la release `prototipo`. Desde el 12 de noviembre incluye también el bucle de juego ([ADR 0018](../decisiones/0018-bucle-de-juego.md)).
- **Release:** prototipo

## Planificación

Desde el 12 de noviembre el alcance está congelado ([planificación](../planificacion.md)): solo correcciones, rendimiento, build y documentación. Tareas en Jira: TAKT-36 (primera build de Windows).

| Semana | Sesiones | Objetivo |
|--------|----------|----------|
| 12–18 nov | jue 12 (en clase, sin gafas), mié 18 (con gafas) | Primera build de Windows (TAKT-36). Prueba de la build por Link y medida de rendimiento. Correcciones bloqueantes, documentación de entrega, cierre del sprint y release `prototipo`. |

Riesgos:
- Nunca se ha empaquetado el proyecto: la primera build puede fallar al cocinar o al arrancar fuera del editor. Por eso se hace el primer día del sprint.
- Solo quedan dos sesiones antes de la entrega (19 nov, 15:00) y las dos semanas anteriores se quedaron por debajo del mínimo de horas.
- La build solo se puede probar en VR en casa, el miércoles 18.

## Bitácora

### Correcciones del sprint 03
- **Horas del 11 de noviembre:** la sesión fue de 11:30 a 12:30 (1,0 h) y no hasta las 12:45 como pone la bitácora del sprint 03; los commits `69f4b4e` y `030ebd6` suman 1,2 h. Con las horas reales, la semana 4 se queda en 2,3 h y el sprint 03 en 5,9 h.
- **Tiempos de las averías:** el commit `69f4b4e` y la bitácora del 11 dicen que *Min Delay* y *Max Delay* se pusieron a 20 y 45 s, pero se habían quedado en 5 y 10 s. Se corrigen el 12 de noviembre, en TAKT-36.

### 2026-11-12 (jueves)
- Sesión en clase, sin gafas, desde las 16:30.
- El mapa por defecto del juego y del editor era `L_XRTemplate`, el de la plantilla: la build habría arrancado en ese nivel. Pasa a ser `L_Dev_Cinta` (*Configuración del proyecto → Mapas y modos*).
- *Min Delay* y *Max Delay* de «Averías aleatorias» a 20 y 45 s (corrección de arriba).
- TAKT-36: primera build de Windows (Win64, Development) con `RunUAT BuildCookRun`, archivada en `E:\TAKT_Builds`, fuera del repositorio. Comando en [`entorno.md`](../entorno.md).
- Resultado: **`BUILD SUCCESSFUL` en 36 minutos**, con 674 paquetes cocinados y sin errores. Casi todo el tiempo se va en compilar los shaders por primera vez (los del motor y los de los materiales); las siguientes builds deberían ser más rápidas. Solo hay dos avisos, de extensiones de OpenXR que no se usan (seguimiento de la mirada y mandos de PICO).
- El ejecutable (`E:\TAKT_Builds\Windows\TAKT.exe`) arranca en `L_Dev_Cinta` con la línea en marcha (luz verde). Sin gafas la cámara se queda a ras de suelo y no se puede interactuar, que es lo esperado: la prueba de verdad es por Link el miércoles 18.
- Problemas encontrados:
  - La build crea `TAKT/Build/Windows/`, que salía como fichero nuevo en Git: las reglas de `Build/` del `.gitignore` llevaban una barra en medio y solo valían en la raíz del repositorio. Pasan a ser `**/Build/...`.
  - La escena se ve muy oscura, salvo lo que ilumina la luz de estado. No es cosa de la build: ya se veía así en el *Play* del editor el 5 de noviembre. Se revisa con gafas el 18.
- Queda para el miércoles 18, con gafas: probar la build por Link, medir con `stat unit` si llega a 72 fps ([ADR 0015](../decisiones/0015-rendimiento-por-link.md)) y mirar la iluminación de la escena.
- Después de subir TAKT-36: demostración al tutor en clase (la avería en el editor y la build). Su valoración: la base está bien, pero falta un **bucle de juego**, algo que dé ganas de seguir jugando. Se diseña un bucle mínimo para responder a lo que pide (bandeja infinita, parejas que puntúan al llegar juntas a una caja al final de la cinta, marcador y partida contrarreloj) y se crean TAKT-37 a TAKT-41. Sesión hasta las 18:10: 0,6 h que no entraron en los commits del día y se suman al de la [ADR 0018](../decisiones/0018-bucle-de-juego.md).

### 2026-11-15 a 2026-11-18
- No se hicieron las sesiones previstas (domingo 15, lunes 16 y miércoles 18). La entrega del prototipo se aplaza al jueves 26 de noviembre a las 15:00, con presentación en clase. El sprint 04 se alarga hasta el 25 de noviembre.

### 2026-11-19 (jueves)
- Sesión en clase, sin gafas, desde las 17:23.
- [ADR 0018](../decisiones/0018-bucle-de-juego.md): bucle de juego mínimo, que amplía el alcance de la [ADR 0006](../decisiones/0006-alcance-del-prototipo.md). La congelación pasa al final de la sesión con gafas del fin de semana.
- Código en `Source/TAKT/Game/`: «Dispensador» (`AProductDispenser`, TAKT-37), «Caja de salida» (`AOutputBin`, TAKT-38) y «Marcador» (`AScoreBoard`, TAKT-39). Compilado con `Build.bat` sin errores ni avisos. Todavía sin colocar en `L_Dev_Cinta` ni probar.
- Problema encontrado: al pasar a `develop` con los cambios, GitHub Desktop chocó con dos niveles (`L_Dev_Cinta` y `L_XRTemplate_Lighting`) guardados el 12 de noviembre después del último commit. Se dejan como estaban en `develop`; esos guardados se conservan en un *stash* de GitHub Desktop por si hiciera falta recuperarlos.
- Queda para el fin de semana, con gafas: colocar los dispensadores, la caja y el marcador en `L_Dev_Cinta`, probar el bucle y la partida contrarreloj (TAKT-40).

### 2026-11-22 (domingo)
- Sesión en casa, con gafas, desde las 19:19, en dos partes: se cortó por un problema con el cargador del portátil y se retomó a las 20:55.
- Montaje del bucle en `L_Dev_Cinta`. Referencia: la cinta tiene el centro de la superficie en (−30, −100, 60) y avanza hacia +X; el jugador está al otro lado de la palanca. Dos «Dispensador», uno para cada mano, a la altura de la cinta y a 10 cm de su borde: (−75, −50, 60) y (−5, −50, 60). «Caja de salida» en (92, −100, 30), justo donde acaba la cinta y con el borde 5 cm por debajo. «Marcador» encima y detrás de la cinta, en (−30, −130, 115), con la caja asignada.
- Prueba por Link: **la caja cuenta bien**. Dos productos que llegan juntos cuentan como pareja y uno solo como suelto (en la segunda prueba, 3 parejas y 4 sueltos en el log). Los dispensadores reponen al coger el producto.
- Problemas encontrados:
  - El dispensador derecho dejaba de reponer. Solo reponía al coger o destruir su producto, así que si el producto se caía de la bandeja sin cogerlo se quedaba esperando. Arreglo: cada 0,25 s comprueba si el producto está a más de 25 cm de la bandeja y, si lo está, lo da por perdido y repone. Compilado con `Build.bat` sin errores ni avisos y probado por Link: al echar el cubo de la bandeja con otro cubo, sale uno nuevo.
  - En esa prueba, el log muestra que los productos de la bandeja derecha se caen uno tras otro (uno cada 1-2 s) mientras se sostiene otro cubo encima para echarlos, y algunos acaban en la cinta y llegan a la caja como sueltos. Causa: un cubo cogido deja de tener física pero sigue chocando con los demás, así que empuja al producto nuevo, que aparece en la bandeja 0,5 s después de coger el anterior, con la mano todavía encima. Seguramente es también lo que dejó parado al dispensador derecho en la primera prueba. Alrededor de la bandeja no hay nada más que pueda empujarlos.
  - El marcador no se ve con las gafas. En la primera prueba no tenía la caja asignada (aviso en el log); en la segunda ya no sale el aviso, pero sigue sin verse.
  - La escena sigue viéndose muy oscura con las gafas.
- TAKT-40 (partida contrarreloj con récord) se recorta del prototipo, como ya preveía la [ADR 0018](../decisiones/0018-bucle-de-juego.md): vuelve al backlog. No queda tiempo antes de la entrega.
- Queda para el lunes 23 y el miércoles 25: la bandeja derecha, el marcador, la iluminación, la PR del bucle y la build de entrega con la release `prototipo`.

### 2026-11-25 (miércoles)
- Sesión en casa, con gafas, en dos tramos: desde las 12:30 y desde las 18:00.
- Valoración del tutor (24 de noviembre): el prototipo tiene que transmitir ya, en pequeño, lo que quiere transmitir el juego final. La idea del juego es **la tranquilidad después de la tormenta**: las averías y la presión de la línea son la tormenta; la calma es la línea otra vez en verde y las parejas sumando. El prototipo ya tenía ese ciclo (atasco, luz roja, palanca, verde), pero con la escena tan oscura no se notaba.
- Bandeja derecha: un cubo cogido sigue chocando con los demás, así que el producto nuevo, que aparecía 0,5 s después de coger el anterior, salía con la mano todavía encima y se caía. *Refill Delay* de los dos dispensadores a 1,5 s. Probado por Link: los productos se quedan en la bandeja.
- Iluminación (TAKT-41): sin iluminación global ni exposición automática ([ADR 0015](../decisiones/0015-rendimiento-por-link.md)), todo lo que no recibía la luz directa del sol se veía negro. Se pone una luz de cielo (*Sky Light*) móvil en `L_XRTemplate_Lighting`, y la «Luz de estado» pasa a tener más intensidad y un radio de 350 cm, de modo que tiñe toda la zona de trabajo: roja durante la avería y verde al volver a la marcha.
- Marcador con letras de 14 cm (antes 8); con la escena iluminada ya se lee con las gafas.
- Averías cada 15-30 s (antes 20-45 s), para que en una demostración corta salgan varias.
- Limpieza del nivel: fuera las pistolas, los cubos sueltos y la mesa de la plantilla, que ya no se usaban.
- Prueba por Link: la escena se ve bien y fluida. En el log, 5 parejas y 5 sueltos, y tres averías reparadas con la palanca (una forzada con `ke * TriggerFault`).

### Control de la semana 5 (12–18 nov)
- **Objetivo:** primera build de Windows ✅ (TAKT-36). Build de entrega, prueba por Link y release `prototipo` ❌: no se hicieron las sesiones del domingo 15, el lunes 16 ni el miércoles 18. El tutor pide además un bucle de juego ([ADR 0018](../decisiones/0018-bucle-de-juego.md)).
- **Horas:** 1,7 h (el jueves 12). **Por debajo del mínimo de 6 h.**
- **Plan:** la entrega se aplaza al jueves 26 y el sprint se alarga hasta el 25.

### Control de la semana 6 (19–25 nov)
- **Objetivo:** bucle de juego montado en el nivel y probado por Link ✅ (TAKT-37, TAKT-38 y TAKT-39, PR #20). Iluminación ✅. Build de entrega ✅. Partida contrarreloj con récord ❌: se recorta (TAKT-40).
- **Sesiones:** jueves 19 (en clase, sin gafas), domingo 22 y miércoles 25 (con gafas, en dos tramos). La del lunes 23 no se hizo.
- **Horas:** 5,1 h: 0,5 h el 19, 1,1 h el 22 y 3,5 h el 25. **Por debajo del mínimo de 6 h**, aunque es la semana con más horas desde la segunda.

### 2026-11-26 (jueves)
- Build de entrega del 25 de noviembre: `BUILD SUCCESSFUL` en 2 min 47 s (la primera tardó 36 min), con los mismos dos avisos de extensiones de OpenXR que no se usan. En `E:\TAKT_Builds\Windows\TAKT.exe`.
- Prueba de la build por Link: el jugador aparece delante de la cinta, la escena se ve iluminada, el marcador se lee y el bucle funciona (en una partida, 90 puntos y 15 sueltos). Con `stat unit`: 15,5 ms por fotograma (unos 65 fps), GPU 10,5 ms e hilo de juego 15,3 ms. Se ve fluido, pero queda por debajo de los 72 fps del objetivo: el límite es el hilo de juego, como ya se vio en el editor ([ADR 0015](../decisiones/0015-rendimiento-por-link.md)). Se revisa después de la entrega.
- Entrega al tutor: la carpeta completa de la build en un ZIP, adjunta a la release `prototipo`.
