from setuptools import find_packages
from setuptools import setup

setup(
    name='ev3_sensor_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('ev3_sensor_msgs', 'ev3_sensor_msgs.*')),
)
