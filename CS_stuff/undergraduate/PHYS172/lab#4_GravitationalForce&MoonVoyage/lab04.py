from __future__ import division
from visual import *

Earth = sphere(pos=vector(0,0,0), radius=6.4e6, color=color.cyan)
craft = sphere(pos=vector(-10*Earth.radius,0,0), radius=1e6, color=color.yellow)
Moon = sphere(pos=vector(4e8,0,0), radius=1.75e6, color=color.white)
Moon.m = 7e22               #units of kg
G = 6.7e-11                 #units of N m^2 / kg^2
Earth.m = 6e24              #units of kg
craft.m = 15e3              #units of kg
craft.v = vector(0,3.3e3,0)     #units of m/s
craft.p = craft.m*craft.v   #units of kg m/s
r_cE = craft.pos - Earth.pos
r_cM = Moon.pos - craft.pos
rmag_cM = sqrt(r_cM.x**2 + r_cM.y**2 + r_cM.z**2)
rmag_cE = sqrt(r_cE.x**2 + r_cE.y**2 + r_cE.z**2)
Fmag_cE = G*Earth.m*craft.m/(rmag_cE**2)
rhat_cE = r_cE/rmag_cE
F_cE = -Fmag_cE*rhat_cE
Fnet_c = F_cE
Fscale = rmag_cE/Fmag_cE
#arr_c = arrow(pos=craft.pos, axis=Fnet_c*Fscale/5, color=color.yellow)
#arr_E = arrow(pos=Earth.pos, axis=-Fnet_c*Fscale/5, color=color.yellow)
parr_c = arrow(color=color.blue)  #momentum of craft arrow
fnetarr_c = arrow(color=color.red)#net force on craft arrow
#new arrows comimg
fnetarr_c=arrow(color=color.red, shaftwidth=2e6)    #net force arrow
fearr_c=arrow(color=color.cyan, shaftwidth=2e6)     #force from Earth arrow
fmarr_c=arrow(color=color.white, shaftwidth=2e6)    #force from Moon arrow

scene.autoscale=0
scene.center = vector(2e8,0,0)
t = 0           #units of seconds
deltat = 10     #units of seconds
trail = curve(color=craft.color)     #adds a trail object with no points
while t< 4*365*24*60*60:
    rate(10000)
    r_cE = craft.pos - Earth.pos
    rmag_cE = sqrt(r_cE.x**2 + r_cE.y**2 + r_cE.z**2)
    rhat_cE = r_cE/rmag_cE
    Fmag_cE = G*Earth.m*craft.m/(rmag_cE**2)
    F_cE = -Fmag_cE*rhat_cE
    #Moon joined
    r_cM = craft.pos-Moon.pos
    rmag_cM = sqrt(r_cM.x**2 + r_cM.y**2 + r_cM.z**2)
    rhat_cM = r_cM/rmag_cM
    Fmag_cM = G*Moon.m*craft.m/(rmag_cM**2)
    F_cM = -Fmag_cM*rhat_cM
    
    Fnet_c = F_cE + F_cM
    craft.p = craft.p + Fnet_c*deltat
    craft.pos = craft.pos + (craft.p/craft.m)*deltat
    trail.append(pos=craft.pos)   #adds a point at the new craft position

    parr_c.pos = craft.pos
    parr_c.axis = craft.p
    fnetarr_c.pos = craft.pos
    fnetarr_c.axis = Fnet_c*Fscale/100
    #new arrow update here
    fearr_c.pos = craft.pos
    fearr_c.axis = F_cE*Fscale
    fmarr_c.pos = craft.pos
    fmarr_c.axis = F_cM*Fscale
    
    t = t + deltat
    if rmag_cE < Earth.radius+craft.radius:
        print ("Crashed into Earth")
        break
    if rmag_cM < Moon.radius+craft.radius:
        print ("Crashed into Moon")
        break
    #print "Fnet_c", Fnet_c












