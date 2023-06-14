
delay = receive - send; 

plot(send, speed);
hold on;
plot(receive, speed);
grid on;
xlabel('Time (ms)');
ylabel('Speeds (m/s)');
title('Transmited and recieved speeds');
legend({'Transmitted speeds','Received speeds'},'Location','northwest')

M = mean(delay);
fprintf('Mean : %.6f ms\n', M);

S = std(delay);
fprintf('Standard deviation : %.6f ms\n', S);

figure;
histogram(delay,5000);
xlabel('Delay');