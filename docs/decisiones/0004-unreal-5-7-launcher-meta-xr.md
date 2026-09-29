# 0004 — Unreal Engine 5.7 del Epic Launcher con el Meta XR Plugin

- **Estado:** Propuesta (confirmar al instalar)
- **Fecha:** 2026-09-29

## Contexto

Hay que instalar Unreal desde cero. El juego se ejecuta en unas Meta Quest 2 en modo autónomo, así que la versión del motor la condiciona la del Meta XR Plugin, no la última que haya publicado Epic. A finales de septiembre de 2026 hay informes de que el plugin de Meta está compilado para UE 5.7 y falla al cargar módulos en UE 5.8.

## Decisión

- **UE 5.7 desde el Epic Games Launcher** con el componente de plataforma Android.
- **Meta XR Plugin** en la versión que declare compatibilidad con 5.7.
- **Congelar la versión** durante todo el curso: no actualizar el motor salvo bloqueo grave (y con una nueva ADR).
- Primer sprint dedicado a quitar riesgo: proyecto vacío ejecutándose en las Quest 2 antes de escribir lógica de juego.

## Alternativas descartadas

- **UE 5.8 (la más reciente):** incompatibilidades reportadas con el plugin de Meta.
- **Fork Oculus-VR de Unreal (GitHub de Meta):** más optimizaciones para Quest, pero exige cuenta de desarrollador de Meta verificada y compilar el motor desde código fuente (horas de compilación y cientos de GB). Desproporcionado para un proyecto individual.
- **Solo OpenXR, sin el plugin de Meta:** menos dependencias, pero se pierden el seguimiento de manos y las utilidades específicas de Quest.

## Consecuencias

- Toolchain de Android ligada a la versión del motor: instalar las versiones de SDK/NDK que indique la documentación de UE 5.7, no las más recientes.
- Hay que verificar al instalar que el plugin sigue soportando Quest 2.
