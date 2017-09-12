s1=sin(2*pi*440*t);
s2=sin(2*pi*350*t);
xt=s1+s2;
%sound(xt, f_sample);
[xn, sampling_index, sampling_locations]=ece301_sampler(xt, 1/4000);

plot(t,xt,sampling_locations, xn, 'ro');
xlabel('t(sec)');
axis([0.2,0.22,-2,2])
legend('conti. signal', 'sampled values');