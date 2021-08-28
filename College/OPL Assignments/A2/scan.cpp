/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2020.
*/

#include <string>
#include <iostream>
#include "scan.h"

using std::cout;
using std::string;


char token_image[MAX_TOKEN_LEN];

token scan() {
    static int c = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */

    /* skip white space */
    while (isspace(c)) {
        c = getchar();
    }
    if (c == EOF)
        return t_eof;
    if (isalpha(c)) {
        do {
            token_image[i++] = c;
            if (i >= MAX_TOKEN_LEN) {
                cout << "max token length exceeded\n"; //changed to cout
                exit(1);
            }
            c = getchar();
        } while (isalpha(c) || isdigit(c) || c == '_');
        token_image[i] = '\0';
        if (!strcmp(token_image, "read")) return t_read;
        else if (!strcmp(token_image, "write")) return t_write;
        //added if and while tokens
        else if (!strcmp(token_image, "if")) return t_if;
        else if (!strcmp(token_image, "while")) return t_while;
        else return t_id;
    }
    else if (isdigit(c)) {
        do {
            token_image[i++] = c;
            c = getchar();
        } while (isdigit(c));
        token_image[i] = '\0';
        return t_literal;
    } else switch (c) {
        case ':':
            if ((c = getchar()) != '=') {
                cout << "error\n"; //changed to cout
                exit(1);
            } else {
                c = getchar();
                return t_gets;
            }
            break;
        case '(': c = getchar(); return t_lparen;
        case ')': c = getchar(); return t_rparen;
        //added conditionals
        case '=': c = getchar(); return t_equal;
        case '<>': c = getchar(); return t_notequal;
        case '<': c = getchar(); return t_less;
        case '>': c = getchar(); return t_greater;
        case '<=': c = getchar(); return t_lessequal;
        case '>=': c = getchar(); return t_greaterequal;
        case '+': c = getchar(); return t_add;
        case '-': c = getchar(); return t_sub;
        case '*': c = getchar(); return t_mul;
        case '/': c = getchar(); return t_div;
        default:
            cout << "error\n"; //changed to cout
            exit(1);
    }
}
