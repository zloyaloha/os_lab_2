from random import randint
f = open("../data/data.txt", 'w')
for i in range(1, 10000000):
    f.write(str(randint(-1000, 1000)) + ' ')