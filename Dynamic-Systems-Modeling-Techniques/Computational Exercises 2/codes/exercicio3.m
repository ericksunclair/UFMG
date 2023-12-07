load('data_for_ex3.mat')

subplot(2,2,1);
stem(t, y, '.');
xlabel('t');
ylabel('y(t)');
title('Sinal y(t)');
grid on;

[ru, lag] = xcorr(u, 'biased');

alpha = 0.05;
N = length(u);
conf_interval = norminv([alpha/2, 1-alpha/2], 0, 1/sqrt(N));

subplot(2,2,2);
plot(lag, ru);
hold on;
line([lag(1), lag(end)], [conf_interval(1), conf_interval(1)], 'color', 'r', 'linestyle', '--');
line([lag(1), lag(end)], [conf_interval(2), conf_interval(2)], 'color', 'r', 'linestyle', '--');
xlabel('\tau');
ylabel('r_{u}(\tau)');
title('Função de Autocorrelação (FAC) de u(t) com Faixas de Confiança de 95%');
legend('r_{u}(\tau)', 'Faixa de Confiança (95%)');
grid on;
hold off;


[ry, lag2] = xcorr(y, 'biased');

N2 = length(y);
conf_interval2 = norminv([alpha/2, 1-alpha/2], 0, 1/sqrt(N2));

subplot(2,2,3);
plot(lag2, ry);
hold on;
line([lag2(1), lag2(end)], [conf_interval2(1), conf_interval2(1)], 'color', 'r', 'linestyle', '--');
line([lag2(1), lag2(end)], [conf_interval2(2), conf_interval2(2)], 'color', 'r', 'linestyle', '--');
xlabel('\tau');
ylabel('r_{y}(\tau)');
title('Função de Autocorrelação (FAC) de y(t) com Faixas de Confiança de 95%');
legend('r_{y}(\tau)', 'Faixa de Confiança (95%)');
grid on;
hold off;


[ruy, lag3] = xcorr(u, y, 'biased');

subplot(2,2,4)
plot(lag3, ruy);
hold on;
line([lag3(1), lag3(end)], [conf_interval2(1), conf_interval2(1)], 'color', 'r', 'linestyle', '--');
line([lag3(1), lag3(end)], [conf_interval2(2), conf_interval2(2)], 'color', 'r', 'linestyle', '--');
xlabel('\tau');
ylabel('r_{uy}(\tau)');
title('Função de Correlação Cruzada (FCC) entre u(t) e y(t) com Faixas de Confiança de 95%');
legend('r_{uy}(\tau)', 'Faixa de Confiança (95%)');
grid on;
hold off;

[max_ruy, idx_max_ruy] = max(ruy);
estimated_delay = lag3(idx_max_ruy);
fprintf('Retardo estimado: %d amostras\n', estimated_delay);