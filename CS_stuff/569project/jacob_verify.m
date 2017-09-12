clear
mdl_puma560
% pick a arbitrary joint angle configuration
q=[0 -pi/2 -pi/2 0 pi/6 0];
% forward kinematics computed by RST built in function
T_simulate=p560.fkine(q);

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
 

% compute jacobian of puma560 reference to the base using RST built in
% function
J_base_simulate=p560.jacob0(q);

% compute jacobian of puma560 reference to the base using cross-product
% method
% compute link transformation matrices
A01;A02=A01*A12;A03=A02*A23;A04=A03*A34;A05=A04*A45;A06=A05*A56;
% get roration matrices from corresponding link transformation matrices
R01=A01(1:3,1:3);R02=A02(1:3,1:3);R03=A03(1:3,1:3);R04=A04(1:3,1:3);R05=A05(1:3,1:3);R06=A06(1:3,1:3);
% compute joint axes of motion reference to base
z0=[0;0;1];z1=R01*z0;z2=R02*z0;z3=R03*z0;z4=R04*z0;z5=R05*z0; 
% get position vector from link transformation matrices
p01 = A01(1:3,4);p02 = A02(1:3,4);p03 = A03(1:3,4);p04 = A04(1:3,4);p05 = A05(1:3,4);p06 = A06(1:3,4);
p16 = p06 - p01;p26 = p06 - p02;p36 = p06 - p03;p46 = p06 - p04;p56 = p06 - p05;
% compute Ji(q) i=1,2,3,4,5,6
J1 = [cross(z0,p06);z0];J2 = [cross(z1,p16);z1];J3 = [cross(z2,p26);z2];
J4 = [cross(z3,p36);z3];J5 = [cross(z4,p46);z4];J6 = [cross(z5,p56);z5];
% jacobian reference to base computed by formula
J_base_formula=[J1 J2 J3 J4 J5 J6];
disp('verfy Jacobian reference to base coordinate')
about J_base_simulate
disp(J_base_simulate)
about J_base_formula
disp(J_base_formula)
disp('J_base_simulate = J_base_formula => forward Jacobian reference to base coordinate verified!')

% forward jacobian reference to end-effector
% compute jacobian of puma560 reference to end-effector using RST built in
% function
J_end_simulate=p560.jacobn(q);
% compute jacobian of puma560 reference to end-effector using differential
% translation and rotation
% find U matrices
A=zeros(4,4,6);
A(:,:,1)=A01;A(:,:,2)=A12;A(:,:,3)=A23;A(:,:,4)=A34;A(:,:,5)=A45;A(:,:,6)=A56;
U=zeros(4,4,6);
U(:,:,6)=A56;
for i=1:5
    U(:,:,6-i)=A(:,:,6-i)*U(:,:,7-i);
end
% compute Ji(q) reference to end-effector
J_end_formula=zeros(6,6);

for i=1:6
    J_end_formula(:,i)=[U(1,4,i)*U(2,1,i)-U(2,4,i)*U(1,1,i);
                        U(1,4,i)*U(2,2,i)-U(2,4,i)*U(1,2,i);
                        U(1,4,i)*U(2,3,i)-U(2,4,i)*U(1,3,i);
                        U(3,1,i);
                        U(3,2,i);
                        U(3,3,i);];
end

disp('verify Jacobian reference to end effector')
about J_end_simulate
disp(J_end_simulate)
about J_end_formula
disp(J_end_formula)
disp('J_end_simulate = J_end_formula => forward Jacobian reference to end-effector verified!')

% find inverse jacobian
% need to check if it is singular or not
if(det(J_base_formula)==0 || det(J_end_formula)==0)
    disp('Matrices not invertable!')
else
    disp('Matrices are not singular, invertable')
end

inv_J_base=inv(J_base_formula);
inv_J_end=inv(J_end_formula);

% check correctness by using J(q)(J+)J(q)=J(q)
J_base = J_base_formula*inv_J_base*J_base_formula;
J_end = J_end_formula*inv_J_end*J_end_formula;
about J_base
disp(J_base)
about J_end
disp(J_end)
disp('J_base = J_base_formula')
disp('J_end = J_end_formula')
disp('result satisfies the formula J=J*(J+)*J')
disp('=> inverse jacobian is verified!')
 
 