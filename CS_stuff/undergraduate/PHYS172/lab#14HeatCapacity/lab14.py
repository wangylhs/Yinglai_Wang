from __future__ import division
from visual.factorial import *
from visual.graph import *
nA = 6.02e23    ## Avogadro's number
Aldata =[(20,0.23/nA),(40,2.09/nA), (60,5.77/nA), (80,9.65/nA), (100,13.04/nA),
         (150,18.52/nA), (200, 21.58/nA), (250,23.25/nA), (300, 24.32/nA),
         (400,25.61/nA)]
Pbdata = [(20,11.01/nA),(40,19.57/nA), (60,22.43/nA), (80,23.69/nA), (100,24.43/nA),
         (150,25.27/nA), (200, 25.87/nA), (250,26.36/nA), (300, 26.82/nA),
         (400,27.45/nA)]
#Heat Capacity graphs
gdisplay(xtitle='Temp',ytitle='Heat Capacity', x=0, y=600, width=600,height=300)

Alg = gdots(color=color.magenta,pos=Aldata)
Pbg = gdots(color=color.cyan, pos=Pbdata)

CAlgraph = gcurve(color=color.magenta) 
CPbgraph = gcurve(color=color.cyan)


## Setting up Graphing Windows
#Ways graph
gdisplay(xtitle='q1',ytitle='Ways', x=500, y=0, width=600,height=300)
waygraph = gvbars(delta=0.7, color=color.red) # to make vertical bar graph

###entropy graphs
gdisplay(xtitle='q1',ytitle='Entropy', x=500, y=300, width=600,height=300)
S1graph = gcurve(color=color.red) 
#S2graph = gcurve(color=color.blue) 
#S1S2graph = gcurve(color=color.green)

###temperature graphs
gdisplay(xtitle='q1',ytitle='Temp.', x=500, y=600, width=600,height=300)
T1graph = gcurve(color=color.red) 
#T2graph = gcurve(color=color.blue)
##
gdisplay(xtitle='q1',ytitle='Capacity', x=500, y=300, width=600,height=300)
CvsqAlgraph = gcurve(color=color.blue)
#CvsqPbgraph = gcurve(color = color.green)
## Constants

hbar= 1e-34     # Planck's constant divided by 2pi
k=1.38e-23      # Boltzmann's constant
mAL= 27*1.7e-27  # Mass of Al (27 nucleons)
mPb= 207*1.7e-27
kAL= 20        # Interatomic spring constant for Aluminum
kPb= 8
## Initial Conditions
#Ntotal = 500 # total number of oscillators
N1 = 105 # number of oscillators in object 1
#N2 = Ntotal-N1 # number of oscillators in object 2
qtotal = 300 # total quanta of energy shared among all the oscillators

q1 = 0 # start with no quanta of energy in object 1

while q1 <= qtotal: # for each possible value of energy in object 1
    #q2 = qtotal - q1 # number of quanta of energy in object 2
    # Calculate number of ways to arrange q1 quanta in object 1:
    ways1 = combin(q1+N1-1,q1)
    # Calculate number of ways to arrange q2 quanta in object 2:
    #ways2 = combin(q2+N2-1,q2)
    # Plot number of ways to arrange energy in the two objects:
    #waygraph.plot( pos=(q1,ways1) )
    S1 = k*log(ways1)
   # S2 = k*log(ways2)
    q1t = q1 + 1
    q1tt = q1t + 1
    #q2t = q2 + 1
    ways1t = combin(q1t+N1-1,q1t)
    ways1tt= combin(q1tt+N1-1,q1tt)
    #ways2t = combin(q2t+N2-1,q2t)
    S1t = k*log(ways1t)
    S1tt = k*log(ways1tt)
    #S2t = k*log(ways2t)
    deltaE = hbar*sqrt(4*kAL/mAL)
    deltaEPb = hbar*sqrt(4*kPb/mPb)
    deltaS1 = S1t - S1
    deltaS1t = S1tt - S1t
    #deltaS2 = S2t - S2
    T1 = deltaE/deltaS1
    TPb = deltaEPb/deltaS1
    T1t = deltaE/deltaS1t
    TPbt = deltaEPb/deltaS1t
    CAl = deltaE/(T1t-T1)
    CPb = deltaEPb/(TPbt-TPb)
    CAl = CAl/35
    CPb = CPb/35
    #T2 = deltaE/deltaS2
    # Plot Entropies
    #S1graph.plot( pos=(q1,log(ways1)) ) # log of ways1
    #S2graph.plot( pos=(q1,log(ways2)) ) # log of ways2
    #S1S2graph.plot( pos=(q1,log(ways1*ways2)) ) # log of ways1*ways2

    # Plot Temperatures
    T1graph.plot( pos=(q1,T1) )
    #T2graph.plot( pos=(q1,T2) )
    CAlgraph.plot( pos=(T1,CAl)) #plots of heat capacity vs. temperature
    CPbgraph.plot( pos=(TPb,CPb)) #plots of lead heat capacity
    CvsqAlgraph.plot( pos = (q1, CAl))
    #CvsqPbgraph.plot( pos = (q1, CPb))
    
    q1 = q1+1
