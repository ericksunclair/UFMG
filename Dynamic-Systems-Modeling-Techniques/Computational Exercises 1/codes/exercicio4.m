% Item 1
num = [1, 0.5];
den = [1, -1.5, 0.7];
H = tf(num,den, -1);

t_ = [500:1:1000];
h_ = impulse(H, t_);
t = [1:1:1000];
h = cat(1,zeros(499,1),h_);

subplot(4,1,1);
plot(t,h,"r.-");
title('Resposta do sistema a um impulso unitário em n=500');
xlabel('tempo (n)');
ylabel('resposta ao impulso (h)');
grid on;

% Item 2
k = 1000;
x = randn(k,1);
y = lsim(H,x,t);

subplot(4,1,2);
plot(t,x);
hold on;
plot (t,y);
title('Resposta do sistema (y) a um sinal aleatório gaussiano (x)');
xlabel('tempo (n)');
ylabel('entrada (x), saída (y)');
legend('x','y');
grid on;

% Item 3
[h_est, r] = deconv(y,x,"same",Method="least-squares");

subplot(4,1,3);
plot(t,h,"r.-");
hold on;
plot(t,h_est,"b.");
title('Resposta ao impulso teórica vs Resposta ao impulso estimada pela deconvolução');
xlabel('tempo (n)');
ylabel('teórica (h), estimada (h_e_s_t)');
legend('h','h_e_s_t');

% Item 4
y_noise = y.*(1 + 0.03.*randn(size(y)));
[h_est2, r2] = deconv(y_noise,x,"same",Method="least-squares");

subplot(4,1,4);
plot(t,h_est,"r.-");
hold on;
plot(t,h_est2,"b.");
title('Resposta ao impulso estimada pela deconvolução sem e com ruído');
xlabel('tempo (n)');
ylabel('sem ruído (h_e_s_t), com ruído (h_e_s_t_2)');
legend('h_e_s_t','h_e_s_t_2');