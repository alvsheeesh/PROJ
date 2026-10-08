# Entorno de desarrollo

Versiones y pasos para montar el entorno de TAKT en Windows. Las versiones de las toolchains salen de los ficheros del motor (`Engine/Config/Windows/Windows_SDK.json` y `Engine/Config/Android/Android_SDK.json`), no de la documentación web, que a veces no coincide.

## Versiones

| Componente | Versión | Ubicación (PC de desarrollo) |
|------------|---------|------------------------------|
| Unreal Engine | 5.8.3 (Epic Games Launcher), plataforma Android | `E:\Epic Games\UE_5.8` |
| Meta XR Plugin | v207.x para UE 5.8 ([ADR 0005](decisiones/0005-unreal-5-8-meta-xr-v207.md)) | Pendiente de instalar |
| Visual Studio | 2026 Community (18.x) | `E:\Microsoft Visual Studio` |
| MSVC | 14.51 (ver la nota más abajo) | — |
| Windows SDK | 10.0.26100 (el motor acepta de 10.0.19041 en adelante) | — |
| JDK para Android | Temurin 21 | `E:\JDK21\jdk-21.0.12.1+1` |
| Android SDK | `platforms;android-36`, `build-tools;36.0.0`, `cmake;3.22.1`, `platform-tools` | `E:\Android\Sdk` |
| Android NDK | r27c (`27.2.12479018`) | `E:\Android\Sdk\ndk\27.2.12479018` |
| Visor | Meta Quest 2 + Meta Quest Link (PC) | — |

### Nota sobre MSVC

UE 5.8.3 prefiere las versiones 14.50 y 14.44 y **veta las 14.50 anteriores a la 35723**, por errores internos del compilador. El componente "MSVC v14.50" del instalador de VS 2026 instala la 14.50.35717, que está vetada. UnrealBuildTool la descarta automáticamente y usa la siguiente válida, en este caso la 14.51. **No se debe fijar `CompilerVersion` a 14.50.**

El fallo conocido de la 14.51 con UE 5.8 (falta la cabecera `hash_map`) se ha reportado al compilar el motor desde el código fuente, en una librería de terceros del motor. Un proyecto con el motor del Launcher no recompila esa librería. Si aun así apareciera, esta nota se revisaría con una ADR.

El compilador se fija a VS 2026 en la configuración del proyecto, para que no busque VS 2022:

```ini
; TAKT/Config/DefaultEngine.ini
[/Script/WindowsTargetPlatform.WindowsTargetSettings]
Compiler=VisualStudio2026
```

Y en el editor: *Editor Preferences → General → Source Code → Source Code Editor = Visual Studio 2026*.

## Visual Studio 2026

Cargas de trabajo: **Desarrollo para el escritorio con C++**, **Desarrollo de juegos con C++** y **Desarrollo de escritorio de .NET**. Dentro de *Desarrollo de juegos con C++*, marcar también la compatibilidad del IDE con Unreal Engine.

No hace falta .NET MAUI: instala su propio Android SDK y su propio JDK, y entra en conflicto con la toolchain de Unreal.

## Android ([ADR 0008](decisiones/0008-toolchain-android-sin-android-studio.md))

1. Descargar *Command line tools only* para Windows desde <https://developer.android.com/studio> (al final de la página).
2. Descomprimir el contenido de su carpeta `cmdline-tools` en `E:\Android\Sdk\cmdline-tools\latest\`, de forma que exista `E:\Android\Sdk\cmdline-tools\latest\bin\sdkmanager.bat`.
3. En PowerShell:

```powershell
$sdk = 'E:\Android\Sdk'
$ndk = '27.2.12479018'
$env:JAVA_HOME = 'E:\JDK21\jdk-21.0.12.1+1'   # solo para esta ventana
$sm = "$sdk\cmdline-tools\latest\bin\sdkmanager.bat"

& $sm --sdk_root=$sdk --licenses
& $sm --sdk_root=$sdk 'platform-tools' 'platforms;android-36' 'build-tools;36.0.0' 'cmake;3.22.1' "ndk;$ndk"

[Environment]::SetEnvironmentVariable('ANDROID_HOME', $sdk, 'User')
[Environment]::SetEnvironmentVariable('NDKROOT', "$sdk\ndk\$ndk", 'User')
[Environment]::SetEnvironmentVariable('NDK_ROOT', "$sdk\ndk\$ndk", 'User')
[Environment]::SetEnvironmentVariable('GRADLE_USER_HOME', 'E:\Android\.gradle', 'User')

$p = [Environment]::GetEnvironmentVariable('Path', 'User')
if ($p -notlike "*$sdk\platform-tools*") {
  [Environment]::SetEnvironmentVariable('Path', "$p;$sdk\platform-tools", 'User')
}
```

4. Cerrar la sesión de Windows y volver a entrar, para que se apliquen las variables.
5. En una terminal nueva, `where.exe adb` debe devolver **primero** `E:\Android\Sdk\platform-tools\adb.exe`. Si aparece antes otro `adb` (por ejemplo, el de `E:\ADB (Oculus)`), quitarlo del `PATH`: dos versiones distintas de adb se cierran el servidor la una a la otra.
6. En Unreal, *Project Settings → Platforms → Android SDK*: SDK `E:\Android\Sdk`, NDK `E:\Android\Sdk\ndk\27.2.12479018` y Java `E:\JDK21\jdk-21.0.12.1+1`.

`JAVA_HOME` no se modifica: en este PC apunta a un JDK 25 que se usa en otras asignaturas.

## Meta Quest 2

- Cuenta de desarrollador de Meta con una organización, y el modo desarrollador activado desde la app Meta Horizon del móvil.
- Meta Quest Link en el PC para la vista previa en VR desde el editor.
