# Bibliotecas necessárias
import numpy as np
from matplotlib import pyplot as plt
from scipy import optimize as opt

# Definição da malha para plotar o gráfico de curva de nível
x1, x2 = np.meshgrid(np.linspace(-200, 200), # Limites da variável x1
                     np.linspace(-200, 200)) # Limites da variável x1

# Calculando a função objetivo para o gráfico de curva de nível
f = 0.6382*x1**2 + 0.3191*x2**2 - 0.2809*x1*x2 - 67.906*x1 - 14.29*x2

# Plotando o gráfico de curva de nível
plt.contour(x1, x2, f, levels=30)
plt.xlabel('x1')
plt.ylabel('x2')
plt.title('Curvas de nível')
plt.savefig('plots/curvas_nivel.png')
plt.show()

# Definição da função que implementa a função objetivo
# e será utilizada no algoritmo de otimização (necessário)
def fx(x):
    x1, x2 = x[0], x[1]
    f = 0.6382*x1**2 + 0.3191*x2**2 - 0.2809*x1*x2 - 67.906*x1 - 14.29*x2
    return f

x0 = np.array([150, 150]) # Ponto inicial p/ algoritmo
xopt = [x0.tolist()] # Lista de pontos por iteração (trajetória)
fxopt = [fx(x0)] # Avaliação de cada ponto da lista
it = 1 # Contador de iteração p/ fins de impressão na tela

# Esta função é apenas uma gambiarra para salvar o ponto de cada
# iteração e sua avaliação além de permitir imprimir na tela
# os dados de cada iteração
def callback(x):
    global xopt, fxopt
    xopt.append(x.tolist())
    fxopt.append(fx(x))
    if True: # Coloque False se quiser bloquear as impressões na tela
        global it
        message = 'It.: %d, ' % it
        message += 'x1 = %.4f, ' % x[0]
        message += 'x2 = %.4f, ' % x[1]
        message += 'f(x) = %.4f' % fx(x)
        print(message)
        it += 1

# # Exemplo de uso do método BFGS
# result = opt.minimize(fx,
#                       x0=x0,
#                       callback=callback,
#                       tol=1e-3, # Critério de parada: quando o elemento
#                                 # com maior valor absoluto no gradiente
#                                 # for menor que tol.
#                       method='BFGS',
#                       options={'maxiter': 100}) # Número máximo de iterações permitido
    
# Exemplo de uso do método Nelder-Mead Simplex
# result = opt.minimize(fx,
#                       x0=x0,
#                       callback=callback,
#                       tol=1e-3, # Critério de parada: quando o maior valor absoluto
#                                 # das diferenças nas avaliações entre pares de pontos do simplex
#                                 # e quando o maior valor absoluto das diferenças
#                                 # das variáveis de cada par de ponto do simplex 
#                                 # ambas forem menor que tol. Em outras palavras:
#                                 # max(|x[i]-x[0]|) <= tol & max(|f(x[i])-f(x[0])|) <= tol
#                                 # para todo 0 < i <= n+1 onde n+1 é o número de pontos do simplex.
#                       method='Nelder-Mead',
#                       options={'maxiter': 100, # Número máximo de iterações permitido
#                                'maxfev': 200}) # Número máximo de avaliações permitido

# Exemplo de uso do método do Gradiente Conjugado
result = opt.minimize(fx,
                      x0=x0,
                      callback=callback,
                      tol=1e-3, # Critério de parada: quando o elemento
                                # com maior valor absoluto no gradiente
                                # for menor que tol.
                      method='CG',
                      options={'maxiter': 100}) # Número máximo de iterações permitido

# Visualizar objeto com informações do resultado da otimização
print('\nSee the result object:\n', result)

# Plotar trajetória do algoritmo nas curvas de nível
plt.contour(x1, x2, f, levels=40)
xopt = np.array(xopt)
plt.plot(xopt[:, 0], xopt[:, 1], '--*r')
plt.xlabel('x1')
plt.ylabel('x2')
plt.title('Curvas de nível e trajetória do algoritmo')
plt.savefig('plots/trajetoria.png')
plt.show()

# Plotar convergência do algoritmo
plt.plot(fxopt, '--*')
plt.title('Convergência')
plt.xlabel('Iterações')
plt.ylabel('f(x)')
plt.grid()
plt.savefig('plots/convergencia.png')
plt.show()

print("Temperatura x1 em regime permanente:", result.x[0])
print("Temperatura x2 em regime permanente:", result.x[1])