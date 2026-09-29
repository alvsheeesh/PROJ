# 0001 — Gestión del proyecto con Jira (Scrum)

- **Estado:** Aceptada
- **Fecha:** 2026-09-29

## Contexto

PROJ exige un tablero de gestión (Trello o Jira) compartido con el profesor, y el profesor quiere ver trabajo subido de forma periódica. El proyecto es individual y dura unos nueve meses, así que la planificación a largo plazo (hitos, épicas) pesa tanto como el día a día.

## Decisión

Usar Jira Cloud (plan Free) con plantilla **Scrum** de software y clave de proyecto `TAKT`:

- **Épicas** para los grandes bloques del juego, visibles en la *Timeline* como planificación del curso.
- **Sprints alineados con la cadencia de revisión del profesor** (2 semanas por defecto).
- Al cerrar cada sprint, **release en GitHub** (`sprint-NN`) con lo entregado: es la prueba del "trabajo subido cada x tiempo".
- **Seguridad como etiqueta (`seguridad`), no como épica**: es un requisito transversal que afecta a tareas de varias épicas.
- Integración **GitHub for Jira**: los commits que mencionan `TAKT-n` aparecen en la incidencia.

## Alternativas descartadas

- **Trello:** más rápido de montar y se comparte con un enlace público, pero no tiene backlog, sprints ni épicas de forma nativa, y la trazabilidad con los commits depende de power-ups. Ya se conoce, así que aporta menos aprendizaje.
- **Kanban en Jira:** menos ceremonia, pero sin sprints no hay cortes naturales que coincidan con las revisiones del profesor.
- **GitHub Projects:** todo en un único sitio y público junto al repositorio, pero el enunciado pide Trello o Jira.

## Consecuencias

- El plan Free no permite acceso anónimo: el profesor tiene que ser invitado como usuario (ocupa 1 de las 10 plazas gratuitas).
- Curva de aprendizaje mayor que Trello; se limita la configuración al mínimo (sin flujos personalizados).
