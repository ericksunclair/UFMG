K = 2;
wn = 1.5;
zeta = 0.2;

num = K*(wn^2);
den = [1 2*zeta*wn wn^2];
H = tf(num, den)

t = (0:0.01:40)';
u = t>=5;
y = lsim(H, u, t);

subplot(5,2,1);
plot(t, u, t, y);
title('Resposta do sistema a um degrau unitário em t=5s');

y_noise = y + 0.5*randn(size(y));

subplot(5,2,2);
plot(t, u, t, y_noise);
title('Resposta do sistema ao degrau unitário com ruído');

N = 10;
y_noise_arr1(:,1) = y_noise;
for i = 2:N
    y_noise_arr1(:,i) = y + 0.5*randn(size(y));
end

y_mean1 = mean(y_noise_arr1, 2);
subplot(5,2,3);
plot(t, u, t, y_mean1);
title('Média de 10 respostas do sistema com ruído');

y_std1 = zeros(4001,1);
for i = 1:4001
    y_std1(i) = std(y_noise_arr1(i,:));
end
subplot(5,2,4);
plot(t, y_std1);
title('Desvio padrão de 10 respostas do sistema com ruído');


N = 100;
y_noise_arr2(:,1) = y_noise;
for i = 2:N
    y_noise_arr2(:,i) = y + 0.5*randn(size(y));
end

y_mean2 = mean(y_noise_arr2, 2);
subplot(5,2,5);
plot(t, u, t, y_mean2);
title('Média de 100 respostas do sistema com ruído');

y_std2 = zeros(4001,1);
for i = 1:4001
    y_std2(i) = std(y_noise_arr2(i,:));
end
subplot(5,2,6);
plot(t, y_std2);
title('Desvio padrão de 100 respostas do sistema com ruído');


N = 1000;
y_noise_arr3(:,1) = y_noise;
for i = 2:N
    y_noise_arr3(:,i) = y + 0.5*randn(size(y));
end

y_mean3 = mean(y_noise_arr3, 2);
subplot(5,2,7);
plot(t, u, t, y_mean3);
title('Média de 1000 respostas do sistema com ruído');

y_std3 = zeros(4001,1);
for i = 1:4001
    y_std3(i) = std(y_noise_arr3(i,:));
end
subplot(5,2,8);
plot(t, y_std3);
title('Desvio padrão de 1000 respostas do sistema com ruído');


N = 10000;
y_noise_arr4(:,1) = y_noise;
for i = 2:N
    y_noise_arr4(:,i) = y + 0.5*randn(size(y));
end

y_mean4 = mean(y_noise_arr4, 2);
subplot(5,2,9);
plot(t, u, t, y_mean4);
title('Média de 10000 respostas do sistema com ruído');

y_std4 = zeros(4001,1);
for i = 1:4001
    y_std4(i) = std(y_noise_arr4(i,:));
end
subplot(5,2,10);
plot(t, y_std4);
title('Desvio padrão de 10000 respostas do sistema com ruído');