#include <iostream>

int main()
{
    //通过死循环来让代码一直执行，便于测试
    while (1)
    {
        //通过指针动态创建内存
        char *ptd;
        ptd = (char *)malloc((10) * sizeof(char));

        // 输入数组，通过这样写可以防止输入的数组不足10个，读取随机的值
        int count = 0;
        for (int i = 0; i < 10; i++)
        {
            if (std::cin >> ptd[i])
            {
                count++;
            }
            else
            {
                break;
            }
        }

        //冒泡法排序
        for (int i = 0; i < count - 1; i++)
        {
            for (int n = i + 1; n < count; n++)
            {
                char exchange;
                if (ptd[n]<ptd[i])
                {
                    exchange = ptd[n];
                    ptd[n] = ptd[i];
                    ptd[i] = exchange;
                } 
            }
        }

        //输出
        for (int i = 0; i < count; i++)
        {
            std::cout  << ptd[i] << " ";
        }

        //释放内存
        delete[] ptd;
    }

    return 0;
}
