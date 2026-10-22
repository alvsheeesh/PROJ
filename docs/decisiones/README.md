# Registro de decisiones

Cada decisión relevante de arquitectura o de proceso se documenta en un fichero numerado (formato ADR ligero): contexto, decisión, alternativas descartadas y consecuencias. Una decisión no se edita cuando se cambia de idea: se crea una nueva que la sustituye.

| Nº | Decisión | Estado | Fecha |
|----|----------|--------|-------|
| [0001](0001-gestion-con-jira.md) | Gestión del proyecto con Jira (Scrum) | Aceptada | 2026-09-29 |
| [0002](0002-github-con-git-lfs.md) | Repositorio público en GitHub con Git LFS | Aceptada | 2026-09-29 |
| [0003](0003-politica-de-assets-repo-publico.md) | Política de assets en un repositorio público | Aceptada | 2026-09-29 |
| [0004](0004-unreal-5-7-launcher-meta-xr.md) | Unreal Engine 5.7 del Launcher con el Meta XR Plugin | Sustituida por 0005 | 2026-09-29 |
| [0005](0005-unreal-5-8-meta-xr-v207.md) | Unreal Engine 5.8 del Launcher con el Meta XR Plugin v207 | Aceptada (plugin aplazado por 0010) | 2026-10-01 |
| [0006](0006-alcance-del-prototipo.md) | Alcance del prototipo (19 nov 2026) | Aceptada | 2026-10-01 |
| [0007](0007-bitacora-por-sprint.md) | Documentación de avances: bitácora por sprint | Aceptada | 2026-10-01 |
| [0008](0008-toolchain-android-sin-android-studio.md) | Toolchain de Android con las command-line tools, sin Android Studio | Aplazada por 0010 | 2026-10-01 |
| [0009](0009-flujo-de-git.md) | Flujo de Git: ramas, pull requests y formato de los commits | Aceptada | 2026-10-08 |
| [0010](0010-prototipo-por-quest-link.md) | Prototipo por Quest Link con OpenXR | Aceptada | 2026-10-15 |
| [0011](0011-ritmo-de-trabajo.md) | Ritmo de trabajo: mínimo semanal y push por sesión | Sustituida por 0013 | 2026-10-15 |
| [0012](0012-cinta-por-fisica.md) | Cinta transportadora por física | Aceptada | 2026-10-21 |
| [0013](0013-ritmo-miercoles-y-sesion-elegida.md) | Ritmo de trabajo: miércoles fijo y una segunda sesión elegida cada semana | Aceptada | 2026-10-22 |

## Plantilla

```markdown
# NNNN — Título

- **Estado:** Propuesta | Aceptada | Sustituida por NNNN | Aplazada por NNNN
- **Fecha:** AAAA-MM-DD

## Contexto
## Decisión
## Alternativas descartadas
## Consecuencias
```
