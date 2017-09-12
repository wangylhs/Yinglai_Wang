duration=8;
f_sample=44100;
t=(((0-4)*f_sample+0.5):((duration-4)*f_sample-0.5))/f_sample;
%load 6 signals
[x1,f_sample,N]=wavread('x1');
x1=x1';
[x2,f_sample,N]=wavread('x2');
x2=x2';
[x3,f_sample,N]=wavread('x3');
x3=x3';
[x4,f_sample,N]=wavread('x4');
x4=x4';
[x5,f_sample,N]=wavread('x5');
x5=x5';
[x6,f_sample,N]=wavread('x6');
x6=x6';
%low pass filter
f=1000;
lpf = sin(2*pi*f*t)./(pi*t);
%prefiltered x1 x2 x3
px1 = ece301conv(x1,lpf);
px2 = ece301conv(x2,lpf);
px3 = ece301conv(x3,lpf);

shifted1 = px1.*cos(2*pi*1000*t);
shifted2 = px2.*cos(2*pi*3000*t);
shifted3 = px3.*cos(2*pi*5000*t);
radio1 = shifted1+shifted2+shifted3;

wavwrite(radio1,f_sample,'radio1.wav');


