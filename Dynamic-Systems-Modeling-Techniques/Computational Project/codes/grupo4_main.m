%%  Universidade Federal de Minas Gerais
%   ELT 016 - Técnicas de Modelagem de Sistemas Dinamicos
%   Prof. Pedro Henrique Silva Coutinho
%   Modelo de simulacao do Grupo 4 para o Trabalho Computacional em Grupo
%% Limpa variaveis, workspace e fecha jenelas de figuras abertas
clear, clc, close all
%% Especifique o tempo de simulacao desejado
tsim = 50; % tempo de simulacao <- pode ser alterado
%% NAO ALTERE O TEMPO DE AMOSTRAGEM ABAIXO!
Ts = 0.01; % tempo de amostragem especificado <- nao pode ser alterado
t = (0:Ts:tsim)'; % vetor de tempo de simulacao de passo fixo <- nao pode ser alterado
N = length(t); % numero de amostras de tempo <- nao pode ser alterado
%% Especifique os parametros da entrada PRBS (Tb, n e A)
Tb = 0.5; % tempo minimo em que o sinal PRBS sera mantido <- pode ser alterado
n = 8; % numero de bits (periodo = 2^n - 1) <- pode ser alterado
A = 0.1; % amplitude do sinal de entrada <- pode ser alterado
p3 = round(Tb/Ts); % <- pode ser alterado
u = A*prbs(N,n,p3)'; % gera sinal PRBS <- nao pode ser alterado
u = u - A/2; % entrada com media zero <- nao pode ser alterado
%%
input = [t,u]; % matriz de dados de entrada para a simulacao do modelo <- nao pode ser alterado
out = sim("grupo4_student.slx"); % realiza a simulacao do modelo <- nao pode ser alterado
y = out.y.Data; % sinal de saida do processo <- nao pode ser alterado
%% Figura da entrada e saida
figure;
plot(t,u)
hold on
plot(t,y)
%% Modelagem fenomenológica
% m*l*(teta)'' = - m*g*sen(teta) - k*l*(teta)' + T/l
% (teta)'' = - g*sen(teta)/l - k*(teta)'/m + T/(m*l*l)
% sendo T o torque de entrada aplicado ao sistema e teta o angulo de saída 
% entre a corda e o eixo vertical do pêndulo

% Vamos linearizar o sistema assumindo que o movimento e pequeno
% suficiente para fazer sen(teta)=teta, então:
% teta'' = - (g/l) * teta - k/m * teta' - 1/m(l^2) * T
% Lembrando que, na nossa base de dados, T será representado por u 
% e teta será representado por y

% Tirando a Transformada de Laplace do sistema obtemos:
% s^2 * teta(s) = - (g/l) * teta(s) - (k/m) * s * teta(s) - (1/m*(l^2)) * T(s)
% Isolando teta(s)/T(s) obtemos a função de transferência do sistema:
% H(s) = teta(s)/T(s) = ( -g/l ) / ( s^2 + k/m * s + 1/(m*(l^2)) )

% Parâmetros do sistema (exemplo)
g = 9.81;  % aceleração devida à gravidade (m/s^2)
l = 1.0;   % comprimento do pêndulo (m)
k = 0.1;   % constante de amortecimento
m = 1.0;   % massa do pêndulo (kg)

num = [-g / l];
den = [1, k / m, 1 / (m * l^2)];
H = tf(num, den);

% Simulação da resposta ao degrau
figure;
step(H);
title('Resposta ao Degrau do Sistema de Exemplo');

% Obter informações sobre a resposta ao degrau
step_info = stepinfo(H);
disp('Informações sobre a Resposta ao Degrau:');
disp(step_info);

%% Escolha e coleta de sinais
% O sistema, como definido anteriormente, é linear, de segunda ordem e com tempo de 
% acomodação de 76 segundos para um degrau unitário. A PRBS escolhida terá A=0.1 
% (pois o sistema é *aproximadamente* linear, então uma PRBS com amplitudes pequenas 
% garante que a resposta do sistema permaneça dentro de uma região linear),
% além de garantir que o sistema consiga responder a tempo, Tb=2s (tempo suficiente 
% para o sistema responder com a apmplitude escolhida) e n=8 bits (para ter uma melhor 
% resolução na identificação do sistema)

% Calcule as FACs de y e y^2 para identificar os primeiros mínimos (tal_y e tal_y2).
% y_dec = y(1:20:end);

N = length(y); % Número de amostras
[lags_y, fac_y, int_conf, ~] = myccf2(y, N, 0, 0);
[lags_y2, fac_y2, int_conf2, ~] = myccf2(y.^2, N, 0, 0);
[~, tau_y] = min(fac_y);
[~, tau_y2] = min(fac_y2);

figure;
subplot(2, 2, 1);
plot(lags_y, fac_y, 'b');
hold on;
plot(lags_y, int_conf * ones(size(lags_y)), 'r--');
plot(lags_y, -int_conf * ones(size(lags_y)), 'r--');
title('FAC de y* com Intervalo de Confiança de 95%');
xlabel('Atraso (segundos)');
ylabel('FAC');
grid on;

subplot(2, 2, 2);
plot(lags_y2, fac_y2, 'b');
hold on;
plot(lags_y2, int_conf2 * ones(size(lags_y2)), 'r--');
plot(lags_y2, -int_conf2 * ones(size(lags_y2)), 'r--');
title('FAC de y*^2 com Intervalo de Confiança de 95%');
xlabel('Atraso (segundos)');
ylabel('FAC');
grid on;


% Avalie a correlação entre u e y usando a FCC. Isso ajuda a verificar se a entrada está 
% correlacionada com a saída, indicando se os dados são adequados para identificação do modelo.

% O tempo de amostragem deve ser escolhido de forma que 10*delta <= tau_min <= 20*delta
% Sendo delta a taxa de decimação. Isso garante uma amostragem suficiente para capturar 
% as características dinâmicas do sistema.
tau_min = min(tau_y, tau_y2);
delta_min = tau_min/20;
delta_max = tau_min/10;
delta = round((delta_max+delta_min)/2);
Ts_novo = Ts*delta;

% Decimar os dados
u_ream = u(1:delta:end);
y_ream = y(1:delta:end);
t_ream = t(1:delta:end);

% Calcular a FCC entre y e u
N_ream = length(y_ream); % Número de amostras
[lags_uy, fcc_uy, int_conf_uy, ~] = myccf2([u_ream, y_ream], N_ream, 0, 0);

% Plotar a FCC com intervalo de confiança de 95%
subplot(2, 2, 3)
plot(lags_uy, fcc_uy, 'b');
hold on;
plot(lags_uy, int_conf_uy * ones(size(lags_uy)), 'r--');
plot(lags_uy, -int_conf_uy * ones(size(lags_uy)), 'r--');
title('FCC entre u e y com Intervalo de Confiança de 95%');
xlabel('Atraso (segundos)');
ylabel('FCC');
grid on;

% Separar em dados de treino e de teste
N_treino = floor(N_ream / 2);
N_teste = N_ream - N_treino;

y_treino = y(1:N_treino);
u_treino = u(1:N_treino);
y_teste = y(N_treino + 1:N_ream);
u_teste = u(N_treino + 1:N_ream);

subplot(2, 2, 4);
hold on;
plot(t_ream(1:N_treino), u_treino, 'b');
plot(t_ream(N_treino + 1:N_ream), u_teste, 'g');
plot(t_ream(1:N_treino), y_treino, 'b');
plot(t_ream(N_treino + 1:N_ream), y_teste, 'g');
title('Dados de treinamento e de teste');
xlabel('tempo (s)');
ylabel('u / y');
legend('Dados de treinamento', 'Dados de teste');
grid on;

%% Seleção da estrutura do modelo
% Inicialização
ordens = 1:10;
AIC_vals = zeros(size(ordens));
n_rest = N_treino - max(ordens);     % número de restrições

% Se fosse fazer cada ordem separadamente:
% % Ordem 1
% n_theta = 1;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 2
% n_theta = 2;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 3
% n_theta = 3;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 3) = y_treino(n_theta - 1:n_theta + n_rest - 2);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 4
% n_theta = 4;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 3) = y_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 4) = u_treino(n_theta - 1:n_theta + n_rest - 2);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 5
% n_theta = 5;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 3) = y_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 4) = u_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 5) = y_treino(n_theta - 2:n_theta + n_rest - 3);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 6
% n_theta = 6;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 3) = y_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 4) = u_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 5) = y_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 6) = u_treino(n_theta - 2:n_theta + n_rest - 3);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 7
% n_theta = 7;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 3) = y_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 4) = u_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 5) = y_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 6) = u_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 7) = y_treino(n_theta - 3:n_theta + n_rest - 4);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 8
% n_theta = 8;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 3) = y_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 4) = u_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 5) = y_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 6) = u_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 7) = y_treino(n_theta - 3:n_theta + n_rest - 4);
% Y(:, 8) = u_treino(n_theta - 3:n_theta + n_rest - 4);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 9
% n_theta = 9;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 3) = y_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 4) = u_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 5) = y_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 6) = u_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 7) = y_treino(n_theta - 3:n_theta + n_rest - 4);
% Y(:, 8) = u_treino(n_theta - 3:n_theta + n_rest - 4);
% Y(:, 9) = y_treino(n_theta - 4:n_theta + n_rest - 5);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
% 
% % Ordem 10
% n_theta = 10;
% 
% % Inicialização de Y e vet_y
% Y = zeros(n_rest, n_theta);
% vet_y = zeros(n_rest, 1);
% 
% % Preenchimento de Y e y_vec
% Y(:, 1) = y_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 2) = u_treino(n_theta:n_theta + n_rest - 1);
% Y(:, 3) = y_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 4) = u_treino(n_theta - 1:n_theta + n_rest - 2);
% Y(:, 5) = y_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 6) = u_treino(n_theta - 2:n_theta + n_rest - 3);
% Y(:, 7) = y_treino(n_theta - 3:n_theta + n_rest - 4);
% Y(:, 8) = u_treino(n_theta - 3:n_theta + n_rest - 4);
% Y(:, 9) = y_treino(n_theta - 4:n_theta + n_rest - 5);
% Y(:, 10) = u_treino(n_theta - 4:n_theta + n_rest - 5);
% vet_y = y_treino(n_theta + 1:n_theta + n_rest);
% 
% % Estimação dos parâmetros
% theta = ((Y' * Y) \ Y') * vet_y;
% 
% % Cálculo do AIC
% y_est = Y * theta;
% residuos = vet_y - y_est;
% var_residuos = var(residuos);
% AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;

% Iterando sobre as ordens
for i=1:length(ordens)
    n_theta = ordens(i);
    
    % Inicialização de Y e vet_y
    Y = zeros(n_rest, n_theta);
    vet_y = zeros(n_rest, 1);

    % Formação da matriz Y
    sub = 1;
    for j = 1:n_theta
        if mod(j, 2) == 1
            Y(:, j) = y_treino(j - sub + 1:j + n_rest - sub);
        else
            Y(:, j) = u_treino(j - sub + 1:j + n_rest - sub);
            sub = sub + 1;
        end
    end

    % Formação do vetor y
    vet_y = y_treino(n_theta + 1:n_theta + n_rest);

    % Estimação dos parâmetros
    theta = ((Y' * Y) \ Y') * vet_y;

    % Cálculo do AIC
    y_est = Y * theta;
    residuos = vet_y - y_est;
    var_residuos = var(residuos);
    AIC_vals(n_theta) = n_rest * log(var_residuos) + 2 * n_theta;
end

% Escolha da ordem com menor AIC
[AIC_min, AIC_min_ind] = min(AIC_vals);
ordem_otima = ordens(AIC_min_ind);

% Plotagem dos resultados
figure;
plot(ordens, AIC_vals, 'o-');
xlabel('Ordem do Modelo (n_\theta)');
ylabel('Critério de Akaike (AIC)');
title('Seleção de Ordem do Modelo');
grid on;

% Exibir a ordem ótima
disp(['A ordem ótima do modelo é: ' num2str(ordem_otima)]);


% Refazendo para a ordem ótima

% Formação da matriz Y
Y = zeros(N_treino - ordem_otima, ordem_otima * 2);
for j = 1:ordem_otima
    Y(:, j) = y_treino(ordem_otima - j + 1:N_treino - j);
    Y(:, j + ordem_otima) = u_treino(ordem_otima - j + 1:N_treino - j);
end
% Formação do vetor y
vet_y = y_treino(ordem_otima + 1:N_treino);

% % Inicialização de Y e vet_y
% Y = zeros(n_rest, ordem_otima);
% vet_y = zeros(n_rest, 1);
% % Preenchimento de Y e y_vec
% sub = 1;
% for j = 1:ordem_otima
%     if mod(j, 2) == 1
%         Y(:, j) = y_treino(j - sub + 1:j + n_rest - sub);
%     else
%         Y(:, j) = u_treino(j - sub + 1:j + n_rest - sub);
%         sub = sub + 1;
%     end
% end
% vet_y = y_treino(ordem_otima + 1:ordem_otima + n_rest);

% Estimação dos parâmetros
theta = ((Y' * Y) \ Y') * vet_y;

%% Validação do modelo
% Estimação para os dados de teste com o modelo ARX

% Formação da matriz Y_teste
Y_teste = zeros(N_teste - ordem_otima, ordem_otima * 2);
for j = 1:ordem_otima
    Y_teste(:, j) = y_teste(ordem_otima - j + 1:N_teste - j);
    Y_teste(:, j + ordem_otima) = u_teste(ordem_otima - j + 1:N_teste - j);
end

% % Formação da matriz Y_teste
% Y_teste = zeros(n_rest, ordem_otima);
% sub = 1;
% for j = 1:ordem_otima
%     if mod(j, 2) == 1
%         Y_teste(:, j) = y_treino(j - sub + 1:j + n_rest - sub);
%     else
%         Y_teste(:, j) = u_treino(j - sub + 1:j + n_rest - sub);
%         sub = sub + 1;
%     end
% end


% Estimação da saída nos dados de teste
y_est_teste = Y_teste * theta;

figure;
subplot(3, 1, 1);
plot(y_teste, 'b', 'DisplayName', 'y(k)');
hold on;
plot(y_est_teste, 'r', 'DisplayName', 'y_{est}(k)');
title('Dados de Teste');
legend;

% Calculo do RMSE
tam_est = length(y_est_teste);
residuos_teste = y_teste(1:tam_est,:) - y_est_teste;
RMSE_teste = sqrt(mean(residuos.^2));
% Exibir o resultado
disp(['O RMSE nos dados de teste é: ' num2str(RMSE_teste)]);

% Aleatoriedade dos resíduos (FAC dos resíduos)
N_res_t = length(residuos_teste); % Número de amostras
[lags_r, fac_r, int_conf_r, ~] = myccf2(residuos_teste, N_res_t, 0, 0);

% Plotar a FAC com intervalo de confiança de 95%
subplot(3, 1, 2);
plot(lags_r, fac_r, 'b');
hold on;
plot(lags_r, int_conf_r * ones(size(lags_r)), 'r--');
plot(lags_r, -int_conf_r * ones(size(lags_r)), 'r--');
title('FAC dos resíduos de teste com Intervalo de Confiança de 95%');
xlabel('Atraso (segundos)');
ylabel('FAC');
grid on;


% Correlação da entrada com os resíduos (FCC)
[lags_ur, fcc_ur, int_conf_ur, ~] = myccf2([u_teste(1:tam_est,:), residuos_teste], N_res_t, 0, 0);

% Plotar a FCC com intervalo de confiança de 95%
subplot(3, 1, 3)
plot(lags_ur, fcc_ur, 'b');
hold on;
plot(lags_ur, int_conf_ur * ones(size(lags_ur)), 'r--');
plot(lags_ur, -int_conf_ur * ones(size(lags_ur)), 'r--');
title('FCC entre os resíduos e u com Intervalo de Confiança de 95%');
xlabel('Atraso (segundos)');
ylabel('FCC');
grid on;
