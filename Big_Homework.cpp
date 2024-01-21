#include <stdio.h>
#include <stdlib.h>

// ����ַ��Ƿ�Ϊ����
int isNumber(char c)
{
    return c >= '0' && c <= '9';
}

// ����ַ��Ƿ�Ϊ�����
int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// ִ������
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

// ������������ʽ
int evaluateExpression(const char *expr)
{
    int numbers[128], numbersTop = -1, operatorsTop = -1;
    char operators[128];

    for (int i = 0; expr[i]; ++i)
    {

        if (expr[i] == ' ') // ��Ϊ�ո�ʱ������ǰ
            continue;

        if (isNumber(expr[i])) //
        {
            int num = 0;
            while (expr[i] && isNumber(expr[i])) // ����λ����������ʱ�������ж�
            {
                num = num * 10 + (expr[i] - '0');
                ++i;
            }
            --i;
            numbers[++numbersTop] = num; // �Ȱ�ȫ��������ջ
        }

        else if (expr[i] == '(') // ��������ջ
        {
            operators[++operatorsTop] = expr[i];
        }

        else if (expr[i] == ')') // ������������ʱ����ʼִ��ѭ����ֱ�����������š�
        {
            while (operatorsTop != -1 && operators[operatorsTop] != '(')
            {
                int num2 = numbers[numbersTop--];
                int num1 = numbers[numbersTop--];
                char op = operators[operatorsTop--];               // �������ջ����
                numbers[++numbersTop] = calculate(num1, num2, op); // �ȼ�����������������
            }
            operatorsTop--;
        }

        else if (isOperator(expr[i])) // �����������ʱ����ʼִ��ѭ����ֱ�������ջΪ�ջ���ջ��������������������
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

    while (operatorsTop != -1) // �����������е��ַ�����������ջ�л������������ô����ִ��ѭ����ֱ�������ջΪ�ա�
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
            return 0; // ����һ�������ţ���û����Ӧ����������֮���
        }
    }
    return count == 0; // ������е����Ŷ���ȷ��ԣ���ôcountӦ��Ϊ0
}

int main()
{
    char expr[128];

    printf("��������ʽ��\n");

    fgets(expr, 128, stdin);

    if (!checkBrackets(expr))
    {
        printf("��������û����ȷ��ԡ�\n");
        return 1;
    }
    
    printf("����ǣ�%d\n", evaluateExpression(expr));

    return 0;

}