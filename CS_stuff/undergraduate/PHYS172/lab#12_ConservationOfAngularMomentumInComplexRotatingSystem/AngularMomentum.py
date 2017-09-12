from __future__ import division
from visual import *

scene.height=1000
scene.center=(0,5,0)
scene.range=(12,12,12)

#Constants
fscale=0.1
g=9.8

#create disk
R=1
disk=sphere(pos=(0,0,0), radius=R, color=color.yellow)
disk.m=1
I=0.5*disk.m*R*R


#set initial conditions

disk.L=vector(0,0,0)  #If the yo-yo is not initially spinning, what is the angular momentum?

disk.p=vector(0,0,0) #yo-yo is not moving initially
x1=0  # length of string pulled off disk
theta=0

Tension_dH = vector(0,disk.m*g,0) # Use momentum principle to determine value to make yo-yo hover

#create string and Force vector arrow and pointer 
string = curve(pos=[disk.pos+vector(-R,0,0),disk.pos+vector(-R,2,0)], radius=R/20)
disk.force = arrow(pos=disk.pos+vector(-R,2,0), axis=fscale*Tension_dH, shaftwidth=R/10, color=color.red)
pointer = arrow(pos=disk.pos, axis=(1.3*R,0,0), shaftwidth=R/10, color=color.cyan)
deltat = 0.001
t=0

scene.autoscale=0
while t < 3:
    rate(200)

    r= vector(-R,0,0)  # vector from rotation axis to string contact at x=-R

    Tension_dH = vector(0,disk.m*g,0)  # Use momentum principle to determine value to make yo-yo hover

    torque_dH = cross(r,Tension_dH) # Definition of torque 
    F_dE = vector(0,-disk.m*g,0)

    Fnet_d = Tension_dH + F_dE
    
    disk.L = disk.L + torque_dH*deltat  #update angular momentum using torque
    omega = disk.L/I # how do you get angular velocity vector omega from the vector disk.L?
    theta = theta - deltat*mag(omega)/2 # Note angular position is not a vector ... which component of omega is nonzero?
    disk.p = disk.p + Fnet_d*deltat  #update disk's linear momentum
    disk.pos = disk.pos + disk.p/disk.m*deltat  #update position of the disk's center of mass
    v=-omega.z*R # The linear velocity of the string
    x1=x1+v*deltat  #The length of string pulled off
    
    string.pos=[disk.pos+vector(-R,0,0),disk.pos+vector(-R,2+x1,0)]
    disk.force.pos=disk.pos+vector(-R,2+x1,0)
# Updates pointer position and makes disk spin    
    pointer.pos=disk.pos
    x=R*cos(theta)
    y=R*sin(theta)
    pointer.axis=1.3*vector(x,y,0)
    disk.axis=vector(x,y,0)
    
    t=t+deltat
print "linear velocity of string"
print v
    
