#pragma once
/*

�б༭��
��Ŀ����
��֪���б༭���𣿲�֪��Ҳû��ϵ�������һ�����㣺
1.������յ�һ��
����
��һ����һ������T��������T�����ݡ�
ÿ�����ݵĿ�ʼʱһ���ַ������ַ�������С��100��ÿ���ַ�һ����(
��������
3
whli##ilr#e(s#*s)
outcha@putchar(*s=#++)
returnWA##A!!##C
 

���
ÿ���������һ�о����б༭���༭�����ַ�����������Կ�������
�������
while(*s)
putchar(*s++)
returnAC

*/
#include <iostream>
using namespace std;
char c[50][101];

void my_flush(char* desc, char* src)
{
    while (*src != '\0')
    {
        *desc = *src;
        desc++;
        src++;
    }
    *desc = '\0';
}

char * line_deal(char* pc)
{
   
    //  @ ֻ���������ַ�
    // A##A ->   A            A!!##C -> AC
    char* cur = pc;
        char* houtou = cur - 1;
    while (*cur != '\0' )
    {
        if (*cur == '@')
        {
            houtou = cur;
        }
        cur++;
    }
    cur = houtou + 1;
    char* new_head = cur;
    while (*cur != '\0')
    {
        if (*cur == '#')
        {
            
                
                if (*(cur + 1) == '\0' && cur != new_head)
                {
                    *(cur - 1) = 0;
                }
                else
                {
                    my_flush(cur -1, cur +1);
                }


                    cur = cur - 1;
                     continue;      
        }
         cur++;  
    }

    return new_head;
}

void test_line()
{
    int n;
    while (scanf("%d",&n) != EOF)
    {
         for (int i = 0; i < n; i++)
        {
            scanf("%s", c[i]);
        }

         for (int i = 0; i < n; i++)
        {
            printf("%s\n", line_deal(c[i]));
        }
    }

   

}

