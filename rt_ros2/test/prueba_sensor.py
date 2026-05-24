import brickpi3
bp = brickpi3.BrickPi3()
bp.set_sensor_type(bp.PORT_2, bp.SENSOR_TYPE.NXT_LIGHT_ON)
import time
time.sleep(1)
print(bp.get_sensor(bp.PORT_2))  # mirar el valor que devuelve el sensor para una superficie
bp.reset_all()