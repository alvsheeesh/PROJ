# 0006 — Alcance del prototipo (entrega del 19 de noviembre de 2026)

- **Estado:** Aceptada
- **Fecha:** 2026-10-01

## Contexto

La entrega del prototipo es el **19 de noviembre de 2026 a las 15:00**: unas 7 semanas desde el arranque (1 de octubre). Al empezar, Unreal no está instalado y el pipeline hacia las Quest 2 está sin probar, que es el mayor riesgo técnico del proyecto. El profesor ha dicho que le interesa la programación que hay detrás, no el apartado gráfico.

## Decisión

El prototipo es una **base técnica con interacción**, no un vertical slice jugable:

1. TAKT se ejecuta en las Quest 2 en modo autónomo.
2. El jugador coge objetos con las manos virtuales y los coloca en una cinta transportadora en marcha. **La entrada es con los mandos de Quest 2**: es más sencillo, más compatible y más fiable al agarrar con precisión. El seguimiento de manos se deja para después del prototipo.
3. **Una avería de principio a fin:** aparece, la máquina se para, el jugador la repara con una interacción física y la máquina vuelve a funcionar.
4. Una arquitectura en C++ pensada para crecer: estado de la máquina, componente de avería genérico y Blueprints solo para configurar contenido.

**Fuera del prototipo:** oleadas y progresión, una segunda avería, UI más allá de un indicador mínimo de estado, audio y arte propios, y seguimiento de manos sin mandos.

**Cierre real:** miércoles 18 de noviembre. El 19 es jueves y la clase empieza a las 15:00, así que no se trabaja en la entrega ese mismo día.

## Alternativas descartadas

- **Vertical slice jugable (oleadas y 1-2 averías):** queda mejor, pero con el pipeline sin probar y 7 semanas a tiempo parcial es desproporcionado. Un retraso en el sprint 1 se lo comería entero.
- **Solo el pipeline más coger un objeto:** demasiado poco. No enseña la lógica de la máquina ni de las averías, que es justo la programación que quiere ver el profesor.

## Consecuencias

- Las épicas *Oleadas y progresión* y la mayor parte de *UI/UX en VR* pasan a después del prototipo.
- La avería del prototipo se diseña como el primer caso de un sistema genérico, para que añadir averías después sea crear datos y no reescribir código.
- **Interacción separada de la fuente de entrada:** los objetos que se pueden coger y las piezas que se reparan reaccionan a eventos genéricos (agarrar, soltar, accionar), no a botones concretos del mando. Así, el seguimiento de manos se podrá añadir después como otra fuente de entrada sin tocar la lógica de la línea ni de las averías.
- El calendario de sprints está en [`docs/planificacion.md`](../planificacion.md).
