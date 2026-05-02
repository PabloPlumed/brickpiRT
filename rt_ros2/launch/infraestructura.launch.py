from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    # Utilizar fichero de launch de charlie para levantar los motores
    motors_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([
                FindPackageShare('brickpi3_charlie'),
                'launch',
                'motors_launch.py'
            ])
        ])
    )

    # Launch del sensor de luz en el puerto 2
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
