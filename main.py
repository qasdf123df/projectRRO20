import math
from math import atan
import serial
import time

def get_x_y(lisd):
    return lisd[0]['x'], lisd[0]['y'], lisd[1]['x'], lisd[1]['y']


def get_dist(old_x, old_y, curr_x, curr_y):  # movement near x and y
    return ((curr_x - old_x) ** 2 + (curr_y - old_y) ** 2) ** 0.5


def get_angle(old_x, old_y, curr_x, curr_y):
    return math.atan(abs(old_x - curr_x) / abs(old_y - curr_y)) * 180 / 3.14

def get_angle_for_turn(old_x, old_y, curr_x, curr_y, angle):
    return atan(abs(old_x - curr_x) / abs(old_y - curr_y)) * 180 / 3.14 - angle

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)


# turn left - plus angle, turn right - minus angle
curr_angle = 0
k = 30
q = [{'x': 24*k, 'y': 22*k}, {'x': 15*k, 'y': 11*k}, {'x': 3*k, 'y': 4*k}, {'x': 0, 'y': 0}]
angle = 0
q.reverse()
while len(q) >= 2:
    print(get_x_y(q))
    print("movement: ", get_dist(get_x_y(q)[0], get_x_y(q)[1],
                                 get_x_y(q)[2], get_x_y(q)[3]))
    print('angle: ', get_angle(get_x_y(q)[0], get_x_y(q)[1],
                               get_x_y(q)[2], get_x_y(q)[3]))
    print('angle to turn: ', get_angle_for_turn(get_x_y(q)[0], get_x_y(q)[1],
                                                get_x_y(q)[2], get_x_y(q)[3], angle))
    line = str(int(get_dist(get_x_y(q)[0], get_x_y(q)[1],
                      get_x_y(q)[2], get_x_y(q)[3]))) + ' ' + str(int(get_angle_for_turn(get_x_y(q)[0], get_x_y(q)[1],
                                                get_x_y(q)[2], get_x_y(q)[3], angle))) + '\n'
    print('line:', line)
    try:
        ser.write(line.encode('utf-8'))
        time.sleep(1)
        # ser.flush()
        while ser.in_waiting <= 0:
            break
        data = ser.readline().decode('utf-8').strip()
        print(f"get: {data}")
    except KeyboardInterrupt:
        ser.close()
    


    angle = get_angle(get_x_y(q)[0], get_x_y(q)[1],
                      get_x_y(q)[2], get_x_y(q)[3])



    q.pop(0)
    print(q)
