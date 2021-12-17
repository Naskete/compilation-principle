#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 0 标识符 1 十进制数字 2 八进制数字 3 十六进制数字 4 运算符、界符、关键字
int sign = -1;
int otcflag = 0; // 八进制标志
int hexflag = 0; // 十六进制标志
int idx = 0;
int num = 0;
string strbuf = "";

string keywords[5] = {"if", "then", "else", "while", "do"};
char SIGNAL[15] = {'+', '-', '*', '/', '>', '<', '=','(', ')', ';','{','}',',','"','^'};

bool IsLetter(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool IsDigit(char ch){
    return (ch >= '0' && ch<='9');
}

int Len(string str){
    return str.length();
}

string readfile(string filename, string str){
    ifstream file;
    file.open(filename, ios::in);
    if(!file.is_open()){
        cout<<"failed to read file"<<endl;
        return NULL;
    }
    string buf;
    while(getline(file, buf)){
        str+=buf;
    }
    return str;
}

void scan(string str){
    if(str[idx]==' '){
        sign = -1;
        idx++;
    } else {
        strbuf = "";
        if(IsLetter(str[idx])||str[idx]=='_'){
            while(IsLetter(str[idx])||str[idx]=='_'||IsDigit(str[idx])){
                strbuf+=str[idx];
                idx++;
            }
            sign = 0;
            for(int i = 0; i < 5; i++){
                if(strbuf==keywords[i]){
                    sign = 4;
                    break;
                }
            }
        } else if(IsDigit(str[idx])){
            otcflag = 0, hexflag = 0;
            // 判断进制
            if(str[idx]=='0'&&(idx+1<Len(str))&&str[idx+1]!=' '){
                idx++;
                if(str[idx]=='x'||str[idx]=='X'){
                    // 十六进制
                    hexflag = 1;
                    idx++;
                }
                otcflag = 1;
            }

            if(!IsDigit(str[idx]))
                otcflag = 0;
            // 十六进制
            if(hexflag){
                while(IsDigit(str[idx])|| (str[idx]>='a'&&str[idx]<='f') || (str[idx]>='A'&&str[idx]<='F')){
                    strbuf+=str[idx];
                    idx++;
                }
            } else {
                // 十进制    
                num = 0;
                if(otcflag){
                    while(str[idx]<'8'&&str[idx]>='0'){
                        num=num*10+str[idx]-'0';
                        idx++;
                    }
                    // 078 error
                } else {
                    while(IsDigit(str[idx])){
                        num = num*10 + str[idx] - '0';
                        idx++;
                    }
                }
            }
            sign = 1 + otcflag + hexflag;
        } else {
            // 界符
            bool flag = false;
            for(int i = 0; i < 15; i++){
                if(str[idx]==SIGNAL[i]){
                    strbuf+=str[idx];
                    // 判断 += -= *= /= == >= <=
                    if(i < 7){
                        if(str[idx+1]=='='){
                            strbuf+=str[idx+1];
                            idx++;
                        }
                    }
                    sign = 4;
                    break;
                }
                if(i==14){
                    flag = !flag;
                }
            }
            if(flag) {
                strbuf += str[idx];
                sign = -2;
            }
            idx++;
        }
    }
}

int main(){
    // string s = "if data+92>0x3f then data=data+01 else data=data-01+0;"; // 测试数据
    string s;
    s= readfile("program.txt", s);
    int length = Len(s);
    while(idx < length){
        scan(s);
        switch(sign){
            case -1: // 空格退出
                break;
            case 0: // 标识符
            case 3: // 数字——十六进制
                cout<<"<"<<sign<<","<<strbuf<<">"<<endl;
                break;
            case 1: // 数字——十进制
            case 2: // 数字——八进制
                cout<<"<"<<sign<<","<<num<<">"<<endl;
                break;
            case 4:
                cout<<"<"<<strbuf<<", ->"<<endl;
                break;
            default:
                cout<<"unknow:"<<strbuf<<endl;
        }
    }
}