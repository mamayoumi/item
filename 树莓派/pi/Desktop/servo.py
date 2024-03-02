
import RPi.GPIO as GPIO
from time import sleep
 
servo_pin = 12                # 舵机信号线接树莓派GPIO17
 
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(servo_pin, GPIO.OUT, initial=False)
initang=90
# 旋转角度转换到PWM占空比
def angleToDutyCycle(angle):
    return 2.5 + angle / 180.0 * 10
def servo(angle):
    global initang
    if angle<initang:
        for mis in range(initang-1,angle-1,-1):
            p.ChangeDutyCycle(angleToDutyCycle(mis))
            sleep(0.015)
            p.ChangeDutyCycle(0)
    
            
    else:
        for mis in range(initang,angle+1):
            p.ChangeDutyCycle(angleToDutyCycle(mis))
            sleep(0.015)
            p.ChangeDutyCycle(0)
    initang=angle
            
 
p = GPIO.PWM(servo_pin, 50)    # 初始频率为50HZ
p.start(angleToDutyCycle(90))  # 舵机初始化角度为90
sleep(0.5)
p.ChangeDutyCycle(0)           # 清空当前占空比，使舵机停止抖动
 
if __name__ == '__main__':
    print('当前为90度')
    while True:
        angle = int(input('旋转度数：'))
        if angle >= 0 and angle <= 180:
            servo(angle) # 清空当前占空比，使舵机停止抖动
        else:
            print('旋转度数在0-180之间！')
