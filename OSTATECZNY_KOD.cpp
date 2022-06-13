#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <cmath>
using namespace std;

template <class T>  // tworzymy kontner imitujący stos 
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
            delete []tab;     // usunięcie zaalokowanej dynamicznie pamięci dla Tablicy 
        }
        
        void push( T s ){
            tab[ ++top ] = s;   // przesuwanie wierzchołka stosu w górę i umieszczenie tam nowego elementu dowolnego typu 
        }
        
        T pop(){
            return tab[top--];  // usunięcie elemntu ustawionego na wierzchołku stosu
        }
        
        int size(){
            return top + 1;   // wyświetlenie ilości stosu
        }
        
        bool empty(){
            return top == -1; // sprawdzenie pustości stosu
        }
        
        bool isFull(){
            return top == maxSize - 1; //sprawdzenie pełności stosu
        }
        
        T peek(){
            return tab[top];  // zwrócenie elementu na wierzchołku stosu
        }
        
        void erase(){
            top = -1;  // pseudo wyczyszczenie wartości stosu 
        }
};

int prior( char z ){
    if( z=='+' || z=='-' ) return 1;
    if( z=='*' || z=='/' || z=='%' ) return 2;
    if( z=='^' ) return 3;
    if( z=='.' ) return 4;
    return 0;                                    // deklaracja priorytetowości znaków prawo i lewostronnych
}

float equation( float a, float b, char op ){  //deklaracja funkcji obliczeniowej kalkulatora
    
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
        case '.': result += ss1.str() + "." + ss2.str(); w = atof(result.c_str()); return w;    // funkcja atof-->zamienia ciąg znakowy na doubla
    }
    return 0;
}

float calculation( char symbol[] ){  //deklaracja funkcji wynikowej kalkulatora
    unsigned int i=0;
    
    Stack <float> values(200);                 
    Stack <char> ops(200);          // deklaracja dwóch stosów: znakowego i liczbowego
    
    for ( i = 0; i < strlen(symbol); i++) {
        if( symbol[i] == ' ' )
            continue;              // ominięcie spacji 
        
        else if( symbol[i] == '(' ){
            ops.push( symbol[i] );   //rzucenie znaku '('na stos znakowy
        }
        
        else if( isdigit(symbol[i])){   
            float val = 0;
            
            while( i<strlen(symbol) && isdigit(symbol[i]) ){
                val = (val*10) + (symbol[i]-'0');   // Przekształcenie znaku na cyfre wykorzystując alfabet ASCII
                i++;
            }
            values.push(val);          // wrzucenie liczny na stos liczbowy 
            i--;   // wrócenie do pozycji wcześniejszej przez nadprogramowe przesunięcie się na tablicy symbol
        }
        
        
        else if( symbol[i] == ')' ){
            while( !ops.empty() && ops.peek() != '(' ){   // Przechodzenie po stosie znkowym do momentu napotkania znaku '('
                float val2 = values.peek();
                values.pop();
                
                float val1 = values.peek();
                values.pop();
                
                char op = ops.peek();
                ops.pop();             // Wyrzucanie wierchołków z stosu liczbowego do momentu znalezienia znaku '('
                
                values.push( equation(val1, val2, op) ); // Wyrzucanie wierchołków z stosu znakowego do momentu znalezienia znaku '('
            }
            if( !ops.empty() )
                ops.pop();    //Opróżnienie stosu ze znaku '('
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
                ops.pop();                        //wyrzucenie operatorów i operandów wyrzszyge stopnia gdy na stos natrafi operand mniejszego stopnia 
                
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
        ops.pop();              // wyrzucanie wszystkich operatorów i operandów do równania 
                
        values.push( equation(val1, val2, op) );    
    }
    
    return values.peek();
}

int main(){
    char wynik[20];
    cin.getline( wynik, 20 );
    cout << calculation( wynik ); // wyświetlenie wyniku 

    return 0;
}
