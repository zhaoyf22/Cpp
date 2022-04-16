#include "baseio.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

namespace BaseIO{
void printState(istream& in) {
    // 流状态打印
    cout << "goodstate: " << in.good() << ", goodbit: " << in.goodbit << endl;
    cout << "failstate: " << in.fail() << ", failbit: " << in.failbit << endl;
    cout << "eofstate: " << in.eof() << ", eofbit: " << in.eofbit << endl;
    cout << "badstate: " << in.bad() << ", badbit: " << in.badbit << endl;
    cout << endl;
}
void baseIOStateTest() {
    // IO对象（流对象）不能拷贝和赋值，只能以引用的方式传递和返回
    //    ofstream out1, out2;
    //    out1 = out2; // 错误，不能对流对象赋值
    //    ofstream print(ofstream); // 错误，不能初始化流对象参数
    //    out2 = print(out2); // 错误，不能拷贝流对象

    // IO对象（流对象）状态
    int value;
    while(cin >> value) {
        printState(cin);
    }

    auto old_state = cin.rdstate(); // 读取当前状态并记录
    printState(cin);

    cin.clear(); // 流状态复位，即错误位全部清除
    printState(cin);

    cin.setstate(old_state); // 设置为原来错误状态，导致failbit置位
    cin.clear(cin.rdstate() & ~cin.failbit); // 流状态复位
    printState(cin);

    cin.setstate(old_state); // 设置为原来错误状态，导致failbit置位
    cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit); // 流状态复位
    printState(cin);

    cin.setstate(old_state);
    printState(cin);

    int temp = 0;
    return;
}

void baseIOFileTest() {
    const string filePath{"D:\\LearnProject\\data\\"};

    // 直接构造且以读取模式打开文件
    ifstream if1(filePath + "FileData.txt");
    string line;
    vector<string> strvec;
    if( if1 ) { // 这种判断方法和基本IO流一致
        getline(if1, line);
        strvec.push_back(line);
    }

    // 默认构造，调用open函数以读取模式打开文件， 且用is_open判断打开是否成功
    ifstream if2;
    if2.open(filePath + "FileData.txt");
    if( if2.is_open() ) {
        getline(if1, line);
        strvec.push_back(line);
    }

    // 当fstream对象被销毁时，会自动调用close
    const int fileNum = 10;
    for(int i=0; i<fileNum; i++) {
        ofstream of(filePath + to_string(i) + ".txt");
        for( string& line : strvec ) {
            of << line << endl;
        }
    }

    // 文件模式
    /*
     * in       输入，以读方式打开
     * out      输出，以写方式打开
     * app      每次写操作前均定位到文件尾，即追加模式
     * ate      打开文件后立即定位到文件尾
     * trunc    截断文件，即覆盖模式
     * binary   二进制模式
     * */

    // 写出默认模式，如下三条语句等价
    ofstream of1(filePath + "FileData.txt");
    ofstream of2(filePath + "FileData.txt", ofstream::out);
    ofstream of3(filePath + "FileData.txt", ofstream::out | ofstream::trunc);

    // 打开文件时候指定模式
    ofstream of4; // 未指定文件模式
    of4.open(filePath + "FileData.txt", ofstream::app); // out和app模式


    int temp = 0;
    return;
}

class PersonInfo {
public:
    long long id;
    string name;
    vector<string> phones;
};

void split(string& str, vector<string>& vec) {
    istringstream is1(str);
    string word;
    vec.clear();
    while( is1 >> word ) {
        vec.push_back(word);
    }
}

void baseIOStingTest() {
    // istringstream 使用实例1，处理输入一行数据中的复合信息
//    string line, phone;
//    vector<PersonInfo> people;
//    while( getline(cin, line) ) {
//        PersonInfo person;
//        istringstream is(line);
//        if( !(is >> person.id) ) {
//            break;
//        }
//        is >> person.name;
//        while(is >> phone) {
//            person.phones.push_back(phone);
//        }
//        people.push_back(person);
//    }

    // istringstream 使用实例2，c++实现简单的单词切割
    string str("hello world, hello motherland!");
    vector<string> words;
    split(str, words);

    // ostringstream 使用，当我们逐步构造输出，希望最后一起获取时，ostringstream 就很有用处
    // 它可以帮我们先将内容“写入”到一个内存ostringstream中，最后一次获取。
    ostringstream os;
    os << 1; // person.id
    os << "lilei"; // person.name;
    cout << os.str() << endl;

    int temp = 0;
    return;
}

void test(){
    baseIOStingTest();
    baseIOFileTest();
    baseIOStateTest();
}
}

