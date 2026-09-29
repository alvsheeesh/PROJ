# TAKT

Videojuego de realidad virtual de oleadas ambientado en una línea de manipulados: el jugador tiene que mantener la máquina en marcha reparando averías con las manos, cada vez más rápido.

Proyecto final (PROJ) de 2º de DAM — Álvaro, curso 2026-2027.

## Stack

- **Motor:** Unreal Engine 5.7 (C++ + Blueprints) con el Meta XR Plugin
- **Plataforma:** Meta Quest 2 en modo autónomo (Android)
- **Gestión:** Jira (Scrum) — _enlace pendiente_
- **Control de versiones:** Git + Git LFS en GitHub

## Estructura del repositorio

```
TAKT/             Proyecto de Unreal (TAKT.uproject, Config/, Content/, Source/)
docs/             Documentación del proyecto
docs/decisiones/  Registro de decisiones de arquitectura (ADR)
CREDITS.md        Assets de terceros y sus licencias
```

## Puesta en marcha

Requisitos: Unreal Engine 5.7 con soporte para Android, Visual Studio 2022 con la carga de trabajo de desarrollo de juegos con C++, y Git con [Git LFS](https://git-lfs.com).

```bash
git lfs install          # una sola vez por máquina
git clone <url-del-repo>
```

Después: clic derecho sobre `TAKT/TAKT.uproject` → *Generate Visual Studio project files* y abrir el proyecto.

## Forma de trabajo

- Sprints en Jira. Al cerrar cada sprint se publica una *release* en GitHub (`sprint-01`, `sprint-02`…) con lo entregado.
- Cada commit referencia la incidencia de Jira que resuelve, para que quede enlazado en el tablero:

```
TAKT-12 Añade el componente de avería al rodillo
```

## Decisiones

Ver [`docs/decisiones/`](docs/decisiones/).
