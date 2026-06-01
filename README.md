# Proyecto BrickPi RT

Robot seguidor de línea sobre plataforma **Charlie (BrickPi3 + Raspberry Pi)** con ROS2 Humble, incluyendo un análisis de comportamiento en tiempo real mediante `cactus_rt`.

---

## Qué mirar y qué no

### Código original del proyecto (lo que hemos implementado nosotros)

| Directorio / Fichero | Qué es |
|---|---|
| `rt_ros2/src/nodo_maquina_estados.cpp` | Máquina de estados del robot (SEGUIR_LINEA → RECUPERAR → PARAR) |
| `rt_ros2/src/nodo_actuador.cpp` | Nodo actuador: traduce estado + error a comandos de velocidad `/cmd_vel` |
| `rt_ros2/src/mainRT.cc` | Ejecutable RT: separa nodos en ejecutores best-effort y real-time (SCHED_FIFO pr=60) |
| `rt_ros2/src/mainBE.cc` | Ejecutable BE: mismos nodos pero en un único ejecutor sin prioridades RT |
| `rt_ros2/src/main.cc` | Variante base del ejecutable (misma estructura que mainRT) |
| `rt_ros2/include/rt_ros2/nodo_maquina_estados.h` | Header de la máquina de estados |
| `rt_ros2/include/rt_ros2/nodo_actuador.h` | Header del actuador |
| `rt_ros2/launch/infraestructura.launch.py` | Launch file: arranca motores (Charlie) + sensor de luz juntos |
| `rt_ros2/CMakeLists.txt` | Build del paquete rt_ros2 con los tres ejecutables + tests |
| `brickpi3_sensors/brickpi3_sensors/light_sensor_node.py` | Nodo sensor NXT de luz (único sensor que usamos de este paquete) |

### Código base reutilizado (no es nuestro, pero lo usamos)

| Directorio | Qué es | Qué hemos usado |
|---|---|---|
| `brickpi3_charlie/` | Robot de demostración Charlie | Solo su `motors_launch.py` y configs URDF/YAML para arrancar los motores |
| `brickpi3_sensors/` | Paquete de nodos sensor para BrickPi3 | Únicamente `light_sensor_node.py` (sensor NXT de luz reflejada) |
| `brickpi3_motors/` | Plugin ROS2 Control para motores BrickPi3 | Usado como dependencia, sin modificar |
| `ev3_sensor_msgs/` | Definición de mensajes custom EV3 | Dependencia, sin modificar |

### Tests

| Fichero | Tipo | Qué hace |
|---|---|---|
| `rt_ros2/test/nodo_test.cpp` | Test automático de nodos | Publica secuencias de iluminancia predefinidas y comprueba que el estado y el error publicados por la máquina de estados son coherentes |
| `rt_ros2/test/test_maquina_estados.py` | Test manual interactivo | Permite enviar valores de iluminancia desde teclado para probar transiciones de estado en tiempo real |
| `rt_ros2/test/test_actuador.py` | Test manual interactivo | Permite forzar estado + error desde teclado para comprobar que el actuador genera los `/cmd_vel` correctos |
| `rt_ros2/test/prueba_motores.py` | Test hardware directo | Prueba los motores A y D directamente vía BrickPi3 (sin ROS), útil para verificar el hardware antes de lanzar el sistema |

---

## Arquitectura del sistema

```
/light_intensity  (Illuminance)
        │
        ▼
 NodoMaquinaEstados
  ├─ /robot_estado  (String: SEGUIR_LINEA | RECUPERAR | PARAR)
  └─ /error_pos     (Float32: valor_sensor - 0.5)
        │
        ▼
   NodoActuador
        └─ /cmd_vel  (TwistStamped)
                │
                ▼
  diff_drive_controller  →  Motores BrickPi3 (PORT_A izquierdo, PORT_D derecho)
```

**Lógica de control (nodo_actuador.cpp):**
- `SEGUIR_LINEA`: avanza a `VEL_LINEAL=0.1 m/s` con corrección proporcional `angular.z = -KP * error` (KP=2.0)
- `RECUPERAR`: reduce velocidad a `VEL_REC=0.05 m/s` y gira agresivamente para reencontrar la línea
- `PARAR`: velocidad cero

**Thresholds del sensor (nodo_maquina_estados.cpp):**
- `illuminance < 0.5` → negro (dentro de la línea)
- `illuminance > 0.7` → blanco (fuera de la línea)
- Timeout recuperación: 10 s → PARAR

---

## Cómo compilar y lanzar

Se necesitan **dos terminales**: una en el Raspberry Pi (robot) y otra en el PC de desarrollo, o dos shells en el mismo sistema.

### Terminal 1 — Compilar e instalar

```bash
# Situarse en la raíz del workspace ROS2
cd ~/ros2_ws   # o donde tengas el workspace

# Compilar solo los paquetes necesarios (más rápido)
colcon build --symlink-install --packages-select rt_ros2 brickpi3_sensors brickpi3_charlie brickpi3_motors ev3_sensor_msgs

# Cargar el entorno
source install/setup.bash
```

> **Nota:** `brickpi3_motors` requiere la variable de entorno `BRICKPI3_ROOT_DIR` apuntando al directorio de BrickPi3:
> ```bash
> export BRICKPI3_ROOT_DIR=~/BrickPi3
> ```

### Terminal 2 — Lanzar la infraestructura (motores + sensor de luz)

```bash
source ~/ros2_ws/install/setup.bash

ros2 launch rt_ros2 infraestructura.launch.py
```

Esto arranca en paralelo:
- El controlador `diff_drive_controller` para los motores (puertos A y D)
- El nodo `light_sensor_node` en `PORT_2`

### Terminal 1 (o una tercera) — Lanzar el sistema RT o BE

**Con tiempo real (SCHED_FIFO, requiere privilegios):**
```bash
sudo -E ros2 run rt_ros2 main_rt
```

**Sin tiempo real (best-effort, para comparativa):**
```bash
ros2 run rt_ros2 main_be
```

Las trazas de latencia se guardan automáticamente en `/code/brickpi/trazas/` en formato Perfetto (visualizables en https://ui.perfetto.dev).

### Lanzar los tests

```bash
# Test automático (sin hardware)
ros2 run rt_ros2 nodo_test

# Test interactivo de la máquina de estados
python3 rt_ros2/test/test_maquina_estados.py

# Test interactivo del actuador
python3 rt_ros2/test/test_actuador.py

# Test de hardware directo (requiere BrickPi3 conectado)
python3 rt_ros2/test/prueba_motores.py
```

---

## Resumen de lo implementado

- **Máquina de estados reactiva** con tres estados y transiciones basadas en umbral del sensor de luz
- **Control proporcional** de velocidad angular para corrección de trayectoria
- **Dos modos de ejecución**: RT (real-time con SCHED_FIFO) y BE (best-effort) para comparar latencias
- **Instrumentación de latencias** con `cactus_rt` y volcado a ficheros Perfetto
- **Launch file de infraestructura** que integra motores y sensor en un único punto de arranque
- **Batería de tests**: tests automáticos de nodos, tests manuales interactivos y tests de hardware directo
