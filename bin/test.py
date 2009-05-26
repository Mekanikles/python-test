'''py_function.py - Python source designed to '''
'''demonstrate the use of python embedding'''
import stackless
import pysage
import sage

import math
import random

def maxabs(value, maxvalue):
    if (abs(value) > maxvalue):
        return math.copysign(maxvalue, value);
    else:
        return value;

class Ball(sage.GameObject):
    def __init__(self, x, y):
        sage.GameObject.__init__(self, x, y, 16, 16)

    def update(self, time):
        pos = pysage.getPos(self)
        vel = pysage.getVel(self)
        
        if (pos[1] < 0):
            pysage.setPos(self, (pos[0], 0))
            pysage.setVel(self, (vel[0], -vel[1]))
            
        if (pos[1] > 480 - 16):
            pysage.setPos(self, (pos[0], 480 - 16))
            pysage.setVel(self, (vel[0], -vel[1]))
            
        if (pos[0] < 0):
            self.reset(-5, random.randint(-3, 3))
            
        if (pos[0] > 640 - 16):
            self.reset(5, random.randint(-3, 3))
                       
    def reset(self, vx, vy):
        pysage.setPos(ball, (320 - 8, 320 - 8))
        pysage.setVel(ball, (vx, vy))

class Paddle(sage.GameObject):
    def __init__(self, x, y, ball, side):
        sage.GameObject.__init__(self, x, y, 16, 64)
        self.ball = ball
        self.side = side
        
    def update(self, time):
        pos = pysage.getPos(self)
        vel = pysage.getVel(self)
        
        if (pos[1] > 480 - 64):
            pysage.setPos(self, (pos[0], 480 - 64))
            pysage.setVel(self, (vel[0], 0))            
            
        if (pos[1] < 0):
            pysage.setPos(self, (pos[0], 0))
            pysage.setVel(self, (vel[0], 0))  

                          
        if (pysage.isColliding(self, self.ball)):
            ballpos = pysage.getPos(self.ball)
            ballvel = pysage.getVel(self.ball)
   
            if (self.side == "right"):
                if (ballvel[0] < 0):
                    self.ball.reset(-5, random.randint(-3, 3))
                else:
                    pysage.setPos(self.ball, (pos[0] - 16, ballpos[1]))
                    pysage.setVel(self.ball, (-ballvel[0], ballvel[1] + (vel[1] / 1.5)))

            elif (self.side == "left"):
                if (ballvel[0] > 0):
                    self.ball.reset(5, random.randint(-3, 3))
                else:
                    pysage.setPos(self.ball, (pos[0] + 16, ballpos[1]))
                    pysage.setVel(self.ball, (-ballvel[0], ballvel[1] + (vel[1] / 1.5)))                               
                    
    def think(self):
        while(1):
            pos = pysage.getPos(self)
            vel = pysage.getVel(self)                 
            ballpos = pysage.getPos(ball)
            ballvel = pysage.getVel(ball)
                                  
            nextypos = (ballpos[1] + 8 + ((pos[0] - ballpos[0]) / ballvel[0])*ballvel[1])
            if (nextypos < 0):
                nextypos = -nextypos
            if (nextypos > 480):
                nextypos = 960 - nextypos
            pysage.setVel(self, (vel[0], maxabs(vel[1] + (nextypos - pos[1] - 32) / 40.0, 3)))
            pysage.sleepThread(1.0/20.0);

ball = Ball(320 - 8, 240 - 8)
paddle1 = Paddle(40, 216, ball, "left")
paddle2 = Paddle(600 - 16, 216, ball, "right")

def setup():
    print "Setting up game."

    pysage.initialize()

    sage.addObject(ball);
    sage.addObject(paddle1);
    sage.addObject(paddle2);
    
    sage.registerUpdate(paddle1.update);
    sage.registerUpdate(paddle2.update);
    sage.registerUpdate(ball.update);
    
    pysage.runThread(paddle1.think)
    pysage.runThread(paddle2.think)

    ball.reset(5, random.randint(-3, 3))

    return
