# Planificación

## Hitos

| Fecha | Hito |
|-------|------|
| 2026-10-01 | Arranque del desarrollo |
| 2026-10-08 | Control del motor: superado sin plan B ([ADR 0005](decisiones/0005-unreal-5-8-meta-xr-v207.md)) |
| 2026-10-14 | Cierre del sprint 1: objetivo no cumplido, sin proyecto de Unreal ([revisión](sprints/sprint-01.md#revisión)) |
| 2026-10-15 | Replanificación: prototipo por Quest Link ([ADR 0010](decisiones/0010-prototipo-por-quest-link.md)) y ritmo semanal ([ADR 0011](decisiones/0011-ritmo-de-trabajo.md)) |
| 2026-11-12 | Congelación de funcionalidades: a partir de aquí solo correcciones |
| 2026-11-18 | Cierre real del prototipo: build de entrega y release `prototipo` |
| **2026-11-19 15:00** | **Entrega del prototipo** |

## Ritmo de trabajo

Mínimo de **9 horas a la semana** en tres sesiones: **lunes, miércoles y viernes por la mañana**. Cada sesión acaba con push. Una sesión perdida se recupera la misma semana. Detalle en la [ADR 0011](decisiones/0011-ritmo-de-trabajo.md).

Cada sesión:

1. *Fetch* y *Pull* de `develop`; la tarea de Jira pasa a *En curso*; rama `tipo/TAKT-NN-…` si es una tarea nueva.
2. Commits pequeños con las horas reales y el impacto ([`CONTRIBUTING.md`](../CONTRIBUTING.md)).
3. Push antes de cerrar, y una línea en la bitácora del sprint.

Cada miércoles: horas de la semana con `git log` y comprobación del objetivo. Si no se ha cumplido, se aplica el recorte previsto de la tabla.

## Sprints hasta el prototipo

El alcance está fijado en la [ADR 0006](decisiones/0006-alcance-del-prototipo.md): base técnica con interacción, por Quest Link ([ADR 0010](decisiones/0010-prototipo-por-quest-link.md)).

| Sprint | Fechas | Objetivo |
|--------|--------|----------|
| [01](sprints/sprint-01.md) · Pipeline Quest 2 | 1–14 oct | Entorno instalado y flujo de trabajo definido. **Sin proyecto:** pasa al sprint 02. |
| [02](sprints/sprint-02.md) · Proyecto y línea | 15–28 oct | TAKT corre por Link desde el repositorio, se coge un objeto con los mandos y un tramo de cinta en C++ transporta objetos, con estado de la máquina (marcha/parada). |
| 03 · Avería | 29 oct–11 nov | Coger de una pila y colocar en la cinta. Una avería de principio a fin: aparece, para la máquina, se repara con una interacción física y la máquina vuelve a funcionar. Indicador mínimo de estado. |
| 04 · Estabilización | 12–18 nov | Sin funcionalidades nuevas. Rendimiento por Link, build de entrega, documentación y release `prototipo`. APK autónomo solo si sobra tiempo. |

## Semana a semana

Semanas de jueves a miércoles: tres sesiones (viernes, lunes, miércoles) y la última justo antes de la clase del jueves.

| Semana | Sesiones | Objetivo (subido el miércoles) | Recorte previsto si no se llega |
|--------|----------|-------------------------------|---------------------------------|
| 1 · 15–21 oct | 16, 19, 21 | Pendientes del 8 de octubre subidos. Proyecto C++ `TAKT/` desde la plantilla VR, con LFS, en el repositorio. Funciona por Link y se coge un objeto con los mandos. | Ninguno: es la base de todo lo demás. Se recupera el jueves o el fin de semana. |
| 2 · 22–28 oct | 23, 26, 28 | Cinta en C++ que mueve los objetos que tiene encima, con velocidad configurable. Estado de la máquina (marcha/parada) en C++ que para y arranca la cinta. Cierre del sprint 02 y release `sprint-02`. | Velocidad fija y estado conmutado desde un botón de depuración. |
| 3 · 29 oct–4 nov | 30, 2, 4 | Pila de objetos que se repone. Interacción genérica (agarrar, soltar, accionar) separada de la entrada. Colocar en la cinta desde la pila. | `Accionar` se deja para la semana 4, con la avería. |
| 4 · 5–11 nov | 6, 9, 11 | Una avería (atasco) que para la máquina, se repara con una interacción física y la máquina vuelve a arrancar. Indicador de estado. Cierre del sprint 03 y release `sprint-03`. | Reparación con una sola acción (una palanca) e indicador como una luz de color. |
| 5 · 12–18 nov | 13, 16, 18 | Correcciones, rendimiento, documentación y release `prototipo`. | Sin APK autónomo. |

Total previsto: unas 45 horas de mínimo. No hay margen dentro del mínimo: las horas de más son el colchón.

## Después del prototipo

Volver al objetivo autónomo en las Quest 2 (Meta XR Plugin y APK), oleadas y progresión, más tipos de avería, UI/UX en VR completa, seguimiento de manos, audio y arte, y rendimiento y build final. Se planifica tras la entrega del 19 de noviembre.
