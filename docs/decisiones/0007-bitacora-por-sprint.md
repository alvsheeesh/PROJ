# 0007 — Documentación de los avances: bitácora por sprint

- **Estado:** Aceptada
- **Fecha:** 2026-10-01

## Contexto

Hay que ir documentando los avances en el repositorio: el profesor quiere ver trabajo periódico y, al final, hay que redactar la memoria del TFC. El tiempo es limitado, así que la documentación no puede costar más que el trabajo que describe.

## Decisión

- Un fichero por sprint en `docs/sprints/sprint-NN.md` con cuatro apartados: **planificación** (objetivo y tareas), **bitácora** (una entrada corta por cada sesión de trabajo), **revisión** (qué se entregó y qué no) y **retrospectiva**.
- Al cerrar cada sprint, la release `sprint-NN` de GitHub enlaza a su bitácora.
- Las decisiones con alternativas van a `docs/decisiones/` (ADR), no a la bitácora. La bitácora solo las enlaza.

## Alternativas descartadas

- **Diario por sesión en ficheros separados:** más detalle, pero cuesta más de mantener y hay que reagrupar todo para la memoria.
- **Solo Jira y las releases:** no deja rastro en el repositorio de los problemas encontrados ni de cómo se resolvieron, que es justo lo que alimenta la memoria.

## Consecuencias

- Cada sesión acaba con 3-5 líneas en la bitácora del sprint en curso.
- La memoria del TFC se puede montar casi directamente a partir de las bitácoras y las ADR.
