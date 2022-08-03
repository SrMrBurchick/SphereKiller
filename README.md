## Тестове завдання на вакансію

UE4 Developer

Завдання для ознайомлення з UE4 - Стрілянина по сферам

Створити у Unreal Engine 4 проект на основі шаблону FirstPerson. Під час старту
гри на рівні повинні з'являтися 15 сфер у радіусі 2000 довкола персонажа (ця
позиція надалі вважається точкою спавна). При пострілі у сферу вона пропадає
(знищується). Після знищення 10ти сфер у радіусі 1500 від точки їх спавна
(навколо якої з'являлися сфери) всі сфери знищуються і з'являється наступна
хвиля: кількість сфер збільшується на 10%, а радіус спавна на 5%. Сфери повинні
з'являтися у випадкових місцях, але так, щоб між ними була відстань щонайменше
80 і залишалася можливість пройти хвилю - тобто наявність 10 сфер у радіусі 1500
від точки їх спавна. Точкою спавна нової хвилі є позиція гравця в момент
завершення попередньої хвилі.

Вимоги:
1. Можна використовувати Blueprints, але більшість логіки мають бути написані на C++.
2. Версія Unreal Engine 4 має бути 22 або новішою.
3. Повинні бути коментарі у коді.
4. Надіслати нам необхідно сам проект (без тимчасових файлів Saved, Intermediate, VS).

Додаткові завдання:
1. Дати можливість змінювати всі введені в завданні параметри. +
2. Додати ефект знищення сфер. -
3. З появою кожної нової сфери зменшувати її розмір до зазначеного, з можливістю налаштовувати крок зміни та мінімальний розмір. -
4. Додати UI на екран із відображенням кількості знищених сфер та номером хвилі. +

# Realization report
So, i've created main logic to the SphereKillerGameMode class. I've some issue
while I was implementing this:
 1. Data from Blueprint clas not aplying affect in cpp class. Nothing has janged. So for spawning Sphere I add ClassFinder object at the BeginPlay method.
 2. The same problem was when I tried to add UUserWidget class, so I solved it in the smae way.
 3. The sphere destroing animation was'nt add. I've tried to slvoe this by using Frature. But as I say the Blueprint class has a strange behaviour
 4. The sphere radius changing TODO
