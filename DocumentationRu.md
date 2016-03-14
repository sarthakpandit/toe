#Документация к движку по-русски.
[In English](Documentation.md)

# Введение в Tiny Open Engine. #

Не смотря на то, что проект называется Tiny Open Engine, по сути он не является движком для игр. Скорее это просто одна из возможных реализаций дизайна Game Object Component System, которая может быть построена как на базе низко уровневых API, так и на базе существующих графических движков и других готовых подсистем.

Слово Tiny присутствует в названии потому что сама ключевая идея очень проста, а её реализация не занимает огромного количества строк кода.

Слово Open ознчает сто структура движка открыта для развития. Движок может расширяться через добавление систем и компонент.

Вместе три слова образуют абривиатуру TOE - что означает палец на ноге. Такой крошечный объект как палец ноги вполне сопоставим с размерами базового кода движка.

Текущая версия движка разрабатывается поверх API, предоставляемым Airplay SDK - коммерческим ПО для создания приложений для смартфонов. Дополнительно ведуться работы по созданию совместимой реализации на базе XNA. Вместе эти две системы разработки покрывают большинство популярных целевых платформ на рынке видеоигр.

Давайте рассмотрим основные принцыпы TOE.

Всё, что происходит в игре в рамках одного пространства-времени описывается объектом World (мир). Например ваш персонаж, бегающий по старинному замку может быть в одном мире. А главное меню - в другом. Когда вы нажимаете кнопку и переходите из игры в главное меню - вы совершаете скачёк между мирами.

Каждый такой мир может иметь свои законы, по которым он работает. Например один может быть трёхмерным, а другой - двумерным. В одном может быть сложная система анимаций, объектов, искуственного интелекта, а другой может довольствоваться выводом нескольких картинок на экран и обработкой нажатия на них. Законы, по которым действует мир определяются подсистемами (Subsystem). Существует некоторе количество доступных подсистем, которые можно использовать в мире. В качестве примера таких подсистем можно привести трёхмерную графику, физическое моделирование, плоское меню, систему анимаций и т.п.

Объект в игре строиться из компонент, которые предоставляют подсистемы. Например подсистема трёхмерной графики предоставляет компонент трёхмерной модели. Подсистема физического моделирования предоставляет компонент для моделирования поведения ящика в физическом мире. Скомбинировав эти два компонента в одном объекте мы получаем в нашем мире ящик, который ведёт себя по физическим законам и выглядит как ящик.

Таким образом, используя простую идею о компонентной структуре, мы получаем мощный инструмент для создания приложений.