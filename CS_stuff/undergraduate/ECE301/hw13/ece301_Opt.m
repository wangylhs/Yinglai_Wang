function [ yt ] = ece301_Opt( xn, sampling_period)
%ECE301_ZOH Summary of this function goes here
%   Detailed explanation goes here


duration=8;
f_sample=44100;
t=(((0-4)*f_sample+0.5):((duration-4)*f_sample-0.5))/f_sample;

n_temp=floor((duration/2-0.5/f_sample)/sampling_period);
sampling_times=(-sampling_period)*n_temp: sampling_period: sampling_period*n_temp;


yt=zeros(size(t));

i=1;
j=1;

propagation_range=100*sampling_period; 
lrange=zeros(size(xn));
rrange=lrange;
jl=1;
jr=1;

to_stop_l=0;
to_stop_r=0;

for(i=1:length(xn))
    while((to_stop_l==0)&&(t(1,jl)<sampling_times(1,i)-propagation_range))
        jl=jl+1;
        if(jl==length(t))
            to_stop_l=1;
        end
    end
    while((to_stop_r==0)&&(t(1,jr)<=sampling_times(1,i)+propagation_range));
        jr=jr+1;
        if(jr==length(t))
            to_stop_r=1;
        end
    end
    lrange(1,i)=jl;
    rrange(1,i)=jr;
    
end

for(i=1:length(xn))
    
    jl=lrange(1,i);
    jr=rrange(1,i);
    yt(1,jl:jr)=yt(1,jl:jr)+xn(1,i)*sinc((t(1,jl:jr)-sampling_times(1,i))/sampling_period);
   
end
end



