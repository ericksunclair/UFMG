load('data_for_ex1.mat');

% matriz de regressores X
X = [ones(length(x), 1), x, x.^2, x.^3, x.^4, x.^5];

% estima os parâmetros theta usando mínimos quadrados
theta = (X' * X) \ (X' * y);

% exibe os parâmetros estimados
disp('Parâmetros estimados:');
disp(theta);

% calcula os valores de potência estimados
y_estimado = X * theta;

% cria um gráfico de dispersão dos dados reais
scatter(x, y, 'b', 'filled');
hold on;

% cria um gráfico da curva de potência estimada
plot(x, y_estimado, 'r', 'LineWidth', 2);

% define rótulos e legendas
xlabel('Velocidade do Vento (m/s)');
ylabel('Potência Gerada (Watts)');
legend({'Dados Reais', 'Potência Estimada'}, 'Location', 'Northwest');
title('Estimativa da Curva de Potência da Turbina Eólica');
grid on;
