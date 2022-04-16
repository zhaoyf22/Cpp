#include "regextest.h"
#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

namespace RegexTest {
void RegexTest1() {
    // regex构造，赋值，重新初始化
    string partten1{"[[:alpha:]]*[^c]ei[[:alpha:]]*"};
    regex r1(partten1);
    regex r2;
    r2 = r1;
    r1.assign(r2);
    auto subExprNum = r1.mark_count(); // 子表达式的数量

    // 应用实例1
    string str1{"receipt freind theif receive"};
    smatch res1;
    if(regex_search(str1, res1, r1)) {
        cout << "*" << res1.str() << "*" << endl;
        cout << "*" << res1.prefix().str() << "*" << endl;
        cout << "*" << res1.suffix().str() << "*" << endl;
    }

    // 应用实例2
    //    regex r3("[[:alnum:]]+\\.(cpp|cxx|c)");
    //    regex r3("[[:alnum:]]+\\.(cpp|cxx|c)$");
    regex r3("[[:alnum:]]+[.](cpp|cxx|c)");
    smatch res2;
    string str2 = "regextest.cpp";
    if(regex_match(str2, res2, r3)) {
        cout << "*" << res2.str() << "*" << endl;
        cout << "*" << res2.prefix().str() << "*" << endl;
        cout << "*" << res2.suffix().str() << "*" << endl;
    }

    // regex构造错误
    try {
        regex r("[[:alnum]+[.](cpp|cxx|c");
    } catch (regex_error e) {
        cout << e.what() << endl << "code: " << e.code() << endl;
    }

    // 正则表达式和输入序列匹配
    cmatch res3;
    if(regex_match("myfile.cpp", res3, r3)) {
        cout << res3.str() << endl;
    }

    int temp = 0;
    return;
}

void RegexTest2() {
    // 匹配与regex迭代器
    string partten1{"[[:alpha:]]*[^c]ei[[:alpha:]]*"};
    regex r1(partten1);
    string str1{"receipt freind theif receive"};
    for(sregex_iterator iter(str1.begin(), str1.end(), r1), iterend;iter != iterend; iter++) {
        cout << iter->str() << endl;
        cout << iter->prefix().str() << endl;
        cout << iter->suffix().str() << endl;
    }

    int temp = 0;
    return;
}

bool valid(const smatch& m) {
    if(m[1].matched) {
        return m[3].matched && (!m[4].matched || m[4].str() == " ");
    } else {
        return !m[3].matched && (m[4].str() == m[6].str());
    }
}

void RegexTest3() {
    // 子表达式
    regex r1("([[:alnum:]]+)[.](cpp|cxx|c)");
    smatch res1;
    string str1 = "file.cpp";
    if(regex_match(str1, res1, r1)) {
        cout << "*" << res1.str(0) << "*" << endl; // 完整匹配项
        cout << "*" << res1[0].str() << "*" << endl; // 完整匹配项
        cout << "*" << res1.str(1) << "*" << endl; // 第一个子表达式
        cout << "*" << res1[1].str() << "*" << endl; // 第一个子表达式
        cout << "*" << res1.str(2) << "*" << endl; // 第二个子表达式
        cout << "*" << res1[2].str() << "*" << endl; // 第二个子表达式
    }

    // 子表达式综合例子，美国电话号码匹配
    regex r2("(\\()?(\\d{3})(\\))?([. -])?(\\d{3})([. -])?(\\d{4})");
    vector<string> numsVec{"028-355-4567", "(028) 111.2345", "(028 4566789",
                           "028).111-2222", "02811112222", "028111 2222",
                           "028 1111 2222", "028.1111.222", "028  111.2222"};
    for(string& str : numsVec) {
        for(sregex_iterator it(str.begin(), str.end(), r2), itend; it != itend; it++) {
            if(valid(*it) ) {
                // replace
                string fmtt("$2.$5.$7");
                cout << "ori phone number: " << it->str() << endl;
                cout << "format phone number: " << regex_replace(it->str(), r2, fmtt) << endl;
                cout << "format phone number: " << it->format(fmtt) << endl;
            }
        }
    }

    // 只替换输入序列的一部分
    string fmt("$2.$5.$7");
    string strline = "lilei 028-111.2222 (028) 333 4444 0285556666";
    cout << regex_replace(strline, r2, fmt) << endl;
    cout << regex_replace(strline, r2, fmt, regex_constants::format_no_copy) << endl;
    string res;
    regex_replace(back_inserter(res), strline.begin(), strline.end(), r2, fmt);
    cout << res << endl;


    int temp = 0;
    return;
}

void RegexTest4() {


}

void test(){
    //    RegexTest1();
    //    RegexTest2();
    RegexTest3();


    int temp = 0;
    return;
}
}

