# 0014 — Estado de la línea: actor de control con modelo mixto

- **Estado:** Aceptada
- **Fecha:** 2026-10-22
- **Tarea:** TAKT-25

## Contexto

La cinta ([ADR 0012](0012-cinta-por-fisica.md)) no decide cuándo pararse: obedece a `SetRunning`. Hace falta alguien que sea el dueño del estado de la línea (en marcha, parada, averiada) y que se lo diga a las cintas. En la semana 4 se añaden la avería (atasco), la reparación y una luz de color ([planificación](../planificacion.md)), así que el estado tiene que poder escucharse desde piezas que todavía no existen, también desde Blueprint.

## Decisión

- **El dueño del estado es un actor, `ALineController`** («Control de línea», `Source/TAKT/Line/`), que se coloca en el nivel y se configura en el panel de detalles: qué cintas manda (`Belts`) y si empieza en marcha (`bStartRunning`).
- **Tres estados** (`ELineState`): Parada, En marcha y Averiada. Transiciones:
  - Parada → En marcha: `Start` (el botón verde).
  - En marcha → Parada: `Stop`.
  - En marcha → Averiada: `TriggerFault`. Las cintas se paran.
  - Averiada → Parada: `Repair`. **Reparar no vuelve a arrancar la línea:** después hay que pulsar el botón verde (`Start`). Son dos gestos distintos en VR.
  - Cualquier otra llamada no cambia nada, devuelve `false` y se anota en el log.
- **Modelo mixto para avisar a las demás piezas:**
  - Lo que la línea *posee* (las cintas) lo manda directamente: el control llama a `SetRunning`. La cinta sigue sin saber nada del control.
  - Lo que solo *observa* (la luz, los botones, el sonido) se suscribe al evento `OnStateChanged(anterior, nuevo)`, que también se puede usar desde Blueprint. El control no los conoce.
- Para probar sin gafas, `Start`, `Stop`, `TriggerFault` y `Repair` son botones del panel de detalles (también durante la partida).
- El estado inicial se aplica a las cintas en el tick siguiente a `BeginPlay`, porque el orden de `BeginPlay` entre actores no está garantizado y una cinta que empezara después se pondría según su propio `bStartRunning`.

## Alternativas descartadas

- **Subsistema del mundo (`UWorldSubsystem`):** se puede consultar desde cualquier sitio sin referencias, pero no está en el nivel, no tiene panel de detalles para elegir las cintas y supone una sola línea por nivel. Más difícil de configurar y de enseñar.
- **Un componente de estado en cada máquina:** cada cinta tendría su propio estado, pero una avería es de toda la línea. Habría que coordinar los componentes entre sí.
- **GameMode o GameState:** mezcla las reglas de la partida (oleadas, puntos) con la máquina, y es donde irán esas reglas más adelante.
- **Todo por eventos (las cintas también escuchan al control):** obliga a tocar la cinta y esconde una relación de propiedad que es directa.
- **Todo por referencias directas (el control llama a la luz, al sonido…):** cada pieza nueva obliga a cambiar el control.
- **StateTree o una clase por estado:** desproporcionado para tres estados y cuatro transiciones. Si la máquina crece (varias averías con reglas propias), se puede revisar.
- **Que reparar devuelva la línea directamente a En marcha:** más sencillo de jugar, pero junta dos acciones en una. Con el botón verde aparte, el jugador decide cuándo vuelve a arrancar.

## Consecuencias

- Una cinta que no esté en la lista de ningún control sigue funcionando sola, con su `bStartRunning` y su `ToggleRunning`.
- Si una cinta está en un control, su `bStartRunning` deja de importar a partir del primer tick.
- Sin gafas, las transiciones también se pueden lanzar durante la partida con el comando de consola `ke * Start` (o `Stop`, `TriggerFault`, `Repair`). Cada cambio sale en pantalla en las versiones de desarrollo.
- La luz de color y los botones de la semana 4 se pueden hacer en Blueprint escuchando `OnStateChanged`, sin tocar C++.
- La avería todavía no tiene causa ni tipo: `TriggerFault` es un botón. El atasco de la semana 4 decidirá si hace falta un motivo de avería.
- Idea para después del prototipo (fuera del alcance de la [ADR 0006](0006-alcance-del-prototipo.md)): elegir la velocidad de la cinta antes del nivel como dificultad, con más puntos a más dificultad. El control de línea sería el sitio natural para guardar esa velocidad y pasársela a las cintas.
