from __future__ import division
from visual.factorial import *
from visual.graph import *

## Setting up Graphing Windows
#Ways graph
gdisplay(xtitle='q1',ytitle='Ways', x=500, y=0, width=600,height=300)
waygraph = gvbars(delta=0.7, color=color.red) # to make vertical bar graph

###entropy graphs
gdisplay(xtitle='q1',ytitle='Entropy', x=500, y=300, width=600,height=300)
S1graph = gcurve(color=color.red) 
S2graph = gcurve(color=color.blue) 
S1S2graph = gcurve(color=color.green)

###temperature graphs
gdisplay(xtitle='q1',ytitle='Temp.', x=500, y=600, width=600,height=300)
T1graph = gcurve(color=color.red) 
T2graph = gcurve(color=color.blue)

## Constants

hbar= 1e-34     # Planck's constant divided by 2pi
k=1.38e-23      # Boltzmann's constant
mAL= 27*1.7e-27  # Mass of Al (27 nucleons)
kAL= 16         # Interatomic spring constant for Aluminum

## Initial Conditions
Ntotal = 500 # total number of oscillators
N1 = 300 # number of oscillators in object 1
N2 = Ntotal-N1 # number of oscillators in object 2
qtotal = 100 # total quanta of energy shared among all the oscillators

q1 = 0 # start with no quanta of energy in object 1

while q1 <= qtotal: # for each possible value of energy in object 1
    q2 = qtotal - q1 # number of quanta of energy in object 2
    # Calculate number of ways to arrange q1 quanta in object 1:
    ways1 = combin(q1+N1-1,q1)
    # Calculate number of ways to arrange q2 quanta in object 2:
    ways2 = combin(q2+N2-1,q2)
    # Plot number of ways to arrange energy in the two objects:
    waygraph.plot( pos=(q1,ways1*ways2) )
    S1 = k*log(ways1)
    S2 = k*log(ways2)
    q1t = q1 + 1
    q2t = q2 + 1
    ways1t = combin(q1t+N1-1,q1t)
    ways2t = combin(q2t+N2-1,q2t)
    S1t = k*log(ways1t)
    S2t = k*log(ways2t)
    deltaE = hbar*sqrt(4*kAL/mAL)
    deltaS1 = S1t - S1
    deltaS2 = S2t - S2
    T1 = deltaE/deltaS1
    T2 = deltaE/deltaS2
    # Plot Entropies
    S1graph.plot( pos=(q1,log(ways1)) ) # log of ways1
    S2graph.plot( pos=(q1,log(ways2)) ) # log of ways2
    S1S2graph.plot( pos=(q1,log(ways1*ways2)) ) # log of ways1*ways2

    # Plot Temperatures
    T1graph.plot( pos=(q1,T1) )
    T2graph.plot( pos=(q1,T2) )
  
    q1 = q1+1

