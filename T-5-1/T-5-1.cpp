#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h> //用来输出文件打不开的错误信息
using namespace std;

// 分割字符串
void split_string(string &wait_to_split, vector<string> &vectors, char keyword)
{
    stringstream ss(wait_to_split);
    string token;
    while (getline(ss, token, keyword))
    {
        vectors.push_back(token);
    }
}
// 分割字符串并转int加到二维向量(重载)
void split_string(string &wait_to_change, vector<vector<int>> &numbers, char keyword)
{
    int toint(string & wait_to_change); // 声明要调用的函数
    vector<int> temp = {0, 0};
    stringstream ss(wait_to_change);
    string token1;
    int count = 0;
    while (getline(ss, token1, keyword))
    {
        int token2 = toint(token1); // 调用定义的toint函数
        if (count == 0)
        {
            temp[0] = token2;
            count++;
        }
        else if (count == 1)
        {
            temp[1] = token2;
            count = 0;
            numbers.push_back(temp);
        }
    }
}
// 转数字,加到向量
void tonumber(string &wait_to_change, vector<vector<int>> &numbers)
{
    vector<int> temp = {0};
    int temp_num;
    istringstream tonum(wait_to_change);
    tonum >> temp_num;
    temp[0] = temp_num;
    numbers.push_back(temp);
}
// 转数字
int toint(string &wait_to_change)
{
    int temp_num;
    istringstream tonum(wait_to_change);
    tonum >> temp_num;
    return temp_num;
}

int main()
{
    string temp, all, temp_data;
    int num, count = 0, res1, res2, res3, len;
    int flag1 = 0, flag2 = 0, compare;
    vector<vector<int>> match;
    vector<string> splited;

    ifstream strin("d:\\str.txt");

    if (strin.is_open() == true)
    {
        while (strin.eof() == false)
        {
            if (strin >> temp) // temp为当前一大串字符串，如果使用getline(strin, temp),就会读入空格
            {
                int n = temp.length();
                if (n != 0) // 检查当前是否是空字符串
                {
                    if (temp.substr(n - 1, 1) != ",")
                    {
                        all.append(temp); // 连接字符串
                        all.append(",");  // 如果最后一位不是逗号，则补充逗号，使得数字结束时都以逗号结尾
                    }
                    else
                        all.append(temp);
                }
            }
        }
    }
    else
    {
        if (strin.is_open() == false)
            cout << "Error:cannot open file 'str.txt':" << strerror(errno) << endl; // 用到头文件<string.h>
    }

    strin.close();

    len = all.length();
    for (int i = 1; i < len - 1; i++)
    {
        if (all.substr(i, 1) == ",")
        {
            if (all.substr(i - 1, 1) == "~" || all.substr(i + 1, 1) == "~") // 删除多余的逗号
            {
                all.replace(i, 1, "");
                i--;   // 索引要减一
                len--; // 字符串长度也要减一
            }
        }
    }
    all.replace(len - 1, 1, ""); // 去除最后一个逗号

    split_string(all, splited, ','); // 调用分割字符串的函数,用逗号把字符串分开,加到splited向量里

    for (string strs : splited) // 遍历splited向量
    {
        size_t found = strs.find('~'); // 查找字符串里是否有~
        if (found != string::npos)     // 如果有,用~分割并加到二维match向量里面
            split_string(strs, match, '~');
        else // 如果没有,转成数字加到二维match向量里面
            tonumber(strs, match);
    }

    ifstream datain("d:\\data.txt");
    if (datain.is_open() == true)
    {
        while (datain.eof() == false)
        {
            if (datain >> temp_data)
            {
                compare = toint(temp_data);

                for (int i = 0; i < match.size(); i++) // 判断这个数字在哪个区间
                {
                    if (match[i].size() == 2) // 如果目前在区间
                    {
                        if (match[i][0] > match[i][1]) // 判断是不是合法区间
                            continue;
                        else
                        {
                            if (compare >= match[i][0] && compare <= match[i][1])
                            {
                                res1 = match[i][0];
                                res2 = match[i][1];
                                cout << setw(8) << compare << " "
                                     << "is in [" << res1 << "," << res2 << "]" << endl;
                                flag1 = 1;
                            }
                            else
                                continue;
                        }
                    }
                    else if (match[i].size() == 1) // 如果目前不在区间
                    {
                        if (compare == match[i][0])
                        {
                            res3 = match[i][0];
                            flag2 = 1;
                            cout << setw(8) << compare << " "
                                 << "is in [" << res3 << "," << res3 << "]" << endl;
                        }
                    }
                }
                if (flag1 == 0 && flag2 == 0)
                {
                    cout << setw(8) << compare << " "
                         << "is not in any range" << endl;
                }
            }
            flag1 = 0; // 判断完一个数字要重置两个flag的值
            flag2 = 0;
        }
    }
    else
    {
        if (strin.is_open() == false)
            cout << "Error:cannot open file 'str.txt':" << strerror(errno) << endl; // 用到头文件<string.h>
    }
    datain.close();

    cout << "请按任意键继续. . .";
    getchar();
    return 0;
}