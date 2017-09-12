from __future__ import division
from visual import *
from visual.graph import *
scene.width = 600
scene.height = 760
## objects :
ceiling = box(pos=vector(0,0,0), size=(0.2,0.01,0.2))
ball = sphere(radius=0.025, color=color.yellow)
spring = cylinder(pos=ceiling.pos, color=color.orange, radius = 0.01)
ygraph = gcurve(color=ball.color)
xgraph = gcurve(color=color.red)
zgraph = gcurve(color=color.blue)
ball.trail = curve(color=ball.color)
## constants & data :
g = 9.8         ##units of kg m/s^2
ball.m = 0.45   ##units of kg
L0 = 0.10       ##units of meter
ks = 13.702    ##units of N/m
deltat = 1.125e-3   ##units of s
amp = 0.05      ##units of m
yeq = -L0 - ball.m*g/ks
#initial values:
ball.pos = vector(0.1,0.025,0.075)
ball.v = vector(0,0,0)
ball.p = ball.m*ball.v
spring.axis = ball.pos-ceiling.pos
##imporove the display
scene.autoscale = 0
scene.center = vector(0,yeq,0)
##loop begin :
t = 0
while t<60:
    rate(1/deltat)
##calculate force on ball by spring
    L = ball.pos-spring.pos
    Lhat = L/sqrt(L.x**2 + L.y**2 + L.z**2)
    F_magbspring = -ks*(sqrt(L.x**2 + L.y**2 + L.z**2) - L0)
    F_bspring = F_magbspring*Lhat
##calculate net force on ball
    F_b = vector(0,-ball.m*g,0)
    Fnet_b = F_b + F_bspring
##apply momentum principle
    ball.p = ball.p + Fnet_b*deltat
##update position
    ball.pos = ball.pos + (ball.p/ball.m)*deltat
    ygraph.plot(pos=(t,ball.pos.y))
    xgraph.plot(pos=(t,ball.pos.x))
    zgraph.plot(pos=(t,ball.pos.z))
    ball.trail.append(pos=ball.pos)
##update axis of spring
    spring.axis = ball.pos - ceiling.pos
##update time
    t = t+deltat
