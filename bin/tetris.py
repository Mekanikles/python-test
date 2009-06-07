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

             
class Shape:
    def __init__(self, x, y, shape):
        self.x = x
        self.y = y
        self.shape = shape
        self.blocks = [pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16),
                    pysage.GameObject(x, y, 16, 16)]   
    def add(self):
        for i in self.blocks:
            pysage.addObject(i)
        pysage.runThread(self.update)
    def checkCollision(self):
        for i in self.blocks:
            for p in lockedblocks:
                if (i.collidesWith(p)):
                    return True
        return False
        
    def positionBlocks(self):
        for i in range(0, 4):
            self.blocks[i].pos = (self.x + shapedata[self.shape][i][0], self.y + shapedata[self.shape][i][1])
    def lockPosition(self):
        for i in self.blocks:
            lockedblocks.append(i)
        
    def update(self):
        while(1):
            self.y += 2
            self.positionBlocks()
            if (self.checkCollision()):
                self.y = math.floor(self.y / 16.0) * 16
                self.positionBlocks()
                break
            yield
        self.lockPosition()
    def remove(self):
        for i in self.blocks:
            pysage.removeObject(i)
        del self

def spawnShape(inputData):
    piece = Shape(random.randint(0, 39) * 16, 0, random.randint(0, 6))
    piece.add()

def main():
    pysage.initialize()

    floor = pysage.GameObject(0, 480, 640, 16)
    pysage.addObject(floor)
    lockedblocks.append(floor)
    pysage.listenForControllerInput(spawnShape)

    pysage.start()
    pysage.cleanup()
    
