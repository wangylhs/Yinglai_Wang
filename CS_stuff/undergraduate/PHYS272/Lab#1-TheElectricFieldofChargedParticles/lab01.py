from __future__ import division
from visual import *

e = 1.6e-19
oofpez = 9e9
scalefactor = 0.002083e-9
Obslocation = vector(0,0,0)
atom1 = sphere(pos=vector(-500e-9,0,0),radius=10e-9,color=color.red)
atom1.q = 12*e
atom2 = sphere(pos=vector(600e-9,0,0),radius=10e-9,color=color.yellow)
atom2.q = 5*e
Earrow = arrow(pos=vector(0,0,0),axis=vector(0,0,0), color=color.cyan)
atom3 = sphere(pos=vector(-1.7122e-7,0,0),radius=10e-9,color=color.yellow)
atom3.q = -e

r1 = Earrow.pos-atom1.pos
r1mag = mag(r1)
r1hat = r1/r1mag

r2 = Earrow.pos-atom2.pos
r2mag = mag(r2)
r2hat = r2/r2mag

r3 = Earrow.pos-atom3.pos
r3mag = mag(r3)
r3hat = r3/r3mag
E1 = oofpez * atom1.q * r1hat / (r1mag**2)
Earrow.axis = scalefactor* E1


print "The magnitude of E1 field =",mag(E1),"N/C"

E2 = oofpez * atom2.q * r2hat / (r2mag**2)
Earrow = arrow(pos=Obslocation, axis=vector(0,0,0),color=color.cyan)

E3 = oofpez * atom3.q * r3hat / (r3mag**2)

Enet=E1+E2+E3
print "Enet =",Enet,"N/C"


Earrow.axis = scalefactor*Enet


