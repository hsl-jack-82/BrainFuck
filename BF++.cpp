// BF++.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string.h>
#define IOTYPE char


class Memory
{
private:
    int* List;
    int len;
    int point;
public:
    Memory(int Long)
    {
        len = Long;
        List = new int[Long];
        for (int i = 0; i < Long; i++)
        {
            List[i] = 0;
        }
        point = 0;
    }
    Memory()
    {
        len = 100;
        List = new int[100];
        for (int i = 0; i < 100; i++)
        {
            List[i] = 0;
        }
        point = 0;
    }
    ~Memory()
    {
        delete List;
    }
    int getLen() { return len; }
    void add() { List[point]++; }
    void sum() { List[point]--; }
    void right() { point++; }
    void left() { point--; }
    void print()
    {
        IOTYPE out = List[point];
        std::cout << out;
    }
    void input(IOTYPE in)
    {
        List[point] = in;
    }
    int get() { return List[point]; }
};

class Excute
{
private:
    Memory paper;
public:
    void excuteFunction(std::string in)
    {
        IOTYPE input;
        char now;
        std::string inLoop;
        for(size_t i = 0; i != in.size(); i++)
        {
            now = in[i];
            switch (now)
            {
            case '+':
                paper.add();
                break;
            case '-':
                paper.sum();
                break;
            case '>':
                paper.right();
                break;
            case '<':
                paper.left();
                break;
            case '[':
                for (size_t j = (i + 1); in[j] != ']'; j++)
                {
                    inLoop = inLoop + in[j];
                }
                while (paper.get() > 1)
                {
                    excuteFunction(inLoop);
                }
                inLoop = "";
                break;
            case ',':
                input = NULL;
                std::cout << "Input: ";
                std::cin >> input;
                paper.input(input);
                break;
            case '.':
                paper.print();
                break;
            default:
                break;
            }
        }
    }
};


std::string splitStr(std::string in, size_t start, size_t end);
std::string splitStr(std::string in, size_t start, size_t end)
{
    if (in.size() < start || in.size() < end || start > end)
    {
        throw "There are some problems about splitStr()'s parameter";
    }
    std::string out = "";
    for (size_t i = start; i < end; i++)
    {
        out = out + in[i];
    }
    return out;
}

bool isOpen(std::string in);
bool isOpen(std::string in)
{
    if (in.length() < 6)
    {
        return false;
    }
    else if (splitStr(in, 0, 4) == "open")
    {
        if (in[4] == ' ')
        {
            return true;
        }
    }
    return false;
}

char* noConst(std::string in)
{
    char* c;
    const int len = in.length();
    c = new char[len + 1];
    strcpy(c, in.c_str());
    return c;
}

void BrainFuck()
{
    std::cout << "BrainFuck by HSL 2021/1/23\n" << "Input exit() to get exit.\n" << "Input open <path> to open file.\n";
    Excute self;
    std::string inputCode;
    std::string path;
    while (true)
    {
        std::cout << ">>> ";
        std::cin >> inputCode;
        if (inputCode == "exit()")
        {
            break;
        }
        else if (isOpen(inputCode))
        {
            path = splitStr(inputCode, 5, inputCode.length());
            std::ifstream srcFile(path);
            if (!srcFile.is_open())
            {
                std::cout << "Error opening file"; exit(1);
            }
            while (!srcFile.eof())
            {
                srcFile.getline(noConst(inputCode), 256);
            }
        }
        self.excuteFunction(inputCode);
    }

}
int main()
{
    BrainFuck();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
