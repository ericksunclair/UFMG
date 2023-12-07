%% Sem ruído
num = [1, 0.5];
den = [1, -1.5, 0.7];
H = tf(num,den, -1);

n = 6;
N = 378;
Tb = 1;
u = prbs(N, n, Tb);

k = 0:N-1;
h1 = impulse(H, k);
y = lsim(H,u,k);

figure('NumberTitle', 'off', 'Name', 'Sem ruído em y(t)');
subplot(3,2,1);
stem(k, u, '.');
xlabel('k');
ylabel('u(k)');
title('Sinal de Entrada PRBS');

subplot(3,2,2);
stem(k, y, '.');
xlabel('k');
ylabel('y(k)');
title('Resposta do Sistema');

n_samples = 40;
subplot(3,2,3);
stem(k(1:n_samples), h1(1:n_samples));
xlabel('k');
ylabel('h(k)');
title('Resposta ao Impulso Real');

n_samples = 40;
ruy = xcorr(u, y, 'biased');
ru = xcorr(u, 'biased');

Ru = toeplitz(ru, [ru(1), zeros(1, n_samples - 1)]);
h2 = Ru \ transpose(ruy);

subplot(3,2,4);
stem(k(1:n_samples), h2, 'r');
xlabel('k');
ylabel('h(k)');
title('Resposta ao Impulso Estimada Usando a Equação de Wiener-Hopf');


h3 = ruy(n_samples:n_samples+39) / var(u);

subplot(3,2,5);
stem(k(1:n_samples), h3, 'r');
xlabel('k');
ylabel('h(k)');
title('Resposta ao Impulso Estimada Usando o Método da Deconvolução');


U = toeplitz(u, [u(1), zeros(1, n_samples - 1)]);
h4 = U \ y;

subplot(3,2,6);
stem(k(1:n_samples), h4, 'r');
xlabel('k');
ylabel('h(k)');
title('Resposta ao Impulso Estimada Usando o Método da Deconvolução do Livro');
%% Com ruído
num = [1, 0.5];
den = [1, -1.5, 0.7];
H = tf(num,den, -1);

n = 6;
N = 378;
Tb = 1;
u = prbs(378, 6, 1);

k = 0:N-1;
h1 = impulse(H, k);
y = lsim(H,u,k);
y_noise = y + 0.3*randn(size(y));

figure('NumberTitle', 'off', 'Name', 'Com ruído em y(t)');
subplot(3,2,1);
stem(k, u, '.');
xlabel('k');
ylabel('u(k)');
title('Sinal de Entrada PRBS');

subplot(3,2,2);
stem(k, y_noise, '.');
xlabel('k');
ylabel('y(k)');
title('Resposta do Sistema');

n_samples = 40;
subplot(3,2,3);
stem(k(1:n_samples), h1(1:n_samples));
xlabel('k');
ylabel('h(k)');
title('Resposta ao Impulso Real');

n_samples = 40;
ruy = xcorr(u, y_noise, 'biased');
ru = xcorr(u, 'biased');

Ru = toeplitz(ru, [ru(1), zeros(1, n_samples - 1)]);
h2 = Ru \ transpose(ruy);

subplot(3,2,4);
stem(k(1:n_samples), h2, 'r');
xlabel('k');
ylabel('h(k)');
title('Resposta ao Impulso Estimada Usando a Equação de Wiener-Hopf');


h3 = ruy(1:n_samples) / var(u);

subplot(3,2,5);
stem(k(1:n_samples), h3, 'r');
xlabel('k');
ylabel('h(k)');
title('Resposta ao Impulso Estimada Usando o Método da Deconvolução');


U = toeplitz(u, [u(1), zeros(1, n_samples - 1)]);
h4 = U \ y_noise;

subplot(3,2,6);
stem(k(1:n_samples), h4, 'r');
xlabel('k');
ylabel('h(k)');
title('Resposta ao Impulso Estimada Usando o Método da Deconvolução do Livro');