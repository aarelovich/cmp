clc;
close all;
clear all;

duration = 10;
NumberOfPoints = 1000000;
fs = 44000;
f1 = 1000;
f2 = 4000;

t = 0:1/fs:duration;
channel = sin(2*pi*f1*t);

% Doing it stereo
tone = [channel' channel'];
wavwrite(tone,fs,'tone.wav');

disp('all done')

Mod = abs(fft(channel(1:1024)));
plot(Mod)


%% Need to use the points in ms. 
%step = duration/NumberOfPoints; 
%t = 0:step:duration;
%%channel = sin(2*pi*f1*t) + sin(2*pi*f2*t);
%channel = sin(2*pi*f2*t);
%
%% Doing it stereo
%tone = [channel' channel'];
%
%wavwrite(tone,fs,'tone.wav');
