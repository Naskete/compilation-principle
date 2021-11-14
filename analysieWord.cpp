#include <iostream>
#include <string>
using namespace std;

// 0 标识符 1 十进制数字 2 八进制数字 3 十六进制数字
int sign = -1;
int otcflag = 0; // 八进制标志
int hexflag = 0; // 十六进制标志
int idx = 0;
int num = 0;
string strToken = "";

string keyword[5] = {"if", "then", "else", "while", "do"};
char signal[10] = {'+', '-', '*', '/', '>', '<', '=','(', ')', ';'};

bool IsLetter(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool IsDigit(char ch){
    return (ch >= '0' && ch<='9');
}

int getLength(string str){
    return str.length();
}

void scan(string str){
    if(str[idx]==' '){
        sign = -1;
        idx++;
    } else {
        strToken = "";
        if(IsLetter(str[idx])){
            while(IsLetter(str[idx])){
                strToken+=str[idx];
                idx++;
            }
            sign = 0;
            for(int i = 0; i < 5; i++){
                if(strToken==keyword[i]){
                    sign = 4;
                    break;
                }
            }
        } else if(IsDigit(str[idx])){
            otcflag = 0, hexflag = 0;
            // 判断进制
            if(str[idx]=='0'&&str[idx+1]!=' '&&(idx+1<getLength(str))){
                idx++;
                if(str[idx]=='x'||str[idx]=='X'){
                    // 十六进制
                    hexflag = 1;
                    idx++;
                }
                if(IsDigit(str[idx+1]))
                    otcflag = 1;
            }
            // 十六进制
            if(hexflag){
                while(IsDigit(str[idx])||IsLetter(str[idx])){
                    strToken+=str[idx];
                    idx++;
                }
            } else {
                // 十进制    
                num = 0;
                while(IsDigit(str[idx])){
                    num = num*10 + str[idx] - '0';
                    idx++;
                }
            }
            sign = 1 + otcflag + hexflag;
        } else {
            // 界符
            for(int i = 0; i < 10; i++){
                if(str[idx]==signal[i]){
                    strToken+=str[idx];
                    // 判断 += -= *= /= == >= <=
                    if(i < 7){
                        if(str[idx+1]=='='){
                            strToken+=str[idx+1];
                            idx++;
                        }
                    }
                    sign = 4;
                    break;
                }
            }
            idx++;
        }
    }
}

int main(){
    string s = "3 >= 3 "; // 测试数据
    int length = getLength(s);
    while(idx < length){
        scan(s);
        switch(sign){
            case -1: // 空格退出
                break;
            case 0: // 标识符
            case 3: // 数字——十六进制
                cout<<"<"<<sign<<","<<strToken<<">"<<endl;
                break;
            case 1: // 数字——十进制
            case 2: // 数字——八进制
                cout<<"<"<<sign<<","<<num<<">"<<endl;
                break;
            case 4:
                cout<<"<"<<strToken<<", ->"<<endl;
                break;
            default:
                cout<<"error:"<<strToken<<endl;
        }
    }
}