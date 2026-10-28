# Planificación

## Hitos

| Fecha | Hito |
|-------|------|
| 2026-10-01 | Arranque del desarrollo |
| 2026-10-08 | Control del motor: superado sin plan B ([ADR 0005](decisiones/0005-unreal-5-8-meta-xr-v207.md)) |
| 2026-10-14 | Cierre del sprint 1: objetivo no cumplido, sin proyecto de Unreal ([revisión](sprints/sprint-01.md#revisión)) |
| 2026-10-15 | Replanificación: prototipo por Quest Link ([ADR 0010](decisiones/0010-prototipo-por-quest-link.md)) y ritmo semanal ([ADR 0011](decisiones/0011-ritmo-de-trabajo.md)) |
| 2026-10-22 | Nuevo ritmo: miércoles fijo y una segunda sesión elegida cada semana, con los recortes previstos ya aplicados ([ADR 0013](decisiones/0013-ritmo-miercoles-y-sesion-elegida.md)) |
| 2026-10-28 | Cierre del sprint 02: objetivo cumplido; el rendimiento por Link (TAKT-26) pasa al sprint 03 ([revisión](sprints/sprint-02.md#revisión)) |
| 2026-11-12 | Congelación de funcionalidades: a partir de aquí solo correcciones |
| 2026-11-18 | Cierre real del prototipo: build de entrega y release `prototipo` |
| **2026-11-19 15:00** | **Entrega del prototipo** |

## Ritmo de trabajo

Mínimo de **6 horas a la semana** en dos sesiones: el **miércoles por la mañana**, fijo y de 4 horas o más, y una **segunda sesión** que se elige en el control de cada miércoles para la semana siguiente. Cada sesión acaba con push. Si la segunda sesión se pierde, se recupera antes del miércoles siguiente. Detalle en la [ADR 0013](decisiones/0013-ritmo-miercoles-y-sesion-elegida.md), que sustituye a la [ADR 0011](decisiones/0011-ritmo-de-trabajo.md) (tres sesiones fijas y 9 h a la semana, vigente hasta el 21 de octubre).

Cada sesión:

1. *Fetch* y *Pull* de `develop`; la tarea de Jira pasa a *En curso*; rama `tipo/TAKT-NN-…` si es una tarea nueva.
2. Commits pequeños con las horas reales y el impacto ([`CONTRIBUTING.md`](../CONTRIBUTING.md)).
3. Push antes de cerrar, y una línea en la bitácora del sprint.

Cada miércoles: horas de la semana con `git log`, comprobación del objetivo y día de la segunda sesión de la semana siguiente. Si el objetivo no se ha cumplido, se decide qué más se recorta en lugar de arrastrarlo.

## Sprints hasta el prototipo

El alcance está fijado en la [ADR 0006](decisiones/0006-alcance-del-prototipo.md): base técnica con interacción, por Quest Link ([ADR 0010](decisiones/0010-prototipo-por-quest-link.md)).

| Sprint | Fechas | Objetivo |
|--------|--------|----------|
| [01](sprints/sprint-01.md) · Pipeline Quest 2 | 1–14 oct | Entorno instalado y flujo de trabajo definido. **Sin proyecto:** pasa al sprint 02. |
| [02](sprints/sprint-02.md) · Proyecto y línea | 15–28 oct | ✅ TAKT corre por Link desde el repositorio, se coge un objeto con los mandos y un tramo de cinta en C++ transporta objetos, con estado de la máquina (marcha/parada). |
| 03 · Avería | 29 oct–11 nov | Rendimiento por Link (TAKT-26, viene del sprint 02). Coger de una pila y colocar en la cinta. Una avería de principio a fin: aparece, para la máquina, se repara con una interacción física y la máquina vuelve a funcionar. Indicador mínimo de estado. |
| 04 · Estabilización | 12–18 nov | Sin funcionalidades nuevas. Rendimiento por Link, build de entrega, documentación y release `prototipo`. APK autónomo solo si sobra tiempo. |

## Semana a semana

Semanas de jueves a miércoles; la sesión del miércoles queda justo antes de la clase del jueves. Desde la semana 2 rige la [ADR 0013](decisiones/0013-ritmo-miercoles-y-sesion-elegida.md): los recortes que antes estaban previstos ya forman parte del objetivo, y la última columna dice qué se recorta si aun así no se llega.

| Semana | Sesiones | Objetivo (subido el miércoles) | Recorte si no se llega |
|--------|----------|-------------------------------|------------------------|
| 1 · 15–21 oct | 16, 19, 21 | Pendientes del 8 de octubre subidos. Proyecto C++ `TAKT/` desde la plantilla VR, con LFS, en el repositorio. Funciona por Link y se coge un objeto con los mandos. | Ninguno: es la base de todo lo demás. Se recupera el jueves o el fin de semana. |
| 2 · 22–28 oct | vie 23 (perdida), mié 28 | Cinta en C++ ✅ (adelantada al 21 oct). Rendimiento por Link a la frecuencia de las Quest 2 (TAKT-26) ❌: pasa a la semana 3. Estado de la máquina (marcha/parada) en C++ que para y arranca la cinta (TAKT-25) ✅. Cierre del sprint 02 y release `sprint-02` ✅. | Estado de la máquina conmutado desde un botón de depuración. |
| 3 · 29 oct–4 nov | jue 29, mié 4 | Rendimiento por Link a la frecuencia de las Quest 2 (TAKT-26, viene de la semana 2). Pila de objetos que se repone. Interacción genérica (agarrar y soltar) separada de la entrada. Colocar en la cinta desde la pila. `Accionar` pasa a la semana 4, con la avería. | La pila no se repone: objetos colocados a mano en el nivel. |
| 4 · 5–11 nov | mié 11 + una a elegir el 4 | Una avería (atasco) que para la máquina y se repara con una palanca (`accionar`); la máquina vuelve a arrancar. Indicador de estado con una luz de color. Cierre del sprint 03 y release `sprint-03`. | La avería se provoca con un botón de depuración en vez de aparecer sola. |
| 5 · 12–18 nov | mié 18 + una a elegir el 11 | Correcciones, rendimiento, documentación y release `prototipo`. Sin APK autónomo. | Solo correcciones bloqueantes y documentación. |

Total previsto: unas 24 horas de mínimo (4 semanas × 6 h) desde el 22 de octubre. Con los recortes ya aplicados, el alcance cabe justo: las horas de más son el colchón.

## Después del prototipo

Volver al objetivo autónomo en las Quest 2 (Meta XR Plugin y APK), oleadas y progresión, más tipos de avería, UI/UX en VR completa, seguimiento de manos, audio y arte, y rendimiento y build final. Se planifica tras la entrega del 19 de noviembre.
