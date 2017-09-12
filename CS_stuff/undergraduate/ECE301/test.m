duration=8;
f_sample=44100;
t=(((0-4)*f_sample+0.5):((duration-4)*f_sample-0.5))/f_sample;
%load 6 signals
[x1,f_sample,N]=wavread('x1');
x1=x1';
f=500;
lpf = sin(2*pi*f*t)./(pi*t);
%prefiltered x1 x2 x3
newx1 = ece301conv(x1,lpf);
wavwrite(newx1,f_sample,'test.wav');