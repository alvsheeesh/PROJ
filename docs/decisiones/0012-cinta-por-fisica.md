# 0012 — Cinta transportadora por física

- **Estado:** Aceptada
- **Fecha:** 2026-10-21
- **Tarea:** TAKT-24

## Contexto

La cinta es la pieza central de la línea de manipulados: el jugador coge objetos de una pila y los deja encima en marcha ([ADR 0006](0006-alcance-del-prototipo.md)), y las averías la paran. Es también la primera clase en C++ del proyecto. La plantilla *Virtual Reality* de UE 5.8 es solo Blueprint, así que con ella se crea el módulo `TAKT` en `TAKT/Source/`.

El agarre de la plantilla funciona por física: lo que se puede coger simula física mientras está suelto, y deja de simularla mientras el jugador lo sujeta. Para el prototipo bastan unas pocas decenas de objetos a la vez.

## Decisión

- **La cinta mueve por física lo que tiene encima.** `AConveyorBelt` (`Source/TAKT/Line/`) tiene una zona de transporte encima de la superficie. Cada tick, antes de la simulación, busca los cuerpos que simulan física dentro de la zona y lleva su velocidad horizontal hacia la de la cinta. La vertical (gravedad, botes) la sigue gestionando la física.
- **La superficie no tiene fricción** (material físico con fricción 0 y combinación *Min*). Así la velocidad de lo que va encima depende solo de la cinta y no del material de cada objeto. Con la cinta parada, la velocidad objetivo es 0: lo que lleva encima se frena con ella.
- **Interfaz mínima:** `Speed` (cm/s, editable), `SetRunning(bool)` e `IsRunning()`. **La cinta no decide cuándo pararse:** obedece a `SetRunning`, que llamará el estado de la máquina (TAKT-25). Por dentro se puede cambiar de técnica sin tocar a quien la usa.
- Lo que el jugador tiene cogido no simula física, así que la cinta no lo toca y no hay pelea entre la mano y la cinta.
- La búsqueda es una consulta de solapamiento por tipo de objeto (*PhysicsBody* y *WorldDynamic*), no eventos de *overlap*, para no depender de que cada objeto tenga activado *Generate Overlap Events*.
- Forma por defecto con el cubo básico del motor, ajustado a `BeltSize` y `Thickness`, para poder probarla sin assets. El origen del actor es el centro de la superficie y avanza hacia su X local.

## Alternativas descartadas

- **Recorrido fijo por spline, sin física mientras el objeto va en la cinta:** barato y determinista, y es lo que haría falta con cientos de objetos. Pero hay que gestionar cuándo un objeto entra y sale del recorrido, qué pasa al cogerlo de la cinta y cómo se reactiva la física al caer por el final: más estados y más casos raros para un prototipo con pocas decenas de objetos, y un trabajo que no se ve.
- **Cinta solo visual (textura que se desplaza):** no mueve nada, así que no se puede dejar un objeto y verlo avanzar, que es la interacción base del prototipo.
- **Fuerzas (`AddForce`) en vez de velocidad:** el resultado depende de la masa y del rozamiento de cada objeto y cuesta más de ajustar. Llevar la velocidad hacia un objetivo da el mismo efecto con un solo parámetro (`Grip`).
- **Mantener la fricción normal de la superficie:** el rozamiento frena el objeto en cada paso de física y la velocidad real queda por debajo de `Speed`, distinta según el material del objeto.
- **Eventos de overlap de la zona:** obligan a que cada objeto que se pueda coger tenga activado *Generate Overlap Events*; si se olvida en un Blueprint, la cinta no lo mueve y no hay ningún error.

## Consecuencias

- Rendimiento: una consulta de solapamiento y un ajuste de velocidad por objeto en cada tick. Sobra para el prototipo; si algún día hay cientos de objetos en la línea, la técnica se cambia por dentro (por ejemplo, la opción del spline) sin tocar la interfaz.
- Solo cintas rectas y horizontales. Una curva o una rampa necesitará otra clase o ampliar esta.
- Un objeto lanzado que cruce la zona también recibe la velocidad de la cinta mientras está dentro. Con una zona baja (15 cm por defecto) apenas se nota.
- La superficie no se anima: el movimiento visual de la cinta (material que se desplaza) se deja para después, como el resto del arte.
- Para probar sin el estado de la máquina hay un botón `ToggleRunning` en el panel de detalles (también durante la partida) y una opción de depuración que dibuja la zona. Es también el recorte previsto para la semana 2 si TAKT-25 no llega ([planificación](../planificacion.md)).
- Queda por comprobar con las Quest que el agarre de la plantilla quita la simulación física al coger. Si no la quita, la cinta tendrá que ignorar explícitamente lo que se está sujetando.
