#pragma once
#include <string>
#include <iostream>
using namespace std;
namespace First
{
    enum State
    {
        EMPTY,
        DELETE,
        EXIST,
    };

    template<class K>
    struct __HashFunc // ������ֵ(���string��ת��������) Ĭ�ϵķ��ع�ϣ��ֵkey�� �º���
    {
        size_t operator()(const K& key)
        {
            return key;
        }
    };

    template<class K>
    class HashTable
    {
        // Key��ʽ������̽��
    public:
        HashTable(size_t capacity = 10)
            :_tables(new K[capacity])
            ,_size(0)
            ,_capacity(capacity)
            ,_states(new State[capacity])
        {
            // memset ������ �����ֽ�Ϊ��λ��ʼ���� ���ڶ�������ֵΪint
            // ������� ������ʼ��Ϊ0x00000001 �����ʼ��Ϊ0x01010101
            //memset(_states, EMPTY, sizeof(State) * capacity);
            for (size_t i = 0; i < capacity; i++)
            {
                _states[i] = EMPTY;
            }
        }

        HashTable(const HashTable<K>& ht)
            :_tables(new K[ht._capacity])
            ,_size(0)
            ,_capacity(ht._capacity)
            ,_states(new State[ht._capacity])
        {
            for (size_t i = 0; i < ht._capacity; i++)
            {
                if (EXIST == ht._states[i])
                {
                    Insert(ht._tables[i]);
                }
            }
        }

       
        
        HashTable& operator=(const HashTable<K>& ht)
        {
            if (ht._tables != _tables && ht._states != _states)
            {
                HashTable<K> tmp(ht);
                Swap(tmp);
            }

            return *this;
        }

        ~HashTable()
        {
            if (NULL != _tables)
            {
                delete[] _tables;
            }

            if (NULL != _states)
            {
                delete[] _states;
            }
        }

        bool Insert(const K& key)
        {
            // ��̬��ϣ�� �����ݵ�
            /*if (_size == _capacity)
            {
                cout<<"HashTable is full"<<endl;
                return false;
            }*/

            _CheckCapacity();  

            size_t index = _HashFunc(key);

            while (EXIST == _states[index])
            {
                index++;
                if (_capacity == index)
                {
                    index=0;
                }
            }

            _tables[index] = key;
            _states[index] = EXIST;
            _size++;
            return true;
        }

        int Find(const K& key)
        {
            size_t index = _HashFunc(key);
            size_t start = index;
            // ���� ���� ��ɾ�� ����״̬
            while (EMPTY != _states[index])
            {
                if (_tables[index] == key)
                {
                    if (_states[index] == EXIST)
                    {
                        return index;
                    }
                    else // ��ɾ�� DELETE
                    {
                        return -1;
                    }
                }

                index++;

                if (index == _capacity)
                {
                    index = 0;
                }
                // ��һȦ û�ҵ���ֹͣ ��ֹ��ѭ��
                if (index == start)
                {
                    return -1;
                }
            }

            return -1;
        }

        bool Remove(const K& key)
        {
            int index = Find(key);
            if (-1 != index)
            {
                _states[index] = DELETE;
                --_size;
                return true;
            }

            return false;
        }

        
        // ����̽���������λ�ã����費��ϣ��ͻ��
        size_t _HashFunc(const K& key)
        {
            __HashFunc<K> hf;
            return hf(key) % _capacity; //  �º���hf() 
            // ��������
            // return __HashFunc<K>()(key) % _capacity;
        }

        void Print()
        {
            for (size_t i = 0; i < _capacity; i++)
            {
                if (EXIST == _states[i])
                {
                    cout<< i << "EXIST:" << _tables[i] << endl;
                }
                else if (DELETE == _states[i])
                {
                    cout<< i << "DELETE:" << _tables[i] << endl;
                }
                else
                {
                    cout << i << "EMPTY" << _tables[i] <<endl;
                }
            }
        }

        void Swap(HashTable<K>& ht)
        {
            swap(_size, ht._size);
            swap(_states, ht._states);
            swap(_tables, ht._tables);
            swap(_capacity, ht._capacity);
        }

    protected:
        void _CheckCapacity() // ����
        {
            // ��̬�� �����ݵ�
            // ��Ч��ϣ����غ����Ӵ����0.7-0.8�Ϻ�
            if (10 * _size / _capacity >= 7)  // _size/_capacityΪ0 ��Ϊ�������� ���Գ�10
                // ��֤�غ�������0.7֮��
            {
                HashTable<K> tmp(2 * _capacity);
                for (size_t i = 0; i < _capacity; i++)
                {
                    if (EXIST == _states[i])
                    {
                         tmp.Insert(_tables[i]);
                    }
                }
                Swap(tmp);
            }
        }

    protected:
        K* _tables;     //  ��ϣ��
        State* _states; //  ״̬��
        size_t _size;
        size_t _capacity;
    };

}

void test_namespace_First()
{
    using namespace First;
    HashTable<int> ht;
    ht.Insert(89);
    ht.Insert(18);
    ht.Insert(49);
    ht.Insert(58);
    ht.Insert(9);
    ht.Print();

    int ret = ht.Find(49);
    cout<<ret<<endl;

    ht.Remove(89);
    ht.Print();  
    
    ht.Remove(18);
    ht.Print();
    cout<<"---------------------------"<<endl;

    HashTable<int> ht2 = ht;
    ht2.Print();
    cout<<"---------------------------"<<endl;
    ht = ht2;
    ht.Print();
    cout<<"---------------------------"<<endl;

}

//============================================================================




namespace Second
{
    enum State
    {
        EMPTY,
        DELETE,
        EXIST,
    };
    //  Key/Value
    template<class K, class V>
    struct HashTableNode
    {
        K _key;
        V _value;
    };

    template<class K>
    struct __HashFunc // Ĭ�ϵķ��ع�ϣ��ֵkey�� �º���
    {
        size_t operator()(const K& key)
        {
            return key;
        }
    };

    // �ػ�string��__HashFunc �º���
    template<>
    struct __HashFunc<string>
    {
        //��������ȱ�� �����ظ�key �硰abcd�� �� ��bcda��
        size_t operator()(const string& str)
        {
             size_t key = 0;
            for (size_t i = 0; i < str.size(); i++)
            {
                key += str[i];
            }

            return key;
        }
    };

    // ʵ�ֹ�ϣ���Key/Value��ʽ�Ķ���̽��
    template<class K, class V, class HashFunc = __HashFunc<K>>
    class HashTable
    {
        typedef HashTableNode<K,V> Node;
     public:
        HashTable(size_t capacity = 10)
            :_tables(new Node[capacity])
            ,_size(0)
            ,_capacity(capacity)
            ,_states(new State[capacity])
        {
            // memset ������ �����ֽ�Ϊ��λ��ʼ���� ���ڶ�������ֵΪint
            // ������� ������ʼ��Ϊ0x00000001 �����ʼ��Ϊ0x01010101
            //memset(_states, EMPTY, sizeof(State) * capacity);
            for (size_t i = 0; i < capacity; i++)
            {
                _states[i] = EMPTY;
            }
        }

        HashTable(const HashTable<K, V, HashFunc>& ht)
            :_tables(new Node[ht._capacity])
            ,_size(0)
            ,_capacity(ht._capacity)
            ,_states(new State[ht._capacity])
        {
            for (size_t i = 0; i < ht._capacity; i++)
            {
                if (EXIST == ht._states[i])
                {
                    Insert(ht._tables[i]._key, ht._tables[i]._value);
                }
            }
        }

       
        
        HashTable& operator=(const HashTable<K, V, HashFunc>& ht)
        {
            if (ht._tables != _tables && ht._states != _states)
            {
                HashTable<K, V, HashFunc> tmp(ht);
                Swap(tmp);
            }

            return *this;
        }

        ~HashTable()
        {
            if (NULL != _tables)
            {
                delete[] _tables;
            }

            if (NULL != _states)
            {
                delete[] _states;
            }
        }

        bool Insert(const K& key, const V& value)
        {
            // ��̬��ϣ�� �����ݵ�
            /*if (_size == _capacity)
            {
                cout<<"HashTable is full"<<endl;
                return false;
            }*/

            _CheckCapacity();  

            //size_t hashKeyStart = _HashFunc(key);
            //size_t add_more = 1;
            //size_t index = hashKeyStart;
            //// ****************************************
            //// ����̽��    Hash(key) + 0 Hash(key) + 1^2 Hash(key) + 2^2

            //while (EXIST == _states[index])
            //{
            //    index = hashKeyStart + add_more * add_more;
            //    add_more++;
            //    if (index >= _capacity)
            //    {
            //          index = index % _capacity;
            //    }  
            //}

             // ****************************************

            // �Ľ� ��GetNextIndex �����ϣ��ͻ
            size_t index = _HashFunc(key);
            // ����̽��   
            size_t i = 1;
            while (EXIST == _states[index])
            {
                index = _GetNextIndex(index, i++);
                if (index >= _capacity)
                {
                      index = index % _capacity;
                }  
            }
            _tables[index]._key = key;
            _tables[index]._value = value;
            _states[index] = EXIST;
            _size++;
            return true;
        }

        int Find(const K& key)
        {
            size_t index = _HashFunc(key);
            size_t start = index;
            size_t i = 1;
            // ���� ���� ��ɾ�� ����״̬
            while (EMPTY != _states[index])
            {
                if (_tables[index]._key == key)
                {
                    if (_states[index] == EXIST)
                    {
                        return index;
                    }
                    else // ��ɾ�� DELETE
                    {
                        return -1;
                    }
                }

                index = _GetNextIndex(index, i++);

                if (index >= _capacity)
                {
                    index = index % _capacity;
                }

                // ��Ϊ��������� ��Ϊ100%  �������ȫ����key��=_key ������ѭ�������
            }

            return -1;
        }

        bool Remove(const K& key)
        {
            int index = Find(key);
            if (-1 != index)
            {
                _states[index] = DELETE;
                --_size;
                return true;
            }

            return false;
        }

        
       // ����̽���������λ��
        size_t _HashFunc(const K& key)
        {
           // __HashFunc<K> hf;
            HashFunc hf;
            return hf(key) % _capacity; //  �º���hf() 
            // ��������
            // return __HashFunc<K>()(key) % _capacity;
        }

        //   ��ϣ��ͻʱ �õ���һ��index�Ŀ���������һ��index��ֵ ���������Ч�� ���� string��index����ͱȽϷ�ʱ
          size_t _GetNextIndex(size_t prev, size_t i) 
         {
             //����̽��
             // ��ʽ�Ƶ� Hash(i) = Hash(0) + i^2
             //          Hash(i-1) = Hash(0) + (i -1)^2=Hash(0)+i^2-2i+1
             //  ������ʽ��� �� Hash(i) = Hash(i-1) + +2*i - 1;
             return prev + 2*i - 1;
         }


        void Print()
        {
            for (size_t i = 0; i < _capacity; i++)
            {
                if (EXIST == _states[i])
                {
                    cout<< i << "EXIST:" <<_tables[i]._key << "-------" <<_tables[i]._value <<endl;
                }
                else if (DELETE == _states[i])
                {
                    cout<< i << "DELETE:" << _tables[i]._key << "-------" << _tables[i]._value <<endl;
                }
                else
                {
                  cout << i << "EMPTY:" << _tables[i]._key << "-------" << _tables[i]._value <<endl;
                }
            }
        }

        void Swap(HashTable<K, V, HashFunc>& ht)
        {
            swap(_size, ht._size);
            swap(_states, ht._states);
            swap(_tables, ht._tables);
            swap(_capacity, ht._capacity);
        }

    protected:
         void _CheckCapacity() // ����
        {
            // ��̬�� �����ݵ�
            // ��Ч��ϣ����غ����Ӵ����0.7-0.8�Ϻ�
            if (10 * _size / _capacity >= 7)  // _size/_capacityΪ0 ��Ϊ�������� ���Գ�10
                // ��֤�غ�������0.7֮��
            {
                HashTable<K, V, HashFunc> tmp(2 * _capacity);
                for (size_t i = 0; i < _capacity; i++)
                {
                    if (EXIST == _states[i])
                    {
                         tmp.Insert(_tables[i]._key, _tables[i]._value);
                    }
                }
                Swap(tmp);
            }
        }

    protected:
        Node* _tables;     //  ��ϣ��
        State* _states; //  ״̬��
        size_t _size;
        size_t _capacity;
    };

}




void test_namespace_Second()
{
    using namespace Second;
    HashTable<string, string> ht;
    ht.Insert("one","һ");
    ht.Insert("two","��");
    ht.Insert("three","��");
    ht.Insert("four","��");
    ht.Insert("five","��");
    ht.Print();

     int ret = ht.Find("two");
    cout<<ret<<endl;

    ret = ht.Find("hfjks");
    cout<<ret<<endl;

    ht.Remove("one");
    ht.Print();  
    
    ht.Remove("two");
    ht.Print();
    cout<<"---------------------------"<<endl;

    HashTable<string, string> ht2 = ht;
    ht2.Print();
    cout<<"---------------------------"<<endl;
    ht = ht2;
    ht.Print();
    cout<<"---------------------------"<<endl;

}

