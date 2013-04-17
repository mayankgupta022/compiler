/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
driver.c
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<malloc.h>
#include "lexerDef.h"
#include "lexer.h"
#include "parserDef.h"
#include "parser.h"
#include "symbolTable.h"

int main(int argc, char *argv[])
{
    FILE *g=fopen("grammar.txt", "r");
    FILE *p=fopen("parsetable.csv", "w");
    FILE *tree=fopen("tree.txt", "w");
    FILE *ast=fopen("ast.txt", "w");
    if(g==NULL)
    {
        printf("Grammar file not found\n");
        return 0;
    }    
    if(p==NULL)
    {
        printf("parsetable file can not be opened\n");
        return 0;
    }    
    if(tree==NULL)
    {
        printf("tree file can not be opened\n");
        return 0;
    }
    int opt,i,fp,Gno, totalAllocatedMemory=0;
    fp = open(argv[1],O_RDONLY);
    if(fp==-1)
    {
        printf("input file not found\n");
        return 0;
    }
    bool error = 0;
    Table T[60][60];
    grammar G[100];
    sets S[60];
    keyword kw[48];
    keyword kn[200];
    parseTree P,A;
    for(i=0; i<48; i++)
        kw[i].present=FALSE;
    keywordTable kt = kw;
    initkt(kt);
    for(i=0; i<200; i++)
        kn[i].present=FALSE;
    keywordTable nt = kn;
    initNt(nt);
    Gno=createGrammar(g,G,nt);
    initSets(S,G,Gno);
//    createSets(s,S,nt);
    initTable(T);
    createParseTable(G,T,S,Gno);
    printTable(p, T);
    variable GT[100]; //max 100 globals possible 
    funTable FT[100];
    recTable RT[100];
    tokenList list;
    do
    {
        printf("\n 1 : Print the token list.\n 2 : Verify the syntactic correctness\n 3 : Print abstract syntax tree\n 4: Print Symbol Table\n 5: Do Type Checking\n\nSelect option->");
        scanf("%d", &opt);
        switch(opt)
        {
            case 1:
                list=createTokenList(fp, kt);
                printTokenList(kt, list);
                break;
            case 2:
                P = parseInputSourceCode(fp, T, kt, G, &error, S);
                if(!error)
                {
                    printParseTree(P, tree);
                    if(P!=NULL)
                        printf("\nParse Tree generated and printed in file tree.txt\n");
                }
                break;
            case 3:
                P = parseInputSourceCode(fp, T, kt, G, &error, S);
                if(error)
                    printf("error\n");
                //parseTree A;
                A = createAbstractSyntaxTree(P);
                if(!error)
                {
                    printAST(A, ast, &totalAllocatedMemory);
                    if(A!=NULL)
                        printf("\nAST generated and printed in file ast.txt\nSize of AST is %d\n",totalAllocatedMemory);
                }
                break;
            case 4:
                P = parseInputSourceCode(fp, T, kt, G, &error, S);
                if(error)
                    printf("error\n");
                
                A = createAbstractSyntaxTree(P);
                if(!error)
                {
                    printAST(A, ast, &totalAllocatedMemory);
                    if(A!=NULL)
                        printf("\nAST generated and printed in file ast.txt\nSize of AST is %d\n",totalAllocatedMemory);
                }

                initSymbolTable(GT,FT,RT);

                createGlobalTable(GT,A);
                createRecordTable(RT,A);
                createSymbolTable( GT, FT, RT, A);
                printGT(GT,RT);
                //printRT(RT);
                printFT(FT,RT);

                break;
            case 5:
                P = parseInputSourceCode(fp, T, kt, G, &error, S);
                if(error)
                    printf("error\n");
                
                A = createAbstractSyntaxTree(P);
                if(!error)
                {
                    printAST(A, ast, &totalAllocatedMemory);
                    if(A!=NULL)
                        printf("\nAST generated and printed in file ast.txt\nSize of AST is %d\n",totalAllocatedMemory);
                }
                initSymbolTable(GT,FT,RT);

                createGlobalTable(GT,A);
                createRecordTable(RT,A);
                createSymbolTable( GT, FT, RT, A);
                printGT(GT,RT);
                //printRT(RT);
                printFT(FT,RT);
                char funname[50];
                strcpy(funname," ");
                typeParse(A,GT, FT,RT,funname);
                break;
            default:
                printf("\nPlease select a valid option\n");
        }
    }while(opt<1 || opt>5);
    fclose(g);
    fclose(p);
    fclose(tree);
    fclose(ast);
    return 0;
}
