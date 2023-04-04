fs = 2;                    % Sampling frequency (samples per second)
dt = 1/fs;                   % seconds per sample
StopTime = 96;             % seconds
t = (0:dt:StopTime)';     % seconds
F = 0.25/8;                    % Sine wave frequency (hertz)
A = 5;
data = A * sin(2*pi*F*t);
plot(t,data)
str = "";
for i = 1 :length(data)
    str = str + data(i) + ",";
end
disp(str);
