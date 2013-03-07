#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED
typedef char *buffer;
typdef int buffersize;

typedef enum
{
    TK_MINUS ,TK_NE ,TK_RECORDID ,TK_COMMENT ,TK_AND ,TK_OP ,TK_CL ,TK_MUL ,TK_DOT ,TK_DIV ,TK_COLON ,TK_SEM ,
    TK_OR ,TK_SQL ,TK_NUM ,TK_RNUM ,TK_FIELDID ,TK_ID ,TK_SQR ,TK_FUNID ,TK_MAIN ,TK_NOT ,TK_PLUS ,TK_LT ,
    TK_ASSIGNOP ,TK_LE ,TK_EQ ,TK_GT ,TK_LE ,TK_CALL ,TK_ELSE ,TK_END ,TK_ENDIF ,TK_ENDRECORD ,TK_ENDWHILE ,
    TK_GLOBAL ,TK_IF ,TK_INPUT ,TK_INT ,TK_LIST ,TK_OUTPUT ,TK_PARAMETER ,TK_PARAMETERS ,TK_READ ,TK_REAL ,
    TK_RECORD ,TK_RETURN ,TK_THEN ,TK_TYPE ,TK_WHILE ,TK_WITH ,TK_WRITE
} symbol;

typedef enum {FALSE,TRUE} bool;

typedef struct
{
    symbol s;
    char lexeme[100];
} token;
typedef token* ptoken;

typedef struct
{
    bool present;
    symbol s;
    char keyword[100];
} keyword;

typedef keyword* keywordTable;


#endif // LEXERDEF_H_INCLUDED
