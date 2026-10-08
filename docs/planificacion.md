# Planificación

## Hitos

| Fecha | Hito |
|-------|------|
| 2026-10-01 | Arranque del desarrollo |
| 2026-10-08 | Control del motor: si no hay build vacía en Quest 2, plan B a UE 5.7 ([ADR 0005](decisiones/0005-unreal-5-8-meta-xr-v207.md)) |
| 2026-11-12 | Congelación de funcionalidades: a partir de aquí solo correcciones |
| 2026-11-18 | Cierre real del prototipo: build de entrega y release `prototipo` |
| **2026-11-19 15:00** | **Entrega del prototipo** |

## Sprints hasta el prototipo

El alcance está fijado en la [ADR 0006](decisiones/0006-alcance-del-prototipo.md): base técnica con interacción.

| Sprint | Fechas | Objetivo |
|--------|--------|----------|
| [01](sprints/sprint-01.md) · Pipeline Quest 2 | 1–14 oct | TAKT corre en las Quest 2 en modo autónomo y se coge un objeto con los mandos. |
| 02 · Línea | 15–28 oct | Tramo de cinta transportadora con objetos que avanzan. Coger de una pila y colocar en la cinta. Estado de la máquina (marcha/parada) en C++. |
| 03 · Avería | 29 oct–11 nov | Una avería de principio a fin: aparece, para la máquina, se repara con una interacción física y la máquina vuelve a funcionar. Indicador mínimo de estado. |
| 04 · Estabilización | 12–18 nov | Sin funcionalidades nuevas. Rendimiento en Quest 2 (objetivo 72 fps estables), build de entrega, documentación y release `prototipo`. |

Los sprints son de 2 semanas mientras no se concrete la cadencia de revisión del profesor. El 04 es más corto porque termina el día antes de la entrega.

## Después del prototipo

Oleadas y progresión, más tipos de avería, UI/UX en VR completa, seguimiento de manos, audio y arte, y rendimiento y build final. Se planifica tras la entrega del 19 de noviembre.
