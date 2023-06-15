# Bibliotecas necessárias
import numpy as np
from matplotlib import pyplot as plt
from scipy import optimize as opt

# Definição da malha para plotar o gráfico de curva de nível
x1, x2, x3 = np.meshgrid(np.linspace(-3, 3), # Limites da variável x1
                         np.linspace(-3, 3), # Limites da variável x2
                         np.linspace(-3, 3)) # Limites da variável x3

# Calculando a função objetivo para o gráfico de curva de nível
f = (2*x1**2 + 2*x2**2 - 2*x1*x2 - 2*x2*x3 + x3**2) / (x1**2 + x2**2 + x3**2)

# Definição da função que implementa a função objetivo
# e será utilizada no algoritmo de otimização (necessário)
def fx(x):
    x1, x2, x3 = x[0], x[1], x[2]
    f = (2*x1**2 + 2*x2**2 - 2*x1*x2 - 2*x2*x3 + x3**2) / (x1**2 + x2**2 + x3**2)
    return f

x0 = np.array([1, 1, 1]) # Ponto inicial p/ algoritmo
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
        message += 'x3 = %.4f, ' % x[2]
        message += 'f(x) = %.4f' % fx(x)
        print(message)
        it += 1

# Exemplo de uso do método BFGS
result = opt.minimize(fx,
                      x0=x0,
                      callback=callback,
                      tol=1e-3, # Critério de parada: quando o elemento
                                # com maior valor absoluto no gradiente
                                # for menor que tol.
                      method='BFGS',
                      options={'maxiter': 30}) # Número máximo de iterações permitido

# Visualizar objeto com informações do resultado da otimização
print('\nSee the result object:\n', result)

# Plotar convergência do algoritmo
plt.plot(fxopt, '--*')
plt.title('Convergência')
plt.xlabel('Iterações')
plt.ylabel('f(x)')
plt.grid()
plt.savefig('plots/convergencia.png')
plt.show()

print("Frequência natural w: ", np.sqrt(result.fun))