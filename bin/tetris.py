import pysage

import math
import random

class Shape:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.box = [pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16)]   
    def add(self):
        for i in self.box:
            pysage.addObject(i)
        pysage.runThread(self.update)
    def positionBlocks(self):
        self.box[0].pos = (self.x - 16, self.y - 16)
        self.box[1].pos = (self.x - 16, self.y)
        self.box[2].pos = (self.x, self.y)
        self.box[3].pos = (self.x, self.y + 16)

    def update(self):
        while(self.y < 448):
            self.y += 2
            self.positionBlocks()
            pysage.yieldThread()
        self.remove()
    def remove(self):
        for i in self.box:
            pysage.removeObject(i)
        del self

def spawnShapes():
    while(1):
        piece = Shape(random.randint(16, 624), 0)
        piece.add()
        pysage.sleepThread(1.0/2.0)

def setup():
    print "Setting up game."
    pysage.initialize()

    pysage.runThread(spawnShapes)
    
