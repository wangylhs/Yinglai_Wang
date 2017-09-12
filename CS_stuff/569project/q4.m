mdl_puma560
% get trajectary for the circle
traject=my_circle([0.5,0,0],0.25);
% translate trjectary to 4x4 homogeneous matrices 
T=transl(traject');
% using inverse kinematics
q = p560.ikine6s(T); 
p560.plot(q,'fps',50/(0.5*pi/0.4),'trail','b')