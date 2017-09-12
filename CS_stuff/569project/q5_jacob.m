clear
mdl_puma560
%y=ax+b
a=input('input a:');
b=input('input b:');
% set velocity and 2 end-points
velocity=0.1;
start=[(-b)/a,0,-0.4];
dest=[0,b,-0.4];
% translate to 4x4 homogeneous matrices
T = transl(start);
q=zeros(round(norm(start-dest)/velocity/0.02)+1,6);
% initialization
% compute q(1) and q'
t=0;
v=[velocity*(1/sqrt(1+a*a));velocity*(a/sqrt(1+a*a));0;0;0;0];
T=transl(start);
q(1,:)=p560.ikine6s(T);
inv_J=inv(p560.jacobn(q(1,:)));
dq=inv_J*v;
% q(i+1)=q(i)+q' * delta t
% keep updating q(i+1) and q' based on different time frame
% v doest not change since its a line
for i=1:round(norm(start-dest)/velocity/0.02)
    q(i+1,:)=q(i,:)+dq'*0.02;
    dq=inv(p560.jacobn(q(i+1,:)))*v;
    t=t+0.02;
end
p560.plot(q,'fps',1/0.02,'trail','b');