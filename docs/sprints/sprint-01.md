# Sprint 01 — Pipeline Quest 2

- **Fechas:** 2026-10-01 → 2026-10-14
- **Objetivo:** TAKT se ejecuta en las Quest 2 en modo autónomo y se coge un objeto con los mandos.
- **Release:** sprint-01

## Planificación

Tareas en Jira: KAN-12 a KAN-22 (épica *Setup y pipeline Quest 2*).

Riesgos:
- Instalar UE 5.8 y configurar la toolchain de Android (SDK, NDK, JDK) en las versiones que pide el motor.
- Modo desarrollador en las Quest 2 (requiere una organización de desarrollador de Meta).
- Soporte real de la Quest 2 con UE 5.8 y el Meta XR Plugin v207 ([ADR 0005](../decisiones/0005-unreal-5-8-meta-xr-v207.md)).

Control intermedio: **8 de octubre**. Si no hay build vacía en el visor, se aplica el plan B de la ADR 0005.

## Bitácora

### 2026-10-01 (jueves)
- Arranque del desarrollo. El repositorio local pasa a `E:\PROJ`: se clona de nuevo desde GitHub en lugar de mover la carpeta antigua.
- [ADR 0005](../decisiones/0005-unreal-5-8-meta-xr-v207.md): UE 5.8 con el Meta XR Plugin v207. Sustituye a la 0004, porque el plugin ya da soporte a 5.8 desde el 23 de septiembre.
- [ADR 0006](../decisiones/0006-alcance-del-prototipo.md): el prototipo del 19 de noviembre es una base técnica con interacción. [ADR 0007](../decisiones/0007-bitacora-por-sprint.md): documentación con esta bitácora.
- Calendario de sprints hasta el prototipo en [`planificacion.md`](../planificacion.md).
- Interacción del prototipo con los mandos; el seguimiento de manos queda para después (añadido a la ADR 0006).
- Clave de Jira cambiada de KAN a TAKT.
- Inventario del PC antes de instalar: sin Visual Studio ni Android SDK; `JAVA_HOME` apunta a un JDK 25 que se usa en clase; **C: solo tiene 21 GB libres**, así que todo el entorno va a E:; 14 GB de RAM.
- Instalados UE 5.8.3 (en `E:\Epic Games`) y JDK 21 (en `E:\JDK21`). Visual Studio 2026 ya estaba instalado en E:.
- MSVC: la 14.50.35717 que trae VS 2026 está **vetada** en el `Windows_SDK.json` de 5.8.3. UnrealBuildTool la descarta y usa la 14.51; no se fija la versión. Detalle en [`entorno.md`](../entorno.md).
- [ADR 0008](../decisiones/0008-toolchain-android-sin-android-studio.md): Android con las command-line tools, sin Android Studio. Los paquetes salen de `Android_SDK.json` (android-36, NDK r27c), no de la web de Epic (SDK 35).
- Siguiente: instalar el SDK de Android con `sdkmanager` y comprobar `adb`; crear el proyecto TAKT (TAKT-17).

### 2026-10-08 (jueves)
- Normas del profesor para el repositorio: flujo `main` → `develop` → ramas de trabajo con *pull request*, y descripción de cada commit con las horas y el impacto. Están en la sección *Forma de trabajo* del README.
- Control del plan B del motor ([ADR 0005](../decisiones/0005-unreal-5-8-meta-xr-v207.md)): todavía no hay build en las Quest, pero no por un fallo de UE 5.8 ni del plugin, sino porque aún no se había creado el proyecto. **No se activa el plan B.**
- Android deja de bloquear: el proyecto se crea con la plantilla *Virtual Reality* (OpenXR) y se prueba por Quest Link, con el juego ejecutándose en el PC. El SDK de Android solo hace falta para empaquetar el APK (TAKT-20).
- Pendiente de confirmar con el profesor si el prototipo se enseña por Link o en las Quest en modo autónomo. Según la respuesta, se revisan las ADR 0005, 0006 y 0008.
- Primer intento de proyecto creado como Blueprint y fuera de `TAKT/`; se rehace como proyecto C++ en `E:\PROJ\TAKT`.

## Revisión

_Pendiente (al cerrar el sprint)._

## Retrospectiva

_Pendiente (al cerrar el sprint)._
