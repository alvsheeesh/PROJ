# 0008 — Toolchain de Android con las command-line tools, sin Android Studio

- **Estado:** Aceptada
- **Fecha:** 2026-10-01

## Contexto

Para compilar para las Quest 2, UE 5.8.3 necesita los paquetes de Android que declara `Engine/Config/Android/Android_SDK.json`: `platforms;android-36`, `build-tools;36.0.0`, `cmake;3.22.1` y el NDK `27.2.12479018` (r27c). La documentación web de Epic dice SDK 35 y build tools 35.0.1; manda el fichero del motor.

El camino documentado por Epic (`Engine/Extras/Android/SetupAndroid.bat`) tiene dos problemas en este PC:

- **Exige Android Studio instalado.** Busca su ruta en el registro y, si no la encuentra, se para.
- **Solo define `JAVA_HOME` si no existe.** En este PC apunta a un JDK 25 que se usa en otras asignaturas, y el Gradle que usa Unreal no funciona con Java 25.

Además, el disco del sistema (C:) tiene poco espacio libre, y Android Studio y Gradle guardan sus cachés allí por defecto.

## Decisión

- Instalar solo las **Android command-line tools** en `E:\Android\Sdk\cmdline-tools\latest`.
- Instalar con `sdkmanager` exactamente los paquetes de `Android_SDK.json`, ejecutándolo con el **JDK 21** (`E:\JDK21\…`) solo en esa sesión de terminal.
- Variables de usuario: `ANDROID_HOME=E:\Android\Sdk`, `NDKROOT` y `NDK_ROOT` apuntando al NDK r27c, y `GRADLE_USER_HOME=E:\Android\.gradle`. **No se toca `JAVA_HOME`.**
- En Unreal (*Project Settings → Platforms → Android SDK*) se indica de forma explícita la ruta del SDK, del NDK y del **JDK 21**, para que el empaquetado no dependa de `JAVA_HOME`.

Los pasos concretos están en [`docs/entorno.md`](../entorno.md).

## Alternativas descartadas

- **Android Studio Koala más `SetupAndroid.bat` (camino oficial de Epic):** trae Logcat y depuración con interfaz. A cambio, hay que instalar una versión antigua concreta, deja cachés en C: y hay que esquivar el problema de `JAVA_HOME`. Para Quest, los logs se consultan con `adb logcat` o con Meta Quest Developer Hub.
- **Turnkey (*Platforms → SDK Management → Install SDK*):** Epic exige un sistema limpio, sin variables de Android ni de Java previas, y cambiaría `JAVA_HOME` para todo el usuario.

## Consecuencias

- El entorno es reproducible con un único script y sin depender del registro de Android Studio.
- Si hace falta depurar código nativo en el visor, se instalará Android Studio en ese momento, apuntándolo a este mismo SDK.
- Si se actualiza el motor (nueva ADR), hay que repetir la instalación con los paquetes de su `Android_SDK.json`.
