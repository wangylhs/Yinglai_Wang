clear
mdl_puma560
start_point=[0.5,-0.25,0];
% call function to get solution q
q=draw_circle_jac(start_point,0.25,0.4);
p560.plot(q,'fps',1/0.02,'trail','b');