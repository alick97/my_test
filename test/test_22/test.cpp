#define _CRT_SECURE_NO_WARNINGS 1


#include <iostream>
#include <string>
#include <queue>
using namespace std;

/*   ���� ������1 */

//4��7�������������֣����Ƕ��壬ʮ���Ʊ�ʾ�У�ÿһλֻ��4��7�������������������������֡�ǰ������������Ϊ��4,7,44,47,74,77,444,447... 




void getnum(int n)
{
    queue<string> q;
   
    string ret ;
   // bool is_4 = true;
 
   q.push("4");
    q.push("7");
    while (n > 0 && !q.empty())
    {
        ret = q.front();
        
      
            q.pop();
    
            q.push(ret + "4");
            q.push(ret + "7");
    
        n--;
    }
    if (ret.size())
    {
    cout<<ret<<endl;
    }
}



int main()
{
    int n = 0;
     while (cin>>n)
     {
         int count = n; // Ҫ�������ݵĸ���
         for (int i = 0; i < count; i++)
         {cin>>n;
             getnum(n);}
     }

    return 0;
}
