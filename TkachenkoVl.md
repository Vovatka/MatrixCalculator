***Автор: Ткаченко Владимир КМБО-05-23. Вариант 20-2-1***

## Задание 1
Разработать грамматику G по описанию (БНФ):

Выражения из присваиваний переменных типа `int`. Пример: `a = 0`; `b = 1`; `a = a + b`;

### Описане языка
Язык описывает последовательность операций присваивания значений переменным 
целочисленного типа.

**В язык входит:**
- Объявление и инициализация переменных типа `int`
- Присваивание значений переменным
- Арифметические операции: сложение `+`, вычитание `-`, умножение `*`, деление `/`
- Использование скобок `()` для изменения приоритета операций
- Использование ранее объявленных переменных в выражениях
- Последовательное выполнение операторов (через точку с запятой `;`)

**В язык не входит:**
- Другие типы данных (кроме `int`)
- Условные операторы (`if`, `else`)
- Циклы (`for`, `while`)
- Функции и процедуры
- Логические операции
- Операции сравнения

**Грамматика G:**
```ebnf
<Program> ::= <StatementList>

<StatementList> ::= <Statement> | <StatementList> <Statement>

<Statement> ::= <Declaration> | <Assignment>

<Declaration> ::= int ID = <Expression> ;

<Assignment> ::= ID = <Expression> ;

<Expression> ::= <Term> | <Expression> + <Term> | <Expression> - <Term>

<Term> ::= <Factor> | <Term> * <Factor> | <Term> / <Factor>

<Factor> ::= IntLiteral | ID | ( <Expression> ) | - <Factor>
```

**Терминалы:**
- IntLiteral - целочисленные литералы: `123`, `-45`, `0`
- ID - идентификаторы переменных: `a`, `b`, `counter`, `tmp`
- Ключевые слова: `int`
- Операторы: `+`, `-`, `*`, `/`, `=`
- Разделители: `;`, `(`, `)`

### Примеры:

1.  Простые объявления и присваивания:

    ```c
    int x = 10;
    int y = 20;
    z = x + y;
    ```

2.  Арифметические операции с приоритетом:

    ```c
    int a = 5;
    int b = 3;
    result = a * b + 2;
    value = a * (b + 2);
    ```

3.  Множественные операции:

    ```c
    int base = 100;
    int bonus = 25;
    int penalty = 10;
    total = base + bonus - penalty;
    result = total / 5 * 2;
    ```

4.  Последовательные вычисления:

    ```c
    int start = 0;
    start = start + 1;
    start = start * 10;
    start = start - 5;
    result = start / 2;
    ```

## Задание 2 - 4

### Класс и однозначность языка и грамматики
Поскольку в левой части продукции всегда стоит один нетерминал, а в правой – любое
выражение, грамматика относится к классу *контекстно-свободных*. При этом грамматика
не является регулярной.

**Правила в грамматике G, нарушающие регулярность:**
- Смешанный порядок терминалов и нетерминалов. Напимер для `<Assignment> ::= ID = <Expression> ;`
Правая часть представляет собой терминал (ID) → терминал (=) → нетерминал (Expression) → терминал (;),
что не укладывается в правила вида A → aB A → Ba.
- Левая рекурсия:
    ```
    <Expression> ::= <Expression> + <Term>
    <Term> ::= <Term> * <Factor>
    ```
    Левая рекурсия невозможна в регулярных грамматиках, т.к. она требует стека, и следовательно,
    не может описана конечным автоматом.

### Cинтаксическое дерево и вывод произвольного предложения
Возьмём в качестве примера следующее предложение:
```
int a = 10;
b = a * 2 + 5;
```

**Полный разбор предложения:**
```ebnf
<Program> ->
<StatementList> ->
<StatementList><Statement> ->
<Statement><Statement> ->
<Declaration><Statement> ->
int ID ("a") = <Expression> ; <Statement> ->
int a = <Expression> ; <Statement> ->
int a = <Term> ; <Statement> ->
int a = <Factor> ; <Statement> ->
int a = IntLiteral ; <Statement> ->
int a = 10 ; <Statement> ->
int a = 10 ; <Assignment> ->
int a = 10 ; ID ("b") = <Expression> ; ->
int a = 10 ; b = <Expression> ; ->
int a = 10 ; b = <Expression> + <Term> ; ->
int a = 10 ; b = <Term> + <Term> ; ->
int a = 10 ; b = <Term> * <Factor> + <Term> ; ->
int a = 10 ; b = <Factor> * <Factor> + <Term> ; ->
int a = 10 ; b = ID ("a") * <Factor> + <Term> ; ->
int a = 10 ; b = a * <Factor> + <Tearm> ; ->
int a = 10 ; b = a * IntLiteral + <Term> ; ->
int a = 10 ; b = a * 2 + <Term> ; ->
int a = 10 ; b = a * 2 + <Factor> ; ->
int a = 10 ; b = a * 2 + IntLiteral ; ->
int a = 10 ; b = a * 2 + 5 ;
```

**Cинтаксическое дерево:**
```tree
<Program>
└── <StatementList>
    ├── <StatementList>
    │   └── <Statement>
    │       └── <Declaration>
    │           ├── int
    │           ├── ID ("a")
    │           ├── =
    │           ├── <Expression>
    │           │   └── <Term>
    │           │       └── <Factor>
    │           │           └── IntLiteral ("10")
    │           └── ;
    └── <Statement>
        └── <Assignment>
            ├── ID ("b")
            ├── =
            ├── <Expression>
            │   ├── <Expression>
            │   │   └── <Term>
            │   │       ├── <Term>
            │   │       │   └── <Factor>
            │   │       │       └── ID ("a")
            │   │       ├── *
            │   │       └── <Factor>
            │   │           └── IntLiteral ("2")
            │   ├── +
            │   └── <Term>
            │       └── <Factor>
            │           └── IntLiteral ("5")
            └── ;
```

### Таблица SLR(1)
**Полный набор правил:**
```ebnf
0. S' -> Program
1. Program -> StatementList
2. StatementList -> Statement
3. StatementList -> StatementList Statement
4. Statement -> Declaration
5. Statement -> Assignment
6. Declaration -> "int" ID "=" Expression ";"
7. Assignment -> ID "=" Expression ";"
8. Expression -> Expression "+" Term
9. Expression -> Expression "-" Term
10. Expression -> Term
11. Term -> Term "*" Factor
12. Term -> Term "/" Factor
13. Term -> Factor
14. Factor -> IntLiteral
15. Factor -> ID
16. Factor -> "(" Expression ")"
17. Factor -> "-" Factor
```

**First таблица:**
|Нетерминал   |FIRST        |
|:-----------:|:-----------:|
|S'           |{int, ID}    |
|Program      |{int, ID}    |
|StatementList|{int, ID}    |
|Statement    |{int, ID}    |
|Declaration  |{int}        |
|Assignment   |{ID}         |
|Expression   |{IntLiteral, ID, "(", "-"}|
|Term         |{IntLiteral, ID, "(", "-"}|
|Factor       |{IntLiteral, ID, "(", "-"}|