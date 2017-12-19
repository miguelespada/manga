import sys
import copy
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
import math
from geometry_msgs.msg import PoseStamped
import time
from tf.transformations import euler_from_quaternion, quaternion_from_euler
import numpy as np
from moveit_msgs.msg import Constraints, OrientationConstraint



DELTA_DISTANCE = -0.02
NORMAL_Z = 0.08
DELTA_ALPHA = 0.035
PUSH_TOLERANCE = 0.001

def initRobot():
    global zeroPose, rospy
    global robot, scene, group
    moveit_commander.roscpp_initialize(sys.argv)
    time.sleep(0.5)
    rospy.init_node('move_group_python_interface',anonymous=True,disable_signals=True)
    time.sleep(0.5)
    robot = moveit_commander.RobotCommander()
    if not("manipulator" in robot.get_group_names()):
        print "ERROR! robot not correctly initilized"
        return
    else:
        print "Manipulator detected"

    scene = moveit_commander.PlanningSceneInterface()
    group = moveit_commander.MoveGroupCommander("manipulator")
    scene = moveit_commander.PlanningSceneInterface()
    robot = moveit_commander.RobotCommander()
    if robot.get_planning_frame() != "/world":
        print "ERROR! robot not correctly initilized"
        return 
    else:
        print "World detetected"

    initialJoinValues = [77.32632695,  -69.73220526,  121.29976102, -141.59751593, -90.06095192,  168.36293361]
    time.sleep(1)

    print "Initial Join values should be", initialJoinValues
    print "Actual values are", np.degrees(robot.get_current_state().joint_state.position)
    group.set_goal_position_tolerance(0.00001)
    group.allow_looking(True)
    group.allow_replanning(True)

    print "Loading points"
    loadMatrix()
    print "Setting Scene"
   # setScene()

    print "Definning zeroPose"
    zeroPose = group.get_current_pose().pose
    zeroPose.position.x = 0.0
    zeroPose.position.y = 0.5
    zeroPose.position.z = 0.1

    zeroPose.orientation.x = 0.5
    zeroPose.orientation.y = 0.5
    zeroPose.orientation.z = -0.5
    zeroPose.orientation.w = 0.5

    print "Loading extra buttons"
    loadExtraButtons()
    return robot, scene, group, zeroPose

def shutdown():
    rospy.signal_shutdown("Closing rospy")

class Point:
    def fromString(self, s):
        tokens = s.split(',')
        self.cord_x = int(tokens[0])
        self.cord_y = int(tokens[1])
        self.x = float(tokens[2])
        self.y = float(tokens[3])
        self.deltaDistance = float(tokens[4])
        self.deltaAlpha = float(tokens[5])
        self.tolerance = float(tokens[6])
        
    def getPos(self):
        h = math.sqrt(self.x*self.x + self.y*self.y)
        cosAlpha = self.x / h

        alpha = math.acos(cosAlpha)
        alpha += self.deltaAlpha
        
        x2 = (h + self.deltaDistance) * math.cos(alpha)
        y2 = (h + self.deltaDistance) * math.sin(alpha)
        return (x2, y2) 
    
def loadPoints():
    global points
    f = open("geometria.txt", 'r')
    lines = f.readlines()
    points = []
    for l in lines:
        if "Punto en (" in l:
            values = l.split("(")[1].split(")")[0].split(",")[0:2]
            points.append(map(lambda x: -float(x) / 1000.0, values))
    print "Total points loaded: ", len(points)       

#loadPoints()
#generateMatrixFromRhino()

def generateMatrixFromRhino():
    w, h = 12, 3;
    pArray = [[0 for x in range(w)] for y in range(h)] 

    for r in range(3):
        for c in range(12):
            p = 35 - (c*3 + r)
            pArray[r][c] = points[p] + [DELTA_DISTANCE, DELTA_ALPHA, PUSH_TOLERANCE]

    ss = "x,y,pos_x,pos_y,DELTA_DISTANCE,DELTA_ALPHA,PUSH_TOLERANCE\n"
    for r in range(3):
        for c in range(12):
            ss += "%d,%d," % (r, c)
            for v in pArray[r][c]:
                ss += "%.6f," % v
            ss = ss[:-1]
            ss += "\n"

    f = open("space.csv", "w")
    f.write(ss)
    f.close()

def loadMatrix():
    global matrix
    i = 0
    f = open("space.csv",'r')
    w, h = 12, 3;
    matrix = [[0 for x in range(w)] for y in range(h)] 
    for l in f.readlines()[1:]:
        p = Point()
        p.fromString(l)
        i += 1
        matrix[p.cord_x][p.cord_y] = p
    print "Total points loaded: ", i
    return matrix

def loadExtraButtons():
    global extra1, extra2
    extra1data = "0,0,0.2,0.22,0.010000,0.01600,0.007000"
    extra1 = Point()
    extra1.fromString(extra1data)

    extra2data = "0,0,-0.2,-0.2,0.020000,0.05500,0.007000"
    extra2 = Point()
    extra2.fromString(extra2data)


def goToPose(pose, step=0.05):
    waypoints = [group.get_current_pose().pose]
    waypoints.append(pose)
    (plan, fraction) = group.compute_cartesian_path(
                         waypoints,   # waypoints to follow
                         step,        # eef_step
                         0.0)         # jump_threshold

        #plan = group.retime_trajectory(robot.get_current_state(), plan, 0.08)
    if fraction == 1.0: 
        success = group.execute(plan)
        if not(success): print "Error"
    else:
        print fraction



def goToPoint(p, z = NORMAL_Z):
    pose = copy.deepcopy(zeroPose)
    pose.position.x = p.getPos()[0]
    pose.position.y = p.getPos()[1]
    pose.position.z = z
    goToPose(pose)
    return pose

def goSlowlyToPoint(p, z = NORMAL_Z):
    pose = copy.deepcopy(zeroPose)
    pose.position.x = p.getPos()[0]
    pose.position.y = p.getPos()[1]
    pose.position.z = z
    goToPose(pose, step=0.0001)
    return pose

def pushInPlace(pose, tol = PUSH_TOLERANCE):
    # Tolerancia [-0.002, 0.004]
    waypoints = [group.get_current_pose().pose]
    waypoints.append(copy.deepcopy(pose))
    pose.position.z = 0.055 + tol 
    waypoints.append(copy.deepcopy(pose))
    pose.position.z = 0.1
    waypoints.append(copy.deepcopy(pose))
    (plan, fraction) = group.compute_cartesian_path(
                         waypoints,   # waypoints to follow
                         0.0003,        # eef_step
                         0.0)         # jump_threshold
    if fraction == 1.0: 
        success = group.execute(plan)
        if not(success): print "Error"
    else:
        print fraction

def setScene():
    scene.remove_world_object("floor")
    scene.remove_world_object("wall")
    scene.remove_attached_object("box")

    p = PoseStamped()
    p.header.frame_id = robot.get_planning_frame()
    p.pose.position.x = 0.
    p.pose.position.y = -0.8
    p.pose.position.z = 0.1
    scene.add_box("obstacle", p, (0.2, 0.4, 0.2))
    scene.remove_world_object("obstacle")

    p = PoseStamped()
    p.header.frame_id = robot.get_planning_frame()
    p.pose.position.x = 0
    p.pose.position.y = 0
    p.pose.position.z = -0.15
    scene.add_box("floor", p, (2, 2, 0.2))


    p = PoseStamped()
    p.header.frame_id = robot.get_planning_frame()
    p.pose.position.x = 0
    p.pose.position.y = -0.4
    p.pose.position.z = 0
    scene.add_box("wall", p, (2, 0.2, 2))

    p = PoseStamped()
    p.header.frame_id = robot.get_planning_frame()
    p = robot.get_link("ee_link").pose()
    p.pose.position.z -= 0.045
   # scene.attach_box(robot.get_link("ee_link").name(), "box", p, size= (0.086, 0.05, 0.05))


def pushAll():
    goToPose(zeroPose)
    for i in range(12):
        for j in range(3):
            pushOne(j, i)
            time.sleep(0.1)
    goToPose(zeroPose)

def pushExtra():
    goToPose(zeroPose)
    pose = goToPoint(extra1)
    time.sleep(0.1)
    pushAndHold(pose, 1, extra1.tolerance)
    time.sleep(0.1)
    goToPose(zeroPose)
    pose = goToPoint(extra2)
    time.sleep(0.1)
    pushAndHold(pose, 1, extra2.tolerance)
    time.sleep(0.1)
    goToPose(zeroPose)

def pushButtonExtra(b, t):
    goToPose(zeroPose)
    if b == 0:
        pose = goToPoint(extra1)
        time.sleep(0.1)
        pushAndHold(pose, t, extra1.tolerance)
        time.sleep(0.1)
    if b == 1:
        pose = goToPoint(extra2)
        time.sleep(0.1)
        pushAndHold(pose, t, extra2.tolerance)
        time.sleep(0.1)
    goToPose(zeroPose)


def pushAndHold(pose, t = 1,  tol = PUSH_TOLERANCE):
    # Tolerancia [-0.002, 0.004]
    waypoints = [group.get_current_pose().pose]
    waypoints.append(copy.deepcopy(pose))
    pose.position.z = 0.055 + tol 
    waypoints.append(copy.deepcopy(pose))
    
    (plan, fraction) = group.compute_cartesian_path(
                         waypoints,   # waypoints to follow
                         0.0003,        # eef_step
                         0.0)         # jump_threshold
    if fraction == 1.0: 
        success = group.execute(plan)
        if not(success): print "Error"
    else:
        print fraction
    
    time.sleep(t)
    
    waypoints = []
    pose.position.z = 0.1
    waypoints.append(copy.deepcopy(pose))
    (plan, fraction) = group.compute_cartesian_path(
                         waypoints,   # waypoints to follow
                         0.0003,        # eef_step
                         0.0)         # jump_threshold
    if fraction == 1.0: 
        success = group.execute(plan)
        if not(success): print "Error"
    else:
        print fraction


def pushTwo((x0, y0), (x1, y1)):
    loadMatrix()
    before = time.time()
    pushOne(x0, y0)
    time.sleep(0.1)
    pushOne(x1, y1)
    print "Total time", time.time() - before
    
def pushOne(x, y):
    p = matrix[x][y]
    pose = goToPoint(p)
    time.sleep(0.1)
    pushInPlace(pose, p.tolerance)
    
def createPath(coords, last = (2, 6)):
    global matrix
    loadMatrix()
    before = time.time()
    for coord in coords:
        if abs(last[0] - coord[0]) +  abs(last[1] - coord[1]) > 6:
            midX =  max(last[0], coord[0]) - abs(last[0] - coord[0]) / 2
            midY = max(last[1], coord[1]) - abs(last[1] - coord[1]) / 2
            goToPoint(matrix[midX][midY])
            time.sleep(0.1)
        pushOne(coord[0], coord[1])
        last = coord
    print "Length", len(coords)
    print "Total time", time.time() - before
    goToZero()
    
def addConstrains():
    pose = group.get_current_pose()
    constraint = Constraints()
    constraint.name = "downRight"
    orientation_constraint = OrientationConstraint()
    orientation_constraint.header = pose.header
    orientation_constraint.link_name = group.get_end_effector_link()
    orientation_constraint.orientation = pose.pose.orientation
    orientation_constraint.absolute_x_axis_tolerance = 0.1
    orientation_constraint.absolute_y_axis_tolerance = 0.1
    orientation_constraint.absolute_z_axis_tolerance = 0.1
    #orientation_constraint.absolute_z_axis_tolerance = 3.14 #ignore this axis
    orientation_constraint.weight = 1

    constraint.orientation_constraints.append(orientation_constraint)
    group.set_path_constraints(constraint)
    
def goToZero():
    plan = goToPose(zeroPose, 0.0001)
    print "Adding Constraints"
    addConstrains()
    return plan