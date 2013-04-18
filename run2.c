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

int main(int argc, char *argv[])
{
    FILE *s=fopen("set.txt", "r");
    FILE *g=fopen("grammar.txt", "r");
    FILE *fp=fopen("parsetable.csv", "w");
    FILE *tree=fopen("tree.txt", "w");
    int i,Gno, Sno,fd;
    bool error = 0;
    Table T[60][60];
    grammar G[100];
    sets S[60];

    keyword kw[48];
    for(i=0; i<48; i++)
        kw[i].present=FALSE;
    keywordTable kt = kw;
    initkt(kt);
    keyword kn[2000];
    for(i=0; i<2000; i++)
        kn[i].present=FALSE;
    keywordTable nt = kn;
    initNt(nt);
    Gno = createGrammar(g,G,nt);
    initSets(S,G,Gno);
    printFirst(S);
    //createSets(s,S,nt);
/*    for(i=0;i<Sno;i++)
    {
    	printf("\n%d %d %s %d\n", S[i].firstno,S[i].followno, toStr(S[i].nt), S[i].eps);
    	for(j=0;j<S[i].firstno;j++)
    		printf("%s ",toStr(S[i].first[j] ));
    	printf("\n");
    	for(j=0;j<S[i].followno;j++)
    		printf("%s ",toStr(S[i].follow[j] ));
    }
    
  initTable(T);
    createParseTable(G,T,S,Gno);
    printTable(fp, T);
    fd = open("input.txt",O_RDONLY);
     if(fd==-1)
    {
        printf("input file not found");
        return 0;
    }
    //tokenList list=createTokenList(fd, kt);
    parseTree P = parseInputSourceCode(fd, T, kt, G, &error);
    printParseTree(P, tree);
	fclose(fp);
    */
    return 0;
}