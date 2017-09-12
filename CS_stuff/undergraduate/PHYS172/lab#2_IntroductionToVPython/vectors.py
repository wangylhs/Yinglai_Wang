from __future__ import division
from visual import *

Sun = sphere(pos=vector(0,0,0), radius=7e9, color=color.orange)

Mercury = sphere(pos=vector(5.8e10,0,0), radius=4e9, color=color.cyan)

Venus = sphere(pos=vector(-1.1e11,0,0), radius=6e9, color=color.yellow)

Earth = sphere(pos=vector(0,1.5e11,0), radius=6.4e9, color=color.blue)

a1 = arrow(pos=Earth.pos, axis=Mercury.pos-Earth.pos, color=color.white)

a2 = arrow(pos=Earth.pos, axis=(Venus.pos-Earth.pos)/2, color=color.red)

deltar = vector(1e9,1e9,0)

step = 0
while step<100:
    rate(20)
    step = step+1
    print (step)
    Mercury.pos = Mercury.pos+deltar
    a1.axis = Mercury.pos-Earth.pos
print ("End of program, step=", step)
