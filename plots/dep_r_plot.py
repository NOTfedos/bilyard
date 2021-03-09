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

fig, ax = plt.subplots()

ax.errorbar(x, y)
#plt.plot(x, y)
ax.set_xlabel('R, см')
ax.set_ylabel('L, м')
ax.set_title(f'Зависимость средней длины пробега L шара от радиуса Лузы R при N={int(n)}')

ax.grid()
plt.show()
