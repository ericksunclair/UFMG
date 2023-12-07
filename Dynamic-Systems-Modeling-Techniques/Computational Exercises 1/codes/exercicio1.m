load("system_response_ex1.mat");

% Item 1
subplot(2,2,1);
plot(t,x,t,y);
title('Sinais de entrada (x) e saída (y) ao longo do tempo');
xlabel('tempo (t)');
ylabel('sinais de entrada (x) e saída (y)');
grid on;
hold on;

% Item 2
k = max(y) / max(x);
y_tal_temp = 0.632 * max(y);

tol = 0.01;
close_tal_array = t(abs(y-y_tal_temp) < tol);
tal = close_tal_array(1);
y_tal = y(t == tal);

plot(tal,y_tal,"r*");
legend('x','y','63,2% de y_m_a_x');

num = k;
den = [tal 1];
H = tf(num,den)

% Item 3
subplot(2,2,2);
y_est = lsim(H,x,t);

plot(t,y,'r:','LineWidth',2);
hold on;
plot(t,y_est,'b--','LineWidth',1);
title('Sinal de saída real (y) e estimado (y_e_s_t) ao longo do tempo');
xlabel('tempo (t)');
ylabel('sinais de saída real (y) e estimado (y_e_s_t)');
legend('y','y_e_s_t');
grid on;

% Item 4
x_noise = x.*(1 + 0.1*randn(size(x)));
y_noise = lsim(H,x_noise,t);

subplot(2,2,3);
plot(t,x_noise);
hold on;
plot(t,y_noise,'LineWidth',2);
title('Sinais de entrada (x_n_o_i_s_e) e saída (y_n_o_i_s_e) ao longo do tempo');
xlabel('tempo (t)');
ylabel('sinais de entrada (x_n_o_i_s_e) e saída (y_n_o_i_s_e)');
legend('x_n_o_i_s_e','y_n_o_i_s_e');
grid on;

% Item 5
k_noise = max(y_noise) / max(x_noise);
y_tal_temp_noise = 0.632 * max(y_noise);

tol_noise = 0.01;
close_tal_array_noise = t(abs(y_noise-y_tal_temp_noise) < tol_noise);
tal_noise = close_tal_array_noise(1);
y_tal_noise = y_noise(t == tal_noise);

num_noise = k_noise;
den_noise = [tal_noise 1];
H_noise = tf(num_noise,den_noise)

% Item 6
k_array = double.empty;
tal_array = double.empty;

for i = 1:100
    x1 = x.*(1 + 0.1*randn(size(x)));
    y1 = lsim(H,x1,t);

    k_array(i) = max(y1) / max(x1);
    y_tal_temp1 = 0.632 * max(y1);
    tol = 0.01;
    close_tal_array = t(abs(y1-y_tal_temp1) < tol);
    tal_array(i) = close_tal_array(1);
end

mean_k = mean(k_array)
std_k = std(k_array)
mean_tal = mean(tal_array)
std_tal = std(tal_array)