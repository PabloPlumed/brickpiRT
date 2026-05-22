from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    # 1. Incluir el launch de los motores de Charlie
    motors_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([
                FindPackageShare('brickpi3_charlie'),
                'launch',
                'motors_launch.py'
            ])
        ])
    )

    # 2. Nodo del sensor de luz
    light_sensor_node = Node(
        package='brickpi3_sensors',
        executable='light_sensor_node',
        name='light_sensor_node',
        parameters=[{'lego_port': 'PORT_2'}],
        output='screen'
    )

    return LaunchDescription([
        motors_launch,
        light_sensor_node
    ])
