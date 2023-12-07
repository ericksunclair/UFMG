%% Sem ruído
load('data_for_ex2.mat');

% função de custo (a ser minimizada)
fun = @(theta) sum((y - filter(theta(3:4), [1, theta(1:2)], u)).^2);

% estimativa inicial dos parâmetros
theta0 = [0.5, 0.5, 0.5, 0.5];

% estimativa dos parâmetros pelos mínimos quadrados
theta_estimado = lsqnonlin(fun, theta0);

% exibe os parâmetros estimados
a1_estimado = theta_estimado(1);
a2_estimado = theta_estimado(2);
b1_estimado = theta_estimado(3);
b2_estimado = theta_estimado(4);
disp(['a1 estimado: ', num2str(a1_estimado)]);
disp(['a2 estimado: ', num2str(a2_estimado)]);
disp(['b1 estimado: ', num2str(b1_estimado)]);
disp(['b2 estimado: ', num2str(b2_estimado)]);

% usando os parâmetros estimados para prever a resposta
y_pred = filter([b1_estimado, b2_estimado], [1, a1_estimado, a2_estimado], u);

% plot da resposta real e da previsão
figure;
plot(y, 'b', 'LineWidth', 2);
hold on;
plot(y_pred, 'r--', 'LineWidth', 2);
legend('Resposta Real', 'Previsão');
xlabel('Amostras');
ylabel('y(k)');
title('Comparação entre Resposta Real e Previsão');

%% Com ruído
load('data_for_ex2.mat');

e = 0.5*randn(size(y));
y_noise = y + e;

% função de custo (a ser minimizada)
fun = @(theta) sum((y_noise - filter(theta(3:4), [1, theta(1:2)], u)).^2);

% estimativa inicial dos parâmetros
theta0 = [1, 1, 1, 1];

% estimativa dos parâmetros pelos mínimos quadrados
theta_estimado = lsqnonlin(fun, theta0);

% exibe os parâmetros estimados
a1_estimado = theta_estimado(1);
a2_estimado = theta_estimado(2);
b1_estimado = theta_estimado(3);
b2_estimado = theta_estimado(4);
disp(['a1 estimado: ', num2str(a1_estimado)]);
disp(['a2 estimado: ', num2str(a2_estimado)]);
disp(['b1 estimado: ', num2str(b1_estimado)]);
disp(['b2 estimado: ', num2str(b2_estimado)]);

% usando os parâmetros estimados para prever a resposta
y_pred = filter([b1_estimado, b2_estimado], [1, a1_estimado, a2_estimado], u);

% plot da resposta real e da previsão
figure;
plot(y_noise, 'b', 'LineWidth', 2);
hold on;
plot(y_pred, 'r--', 'LineWidth', 2);
legend('Resposta Real', 'Previsão');
xlabel('Amostras');
ylabel('y(k)');
title('Comparação entre Resposta Real e Previsão');