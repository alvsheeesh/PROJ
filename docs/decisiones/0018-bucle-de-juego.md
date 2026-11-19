# 0018 — Bucle de juego mínimo para el prototipo

- **Estado:** Aceptada
- **Fecha:** 2026-11-19 (diseño decidido el 2026-11-12)
- **Tareas:** TAKT-37, TAKT-38, TAKT-39, TAKT-40
- **Modifica:** el alcance de la [ADR 0006](0006-alcance-del-prototipo.md)

## Contexto

El 12 de noviembre se enseñó al tutor lo que había: coger y colocar en la cinta, la avería de principio a fin y la primera build. Su valoración: la base está bien, pero falta un bucle de juego, algo que dé ganas de seguir jugando. La [ADR 0006](0006-alcance-del-prototipo.md) había dejado fuera oleadas, progresión e interfaz, y la congelación del alcance empezaba ese mismo día. La entrega se aplazó del 19 al 26 de noviembre a las 15:00, y se presenta en clase con las gafas.

## Decisión

Un bucle mínimo con tres piezas nuevas en `Source/TAKT/Game/`, que se comunican con eventos como la avería ([ADR 0017](0017-averia-palanca-y-luz.md)):

- **Bandeja infinita:** `AProductDispenser` («Dispensador»). Tiene siempre un producto encima (por defecto `BP_Grabbable_SmallCube`). Cuando una mano lo coge (`OnGrabbed` del «Cogible», [ADR 0016](0016-interaccion-generica.md)), pone otro al cabo de *Refill Delay* (0,5 s). Si ya hay *Max Products* suyos en el nivel (10), elimina el más antiguo que nadie sostiene. Dos dispensadores delante de la cinta, uno por mano.
- **Caja de salida:** `AOutputBin` («Caja de salida»), en el hueco al final de la cinta. Detecta con una consulta de solapamiento (como la cinta) los productos que caen dentro y los elimina al poco. **Pareja = dos productos que llegan juntos**, separados menos de *Pair Window* (0,75 s, unos 30 cm con la cinta a 40 cm/s): así se premia colocarlos bien juntos en la cinta. Un producto que llega solo no puntúa. Avisa con `OnPairDelivered` y `OnSingleDelivered`; no sabe nada de puntos.
- **Marcador:** `AScoreBoard` («Marcador»). Escucha a la caja, suma *Points Per Pair* (10) por pareja, cuenta los sueltos y lo enseña con un texto 3D.
- **Partida contrarreloj (TAKT-40, segundo paso):** partidas de unos 2 minutos con cuenta atrás en el marcador; al acabar enseña la puntuación y el récord, y la siguiente empieza sola. Es lo que da un objetivo (superar el récord) y hace que la avería importe: con la línea parada se pierde tiempo. Solo entra si el bucle básico está probado en VR antes del 25 de noviembre; si no, es el recorte.
- **Congelación:** pasa al final de la sesión con gafas del fin de semana del 21-22 de noviembre. El 25, solo correcciones, build y release `prototipo`.
- **Prueba sin gafas:** cubos colocados a mano sobre la cinta en el editor caen en la caja y suman (juntos) o cuentan como sueltos (separados); `ke * Dispense` repone la bandeja. Con gafas: coger de la bandeja, alturas y alcance.

## Alternativas descartadas

- **Casillas que avanzan con la cinta** (colocar cada pareja en un tramo marcado): la cinta mueve los objetos por física, pero su superficie no se mueve; habría que crear marcas sincronizadas y detectar qué hay en cada una. Demasiado para una semana; «llegar juntos a la caja» premia lo mismo.
- **Puntos en el GameMode o el GameState:** es el sitio habitual en Unreal, pero el GameMode del proyecto es el Blueprint de la plantilla y no conviene tocarlo a una semana de la entrega. Se puede mover después del prototipo.
- **Marcador con un widget (UMG):** en VR necesita un `WidgetComponent` y ajustar la interacción; un texto 3D basta para enseñar dos números.
- **Vidas por productos perdidos:** no aplica, porque los productos los coloca el jugador; no llegan solos a la cinta.
- **Seguir con el alcance de la ADR 0006 sin bucle:** cumplía lo planificado, pero no lo que pide quien evalúa el prototipo.

## Consecuencias

- El prototipo pasa de demostrar piezas sueltas a tener una partida: coger, colocar en pareja, puntuar y reparar averías.
- Se pierde la semana de estabilización prevista: la build de entrega se hace el 25 con menos margen. Por eso el reloj es opcional.
- La caja y el marcador no dependen de la cinta ni de la avería: otra forma de puntuar sería otro actor que escuche a la caja.
