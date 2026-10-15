# Sprint 02 — Proyecto y línea

- **Fechas:** 2026-10-15 → 2026-10-28
- **Objetivo:** TAKT corre por Quest Link desde el repositorio, se coge un objeto con los mandos y un tramo de cinta en C++ transporta objetos, con el estado de la máquina (marcha/parada).
- **Release:** sprint-02

## Planificación

Incluye lo que no se hizo en el sprint 01 (crear el proyecto y cogerlo por Link). Primer sprint con el ritmo de la [ADR 0011](../decisiones/0011-ritmo-de-trabajo.md): lunes, miércoles y viernes por la mañana, mínimo 9 horas a la semana.

| Semana | Sesiones | Objetivo |
|--------|----------|----------|
| 15–21 oct | vie 16, lun 19, mié 21 | Pendientes del 8 de octubre subidos. Proyecto C++ `TAKT/` en el repositorio con LFS. Funciona por Link y se coge un objeto con los mandos. |
| 22–28 oct | vie 23, lun 26, mié 28 | Cinta en C++ y estado de la máquina (marcha/parada). Cierre y release `sprint-02`. |

Riesgos:
- Primer proyecto C++ de Unreal: compilación con VS 2026 y la MSVC 14.51 ([`entorno.md`](../entorno.md)).
- Tamaño del primer commit del proyecto: comprobar antes del push que `.gitignore` deja fuera `Binaries/`, `Intermediate/`, `Saved/` y `DerivedDataCache/`, y que los `.uasset`/`.umap` van por LFS.
- Quest Link en el portátil con dos GPU: la aplicación tiene que ejecutarse en la RTX 4060, no en la Iris Xe.

## Bitácora

### 2026-10-15 (jueves)
- Replanificación tras el cierre del sprint 01. [ADR 0010](../decisiones/0010-prototipo-por-quest-link.md): el prototipo va por Quest Link con OpenXR, y el Meta XR Plugin y el APK pasan a después. [ADR 0011](../decisiones/0011-ritmo-de-trabajo.md): mínimo de 9 horas a la semana en tres sesiones fijas, con push al final de cada una.
- Planificación semana a semana, con un recorte previsto para cada semana, en [`planificacion.md`](../planificacion.md).

## Revisión

_Pendiente (al cerrar el sprint)._

## Retrospectiva

_Pendiente (al cerrar el sprint)._
