from __future__ import division
from visual import *

e = 1.6e-19
oofpez = 9e9
scalefactor = 0.002083e-15

atom1 = sphere(pos=vector(0.5e-9,0,0),radius=1e-10,color=color.red)
atom1.q = -1*e
atom2 = sphere(pos=vector(-0.5e-9,0,0),radius=1e-10,color=color.yellow)
atom2.q = 1*e


##r1 = Obslocation-atom1.pos
#r1mag = mag(r1)
#r1hat = r1/r1mag


#r2 = Obslocation-atom2.pos
#r2mag = mag(r2)
#r2hat = r2/r2mag

#E1 = oofpez * atom1.q * r1hat / (r1mag**2)
#Earrow.axis = scalefactor* E1


#print "The magnitude of E1 field =",mag(E1),"N/C"

#E2 = oofpez * atom2.q * r2hat / (r2mag**2)

#Enet=E1+E2
#print "Enet =",Enet,"N/C"
#Earrow.axis = scalefactor*Enet

theta = 0
r = 2e-9
while theta < 2 * pi:
    Obslocation = vector(r*cos(theta),0,r*sin(theta))
    Obslocation2 = vector(r*cos(theta),r*sin(theta),0)
    
    r1=Obslocation-atom1.pos
    r1mag = mag(r1)
    r1hat = r1 / r1mag
    E1 = oofpez * atom1.q / (r1mag**2) * r1hat
    r2=Obslocation-atom2.pos
    r2mag = mag(r2)
    r2hat = r2 / r2mag

    E2 = oofpez * atom2.q / (r2mag**2) * r2hat
    Enet = E1 + E2
    
    print "The observation location is ", Obslocation, "m"
    print "Enet =",Enet,"N/C"
    Earrow = arrow(pos = Obslocation, axis= Enet*scalefactor, color=color.orange)            
    r1=Obslocation2-atom1.pos
    r1mag = mag(r1)
    r1hat = r1 / r1mag
    E1 = oofpez * atom1.q / (r1mag**2) * r1hat
    r2=Obslocation2-atom2.pos
    r2mag = mag(r2)
    r2hat = r2 / r2mag

    E2 = oofpez * atom2.q / (r2mag**2) * r2hat
    Enet = E1 + E2
    theta = theta + pi/60
    Earrow2 = arrow(pos = Obslocation2, axis= Enet*scalefactor, color=color.orange)



