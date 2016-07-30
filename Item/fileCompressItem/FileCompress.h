#pragma once
#include<iostream>
#include<string>

using namespace std;
#include"HuffmanTree.h"
typedef unsigned long LongType;
struct CharInfo
{
    unsigned char _ch; // �ַ�
    LongType _count; // �ַ����ִ���
    string _code; // ����������

    CharInfo(const LongType count = 0)
        :_count(count)
    {}

    CharInfo(const char ch)
        :_ch(ch)
    {};

    CharInfo operator+(const CharInfo& c) const
    {
        return CharInfo(_count + c._count);
    }

    bool operator!=(const CharInfo& c) const
    {
        return _count != c._count;
    }

    bool operator<(const CharInfo& c) const
    {
        return _count < c._count;
    }


};

class FileCompress
{
public:
    FileCompress()
    {}

    // ѹ��
    void Compress(const char* filename)
    {
       // ��ʼ��
        for (size_t i = 0; i < 256; ++i)
        {
            _infos[i]._ch = i;
            _infos[i]._count = 0;
        }

        FILE* fOut = fopen(filename, "rb");
        assert(fOut);


        // 1 ͳ���ļ����ַ����ֵĴ���
        char ch = fgetc(fOut);

       // while (ch != EOF)
        while (!feof(fOut))
        {
            _infos[(unsigned char)ch]._count++; // ��ע�⡿���±� ���޷���
            ch = fgetc(fOut);
        }

        // ����HuffmanTree
        CharInfo invalid; // Ĭ��ֵ��Ϊ ��Чֵ
        HuffmanTree<CharInfo> h_tree(_infos, 256, invalid);
        HuffmanNode<CharInfo>* h_root = h_tree.GetRootNode(); 
        // ����Huffman����
        string str; // ��¼����
        GenerateHuffmanCode(h_root, str); 


     
        char data = 0; // д��ѹ���ļ�������
        int bitcount = 7; // �����λ��Ϣ
        string compressFilename(filename); // ѹ���ļ�����
        compressFilename += ".compress";
        FILE* fIn = fopen(compressFilename.c_str(), "wb");

           // �ļ�ָ�� ������ͷ
        fseek(fOut, 0, SEEK_SET);
        ch = fgetc(fOut);

       // while (ch != EOF)
        while (!feof(fOut))
        {
            const char* cur = _infos[(unsigned char)ch]._code.c_str();

            while (*cur)
            {
                if (bitcount >= 0)
                {
                    data <<= 1; // ���� ���λ�ƶ�
                    data = data | (*cur - '0');  
                    bitcount--;
                }

                if (bitcount < 0) // 8 λ��
                {
                    fputc(data, fIn);
                    bitcount = 7;
                    data = 0;
                }

                cur++;
            }

            ch = getc(fOut);
        }

        // ���ûд��һ���ֽ� 
        data <<= bitcount + 1;
        fputc(data, fIn);

        // д�����ļ�
        string configFile = filename;
        configFile += ".config";
        FILE* fConfig = fopen(configFile.c_str(), "wb");
        assert(fConfig);
        string line;
        char buffer[150];
        for (size_t i = 0; i < 256; i++)
        {
            if (_infos[i]._count > 0)
            {
                line += _infos[i]._ch;
                line += ",";

                _itoa(_infos[i]._count, buffer, 10); // 10 ʮ����
                line += buffer;
                line += '\n';

                fputs(line.c_str(), fConfig);
            }

            line.clear();
        }

        fclose(fConfig);
        fclose(fIn);
        fclose(fOut);
    }
    
    bool ReadLine(FILE* fOut, string& line)
    {
        char ch = fgetc(fOut);
        //if (ch == EOF)
        if (feof(fOut))
        {
            return false;
        }

        while ((!feof(fOut)) && ch != '\n')
        {
            line += ch;
            ch = fgetc(fOut);
        }

        return true;
    }



    // ��ѹ��
    void Uncompress(const char* filename)
    {
        // ��ʼ��
        for (size_t i = 0; i < 256; ++i)
        {
            _infos[i]._ch = i;
            _infos[i]._count = 0;
        }

        // �������ļ����õ��ַ����ֵĴ���
        string configFile = filename;
        configFile += ".config";
        FILE* fConfig = fopen(configFile.c_str(), "rb");
        assert(fConfig);
        string line;
        while (ReadLine(fConfig, line))
        {
            // ��ע�⡿�����\n��ͳ�Ƶ�����
            if (line.empty())
            {
                line += '\n';
            }
            else
            {
                _infos[(unsigned char)line[0]]._count = atoi(line.substr(2).c_str()); 
                line.clear();
            }
        }

        // ����HuffmanTree
        CharInfo invalid;
        HuffmanTree<CharInfo> h_tree(_infos, 256, invalid);

        // ��ע�⡿��ֹ���ѹ�����ַ� ������_count ���þ��������ַ��ĸ��� �������������¼����
        int uncompress_ch_count = (h_tree.GetRootNode())->_weight._count;

        // ��ȡѹ���ļ������л�ԭ
        string compressFile = filename;
        compressFile += ".compress";
        FILE* fOut = fopen(compressFile.c_str(), "rb");
        assert(fOut);

        // ��ԭ�ļ�
        string uncompressFile = filename;
        uncompressFile += ".uncompress";
        FILE* fIn = fopen(uncompressFile.c_str(), "wb");
        assert(fIn);

        HuffmanNode<CharInfo>* h_root = h_tree.GetRootNode();
        HuffmanNode<CharInfo>* cur = h_root;
        char ch = fgetc(fOut);
        int pos = 7;

       // while (ch != EOF)
        while (!feof(fOut)) // ��ע�⡿feof�����ֽڸ����ķ�ʽ���ж��ļ����� �� EOF ʹ���ļ���β��EOF(-1)���λ ��ȱ�� ����asciiΪ-1������Ҫ2��3���ֽڱ��� ������һ���ֽھͿ����� -1�����ַ� ���� Ϊ������
        {
            if (ch & (1 << pos)) // ��0 ��1
            {
                cur = cur->_right;
            }
            else
            {
                cur = cur->_left;
            }

            if (cur->_left == NULL && cur->_right == NULL)
            {
                if (uncompress_ch_count == 0) // ��ֹ���д�������ַ�
                {
                    break;
                }

                // д��ѹ�ַ�
                fputc(cur->_weight._ch, fIn);
                uncompress_ch_count--;
                cur = h_root;
            }

            if (pos == 0)
            {
                ch = fgetc(fOut);
                pos = 8;
            }

            --pos;
        }

        fclose(fOut);
        fclose(fIn);
    }


protected:
    void  GenerateHuffmanCode(HuffmanNode<CharInfo>* root, string code) // str ֵ���ݲ������� ��ջ���ÿ���strȥ������
    {
        if (root == NULL)
        {
            return;
        }

        // ��� 0  �ұ�1
        GenerateHuffmanCode(root->_left, code + '0'); 
        GenerateHuffmanCode(root->_right, code + '1'); 

        if (root->_left == NULL && root->_right == NULL)
        {
            _infos[(root->_weight)._ch]._code = code;
        }
    }

private:
    CharInfo _infos[256];
};
