from __future__ import division
from visual import *
from visual.graph import *
scene.width = 600
scene.height = 760
## objects :
ceiling = box(pos=vector(0,0,0), size=(0.2,0.01,0.2))
ball = sphere(radius=0.025, color=color.yellow)
spring = cylinder(pos=ceiling.pos, color=color.orange, radius = 0.01)
ygraph = gcurve(color=color.yellow)
xgraph = gcurve(color=color.red)
zgraph = gcurve(color=color.blue)
ball.trail = curve(color=ball.color)
gdisplay(xtitle='Seconds', ytitle='Joules', x=500,y=0,width=800,height=500)
Kgraph = gcurve(color=color.magenta)
Ugraph = gcurve(color=color.blue)
Etotal = gcurve(color=color.red)

## constants & data :
g = 0         ##units of kg m/s^2
ball.m = 7.7   ##units of kg
L0 = 0       ##units of meter
ks = 17.5   ##units of N/m
deltat = 0.0001   ##units of s
amp = 0.09      ##units of m
yeq = -L0 - ball.m*g/ks
b=1.8           ##units of kg/s
#initial values:
ball.pos = vector(0,0.2,0)
ball.v = vector(0,0,0)
ball.p = ball.m*ball.v
spring.axis = ball.pos-ceiling.pos
##imporove the display
scene.autoscale = 0
scene.center = vector(0,yeq,0)
##loop begin :
t = 0
while t<2.2:
    rate(1/deltat)
##calculate force on ball by spring
    L = ball.pos-spring.pos
    Lhat = L/sqrt(L.x**2 + L.y**2 + L.z**2)
    F_magbspring = -ks*(sqrt(L.x**2 + L.y**2 + L.z**2) - L0)
    F_bspring = F_magbspring*Lhat
##calculate net force on ball
    F_b = vector(0,-ball.m*g,0)
    F_ballliquid = -b*ball.p/ball.m
    Fnet_b = F_b + F_bspring + F_ballliquid
##apply momentum principle
    ball.p = ball.p + Fnet_b*deltat
##update position
    ball.pos = ball.pos + (ball.p/ball.m)*deltat
    #ygraph.plot(pos=(t,ball.pos.y))
#    xgraph.plot(pos=(t,ball.pos.x))
#    zgraph.plot(pos=(t,ball.pos.z))

    ball.trail.append(pos=ball.pos)
    pmag = mag(ball.p)         #craft's mag momentum
    K = 0.5*ball.m*((pmag/ball.m)**2)
    U = 0.5*ks*(mag(spring.axis)-L0)**2
    E = K + U
    Kgraph.plot(pos=(t,K))
    Ugraph.plot(pos=(t,U))
    Etotal.plot(pos=(t,E))
##update axis of spring
    spring.axis = ball.pos - ceiling.pos
##update time
    t = t+deltat
