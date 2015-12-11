# README #

Проект по работе 3 (вариант 22) "Сетевой сервис"

### Содержание репозитория ###
Проект создан в Qt Creatror, содержит следующие подпроекты:

- NetworkServiceLib - Библиотека, содержащая реализацию системы
- ConsoleApp - простое диалоговое приложение, демонстрирующее возможности библиотеки,
- Testing - unit-тестирующее приложение, написанное с использованием QtTesting Framework
Также в директории проекта размещены файлы:
- tasks.jpg - задания,
- classdiagram.xmi - UML-диаграмма классов для Umbrello

### Сборка ###
Для сборки необходима установленная в системе библиотека RapidJSON версии >=1.2.0, а также следующие утилиты:

* qmake
* make
* doxygen
* qhelpgeneator

Компиляция: qmake, затем make

* Запуск тестов: автоматически при сборке
* Документация автоматически генерируется doxygen`ом в папке Documentation в виде html-файлов
* Также генерируется документация для Qt Creator