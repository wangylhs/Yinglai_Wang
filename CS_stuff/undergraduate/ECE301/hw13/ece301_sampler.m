function [ sampled_values, sampling_index, sampling_times] = ece301_sampler( xt, sampling_period)
%ECE301_SAMPLER Summary of this function goes here
%   Detailed explanation goes here

duration=8;

f_sample=44100;

n_temp=floor((duration/2-0.5/f_sample)/sampling_period);

sampling_index=(-n_temp):n_temp;
sampling_times=(-sampling_period)*n_temp: sampling_period: sampling_period*n_temp;

t=(((0-4)*f_sample+0.5):((duration-4)*f_sample-0.5))/f_sample;


i=1;
j=1;
deltat=t(1,2)-t(1,1);

for(i=1:length(sampling_index))
    while(t(1,j+1)<sampling_times(1,i))
        j=j+1;
    end
    sampled_values(1,i)=(sampling_times(1,i)-t(1,j))/deltat*xt(1,j+1)+(t(1,j+1)-sampling_times(1,i))/deltat*xt(1,j);
end









end
