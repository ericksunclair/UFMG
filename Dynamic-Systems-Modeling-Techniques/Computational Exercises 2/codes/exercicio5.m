%% Sem ruído
num = [1, 0.8];
den = [1, -1, 0.3];
H = tf(num,den, -1);

[mag, phase, w] = bode(H);

phase_deg = squeeze(phase) * 180 / pi;

figure('NumberTitle', 'off', 'Name', 'Sem ruído em y(t)');
subplot(3, 2, 1);
semilogx(w, 20*log10(squeeze(mag)));
grid on;
title('Ganho em dB');
xlabel('Frequência (rad/s)');
ylabel('Ganho (dB)');

subplot(3, 2, 2);
semilogx(w, phase_deg);
grid on;
title('Fase em Graus');
xlabel('Frequência (rad/s)');
ylabel('Fase (graus)');


n = 11;
N = 512;
Tb = 1;
u = prbs(N, n, Tb);

k = 0:N-1;
y = lsim(H,u,k);

[Pxx, w2] = pwelch(y, [], [], w);

gain_dB = 10*log10(Pxx);
phase_deg = angle(Pxx) * 180 / pi;

subplot(3, 2, 3);
semilogx(w2, gain_dB);
grid on;
title('Estimativa do Ganho em dB');
xlabel('Frequência (rad/s)');
ylabel('Ganho (dB)');

subplot(3, 2, 4);
semilogx(w2, phase_deg);
grid on;
title('Estimativa da Fase em Graus');
xlabel('Frequência (rad/s)');
ylabel('Fase (graus)');

h1 = impulse(H, k);
h2 = real(ifft(sqrt(Pxx)));

subplot(3,2,5);
plot(h1);
xlabel('k');
ylabel('h(k)');
grid on;
title('Resposta ao Impulso Real');

subplot(3,2,6);
plot(h2);
xlabel('k');
ylabel('h(k)');
grid on;
title('Resposta ao Impulso Estimada pela Identificação no Domínio da Frequência');
%% Com ruído
num = [1, 0.8];
den = [1, -1, 0.3];
H = tf(num,den, -1);

[mag, phase, w] = bode(H);

phase_deg = squeeze(phase) * 180 / pi;

figure('NumberTitle', 'off', 'Name', 'Com ruído em y(t)');
subplot(3, 2, 1);
semilogx(w, 20*log10(squeeze(mag)));
grid on;
title('Ganho em dB');
xlabel('Frequência (rad/s)');
ylabel('Ganho (dB)');

subplot(3, 2, 2);
semilogx(w, phase_deg);
grid on;
title('Fase em Graus');
xlabel('Frequência (rad/s)');
ylabel('Fase (graus)');


n = 11;
N = 512;
Tb = 1;
u = prbs(N, n, Tb);

k = 0:N-1;
y = lsim(H,u,k);

e = 0.4*randn(size(y));
y_noise = y + e;

[Pxx, w2] = pwelch(y_noise, [], [], w);

gain_dB = 10*log10(Pxx);
phase_deg = angle(Pxx) * 180 / pi;

subplot(3, 2, 3);
semilogx(w2, gain_dB);
grid on;
title('Estimativa do Ganho em dB');
xlabel('Frequência (rad/s)');
ylabel('Ganho (dB)');

subplot(3, 2, 4);
semilogx(w2, phase_deg);
grid on;
title('Estimativa da Fase em Graus');
xlabel('Frequência (rad/s)');
ylabel('Fase (graus)');


h1 = impulse(H, k);
h2 = real(ifft(sqrt(Pxx)));

subplot(3,2,5);
plot(h1);
xlabel('k');
ylabel('h(k)');
grid on;
title('Resposta ao Impulso Real');

subplot(3,2,6);
plot(h2);
xlabel('k');
ylabel('h(k)');
grid on;
title('Resposta ao Impulso Estimada pela Identificação no Domínio da Frequência');


[coherence, w3] = mscohere(u, y_noise, [], [], w);
coher_th = 0.6;

figure;
plot(w3, coherence);
grid on;
title('Função de Coerência entre u e y\_noise com o limiar de 0,6');
xlabel('Frequência (rad/s)');
ylabel('Coerência');

hold on;
plot([min(w3), max(w3)], [coher_th, coher_th], 'r--', 'LineWidth', 2);
legend('Coerência', 'Limiar de Coerência');
hold off;

rel_freq = w3(coherence >= coher_th);
rel_bandwidth = max(rel_freq) - min(rel_freq);
disp(['Largura de Banda Confiável: ', num2str(rel_bandwidth), ' rad/s']);
