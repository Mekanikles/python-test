# -*- coding: cp1252 -*-
import sage

import stackless

## Utilities for tasklets.
_yieldChannel = stackless.channel()
_sleepingTasklets = []
_currentTime = 0

def _checkSleepingTasklets():
    """ Awaken all tasklets which are due to be awakened. """

    while len(_sleepingTasklets):
        endTime = _sleepingTasklets[0][0]
        if endTime > _currentTime:
            break
        channel = _sleepingTasklets[0][1]
        del _sleepingTasklets[0]
        # We have to send something, but it doesn't matter what as it is not used.
        channel.send(None)

def _tickTasklets(currentTime):
    """ Run one frame of tasklets. """
    
    # Only schedule as many tasklets as there are waiting when
    # we start.  This is because some of the tasklets we awaken
    # may BeNice their way back onto the channel.  Well they
    # would
    n = -_yieldChannel.balance
    while n > 0:
        _yieldChannel.send(None)
        n -= 1

    _checkSleepingTasklets()

    # Run any tasklets which need to be scheduled.  As long as the BeNice and
    # Sleep callers do not use schedule they should never be in the scheduler
    # at this point, but rather back in the yield channel or on a sleep channel.
    interruptedTasklet = stackless.run(1000000)
    if interruptedTasklet:
        print "Warning: Tasklet", interruptedTasklet, "was interrupted, make sure it does not busy loop."
        interruptedTasklet.insert()

def yieldThread():
    """ Signal that the tasklet can be interrupted. """
    _yieldChannel.receive()

def sleepThread(secs):
    """ Put the current tasklet to sleep for a number of seconds. """
    channel = stackless.channel()
    endTime = _currentTime + secs
    _sleepingTasklets.append((endTime, channel))
    _sleepingTasklets.sort()
    # Block until we get sent an awakening notification.
    channel.receive()

def runThread(function):
    stackless.tasklet(function)()


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
    def _update(currentTime):
        global _currentTime
        _currentTime = currentTime
        _tickTasklets(currentTime)
         
    sage.registerUpdateFunction(_update)

def addObject(object):
    sage.addObject(object)
    
def removeObject(object):
    sage.removeObject(object)
    
def listenForControllerInput(object):
    filtr = sage.InputData(0,0,0)
    sage.registerInputListener(object, filtr)
    

# Scheduler running related functions.
