from random import randint
f = open("test/data.txt", 'w')
for i in range(1, 100):
    f.write(str(randint(1, 10000)) + ' ')