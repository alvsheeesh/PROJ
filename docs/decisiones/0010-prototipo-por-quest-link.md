# 0010 — Prototipo por Quest Link con OpenXR

- **Estado:** Aceptada
- **Fecha:** 2026-10-15
- **Aplaza:** el Meta XR Plugin de la [0005](0005-unreal-5-8-meta-xr-v207.md) y la [0008](0008-toolchain-android-sin-android-studio.md) hasta después del prototipo

## Contexto

El sprint 1 terminó el 14 de octubre sin proyecto de Unreal ni build en las Quest 2. Hasta la entrega del 19 de noviembre quedan cinco semanas, con una semana de retraso respecto a la [planificación](../planificacion.md).

La plantilla *Virtual Reality* de UE 5.8 usa OpenXR y funciona por Quest Link, con el juego ejecutándose en el PC y las Quest como visor. El profesor ha dicho que le da igual cómo se enseñe el prototipo, siempre que se vea la programación.

Lo que hace falta para ejecutar en las Quest de forma autónoma (APK, SDK y NDK de Android, firma, Meta XR Plugin) no aporta nada a la lógica de la línea ni de las averías, que es lo que se evalúa en el prototipo.

## Decisión

- El prototipo se desarrolla y se enseña **por Quest Link**, con el proyecto creado desde la plantilla *Virtual Reality* (OpenXR) en C++.
- El **Meta XR Plugin no se instala hasta después del prototipo**. Solo se necesita para el seguimiento de manos y las funciones propias de Quest, que ya estaban fuera del alcance ([ADR 0006](0006-alcance-del-prototipo.md)).
- **El APK queda como extra:** si en la semana de estabilización sobra tiempo, se intenta una build autónoma. Si no sale, no bloquea la entrega.
- El motor sigue siendo **UE 5.8.3** y sigue congelado ([ADR 0005](0005-unreal-5-8-meta-xr-v207.md)).

## Alternativas descartadas

- **Mantener el objetivo autónomo:** añade al camino crítico la toolchain de Android, el empaquetado y la depuración en el visor, justo cuando vamos con retraso. Es el riesgo que más tiempo puede comerse sin dejar nada que enseñar.
- **Instalar el Meta XR Plugin igualmente:** más configuración y otra posible fuente de errores, sin ninguna función que el prototipo use.
- **Simulador XR sin visor:** sirve para probar la lógica, pero no las sensaciones de coger objetos con los mandos, que es la base de la interacción.

## Consecuencias

- La toolchain de Android ya instalada ([ADR 0008](0008-toolchain-android-sin-android-studio.md)) se queda como está, sin usarse hasta el APK.
- El rendimiento se mide en el PC por Link. Los 72 fps en la Quest autónoma pasan a después del prototipo, y el contenido se mantiene ligero para que el salto no sea traumático.
- La interacción sigue separada de la fuente de entrada ([ADR 0006](0006-alcance-del-prototipo.md)), así que pasar al plugin de Meta o al seguimiento de manos no toca la lógica del juego.
- Después del prototipo hace falta una ADR que decida cuándo se vuelve al objetivo autónomo.
