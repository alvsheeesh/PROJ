# Sprint 03 — Avería

- **Fechas:** 2026-10-29 → 2026-11-11
- **Objetivo:** TAKT va a la frecuencia de las Quest 2 por Link, se coge un objeto de una pila y se coloca en la cinta, y una avería funciona de principio a fin: aparece, para la máquina, se repara con una interacción física y la máquina vuelve a arrancar, con un indicador mínimo de estado.
- **Release:** sprint-03

## Planificación

Tareas en Jira: TAKT-26 (rendimiento por Link, viene del sprint 02), TAKT-29 (interacción genérica: coger y soltar) y TAKT-30 (colocar en la cinta desde la pila). Las de la avería se crearon el 5 de noviembre: TAKT-31 (atasco), TAKT-32 (palanca) y TAKT-33 (luz de estado).

| Semana | Sesiones | Objetivo |
|--------|----------|----------|
| 29 oct–4 nov | jue 29, mié 4 | Rendimiento por Link (TAKT-26). Pila de objetos que se repone. Interacción genérica (agarrar y soltar) separada de la entrada. Colocar en la cinta desde la pila. |
| 5–11 nov | mié 11 + una a elegir el 4 | Avería (atasco) que para la máquina y se repara con una palanca (`accionar`); la máquina vuelve a arrancar. Indicador de estado con una luz de color. Cierre y release `sprint-03`. |

Riesgos:
- La semana 3 empieza con TAKT-26, que venía del sprint anterior: es probable aplicar su recorte (la pila no se repone y los objetos se colocan a mano en el nivel).
- Las gafas están en casa: lo que necesita VR se prueba allí; fuera de casa se trabaja con el *Play* normal del editor.

## Bitácora

### 2026-10-29 (jueves, tarde)
- Segunda sesión de la semana 3, por la tarde y sin las gafas (la de la mañana no se hizo).
- TAKT-26, medición en el editor con *Play* normal en `L_Dev_Cinta` (1387×862): `stat unit` da 3,2 ms de GPU y 5,2 ms de juego. Según `ProfileGPU`, el 44 % del fotograma eran sombras, con un pase por cada objeto: la luz direccional era estacionaria y el nivel no tiene la iluminación construida. Ray tracing, Lumen y las sombras virtuales estaban activados, pero con *forward shading* no se usaban.
- Decidido en la [ADR 0015](../decisiones/0015-rendimiento-por-link.md): luz direccional movible con 2 cascadas y 15 m de sombra, y fuera ray tracing, Lumen, sombras virtuales y campos de distancia. Substrate se queda.
- Resultado en el editor, con la misma medición: **GPU de 3,2 a 1,9 ms (−40 %)**; las sombras pasan de 1,4 a 0,2 ms y la memoria de vídeo de 1,05 a 0,8 GB. Desaparece el aviso de iluminación sin construir. Al reiniciar, el editor recompiló los shaders.
- Falta la medida que cuenta: *VR Preview* por Link con `stat unit`, objetivo 72 fps. Si no llega, el siguiente paso es la resolución de render.
- TAKT-29: decidido el diseño de la interacción propia ([ADR 0016](../decisiones/0016-interaccion-generica.md)): `UGrabbableComponent` en los objetos y `UHandComponent` en cada mano, en C++; el objeto se ancla a la mano y al soltarlo recupera la física con la velocidad de la mano; la entrada se queda en Blueprint. Se implementa el 4 de noviembre. Creada también TAKT-30 (colocar en la cinta desde la pila).

### 2026-11-04 (miércoles)
- TAKT-26 medido por Link (*VR Preview* en `L_Dev_Cinta`, `stat unit`, resolución 2080×2096): **GPU 9,5 ms**, por debajo de los 13,9 ms que permite ir a 72 Hz. Fotograma 14,7 ms (unos 68 fps), frente a los 25-36 fps del 21 de octubre.
- El tiempo de juego (14,5 ms) es casi el del fotograma completo: con OpenXR el hilo de juego espera la sincronización del visor, y en *VR Preview* también carga con el editor. Fuera del editor se espera que llegue a 72; se comprueba con la build de la semana 5. No hace falta bajar la resolución.

- TAKT-29 implementado según la [ADR 0016](../decisiones/0016-interaccion-generica.md): `UGrabbableComponent` («Cogible») y `UHandComponent` («Mano») en `TAKT/Source/TAKT/Interaction/`, con `EnhancedInput` como dependencia del módulo. Antes de fusionarla, la ADR se ajustó en la entrada: cada mano recibe sus *Input Actions* como propiedades y se engancha a ellas sola, en lugar de conectarlas en el gráfico del pawn.
- En `BP_XRPawn`, una *Mano* en cada controlador de agarre con `IA_Grab_*_Pressed` para coger e `IA_Grab_*_Released` para soltar. En `BP_Grabbable_SmallCube`, *Cogible* en lugar del `GrabComponent` de la plantilla.
- Al añadir clases nuevas, el editor no recompila el módulo solo y Live Coding no sirve: se compila con `Build.bat` (comando en [`entorno.md`](../entorno.md)) con el editor cerrado. Las dos compilaciones, sin avisos.
- Probado por Link: se coge, se suelta y se lanza con las dos manos, también un cubo en cada mano a la vez (velocidades al soltar de hasta 7 m/s). Soltar con el grip ya funciona bien, que era el problema del agarre de la plantilla.
- Problemas encontrados:
  - Con una sola acción (`IA_Grab_*_Pressed`) el cubo se soltaba en el fotograma siguiente: con el *trigger* *Pressed* la acción empieza y termina en el mismo gesto. Se separó en dos acciones (coger y soltar), que es como las trae la plantilla.
  - **El alcance es demasiado grande:** se cogen cubos que en la realidad no estarían al alcance. *Grab Radius* es de 15 cm medidos desde el punto de agarre del mando. Se ajustará en el pawn (6-8 cm) en la próxima prueba con gafas, sin tocar código.

### Control de la semana 3 (29 oct–4 nov)
- **Objetivo:** rendimiento por Link ✅ (TAKT-26: unos 68 fps con la GPU a 9,5 ms). Interacción genérica (agarrar y soltar) separada de la entrada ✅ (TAKT-29). Pila que se repone y colocar en la cinta desde la pila ❌ (TAKT-30): se aplica el recorte previsto, objetos colocados a mano en el nivel, y pasa a la semana 4.
- **Sesiones:** 2 de 2: el jueves 29 por la tarde, sin gafas (la de la mañana no se hizo y se recuperó por la tarde), y el miércoles 4 por la tarde, con gafas.
- **Horas:** 3,6 h: 1,1 h el 29 y 2,5 h el 4. **Por debajo del mínimo de 6 h.**
- **Semana 4:** segunda sesión el **jueves 5 por la tarde, sin gafas**: código de la avería (atasco), de la palanca (`accionar`) y de la luz, probado con `ke`. El miércoles 11, con gafas: prueba por Link, TAKT-30 con el recorte, ajuste del alcance y cierre del sprint 03.

### 2026-11-05 (jueves)
- Sesión en clase, sin gafas. Decidido el diseño de la avería en la [ADR 0017](../decisiones/0017-averia-palanca-y-luz.md) y creadas TAKT-31 (atasco), TAKT-32 (palanca) y TAKT-33 (luz).
- TAKT-31: componente «Averías aleatorias» (`URandomFaultComponent`) en el control de línea. Cada vez que la línea arranca programa el atasco entre *Min Delay* y *Max Delay* segundos y lo cancela si la línea se para antes.
- TAKT-32: evento genérico `accionar` con el componente «Accionable» (`UActuatableComponent`, `OnActuated`) y la «Palanca» (`ALever`), que repara la línea averiada y la vuelve a arrancar. La mano acciona con el mismo grip si el accionable está más cerca que cualquier cogible. Se llama *Actuate* porque `UActorComponent` ya tiene `Activate`.
- TAKT-33: «Luz de estado» (`AStatusLight`): bola y luz puntual sin sombras, verde en marcha, ámbar parada y roja averiada, escuchando `OnStateChanged`.
- Compilado con `Build.bat`, sin avisos. Montado en `L_Dev_Cinta` con *Min/Max Delay* de 5 y 10 s para probar.
- Probado en el *Play* normal: la línea se atasca sola, la cinta se para y la luz se pone roja; `ke * Actuate` repara y vuelve a arrancar (Averiada → Parada → En marcha) y la luz vuelve a verde. Si la línea se para antes del atasco, no salta. Accionar la palanca cuando no hay avería solo mueve el mango.
- Problemas encontrados:
  - No se distingue si la bola de la luz cambia de color: se ve oscura y lo que cambia claramente es la luz que da alrededor. Se mira con las gafas el miércoles; si no cambia, la bola necesita un material emisivo.
- Queda para el miércoles 11, con gafas: accionar la palanca con el grip por Link, devolver *Min/Max Delay* a valores de juego y TAKT-30.

## Revisión

_Al cerrar el sprint._

## Retrospectiva

_Al cerrar el sprint._
