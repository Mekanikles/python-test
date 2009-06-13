# -*- coding: cp1252 -*-
from __future__ import generators
from collections import deque

import sage

class _Thread():
    def __init__(self, func):
        self.nexttick = 0;
        self.generator = func()

class _Scheduler():
    def __init__(self):
        self._runningThreads = deque()
        
    def runFrame(self, currentTime):
        for i in range(len(self._runningThreads)):
            try:
                thread = self._runningThreads[0]
                if (currentTime >= thread.nexttick):
                    sleep = thread.generator.next()
                    if (sleep > 0):
                        thread.nexttick = currentTime + sleep
                self._runningThreads.rotate(-1)
            except StopIteration:
                del self._runningThreads[0]
            except IndexError:
                # allow internal exception to propagate
                if len(self._runningThreads) > 0: raise

    def addThread(self, thread):
        self._runningThreads.append(thread)

scheduler = _Scheduler()
        
class GameObject(sage.GameObject):
    def __init__(self, x, y, w, h):
        sage.GameObject.__init__(self, x, y, w, h)

    def _getPos(self):return (sage.getObjectPosX(self), sage.getObjectPosY(self))
    def _getVel(self): return (sage.getObjectVelX(self), sage.getObjectVelY(self))
    def _setPos(self, pos):
        sage.setObjectPosX(self, pos[0])
        sage.setObjectPosY(self, pos[1])
    def _setVel(self, vel):
        sage.setObjectVelX(self, vel[0])
        sage.setObjectVelY(self, vel[1])
    def _getX(self): return sage.getObjectPosX(self)
    def _getY(self): return sage.getObjectPosY(self) 
    def _setX(self, x): sage.setObjectPosX(self, x)
    def _setY(self, y): sage.setObjectPosY(self, y)
    def _getVX(self): return sage.getObjectVelX(self)
    def _getVY(self): return sage.getObjectVelY(self) 
    def _setVX(self, vx): sage.setObjectVelX(self, vx)
    def _setVY(self, vy): sage.setObjectVelY(self, vy)
    pos = property(_getPos, _setPos)
    vel = property(_getVel, _setVel)   
    x = property(_getX, _setX)
    y = property(_getY, _setY)
    vx = property(_getVX, _setVX)
    vy = property(_getVY, _setVY)
    
    def collidesWith(obj1, obj2):
        return sage.objectsColliding(obj1, obj2)

def initialize():
    # Import Psyco if available
    try:
        import psyco
        psyco.full()
    except ImportError:
        pass
    sage.initialize()
    sage.registerUpdateListener(scheduler.runFrame)

    
def start():
    sage.run()
    
def cleanup():
    sage.terminate()


def runThread(function):
    scheduler.addThread(_Thread(function))

def addObject(object, type):
    sage.addObject(object, type)
    
def removeObject(object):
    sage.removeObject(object)
    
def listenForControllerInput(function):
    filtr = sage.InputData(0,0,0)
    sage.registerInputListener(function, filtr)

def listenForCollisionOnObject(function, object):
    filtr = sage.CollisionData(-1, -1, object, 0)
    sage.registerCollisionListener(function, filtr)

def listenForCollisionBetweenObjects(function, object1, object2):
    filtr = sage.CollisionData(-1, -1, object1, object2)
    sage.registerCollisionListener(function, filtr)

def listenForCollisionOnType(function, type):
    filtr = sage.CollisionData(type, -1, 0, 0)
    sage.registerCollisionListener(function, filtr)
    
def listenForCollisionBetweenTypes(function, type1, type2):
    filtr = sage.CollisionData(type1, type2, 0, 0)
    sage.registerCollisionListener(function, filtr)

def enableCollision(type1, type2):
    sage.enableCollisionCheck(type1, type2)

def createNewObjectType():
    return creatNewObjectType()
