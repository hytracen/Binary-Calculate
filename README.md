# BinaryCalculate
> 四川大学-游戏编程实践-基于二叉树的四则运算-实验代码

# 运行说明

可使用CLion 2020.3.2打开本工程并运行，或直接运行 cmake-build-debug 文件夹下的Week03.exe

# 输入

不带空格和等号的运算表达式，例如：3+5

# 输出

运算结果以及二叉树的层序输出结果

![img](file:///C:/Users/Yoyotao/AppData/Local/Temp/msohtmlclip1/01/clip_image002.jpg)

# 可处理的运算表达式

1、运算符可包含 +、-、*、/、^，并可以在不加括号的情况下根据运算符优先级计算表达式

2、可处理多位浮点数，包括负数（ 输入需符合规范，如：-3+3、3+(-3) ）

# 可处理的输入错误

1、括号不匹配

2、除数为0（例如7/0）

3、数字前存在多余的0（例如000.567）

4、小数点位于错误的位置（例如 .03、03.）

5、运算符位于错误的位置（例如 3++3）

6、输入不属于表达式的特殊符号（例如 #、&等）