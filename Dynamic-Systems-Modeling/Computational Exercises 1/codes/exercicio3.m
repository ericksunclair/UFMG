%% Caso sobreamortecido
load("system_response2_unitary_step.mat")
K = (max(y) - min(y)) / 1
y_norm = y / max(abs(y));

Mi = (y_norm(750) - y_norm(749)) / (t(750) - t(749));
r = Mi*t - 0.6;

subplot(2,2,1);
plot(t,y_norm,'LineWidth',2);
hold on;
plot(t(600:100:1620),r(600:100:1620),'LineWidth',1);
title('Resposta normalizada (y_n_o_r_m = y/K) do sistema ao degrau unitário');
xlabel('tempo (t)');
ylabel('resposta normalizada (y_n_o_r_m)');
grid on;

tol_tm = 0.001;
close_tm_arr = t(abs(r-1) < tol_tm);
tm = close_tm_arr(1);
plot(tm,r(t == tm),"r.",'LineWidth',2);
legend('y_n_o_r_m','r','tm');

const_1 = ones(1,length(t));
m1 = trapz(t,const_1) - trapz(t,y_norm);

lambda = (tm - m1) * Mi;
eta = lambda2eta(lambda)

tal_1 = ( eta^(eta / (1-eta)) ) / Mi
tal_2 = ( eta^(1 / (1-eta)) ) / Mi
tal_d = m1 - tal_1 - tal_2



%% Caso subamortecido
load("system_response3.mat")

subplot(2,2,1);
plot(t,u,t,y,'LineWidth',2);
title('Entrada (u) e saída (y) do sistema');
xlabel('tempo (t)');
ylabel('entrada (u) e saída (y)');
grid on;
hold on;

K = y(t == 100) / u(t == 100)

tol_tm = 0.001;
close_tm_arr = t(abs(y-y(t == 100)) < tol_tm);
tm = close_tm_arr(1);

m1 = trapz(t,y-y(t == 100));

Mi = (y(1041) - y(1040)) / (t(1041) - t(1040));

r = Mi*t + 2.35;
plot(t(810:50:1260),r(810:50:1260),'LineWidth',1);
plot(tm,y(t == tm),"k.",'LineWidth',3);
legend('u','y','r','tm');

lambda = (tm - m1) * Mi;
zeta = lambda2zeta(lambda)
wn = (acos(zeta) / sqrt(1 - (zeta^2)) ) * (1 / (tm - m1))
tal_d = m1 - ((2*zeta) / wn)