# 0003 — Política de assets en un repositorio público

- **Estado:** Aceptada
- **Fecha:** 2026-09-29

## Contexto

El repositorio es público ([0002](0002-github-con-git-lfs.md)). La licencia estándar de Fab (el antiguo Marketplace de Unreal) no deja claro que se puedan publicar sus assets en formato fuente en un repositorio abierto, y la interpretación más prudente es que no.

## Decisión

Solo entran en el repositorio:

1. Assets **propios** (modelados, texturas, sonidos hechos para TAKT).
2. Assets con licencia que permita **redistribución**: CC0 (p. ej. Kenney, Poly Haven) o CC-BY con atribución.
3. Contenido de ejemplo de Epic que el EULA de Unreal permite distribuir (plantillas, *starter content*).

Cada asset de terceros se anota en `CREDITS.md` con autor, licencia y enlace **en el mismo commit en el que se añade**.

## Alternativas descartadas

- **Usar Fab y excluirlo con `.gitignore`:** el código se vería, pero nadie (tampoco el profesor) podría abrir el proyecto clonado: faltarían referencias.
- **Repositorio privado:** descartado en [0002](0002-github-con-git-lfs.md).

## Consecuencias

- Estética más sencilla (*greybox* + packs CC0), algo coherente con que el profesor valora la programación, no los gráficos.
- Si más adelante hace falta un asset de Fab concreto, se revisa esta decisión con una nueva ADR.
