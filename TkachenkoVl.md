***Автор: Ткаченко Владимир КМБО-05-23. Вариант 20-2-1***

***лучше смотреть тут: https://github.com/Vovatka/MatrixCalculator/blob/develop/TkachenkoVl.md***
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

## Задание 2

### Класс и однозначность языка и грамматики
Поскольку в левой части продукции всегда стоит один нетерминал, а в правой – любое
выражение, грамматика относится к классу *контекстно-свободных*. При этом она
однозначна (будет доказано в задании 4) и не является регулярной.

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

## Задание 3

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
    │           ├── ID
    │           ├── =
    │           ├── <Expression>
    │           │   └── <Term>
    │           │       └── <Factor>
    │           │           └── IntLiteral
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
            │   │       │       └── ID
            │   │       ├── *
            │   │       └── <Factor>
            │   │           └── IntLiteral
            │   ├── +
            │   └── <Term>
            │       └── <Factor>
            │           └── IntLiteral
            └── ;
```

![5328239842653047882](https://github.com/user-attachments/assets/8aff5297-5797-40e1-b168-675086c63374)

## Задание 4

### Таблица SLR(1)

**Набор правил:**
```ebnf
0. S' -> .Program
1. Program -> .StatementList
2. StatementList -> .Statement
3. StatementList -> .StatementList Statement
4. Statement -> .Declaration
5. Statement -> .Assignment
6. Declaration -> .int ID = Expression ;
7. Assignment -> .ID = Expression ;
8. Expression -> .Expression + Term
9. Expression -> .Expression - Term
10. Expression -> .Term
11. Term -> .Term * Factor
12. Term -> .Term / Factor
13. Term -> .Factor
14. Factor -> .IntLiteral
15. Factor -> .ID
16. Factor -> .( Expression )
17. Factor -> .- Factor
```


|Нетерминал   |FIRST                     |FOLLOW                   |
|:-----------:|:------------------------:|:-----------------------:|
|S'           |{int, ID}                 |{$}                      |
|Program      |{int, ID}                 |{$}                      |
|StatementList|{int, ID}                 |{$,int,ID}               | 
|Statement    |{int, ID}                 |{$,int,ID}               |
|Declaration  |{int}                     |{$,int,ID}               | 
|Assignment   |{ID}                      |{$,int,ID}               |
|Expression   |{IntLiteral, ID, "(", "-"}|{";","+","-",")"}        |
|Term         |{IntLiteral, ID, "(", "-"}|{";","+","-","*","/",")"}|
|Factor       |{IntLiteral, ID, "(", "-"}|{";","+","-","*","/",")"}|

**Стартовое сотояние:**
```ebnf
0. S' -> .Program
1. Program -> .StatementList
2. StatementList -> .Statement
3. StatementList -> .StatementList Statement
4. Statement -> .Declaration
5. Statement -> .Assignment
6. Declaration -> .int ID = Expression ;
7. Assignment -> .ID = Expression ;
```

*Дублирующие состояния goto(n1, T1)=goto(n2, T1) для упрощения записаны в следующем виде: goto(n1/n2, T1)*
|STATE| GOTO                                   | STATE CONTENT                                                                                                 |
|:---:|:--------------------------------------:|:-------------------------------------------------------------------------------------------------------------:|
| I1  |goto(0, Program)                        |{S' -> Program.}                                                                                               |
| I2  |goto(0, StatementList)                  |{Program -> StatementList.;<br>StatementList -> StatementList.Statement}                                       |
| I3  |goto(0, Statement)                      |{StatementList -> Statement.}                                                                                  | 
| I4  |goto(0/2, Declaration)                  |{Statement -> Declaration.}                                                                                    |
| I5  |goto(0/2, Assignment)                   |{Statement -> Assignment.}                                                                                     |
| I6  |goto(0/2, int)                          |{Declaration -> int. ID = Expression ;}                                                                        |
| I7  |goto(0/2, ID)                           |{Assignment -> ID. = Expression ;}                                                                             |
| I8  |goto(2, Statement)                      |{StatementList -> StatementList Statement.}                                                                    |
| I9  |goto(6, ID)                             |{Declaration -> int ID. = Expression ;}                                                                        |
| I10 |goto(7, =)                              |{Assignment -> ID =. Expression ;}                                                                             |
| I11 |goto(9, =)                              |{Declaration -> int ID =. Expression ;}                                                                        |
| I12 |goto(10, Expression)                    |{Assignment -> ID = Expression.;<br>Expression -> Expression. + Term;<br>Expression -> Expression. - Term}     |
| I13 |goto(10/11/17/21/22, Term)              |{Expression -> Term.;<br>Term -> Term. * Factor;<br>Term -> Term. / Factor}                                    |
| I14 |goto(10/11/17/21/22, Factor)            |{Term -> Factor.}                                                                                              |
| I15 |goto(10/11/17/21/22/23/24, IntLiteral)  |{Factor -> IntLiteral.}                                                                                        |
| I16 |goto(10/11/17/21/22/23/24, ID)          |{Factor -> ID.}                                                                                                |
| I17 |goto(10/11/18/23/24, "(")               |{Factor -> (. Expression )}                                                                                    |
| I18 |goto(10/11/17/21/22/23/24, -)           |{Factor -> -. Factor}                                                                                          |
| I19 |goto(11, Expression)                    |{Declaration -> int ID = Expression.;<br>Expression -> Expression. + Term;<br>Expression -> Expression. - Term}|
| I20 |goto(12, ";")                           |{Assignment -> ID = Expression ;.}                                                                             |
| I21 |goto(12, +)                             |{Expression -> Expression +. Term}                                                                             |
| I22 |goto(12, -)                             |{Expression -> Expression -. Term}                                                                             |
| I23 |goto(13, \*)                            |{Term -> Term *. Factor}                                                                                       |
| I24 |goto(13, /)                             |{Term -> Term /. Factor}                                                                                       |
| I25 |goto(17, Expression)                    |{Factor -> ( Expression.) ;<br>Expression -> Expression. + Term;<br>Expression -> Expression. - Term}          |
| I26 |goto(18, Factor)                        |{Factor -> - Factor.}                                                                                          |
| I27 |goto(19, ";")                           |{Declaration -> int ID = Expression ;.}                                                                        |
| I28 |goto(21, Term)                          |{Expression -> Expression + Term.;<br>Term -> Term. * Factor;<br>Term -> Term. / Factor}                       |
| I29 |goto(22, Term)                          |{Expression -> Expression - Term.;<br>Term -> Term. * Factor;<br>Term -> Term. / Factor}                       |
| I30 |goto(23, Factor)                        |{Term -> Term * Factor.}                                                                                       |
| I31 |goto(24, Factor)                        |{Term -> Term / Factor.}                                                                                       |
| I32 |goto(25, ")")                           |{Factor -> ( Expression ).}                                                                                    |

|State|int|ID |=  |;  |+  | - | *  | /  |IntLiteral| ( | ) |$   |S'  |Program|StatementList|Statement|Declaration|Assignment|Expression|Term|Factor|
|:---:|:-:|:-:|:-:|:-:|:-:|:-:|:--:|:--:|:--:|:---:|:---:|:---:|:---:|:---------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| 0   |s6 |s7 |   |   |   |   |    |    |    |     |     |     |     | 1   | 2   | 3   | 4   | 5   |     |     |     |
| 1   |   |   |   |   |   |   |    |    |    |     |     | acc |     |     |     |     |     |     |     |     |     |
| 2   |s6 |s7 |   |   |   |   |    |    |    |     |     | r1  |     |     | 8   | 4   | 5   |     |     |     |     |
| 3   |r2 |r2 |   |   |   |   |    |    |    |     |     | r2  |     |     |     |     |     |     |     |     |     |
| 4   |r4 |r4 |   |   |   |   |    |    |    |     |     | r4  |     |     |     |     |     |     |     |     |     |
| 5   |r5 |r5 |   |   |   |   |    |    |    |     |     | r5  |     |     |     |     |     |     |     |     |     |
| 6   |   |s9 |   |   |   |   |    |    |    |     |     |     |     |     |     |     |     |     |     |     |     |
| 7   |   |   |s10|   |   |   |    |    |    |     |     |     |     |     |     |     |     |     |     |     |     |
| 8   |r3 |r3 |   |   |   |   |    |    |    |     |     | r3  |     |     |     |     |     |     |     |     |     |
| 9   |   |s11|   |   |   |   |    |    |    |     |     |     |     |     |     |     |     |     |     |     |     |
| 10  |   |s16|   |   |   |s18|    |    | s15| s17 |     |     |     |     |     |     |     |     | 12  | 13  | 14  |
| 11  |   |s16|   |   |   |s18|    |    | s15| s17 |     |     |     |     |     |     |     |     | 19  | 13  | 14  |
| 12  |   |   |   |s20|s21|s22|    |    |    |     |     |     |     |     |     |     |     |     |     |     |     |
| 13  |   |   |   |r10|r10|r10| s23| s24|    |     | r10 |     |     |     |     |     |     |     |     |     |     |
| 14  |   |   |   |r13|r13|r13| r13| r13|    |     | r13 |     |     |     |     |     |     |     |     |     |     |
| 15  |   |   |   |r14|r14|r14| r14| r14|    |     | r14 |     |     |     |     |     |     |     |     |     |     |
| 16  |   |   |   |r15|r15|r15| r15| r15|    |     | r15 |     |     |     |     |     |     |     |     |     |     |
| 17  |   |s16|   |   |   |s18|    |    | s15| s17 |     |     |     |     |     |     |     |     | 25  | 13  | 14  |
| 18  |   |s16|   |   |   |s18|    |    | s15| s17 |     |     |     |     |     |     |     |     |     |     | 26  |
| 19  |   |   |   |s27|s21|s22|    |    |    |     |     |     |     |     |     |     |     |     |     |     |     |
| 20  |r7 |r7 |   |   |   |   |    |    |    |     |     | r7  |     |     |     |     |     |     |     |     |     |
| 21  |   |s16|   |   |   |s18|    |    | s15| s17 |     |     |     |     |     |     |     |     |     | 28  | 14  |
| 22  |   |s16|   |   |   |s18|    |    | s15| s17 |     |     |     |     |     |     |     |     |     | 29  | 14  |
| 23  |   |s16|   |   |   |s18|    |    | s15| s17 |     |     |     |     |     |     |     |     |     |     | 30  |
| 24  |   |s16|   |   |   |s18|    |    | s15| s17 |     |     |     |     |     |     |     |     |     |     | 31  |
| 25  |   |   |   |   |s21|s22|    |    |    |     | s32 |     |     |     |     |     |     |     |     |     |     |
| 26  |   |   |   |r17|r17|r17| r17| r17|    |     | r17 |     |     |     |     |     |     |     |     |     |     |
| 27  |r6 |r6 |   |   |   |   |    |    |    |     |     | r6  |     |     |     |     |     |     |     |     |     |
| 28  |   |   |   |r8 |r8 |r8 | s23| s24|    |     | r8  |     |     |     |     |     |     |     |     |     |     |
| 29  |   |   |   |r9 |r9 |r9 | s23| s24|    |     | r9  |     |     |     |     |     |     |     |     |     |     |
| 30  |   |   |   |r11|r11|r11| r11| r11|    |     | r11 |     |     |     |     |     |     |     |     |     |     |
| 31  |   |   |   |r12|r12|r12| r12| r12|    |     | r12 |     |     |     |     |     |     |     |     |     |     |
| 32  |   |   |   |r16|r16|r16| r16| r16|    |     | r16 |     |     |     |     |     |     |     |     |     |     |

**Разбор предложения `int a = 4; b = (a + 3) * 2;`**

| Стек                                   | Вход                          | Действие                     |
|----------------------------------------|-------------------------------|------------------------------|
| I₀                                     | int a = 4; b = (a + 3) * 2; $ | s6 (shift int)               |
| I₀ int I₆                              | a = 4; b = (a + 3) * 2; $     | s9 (shift ID)                |
| I₀ int I₆ ID I₉                        | = 4; b = (a + 3) * 2; $       | s11 (shift =)                |
| I₀ int I₆ ID I₉ = I₁₁                  | 4; b = (a + 3) * 2; $         | s15 (shift IntLiteral)       |
| I₀ int I₆ ID I₉ = I₁₁ IntLiteral I₁₅   | ; b = (a + 3) * 2; $          | r14 (Factor → IntLiteral)    |
| I₀ int I₆ ID I₉ = I₁₁                  | ; b = (a + 3) * 2; $          | goto Factor → I₁₄            |
| I₀ int I₆ ID I₉ = I₁₁ Factor I₁₄       | ; b = (a + 3) * 2; $          | r13 (Term → Factor)          |
| I₀ int I₆ ID I₉ = I₁₁                  | ; b = (a + 3) * 2; $          | goto Term → I₁₃              |
| I₀ int I₆ ID I₉ = I₁₁ Term I₁₃         | ; b = (a + 3) * 2; $          | r10 (Expression → Term)      |
| I₀ int I₆ ID I₉ = I₁₁                  | ; b = (a + 3) * 2; $          | goto Expression → I₁₉        |
| I₀ int I₆ ID I₉ = I₁₁ Expression I₁₉   | ; b = (a + 3) * 2; $          | s27 (shift ;)                |
| I₀ int I₆ ID I₉ = I₁₁ Expression I₁₉ ; I₂₇ | b = (a + 3) * 2; $        | r6 (Declaration → int ID = Expression ;) |
| I₀                                     | b = (a + 3) * 2; $            | goto Declaration → I₄        |
| I₀ Declaration I₄                      | b = (a + 3) * 2; $            | r4 (Statement → Declaration) |
| I₀                                     | b = (a + 3) * 2; $            | goto Statement → I₃          |
| I₀ Statement I₃                        | b = (a + 3) * 2; $            | r2 (StatementList → Statement) |
| I₀                                     | b = (a + 3) * 2; $            | goto StatementList → I₂      |
| I₀ StatementList I₂                    | b = (a + 3) * 2; $            | s7 (shift ID)                |
| I₀ StatementList I₂ ID I₇              | = (a + 3) * 2; $              | s10 (shift =)                |
| I₀ StatementList I₂ ID I₇ = I₁₀        | (a + 3) * 2; $                | s17 (shift ()                |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇  | a + 3) * 2; $                 | s16 (shift ID)               |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ ID I₁₆ | + 3) * 2; $         | r15 (Factor → ID)            |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇  | + 3) * 2; $                   | goto Factor → I₁₄            |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Factor I₁₄ | + 3) * 2; $          | r13 (Term → Factor)          |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇  | + 3) * 2; $                   | goto Term → I₁₃              |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Term I₁₃ | + 3) * 2; $           | r10 (Expression → Term)      |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇  | + 3) * 2; $                   | goto Expression → I₂₅        |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ | + 3) * 2; $   | s21 (shift +)                |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ + I₂₁ | 3) * 2; $ | s15 (shift IntLiteral) |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ + I₂₁ IntLiteral I₁₅ | ) * 2; $ | r14 (Factor → IntLiteral) |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ + I₂₁ | ) * 2; $ | goto Factor → I₁₄ |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ + I₂₁ Factor I₁₄ | ) * 2; $ | r13 (Term → Factor) |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ + I₂₁ | ) * 2; $ | goto Term → I₂₈ |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ + I₂₁ Term I₂₈ | ) * 2; $ | r8 (Expression → Expression + Term) |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ | ) * 2; $ | s32 (shift )) |
| I₀ StatementList I₂ ID I₇ = I₁₀ ( I₁₇ Expression I₂₅ ) I₃₂ | * 2; $ | r16 (Factor → ( Expression )) |
| I₀ StatementList I₂ ID I₇ = I₁₀        | * 2; $                        | goto Factor → I₁₄            |
| I₀ StatementList I₂ ID I₇ = I₁₀ Factor I₁₄ | * 2; $                 | r13 (Term → Factor)          |
| I₀ StatementList I₂ ID I₇ = I₁₀        | * 2; $                        | goto Term → I₁₃              |
| I₀ StatementList I₂ ID I₇ = I₁₀ Term I₁₃ | * 2; $                 | s23 (shift *)                |
| I₀ StatementList I₂ ID I₇ = I₁₀ Term I₁₃ * I₂₃ | 2; $           | s15 (shift IntLiteral)       |
| I₀ StatementList I₂ ID I₇ = I₁₀ Term I₁₃ * I₂₃ IntLiteral I₁₅ | ; $ | r14 (Factor → IntLiteral) |
| I₀ StatementList I₂ ID I₇ = I₁₀ Term I₁₃ * I₂₃ | ; $           | goto Factor → I₃₀            |
| I₀ StatementList I₂ ID I₇ = I₁₀ Term I₁₃ * I₂₃ Factor I₃₀ | ; $ | r11 (Term → Term * Factor) |
| I₀ StatementList I₂ ID I₇ = I₁₀        | ; $                           | goto Term → I₁₃              |
| I₀ StatementList I₂ ID I₇ = I₁₀ Term I₁₃ | ; $                 | r10 (Expression → Term)      |
| I₀ StatementList I₂ ID I₇ = I₁₀        | ; $                           | goto Expression → I₁₂        |
| I₀ StatementList I₂ ID I₇ = I₁₀ Expression I₁₂ | ; $                 | s20 (shift ;)                |
| I₀ StatementList I₂ ID I₇ = I₁₀ Expression I₁₂ ; I₂₀ | $             | r7 (Assignment → ID = Expression ;) |
| I₀ StatementList I₂                     | $                             | goto Assignment → I₅         |
| I₀ StatementList I₂ Assignment I₅       | $                             | r5 (Statement → Assignment)  |
| I₀ StatementList I₂                     | $                             | goto Statement → I₈          |
| I₀ StatementList I₂ Statement I₈        | $                             | r3 (StatementList → StatementList Statement) |
| I₀ StatementList I₂                     | $                             | goto StatementList → I₂      |
| I₀ StatementList I₂                     | $                             | r1 (Program → StatementList) |
| I₀                                     | $                             | goto Program → I₁            |
| I₀ Program I₁                          | $                             | acc                    |

**optional: дерево состояний в черновом варианте (здесь стартовое состояние I0 записано в полном виде)**
![StateTree (на всякий случай)](https://github.com/user-attachments/assets/e2b02798-e4ae-4a1f-8abf-fcd82b797f22)
![StateTreeContinue](https://github.com/user-attachments/assets/7ea61be1-3b4b-4b10-86f6-f24f05debc47)
