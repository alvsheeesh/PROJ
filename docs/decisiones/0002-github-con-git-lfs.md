# 0002 — Repositorio público en GitHub con Git LFS

- **Estado:** Aceptada
- **Fecha:** 2026-09-29

## Contexto

Un proyecto de Unreal mezcla código C++ (texto) con assets binarios (`.uasset`, `.umap`, mallas, texturas, audio) que Git gestiona mal: cada versión de un binario se guarda entera y el repositorio crece sin control. El repositorio será público porque el proyecto irá al portfolio.

## Decisión

- GitHub, **repositorio público**, con **Git LFS** para todos los binarios (ver `.gitattributes`); `.uasset` y `.umap` marcados como bloqueables.
- `.gitignore` excluye todo lo que el motor regenera (`Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`), los builds de Android (`.apk`, `.obb`) y los secretos (keystores).
- El proyecto de Unreal vive en `TAKT/`; la documentación, en `docs/`. Así el asistente de Unreal crea el proyecto directamente en su sitio y la documentación del TFC no se mezcla con el contenido del juego.
- Activar *secret scanning* y *push protection* de GitHub (gratis en repos públicos).

## Alternativas descartadas

- **Repositorio privado:** evita los problemas de licencias de assets, pero obliga a invitar al profesor y no sirve para el portfolio sin hacerlo público después.
- **`.uproject` en la raíz del repo:** es lo habitual, pero obliga a mover el proyecto tras crearlo y mezcla la documentación con las carpetas del motor.
- **Perforce (Helix Core):** el estándar en estudios de Unreal, pero el enunciado pide GitHub y añade infraestructura que no aporta a un proyecto individual.
- **Gitea autoalojado en el NAS:** LFS sin cuota, pero el profesor necesita un enlace accesible y exponer el NAS a internet no compensa.
- **Git sin LFS:** el historial de binarios haría el repositorio inmanejable en pocas semanas.

## Consecuencias

- La cuota gratuita de LFS en GitHub es de 10 GiB de almacenamiento y 10 GiB de transferencia al mes; cada versión de un asset suma. Hay que vigilarla.
- Es necesario `git lfs install` en cada máquina antes de clonar.
- Al ser público, todo lo que se sube es visible para siempre (el historial no se borra fácilmente): nunca subir credenciales, ni siquiera "un momento".
