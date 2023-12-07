load('data_for_ex3.mat');

% divide os dados em conjuntos de treinamento e teste
total_samples = size(x, 1);
train_ratio = 0.7;
train_size = round(total_samples * train_ratio);

x_train = x(1:train_size, :);
y_train = y(1:train_size);
x_test = x(train_size+1:end, :);
y_test = y(train_size+1:end);

% estima os parâmetros do modelo de regressão usando mínimos quadrados
theta = pinv(x_train' * x_train) * (x_train' * y_train);

% faz previsões para o conjunto de treinamento e teste
y_train_pred = x_train * theta;
y_test_pred = x_test * theta;

% cria os gráficos de comparação
figure;
subplot(2, 1, 1);
plot(1:train_size, y_train, 'b', 1:train_size, y_train_pred, 'r');
title('Conjunto de Treinamento: Valores Reais vs. Estimados');
xlabel('Amostras');
ylabel('Resistência à Compressão (MPa)');
legend('Real', 'Estimado');

subplot(2, 1, 2);
plot(1:(total_samples-train_size), y_test, 'b', 1:(total_samples-train_size), y_test_pred, 'r');
title('Conjunto de Teste: Valores Reais vs. Estimados');
xlabel('Amostras');
ylabel('Resistência à Compressão (MPa)');
legend('Real', 'Estimado');

% calcula do RMSE para o conjunto de treinamento
n_train = size(y_train, 1);
rmse_train = sqrt(mean((y_train - y_train_pred).^2));

% calcula do RMSE para o conjunto de teste
n_test = size(y_test, 1);
rmse_test = sqrt(mean((y_test - y_test_pred).^2));

fprintf('RMSE para o Conjunto de Treinamento: %.4f\n', rmse_train);
fprintf('RMSE para o Conjunto de Teste: %.4f\n', rmse_test);
