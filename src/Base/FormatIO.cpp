#include "formatio.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

namespace FormatIo {
void formatIoTest1() {
    // 操纵符
    // 控制布尔值格式
    bool truev = true;
    bool falsev = false;
    cout << truev << " , " << falsev << endl;
    cout << boolalpha << truev << " , " << falsev << endl;
    cout << noboolalpha << truev << " , " << falsev << endl;
    cout << endl;

    // 指定整形值的进制，浮点数表示不受影响
    cout << "default: " << 20 << " , " << 1024 << endl;
    cout << "oct: " << oct << 20 << " , " << 1024 << endl; // 八进制
    cout << "hex: " << hex << 20 << " , " << 1024 << endl; // 十六进制
    cout << "dec: " << dec << 20 << " , " << 1024 << endl << endl; // 十进制

    // 在输出中指出进制，字符以大写的形式打印
    cout << showbase << uppercase;
    cout << "default: " << 20 << " , " << 1024 << endl;
    cout << "oct: " << oct << 20 << " , " << 1024 << endl; // 八进制
    cout << "hex: " << hex << 20 << " , " << 1024 << endl; // 十六进制
    cout << "dec: " << dec << 20 << " , " << 1024 << endl; // 十进制
    cout << noshowbase << nouppercase << endl;

    // 控制浮点数格式
    // 1）指定打印精度（多少个数字）
    cout << "Precision: " << cout.precision() << ", value: " << sqrt(2.0) << endl;
    cout.precision(12); // 成员函数precision, 有参版本，设置精度，无参版本，返回当前精度
    cout << "Precision: " << cout.precision() << ", value: " << sqrt(2.0) << endl;
    cout << setprecision(3); // 操纵符
    cout << "Precision: " << cout.precision() << ", value: " << sqrt(2.0) << endl;
    cout << setprecision(6) << endl; // 恢复默认6位精度

    // 2）指定浮点数计数法
    cout << "default format: " << 100 * sqrt(2.0) << endl; // 默认模式，精度控制数字的总位数
    cout << "scientific: " << scientific << 100 * sqrt(2.0) << endl; // 科学计数法
    cout << "fixed decimal: " << fixed << 100 * sqrt(2.0) << endl; // 定点十进制
    cout << "hexadecimal: " << hexfloat << 100 * sqrt(2.0) << endl; // 十六进制
    cout << "defaultfloat: " << defaultfloat << 100 * sqrt(2.0) << endl << endl; // 恢复默认模式

    // 3）打印小数点
    cout << 10.0 << endl; // 默认，当一个浮点数的小数部分为0时，不显示小数点，showpoint强制打印小数点
    cout << showpoint << 10.0 << endl;
    cout << noshowpoint << 10.0 << endl << endl;

    // 输出补白
    int i = -16;
    double d = 3.14159;
    // 默认右对齐
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;

    // 左对齐
    cout << left;
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;

    // 右对齐
    cout << right;
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;

    // 中间，控制负号的位置
    cout << internal;
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;

    // 设置补白字符
    cout << setfill('#');
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;

    // 控制输入格式
    cin >> noskipws; // 设置输入运算符读取空白符（空格符， 制表符， 换行符，回车符）
    cin >> skipws; // 恢复到默认状态

    int temp = 0;
    return;
}

void test(){
    formatIoTest1();
}
}
