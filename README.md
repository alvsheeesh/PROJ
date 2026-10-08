# TAKT

Videojuego de realidad virtual de oleadas ambientado en una línea de manipulados: el jugador tiene que mantener la máquina en marcha reparando averías con las manos, cada vez más rápido.

Proyecto final (PROJ) de 2º de DAM — Álvaro, curso 2026-2027.

## Stack

- **Motor:** Unreal Engine 5.8 (C++ + Blueprints) con el Meta XR Plugin v207
- **Plataforma:** Meta Quest 2 en modo autónomo (Android)
- **Gestión:** Jira (Scrum) — _enlace pendiente_
- **Control de versiones:** Git + Git LFS en GitHub

## Estructura del repositorio

```
TAKT/             Proyecto de Unreal (TAKT.uproject, Config/, Content/, Source/)
docs/             Documentación del proyecto
docs/decisiones/  Registro de decisiones de arquitectura (ADR)
docs/sprints/     Bitácora de cada sprint (planificación, avances, revisión, retro)
docs/planificacion.md  Hitos y calendario de sprints
docs/entorno.md   Entorno de desarrollo: versiones y pasos de instalación
CREDITS.md        Assets de terceros y sus licencias
```

## Puesta en marcha

Requisitos: Unreal Engine 5.8 con soporte para Android, Visual Studio 2026 con las cargas de trabajo de C++ para escritorio y para juegos, el Android SDK y el NDK que pide el motor, JDK 21 y Git con [Git LFS](https://git-lfs.com). Versiones exactas y pasos en [`docs/entorno.md`](docs/entorno.md).

```bash
git lfs install          # una sola vez por máquina
git clone <url-del-repo>
```

Después: clic derecho sobre `TAKT/TAKT.uproject` → *Generate Visual Studio project files* y abrir el proyecto.

## Forma de trabajo

- Sprints en Jira. Al cerrar cada sprint, `develop` se fusiona en `main` y se publica una *release* en GitHub (`sprint-01`, `sprint-02`…) con lo entregado.

### Ramas

```
main      ← solo lo entregado al cerrar cada sprint (release sprint-NN)
└─ develop    ← integración: aquí se fusiona cada tarea terminada
   └─ tipo/TAKT-NN-descripcion   ← una rama por tarea de Jira
```

- Las ramas de trabajo salen de `develop` y vuelven a `develop` con un *pull request*. Nunca se hacen commits directos a `main` ni a `develop`.
- Tipos de rama: `feature` (funcionalidad), `fix` (corrección), `docs` (documentación) y `chore` (configuración y mantenimiento). Ejemplo: `feature/TAKT-17-proyecto-vr`.

### Commits

El resumen empieza por la clave de Jira, para que el commit quede enlazado en el tablero. La descripción indica siempre las horas dedicadas y el impacto:

```
TAKT-17 Crea el proyecto TAKT desde la plantilla VR

Horas: 0.5h
Impacto: Medio
```

Escala de impacto provisional: **Bajo**, **Medio** o **Alto** (pendiente de confirmar con el profesor).

## Planificación y avances

- **Prototipo:** entrega el 19 de noviembre de 2026 ([alcance](docs/decisiones/0006-alcance-del-prototipo.md) · [calendario](docs/planificacion.md)).
- **Bitácora:** [`docs/sprints/`](docs/sprints/).

## Decisiones

Ver [`docs/decisiones/`](docs/decisiones/).
