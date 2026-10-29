# 0015 — Rendimiento por Link: luz movible con sombras en cascada y sin funciones que no se usan

- **Estado:** Aceptada
- **Fecha:** 2026-10-29
- **Tarea:** TAKT-26

## Contexto

El 21 de octubre, la prueba por Quest Link iba a unos 25-36 fps (`stat fps`), muy por debajo de los 72 Hz de las Quest 2. Por debajo de esa frecuencia la prueba en VR marea y no sirve para valorar la interacción.

Medición del 29 de octubre en el editor, sin gafas, con *Play* normal en `L_Dev_Cinta` a 1387×862:

- `stat unit`: juego 5,2 ms, dibujado 2,9 ms y **GPU 3,2 ms**. A 72 Hz hay 13,9 ms por fotograma. El juego cabe; el límite es la GPU, que en VR pinta dos ojos a unas 6-7 veces esa resolución (de ahí los ~40 fps estimados por Link).
- `ProfileGPU`: **el 34 % del fotograma es proyección de sombras y otro 10 % cálculo de sombras**, con un pase por objeto (*PerObject*). La luz direccional (subnivel `L_XRTemplate_Lighting`) es estacionaria y el nivel no tiene la iluminación construida (el `_BuiltData` no se versiona), así que el motor cae en sombras dinámicas por objeto, que son caras.
- Ray tracing, Lumen y las sombras virtuales están activados en el proyecto (vienen de la plantilla), pero no aparecen en el perfil: con *forward shading* ([ADR 0010](0010-prototipo-por-quest-link.md), plantilla VR) no se usan.

## Decisión

- **La luz direccional pasa a *Movible*** con sombras en cascada de corto alcance: **2 cascadas** y **15 m** de distancia de sombra dinámica. Un solo mapa de sombras para toda la escena en lugar de un pase por objeto, sin construir la iluminación.
- **Se apagan en `DefaultEngine.ini` las funciones que no se usan con *forward shading*:** ray tracing (`r.RayTracing`, y sus *proxies*), Lumen para la iluminación global y los reflejos (`r.DynamicGlobalIlluminationMethod=0`, `r.ReflectionMethod=0`), sombras virtuales (`r.Shadow.Virtual.Enable=0`) y campos de distancia (`r.GenerateMeshDistanceFields=False`). No cambia lo que se ve y ahorra memoria de vídeo y trabajo de fondo.
- **Substrate se mantiene:** no aparece en el perfil y desactivarlo puede obligar a convertir los materiales de la plantilla.
- La medida que cuenta es la de **VR Preview por Link con `stat unit`**. Si con esto no se llega a 72 fps, la siguiente palanca es la resolución de render (densidad de píxeles de Link o `r.ScreenPercentage`).

## Alternativas descartadas

- **Construir la iluminación (*Build Lighting*) y versionar el `_BuiltData` por LFS:** es lo que más rinde y lo habitual en VR autónoma, pero obliga a reconstruir cada vez que se mueve algo estático, y en las semanas 3 y 4 el nivel cambia constantemente. Se retoma con el APK para Quest, después del prototipo.
- **Quitar las sombras de la luz principal:** lo más barato, pero en VR las sombras ayudan a calcular la distancia al coger objetos, que es la mecánica central.
- **Bajar la resolución de render primero:** se pierde nitidez en todo para pagar un coste que está en un sitio concreto. Queda como siguiente paso si hace falta.
- **Desactivar también Substrate:** sin coste medido y con riesgo de romper materiales.
- **No medir y aplicar la lista habitual de recortes de VR:** sin la medición no se habría visto que el problema eran las sombras por objeto.

## Consecuencias

- Al reiniciar el editor se recompilan los shaders (ray tracing y campos de distancia cambian las permutaciones).
- El aviso «La iluminación debe ser reconstruida» desaparece para la luz direccional, porque ya no es estacionaria.
- El cambio de la luz está en el subnivel `L_XRTemplate_Lighting`, que comparten `L_Dev_Cinta` y el mapa de la plantilla.
- Las sombras se cortan a 15 m: suficiente para una línea de manipulados a escala de habitación.
- Sin gafas, el coste de las sombras se comprueba con `ProfileGPU` en el *Play* normal; la cifra final de fps se toma por Link.
