import brickpi3
import time

# Inicializar la placa
bp = brickpi3.BrickPi3()

def test_motores():
    try:
        print("Iniciando prueba infinita de motores (MA y MD)...")
        print("Pulsa Ctrl+C para detener la prueba.")
        
        while True:
            # Probar Motor A (MA) - Izquierdo
            print("\n[TEST] Probando solo MOTOR A (Puerto MA)...")
            bp.set_motor_power(bp.PORT_A, 50)
            bp.set_motor_power(bp.PORT_D, 0)
            time.sleep(2)

            # Probar Motor D (MD) - Derecho
            print("[TEST] Probando solo MOTOR D (Puerto MD)...")
            bp.set_motor_power(bp.PORT_A, 0)
            bp.set_motor_power(bp.PORT_D, 50)
            time.sleep(2)

            # Probar ambos motores a la vez
            print("[TEST] Probando AMBOS motores...")
            bp.set_motor_power(bp.PORT_A, 50)
            bp.set_motor_power(bp.PORT_D, 50)
            time.sleep(2)

            # Parada de seguridad antes de repetir
            print("[PAUSA] Motores parados 1 seg.")
            bp.set_motor_power(bp.PORT_A, 0)
            bp.set_motor_power(bp.PORT_D, 0)
            time.sleep(1)

    except KeyboardInterrupt:
        print("\nPrueba detenida por el usuario.")
    except Exception as e:
        print(f"Error inesperado: {e}")
    finally:
        # Importante: resetear todo para que los motores no se queden girando
        bp.reset_all()
        print("Hardware reseteado y motores apagados.")

if __name__ == "__main__":
    test_motores()
