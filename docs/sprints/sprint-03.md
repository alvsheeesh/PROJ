# Sprint 03 — Avería

- **Fechas:** 2026-10-29 → 2026-11-11
- **Objetivo:** TAKT va a la frecuencia de las Quest 2 por Link, se coge un objeto de una pila y se coloca en la cinta, y una avería funciona de principio a fin: aparece, para la máquina, se repara con una interacción física y la máquina vuelve a arrancar, con un indicador mínimo de estado.
- **Release:** sprint-03

## Planificación

Tareas en Jira: TAKT-26 (rendimiento por Link, viene del sprint 02). Las de la pila, la interacción genérica (agarrar y soltar) y la avería se crean al empezar cada semana.

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

## Revisión

_Al cerrar el sprint._

## Retrospectiva

_Al cerrar el sprint._
