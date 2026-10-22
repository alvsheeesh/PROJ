# 0013 — Ritmo de trabajo: miércoles fijo y una segunda sesión elegida cada semana

- **Estado:** Aceptada
- **Fecha:** 2026-10-22
- **Sustituye a:** [0011](0011-ritmo-de-trabajo.md)
- **Tarea:** TAKT-27

## Contexto

La [ADR 0011](0011-ritmo-de-trabajo.md) fijó un mínimo de 9 horas a la semana en tres sesiones fijas (lunes, miércoles y viernes por la mañana). En su primera semana (15–21 oct) se hicieron 2 de las 3 sesiones y 4.9 h. Las sesiones perdidas no se pueden prever de una semana para otra: dependen de los deberes del resto de asignaturas y de las prácticas.

Lo único que se puede garantizar todas las semanas es el miércoles por la mañana. Hasta el cierre del prototipo (18 de noviembre) quedan 4 semanas. El plan de la ADR 0011 contaba con unas 36 h para ese tramo y no tenía margen.

## Decisión

- **Miércoles por la mañana, fijo, de 4 horas o más.** Es la sesión que no se mueve. Cierra la semana (que va de jueves a miércoles) con el control semanal.
- **Una segunda sesión por semana, elegida en el control del miércoles** para la semana siguiente, cuando ya se conocen los deberes. Una vez elegida, es tan fija como el miércoles. Si se pierde, se recupera antes del miércoles siguiente.
- **Mínimo de 6 horas a la semana** entre las dos sesiones. Las horas de más son margen, no plan.
- **Los recortes previstos se aplican desde ya** en la [planificación](../planificacion.md), en lugar de esperar a no llegar: reparar la avería con una palanca, un indicador de estado con una luz de color y nada de APK autónomo.
- Se mantiene de la ADR 0011: cada sesión acaba con push, commits por paso con sentido y horas reales ([ADR 0009](0009-flujo-de-git.md)), y control semanal el miércoles (horas con `git log`, línea en la bitácora y, si el objetivo no se cumple, el recorte de esa semana).

## Alternativas descartadas

- **Mantener la ADR 0011 (lunes, miércoles y viernes fijos):** la primera semana ya mostró que no se sostiene, y fingir que sí solo retrasa el momento de recortar.
- **Solo el miércoles fijo y el resto cuando se pueda:** quedan garantizadas unas 16 h hasta el prototipo, menos de la mitad del plan. Habría que recortar el alcance de la [ADR 0006](0006-alcance-del-prototipo.md) mucho más allá de los recortes previstos, por ejemplo con una avería sin interacción física.
- **9 horas a la semana con el miércoles como ancla y el resto libre:** se mantiene el alcance, pero es la alternativa «horas sin días fijos» que ya descartó la ADR 0011: las horas se dejan para el final de la semana, y tanto el sprint 1 como la semana 1 lo confirman.
- **Elegir la segunda sesión cada lunes:** el lunes cae a mitad de la semana de trabajo y ya es tarde para recuperar una sesión perdida. El miércoles coincide con el control y con el cierre de la semana.

## Consecuencias

- El prototipo cuenta con unas **24 h de mínimo** (4 semanas × 6 h), frente a las 36 h de la ADR 0011. Con los recortes ya aplicados, el alcance cabe justo. Si una semana se queda por debajo del mínimo, en el control se decide qué más se recorta, en lugar de arrastrarlo.
- La interacción física para reparar la avería sigue dentro del alcance de la ADR 0006: es una palanca, la versión mínima que ya se había previsto.
- Cada control del miércoles tiene un punto más: fijar el día de la segunda sesión de la semana siguiente y apuntarlo en la bitácora.
- La sesión del miércoles cae justo antes de la clase de PROJ del jueves, así que lo que se enseña a Pol siempre está subido.
