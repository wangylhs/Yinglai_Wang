
function out = draw_circle_jac(start,r,velocity)
    mdl_puma560
    t=0;
    % based on theta=l/r to calculate velocity
    v=[0;velocity*sin(velocity*t/r);velocity*cos(velocity*t/r);0;0;0];
    q=zeros(round(2*pi*r/velocity/0.02)+1,6);
    % initialization
    % get q(1) and q'
    T=transl(start);
    q(1,:)=p560.ikine6s(T);
    inv_J=inv(p560.jacobn(q(1,:)));
    dq=inv_J*v;
    
    for i=1:round(2*pi*r/velocity/0.02)
        % q(i+1)=q(i)+q'*delta t
        % keep updating q(i) q' and velocity based on different time frame
        q(i+1,:)=q(i,:)+dq'*0.02;
        inv_J=inv(p560.jacobn(q(i+1,:)));
        dq=inv_J*v;
        t=t+0.02;
        v=[0;velocity*sin(velocity*t/r);velocity*cos(velocity*t/r);0;0;0];
    end
    %return solution q
    out=q;
    return;
    end