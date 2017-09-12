wtZ=ece301_ZOH(wn, T);
wtL=ece301_Lin(wn, T);
wtO=ece301_Opt(wn, T);
plot(sampling_locations, wn, 'ro', t, wtZ, t, wtL, t, wtO );
xlabel('t (sec)');
legend('sampled_values', 'ZOH', 'Linear', 'Optimal');