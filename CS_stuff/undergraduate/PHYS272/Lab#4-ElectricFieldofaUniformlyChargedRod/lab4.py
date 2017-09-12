from __future__ import division
from visual import *

#initial values

e = 1.6e-19
oofpez = 9e9
scalefactor = 4/620

L = 2
N = 100
Q = 3e-8
deltax = L/N
deltaq = Q/N
Obslocation = vector(0.3,0.4,0)
x = -L/2+deltax/2
Enet = vector(0,0,0)
r1 = vector(0,0,0)

while x < L/2 :
    sphere(pos=(x,0,0),radius=0.1,color=color.cyan)
    r1 = Obslocation-vector(x,0,0)
    r1mag = mag(r1)
    r1hat = r1/r1mag
    E1 = oofpez * deltaq * r1hat / (r1mag**2)
    Enet = Enet + E1
    x = x + deltax

# calculation section
Earrow = arrow(pos=Obslocation,axis=scalefactor*Enet,color=color.red)
Enet = mag(Enet)
print Enet

