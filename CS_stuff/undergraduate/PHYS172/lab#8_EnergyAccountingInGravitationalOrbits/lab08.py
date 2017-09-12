from __future__ import division
from visual import *
from visual.graph import *
##objects:
Earth = sphere(pos=vector(0,0,0), radius=6.4e6, color=color.cyan)
craft = sphere(pos=vector(-10*Earth.radius,0,0), radius=1e6, color=color.yellow)
gdisplay(xtitle='Seconds', ytitle='Joules', x=500,y=0, width=800, height=500)
Kgraph = gcurve(color=color.magenta)
Ugraph = gcurve(color=color.yellow)
Etotal = gcurve(color=color.red)
Wgraph = gcurve(color=color.cyan)
#constant & data:
W_oncraft = 0
G = 6.7e-11
Earth.m = 6e24
craft.m = 15e3
craft.v = vector(0,3544.36171969,0)     #units of m/s
craft.p = craft.m*craft.v   #units of kg m/s
r_cE = craft.pos - Earth.pos
rmag_cE = sqrt(r_cE.x**2 + r_cE.y**2 + r_cE.z**2)
Fmag_cE = G*Earth.m*craft.m/(rmag_cE**2)
rhat_cE = r_cE/rmag_cE
F_cE = -Fmag_cE*rhat_cE
Fnet_c = F_cE
Fscale = rmag_cE/Fmag_cE
v = sqrt(2*G*Earth.m/rmag_cE)
print v
#scene.autoscale=0
#scene.center = vector(2e8,0,0)
t = 0           #units of seconds
deltat = 1     #units of seconds
trail = curve(color=craft.color)     #adds a trail object with no points
while t< 4*24*60*60:
    rate(50000)
    r_cE = craft.pos - Earth.pos
    rmag_cE = sqrt(r_cE.x**2 + r_cE.y**2 + r_cE.z**2)
    rhat_cE = r_cE/rmag_cE
    Fmag_cE = G*Earth.m*craft.m/(rmag_cE**2)
    F_cE = -Fmag_cE*rhat_cE
    
    Fnet_c = F_cE
    craft.p = craft.p + Fnet_c*deltat
    craft.pos = craft.pos + (craft.p/craft.m)*deltat
    trail.append(pos=craft.pos)   #adds a point at the new craft position
    pmag = mag(craft.p)         #craft's mag momentum
    K = 0.5*craft.m*((pmag/craft.m)**2)
    U = -G*craft.m*Earth.m/rmag_cE
    E = K + U
    deltar = (craft.p/craft.m)*deltat
    W_interval = Fnet_c.x*deltar.x + Fnet_c.y*deltar.y + Fnet_c.z*deltar.z
    W_oncraft = W_oncraft + W_interval
    Wgraph.plot(pos=(t,W_oncraft))
    #Kgraph.plot(pos=(t,K))
    Ugraph.plot(pos=(t,U))
    Etotal.plot(pos=(t,E))
    
    t = t + deltat
