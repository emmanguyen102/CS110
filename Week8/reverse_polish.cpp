#include <iostream>

using namespace std;

float numb[80];
int pos = -1;

void push_numb(float value){
    pos++;
    numb[pos] = value;
    numb[pos+1] = 0;
}

float pop_numb(){
    float t = numb[pos];
    pos--;
    return t;
}

bool isOp(char c) {
    switch(c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '#':
            return true;
        default:
            return false;
    }
}

bool handleOp (char expression) {
    float a, b, c;
    a = b = c = 0.0;

    if (expression == '+'){
        a = pop_numb();
        b = pop_numb();
        c = (a + b);
    } else if (expression == '-'){
        a = pop_numb();
        b = pop_numb();
        c = b - a;
    } else if (expression == '*'){
        a = pop_numb();
        b = pop_numb();
        c = (a * b);
    } else if (expression == '/'){
        a = pop_numb();
        b = pop_numb();
        if(a == 0) {
            return false;
        }
        c = (b / a);
    }
    push_numb(c);
    return true;
}

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    string expr;
    cout << "EXPR> ";
    getline(cin, expr);

    if(!isdigit(expr[0])) {
        cout << "Error: Expression must start with a number" << endl;
        return EXIT_FAILURE;
    }

    string::size_type i = 0;
    string tok = "";

    while (i < expr.length()){
        //Skip white space
        while (isspace(expr[i])){
            i++;
        }

        //Check for digits and .
        if (isdigit(expr[i]) || expr[i] == '.'){
            while (isdigit(expr[i]) || expr[i] == '.'){
                tok += expr[i];
                i++;
            }
            //Push on stack number.
            push_numb(atof(tok.c_str()));
            tok = "";
        }
        //Check for operator
        else if (isOp(expr[i])){
            if(expr[i] == '#')  {
                if(pos != 0) {
                    cout << "Error: Too few operators" << endl;
                    return EXIT_FAILURE;
                } else {
                    cout << "Correct: " << numb[0] << " is the result" << endl;
                    return EXIT_SUCCESS;
                }
            } else {
                if(pos == 0) {
                    cout << "Error: Too few operands" << endl;
                    return EXIT_FAILURE;
                } else {
                    if(handleOp(expr[i])) {
                        i++;
                    } else {
                        cout << "Error: Division by zero" << endl;
                        return EXIT_FAILURE;
                    }
                }
            }
        }
        else {
            cout << "Error: Unknown character" << endl;
            return EXIT_FAILURE;
        }
    }
}
