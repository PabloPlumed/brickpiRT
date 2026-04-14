import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Float32
import threading

class TestNodoActuador(Node):
    def __init__(self):
        super().__init__('test_actuador_publisher')
        self.pub_estado = self.create_publisher(String,  '/robot_estado', 10)
        self.pub_error  = self.create_publisher(Float32, '/error_pos', 10)
        self.timer = self.create_timer(0.05, self.callback)
        self.estado = "PARAR"
        self.error  = 0.0
        self.get_logger().info('Listo. Comandos:')
        self.get_logger().info('  s <error>  →  SEGUIR_LINEA con ese error  (ej: s 0.1)')
        self.get_logger().info('  r <error>  →  RECUPERAR con ese error     (ej: r 0.4)')
        self.get_logger().info('  p          →  PARAR')

    def callback(self):
        msg_estado = String()
        msg_estado.data = self.estado
        self.pub_estado.publish(msg_estado)

        msg_error = Float32()
        msg_error.data = self.error
        self.pub_error.publish(msg_error)

def leer_teclado(nodo):
    while True:
        try:
            partes = input().split()
            if not partes:
                continue

            cmd = partes[0]

            if cmd == 's' and len(partes) == 2:
                nodo.estado = "SEGUIR_LINEA"
                nodo.error  = float(partes[1])
                print(f'SEGUIR_LINEA  error={nodo.error:.2f}')

            elif cmd == 'r' and len(partes) == 2:
                nodo.estado = "RECUPERAR"
                nodo.error  = float(partes[1])
                print(f'RECUPERAR  error={nodo.error:.2f}')

            elif cmd == 'p':
                nodo.estado = "PARAR"
                nodo.error  = 0.0
                print('PARAR')

            else:
                print('Comandos: s <error> | r <error> | p')

        except ValueError:
            print('Error inválido, usa un número entre -0.5 y 0.5')

rclpy.init()
nodo = TestNodoActuador()
hilo = threading.Thread(target=leer_teclado, args=(nodo,), daemon=True)
hilo.start()
rclpy.spin(nodo)
rclpy.shutdown()