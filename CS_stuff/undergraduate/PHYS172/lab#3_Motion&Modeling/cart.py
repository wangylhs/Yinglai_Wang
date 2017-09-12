from __future__ import division
from visual import *
from visual.graph import *

scene.y = 400 #move animation window down 400 pixels from top of screen

track = box(pos=vector(0,-0.05, 0), size=(2.0,0.05, 0.10))

cart = box(pos=vector(-0.5,0,0), size=(0.1,0.04,0.06), color=color.green)

cart.m = 0.80
cart.v = vector(0.7,0,0)
cart.p = cart.m*cart.v
deltat = 0.01
t = 0

#position vs time graph
gdisplay(xtitle='Time', ytitle='Position', x=500, y=0, width=600, height=300)
posgraph = gcurve(color=color.red) # to make position graph
#momentum vs time graph
gdisplay(xtitle='Time', ytitle='Momentum', x=500, y=300, width=600, height=300)
pgraph = gcurve(color=color.green)
#netForce vs time graph
gdisplay(xtitle='Time', ytitle='Fnet', x=500, y=600, width=600, height=300)
Fgraph = gcurve(color=color.blue)


while t<3.0:
    cart.pos = cart.pos + (cart.p/cart.m)*deltat
    t = t + deltat
    #rate(10)
    Fnet = vector(-0.4,0,0)
    cart.p = cart.p + Fnet*deltat
    #print("t=", t, "cart.p=", cart.p)
    posgraph.plot( pos=(t, cart.pos.x) )
    pgraph.plot( pos=(t, cart.p.x))
    Fgraph.plot( pos=(t, Fnet.x))
