# 1 задание

/*

ТОКЕНЫ:

Строки (StringLiteral)
"..."

Целые числа (IntLiteral)
1234
-23
-0  (=0)

ID'шники (ID)
Терминалы, состоящие из букв английского алфавита Aa-Zz и (опционально) цифр 0-9,
такие что в начале терминала должна стоять буква
(Проще говоря, как название любой функции или переменной в С)

*/

<TryCatchBlock> ::= <TryBlock><CatchBlock> | <TryCatchBlock><CatchBlock>

<TryBlock> ::= try <Block>
<CatchBlock> ::= catch (ID ID) <Block>

<Block> ::= {<StatementList>}

<StatementList> ::= ^ | <NonEmptyStatementList>

<NonEmptyStatementList> ::= <Statement> | <NonEmptyStatementList><Statement>

<Statement> ::= <TryCatchBlockStatement> | <ThrowStatement> | <PrintStatement>

<TryCatchBlockStatement> ::= <TryCatchBlock>;

<ThrowStatement> ::= throw <Exception>;
<Exception> ::= new ID(<Expression>) | ID

<PrintStatement> ::= print(<Expression>);

<Expression> ::= StringLiteral | IntLiteral
/* 
ПРИМЕР:

try {
    print("Trying 1");
    print("Trying 2");
    try {
        print("Success");
    } catch {
        throw Ex1;
    };
} catch (Ex1 e) {
    throw new E(1);
} catch (Ex2 e) {
    throw new Ex2("Desctiption");
}


Преобразуется в последовательность токенов

1.
try {
    print(StringLiteral);
    print(StringLiteral);
    try {
        print(StringLiteral);
    } catch {
        throw ID;
    };
} catch (ID ID) {
    throw new ID(IntLiteral);
} catch (ID ID) {
    throw new ID(StringLiteral);
}

2.
try {
    print(<Expression>);
    print(<Expression>);
    try {
        print(<Expression>);
    } catch {
        throw ID;
    };
} catch (ID ID) {
    throw new ID(<Expression>);
} catch (ID ID) {
    throw new ID(<Expression>);
}

3.
try {
    print(<Expression>);
    print(<Expression>);
    try {
        print(<Expression>);
    } catch {
        throw <Exception>;
    };
} catch (ID ID) {
    throw <Exception>;
} catch (ID ID) {
    throw <Exception>;
}

4.
try {
    <PrintStatement>
    <PrintStatement>
    try {
        <PrintStatement>
    } catch {
        <ThrowStatement>
    };
} catch (ID ID) {
    <ThrowStatement>
} catch (ID ID) {
    <ThrowStatement>
}

5.
try {
    <Statement>
    <Statement>
    try {
        <Statement>
    } catch {
        <Statement>
    };
} catch (ID ID) {
    <Statement>
} catch (ID ID) {
    <Statement>
}

6.
try {
    <StatementList>
    <Statement>
    try <Block> catch <Block>;
} 
catch (ID ID) <Block>
catch (ID ID) <Block>

7.
try {
    <StatementList>
    <TryCatchBlockStatement>
} 
catch (ID ID) <Block>
catch (ID ID) <Block>

8.
try {
    <StatementList>
    <Statement>
} 
catch (ID ID) <Block>
catch (ID ID) <Block>


9.
try {
    <StatementList>
} 
catch (ID ID) <Block>
catch (ID ID) <Block>

10.
try <Block> 
catch (ID ID) <Block>
catch (ID ID) <Block>

11.
<TryBlock>
<CatchBlock>
<CatchBlock>

12.
<TryCatchBlock>
<CatchBlock>

13.
<TryCatchBlock>
*/

# 2 и 4 задания

## Грамматика

### Вид : Контекстно-свободная
тк все правила имеют вид A -> B, где A - одиночный нетерминал, а B - цепочка терминалов и/или нетерминалов

Грамматика не является регулярной, тк
регулярные грамматики допускают только правила вида:
- A → aB
- A → Ba
- A → a 

правила нарушающие это ограничение:
<TryCatchBlock> ::= <TryBlock><CatchBlock> (A -> BC)
<StatementList> ::= <StatementList><Statement> (A -> AB)

### Однозначность: Однозначная

Полный набор правил:
0. S' -> <TryCatchBlock> (стартовое правило)
1. <TryCatchBlock> -> <TryBlock><CatchBlock>
2. <TryCatchBlock> -> <TryCatchBlock><CatchBlock>
3. <TryBlock> -> try <Block>
4. <CatchBlock> -> catch (ID ID) <Block>
5. <Block> -> {<StatementList>}
6. <StatementList> -> ^
7. <StatementList> -> <NonEmptyStatementList>
8. <NonEmptyStatementList> -> <Statement>
9. <NonEmptyStatementList> -> <NonEmptyStatementList><Statement>
10. <Statement> -> <TryCatchBlockStatement>
11. <Statement> -> <ThrowStatement>
12. <Statement> -> <PrintStatement>
13. <TryCatchBlockStatement> -> <TryCatchBlock>;
14. <ThrowStatement> -> throw <Exception>;
15. <Exception> -> new ID(<Expression>)
16. <Exception> -> ID
17. <PrintStatement> -> print(<Expression>);
18. <Expression> -> StringLiteral
19. <Expression> -> IntLiteral

FIRST(S') = { try }
FIRST(<TryCatchBlock>) = { try }
FIRST(<TryBlock>) = { try }
FIRST(<CatchBlock>) = { catch }
FIRST(<Block>) = { `{` }
FIRST(<StatementList>) = { try, throw, print, ^ }
FIRST(<NonEmptyStatementList>) = { try, throw, print }
FIRST(<Statement>) = { try, throw, print }
FIRST(<TryCatchBlockStatement>) = { try }
FIRST(<ThrowStatement>) = { throw }
FIRST(<Exception>) = { new, ID }
FIRST(<PrintStatement>) = { print }
FIRST(<Expression>) = { StringLiteral , IntLiteral }

FOLLOW(S') = { $ }
FOLLOW(<TryCatchBlock>) = { catch , `;`, $ }
FOLLOW(<TryBlock>) = { catch }
FOLLOW(<CatchBlock>) = { catch , `;`, $ }
FOLLOW(<Block>) = { catch , `;`, $ }
FOLLOW(<StatementList>) = { `}` }
FOLLOW(<NonEmptyStatementList>) = { `}`, try, throw, print }
FOLLOW(<Statement>) = { `}`, try, throw, print }
FOLLOW(<TryCatchBlockStatement>) = { `}`, try, throw, print }
FOLLOW(<ThrowStatement>) = { `}`, try, throw, print }
FOLLOW(<Exception>) = { `;` }
FOLLOW(<PrintStatement>) = { `}`, try, throw, print }
FOLLOW(<Expression>) = { `)` }

LR(0) коллекция:

-----------------------

I_0 = closure( S -> * <TryCatchBlock> )
S -> * <TryCatchBlock>
<TryCatchBlock> -> * <TryBlock><CatchBlock>
<TryCatchBlock> -> * <TryCatchBlock><CatchBlock>
<TryBlock>      -> * try <Block>

I_1 = goto(I_0, <TryCatchBlock>)
S -> <TryCatchBlock> *
<TryCatchBlock> -> <TryCatchBlock> * <CatchBlock>
<CatchBlock>    -> * catch (ID ID) <Block>

I_2 = goto(I_0, <TryBlock>) = goto(I_7, <TryBlock>) = goto(I_10, <TryBlock>)
<TryCatchBlock> -> <TryBlock> * <CatchBlock>
<CatchBlock>    -> * catch (ID ID) <Block> 

I_3 = goto(I_0, try) = goto(I_7, try) = goto(I_10, try)
<TryBlock>      -> try * <Block>
<Block>         -> * { <StatementList> }

I_4 = goto(I_1, <CatchBlock>) = goto(I_15, <CatchBlock>)
<TryCatchBlock> -> <TryCatchBlock> <CatchBlock> *

I_5 = goto(I_1, catch) = goto(I_2, catch) = goto(I_15, catch)
<CatchBlock>    -> catch * (ID ID) <Block>

I_6 = goto(I_3, <Block>)
<TryBlock>      -> try <Block> *

I_7 = goto(I_3, `{`) = goto(I_20, `{`)
<Block>         -> { * <StatementList> }
<StatementList> -> *
<StatementList> -> * <NonEmptyStatementList>
<NonEmptyStatementList> -> * <Statement>
<NonEmptyStatementList> -> * <NonEmptyStatementList><Statement>
<Statement>     ->  * <TryCatchBlockStatement>
<Statement>     ->  * <ThrowStatement>
<Statement>     ->  * <PrintStatement>
<TryCatchBlockStatement> -> * <TryCatchBlock> ;
<TryCatchBlock> -> * <TryBlock><CatchBlock>
<TryCatchBlock> -> * <TryCatchBlock><CatchBlock>
<TryBlock>      -> * try <Block>
<ThrowStatement> -> * throw <Exception> ;
<PrintStatement> -> * print ( <Expression> ) ;

I_8 = goto(I_5, `(`)
<CatchBlock>    -> catch ( * ID ID) <Block>

I_9 = goto(I_7, <StatementList>)
<Block>         -> { <StatementList> * }

I_10 = goto(I_7, <NonEmptyStatementList>)
<StatementList> -> <NonEmptyStatementList> *
<NonEmptyStatementList> -> <NonEmptyStatementList> * <Statement>
<Statement>     ->  * <TryCatchBlockStatement>
<Statement>     ->  * <ThrowStatement>
<Statement>     ->  * <PrintStatement>
<TryCatchBlockStatement> -> * <TryCatchBlock> ;
<TryCatchBlock> -> * <TryBlock><CatchBlock>
<TryCatchBlock> -> * <TryCatchBlock><CatchBlock>
<TryBlock>      -> * try <Block>
<ThrowStatement> -> * throw <Exception> ;
<PrintStatement> -> * print ( <Expression> ) ;

I_11 = goto(I_7, <Statement>)
<NonEmptyStatementList> -> <Statement> *

I_12 = goto(I_7, <TryCatchBlockStatement>) = goto(I_10, <TryCatchBlockStatement>)
<Statement>     ->  <TryCatchBlockStatement> *

I_13 = goto(I_7, <ThrowStatement>) = goto(I_10, <ThrowStatement>)
<Statement>     ->  <ThrowStatement> *

I_14 = goto(I_7, <PrintStatement>) = goto(I_10, <PrintStatement>)
<Statement>     ->  <PrintStatement> *

I_15 = goto(I_7, <TryCatchBlock>) = goto(I_10, <TryCatchBlock>)
<TryCatchBlockStatement> -> <TryCatchBlock> * ;
<TryCatchBlock> -> <TryCatchBlock> * <CatchBlock>
<CatchBlock>    -> * catch (ID ID) <Block>

I_16 = goto(I_7, throw) = goto(I_10, throw)
<ThrowStatement> -> throw * <Exception> ;
<Exception> -> * new ID(<Expression>)
<Exception> -> * ID

I_17 = goto(I_7, print) = goto(I_10, print)
<PrintStatement> -> print * ( <Expression> ) ;

I_18 = goto(I_8, ID)
<CatchBlock>    -> catch ( ID * ID) <Block>

I_19 = goto(I_18, ID)
<CatchBlock>    -> catch ( ID ID *) <Block>

I_20 = goto(I_19, `)`)
<CatchBlock>    -> catch ( ID ID ) * <Block>
<Block>         -> * { <StatementList> }

I_21 = goto(I_20, <Block>)
<CatchBlock>    -> catch ( ID ID ) <Block> *

I_22 = goto(I_9, `}`)
<Block>         -> { <StatementList> } *

I_23 = goto(I_10, <Statement>)
<NonEmptyStatementList> -> <NonEmptyStatementList> <Statement> *

I_24 = goto(I_15, `;`)
<TryCatchBlockStatement> -> <TryCatchBlock>; *

I_25 = goto(I_16, <Exception>)
<ThrowStatement> -> throw <Exception> * ;

I_26 = goto(I_25, `;`)
<ThrowStatement> -> throw <Exception>; *

I_27 = goto(I_16, new)
<Exception> -> new * ID(<Expression>)

I_28 = goto(I_27, ID)
<Exception> -> new ID * (<Expression>)

I_29 = goto(I_28, `(`)
<Exception> -> new ID ( * <Expression> )
<Expression> -> * StringLiteral
<Expression> -> * IntLiteral

I_30 = goto(I_29, <Expression>)
<Exception> -> new ID ( <Expression> * )

I_31 = goto(I_30, `)`)
<Exception> -> new ID ( <Expression> ) *

I_32 = goto(I_29, StringLiteral) = goto(I_35, StringLiteral)
<Expression> -> StringLiteral *

I_33 = goto(I_29, IntLiteral) = goto(I_35, IntLiteral)
<Expression> -> IntLiteral *

I_34 = goto(I_16, ID)
<Exception> -> ID * 

I_35 = goto(I_17, `(`)
<PrintStatement> -> print ( * <Expression> ) ;
<Expression> -> * StringLiteral
<Expression> -> * IntLiteral

I_36 = goto(I_35, <Expression>)
<PrintStatement> -> print ( <Expression> * ) ;

I_37 = goto(I_36, `)`)
<PrintStatement> -> print ( <Expression> ) * ;

I_38 = goto(I_37, `;`)
<PrintStatement> -> print ( <Expression> ) ; *

I_39 = goto(I_2, <CatchBlock>)
<TryCatchBlock> -> <TryBlock> <CatchBlock> *
-----------------------

Нетерминалы:
try catch { } ; throw print new ID StringLiteral IntLiteral ( ) $

Терминалы: 
<TryCatchBlock>
<TryBlock>
<CatchBlock>
<Block>
<StatementList>
<NonEmptyStatementList>
<Statement>
<TryCatchBlockStatement>
<ThrowStatement>
<PrintStatement>
<Exception>
<Expression>

таблицы Action и Goto SLR(1) таблицы (отсутствие подходящего пункта = ERR) :

-----------------------------

i_0
ACTION:
    try -> shift 3
GOTO:
    <TryCatchBlock> -> goto 1
    <TryBlock> -> goto 2

i_1
ACTION:
    $ -> ACC
    catch -> shift 5
GOTO:
    <CatchBlock> -> goto 4

i_2
ACTION:
    catch -> shift 5
GOTO:
    <CatchBlock> -> goto 4

i_3
ACTION:
    `{` -> shift 7
GOTO:
    <Block> -> goto 6

i_4
ACTION:
    catch -> reduce 2
    `;` -> reduce 2
    $  -> reduce 2

i_5
ACTION:
    `(` -> shift 8

i_6
ACTION:
    catch -> reduce 3

i_7
ACTION:
    throw -> shift 16
    print -> shift 17
    try -> shift 3
    `}` -> reduce 6
GOTO:
    <StatementList> -> goto 9
    <NonEmptyStatementList> -> goto 10
    <Statement> -> goto 11
    <TryCatchBlockStatement> -> goto 12
    <ThrowStatement> -> goto 13
    <PrintStatement> -> goto 14
    <TryCatchBlock> -> goto 15
    <TryBlock> -> goto 2


i_8
ACTION:
    ID -> shift 18

i_9
ACTION:
    `}` -> shift 22

i_10
ACTION:
    try -> shift 3
    throw -> shift 16
    print -> shift 17
    `}` -> reduce 7
GOTO:
    <Statement> -> goto 23
    <TryCatchBlock> -> goto 15
    <TryCatchBlockStatement> -> goto 12
    <ThrowStatement> -> goto 13
    <PrintStatement> -> goto 14
    <TryBlock> -> goto 2

i_11
ACTION:
    `}` -> reduce 8
    try -> reduce 8
    throw -> reduce 8
    print -> reduce 8

i_12
ACTION:
    `}` -> reduce 10
    try -> reduce 10
    throw -> reduce 10
    print -> reduce 10

i_13
ACTION:
    `}` -> reduce 11
    try -> reduce 11
    throw -> reduce 11
    print -> reduce 11

i_14
ACTION:
    `}` -> reduce 12
    try -> reduce 12
    throw -> reduce 12
    print -> reduce 12

i_15
ACTION:
    catch -> shift 5
    `;` -> shift 24
GOTO:
    <CatchBlock> -> goto 4

i_16
ACTION:
    new -> shift 27
    ID -> shift 34
GOTO:
    <Exception> -> goto 25

i_17
ACTION:
    `(` -> shift 35

i_18
ACTION:
    ID -> shift 19

i_19
ACTION:
    `)` -> shift 20

i_20
ACTION:
    `{` -> shift 7
GOTO:
    <Block> -> goto 21

i_21
ACTION:
    catch -> reduce 4
    `;` -> reduce 4
    $ -> reduce 4

i_22
ACTION:
    catch -> reduce 5
    `;` -> reduce 5
    $ -> reduce 5

i_23
ACTION:
    `}` -> reduce 9
    try -> reduce 9
    throw -> reduce 9
    print -> reduce 9

i_24
ACTION:
    `}` -> reduce 13
    try -> reduce 13
    throw -> reduce 13
    print -> reduce 13

i_25
ACTION:
    `;` -> shift 26

i_26
ACTION:
    `}` -> reduce 14
    try -> reduce 14
    print -> reduce 14
    throw -> reduce 14

i_27
ACTION:
    ID -> shift 28

i_28
ACTION:
    `(` -> shift 29

i_29
ACTION:
    StringLiteral -> shift 32
    IntLiteral -> shift 33
GOTO:
    <Expression> -> goto 30

i_30
ACTION:
    `(` -> shift 31

i_31
ACTION:
    `;` -> reduce 15

i_32
ACTION:
    `)` -> reduce 18

i_33
ACTION:
    `)` -> reduce 19

i_34
ACTION:
    `;` -> reduce 16

i_35
ACTION:
    StringLiteral -> shift 32
    IntLiteral -> shift 33
GOTO:
    <Expression> -> goto 36

i_36
ACTION:
    `)` -> shift 37

i_37
ACTION:
    `;` -> shift 38

i_38
ACTION:
    `}` -> reduce 17
    try -> reduce 17
    throw -> reduce 17
    print  -> reduce 17

i_39
ACTION:
    catch -> reduce 1
    `;` -> reduce 1
    $ -> reduce 1

-----------------------------

В процессе построения SLR(1) таблицы никаких конфликтов не возникло => Грамматика однозначна.
( РЕШЕНИЕ ЗАДАНИЯ 4 )

## Язык

### Вид : Контекстно-свободный
Поскольку:
- Порождается контекстно-свободной грамматикой
- Не требует контекстных ограничений для синтаксического разбора
- Не может быть описан конечным автоматом (из-за рекурсивной вложенности)

Рассмотрим
w_n = try { w_(n-1) } catch (E e) {}
w_1 = try { } catch (E e) {}

<A> ::= try {
<B> ::= } catch {} 

w_n = A^n B^n

Если лемма о разрастании выполняется для данного языка, то
возьмём n = p - константе из леммы
|w_n| >= 2p > p. Значит существует разбиение w = xyz такое что
|xy| <= p
|y| > 0
для любого k>=0 xy^kz принадлежит языку

Из-за первого условия y может быть только в половине с A:
y = A^j
Но тогда xy^2z = xyyz не принадлежит языку, тк A не балансируют с B, те появляются структуры
try { try { ... try {} try {} catch (...) {...} ...} catch (...) {...} } catch (...) {...}
с двумя try подряд, что не принадлежит языку

Брать y не равным try {} нельзя, поскольку:
1. y = try
Аналогично не принадлежит языку
try try {}
2. y = {...}
Аналогично не принадлежит языку из-за структур try {...} {...}
3. Прочие разбиения
Прочие разбиения не соблюдают баланс скобок { }, и также не принадлежат языку

Значит, лемма о разрастании неверна для этого языка, 
значит язык не регулярный,
значит он контекстно-свободный

### Однозначность : Однозначная
Язык порождается однозначной грамматикой -> язык по определению однозначен