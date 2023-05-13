#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<char> calculation;
int generate_mode,max_value,num_questions,allow_decimal, allow_parenthesis;

string generate_number()
{
    return to_string(rand() % max_value + 1);
}
char generate_operator()
{
    return calculation[rand()% calculation.size()];
}
// 递归生成表达式
string generate_expression(int depth) {
    if(depth == 0)

        return (generate_number() + generate_operator() +generate_number());
    else
    {
        generate_mode = rand()%4;
        switch (generate_mode) {
            case 0:
                return(generate_number() + generate_operator() + generate_number());
                break;
            case 1:
                return(generate_expression(depth -1) + generate_operator() + generate_number());
                break;
            case 2:
                return(generate_number() + generate_operator() + generate_expression(depth -1));
                break;
            case 3:
                return (generate_expression(depth -1) + generate_operator() + generate_expression(depth -1));
                break;
        }
    }
}

// 将表达式写入文件
void write_expression_to_file(ofstream& fout, string expression) {
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == '/')
            fout << "÷";
        else if (expression[i] == '*')
            fout << "×";
        else if (expression[i] == '(')
            fout << "（";
        else if (expression[i] == ')')
            fout << "）";
        else
            fout << expression[i];
    }
    fout << "=" << endl;
}

// 生成题目并输出到文件
void generate_questions_to_file(string filename) {
    srand(time(nullptr)); // 初始化随机种子
    ofstream fout(filename);
    for (int i = 0; i < num_questions; i++) {
        string expression = generate_expression(3);
        write_expression_to_file(fout, expression);
    }
    fout.close();
}

// 主函数，负责读取用户输入和调用相关函数
int main() {
    // 提示用户输入选项
    cout << "Four arithmetic generators" << endl;
    cout << "------------------" << endl;
    cout << "Enter options" << endl;
    cout << "1. Generate a question and save it to a file" << endl;
    cout << "2. exit" << endl;

    while (true) { // 不断处理用户输入直到退出
        char input;
        cin >> input;
        switch (input) {
            case '1': { // 生成题目并保存到文件
                string filename;

                // 提示用户设置选项
                cout << "Enter the number of questions:";
                cin >> num_questions;
                cout << "Enter the operator(end with #):";
                char op;
                while (cin >> op) {
                    if (op == '+') calculation.push_back('+');
                    else if (op == '-') calculation.push_back('-');
                    else if (op == '*') calculation.push_back('*');
                    else if (op == '/') calculation.push_back('/');
                    else break;
                }
                cout << "Maximum";
                cin >> max_value;
                cout << "Whether decimals are allowed(0/1):";
                cin >> allow_decimal;
                cout << "Whether parentheses are allowed(0/1):";
                cin >> allow_parenthesis;
                cout << "Enter a file name:";
                cin >> filename;

                // 生成题目并保存到文件
                generate_questions_to_file(filename);
                cout << "The question was successfully generated and saved to a file " << filename << endl;
                break;
            }
            case '2': { // 退出程序
                cout << "Program end" << endl;
                return 0;
            }
            default:
                cout << "Error input" << endl;
                break;
        }
    }
}
