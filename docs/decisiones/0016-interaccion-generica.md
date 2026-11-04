# 0016 — Interacción genérica: componentes en C++ para coger y soltar

- **Estado:** Aceptada
- **Fecha:** 2026-10-29 (la entrada se revisó el 2026-11-04, antes de fusionarla)
- **Tarea:** TAKT-29

## Contexto

La [ADR 0006](0006-alcance-del-prototipo.md) pide para el prototipo coger objetos con los mandos y colocarlos en una cinta en marcha, con la interacción hecha por eventos genéricos (agarrar, soltar, accionar) y una arquitectura C++ extensible. Hasta ahora se usa el agarre de la plantilla VR (`BP_GrabComponent`, en Blueprint), que mezcla la entrada con la lógica y al que le cuesta soltar con el grip (bitácora del 21 de octubre). La [planificación](../planificacion.md) pone en la semana 3 una interacción propia, separada de la entrada; `accionar` llega en la semana 4 con la palanca de la avería.

## Decisión

- **`UGrabbableComponent`** (C++, `Source/TAKT/Interaction/`): se añade a cualquier actor con física para que se pueda coger. Avisa con los eventos `OnGrabbed(mano)` y `OnReleased(mano)`, que también se pueden usar desde Blueprint. No sabe nada de mandos.
- **`UHandComponent`** (C++): va en cada mano del pawn. `Grab()` busca el cogible más cercano dentro de un radio; `Release()` suelta lo que sostiene. Lleva la cuenta de su propia velocidad para que el objeto se pueda lanzar.
- **Se ancla a la mano:** al coger, el objeto apaga su física y se engancha a la mano; al soltar, recupera la física con la velocidad de la mano.
- **La entrada se elige con datos:** cada mano tiene las propiedades *Grab Action* y *Release Action*, con las *Input Actions* del grip de su mando (Enhanced Input; en la plantilla, `IA_Grab_Left_Pressed` e `IA_Grab_Left_Released`, y las de la derecha), que se asignan en el pawn. La mano se engancha a ellas sola: coge cuando se dispara la primera y suelta cuando se dispara la segunda. Sin *Release Action*, suelta cuando termina la acción de coger (para una acción sin *triggers* que dura mientras se mantiene el botón). Cambiar de botón o de mando se hace en el *Input Mapping Context*, sin tocar el C++ ni el gráfico del pawn. `Grab()` y `Release()` siguen siendo públicas para llamarlas desde otro sitio.
- Igual que el control de línea ([ADR 0014](0014-estado-de-la-linea.md)), lo demás (cinta, pila, sonido) se entera escuchando eventos, sin conocer la mano.
- **Prueba sin gafas:** en el *Play* normal, `ke * Grab` y `ke * Release` cogen y sueltan el cogible más cercano a la mano, y los eventos se ven en el log y en pantalla (solo en desarrollo). La prueba de verdad (coger, soltar y lanzar) es por Link.

## Alternativas descartadas

- **Interfaz de C++ (`IInteractable`) en lugar de componente:** cada clase de objeto tendría que implementarla en código. Un componente se añade desde el editor a cualquier actor, también a los cubos de la plantilla.
- **Seguir con el `BP_GrabComponent` de la plantilla:** la lógica se queda en un Blueprint ajeno, la entrada sigue mezclada con la interacción y el problema al soltar con el grip no se resuelve.
- **Conectar el grip a `Grab()` y `Release()` en el gráfico del pawn** (la primera versión de esta ADR): obliga a editar y desconectar nodos del Blueprint de la plantilla, y la conexión queda escondida en un gráfico en lugar de verse en las propiedades de cada mano.
- **Interaction SDK de Meta:** viene dentro del Meta XR Plugin, aplazado por la [ADR 0010](0010-prototipo-por-quest-link.md). Unreal no trae ningún plugin propio para coger objetos en VR; la plantilla lo hace en Blueprint.
- **Plugin de interacción VR de terceros (VR Expansion Plugin o similar):** hace mucho más de lo necesario, depende de que sea compatible con el motor congelado en 5.8 ([ADR 0005](0005-unreal-5-8-meta-xr-v207.md)) y sustituye el código propio que el prototipo tiene que enseñar.
- **Arrastrar el objeto con física (`UPhysicsHandleComponent`):** el objeto choca mientras se sostiene, pero tiembla y necesita ajustes. Se puede revisar después del prototipo.
- **Decidir ahora `accionar`:** llega en la semana 4 con la palanca. Será otro evento en este componente o un componente hermano; se decide entonces.

## Consecuencias

- El módulo `TAKT` depende de `EnhancedInput` (en `TAKT.Build.cs`).
- En el pawn de la plantilla (`BP_XRPawn`) se añade un componente *Mano* a cada controlador de movimiento con sus dos acciones.
- Los cubos de la plantilla pasan a usar `UGrabbableComponent` en lugar de `BP_GrabComponent` en `L_Dev_Cinta`. El resto de la plantilla no se toca.
- La pila y la cinta pueden reaccionar a `OnGrabbed`/`OnReleased` (por ejemplo, para reponer la pila) sin que la mano lo sepa.
- Mientras se sostiene, el objeto no choca con nada: atraviesa la cinta y las paredes. Para el prototipo es aceptable.
