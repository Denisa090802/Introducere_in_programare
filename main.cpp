#include <bits/stdc++.h>
#include "graphics.h"
#define pi 3.14159265359
#include <winbgim.h>

#include <cstring>
#include <map>
#include <vector>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <windows.h>

using namespace std;

bool eroare4=false;
bool salt = false;

stack <double> values; /// stiva pentru valori

stack <string> ops; /// stiva pentru operatori

string to_string(int x)
{
    string ans;
    while(x)
    {
        ans += char(x % 10 +'0');
        x /= 10;
    }
    return ans;
}

void transformare( string &s )
{

    int i;
    for(i=0; i<s.size()-1; i++)
    {

        if(s[i]=='('&& s[i+1]=='-')
        {
            s.insert(i+1, "0");
            i++;
        }
    }
/// (-3)+5    (0-3)+5
}
int esteLiteraCifraOperator (char s)
{


    if(s>='a' && s<='z') return 1;
    else if(s>='0' && s<='9') return 1;
    else if(s=='+'||s =='-'|| s=='*'|| s=='^'|| s =='*'|| s=='/'|| s==')'|| s=='('|| s =='<'|| s =='>'|| s =='=') return 1;
    return 0;
}

int verifParanteze ( string s )
{
    int p=0,i;
    for(i=0; i<s.size(); i++)
    {
        if(s[i]=='(') p++;
        else if(s[i]==')') p--;

    }

    for(i=0; i<s.size()-1; i++) if(s[i]=='(' && s[i+1]==')') return 0;
    if(p!=0) return 0;
    return 1;
}
int verifOperatori( string s )
{
    int p=0,i;
    for(i=0; i<s.size()-1; i++)
    {
        if((s[i]== '+' || s[i]== '-' || s[i] == '*' || s[i] == '/' || s[i] == '>' || s[i] == '<' ||s[i] == '^') && (s[i+1]== '+' || s[i+1]== '-' || s[i+1] == '*' || s[i+1] == '/' || s[i+1] == ')' || s[i+1] == '>' || s[i+1] == '<' ||s[i+1] == '^'))
            return 0;
    }
    for(i=0; i<s.size(); i++)
    {
        if(s[i] == ' ') return 0;
    }
    return 1;
}
int verifCaractere( string s )
{
    int i;

    string t = "";
    switch (s[s.size()-1])
    {
    case 'n':
    case 's':
    case 'g':
    case 'd':
    case '+':
    case '*':
    case '-':
    case '/':
    case '<':
    case '>':
    case '=':
        return 0;
    default :
        break;
    }
    for(i = 0; i<s.size(); i++ )
    {
        if('a'<=s[i] && s[i] <= 'z' && s[i] != 'x')
        {
            t = "";
            while('a'<=s[i] && s[i] <= 'z')
            {
                t += s[i];
                i++;
            }

        }
        if(t.size()>3) return 0;
        else if(t.size() != 0 && t!="sin" && t!="cos" && t!="tg" && t!="ctg" && t!="rad" && t!="abs" && t!="log" ) return 0;
        else if(!esteLiteraCifraOperator(s[i])) return 0;
    }

    return 1;
}
int Prioritate(string op)
{
    if(op == "+"||op == "-")
        return 1;
    if(op == "*"||op == "/")
        return 2;
    if(op=="^")
        return 3;
    if(op == "==" || op == "!=" || op=="<" || op==">" || op == ">=" || op == "<=")
        return 4;
    if(op=="sin" || op=="cos" || op=="tg" || op=="ctg" || op=="log" || op=="rad" || op=="abs")
        return 5;
    return 0;
}

double ApplyOp(double a, double b, string op)
{
    if(op == "+")
        return a+b;
    if(op == "-")
        return a-b;
    if(op == "*")
        return a*b;
    if(op == "/")
        return a/b;
    if(op == "^")
        return pow(a,b);
    if(op == "<")
        return a<b;
    if(op == "<=")
        return a<=b;
    if(op == ">")
        return a>b;
    if(op == ">=")
        return a>=b;
    if(op == "=")
        return a==b;
    if(op == "!=")
        return a!=b;
    if(op == "sin")
        return sin(a);
    if(op == "cos")
        return cos(a);
    if(op == "tg")
        return tan(a);
    if(op == "ctg")
        return cos(a)/sin(a);
    if(op == "log")
        return log(a);
    if(op == "rad")
        return sqrt(a);
    if(op == "abs")
        return abs(a);
}


void drawButton(int left, int top, int right, int bottom, string buttonText, int color = 12, int bkg = WHITE)
{
    char* str = (char*)buttonText.c_str();
    int text_w = textwidth(str);
    int text_h = textheight(str);
    int rect_w = right - left;
    int rect_h = bottom - top;
    setcolor(color);
    int x = left + (rect_w - text_w) / 2;
    int y = top + (rect_h - text_h) / 2;

    rectangle(left, top, right, bottom);
    setfillstyle(SOLID_FILL,bkg);
    floodfill(left+1, top+1, color);
    rectangle(left+5, top+5, right-5, bottom-5);
    outtextxy(x,y,str);
}


void VerificaEvalueaza()
{
    if(values.size() <= 0)
    {

        eroare4 = true;
        return;
    }

    if(ops.top() == "+" || ops.top() == "-" || ops.top() == "*" || ops.top() == "/" || ops.top() == "^" || ops.top() == "<" || ops.top() == ">" ||
            ops.top() == "<=" || ops.top() == ">=" || ops.top() == "=" || ops.top() == "!=")
    {
        if(values.size() < 2)
        {

            eroare4 = true;
            return;
        }

        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();
        string op = ops.top();
        ops.pop();
        values.push(ApplyOp(val1, val2, op)); /// punem in stiva de valori rezultatul gasit
    }
    else if(ops.top()=="rad" || ops.top()== "log" )
    {
        double val1 = values.top();
        values.pop();
        if(val1>0)
        {
            string op = ops.top();
            ops.pop();
            values.push(ApplyOp(val1, 0, op));
        }
        else
        {
            string op = ops.top();
            ops.pop();
            if(op == "log")
                values.push(ApplyOp(0.000000001, 0, op));
            else if(op == "rad")
                values.push(ApplyOp(0, 0, op));

        }
    }
    else if(ops.top() == "sin" || ops.top() == "cos" || ops.top() == "tg" || ops.top() == "ctg" || ops.top() == "abs")
    {

        double val1 = values.top();
        values.pop();
        string op = ops.top();
        ops.pop();
        values.push(ApplyOp(val1, 0, op));

    }
}

double Evaluate(string sir, double nr)
{
    int i;

    string t = "";
    eroare4=false;
    for(i = 0; sir[i] != 0; )
    {

        if(sir[i] == ' ')
            i++;

        else if(sir[i] == '(')
        {
            t = sir[i];
            ops.push(t); /// se pune caracterul in stiva de operatori
            i++;
        }

        else if(sir[i] == '+' || sir[i] == '-' || sir[i] == '*' || sir[i] == '/' || sir[i] == '^')
        {
            t = sir[i];
            while(!ops.empty() && Prioritate(ops.top())>= Prioritate(t) && !values.empty() && !eroare4)
            {
                VerificaEvalueaza();
            }
            ops.push(t);
            i++;
        }

        else if(sir[i] == '<')
        {
            if(sir[i+1] == '=')
            {
                t = "<=";
                while(!ops.empty() && Prioritate(ops.top())>= Prioritate(t) && !values.empty() && !eroare4)
                {
                    VerificaEvalueaza();
                }
                i+=2;
                ops.push(t);
            }
            else
            {
                t = "<";
                while(!ops.empty() && Prioritate(ops.top())>= Prioritate(t) && !values.empty() && !eroare4)
                {
                    VerificaEvalueaza();
                }
                ops.push(t);
                i++;
            }
        }
        else if(sir[i] == '>')
        {
            if(sir[i+1] == '=')
            {
                t = ">=";
                while(!ops.empty() && Prioritate(ops.top())>= Prioritate(t) && !values.empty() && !eroare4)
                {
                    VerificaEvalueaza();
                }
                i+=2;
                ops.push(t);
            }
            else
            {
                t = ">";
                while(!ops.empty() && Prioritate(ops.top())>= Prioritate(t) && !values.empty() && !eroare4)
                {
                    VerificaEvalueaza();
                }
                ops.push(t);
                i++;
            }
        }
        else if(sir[i] == '!')
        {
            if(sir[i+1] == '=')
            {
                t = "!=";
                while(!ops.empty() && Prioritate(ops.top())>= Prioritate(t) && !values.empty() && !eroare4)
                {
                    VerificaEvalueaza();
                }
                i+=2;
                ops.push(t);
            }
        }
        else if(sir[i] == '=')
        {
            t = "=";
            while(!ops.empty() && Prioritate(ops.top())>= Prioritate(t) && !values.empty() && !eroare4)
            {
                VerificaEvalueaza();
            }
            i++;
            ops.push(t);
        }
        else if(sir[i] == 'x')
        {
            values.push(nr);
            i++;
        }
        else if('a'<=sir[i] && sir[i] <= 'z' && sir[i] != 'x')
        {
            t = "";
            while('a'<=sir[i] && sir[i] <= 'z')
            {
                t += sir[i];
                i++;
            }

            if(t == "pi")
                values.push(pi);
            else
            {
                while(!ops.empty() && Prioritate(ops.top())>= Prioritate(t) && !values.empty() && !eroare4)
                {
                    VerificaEvalueaza();
                }
                ops.push(t);
            }

        }
        else if(isdigit(sir[i]))      /// daca este cifra
        {
            double val1 = 0, val2 = 0;

            while(i < sir.length() &&
                    isdigit(sir[i])) /// cat timp urmatorul caracter este cifra
            {
                val1 = (val1*10) + (sir[i]-'0'); /// se formeaza numarul din cifrele alaturate gasite
                i++;
            }
            if(sir[i] == ',')
            {
                i++;
                if(isdigit(sir[i]))
                {
                    int p = 1;
                    while(i < sir.length() &&
                            isdigit(sir[i]))
                    {
                        p*=10;
                        val2 = (val2*10) + (sir[i]-'0'); /// se formeaza numarul din cifrele alaturate gasite
                        i++;
                    }
                    val2 /= p;
                }
                val1 += val2;
            }
            values.push(val1); /// se pune valoarea in stiva de valori
        }

        else if(sir[i] == ')')
        {
            while(!ops.empty() && ops.top() != "(" && !values.empty() && !eroare4)  /// cat timp stiva de operatori nu este goala si expresia este corecta
            {
                VerificaEvalueaza();
            }
            if(!ops.empty())
                ops.pop();
            i++;
        }
    }
    /// efectuam restul operatiilor
    while(!ops.empty() && !values.empty() && !eroare4)
    {
        VerificaEvalueaza();
    }
    if(!values.empty()) return values.top();
    return 0;
}

const double WIDTH = 800, HEIGHT = 600;

void drawLine(int x, int y, int nx, int ny, int color)
{
    moveto(x, y);
    setcolor(color);
    lineto(nx, ny);
}

void print_pagina (bool stanga_selectat, bool dreapta_selectat, bool functie_selectat, string stanga, string dreapta, string functie,string eroare );

static std::string double_to_string(double d)
{
    std::ostringstream oss;
    oss.precision(5);
    oss << std::fixed << d;
    std::string str = oss.str();

    std::size_t pos1 = str.find_last_not_of("0");
    if(pos1 != std::string::npos)
        str.erase(pos1+1);

    std::size_t pos2 = str.find_last_not_of(".");
    if(pos2 != std::string::npos)
        str.erase(pos2+1);

    return str;
}

void AfisareGrafic(double a, double b, string s)
{
    int WIDTH=800, HEIGHT=600;
    setbkcolor(WHITE);
    cleardevice();
    double x, y = 0, maxim= -99999999, minim = 99999999;
    // minim = 1<<31, maxim = -(1<<31);
    double m1, m2, n1, n2;
    double start1, start2;
    double nry = 0, nrx = 0;

    //Aflu maximul si minimul functie si coordonatele unei numar intreg prin care trece functia
    float yy;
    float y1,y2;
    bool ok1=0,ok2=0, minl = 0, maxl = 0;
    int i=720,j=720;

    for(x = a; x <= b; x += 0.01)
    {
        y = Evaluate(s, x);
            if(y < minim)
                minim = y;
            if(y > maxim)
                maxim = y;
            if(nrx == 0)
            {

                string t = to_string(y);
                /*stringstream ss;
                   ss << y;
                   string t=ss.str();
                */
                int i;
                for(i = 0; t[i] && t[i] != '.'; i++)
                    ;
                if(t[i] == 0)
                {
                    nrx = x;
                    nry = y;
                }
                else if((t[i + 1] == t[i + 2]) && (t[i +1] == t[i + 3]) && (t[i + 1] == t[i + 4]) && (t[i + 1] == '0'))
                {
                    int semn = 1, j = 0;
                    if(t[0] == '-')
                    {
                        semn = -1;
                        j++;
                    }
                    for(; t[j] != '.'; j++)
                        nry = nry * 10 + (t[j] - '0');
                    nry *= semn;
                    nrx = x;
                }

        }

    }
    double raport = 1.00000*740/(b - a);
    double stanga = 30, dreapta = WIDTH - 30, sus, jos;
    sus = 280 - abs(maxim * raport);
    jos = 280 + abs(minim * raport);
    m1 = (stanga - dreapta) / (a - b);
    n1 = stanga - m1 * a;
    m2 = (sus - jos) / (maxim - minim);
    n2 = sus - m2 * maxim;
    double raport1 = raport;
    int pas = 1;
    if((b - a) > 20 && (b - a) <= 100)
    {
        pas = 5;
        raport1 = raport * 5;
    }
    else if((b - a) > 100 && (b - a) <= 1000)
    {
        pas = 50;
        raport1 = raport * 50;
    }
    else if((b - a) > 1000)
    {
        pas = 1000;
        raport1 = raport * 1000;
    }
    x = 30;
    y = 555;
    for(int i = a; i <= b; i+=pas)
    {
        setcolor(7);
        if(i == 0) setcolor(BLACK);
        line(x, 550, x, 10);
        x+=raport1;
    }
    x = 10;
    y = m2 * nry + n2;
    for(int i = nry; y > 10; i+=pas)
    {
        setcolor(7);
        if(i == 0) setcolor(BLACK);
        if(y > 550) setcolor(WHITE);
        line(30, y, 770, y);
        y-=raport1;
    }
    x = 10;
    y = m2 * nry + n2;
    for(int i = nry; y < 550; i-=pas)
    {
        setcolor(7);
        if(i == 0) setcolor(BLACK);
        if(y < 10) setcolor(WHITE);
        line(30, y, 770, y);
        y+=raport1;
    }

    //Trasez graficul
    start1 = m1 * a + n1;
    start2 = m2 * Evaluate(s, a) + n2;
    for(x = a + 0.01; x <= b; x += 0.01)
    {
        y = Evaluate(s, x);
        setcolor(RED);
        if((start2 < 10 || start2 > 550) && (((m2 * y + n2) < 10) || ((m2 * y + n2) > 550)))
            setcolor(WHITE);
        if((m2 * y + n2) < 10)
            line(start1, start2, m1 * x + n1, 10);
        else if((m2 * y + n2) > 550)
            line(start1, start2, m1 * x + n1, 550);
        else if(start2 < 10)
            line(start1, 10, m1 * x + n1, m2 * y + n2);
        else if(start2 > 550)
            line(start1, 550, m1 * x + n1, m2 * y + n2);
        else
            line(start1, start2, m1 * x + n1, m2 * y + n2);
        start1 = m1 * x + n1;
        start2 = m2 * y + n2;

    }

    //Trasez coordonatele pe axe
    x = 30;
    y = 555;
    if((a>=10 && a <= 99) || (a<=-10 && a >=-99))
        x = 22;
    if((a>=100 && a <= 999) || (a<=-100 && a >= -1000))
        x = 18;
    if((a >= 1000) || (a < -1000))
        x = 12;
    if(((b - a) > 20 && (b - a) < 100) || ((b-a < -20) && (b-a) > -100))
    {
        pas = 5;
        raport1 = raport * 5;
    }
    else if(((b - a) > 100 && (b - a) <= 1000) || ((b-a) < -100 && (b-a) >=-1000))
    {
        pas = 50;
        raport1 = raport * 50;
    }
    for(int i = a; i <= b; i+=pas)
    {
        stringstream strs;
        strs << i;
        string temp_str = strs.str();
        char* char_type = (char*) temp_str.c_str();
        setcolor(BLACK);
        settextstyle(8,0,1);
        outtextxy(x,y,char_type);
        x+=raport1;
    }
    x = 10;
    y = m2 * nry + n2;
    for(int i = nry; y > 10; i+=pas)
    {
        stringstream strs;
        strs << i;
        string temp_str = strs.str();
        char* char_type = (char*) temp_str.c_str();
        setcolor(BLACK);
        settextstyle(8,0,1);
        if(y > 550) setcolor(WHITE);
        outtextxy(x,y,char_type);
        y-=raport1;
    }
    x = 10;
    y = m2 * nry + n2;
    for(int i = nry; y < 550; i-=pas)
    {
        stringstream strs;
        strs << i;
        string temp_str = strs.str();
        char* char_type = (char*) temp_str.c_str();
        setcolor(BLACK);
        settextstyle(8,0,1);
        if(y < 10) setcolor(WHITE);
        outtextxy(x,y,char_type);
        y+=raport1;
    }
    //Trasez careul negru
    drawLine(30,10,WIDTH - 30, 10, BLACK);
    drawLine(30, HEIGHT - 50, WIDTH - 30, HEIGHT - 50, BLACK);
    drawLine(30, 10, 30, HEIGHT - 50, BLACK);
    drawLine(WIDTH - 30, 10, WIDTH - 30, HEIGHT - 50, BLACK);

    settextstyle(5,0,2);
    drawButton(720,720,790,790, "back",2);
    drawButton(40, 600, 160, 650, "zoom in",2);
    drawButton(180, 600, 300, 650, "zoom out",2);
    drawButton(500, 600, 620, 650, "move left",2);
    drawButton(640, 600, 760, 650, "move right",2);
    rectangle(40,660,700,795);

    /// ****************


    /// parcurgerea pentru aflarea punctelor de extrem
    settextstyle(8,0,1);
    setcolor(RED);
    outtextxy(60,680,"minim global:");
    outtextxy(390,680,"maxim global:");
    outtextxy(60,720,"minim local:");
    outtextxy(390,720,"maxim local:");

    minim = 0;
    bool min_set = false;
    maxim = 0;
    bool max_set = false;

    const int max_level = 1000000;
    ok1=0;
    ok2=0;
    minl = 0;
    maxl = 0;
    i=720;
    j=720;
    for(x = a; x <= b; x += 0.01)
    {
        y = Evaluate(s, x);
        if(y > 0)
        {
            if(y > max_level)
                break;
        }
        if(y < 0)
        {
            if(y < -max_level)
                break;
        }


        if(y < minim)
        {
            minim = y;
            min_set = true;
        }
        if(y > maxim)
        {
            maxim = y;
            max_set = true;
        }

        if(x-0,01 >= a)
        {
            y1 = Evaluate(s, x-0.01);
            ok1=1;
        }
        if(x+0.01 <= b )
        {
            y2 = Evaluate(s, x+0.01);
            ok2=1;
        }
        if(x == a)
        {
            if(y2 < y)
            {
                setcolor(BLUE);
                if(((m2 * y + n2) < 10) || ((m2 * y + n2) > 550))
                setcolor(WHITE);
                circle(m1 * x + n1, m2 * y + n2, 6);
                circle(m1 * x + n1, m2 * y + n2, 8);
            }
            else if(y2 > y)
            {
                setcolor(GREEN);
                if(((m2 * y + n2) < 10) || ((m2 * y + n2) > 550))
                setcolor(WHITE);
                circle(m1 * x + n1, m2 * y + n2, 6);
                circle(m1 * x + n1, m2 * y + n2, 8);
            }

        }
        else if(x == b)
        {
            if(y1 < y)
            {
                setcolor(BLUE);
                if(((m2 * y + n2) < 10) || ((m2 * y + n2) > 550))
                setcolor(WHITE);
                circle(m1 * x + n1, m2 * y + n2, 6);
                circle(m1 * x + n1, m2 * y + n2, 8);
            }
            else if(y1 > y)
            {
                setcolor(GREEN);
                if(((m2 * y + n2) < 10) || ((m2 * y + n2) > 550))
                setcolor(WHITE);
                circle(m1 * x + n1, m2 * y + n2, 6);
                circle(m1 * x + n1, m2 * y + n2, 8);
            }
        }
        else
        {
            if(y1 > y && y < y2)
        {
            setcolor(GREEN);
            if(((m2 * y + n2) < 10) || ((m2 * y + n2) > 550))
                setcolor(WHITE);
            circle(m1 * x + n1, m2 * y + n2, 6);
            circle(m1 * x + n1, m2 * y + n2, 8);
        }
        if(y1 < y && y > y2)
        {
            setcolor(BLUE);
            if(((m2 * y + n2) < 10) || ((m2 * y + n2) > 550))
                setcolor(WHITE);
            circle(m1 * x + n1, m2 * y + n2, 6);
            circle(m1 * x + n1, m2 * y + n2, 8);
        }
        }
        setcolor(BLACK);
        if(i<=800 && ok1 && y1>y && y2>y)
        {
            string pp1 = double_to_string(y);
            char* str = (char*)pp1.c_str();
            if(i>=780) outtextxy(220,i, " ... " );
            else outtextxy(220,i,str);
            i+=20;

        }
        if(j<=800 && ok2 && y1<y && y2<y)
        {
            string pp2 = double_to_string(y);
            char* str = (char*)pp2.c_str();
            if(j>=780) outtextxy(550,j, " ... " );
            else outtextxy(550,j,str);
            j+=20;

        }

    }

    /*cout<<"minim  "<<minim<<"-"<<double_to_string(minim)<<endl;
    cout<<"maxim "<<maxim<<"-"<<double_to_string(maxim)<<endl;
    */

    if(min_set)
    {
        string p1 = double_to_string(minim);
        char* str1 = (char*)p1.c_str();
        settextstyle(8,0,1);
        setcolor(BLACK);
        outtextxy(220,680,str1);
    }
    if(max_set)
    {
        string p2 = double_to_string(maxim);
        char* str2 = (char*)p2.c_str();
        settextstyle(8,0,1);
        setcolor(BLACK);
        outtextxy(550,680,str2);
    }


    ///******************


}

void print_pagina (bool stanga_selectat, bool dreapta_selectat, bool functie_selectat, string stanga, string dreapta, string functie,string eroare )
{
    if(eroare.size() != 0)
    {
        readimagefile("poza.jpg", 0, 0, 800, 800);
    }
    setbkcolor(0);

    int x=1,i;

    settextstyle(5,0,3);
    drawButton(750, 10, 790, 50, "?", 12, BLACK);
    drawButton(200, 600, 600, 700, "Arata grafic", 12, BLACK);
    settextstyle(5,0,3);
    drawButton(200, 100, 600, 200, (functie.size()!=0 || functie_selectat)?functie:"Introduceti functia", functie_selectat?2:14, BLACK);
    drawButton(200, 250, 600, 350, (stanga.size()!=0 || stanga_selectat)?stanga:"Introduceti interval stanga", stanga_selectat?2:14, BLACK);
    drawButton(200, 400, 600, 500, (dreapta.size()!=0 || dreapta_selectat)?dreapta:"Introduceti interval dreapta", dreapta_selectat?2:14, BLACK);
    if(eroare.size()!=0)
    {
        drawButton(200, 530, 600, 575, eroare, 4, BLACK);
    }
}
void pagina()
{
    int home = initwindow(800,800,"Graficul functiei");
    readimagefile("poza.jpg", 0, 0, 800, 800);

    bool stanga_selectat = false;
    bool dreapta_selectat = false;
    bool functie_selectat = false;

    string functie="";
    string stanga="";
    string dreapta="";
    string eroare="";

    print_pagina(stanga_selectat, dreapta_selectat, functie_selectat, stanga, dreapta, functie, eroare);

    POINT cursorPosition;
    int mX, mY;
    bool prima_pagina = true;

    int a,b;

    bool ignore = false;
    while(true)
    {
        bool changed = false;
        bool selectie_changed = false;

        bool changed1 = false, changed2 = false, changed3= false, changed4 = false, changed5 = false, changed6 = false;

        if(GetAsyncKeyState(VK_LBUTTON)) /// spune daca s-a dat click pe mouse
        {
            GetCursorPos(&cursorPosition);
            ScreenToClient(GetForegroundWindow(), &cursorPosition);
            mX = cursorPosition.x;
            mY = cursorPosition.y;

            /// *****
            if( 600 <= mY && mY <= 700)
            {
                if(200 <= mX && mX <= 600)
                {
                    changed = true;
                    ignore = true;
                }
            }
            /// *****
            if( 250<= mY && mY<=350 )
                if( 200 <= mX && mX <= 600)
                {
                    stanga_selectat = !stanga_selectat;
                    if(stanga_selectat)
                    {
                        dreapta_selectat = false;
                        functie_selectat = false;
                    }
                    selectie_changed = true;
                    ignore = true;
                }


            if( 400<= mY && mY<=500 )
                if( 200 <= mX && mX <= 600)
                {
                    dreapta_selectat = !dreapta_selectat;
                    if(dreapta_selectat)
                    {
                        stanga_selectat = false;
                        functie_selectat = false;
                    }
                    selectie_changed = true;
                    ignore = true;
                }

            if( 100<= mY && mY<=200 )
                if( 200 <= mX && mX <= 600)
                {
                    functie_selectat = !functie_selectat;
                    if(functie_selectat)
                    {
                        stanga_selectat = false;
                        dreapta_selectat = false;
                    }
                    selectie_changed = true;
                    ignore = true;
                }

            ///Controale pt pagina graficului
            /// zoom in
            if( 600 <= mY && mY <= 650)
            {
                if(40 <= mX && mX <= 160)
                {
                    changed1 = true;
                }
            }
            ///zoom out
            if( 600 <= mY && mY <= 650)
            {
                if(180 <= mX && mX <= 300)
                {
                    changed2= true;
                }

            }
            ///back
            if( 730 <= mY && mY <= 780)
            {
                if( 730<= mX && mX <=780 )
                {
                    changed3 = true;
                }
            }

            ///750, 10, 790, 50
            if( 10 <= mY && mY <= 50)
            {
                if( 750<= mX && mX <=790 )
                {
                    changed4 = true;
                }
            }

            ///move left
            if( 600 <= mY && mY <= 650)
            {
                if( 500<= mX && mX <=620 )
                {
                    changed5 = true;
                }

            }
            ///move right
            if( 600 <= mY && mY <= 650)
            {
                if( 640<= mX && mX <=760 )
                {
                    changed6 = true;
                }
            }

        }

        if(prima_pagina)
        {

            bool enter_pressed = false;
            if(!ignore)
            {
                if(stanga_selectat)
                {
                    char c = getch();
                    if(c == 8)
                        stanga = stanga.substr(0, stanga.size()-1);
                    else if(c == 13)
                    {
                        enter_pressed = true;
                        stanga_selectat = false;
                    }
                    else
                        stanga.push_back(c);
                    selectie_changed = true;
                }
                if(dreapta_selectat)
                {
                    char c = getch();
                    if(c == 8)
                        dreapta = dreapta.substr(0, dreapta.size()-1);
                    else if(c == 13)
                    {
                        enter_pressed = true;
                        dreapta_selectat = false;
                    }
                    else
                        dreapta.push_back(c);
                    selectie_changed = true;
                }
                if(functie_selectat)
                {
                    char c = getch();
                    if(c == 8)
                        functie = functie.substr(0, functie.size()-1);
                    else if(c == 13)
                    {
                        enter_pressed = true;
                        functie_selectat = false;
                    }
                    else
                        functie.push_back(c);
                    selectie_changed = true;
                }
            }
            if(enter_pressed == false)
                ignore = false;
             if(changed4)
             {
                 system("regulament.exe");
             }


            if(changed)
            {
                cleardevice();
                stringstream stg(stanga);
                stringstream dr(dreapta);
                stg >> a;
                dr>> b;

                eroare = "";
                transformare(functie);
                // settextstyle(5,0,3);
                if(verifOperatori(functie)==0)
                {
                    eroare += "eroare operatori  ";
                    selectie_changed = true;
                }
                if(verifParanteze(functie)==0)
                {
                    eroare += "eroare paranteze  ";
                    selectie_changed = true;
                }
                if(verifCaractere(functie)==0)
                {
                    eroare += "eroare caractere  ";
                    selectie_changed = true;
                }
                if( a>=b  )
                {
                    eroare += "eroare interval  ";
                    selectie_changed = true;
                }
                if(eroare.size()== 0)
                {
                    double rezultat = Evaluate(functie,8);
                    if(eroare4 == false )
                    {
                        prima_pagina = false;
                        AfisareGrafic(a,b,functie);

                    }
                    else
                    {
                        eroare += "eroare ";
                        selectie_changed = true;
                    }
                }

            }
            if(selectie_changed )
            {
                setviewport(200, 100, 601, 201, 1);
                clearviewport();

                setviewport(200, 250, 601, 351, 1);
                clearviewport();

                setviewport(200, 400, 601, 501, 1);
                clearviewport();

                setviewport(200, 600, 601, 701, 1);
                clearviewport();

                setviewport(0,0,800,800,0);
                print_pagina(stanga_selectat, dreapta_selectat, functie_selectat, stanga, dreapta, functie,eroare);
            }

        }
        else
        {
            int k;
            k=2;
            if(changed1)
            {
                cleardevice();
                if(a+k <= b-k)
                {
                    a+=k;
                    b-=k;
                }

                AfisareGrafic(a,b,functie);
                delay(5);
            }
            else if(changed2)
            {
                cleardevice();
                a-=k;
                b+=k;

                AfisareGrafic(a,b,functie);
                delay(5);
            }
            else if(changed3)
            {
                cleardevice();
                readimagefile("poza.jpg", 0, 0, 800, 800);
                prima_pagina = true;
                print_pagina(stanga_selectat, dreapta_selectat, functie_selectat, stanga, dreapta, functie, eroare);
            }
            else if(changed5)
            {
                cleardevice();
                a-=k;
                b-=k;

                AfisareGrafic(a,b,functie);
                delay(5);
            }
            else if(changed6)
            {
                cleardevice();
                a+=k;
                b+=k;

                AfisareGrafic(a,b,functie);
                delay(5);
            }
        }
        delay(5);
    }
}
int main()
{
    pagina();
    getch();
    closegraph();
    return 0;
}
