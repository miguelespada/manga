#!/usr/bin/env python3
from OSC import OSCServer, OSCClient, OSCMessage
import sys
from time import sleep
from random import shuffle
from random import random


import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("8.8.8.8", 80))
ip = s.getsockname()[0]
s.close()

from controllerLib import *
robot, scene, group, zeroPose  = initRobot()

HOST = (ip, 7000)
server = OSCServer( HOST  )
server.timeout = 0
run = True

# this method of reporting timeouts only works by convention
# that before calling handle_request() field .timed_out is 
# set to False
def handle_timeout(self):
    self.timed_out = True

# funny python's way to add a method to an instance of a class
import types
server.handle_timeout = types.MethodType(handle_timeout, server)

def zero_callback(path, tags, args, source):

    client = OSCClient()
    client.connect( (source[0], 8001) )
    client.send( OSCMessage("/busy" ) )
    print "Go Zero"
    goToZero()

    client = OSCClient()
    client.connect( (source[0], 8001) )
    client.send( OSCMessage("/noBusy" ) )

def test_callback(path, tags, args, source):

    client = OSCClient()
    client.connect( (source[0], 8001) )
    client.send( OSCMessage("/busy" ) )
    print "Do test"
    pushTwo((2, 4), (2, 5))

    client = OSCClient()
    client.connect( (source[0], 8001) )
    client.send( OSCMessage("/noBusy" ) )

def all_callback(path, tags, args, source):
    if args[0] == 1.0:  pushAll()

def quit_callback(path, tags, args, source):
    # don't do this at home (or it'll quit blender)
    global run
    run = False

def stop_callback(path, tags, args, source):
    group.stop()

def trajectory_callback(path, tags, args, source):
    trajectory = args[0]
    tokens = trajectory.split(";")
    tPoints = []
    for t in tokens[:-1]:
        tPoints.append(map(lambda x: int(x), t.split(",")))

    client = OSCClient()
    client.connect( (source[0], 8001) )
    client.send( OSCMessage("/busy" ) )

    shuffle(tPoints)
    print "Executing", tPoints
    createPath(tPoints)
   
    if random() > 0.5:
        b = 0
        if random() > 0.5:
            b = 1
        print "Push extra", b
        pushButtonExtra(b, 0.5 + random() * 3)


    client = OSCClient()
    client.connect( (source[0], 8001) )
    client.send( OSCMessage("/noBusy" ) )
    
def ping_callback(path, tags, args, source):
    try:
        client = OSCClient()
        client.connect( (source[0], 8001) )
        client.send( OSCMessage("/ping" ) )
    except Exception as e:
        print e

server.addMsgHandler( "/1/push4",  trajectory_callback )
server.addMsgHandler( "/1/push5", stop_callback )
server.addMsgHandler( "/1/push6", quit_callback )
server.addMsgHandler( "/1/push1",  zero_callback )
server.addMsgHandler( "/zero",  zero_callback )
server.addMsgHandler( "/1/push2",  test_callback )
server.addMsgHandler( "/test",  test_callback )
server.addMsgHandler( "/path",  trajectory_callback )
server.addMsgHandler( "/1/push3",  all_callback )

server.addMsgHandler( "/ping",  ping_callback )

# user script that's called by the game engine every frame
def each_frame():
    # clear timed_out flag
    server.timed_out = False
    # handle all pending requests then return
    while not server.timed_out:
        server.handle_request()


print "Listening ", HOST 
# simulate a "game engine"
try:
    while run:
        sleep(0.1)
        # call user script
        each_frame()
    raise KeyboardInterrupt
except KeyboardInterrupt:
    pass

print "Bye!"
print "Close rospy"
rospy.signal_shutdown("final")
server.close()