# Sprint 02 — Proyecto y línea

- **Fechas:** 2026-10-15 → 2026-10-28
- **Objetivo:** TAKT corre por Quest Link desde el repositorio, se coge un objeto con los mandos y un tramo de cinta en C++ transporta objetos, con el estado de la máquina (marcha/parada).
- **Release:** sprint-02

## Planificación

Tareas en Jira: TAKT-17 (proyecto con LFS), TAKT-21 (coger un cubo con el mando) y TAKT-22 (GitHub for Jira) en la primera semana; TAKT-24 (cinta) y TAKT-25 (estado de la máquina) en la segunda.

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

### 2026-10-15 (jueves, tarde)
- Jira al día: sprint 01 cerrado (TAKT-12, 13, 14, 16 y 23 finalizadas; TAKT-15, 18, 19 y 20 al backlog por la ADR 0010) y sprint 02 empezado.
- TAKT-17: proyecto creado con la plantilla *Virtual Reality* de UE 5.8 en `TAKT/` (estructura de la [ADR 0002](../decisiones/0002-github-con-git-lfs.md)). En 5.8 esta plantilla es solo Blueprint y el asistente no deja elegir C++: el proyecto pasa a C++ al añadir la primera clase, que será la de la cinta (TAKT-24), en lugar de crear ahora una clase vacía.
- Primer commit del proyecto: 189 assets de la plantilla por LFS (unos 55 MB), configuración y `.uproject`. `Intermediate/`, `Saved/` y `DerivedDataCache/` quedan fuera por el `.gitignore`.

## Revisión

_Pendiente (al cerrar el sprint)._

## Retrospectiva

_Pendiente (al cerrar el sprint)._
