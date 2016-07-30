#pragma once

#include"Heap.h"
#include <assert.h>
#include <iostream>
using namespace std;
template <class T>
struct HuffmanNode
{
    HuffmanNode<T>* _left;
    HuffmanNode<T>* _right;
    T _weight; // Ȩ��

    HuffmanNode()
        :_left(NULL)
        ,_right(NULL)
    {}

    HuffmanNode(T weight)
        :_left(NULL)
        ,_right(NULL)
        ,_weight(weight)
    {}

    bool operator<(const HuffmanNode<T>& h) const
    {
       return  _weight < h._weight;
    }

};


template <class T>
class HuffmanTree
{
    typedef HuffmanNode<T> Node;
public:
    HuffmanTree()
        :_root(NULL)
    {}

    HuffmanTree(const T* arr, size_t size, const T& invalid)
    {
        assert(arr);
        _root = _CreatTree(arr, size, invalid);
    }

    Node* GetRootNode()
    {
        return _root;
    }

    ~HuffmanTree()
    {
        _delete(_root);
    }

protected:
    Node*  _CreatTree(const T* arr, size_t size, const T& invalid)
    {
        assert(arr != NULL && size > 0);

        // ��С��
        Heap<Node*, Less> heap;
        Node* parent = NULL; // ��С �� ��С��ӽ��ָ��

        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] != invalid) // ����operator!=
            {
                heap.Push(new Node(arr[i])); // ����ѹ����ָ�� �Ƚ�LessҪ�ػ�һ��T* ���ػ���
            }
        }

        while (heap.Size() > 1)
        {
            Node* firstMin = heap.GetTop();
            heap.Pop();

            Node* secondMin = heap.GetTop();
            heap.Pop();

            parent = new Node(firstMin->_weight + secondMin->_weight); // ����_weight �����ǽṹ������� operator+Ҫ���� ��FileCompress.h �� struct CharInfo������
            parent->_left = firstMin;
            parent->_right = secondMin;

            // �¼����� ����ѹ�����
            heap.Push(parent);
        }

        return parent;
    }

    void _delete(Node* root)
    {
        if (root != NULL)
        {
            _delete(root->_left);
            _delete(root->_right);

            delete root;
        }
    }

private:
    Node* _root;
};