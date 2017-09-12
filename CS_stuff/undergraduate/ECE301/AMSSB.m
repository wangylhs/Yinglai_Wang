function[y]=AMSSB(ch)
        w=(ch)*1000;
        f=1000;
        duration=8;
        f_sample=44100;

        t=(((0-4)*f_sample+0.5):((duration-4)*f_sample-0.5))/f_sample;

        [radio2, f_sample, N]=wavread('radio2');

        radio2=radio2';
        %lpf=sin(2*pi*f*t)./(pi*t);
        bpf=(sin(2*pi*(w)*t)./(pi*t))-(sin(2*pi*(w-f)*t)./(pi*t));
        radio2bdp=ece301conv(radio2,bpf);
        shiftedbdp = radio2bdp.*cos(2*pi*w*t);
        signal = ece301conv(shiftedbdp,sin(2*pi*f*t)./(pi*t));
        signal = signal*4;
        wavwrite(signal,f_sample,'ssb4.wav');
end