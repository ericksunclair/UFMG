% Item 1
num = [1, 0.3];
den = [1, 0.2, 0.8];
Hz = tf(num,den, -1);

subplot(2,2,1);
bode(Hz);
grid on;

% Item 2
u = randn(1024,1);
t = 1:1:1024;

y = lsim(Hz,u,t);
H_est = tfest(u,y,2,0);

subplot(2,2,2);
bode(H_est);
grid on;

% Item 3
A1 = 1; A2 = 1; A3 = 1;
F1 = 1/100; F2 = 0.1592; F3 = 1/47;
r1 = A1 .* sin (2* pi * F1 * t );
r2 = A2 .* sin (2* pi * F2 * t );
r3 = A3 .* sin (2* pi * F3 * t );
u2 = transpose(r1 + r2 + r3);

y2 = lsim(Hz,u2,t);
H_est2 = tfest(u2,y2,2,0);

subplot(2,2,3);
bode(H_est2);
grid on;