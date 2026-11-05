# 0017 — Avería de principio a fin: atasco aleatorio, palanca accionable y luz de estado

- **Estado:** Aceptada
- **Fecha:** 2026-11-05
- **Tareas:** TAKT-31, TAKT-32, TAKT-33

## Contexto

La [ADR 0006](0006-alcance-del-prototipo.md) pide para el prototipo una avería de principio a fin, y la [ADR 0013](0013-ritmo-miercoles-y-sesion-elegida.md) la recorta a un atasco que para la máquina, se repara con una palanca y se indica con una luz de color. El estado de la línea ya existe ([ADR 0014](0014-estado-de-la-linea.md)): `ALineController` con `TriggerFault`, `Repair` y el evento `OnStateChanged`. La interacción propia ([ADR 0016](0016-interaccion-generica.md)) tiene coger y soltar, y dejó para esta semana el tercer evento genérico, `accionar`. Hay que decidir qué provoca el atasco, cómo se acciona la palanca y cómo se hace la luz.

## Decisión

- **Atasco por temporizador aleatorio:** componente `URandomFaultComponent` («Averías aleatorias», `Source/TAKT/Line/`) que se añade al control de línea. Cada vez que la línea pasa a En marcha, elige una espera entre *Min Delay* y *Max Delay* (20-45 s por defecto) y después llama a `TriggerFault`. Si la línea deja de estar en marcha antes, cancela la espera. El control no sabe que existe.
- **`accionar` en un componente hermano:** `UActuatableComponent` («Accionable», `Source/TAKT/Interaction/`) con el evento `OnActuated(mano)` y la función `Actuate(mano)`, con un tiempo mínimo entre accionamientos. Se llama *Actuate* y no *Activate* porque `UActorComponent` ya tiene `Activate`/`IsActive` para encender y apagar componentes.
- **Mismo gesto que coger:** al apretar el grip, la mano busca el cogible y el accionable más cercanos dentro de su radio; si el accionable está más cerca (o no hay cogible), lo acciona. No hace falta ninguna entrada nueva en el pawn.
- **Palanca:** actor `ALever` («Palanca», `Source/TAKT/Line/`) hecho con las formas básicas del motor y un «Accionable». Tiene la propiedad *Line*. Al accionarla, si la línea está averiada llama a `Repair` y, si *Start After Repair* está activado (por defecto), a `Start`: la máquina vuelve a arrancar. En otro estado solo se mueve. El mango baja y vuelve a subir como respuesta visual.
- **Luz de estado:** actor `AStatusLight` («Luz de estado», `Source/TAKT/Line/`) con una bola y una luz puntual sin sombras. Tiene la propiedad *Line* y un color por estado editable en *Detalles* (verde en marcha, ámbar parada, rojo averiada). Escucha `OnStateChanged`, sin gráficos de Blueprint.
- **Prueba sin gafas:** en el *Play* normal de `L_Dev_Cinta`, con *Min/Max Delay* bajos, la línea pasa sola a Averiada y la luz se pone roja; `ke * Actuate` repara y vuelve a arrancar (luz verde). `ke * TriggerFault`, `ke * Stop` y `ke * Start` sirven para recorrer todos los colores. Accionar con el grip se prueba por Link.
- **Recorte (sin cambios):** si el temporizador da problemas, la avería se provoca a mano con `TriggerFault`.

## Alternativas descartadas

- **Atasco por detección física** (un objeto parado en la cinta en marcha durante unos segundos, o demasiados objetos al final): depende de la física y de TAKT-30, es frágil y sin gafas no se puede probar bien. Desproporcionado para el tiempo que queda; sería otro componente que llame a `TriggerFault`.
- **Atasco al pasar N objetos:** necesita un sensor de paso al final de la cinta y no aporta mucho frente al temporizador.
- **Poner el temporizador en el propio control de línea:** mezcla el estado con una de sus posibles causas.
- **`OnActivated` dentro de `UGrabbableComponent`:** obligaría a que todo lo que se acciona se pueda coger, y la palanca no se coge.
- **Palanca física que se coge y se gira hasta un umbral:** más realista en VR, pero el agarre de la ADR 0016 engancha el objeto a la mano sin física, así que habría que cambiar la mano. Se puede hacer después del prototipo sin cambiar el evento `OnActuated`.
- **Otra *Input Action* para accionar (por ejemplo, el gatillo):** hay que añadirla al pawn y enseñar al jugador un segundo botón para algo que se hace con la mano.
- **Luz en Blueprint:** obliga a editar nodos de un gráfico.
- **Luz como componente del control de línea:** quedaría pegada al control y no se podría colocar donde se vea.

## Consecuencias

- La avería se ve de principio a fin con tres piezas independientes que solo se conocen a través del control de línea.
- La mano ya tiene los tres eventos genéricos de la ADR 0006: agarrar, soltar y accionar.
- Si una palanca y un cubo están igual de cerca, gana el más cercano por muy poco; en la prueba con gafas se verá si hace falta dar prioridad a uno.
- La bola de la luz usa el material de las formas básicas del motor; si su parámetro de color no se llama `Color`, se cambia *Color Parameter Name* en *Detalles* o se le pone otro material.
