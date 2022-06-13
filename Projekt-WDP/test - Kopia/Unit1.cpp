//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <cmath>
using namespace std;
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
char wynik[20];
int j = 0;
ofstream plik("plik.txt", ios::app);

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

template <class T>
class Stack{
    int maxSize;
    T *tab;
    int top;
    
    public:
        Stack( int size ){
            maxSize = size;
            tab = new T[ size ];
            top = -1;
        }
        
        ~Stack(){
            delete []tab;
        }
        
        void push( T s ){
            tab[ ++top ] = s;
        }
        
        T pop(){
            return tab[top--];
        }
        
        int size(){
            return top + 1;
        }
        
        bool empty(){
            return top == -1;
        }
        
        bool isFull(){
            return top == maxSize - 1;
        }
        
        T peek(){
            return tab[top];
        }
        
        void erase(){
            top = -1;
        }
};

int prior( char z ){
    if( z=='+' || z=='-' ) return 1;
    if( z=='*' || z=='/' || z=='%' ) return 2;
    if( z=='^' ) return 3;
    if( z=='.' ) return 4;
    return 0;
}

float equation( float a, float b, char op ){ 
    
    string result = "";
    double w;
    stringstream ss1;
    stringstream ss2;
    ss1 << a;
    ss2 << b;

    int one;
    int two;
    
    switch( op ){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        case '%': one = a; two = b; return one % two;
        case '.': result += ss1.str() + "." + ss2.str(); w = atof(result.c_str()); return w;
    }
    return 0;
}

float calculation( char symbol[] ){
    unsigned int i=0;
    
    Stack <float> values(200);                 
    Stack <char> ops(200);
    
    for ( i = 0; i < strlen(symbol); i++) {
        if( symbol[i] == ' ' )
            continue;
        
        else if( symbol[i] == '(' ){
            ops.push( symbol[i] );
        }
        
        else if( isdigit(symbol[i])){   
            float val = 0;
            
            while( i<strlen(symbol) && isdigit(symbol[i]) ){
                val = (val*10) + (symbol[i]-'0');
                i++;
            }
            values.push(val);
            i--;
        }
        
        
        else if( symbol[i] == ')' ){
            while( !ops.empty() && ops.peek() != '(' ){
                float val2 = values.peek();
                values.pop();
                
                float val1 = values.peek();
                values.pop();
                
                char op = ops.peek();
                ops.pop();
                
                values.push( equation(val1, val2, op) );
            }
            if( !ops.empty() )
                ops.pop();
        }
        else{
            if( symbol[i] == '-' && isdigit( symbol[i+1] ) ){
                float val = 0;
                while( i+1 < strlen(symbol) && isdigit(symbol[i+1]) ){
                    val = (val*10) + (symbol[i+1] - '0');
                    i++;
                }
                val = -val;
                values.push(val);
                continue;
            }
            
            while( !ops.empty() && prior(ops.peek()) >= prior(symbol[i]) ){  
                float val2 = values.peek();
                values.pop();
                
                float val1 = values.peek();
                values.pop();
                
                char op = ops.peek();
                ops.pop();
                
                values.push( equation(val1, val2, op) );
            }
            ops.push(symbol[i]);
            
        }
        
    }
    
    while( !ops.empty() ){
        float val2 = values.peek();
        values.pop();
                
        float val1 = values.peek();
        values.pop();
                
        char op = ops.peek();
        ops.pop();
                
        values.push( equation(val1, val2, op) );    
    }
    
    return values.peek();
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Image1->Picture->LoadFromFile("Numery/z7.bmp");
        Image2->Picture->LoadFromFile("Numery/z8.bmp");
        Image3->Picture->LoadFromFile("Numery/z9.bmp");
        Image4->Picture->LoadFromFile("Numery/z4.bmp");
        Image5->Picture->LoadFromFile("Numery/z5.bmp");
        Image6->Picture->LoadFromFile("Numery/z6.bmp");
        Image7->Picture->LoadFromFile("Numery/z1.bmp");
        Image8->Picture->LoadFromFile("Numery/z2.bmp");
        Image9->Picture->LoadFromFile("Numery/z3.bmp");
        Image10->Picture->LoadFromFile("Numery/z0.bmp");
        Image11->Picture->LoadFromFile("Numery/z..bmp");
        Image12->Picture->LoadFromFile("Numery/zce.bmp");
        Image13->Picture->LoadFromFile("Numery/z(.bmp");
        Image14->Picture->LoadFromFile("Numery/z).bmp");
        Image15->Picture->LoadFromFile("Numery/z+.bmp");
        Image16->Picture->LoadFromFile("Numery/z-.bmp");
        Image17->Picture->LoadFromFile("Numery/zm.bmp");
        Image18->Picture->LoadFromFile("Numery/zd.bmp");
        Image19->Picture->LoadFromFile("Numery/z^.bmp");
        Image20->Picture->LoadFromFile("Numery/z=.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
        wynik[j++] += '7';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2Click(TObject *Sender)
{
        wynik[j++] += '8';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3Click(TObject *Sender)
{
        wynik[j++] += '9';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4Click(TObject *Sender)
{
        wynik[j++] += '4';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image5Click(TObject *Sender)
{
        wynik[j++] += '5';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image6Click(TObject *Sender)
{
        wynik[j++] += '6';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image7Click(TObject *Sender)
{
        wynik[j++] += '1';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image8Click(TObject *Sender)
{
        wynik[j++] += '2';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image9Click(TObject *Sender)
{
        wynik[j++] += '3';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image10Click(TObject *Sender)
{
        wynik[j++] += '0';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11Click(TObject *Sender)
{
        wynik[j] = '.';
        j++;
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image12Click(TObject *Sender)
{
        for(int i=0; i<20; i++){
                wynik[i] = NULL;
        }
        j=0;
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image13Click(TObject *Sender)
{
        wynik[j++] += ' ';
        wynik[j++] += '(';
        wynik[j++] += ' ';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image14Click(TObject *Sender)
{
        wynik[j++] += ' ';
        wynik[j++] += ')';
        wynik[j++] += ' ';
        Label1->Caption = wynik;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Image15Click(TObject *Sender)
{
        wynik[j++] += ' ';
        wynik[j++] += '+';
        wynik[j++] += ' ';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image16Click(TObject *Sender)
{
        if(wynik[j-1] >= '1' && wynik[j-1] <='9'){
                wynik[j++] += ' ';
                wynik[j++] += '-';
                wynik[j++] += ' ';
                Label1->Caption = wynik;
        }
        else{
                wynik[j++] += '-';
                Label1->Caption = wynik;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image17Click(TObject *Sender)
{
        wynik[j++] += ' ';
        wynik[j++] += '*';
        wynik[j++] += ' ';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image18Click(TObject *Sender)
{
        wynik[j++] += ' ';
        wynik[j++] += '/';
        wynik[j++] += ' ';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image19Click(TObject *Sender)
{
        wynik[j++] += ' ';
        wynik[j++] += '^';
        wynik[j++] += ' ';
        Label1->Caption = wynik;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image20Click(TObject *Sender)
{
        Label1->Caption = CurrToStr(calculation(wynik));

        plik << wynik << " = " << calculation(wynik) << endl;
}
//---------------------------------------------------------------------------

