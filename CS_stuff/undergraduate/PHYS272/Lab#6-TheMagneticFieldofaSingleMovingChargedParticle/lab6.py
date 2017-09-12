from __future__ import division

from visual import *

#define constant
e=1.6e-19
oofpez=9e9
scalefactor=5e-7
muzofp=1e-7
deltat=5e-20

#initial values
t=0

#create objects
atom=sphere(pos=vector(2e-9,0,0),radius=1e-10,color=color.yellow)
atom.q=1.6e-19
atom.v=vector(-4e5,0,0)
Barrow=arrow(pos=(0,0,-6e-10),axis=vector(0,0,0),color=color.green)
Carrow=arrow(pos=(0,0,6e-10),axis=vector(0,0,0),color=color.red)
Darrow=arrow(pos=(0,6e-10,0),axis=vector(0,0,0),color=color.yellow)
Earrow=arrow(pos=(0,-6e-10,0),axis=vector(0,0,0),color=color.cyan)

scene.autoscale=0

#calculation


while atom.pos.x>-2e-9:
    r=Barrow.pos-atom.pos
    rC=Carrow.pos-atom.pos
    rD=Darrow.pos-atom.pos
    rE=Earrow.pos-atom.pos
    rCmag=mag(rC)
    rDmag=mag(rD)
    rEmag=mag(rE)
    rmag=mag(r)
    rhat=r/rmag
    rChat=rC/rCmag
    rDhat=rD/rDmag
    rEhat=rE/rEmag
    B=muzofp*e*cross(atom.v,rhat)/(rmag**2)
    BC=muzofp*e*cross(atom.v,rChat)/(rCmag**2)
    BD=muzofp*e*cross(atom.v,rDhat)/(rDmag**2)
    BE=muzofp*e*cross(atom.v,rEhat)/(rEmag**2)
    Barrow.axis=B*scalefactor
    Carrow.axis=BC*scalefactor
    Darrow.axis=BD*scalefactor
    Earrow.axis=BE*scalefactor
    atom.pos=atom.pos+atom.v*deltat
    t=t+deltat
    
    
