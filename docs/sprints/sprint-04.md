# Sprint 04 — Estabilización

- **Fechas:** 2026-11-12 → 2026-11-18
- **Objetivo:** el prototipo funciona por Quest Link desde una build de Windows, fuera del editor, sin funcionalidades nuevas, con el rendimiento medido en la build, la documentación al día y la release `prototipo`.
- **Release:** prototipo

## Planificación

Desde el 12 de noviembre el alcance está congelado ([planificación](../planificacion.md)): solo correcciones, rendimiento, build y documentación. Tareas en Jira: TAKT-36 (primera build de Windows).

| Semana | Sesiones | Objetivo |
|--------|----------|----------|
| 12–18 nov | jue 12 (en clase, sin gafas), mié 18 (con gafas) | Primera build de Windows (TAKT-36). Prueba de la build por Link y medida de rendimiento. Correcciones bloqueantes, documentación de entrega, cierre del sprint y release `prototipo`. |

Riesgos:
- Nunca se ha empaquetado el proyecto: la primera build puede fallar al cocinar o al arrancar fuera del editor. Por eso se hace el primer día del sprint.
- Solo quedan dos sesiones antes de la entrega (19 nov, 15:00) y las dos semanas anteriores se quedaron por debajo del mínimo de horas.
- La build solo se puede probar en VR en casa, el miércoles 18.

## Bitácora

### Correcciones del sprint 03
- **Horas del 11 de noviembre:** la sesión fue de 11:30 a 12:30 (1,0 h) y no hasta las 12:45 como pone la bitácora del sprint 03; los commits `69f4b4e` y `030ebd6` suman 1,2 h. Con las horas reales, la semana 4 se queda en 2,3 h y el sprint 03 en 5,9 h.
- **Tiempos de las averías:** el commit `69f4b4e` y la bitácora del 11 dicen que *Min Delay* y *Max Delay* se pusieron a 20 y 45 s, pero se habían quedado en 5 y 10 s. Se corrigen el 12 de noviembre, en TAKT-36.

### 2026-11-12 (jueves)
- Sesión en clase, sin gafas, desde las 16:30.
- El mapa por defecto del juego y del editor era `L_XRTemplate`, el de la plantilla: la build habría arrancado en ese nivel. Pasa a ser `L_Dev_Cinta` (*Configuración del proyecto → Mapas y modos*).
- *Min Delay* y *Max Delay* de «Averías aleatorias» a 20 y 45 s (corrección de arriba).
- TAKT-36: primera build de Windows (Win64, Development) con `RunUAT BuildCookRun`, archivada en `E:\TAKT_Builds`, fuera del repositorio. Comando en [`entorno.md`](../entorno.md).
- Resultado: **`BUILD SUCCESSFUL` en 36 minutos**, con 674 paquetes cocinados y sin errores. Casi todo el tiempo se va en compilar los shaders por primera vez (los del motor y los de los materiales); las siguientes builds deberían ser más rápidas. Solo hay dos avisos, de extensiones de OpenXR que no se usan (seguimiento de la mirada y mandos de PICO).
- El ejecutable (`E:\TAKT_Builds\Windows\TAKT.exe`) arranca en `L_Dev_Cinta` con la línea en marcha (luz verde). Sin gafas la cámara se queda a ras de suelo y no se puede interactuar, que es lo esperado: la prueba de verdad es por Link el miércoles 18.
- Problemas encontrados:
  - La build crea `TAKT/Build/Windows/`, que salía como fichero nuevo en Git: las reglas de `Build/` del `.gitignore` llevaban una barra en medio y solo valían en la raíz del repositorio. Pasan a ser `**/Build/...`.
  - La escena se ve muy oscura, salvo lo que ilumina la luz de estado. No es cosa de la build: ya se veía así en el *Play* del editor el 5 de noviembre. Se revisa con gafas el 18.
- Queda para el miércoles 18, con gafas: probar la build por Link, medir con `stat unit` si llega a 72 fps ([ADR 0015](../decisiones/0015-rendimiento-por-link.md)) y mirar la iluminación de la escena.
