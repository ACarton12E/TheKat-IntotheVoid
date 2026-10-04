# The Kat: Into the Void!

<img title="" src="./src/assets/Images/Other/Car.png" alt="Caratula" width="402" data-align="center">

> Idioma por defecto: [English](./README.md) | **Español**

Cuenta la historia de un gato llamado The Kat, atrapado dentro del estómago vacío de un virus llamado BRutor.

Es un juego de pixel art inspirado en Nyan Cat: Lost in Space.

## Historia

> ### Capítulo 1: El Flop-Drivetor
> 
> Todo comienza en la casa de Sylvienee. Ella recibe un disquete desconocido etiquetado como "Flop-Drivetor" y lo introduce en su computadora, solo para encontrarse con un archivo ejecutable sospechoso. Al abrirlo, el programa le solicita una contraseña de superusuario; sin embargo, como Sylvienee tiene un comando automatizado para saltarse la autenticación de root, un pez aparece en la pantalla y comienza a devorar lentamente los píxeles de la pantalla, identificándose a sí mismo como BRutor.
> 
> Sylvienee tiene el DigiCU-3D, un digitalizador creado por su primo ingeniero Jason que distribuye los datos entre la CPU y la GPU mientras mantiene una gran parte en la memoria RAM; por razones de seguridad, estos datos no se borran cuando la computadora se reinicia.

> ### Capítulo 2: Al Caño
> 
> Mientras Sylvienee se digitaliza a sí misma, saca su Spray Antivirus y le dispara a BRutor pero falla; BRutor es extremadamente rápido.
> 
> En ese momento de tensión, The Kat, la mascota de Sylvienee, se acerca con curiosidad a la computadora. Al ver a Sylvienee luchar, llama a Starubela, Felix y Tomy para que miren, pero accidentalmente tropiezan con el digitalizador y terminan siendo digitalizados también.
> 
> Al ver a los dos pelear, Sylvienee se distrae tanto con sus mascotas que BRutor aprovecha la oportunidad para des-digitalizarse, desatando el caos en el mundo exterior.

> ### Capítulo 3: ¡Hacia el Vacío! (Into the Void!)
> 
> Sylvienee se molesta muchísimo y los regaña severamente, pero ellos la ignoran y salen corriendo, abriendo frenéticamente archivos, aplicaciones y comandos. Sylvienee grita: "¡¡CUIDADO CON LA RAM!! SE VA A REINIC..." y se activa un evento masivo de OOM-Killer que reinicia automáticamente la computadora.
> 
> Todos esperan a que la PC reinicie, sintiéndose algo aliviados... pero BRutor ha corrompido el GRUB y un Nyan Cat aparece en la pantalla. De repente, de la nada, un vacío los traga y materializa en un paisaje gris lleno de ondas y objetos flotantes.
> 
> Todos se separan excepto Sylvienee y The Kat, quienes permanecen juntos y caen suavemente sobre una plataforma flotante; la gravedad no es muy fuerte allí, pero se siente extraña.
> 
> Desafortunadamente, la motocicleta voladora de Sylvienee está destrozada, así que envía a The Kat a recolectar aleaciones para repararla y escapar. Sin embargo, no esperaban el peligro que acecha hacia donde se dirige The Kat: los Shaders, y hay otro mucho, mucho más lejos en la distancia:
> 
> - **Fishoder**: Un Shader con forma de pez que te traga por completo.
> - **Shadowner**: Un Shader con forma de renacuajo que te persigue si te acercas demasiado.
> - **Pushader**: Un Shader con forma de bola de pinchos que siempre está dormido; no es hostil, pero inflige daño si lo tocas.
> - **LongShodernom**: El jefe; comparte la misma base de código, toma la forma de una desagradable masa roja de caras tristes encajonada en una armadura con forma de pez con brazos y piernas.
> 
> #### ...y la aventura apenas comienza.

---

## Controles y Jugabilidad

### Mando / Gamepad

- **Botón A / X**: Saltar (normalmente doble salto)
- **Botón X / □**: Detenerse
- **Stick Izquierdo**: Apuntar / Nadar o Volar hacia
- **Gatillo Derecho (RT / R2)**: Disparar

### Teclado y Ratón

- **Espacio**: Saltar (normalmente doble salto)
- **X**: Detenerse
- **Posición del Ratón**: Apuntar / Nadar o Volar hacia
- **Clic Izquierdo**: Disparar

---

## Configuración

### Dependencias Requeridas

- SDL2 Core
- SDL2 Image
- SDL2 TTF
- SDL2 Mixer
- XMake

### Instalación

#### Ubuntu / Debian

```bash
sudo apt update
sudo apt install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-ttf-2.0-0 libsdl2-mixer-2.0-0
```

#### Fedora / RHEL

```bash
sudo dnf install SDL2 SDL2_image SDL2_ttf SDL2_mixer
```

### Compilación

```bash
# Clonar el repositorio:
git clone https://github.com/ACarton12E/TheKat-IntotheVoid

# Entrar al directorio y ejecutar con xmake:
cd TheKat-IntotheVoid
xmake run
```

---

## Información del Juego

### Datos Técnicos

- **Lenguaje**: :hammer: `C++20`
- **Librerías utilizadas**: `SDL2 (Mixer, TTF, Image)`
- **Sistema de construcción**: `XMake`
- **Versión del juego**: `0.1-a bedul`

### Requisitos del Sistema

#### PC

- **CPU**: Intel Core 2 Duo T7300 (2.0 GHz) / AMD Turion 64 X2.
- **RAM**: 258MB de RAM DDR2
- **GPU**: iGPU (24MB, OpenGL 2.1)
- **Almacenamiento**: 258MB | HDD / CD
- **SO**: Linux (todas las distribuciones), Windows

#### Teléfono Celular

- **CPU**: Snapdragon 400 / MediaTek MT6582 (Quad-Core @ 1.2 GHz ARM)
- **RAM**: 258MB de RAM
- **GPU**: Adreno 305 / Mali-400 MP2 (Soporta OpenGL ES 2.0)
- **SO**: Solo Android

#### Raspberry Pi

- **Placa**: Raspberry Pi 2 Model B
- **CPU**: Broadcom BCM2836 (Quad-Core ARM Cortex-A7 @ 900 MHz)
- **RAM**: 258MB de RAM
- **GPU**: VideoCore IV (OpenGL ES 2.0)

#### PinePhone

- **CPU**: Allwinner A64 (Quad-Core ARM Cortex-A53 @ 1.15 GHz)
- **RAM**: 258MB de RAM
- **GPU**: ARM Mali-400 MP2 @ 400 MHz

---

>**¡¡AVISO!!** Los requisitos de los sistemas a parte de PC y Android no fueron verificados, ¡apoyame a saber si funcionan bien!

¡Gracias por jugar! :)

<img title="" src="./src/assets/Images/Other/Car1.png" alt="content" width="252" data-align="center">
