import pysage

import math
import random

def maxabs(value, maxvalue):
    if (abs(value) > maxvalue):
        return math.copysign(maxvalue, value);
    else:
        return value;

class Ball(pysage.GameObject):
    def __init__(self, x, y):
        pysage.GameObject.__init__(self, x, y, 16, 16)

    def add(self):
        pysage.addObject(self);
        pysage.runThread(self.update)

    def update(self):
        while(1):
            if (self.y < 0):
                self.y = 0
                self.vy = -self.vy
                
            if (self.y > 480 - 16):
                self.y = 480 - 16
                self.vy = -self.vy
                
            if (self.x < 0):
                self.reset(-5, random.randint(-3, 3))
                
            if (self.x > 640 - 16):
                self.reset(5, random.randint(-3, 3))
            yield
                       
    def reset(self, vx, vy):
        self.pos = (320 - 8, 240 - 8)
        self.vel = (vx, vy)

class Paddle(pysage.GameObject):
    def __init__(self, x, y, ball, side):
        pysage.GameObject.__init__(self, x, y, 16, 64)
        self.ball = ball
        self.side = side

    def add(self):
        pysage.addObject(self);
        pysage.runThread(self.think) 
        pysage.runThread(self.update)

         
    def update(self):
        while(1):
            if (self.y > 480 - 64):
                self.y = 480 - 64
                self.vy = 0            
                
            if (self.y < 0):
                self.y = 0
                self.vy = 0  
          
            if (self.collidesWith(self.ball)):
                if (self.side == "right"):
                    if (self.ball.vx < 0):
                        self.ball.reset(-4, random.randint(-3, 3))
                    elif (self.ball.x > self.x):
                        self.ball.vy = -self.ball.vy + (self.vy / 1.5)  
                    else:
                        self.ball.x = self.x - 16
                        self.ball.vel = (-self.ball.vx * 1.05, self.ball.vy + (self.vy / 1.5))

                elif (self.side == "left"):
                    if (self.ball.vx > 0):
                        self.ball.reset(4, random.randint(-3, 3))
                    elif (self.ball.x < self.x):
                        self.ball.vy = -self.ball.vy + (self.vy / 1.5)  
                    else:
                        self.ball.x = self.x + 16
                        self.ball.vel = (-self.ball.vx * 1.05, self.ball.vy + (self.vy / 1.5))
            yield
                        
    def think(self):
        while(1):
            nextypos = 0
            if (self.ball.vx != 0):
                nextypos = (self.ball.y + 8 + ((self.x - self.ball.x) / self.ball.vx)*self.ball.vy)

            if (nextypos < 0):
                nextypos = -nextypos
            if (nextypos > 480):
                nextypos = 960 - nextypos
            self.vy = maxabs(self.vy + (nextypos - self.y - 32) / 10.0, 4)
            yield (1.0/4.0)

ball = Ball(320 - 8, 240 - 8)
paddle1 = Paddle(40, 216, ball, "left")
paddle2 = Paddle(600 - 16, 216, ball, "right")

def main():
    pysage.initialize()

    ball.add()
    paddle1.add()
    paddle2.add()

    ball.reset(4, random.randint(-3, 3))

    
    pysage.start()
    pysage.cleanup()
    
    return
