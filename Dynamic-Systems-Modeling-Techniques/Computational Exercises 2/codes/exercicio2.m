k = 1000;
e = randn(1, k);
u = 0.9 * circshift(e, [0, -1]) + 0.8 * circshift(e, [0, -2]) + 0.7 * circshift(e, [0, -3]) + e;

subplot(2,2,1);
stem(1:k, u, '.');
xlabel('k');
ylabel('u(k)');
title('Sinal u(k)');
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
title('Função de Autocorrelação (FAC) de u(k) com Faixas de Confiança de 95%');
legend('r_{u}(\tau)', 'Faixa de Confiança (95%)');
grid on;
hold off;


[re, lag2] = xcorr(e, 'biased');

N2 = length(e);
conf_interval2 = norminv([alpha/2, 1-alpha/2], 0, 1/sqrt(N2));

subplot(2,2,3);
plot(lag2, re);
hold on;
line([lag2(1), lag2(end)], [conf_interval2(1), conf_interval2(1)], 'color', 'r', 'linestyle', '--');
line([lag2(1), lag2(end)], [conf_interval2(2), conf_interval2(2)], 'color', 'r', 'linestyle', '--');
xlabel('\tau');
ylabel('r_{e}(\tau)');
title('Função de Autocorrelação (FAC) de e(k) com Faixas de Confiança de 95%');
legend('r_{e}(\tau)', 'Faixa de Confiança (95%)');
grid on;
hold off;


[reu, lag3] = xcorr(e, u, 'biased');

subplot(2,2,4)
plot(lag3, reu);
hold on;
line([lag3(1), lag3(end)], [conf_interval2(1), conf_interval2(1)], 'color', 'r', 'linestyle', '--');
line([lag3(1), lag3(end)], [conf_interval2(2), conf_interval2(2)], 'color', 'r', 'linestyle', '--');
xlabel('\tau');
ylabel('r_{eu}(\tau)');
title('Função de Correlação Cruzada (FCC) entre e(k) e u(k) com Faixas de Confiança de 95%');
legend('FCC', 'Faixa de Confiança (95%)');
grid on;
hold off;