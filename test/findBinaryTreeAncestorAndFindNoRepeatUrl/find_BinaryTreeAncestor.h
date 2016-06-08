#pragma once
#include <iostream>
using namespace std;

/****************
 * �������� ��������������Ĺ������Ƚ��
******************/

struct Node
{
    Node* left;
    Node* right;
    int value;

    Node(int v)
        :value(v)
        ,left(NULL)
        ,right(NULL)
    {}
};

// ����һ int count ����
int _find_ancestor(Node* root, Node* & ancestor, const Node* a, const Node* b)
{
    if (root == NULL)
    {
        return 0;
    }
    int count = 0;
  

    count += _find_ancestor(root->left, ancestor, a , b);

    if (root == a || root == b)
    {
        count += 1;
    }
    /*if (count == 2)
    {
        ancestor = root;
    }*/

   count += _find_ancestor(root->right, ancestor, a, b);

    if (count == 2)
    {
        ancestor = root ;
        count = 0; // ��ֹ���� ʱ ����count��ֵ����2 ���� ancestor��׼ȷ ������
    }
    
    return count;

}

void test_find_ancestor()
{
   //     1
    //  2   3
    // 4  5
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;

    Node* ancestor = NULL;
    // 4 5
   // _find_ancestor(&n1, ancestor,&n4, &n5); 

    // 2 5
   // _find_ancestor(&n1, ancestor,&n2, &n5); 

    // 5 3
     _find_ancestor(&n1, ancestor,&n5, &n3); 
}


// ������ bool�б�
bool find_ancestor_bool(Node* root, Node* & ancestor, const Node* a, const Node* b)
{
    if (root == NULL)
    {
        return false;
    }
  
    bool  b_left = find_ancestor_bool(root->left, ancestor, a, b);

    bool b_right = find_ancestor_bool(root->right, ancestor, a, b);
    
    
    if (root == a || root == b)
    {
        if (b_left || b_right)
        {
            ancestor = root;
        }

        return true;
    }

    if (b_left && b_right)
    {
        ancestor = root;
    }

    return b_left || b_right;

}


void test_find_ancestor_bool()
{
   //     1
    //  2   3
    // 4  5
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;

    Node* ancestor = NULL;
    // 4 5
    //find_ancestor_bool(&n1, ancestor,&n4, &n5); 

    // 2 5
   // find_ancestor_bool(&n1, ancestor,&n2, &n5); 

    // 5 3
    // find_ancestor_bool(&n1, ancestor,&n5, &n3); 
     // 1 5
     find_ancestor_bool(&n1, ancestor,&n1, &n5); 
}

// ����3 ����ջ ����� ���� ��¼ �ҵ����� ·��  ��� �������� ջ����������� �ҵ���һ�γ��ֱ���ͬ�ĵ��ǰһ�� ��Ϊ��������
// ע�� �����ǰ���� ����ʱ Ҫ����ǰѹջ�� Ԫ�ص��� ջ�����ô���
// ������ vector Ϊ�� �������
#include<vector>

void find_ancestor_vector_R(Node* root, vector<Node*>& va,vector<Node*>& vb, Node* a, Node* b, Node* &ancestor)
{
    if (root == NULL)
    {
        return;
    }

    va.push_back(root);
    vb.push_back(root);

    find_ancestor_vector_R(root->left, va, vb, a, b, ancestor);
    find_ancestor_vector_R(root->right, va, vb, a, b, ancestor);
    
    if (va.back() != a)
    {
        va.pop_back();    
    }

    if (vb.back() != b)
    {
        vb.pop_back();
    }
}

Node* find_ancestor_vector(Node* root, Node* a, Node* b)
{
    vector<Node*> va,vb;
    Node* ancestor = NULL;

    find_ancestor_vector_R(root, va, vb, a, b, ancestor);

    // ��va vb �ķֲ�� ֮ǰ�ĵ� 
    int i = 0;
    while (i < va.size() && i < vb.size() && va[i] == vb[i])
    {
        ancestor = va[i];
        i++;
    }

    return ancestor;
}

void  test_find_ancestor_vector()
{
    //     1
    //  2   3
    // 4  5
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;

    Node* ancestor = NULL;
    // 4 5
    ancestor = find_ancestor_vector(&n1, &n4, &n5); 

    // 2 5
    ancestor = find_ancestor_vector(&n1, &n2, &n5); 

    // 5 3
    ancestor = find_ancestor_vector(&n1, &n5, &n3); 
     // 1 5
     ancestor = find_ancestor_vector(&n1, &n1, &n5); 
}

