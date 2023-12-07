% carrega os dados do arquivo
load('data_TRMS.mat');

% calcula as FACs para y* e y*^2
N = length(y); % Número de amostras
FAC_y = xcorr(y, 'biased');
FAC_y2 = xcorr(y.^2, 'biased');

% calcula o intervalo de confiança de 95% para as FACs
conf_interval = 1.96 / sqrt(N); % 1.96 é o valor crítico para 95% de confiança

% determina o tempo de amostragem Ts com base nos primeiros mínimos das FACs
[min_y, tau_y] = min(FAC_y);
[min_y2, tau_y2] = min(FAC_y2);
Ts = tau_y;

% mostra os resultados
disp(['Primeiro mínimo da FAC de y: ' num2str(tau_y)]);
disp(['Primeiro mínimo da FAC de y^2: ' num2str(tau_y2)]);
disp(['Tempo de amostragem Ts escolhido: ' num2str(Ts)]);

% plota as FACs com o intervalo de confiança
t1 = (-N+1:N-1) * Ts;
figure;
subplot(3, 2, 1);
plot(t1, FAC_y, 'b');
hold on;
plot(t1, conf_interval * ones(size(t1)), 'r--');
plot(t1, -conf_interval * ones(size(t1)), 'r--');
title('FAC de y* com Intervalo de Confiança de 95%');
xlabel('Atraso (segundos)');
ylabel('FAC');

subplot(3, 2, 2);
plot(t1, FAC_y2, 'b');
hold on;
plot(t1, conf_interval * ones(size(t1)), 'r--');
plot(t1, -conf_interval * ones(size(t1)), 'r--');
title('FAC de y*^2 com Intervalo de Confiança de 95%');
xlabel('Atraso (segundos)');
ylabel('FAC');



% calcula a FCC entre u e y
FCC_uy = xcorr(u, y, 'biased');

% plota a FCC
t2 = (-N+1:N-1) * Ts;
subplot(3, 2, 3);
plot(t2, FCC_uy);
title('Função de Correlação Cruzada entre u e y');
xlabel('Tempo (s)');
ylabel('FCC');

% calcula o intervalo de confiança de 95%
N = length(u);
conf_interval2 = 1.96 / sqrt(N); % 1.96 é o valor crítico para 95% de confiança
hold on;
plot(t2, conf_interval2 * ones(size(t2)), 'r--');
plot(t2, -conf_interval2 * ones(size(t2)), 'r--');
hold off;



% divide os dados em dados de treinamento e teste
N_treinamento = floor(N / 2);
N_teste = N - N_treinamento;

% dados de treinamento
y_treinamento = y(1:N_treinamento);
u_treinamento = u(1:N_treinamento);

% usa o estimador de mínimos quadrados para encontrar os parâmetros do modelo ARX
M = 2; % ordem do modelo
Y = zeros(N_treinamento - M, M);
for k = 1:N_treinamento - M
    Y(k, :) = [y_treinamento(k + 1), u_treinamento(k + 1)];
end

theta = Y \ y_treinamento(M + 1:N_treinamento);



% calcula os resíduos de estimação
Psi_hat = [zeros(M, 1); y_treinamento(1:N_treinamento - M) - Y * theta];
residuos = y_treinamento(M + 1:N_treinamento) - Psi_hat(M + 1:N_treinamento);

% calcula a variância dos resíduos
variancia_residuos = var(residuos);

% calcula o AIC
n_theta = length(theta); % Número de parâmetros do modelo
AIC = N_treinamento * log(variancia_residuos) + 2 * n_theta;
disp(['AIC calculado: ' num2str(AIC)]);



% dados de teste
y_teste = y(N_treinamento + 1:N);
u_teste = u(N_treinamento + 1:N);

% estima os valores de saída com o modelo ARX
y_estimado_treinamento = zeros(N_treinamento - M, 1);
for k = 1:N_treinamento - M
    y_estimado_treinamento(k) = [y_treinamento(k + 1), u_treinamento(k + 1)] * theta;
end

y_estimado_teste = zeros(N_teste, 1);
for k = 1:N_teste
    y_estimado_teste(k) = [y_teste(k), u_teste(k)] * theta;
end

% plot dos resultados
subplot(3, 2, 5);
plot(y_treinamento(M + 1:N_treinamento), 'b', 'DisplayName', 'y(k)');
hold on;
plot(y_estimado_treinamento, 'r', 'DisplayName', 'y\^(k)');
title('Dados de Treinamento');
legend;

subplot(3, 2, 6);
plot(y_teste, 'b', 'DisplayName', 'y(k)');
hold on;
plot(y_estimado_teste, 'r', 'DisplayName', 'y\^(k)');
title('Dados de Teste');
legend;
