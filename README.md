# Periodicity-of-polynomials

Программа для поиска периодов полиномов Жегалкина степени 2 методом разложения на линейные полиномы.

$ make   - сборка программы

$ ./main - запуск программы

Полиномы необходимо задавать в приведенном виде без пробелов.

Правильно:

x1x2+x2x3+x5+x6+1

x1+x3+1+x2+x4

x10+x2x3+x4+1

Неправильно:

x1x2+x1+x3x4+x1 (правильно: x1x2+x3x4) 

x1x10 + x2x3    (правильно: x1x10+x2x3)
