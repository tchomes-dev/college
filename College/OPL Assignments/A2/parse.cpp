/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2020.
*/

#include <string>
#include <iostream>

#include "scan.h"

using std::string;
using std::cout;

const string names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

static token input_token;

void error () {
    cout << "syntax error\n"; //changed to cout
    exit (1);
}

void match (token expected) {
    if (input_token == expected) {
        cout << "matched " << names[input_token]; //changed to cout
        if (input_token == t_id || input_token == t_literal)
            cout << ": " << token_image;
        cout << "\n";
        input_token = scan ();
    }
    else error ();
}

void program ();
void stmt_list ();
void stmt ();
void expr ();
void cond ();
void term ();
void term_tail ();
void factor ();
void factor_tail ();
void rel_op ();
void add_op ();
void mul_op ();

void program () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict program --> stmt_list eof\n"; //changed to cout
            stmt_list ();
            match (t_eof);
            break;
        default: error ();
    }
}

void stmt_list () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
            cout << "predict stmt_list --> stmt stmt_list\n"; //changed to cout
            stmt ();
            stmt_list ();
            break;
        case t_eof:
            cout << "predict stmt_list --> epsilon\n"; //changed to cout
            break;          /* epsilon production */
        default: error ();
    }
}

void stmt () {
    switch (input_token) {
        case t_id:
            cout << "predict stmt --> id gets expr\n"; //changed to cout
            match (t_id);
            match (t_gets);
            expr ();
            break;
        case t_read:
            cout << "predict stmt --> read id\n"; //changed to cout
            match (t_read);
            match (t_id);
            break;
        case t_write:
            cout << "predict stmt --> write expr\n"; //changed to cout
            match (t_write);
            expr ();
            break;
//added case for if tokens
        case t_if:
            cout << "predict stmt --> if cond stmt_list\n"; //changed to cout
            cond();
            stmt_list();
            break;
//added case for while tokens
        case t_while:
            cout << "predict stmt --> while cond stmt_list\n"; //changed to cout
            cond();
            stmt_list();
            break;
        default: error ();
    }
}

void expr () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            cout << "predict expr --> term term_tail\n"; //changed to cout
            term ();
            term_tail ();
            break;
        default: error ();
    }
}

//added conditons
void cond() { 
    switch (input_token) { 
        case t_id:         
        case t_literal:         
        case t_lparen:             
            cout << "predict cond_expr --> expr ro expr\n";             
            expr();             
            rel_op();             
            expr();             
            break;         
        default: error(); 
    } 
}

void term () {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            cout << "predict term --> factor factor_tail\n"; //changed to cout
            factor ();
            factor_tail ();
            break;
        default: error ();
    }
}

void term_tail () {
    switch (input_token) {
        case t_add:
        case t_sub:
            cout << "predict term_tail --> add_op term term_tail\n"; //changed to cout
            add_op ();
            term ();
            term_tail ();
            break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict term_tail --> epsilon\n"; //changed to cout
            break;          /* epsilon production */
        default: error ();
    }
}

void factor () {
    switch (input_token) {
        case t_literal:
            cout << "predict factor --> literal\n"; //changed to cout
            match (t_literal);
            break;
        case t_id :
            cout << "predict factor --> id\n"; //changed to cout
            match (t_id);
            break;
        case t_lparen:
            cout << "predict factor --> lparen expr rparen\n"; //changed to cout
            match (t_lparen);
            expr ();
            match (t_rparen);
            break;
        default: error ();
    }
}

void factor_tail () {
    switch (input_token) {
        case t_mul:
        case t_div:
            cout << "predict factor_tail --> mul_op factor factor_tail\n";
            mul_op ();
            factor ();
            factor_tail ();
            break;
        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            cout << "predict factor_tail --> epsilon\n";
            break;          /* epsilon production */
        default: error ();
    }
}

//added relation operations
void rel_op () {
    switch (input_token) {
        case t_equal:
        case t_notequal:
        case t_less:
        case t_greater:
        case t_lessequal:
        case t_greaterequal:
    }
}

void add_op () {
    switch (input_token) {
        case t_add:
            cout << "predict add_op --> add\n";
            match (t_add);
            break;
        case t_sub:
            cout << "predict add_op --> sub\n";
            match (t_sub);
            break;
        default: error ();
    }
}

void mul_op () {
    switch (input_token) {
        case t_mul:
            cout << "predict mul_op --> mul\n";
            match (t_mul);
            break;
        case t_div:
            cout << "predict mul_op --> div\n";
            match (t_div);
            break;
        default: error ();
    }
}

int main () {
    input_token = scan ();
    program ();
    return 0;
}
