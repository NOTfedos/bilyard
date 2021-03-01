import matplotlib.pyplot as plt


rf = open('../data/output_eps2.txt')
x = []
y = []
carr = []
for line in rf:
    r, n, l, c = list(map(float, line.split()))
    #print(r, n, l, c)
    x.append(r*100)
    y.append(l)
    carr.append(c)

xerr = [0.05 for _ in range(len(x))]
plt.plot(x, y)
#plt.plot(x, y)
plt.xlabel('R, см')
plt.ylabel('L, м')
plt.title(f'Зависимость средней длины пробега L шара от радиуса Лузы R при N={int(n)}')

plt.show()
