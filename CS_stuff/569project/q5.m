mdl_puma560
% y=ax+b
a=input('input a:');
b=input('input b:');
% set start and end point
start=[(-b)/a,0,-0.4];
dest=[0,b,-0.4];
% translate to 4x4 homogeneous matrices
T1 = transl(start); 
T2 = transl(dest);	
T = ctraj(T1, T2, 50); 	% compute a Cartesian path

% using inverse kinematics
q = p560.ikine6s(T);
% eliminate NaNs in q
j=1;
for i=1:50
    TF=isnan(q(i,1));
    if(TF==1)
        q(i,:)=0;
    else
        new_q(j,:)=q(i,:);
        j=j+1;
    end
end

l=size(new_q);

p560.plot(new_q,'fps',l(1)*0.1/norm(start-dest),'trail','b')
