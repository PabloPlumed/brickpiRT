# Test para comprobar el correcto funcionamiento del nodo maquina de estados
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Illuminance
import threading

class TestMaquinaEstados(Node):
    def __init__(self):
        super().__init__('test_me_publisher')
        self.pub = self.create_publisher(Illuminance, '/light_intensity', 10)
        self.timer = self.create_timer(0.1, self.callback)
        self.valor = 0.5 # Publicamos 0.5 por defecto, ir cambiandolo en la terminal
        self.get_logger().info('Publicando. Escribe un valor (0.0-1.0) y Enter para cambiarlo.')

    def callback(self):
        msg = Illuminance()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.illuminance = self.valor
        self.pub.publish(msg)

def leer_teclado(nodo):
    while True:
        try:
            v = float(input())
            nodo.valor = v
            print(f'Valor cambiado a: {v}')
        except ValueError:
            print('Valor inválido, escribe un número entre 0.0 y 1.0')

rclpy.init()
nodo = TestMaquinaEstados()

# Thread separado para leer teclado sin bloquear el spin
hilo = threading.Thread(target=leer_teclado, args=(nodo,), daemon=True)
hilo.start()

rclpy.spin(nodo)
rclpy.shutdown()