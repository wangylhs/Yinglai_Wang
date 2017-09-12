clear
% work with a model of the Puma 560 robot
mdl_puma560
% pick a arbitrary joint angle configuration
q=[pi/2 pi/4 0 pi/2 0 0];
disp('verify forward kinematics')
% forward kinematics computed by RST built in function
T_simulate=p560.fkine(q);

% compute forward kinematics by old fasion
% define DH table variable based on p560.display 
theta=[q(1) q(2) q(3) q(4) q(5) q(6)];
alpha=[pi/2 0 -pi/2 pi/2 -pi/2 0];
a=[0 0.4318 0.0203 0 0 0];
d=[0 0 0.15 0.4318 0 0];

% compute link transformation matrix
A01=[cos(theta(1)) -cos(alpha(1))*sin(theta(1)) sin(alpha(1))*sin(theta(1)) a(1)*cos(theta(1));
     sin(theta(1)) cos(alpha(1))*cos(theta(1)) -sin(alpha(1))*cos(theta(1)) a(1)*sin(theta(1));
     0 sin(alpha(1)) cos(alpha(1)) d(1);
     0 0 0 1];
A12=[cos(theta(2)) -cos(alpha(2))*sin(theta(2)) sin(alpha(2))*sin(theta(2)) a(2)*cos(theta(2));
     sin(theta(2)) cos(alpha(2))*cos(theta(2)) -sin(alpha(2))*cos(theta(2)) a(2)*sin(theta(2));
     0 sin(alpha(2)) cos(alpha(2)) d(2);
     0 0 0 1];
A23=[cos(theta(3)) -cos(alpha(3))*sin(theta(3)) sin(alpha(3))*sin(theta(3)) a(3)*cos(theta(3));
     sin(theta(3)) cos(alpha(3))*cos(theta(3)) -sin(alpha(3))*cos(theta(3)) a(3)*sin(theta(3));
     0 sin(alpha(3)) cos(alpha(3)) d(3);
     0 0 0 1];
A34=[cos(theta(4)) -cos(alpha(4))*sin(theta(4)) sin(alpha(4))*sin(theta(4)) a(4)*cos(theta(4));
     sin(theta(4)) cos(alpha(4))*cos(theta(4)) -sin(alpha(4))*cos(theta(4)) a(4)*sin(theta(4));
     0 sin(alpha(4)) cos(alpha(4)) d(4);
     0 0 0 1];
A45=[cos(theta(5)) -cos(alpha(5))*sin(theta(5)) sin(alpha(5))*sin(theta(5)) a(5)*cos(theta(5));
     sin(theta(5)) cos(alpha(5))*cos(theta(5)) -sin(alpha(5))*cos(theta(5)) a(5)*sin(theta(5));
     0 sin(alpha(5)) cos(alpha(5)) d(5);
     0 0 0 1];
A56=[cos(theta(6)) -cos(alpha(6))*sin(theta(6)) sin(alpha(6))*sin(theta(6)) a(6)*cos(theta(6));
     sin(theta(6)) cos(alpha(6))*cos(theta(6)) -sin(alpha(6))*cos(theta(6)) a(6)*sin(theta(6));
     0 sin(alpha(6)) cos(alpha(6)) d(6);
     0 0 0 1];

% compute forward kinematics by formula
T_formula = A01*A12*A23*A34*A45*A56;

about T_simulate
disp(T_simulate)
about T_formula
disp(T_formula)
% forward kinematics is varified since the homogeneous matrix computed by
% formula is as same as simulated
disp('T_simulate = T_formula => forward kinematics verified!')

disp('verify inverse kinematics')
% inverse kinematics computed by RST built in function
inv_q=p560.ikine6s(T_simulate);
T=p560.fkine(inv_q);
about T
disp(T)
% even inv_q is different than q, but it will give the same end effector
% pose as q
% inverse kinematics is varified since T is same as computed by forward
% kinematics
disp('T = T_simulate = T_formula => inverse kinematics verified!')
 
 
 
 
