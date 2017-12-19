from controllerLib import *
robot, scene, group, zeroPose  = initRobot()
import time


print "OK"
while True:
	print np.degrees(robot.get_current_state().joint_state.position)
	time.sleep(0.02)