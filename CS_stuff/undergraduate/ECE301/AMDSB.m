function[y]=AMDSB(ch)
        w=(ch*2000)-1000;
        f=1000;
        duration=8;
        f_sample=44100;

        t=(((0-4)*f_sample+0.5):((duration-4)*f_sample-0.5))/f_sample;

        [radio1, f_sample, N]=wavread('radio1');

        radio1=radio1';
        %lpf=sin(2*pi*f*t)./(pi*t);
        bpf=(sin(2*pi*(w+f)*t)./(pi*t))-(sin(2*pi*(w-f)*t)./(pi*t));
        
        %dft1 = fftshift(fft(bpf));
        %dft1 = fftshift(fft(radio1));
        %plot(1:length(dft1),dft1)
        radio1bdp=ece301conv(radio1,bpf);
        %figure
         %dft1 = fftshift(fft(radio1bdp));
        %plot(1:length(dft1),dft1)
        %plot(1:length(radio1bdp),radio1bdp)
        shiftedbdp = radio1bdp.*cos(2*pi*w*t);
          %figure
         %dft1 = fftshift(fft(shiftedbdp));
        %plot(1:length(dft1),dft1)
        
        signal = ece301conv(shiftedbdp,sin(2*pi*f*t)./(pi*t));
        signal = signal*2;
        
        wavwrite(signal,f_sample,'dsb1.wav');
end