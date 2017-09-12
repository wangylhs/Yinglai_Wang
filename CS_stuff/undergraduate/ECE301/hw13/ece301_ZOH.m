function [ yt ] = ece301_ZOH( xn, sampling_period)
%ECE301_ZOH Summary of this function goes here
%   Detailed explanation goes here


duration=8;
f_sample=44100;
t=(((0-4)*f_sample+0.5):((duration-4)*f_sample-0.5))/f_sample;

n_temp=floor((duration/2-0.5/f_sample)/sampling_period);
sampling_times=(-sampling_period)*n_temp: sampling_period: sampling_period*n_temp;


yt=t;

i=1;
j=1;
for(i=1:length(t))
    if(j<2*n_temp+1)
        if(t(1,i)<sampling_times(1,j+1))
            yt(1,i)=xn(1,j);
        else
            j=j+1;
            yt(1,i)=xn(1,j);
        end
    else
        yt(1,i)=xn(1,j);
    end
end
end
