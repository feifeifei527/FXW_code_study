#include <iostream>

int main()
{
   while(1) 
   {
       char *ptd;
       ptd = (char *)malloc((10) * sizeof(char));

       for (int i = 0; i < 10; i++)
       {
           std::cin >> ptd[i];
       }

       for (int i = 0; i < 9; i++)
       {
           for (int n = i + 1; n < 10; n++)
           {
               char exchange;
               if (ptd[i] > ptd[n])
               {

                   exchange = ptd[n];
                   ptd[n] = ptd[i];
                   ptd[i] = exchange;
               }
           }
       }

       for (int i = 0; i < 10; i++)
       {
           std::cout << "p[" << i << "] = " << ptd[i] << std::endl;
       }

       free(ptd);
   }
   
   return 0;
}