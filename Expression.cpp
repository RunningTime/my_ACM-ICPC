/*
    *表达式求值，逆波兰式(后缀表达式)算法
    *输入(可以有空格，支持小数，实现'+-/*%')： ((1+2)*5+1)/4=
    *注意：取模一定是要整型，实现版本数字全是double，强制类型转换可能倒置错误
    *转换为后缀表达式： 得到：1 2 + 5 * 1 + 4 / =
    *计算后缀表达式：得到：4.00
*/
struct Exp  {
    stack<char> op;
    stack<double> num;
    bool error;
 
    int prior(char ch)  {                          //运算符的优先级
        switch (ch) {
            case '+':
            case '-': return 1;
            case '*':
            case '%':
            case '/': return 2;
            default:  return 0;
        }
    }
    bool is_digit(char ch)  {
        return '0' <= ch && ch <= '9';
    }
    string get_postfix(string s)    {              //中缀表达式转变后缀表达式
        while (!op.empty ())    op.pop ();
        op.push ('#');
        string ret = "";
        int len = s.length (), i = 0;
        while (i < len)    {
            if (s[i] == ' ' || s[i] == '=')    {
                i++;    continue;
            }
            else if (s[i] == '(')    {
                op.push (s[i++]);
            }
            else if (s[i] == ')')   {
                while (op.top () != '(')    {
                    ret += op.top ();   ret += ' ';
                    op.pop ();
                }
                op.pop ();  i++;
            }
            else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%')  {
                while (prior (op.top ()) >= prior (s[i]))    {
                    ret += op.top ();   ret += ' ';
                    op.pop ();
                }
                op.push (s[i++]);
            }
            else    {
                while (is_digit (s[i]) || s[i] == '.')  {
                    ret += s[i++];
                }
                ret += ' ';
            }
        }
        while (op.top () != '#') {
            ret += op.top ();   ret += ' ';
            op.pop ();
        }
        ret += '=';
        return ret;
    }
    double cal(double a, double b, char ch) {
        if (ch == '+')  return a + b;
        if (ch == '-')  return a - b;
        if (ch == '*')  return a * b;
        if (ch == '%')  return (int)((int)a % (int)b);
        if (ch == '/')  {
            if (b != 0) return a / b;
            error = true;   return 0;
        }
    }
    double solve(string str)    {                   //计算后缀表达式
        string s = get_postfix (str);
        while (!num.empty ())   num.pop ();
        error = false;
        int len = s.length (), i = 0;
        while (i < len)  {
            if (s[i] == ' ' || s[i] == '=') {i++;   continue;}
            else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%')  {
                double a = num.top ();  num.pop ();
                double b = num.top ();  num.pop ();
                num.push (cal (b, a, s[i]));    i++;
            }
            else  {
                double x = 0;
                while (is_digit (s[i])) {
                    x = x * 10 + s[i] - '0';    i++;
                }
                if (s[i] == '.')    {
                    double k = 10.0, y = 0;
                    i++;
                    while (is_digit (s[i])) {
                        y += ((s[i] - '0') / k);
                        i++;    k *= 10;
                    }
                    x += y;
                }
                num.push (x);
            }
        }
        return num.top ();
    }
}E;
int main(void)    {
    ios::sync_with_stdio (false);
    int T;  cin >> T;
    string str; getline (cin, str);
    while (T--) {
        getline (cin, str);
        cout << E.get_postfix (str) << endl;
        cout << fixed << setprecision (6) << E.solve (str) << endl;
    }
    return 0;
}
