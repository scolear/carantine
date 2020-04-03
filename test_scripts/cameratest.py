from picamera import PiCamera
from time import sleep

camera = PiCamera()

camera.rotation = 180

if __name__ == '__main__':
    try:
        camera.start_preview(fullscreen=False, window = (100, 20, 1024, 768), alpha=200)
        while True:
            continue
    except KeyboardInterrupt:
        camera.stop_preview()
        print('Stopped')
