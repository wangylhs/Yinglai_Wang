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

%prefiltered signals
px1 = ece301conv(x1,lpf);
px2 = ece301conv(x2,lpf);
px3 = ece301conv(x3,lpf);
px4 = ece301conv(x4,lpf);
px5 = ece301conv(x5,lpf);
px6 = ece301conv(x6,lpf);

shifted1 = px1.*cos(2*pi*1000*t);
shifted2 = px2.*cos(2*pi*2000*t);
shifted3 = px3.*cos(2*pi*3000*t);
shifted4 = px4.*cos(2*pi*4000*t);
shifted5 = px5.*cos(2*pi*5000*t);
shifted6 = px6.*cos(2*pi*6000*t);
%after shift conv with lpf
shifted1lp = ece301conv(shifted1,sin(2*pi*1000*t)./(pi*t));
shifted2lp = ece301conv(shifted2,sin(2*pi*2000*t)./(pi*t));
shifted3lp = ece301conv(shifted3,sin(2*pi*3000*t)./(pi*t));
shifted4lp = ece301conv(shifted4,sin(2*pi*4000*t)./(pi*t));
shifted5lp = ece301conv(shifted5,sin(2*pi*5000*t)./(pi*t));
shifted6lp = ece301conv(shifted6,sin(2*pi*6000*t)./(pi*t));



radio2 = shifted1lp+shifted2lp+shifted3lp+shifted4lp+shifted5lp+shifted6lp;
dft1 = fftshift(fft(radio2));
plot(1:length(dft1),dft1)
wavwrite(real(radio2), f_sample, 'radio2.wav');