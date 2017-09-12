from __future__ import division
from visual.graph import *

# Constants
k = 9.e9 # Coulomb force constant

pscale = 1 #momentum scale factor
fscale = 1 #force scale factor

# Objects
gold=sphere(pos=(0,0,0) , radius=1.e-14, color=color.yellow)

b= 3e-14  # impact parameter
alpha=sphere(pos=(-2.275e-13,b,0) , radius=1.e-14, color=color.cyan)


# Initial values
gold.m = 197*1.7e-27    # mass of gold nucleus - units of kg
alpha.m = 4*1.7e-27  # mass of alpha particle - units of kg
gold.c= 79*1.6e-19   # charge of gold nucleus - units of Coulombs
alpha.c= 2*1.6e-19   # charge of alpha particle - units of Coulombs

#set the alpha's initial momentum: moves only in the +x direction

alpha.K= 1e7 *1.6e-19 # initial energy of alpha particle; converts eVs to Joules
alpha.p=vector( 1.475e-19 ,0,0) # initial momentum of alpha; in terms of alpha.K
gold.p=vector(0,0,0)

alpha.trail = curve(color=alpha.color) # for displaying the trajectory
gold.trail = curve(color=gold.color) # for displaying the trajectory

# Setting the timestep and zeroing the cumulative time
deltat = 2.1e-23

t = 0

gdisplay(xtitle='Time',ytitle='Px', x=400, y=0, width=400,height=200)
alphapx=gcurve(color=color.blue)
goldpx=gcurve(color=color.yellow)
totalpx=gcurve(color=color.green) # this is for the py of gold + alpha
##
gdisplay(xtitle='Time',ytitle='Py', x=400, y=200, width=400,height=200) 
alphapy=gcurve(color=color.blue) 
goldpy=gcurve(color=color.yellow)
totalpy=gcurve(color=color.green) # this is for the py of gold + alpha

# Loop for repetitive calculations

while t < 2.1e-20:
    rate(1000) 
    r_aG = alpha.pos - gold.pos # the relative position vector between the alpha and the gold
    rmag_aG = mag(r_aG) # the magnitude of r_aG
    rhat_aG =  r_aG/rmag_aG # the unit vector of r_aG
    
    Fmag_aG =  k*gold.c*alpha.c/((rmag_aG)**2) # the magnitude of the Coulomb force of the gold on the alpha
    F_aG =  rhat_aG*Fmag_aG # the Coulomb force of the gold on the alpha
    
    Fnet_a = F_aG # the net force on the alpha particle

    F_Ga  =  -F_aG # the Coulomb force of the alpha on the gold

    Fnet_G = -Fnet_a # the net force on the gold nucleus

    
    alpha.p=  alpha.p + Fnet_a*deltat # update the momentum
    alpha.pos= alpha.pos + deltat*alpha.p/alpha.m # update the position
    gold.p=  gold.p + Fnet_G*deltat # update the momentum
    gold.pos= gold.pos + deltat*gold.p/gold.m # update the position

    t=t+deltat
 
    alpha.trail.append(pos=alpha.pos)  #appends new position to alpha trail
    gold.trail.append(pos=gold.pos)  #appends new position to gold trail
    alphapx.plot(pos=(t, alpha.p.x))
    alphapy.plot(pos=(t, alpha.p.y))
    totalpx.plot(pos=(t, gold.p.x+alpha.p.x))
    goldpx.plot(pos=(t, gold.p.x))
    goldpy.plot(pos=(t, gold.p.y))
    totalpy.plot(pos=(t, alpha.p.y+gold.p.y))
    
theta=atan2(alpha.p.y,alpha.p.x)*180/3.14159
#print "b(m)"," ","theta(degrees)"
#print b,theta


