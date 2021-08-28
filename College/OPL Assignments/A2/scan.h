/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2020.
*/

//added tokens to support extended calculator language
typedef enum {t_read, t_write, t_id, t_literal, t_gets,
              t_equal, t_notequal, t_less, t_greater, t_lessequal, t_greaterequal,
              t_if, t_while, t_end,
              t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof} token;

#define MAX_TOKEN_LEN 128
extern char token_image[MAX_TOKEN_LEN];

extern token scan();
