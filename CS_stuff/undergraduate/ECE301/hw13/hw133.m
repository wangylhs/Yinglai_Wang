T=1/4000;
[xn, sampling_index, sampling_locations]=ece301_sampler(xt,T);
ytZ=ece301_ZOH(xn, T);
ytL=ece301_Lin(xn, T);
ytO=ece301_Opt(xn, T);
plot(t,xt, sampling_locations, xn, 'ro', t, ytZ, t, ytL, t, ytO );
xlabel('t (sec)');
axis([0.2035, 0.207, -0.7,0.2])
legend('conti. signal', 'sampled_values', 'ZOH', 'Linear', 'Optimal');