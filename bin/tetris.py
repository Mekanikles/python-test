import pysage

import math
import random
  
shapedata = [[[-16, -16], ##S-shape
              [-16, 0],
              [0, 0],
              [0, 16]],

             [[0, -32], ##Mirrored S-shape
              [0, -16],
              [0, 0],
              [0, 16]],
             
             [[0, -16], ##Box-shape
              [0, 0],
              [-16, 0],
              [-16, 16]],
             
             [[-16, -16], ##I-shape
              [0, -16],
              [-16, 0],
              [0, 0]],
             
             [[0, -32], ##L-shape
              [0, -16],
              [0, 0],
              [-16, 0]],
             
             [[-16, -32], ##Mirrored L-shape
              [-16, -16],
              [-16, 0],
              [0, 0]],
             
             [[-16, -16], ##T-shape
              [0, -16],
              [16, -16],
              [0, 0]]]

lockedblocks = []

# Object types
TYPE_FLOOR = 0
TYPE_SHAPE = 1
TYPE_BLOCK = 2

callCount = 0
            
class Shape:
    def __init__(self, x, y, shape):
        self.x = x
        self.y = y
        self.shape = shape
        self.blocks = [pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16)]
        self.inair = True
    def add(self):
        for i in self.blocks:
            pysage.addObject(i, TYPE_SHAPE)
            pysage.listenForCollisionOnObject(self.handleCollision, i)
        pysage.runThread(self.update)

    def handleCollision(self, data):
        global callCount
        callCount+=1
        if (self.inair):
            self.inair = False
            self.y = math.floor(self.y / 16.0) * 16
            self.positionBlocks()
            self.lockPosition()
            
    def positionBlocks(self):
        for i in range(0, 4):
            self.blocks[i].pos = (self.x + shapedata[self.shape][i][0], self.y + shapedata[self.shape][i][1])

    def lockPosition(self):
        for i in self.blocks:
            lockedblocks.append(i)
            pysage.removeObject(i)
            pysage.addObject(i, TYPE_BLOCK)
    
    def update(self):
        while(self.inair):
            self.y += 4
            self.positionBlocks()
            yield
        
    def remove(self):
        for i in self.blocks:
            pysage.removeObject(i)
        del self

def spawnShape(inputData):
    piece = Shape(random.randint(0, 39) * 16, -64, random.randint(0, 6))
    piece.add()

def callCounter():
    while (1):
        global callCount
        print "Pythoncalls/sec:", callCount
        callCount = 0
        yield 1

def main():
    pysage.initialize()


    pysage.enableCollision(TYPE_SHAPE, TYPE_FLOOR)
    pysage.enableCollision(TYPE_SHAPE, TYPE_BLOCK)

    floor = pysage.GameObject(0, 480, 640, 16)
    pysage.addObject(floor, TYPE_FLOOR)
    lockedblocks.append(floor)
    pysage.listenForControllerInput(spawnShape)

    pysage.runThread(callCounter)

    pysage.start()
    pysage.cleanup()
    
