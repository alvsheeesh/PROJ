# 0009 — Flujo de Git: ramas, pull requests y formato de los commits

- **Estado:** Aceptada
- **Fecha:** 2026-10-08

## Contexto

El profesor sigue la actividad del repositorio (commits, pushes, ramas) con una herramienta propia y ha fijado dos normas:

1. No se trabaja directamente en `main`: el flujo es `main` → `develop` → una rama por tarea, que vuelve a `develop` al terminarla.
2. La descripción de cada commit indica las **horas dedicadas** (`Horas: 0.1h`) y el **impacto** (`Impacto: Sugerencia`). No ha definido ninguna escala de impacto.

El primer commit con este formato (`c7e36ba`, TAKT-12) usó una escala provisional de tres niveles (Bajo / Medio / Alto) con `Impacto: Medio`. Ese commit ya está en `main` y no se reescribe.

## Decisión

**Ramas**

- `main` solo recibe `develop` al cerrar cada sprint, con un *pull request* y la release `sprint-NN`.
- `develop` es la rama de integración. Las ramas de trabajo salen de `develop` y vuelven con un *pull request*.
- Una rama por tarea de Jira: `tipo/TAKT-NN-descripcion`, con tipo `feature`, `fix`, `docs` o `chore`. La clave hace que GitHub for Jira enlace la rama, sus commits y el PR a la tarea.
- Los PR se fusionan con **merge commit**. *Squash* y *rebase* quedan desactivados en los ajustes del repositorio.
- `main` y `develop` se protegen con un *ruleset* de GitHub: sin pushes directos, todo por PR.

**Commits**

- Resumen: `TAKT-NN Verbo en presente…` (la clave al principio enlaza el commit en Jira).
- Al final de la descripción, separados por una línea en blanco, dos *trailers* de Git: `Horas:` e `Impacto:`.
- Escala de impacto de cinco niveles: **Sugerencia**, **Menor**, **Medio**, **Mayor** y **Crítico**. Se mantiene *Medio* para que el commit `c7e36ba` siga siendo válido. Definiciones y ejemplos en [`CONTRIBUTING.md`](../../CONTRIBUTING.md).
- Las horas son tiempo real (incluido investigar, revisar y probar), con una décima de hora de precisión. Si una sesión acaba en varios commits, sus horas suman el tiempo real de la sesión.
- Un hook `commit-msg` versionado en `.githooks/` rechaza el commit si falta la clave de Jira, las horas o el impacto, o si el impacto no está en la escala.

## Alternativas descartadas

- **Commits directos a `main`:** es lo que el profesor ha pedido evitar.
- **Squash merge:** deja un historial más limpio, pero junta los commits de la rama en uno solo y se pierden las horas y el impacto de cada uno.
- **Fusionar en local con GitHub Desktop:** cuando puede, Git hace *fast-forward* y la rama no deja rastro en el historial; además, no queda ningún PR que revisar.
- **Git Flow completo (ramas `release/` y `hotfix/`):** ceremonia pensada para equipos con varias versiones en paralelo. Con una persona y un sprint cada dos semanas, `develop` → `main` por PR basta.
- **Conventional Commits (`feat(TAKT-23): …`):** el tipo ya va en el nombre de la rama, y la clave de Jira al principio es lo que necesita la integración. Repetirlo en cada commit no aporta nada.
- **Escala de tres niveles (Bajo / Medio / Alto):** no distingue un retoque de documentación de una funcionalidad del juego, ni una funcionalidad de un cambio de arquitectura.
- **Registrar las horas solo en Jira (*worklog*):** el profesor las pide en el commit. Llevarlas en los dos sitios duplicaría el trabajo.

## Consecuencias

- Cada clon del repositorio tiene que activar el hook una vez: `git config core.hooksPath .githooks`.
- El hook no se ejecuta en los merge commits ni en los PR que se fusionan desde la web de GitHub; esos no llevan horas ni impacto.
- Las horas de un sprint salen de `git log` (comando en `CONTRIBUTING.md`), sin apuntarlas a mano en la bitácora.
