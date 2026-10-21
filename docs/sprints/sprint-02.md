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

### 2026-10-16 (viernes) y 2026-10-19 (lunes)
- Sesiones no hechas. No hay trabajo de esos días.

### 2026-10-21 (miércoles, tarde)
- TAKT-24: decidida la cinta por física ([ADR 0012](../decisiones/0012-cinta-por-fisica.md)). Descartados el recorrido por spline sin física y la cinta solo visual.
- Primera clase en C++: `AConveyorBelt` en `TAKT/Source/TAKT/Line/`. Con ella el proyecto pasa a C++: módulo `TAKT` y sus *targets* de juego y de editor. La cinta arrastra los cuerpos con física que tiene encima, se configura con `Speed` y obedece a `SetRunning`; parada, frena lo que lleva. Tiene un botón `ToggleRunning` en el panel de detalles para probarla sin el estado de la máquina.
- Primera compilación C++ con VS 2026 y MSVC 14.51: a la primera, sin avisos en el código del proyecto. El editor carga el módulo `TAKT`.
- Cinta probada en el nivel de pruebas `TAKT/Maps/L_Dev_Cinta` (copia del nivel de la plantilla): los cubos de la plantilla avanzan hasta el final y caen, y `ToggleRunning` la para y la arranca. Ese nivel no tiene la iluminación precalculada (el `_BuiltData` no se versiona), así que el cielo sale negro y el editor pide reconstruir la iluminación. No afecta a las pruebas.
- TAKT-21 por Link ✅: con Meta Horizon Link como runtime de OpenXR y *Orígenes desconocidos* activado en la app de Link (si no, Link no deja abrir el editor). Si las gafas no están en Link cuando arranca el editor, *VR Preview* sale en gris. Se coge un cubo con el grip y se deja en la cinta, que lo transporta. **Al cogerlo de la cinta en marcha, la cinta no tira de él**: queda confirmado el supuesto de la [ADR 0012](../decisiones/0012-cinta-por-fisica.md).
- Problemas encontrados:
  - **Rendimiento: unos 25-36 fps por Link** (`stat fps`), muy por debajo de los 72-90 Hz de las Quest 2. La plantilla trae activados ray tracing, Lumen, sombras virtuales y Substrate. Hay que medir con `stat unit` antes de recortar nada.
  - **Soltar con el grip cuesta**: el cubo no se suelta cuando se quiere. Es el agarre de la plantilla, no la cinta. Se tendrá en cuenta en la interacción propia de la semana 3.

### Control de la semana 1 (15–21 oct)
- **Objetivo:** proyecto `TAKT/` en el repositorio con LFS ✅ (15 oct; pasa a C++ hoy con la cinta). Funciona por Link y se coge un objeto con los mandos ✅ (21 oct, por la tarde). **Objetivo cumplido**, con dos de las tres sesiones perdidas.
- **Sesiones:** 2 de 3 (15 y 21 oct); las del 16 y el 19 no se hicieron.
- **Horas:** 4.9 h: 3.2 h el 15 oct (0.7 h según `git log` más 2.5 h de `5a66f58` y `9396963`, que no cuentan porque los trailers llevan sangrado) y 1.7 h el 21 oct. Por debajo del mínimo de 9 h.
- **Recorte:** la semana 1 no tiene recorte previsto porque es la base de todo lo demás ([planificación](../planificacion.md)). Lo que falte se recupera el jueves 22 o el fin de semana.
- **Semana 2:** la cinta se ha adelantado a hoy, así que las sesiones del 23, 26 y 28 quedan para el rendimiento por Link (TAKT-26, que entra en el sprint; ahora es lo más urgente: por debajo de 72 fps la prueba en VR marea y no es fiable), TAKT-25 (estado de la máquina) y el cierre del sprint.

## Revisión

_Pendiente (al cerrar el sprint)._

## Retrospectiva

_Pendiente (al cerrar el sprint)._
