\# Quadratic Equation Solver



\## Описание

Решение квадратного уравнения ax² + bx + c = 0 с поддержкой экспоненциальной формы чисел (e, E).



\## Особенности

\- Паттерн Интерпретатор для проверки формата чисел

\- Поддержка чисел вида: 123, -1.5, 1e3, -2.5E-5

\- Обработка всех случаев: 2 корня, 1 корень, нет корней, линейное уравнение, INF, WRONG

\- Google Test (покрытие >80%)

\- Повторный ввод, выход по пустой строке



\## Сборка и запуск

```bash

mkdir build \&\& cd build

cmake .. -DCMAKE\_TOOLCHAIN\_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build . --config Release

cd Release

quadratic.exe

