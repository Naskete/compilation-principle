#include "analysieWord.cpp"
#include <iostream>
#include <stack>
#include <map>
using namespace std;

stack<char> s;
map<char, map<char, string> > table;
string target;
string obj;

void initTable(){
    table['E']['i'] = "TA";
    table['E']['('] = "TA";
    table['A'][')'] = "ε";
    table['A']['+'] = "+TA";
    table['A'][';'] = "ε";
    table['T']['i'] = "FB";
    table['T']['('] = "FB";
    table['B'][')'] = "ε";
    table['B']['+'] = "ε";
    table['B']['*'] = "*FB";
    table['B'][';'] = "ε";
    table['F']['i'] = "i";
    table['F']['('] = "(E)";
}

void pushStr(stack<char> &s,string str){
    if(str!="ε"){
        int l = Len(str);
        if(l==1){
            s.push(str[0]);
        } else {
            for(int i = 1; i <= l; i++){
                s.push(str[l-i]);
            }
        }
    }
    
}

void analyis(){
    s.push(';');
    s.push('E');
    int end = Len(target);
    int i = 0;
    while(i < end){
        if(s.top()==target[i] && target[i]==';'){
            cout<<obj<<endl<<"正确"<<endl;
            break;
        } else {
            if(s.top()==target[i]){
                s.pop();
                i++;
            }
            if(table[s.top()].count(target[i])==0){
                cout<<obj<<endl<<"错误"<<endl;
                break;
            }
            string val = table[s.top()][target[i]];
            // cout<<val<<endl;
            s.pop();
            pushStr(s, val);
            // cout<<"top:\t"<<s.top()<<endl;
            // cout<<"target:\t"<<target[i]<<endl;
        }
    }
}

int main(){
    initTable();
    string str;
    str = readfile("expression.txt", str);
    int len = Len(str);
    // 0 标识符 1 十进制数字 2 八进制数字 3 十六进制数字
    while(idx < len){
        scan(str);
        switch(sign){
            // 标识符
            case 0:
            case 3:
                target+='i';
                obj+=strbuf;
                // cout<<"letter"<<" "<<strbuf<<endl;
                break;
            // 数字
            case 1:
            case 2:
                target+='i';
                obj+=to_string(num);
                // cout<<"number"<<" "<<num<<endl;
                break;
            case 4:
                // ; 相当于 # 结束符，进行语法分析
                target+=strbuf;
                obj+=strbuf;
                // cout<<"sign"<<" "<<strbuf<<endl;
                if(strbuf[0]==';'){
                    analyis();
                    target="";
                    obj="";
                }
                break;
        }
    }
    return 0;
}