from pynput import keyboard
import serial
    
import time

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

key_states = {
    'up': False,
    'down': False,
    'left': False,
    'right': False,
    'light':False
}
def send_signal():
    pass
  
def send_serial_command():
    if key_states['up']:
        ser.write(b'1\n')
    elif key_states['down']:
        ser.write(b'2\n')
    elif key_states['left']:
        ser.write(b'3\n')
    elif key_states['right']:
        ser.write(b'4\n')
    elif key_states['light']:
        ser.write(b'5\n')
    else:
        ser.write(b'0\n')
   
def on_press(key):
    try:
        if key == keyboard.Key.up:
            key_states['up'] = True
        elif key == keyboard.Key.down:
            key_states['down'] = True
        elif key == keyboard.Key.left:
            key_states['left'] = True
        elif key == keyboard.Key.right:
            key_states['right'] = True
        elif key == keyboard.Key.ctrl:
            key_states['light'] = True
        send_serial_command()
    except:
        pass

def on_release(key):
    try:
        if key == keyboard.Key.up:
            key_states['up'] = False
        elif key == keyboard.Key.down:
            key_states['down'] = False
        elif key == keyboard.Key.left:
            key_states['left'] = False
        elif key == keyboard.Key.right:
            key_states['right'] = False
        elif key == keyboard.Key.ctrl:
            key_states['light'] = False
        elif key == keyboard.Key.esc:
            return False
        send_serial_command()
    except:
        pass

print("wait esc...")

with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()

ser.close()
# picam2.stop()
# cv2.destroyAllWindows()
