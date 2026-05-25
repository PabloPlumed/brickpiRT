"""ColorSensorNode supports 3 light detection modes:
   COLOR: Returns one of none, Black, Blue, Green, Yellow, Red, White, Brown.
   REFLECTED: Returns UInt8 between 0-100 indicating percentage of reflected light received.
   AMBIENT: Returns UInt8 between 0-100 of ambient light received
       (ie sensor does not activate illumination).
"""

import os
import ctypes
import brickpi3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Illuminance


def set_rt_priority(priority):
    """Asigna prioridad SCHED_FIFO al thread actual"""
    SCHED_FIFO = 1
    class sched_param(ctypes.Structure):
        _fields_ = [('sched_priority', ctypes.c_int)]
    param = sched_param(priority)
    libc = ctypes.CDLL('libc.so.6')
    ret = libc.sched_setscheduler(0, SCHED_FIFO, ctypes.byref(param))
    return ret


def set_cpu_affinity(core):
    """Pina el proceso al core indicado"""
    os.sched_setaffinity(0, {core})


class ColorSensorNode(Node):
    """ColorSensorNode publishes appropriate message"""
    def __init__(self):
        super().__init__("color_sensor_node")
        self.declare_parameter('lego_port', 'PORT_1')
        self.declare_parameter('detection_mode', 'REFLECTED')
        self.declare_parameter('frequency', 2.0)
        self.bp = brickpi3.BrickPi3()
        port_dict = { "PORT_1": self.bp.PORT_1,
                      "PORT_2": self.bp.PORT_2,
                      "PORT_3": self.bp.PORT_3,
                      "PORT_4": self.bp.PORT_4 }
        self.lego_port_name = self.get_parameter('lego_port').get_parameter_value().string_value
        try:
            self.lego_port = port_dict[self.lego_port_name]
        except KeyError as e:
            fatal_msg = f'Unknown lego input port: {e}'
            self.get_logger().fatal(fatal_msg)
            raise IOError(fatal_msg) from e
        self.detection_mode = \
            self.get_parameter('detection_mode').get_parameter_value().string_value
        if self.detection_mode == "REFLECTED":
            self.publisher = self.create_publisher(Illuminance, "light_intensity", 10)
            self.bp.set_sensor_type(self.lego_port, self.bp.SENSOR_TYPE.NXT_LIGHT_ON)
        else:
            fatal_msg = f'Unknown mode: {self.detection_mode}'
            self.get_logger().fatal(fatal_msg)
            raise ValueError(fatal_msg)

        self.colormap = ["none", "Black", "Blue", "Green", "Yellow", "Red", "White", "Brown"]
        timer_period = 1.0/self.get_parameter('frequency').get_parameter_value().double_value
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.get_logger().info("Node has started.")

    def timer_callback(self):
        """reads color sensor and publishes appropriate message"""
        try:
            value = self.bp.get_sensor(self.lego_port)
            if self.detection_mode == "REFLECTED":
                msg = Illuminance()
                # Normalizamos el valor del sensor, 1.0 -> blanco, 0.0 -> Negro
                NEGRO_PURO = 2634   # Obtenidos empiricamente
                BLANCO_PURO = 1926
                msg.illuminance = (NEGRO_PURO - value) / (NEGRO_PURO - BLANCO_PURO)

            msg.header.stamp = self.get_clock().now().to_msg()
            msg.header.frame_id = "color_sensor"
            self.publisher.publish(msg)
        except brickpi3.SensorError as e:
            warn_msg = f'Invalid color sensor data on {self.lego_port_name}'
            self.get_logger().warn(warn_msg)

    def destroy_node(self):
        self.bp.reset_all()
        super().destroy_node()


# Pineamos el thread al core 3 y le damos la mayor prioridad entre los otros procesos
set_cpu_affinity(1)
#ret = set_rt_priority(55)
#if ret != 0:
#    print("WARN: No se pudo establecer prioridad RT, ejecuta: sudo setcap cap_sys_nice+ep $(which python3)")
#else:
#    print("INFO: Prioridad RT 55 y core 3 asignados al sensor")

rclpy.init()
color_sensor_node = ColorSensorNode()
try:
    rclpy.spin(color_sensor_node)
except KeyboardInterrupt:
    pass
finally:
    color_sensor_node.destroy_node()
    rclpy.shutdown()