#include<iostream>

using namespace std;


string addition(string a,string b){
    int len1 = a.length(),len2 = b.length();
    int i=len1-1,j=len2-1,carry=0,sum=0;
    string result = "";
    for(;i>=0 && j>=0;i--,j--){
        int x = a.at(i) - '0',y = b.at(j) - '0';
        int res = x + y + carry;
        sum=res%10;
        res/=10;
        carry=0;
        if(res != 0){
            carry=res%10;
        }
        char ch = sum + '0';
        result.insert(0,1,ch);
    }
    
    while(i >= 0){
        int x = a.at(i) - '0';
        int res = x + carry;
        int sum=res%10;
        res/=10;
        carry=0;
        if(res != 0){
            carry=res%10;
        }
        char ch = sum + '0';
        result.insert(0,1,ch);
        i--;
    }
    while(j >= 0){
        int y = b.at(j) - '0';
        int res = y + carry;
        int sum=res%10;
        res/=10;
        carry=0;
        if(res != 0){
            carry=res%10;
        }
        char ch = sum + '0';
        result.insert(0,1,ch);
        j--;
    }
    if(carry != 0){
        result.insert(0,1,carry + '0');
    }
    return result;
}

string subtraction(string a,string b){
    
    int len1=a.length(),len2=b.length();
    int borrow=0,i=len1-1,j=len2-1;
    string result = "";
    for(;i>=0 && j>=0;i--,j--){
        int x=a.at(i) - '0',y=b.at(j) - '0';
        if(borrow == 1){
            if(x > 0){
                borrow=0;
                x--;
            }
            else{
                x = borrow * 10 - 1;
            }
        }
        if(x < y){
            borrow=1;
            x = borrow * 10 + x;
        }
        int temp = x - y;
        result.insert(0,1,temp + '0');
    }
    while(i >= 0){
        int x = a.at(i) - '0';
        if(borrow == 1){
            if(x > 0){
                borrow=0;
                x--;
            }
            else{
                x = borrow * 10 - 1;
            }
        }
        result.insert(0,1,x + '0');
        i--;
    }
    int k=0;
    while(k < result.length()-1 && result[k] == '0'){
        k++;
    }
    string res = "";
    for(int i=k;i<result.length();i++){
        res.append(1,result[i]);
    }
    return res;
}

string multiply(string a,string b){
    
    if(a == "0" || b == "0"){
        return "0";
    }
    int a_len = a.length(),b_len = b.length();
    string result = "";
    for(int i=0;i<a_len;i++){
        result.append(1,'0');
        int carry = 0;
        string temp = "";
        for(int j=b_len-1;j>=0;j--){
            int num1 = a[i] - '0';
            int num2 = b[j] - '0';
            int prod = num1 * num2 + carry;
            int to_add = prod % 10;
            carry = 0;
            prod = prod / 10;
            if(prod != 0){
                carry = prod % 10;
            }
            temp.insert(0,1,to_add + '0');
        }
        if(carry != 0){
            temp.insert(0,1,carry + '0');
        }
        result = addition(result,temp);
    }
    return result;
}

string divideBy2(string num){
    int len = num.length();
    int carry = 0;
    string result = "";
    for(int i=0;i<len;i++){
        int digit = (num[i] - '0') + (carry * 10);
        carry = 0;
        int to_add = digit / 2;
        if(digit % 2 != 0){
            carry = digit % 2;
        }
        result.append(1,to_add + '0');
    }
    int k=0;
    while(k < result.length()-1 && result[k] == '0'){
        k++;
    }
    string res = "";
    for(int i=k;i<result.length();i++){
        res.append(1,result[i]);
    }
    return res;
}

string exponent(string x,string y){
    int y_len = y.length();
    if(y_len == 1){
        if(y[0] == '1'){
            return x;
        }
        if(y[0] == '0'){
            return "1";
        }
    }
    int unit_digit = y[y_len - 1] - '0';
    string left,right;
    if(unit_digit % 2 == 1){
        left = x;
        right = exponent(x,subtraction(y,"1"));
        return multiply(left,right);
    }
    left = exponent(x,divideBy2(y));
    return multiply(left,left);
}

string factorial(string num){
    string result = "1";
    if(num == "0" || num == "1"){
        return "1";
    }
    while(num != "1"){
        result = multiply(result,num);
        num = subtraction(num,"1");
    }
    return result;
}

bool isOperator(char ch){
    return ch == '+' || ch == '-' || ch == 'x';
}

string perform(string op1,string op2,char oper){
    string result = "";
    switch(oper){
        case '+':
            result = addition(op1,op2);
            break;
        case '-':
            result = subtraction(op1,op2);
            break;
        case 'x':
            result = multiply(op1,op2);
            break;
    }
    return result;
}


string evaluate(string exp){
    int n = exp.length();
    char optr_stack[3000];
    string opnd_stack[3000];
    string operand = "";
    int opti = -1,opndi = -1;
    for(int i=0;i<n;i++){
        char ch = exp[i];
        if(!isOperator(ch)){
            operand.append(1,ch);
            continue;
        }
        opnd_stack[++opndi] = operand;
        operand = "";
        if(opti == -1 || ch == 'x'){
            optr_stack[++opti] = ch;
        }
        else{
            char top = optr_stack[opti];
            while(opti != -1 && top == 'x'){
                string op2 = opnd_stack[opndi--];
                string op1 = opnd_stack[opndi--];
                string result = "";
                result = perform(op1,op2,top);
                opnd_stack[++opndi] = result;
                top = optr_stack[--opti];
            }
            optr_stack[++opti] = ch;
        }
    }
    if(operand != ""){
        opnd_stack[++opndi] = operand;
    }
    
    while(opti != -1){
        char optr = optr_stack[opti--];
        string op2 = opnd_stack[opndi--];
        string op1 = opnd_stack[opndi--];
        opnd_stack[++opndi] = perform(op1,op2,optr);
    }
    return opnd_stack[0];
}

string removeLeadingZeros(string x){
    int i=0;
    for(;i<x.length()-1;i++){
        if(x[i] != '0'){
            break;
        }
    }
    if(i >= x.length()){
        return "";
    }
    return x.substr(i);
}

bool isAGreaterThanB(string x,string y){
    x = removeLeadingZeros(x);
    y = removeLeadingZeros(y);
    int x_len = x.length();
    int y_len = y.length();
    if(x_len > y_len){
        return true;
    }
    if(x_len == y_len){
        for(int i=0;i<x_len;i++){
            int num1 = x[i] - '0';
            int num2 = y[i] - '0';
            if(num1 > num2){
                return true;
            }
            else if(num1 < num2){
                break;
            }
        }
    }
    return false;
}

bool isAEqualB(string a,string b){
    a = removeLeadingZeros(a);
    b = removeLeadingZeros(b);
    int a_len = a.length();
    int b_len = b.length();
    if(a_len < b_len){
        return false;
    }
    for(int i=0;i<a_len;i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

string getReminder(string big,string small){
    string dividend = big;
    int idx = 0;
    string target = "";
    while(isAGreaterThanB(dividend,small) || isAEqualB(dividend,small)){
        target = removeLeadingZeros(target);
        while(isAGreaterThanB(small,target) || (!isAEqualB(small,target) && !isAGreaterThanB(target,small))){
            target.append(1,big[idx]);
            idx++;
        }
        int count = 1;
        string temp = small;
        while(isAGreaterThanB(target,temp) || isAEqualB(target,temp)){
            temp = multiply(small,to_string(count));
            count++;
        }
        temp = subtraction(temp,small);
        target = subtraction(target,temp);
        dividend = target;
        if(idx < big.length()){
            dividend = dividend + big.substr(idx);
        }
    }
    dividend = removeLeadingZeros(dividend);
    return dividend;
}

string gcd(string x,string y){
    if(x == "0"){
        return y;
    }
    else if(y == "0"){
        return x;
    }
    if(isAGreaterThanB(y,x)){
        return gcd(y,x);
    }
    string temp = getReminder(x,y);
    if(temp == "0"){
        return y;
    }
    return gcd(y,temp);
}


int main(){

    cout << "1. Addition, Subtraction & Multiplication" << endl;
    cout << "2. Exponentiation" << endl;
    cout << "3. GCD" << endl;
    cout << "4. Factorial" << endl;
    char option;
    cin >> option;
    string x,y,expression;
    switch(option){
        case '1':
            cin >> expression;
            cout << evaluate(expression) << endl;
            break;
        case '2':
            cin >> x;
            cin >> y;
            cout << exponent(x,y) << endl;
            break;
        case '3':
            cin >> x;
            cin >> y;
            cout << gcd(x,y) << endl;
            break;
        case '4':
            cin >> x;
            cout << factorial(x) << endl;
            break;
        default:
            cout << "Invalid Input!" << endl;
    }

    return 0;

}



