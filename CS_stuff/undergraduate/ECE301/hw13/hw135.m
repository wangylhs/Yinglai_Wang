T=1/500;
%s1=sin(2*pi*440*t);
%s2=sin(2*pi*350*t);
%xt=s1+s2;
%sound(xt, f_sample);
%[xn, sampling_index, sampling_locations]=ece301_sampler(xt, T);

%plot(t,xt,sampling_locations, xn, 'ro');
%xlabel('t(sec)');
%axis([0.2,0.22,-2,2])
%legend('conti. signal', 'sampled values');
[xn, sampling_index, sampling_locations]=ece301_sampler(xt,T);
ytZ=ece301_ZOH(xn, T);
ytL=ece301_Lin(xn, T);
ytO=ece301_Opt(xn, T);

plot(t,xt, sampling_locations, xn, 'ro', t, ytZ, t, ytL, t, ytO );
xlabel('t (sec)');
axis([0.2, 0.22, -2,2])
legend('conti. signal', 'sampled_values', 'ZOH', 'Linear', 'Optimal');

