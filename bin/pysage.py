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
    stackless.run(10000000)

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
    
def initialize():
    def _update(currentTime):
        global _currentTime
        _currentTime = currentTime
        _tickTasklets(currentTime)
         
    sage.registerUpdate(_update)


def getPos(object):
    return (sage.getObjectPosX(object), sage.getObjectPosY(object))

def setPos(object, pos):
    sage.setObjectPosX(object, pos[0])
    sage.setObjectPosY(object, pos[1])

def getVel(object):
    return (sage.getObjectVelX(object), sage.getObjectVelY(object))

def setVel(object, vel):
    sage.setObjectVelX(object, vel[0])
    sage.setObjectVelY(object, vel[1])

def isColliding(obj1, obj2):
    return sage.objectsColliding(obj1, obj2)
    


# Scheduler running related functions.
