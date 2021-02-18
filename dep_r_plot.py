import matplotlib.pyplot as plt


rf = open('data/output_eps2.txt')
x = []
y = []
for line in rf:
    r, n, l, c = list(map(float, line.split()))
    x.append(r*100)
    y.append(l)

xerr = [0.05 for _ in range(len(x))]
plt.plot(x, y)
plt.xlabel('R, см')
plt.ylabel('L, м')
plt.title(f'Зависимость средней длины пробега шара L от радиуса лузы R, при N={int(n)}')

plt.show()
