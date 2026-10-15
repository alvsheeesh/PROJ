# Cómo se trabaja en este repositorio

Normas del flujo de Git de TAKT. El porqué de cada una está en la [ADR 0009](docs/decisiones/0009-flujo-de-git.md).

## Ramas

```
main      ← solo lo entregado al cerrar cada sprint (release sprint-NN)
└─ develop    ← integración: aquí se fusiona cada tarea terminada
   └─ tipo/TAKT-NN-descripcion   ← una rama por tarea de Jira
```

- Tipos de rama: `feature` (funcionalidad), `fix` (corrección), `docs` (documentación) y `chore` (configuración y mantenimiento). Ejemplo: `feature/TAKT-17-proyecto-vr`.
- Nunca se hacen commits directos a `main` ni a `develop`.

## Ciclo de una tarea

1. En GitHub Desktop, con `develop` actualizada (*Fetch origin* → *Pull*): *Branch → New branch* a partir de `develop`.
2. Commits pequeños, uno por cambio con sentido, no uno por sesión. GitHub Desktop deja marcar qué ficheros (y qué líneas) entran en cada commit.
3. *Push* al acabar cada sesión, aunque la tarea no esté terminada.
4. Al terminar la tarea: *Create Pull Request* con base `develop` y fusionar en GitHub con **Create a merge commit**.
5. Al cerrar el sprint: PR de `develop` a `main`, merge commit y release `sprint-NN` enlazando a la bitácora.

## Mensaje de commit

En GitHub Desktop, *Summary* es la primera línea y *Description* el resto. Las líneas de horas e impacto van al final, después de una línea en blanco:

```
TAKT-23 Añade la máquina de estados de la cinta

UConveyorComponent con los estados Parada, EnMarcha y Averiada.
La avería se dispara desde un evento genérico (ADR 0006).

Horas: 1.5h
Impacto: Mayor
```

- **Resumen:** la clave de Jira y un verbo en presente.
- **Horas:** tiempo real dedicado, incluido investigar, revisar y probar. En horas, con punto decimal y una décima de precisión (`0.1h` ≈ 6-10 min, `0.5h`, `2h`). Si una sesión se reparte en varios commits, las horas de esos commits suman el tiempo real de la sesión.
- **Impacto:** uno de los cinco niveles de la escala.

### Escala de impacto

| Impacto | Cuándo | Ejemplos |
|---|---|---|
| **Sugerencia** | No cambia el comportamiento ni el contenido de fondo | erratas, formato, comentarios, retoques de documentación |
| **Menor** | Cambio acotado, sin efecto en el juego ni en la arquitectura | refactor pequeño, ajuste de configuración o de un valor, script de apoyo |
| **Medio** | Trabajo de peso en un área, sin cambiar el comportamiento del juego ni la arquitectura | ADR o planificación, toolchain, herramienta de desarrollo, tests |
| **Mayor** | Funcionalidad nueva o cambio de comportamiento en un sistema del juego | coger objetos, estados de la cinta, una avería |
| **Crítico** | Afecta a varios sistemas o a la arquitectura, o desbloquea o rompe la build | base de la interacción, cambio de versión del motor o del plugin, arreglar la build en las Quest |

## Hook de comprobación

`.githooks/commit-msg` rechaza el commit si el resumen no empieza por `TAKT-NN`, si falta `Horas:` o `Impacto:`, o si el impacto no está en la escala. Se activa una vez por clon:

```bash
git config core.hooksPath .githooks
```

No se aplica a los merge commits.

## Horas por sprint

Desde Git Bash, en la raíz del repositorio (ajustando las fechas del sprint):

```bash
git log --no-merges --since=2026-10-01 --until=2026-10-15 \
  --format='%(trailers:key=Horas,valueonly,separator=)' \
  | sed 's/h$//' | awk '{s+=$1} END {print s " h"}'
```
