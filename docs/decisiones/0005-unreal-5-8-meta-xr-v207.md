# 0005 — Unreal Engine 5.8 del Epic Launcher con el Meta XR Plugin v207

- **Estado:** Aceptada
- **Fecha:** 2026-10-01
- **Sustituye a:** [0004](0004-unreal-5-7-launcher-meta-xr.md)

## Contexto

La [0004](0004-unreal-5-7-launcher-meta-xr.md) elegía UE 5.7 porque el Meta XR Plugin de ese momento no cargaba en UE 5.8. El 23 de septiembre de 2026 Meta publicó el **Meta XR Plugin v207.0**, cuyo motor objetivo es **UE 5.8.0**. Con eso deja de cumplirse el motivo de la 0004.

Además, el plugin descargable se publica para una sola versión del motor ("targets the latest supported version of Unreal Engine"). Quedarse en 5.7 significa quedarse con una versión antigua del plugin que ya no recibirá correcciones.

Unreal todavía no está instalado, así que cambiar ahora no cuesta nada.

## Decisión

- **UE 5.8 desde el Epic Games Launcher**, con el componente de plataforma Android.
- **Meta XR Plugin v207.0**, o la última 207.x para UE 5.8 en el momento de instalar.
- **Congelar el motor durante todo el curso.** El plugin solo se actualiza si arregla algo que nos bloquea, y queda anotado en la bitácora del sprint. Para cambiar de motor hace falta una ADR nueva.
- El sprint 1 sigue dedicado a quitar riesgo: un proyecto vacío ejecutándose en las Quest 2 antes de escribir lógica de juego.

### Criterio de vuelta atrás (plan B)

Si el **8 de octubre de 2026** (mitad del sprint 1) no hay una build vacía funcionando en las Quest 2 por un fallo atribuible a UE 5.8 o al plugin, se pasa a **UE 5.7 con la última versión del plugin para 5.7**, con una ADR nueva que sustituya a esta.

## Alternativas descartadas

- **UE 5.7 con una versión anterior del plugin:** hay más tutoriales y más problemas ya documentados. A cambio, el plugin se queda congelado sin correcciones, y la limitación de Fixed Foveated Rendering en tiempo de ejecución afecta a "UE 5.7+", así que en ese punto 5.7 no gana nada. Queda como plan B.
- **Fork Oculus-VR de Unreal (GitHub de Meta):** mismo motivo que en la 0004, porque hay que compilar el motor (horas y cientos de GB). Con v207, además, Dynamic Resolution solo está disponible en el fork. Se acepta perderla.
- **Solo OpenXR, sin el plugin de Meta:** igual que en la 0004, se pierden el seguimiento de manos y las utilidades específicas de Quest.

## Consecuencias

- La toolchain de Android (SDK, NDK y JDK) va ligada a la versión del motor: se instalan las versiones que indique la documentación de UE 5.8, no las más recientes.
- Problemas conocidos de v207 que afectan al diseño:
  - Fixed Foveated Rendering no se puede cambiar en tiempo de ejecución en UE 5.7+, así que se fija en los ajustes del proyecto.
  - No hay Dynamic Resolution fuera del fork, así que el rendimiento en Quest 2 se gestiona con un presupuesto fijo (resolución y contenido), sin escalado automático.
- Quest 2: no se ha encontrado ningún aviso de fin de soporte para apps autónomas, pero tampoco una confirmación explícita en las notas de v207. Lo valida la primera build en el visor (sprint 1).
- Motor muy reciente: habrá menos material específico de 5.8. La documentación de 5.7 suele servir.

## Fuentes

- [Meta XR Plugin v207.0, notas de versión](https://developers.meta.com/horizon/downloads/package/unreal-engine-5-integration/207.0/)
- [Instalación del Meta XR Plugin](https://developers.meta.com/horizon/documentation/unreal/unreal-quick-start-install-metaxr-plugin/)
- [Matriz de compatibilidad de Meta para Unreal](https://developers.meta.com/horizon/documentation/unreal/unreal-compatibility-matrix/)
