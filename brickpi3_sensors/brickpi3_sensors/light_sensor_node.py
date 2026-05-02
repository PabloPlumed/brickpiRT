"""ColorSensorNode supports 3 light detection modes:
   COLOR: Returns one of none, Black, Blue, Green, Yellow, Red, White, Brown.
   REFLECTED: Returns UInt8 between 0-100 indicating percentage of reflected light received.
   AMBIENT: Returns UInt8 between 0-100 of ambient light received
       (ie sensor does not activate illumination).
"""

import brickpi3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Illuminance


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
                # User measurements: Negro ~ 2.7, Blanco ~ 1.9
                # We want Negro < 0.5 and Blanco > 0.7
                # Formula: 3.1 - value
                msg.illuminance = 3.1 - (float(value) / 1023.0)

            msg.header.stamp = self.get_clock().now().to_msg()
            msg.header.frame_id = "color_sensor"
            self.publisher.publish(msg)
        except brickpi3.SensorError as e:
            warn_msg = f'Invalid color sensor data on {self.lego_port_name}'
            self.get_logger().warn(warn_msg)

rclpy.init()
color_sensor_node = ColorSensorNode()
rclpy.spin(color_sensor_node)
color_sensor_node.destroy_node()
rclpy.shutdown()
