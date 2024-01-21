#include <stdio.h>
#include <stdlib.h>

// 检查字符是否为数字
int isNumber(char c)
{
    return c >= '0' && c <= '9';
}

// 检查字符是否为运算符
int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 执行运算
int calculate(int num1, int num2, char op)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        return 0;
    }
}

// 解析并计算表达式
int evaluateExpression(const char *expr)
{
    int numbers[128], numbersTop = -1, operatorsTop = -1;
    char operators[128];

    for (int i = 0; expr[i]; ++i)
    {

        if (expr[i] == ' ') // 当为空格时继续向前
            continue;

        if (isNumber(expr[i])) //
        {
            int num = 0;
            while (expr[i] && isNumber(expr[i])) // 当两位及以上数字时，进行判断
            {
                num = num * 10 + (expr[i] - '0');
                ++i;
            }
            --i;
            numbers[++numbersTop] = num; // 先把全部数字入栈
        }

        else if (expr[i] == '(') // 右括号入栈
        {
            operators[++operatorsTop] = expr[i];
        }

        else if (expr[i] == ')') // 当遇到右括号时，开始执行循环，直到遇到左括号。
        {
            while (operatorsTop != -1 && operators[operatorsTop] != '(')
            {
                int num2 = numbers[numbersTop--];
                int num1 = numbers[numbersTop--];
                char op = operators[operatorsTop--];               // 运算符出栈计算
                numbers[++numbersTop] = calculate(num1, num2, op); // 先计算配对括号里的运算
            }
            operatorsTop--;
        }

        else if (isOperator(expr[i])) // 当遇到运算符时，开始执行循环，直到运算符栈为空或者栈顶的运算符不是运算符。
        {
            while (operatorsTop != -1 && isOperator(operators[operatorsTop]))
            {
                int num2 = numbers[numbersTop--];
                int num1 = numbers[numbersTop--];
                char op = operators[operatorsTop--];
                numbers[++numbersTop] = calculate(num1, num2, op);
            }
            operators[++operatorsTop] = expr[i];
        }
    }

    while (operatorsTop != -1) // 当处理完所有的字符后，如果运算符栈中还有运算符，那么继续执行循环，直到运算符栈为空。
    {
        int num2 = numbers[numbersTop--];
        int num1 = numbers[numbersTop--];
        char op = operators[operatorsTop--];
        numbers[++numbersTop] = calculate(num1, num2, op);
    }

    return numbers[0];
}

int checkBrackets(const char *expr)
{
    int count = 0;
    for (int i = 0; expr[i]; ++i)
    {
        if (expr[i] == '(')
        {
            ++count;
        }
        else if (expr[i] == ')')
        {
            --count;
        }
        if (count < 0)
        {
            return 0; // 发现一个右括号，但没有相应的左括号与之配对
        }
    }
    return count == 0; // 如果所有的括号都正确配对，那么count应该为0
}

int main()
{
    char expr[128];

    printf("请输入算式：\n");

    fgets(expr, 128, stdin);

    if (!checkBrackets(expr))
    {
        printf("错误：括号没有正确配对。\n");
        return 1;
    }
    
    printf("结果是：%d\n", evaluateExpression(expr));

    return 0;

}