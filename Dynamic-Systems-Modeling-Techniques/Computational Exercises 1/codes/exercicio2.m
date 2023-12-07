% Item 1
K = 3;
zeta = 0.05;
wn = 1.5;

num = K*(wn^2);
den = [1, 2*zeta*wn, wn^2];
H = tf(num,den);

subplot(2,2,1);
[y,t] = step(H, 50);
plot(t,y);
title('Resposta do sistema ao degrau unitário para zeta = 0,05');
xlabel('tempo (t)');
ylabel('resposta (y)');
legend('y');
grid on;

y_inf = 3;
n_ciclos = 12;
zeta_est = 0.6 / n_ciclos
ts = 50;
wn_est = 4 / (zeta_est * ts)

num_est = K * (wn_est^2);
den_est = [1, 2*zeta_est*wn_est, wn_est^2];
H_est = tf(num_est,den_est);


% Item 3
subplot(2,2,2);
[y_est,t_est] = step(H_est, 50);
plot(t,y,'b:','LineWidth',1.5);
hold on;
plot(t_est,y_est,'--','LineWidth',2);
title('Resposta ao degrau unitário com H (y) e com H estimado (y_e_s_t) para zeta = 0,05');
xlabel('tempo (t)');
ylabel('resposta (y_e_s_t)');
legend('y', 'y_e_s_t');
grid on;


% Item 4
% para zeta = 0,15
zeta2 = 0.15;

num2 = K*(wn^2);
den2 = [1, 2*zeta2*wn, wn^2];
H2 = tf(num2,den2);
[y2,t2] = step(H2, 50);

n_ciclos2 = 5;
zeta_est2 = 0.6 / n_ciclos2
ts2 = 22;
wn_est2 = 4 / (zeta_est2 * ts2)

num_est2 = K * (wn_est2^2);
den_est2 = [1, 2*zeta_est2*wn_est2, wn_est2^2];
H_est2 = tf(num_est2,den_est2);

subplot(2,2,3);
[y_est2,t_est2] = step(H_est2, 50);
plot(t2,y2,'b:','LineWidth',1.5);
hold on;
plot(t_est2,y_est2,'--','LineWidth',2);
title('Resposta ao degrau unitário com H (y) e com H estimado (y_e_s_t) para zeta = 0,15');
xlabel('tempo (t)');
ylabel('resposta (y_e_s_t)');
legend('y', 'y_e_s_t');
grid on;


% para zeta = 0,55
zeta3 = 0.55;

num3 = K*(wn^2);
den3 = [1, 2*zeta3*wn, wn^2];
H3 = tf(num3,den3);
[y3,t3] = step(H3, 50);

n_ciclos3 = 1;
zeta_est3 = 0.6 / n_ciclos3
ts3 = 5;
wn_est3 = 4 / (zeta_est3 * ts3)

num_est3 = K * (wn_est3^2);
den_est3 = [1, 2*zeta_est3*wn_est3, wn_est3^2];
H_est3 = tf(num_est3,den_est3);

subplot(2,2,4);
[y_est3,t_est3] = step(H_est3, 50);
plot(t3,y3,'b:','LineWidth',1.5);
hold on;
plot(t_est3,y_est3,'--','LineWidth',2);
title('Resposta ao degrau unitário com H (y) e com H estimado (y_e_s_t) para zeta = 0,55');
xlabel('tempo (t)');
ylabel('resposta (y_e_s_t)');
legend('y', 'y_e_s_t');
grid on;