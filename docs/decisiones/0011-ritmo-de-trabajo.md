# 0011 — Ritmo de trabajo: mínimo semanal y push por sesión

- **Estado:** Sustituida por [0013](0013-ritmo-miercoles-y-sesion-elegida.md)
- **Fecha:** 2026-10-15

## Contexto

En el sprint 1 no se fijó cuándo se trabajaba: hubo dos días de trabajo (1 y 8 de octubre), un solo commit de trabajo y una semana sin actividad en el repositorio. El profesor sigue la actividad del repositorio y pide trabajo subido de forma periódica.

El proyecto se hace en paralelo a las prácticas y al resto de asignaturas, así que el tiempo tiene que estar reservado de antemano.

## Decisión

- **Mínimo de 9 horas a la semana**, en tres sesiones fijas: **lunes, miércoles y viernes por la mañana** (unas 3 horas cada una).
- **Cada sesión acaba con push**, aunque la tarea no esté terminada. La actividad del repositorio refleja entonces los días en que se trabaja de verdad.
- **Commits por paso con sentido**, no uno por sesión, con las horas reales ([ADR 0009](0009-flujo-de-git.md)).
- **Una sesión que se pierde se recupera la misma semana** (otro día, o martes o jueves antes de clase). El mínimo es semanal.
- Cada semana tiene un **objetivo verificable** y un **recorte previsto** en [`planificacion.md`](../planificacion.md). Las semanas van de jueves a miércoles, para que la última sesión de cada semana caiga antes de la clase del jueves.
- **Control semanal el miércoles:** horas de la semana con `git log` ([`CONTRIBUTING.md`](../../CONTRIBUTING.md)) y una línea en la bitácora. Si el objetivo de la semana no se cumple, se aplica el recorte previsto en vez de alargar el plan.

## Alternativas descartadas

- **Commits automáticos o programados para tener actividad:** cada commit lleva las horas dedicadas, así que unos commits vacíos se notarían enseguida y quitarían credibilidad al historial entero.
- **Trabajar "cuando haya hueco", sin días fijos:** es lo que pasó en el sprint 1.
- **Un mínimo de horas sin días fijos:** las horas se acaban dejando para el final de la semana o del sprint.
- **Dos sesiones largas en lugar de tres:** menos cambios de contexto, pero más días seguidos sin actividad y peor cuando se pierde una.

## Consecuencias

- Al prototipo le llegan unas 45 horas (5 semanas × 9 h). El alcance de la [ADR 0006](0006-alcance-del-prototipo.md) cabe justo, sin margen para imprevistos. Por eso cada semana tiene un recorte previsto.
- Las horas de más (martes, jueves y fines de semana) son margen, no plan.
