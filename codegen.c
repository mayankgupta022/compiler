

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

#include"lexerDef.h"
#include"lexer.h"
#include"parserDef.h"
#include"parser.h"
#include"symbolTable.h"
#include"semantic.h"
//#include"codegen.h"


void evaluate(parseTree A, FILE *fp)
{

	//printf("%s\n", A->t->lexeme);
	int c1=0,c2=0,i;
	char temp[30]="";
	for(i=0;A->next[i]!=NULL;i++)
		c1++;
	//printf("c=%d\n",c1);
	if(c1 == 2)
	{
		evaluate(A->next[0],fp);
		fprintf(fp,"push AX\n");
		//push();
		evaluate(A->next[1],fp);
		fprintf(fp,"pop DX\n");
		if(A->next[1]->t->s == TK_PLUS)
			fprintf(fp,"add AX,DX\n");
		if(A->next[1]->t->s == TK_MINUS)
			fprintf(fp,"sub AX,DX\n");
		if(A->next[1]->t->s == TK_MUL)
			fprintf(fp,"imul DX\n");
		if(A->next[1]->t->s == TK_DIV)
			fprintf(fp,"idiv DX\n");
		//calculate();
	}
	else if(c1==1)
	{
		evaluate(A->next[0],fp);
		fprintf( fp,"pop DX\n");
		if(A->t->s == TK_PLUS)
			fprintf(fp,"add AX,DX\n");
		if(A->t->s == TK_MINUS)
			fprintf(fp,"sub AX,DX\n");
		if(A->t->s == TK_MUL)
			fprintf(fp,"imul DX\n");
		if(A->t->s == TK_DIV)
			fprintf(fp,"idiv DX\n");
		//calculate();
	}
	else if(c1==0)
	{
		char temp[30];
		strcpy(temp,A->t->lexeme);
		//printf("%s\n",toStr(A->parent->t->s));
		if(A->parent->next[1] && A->parent->t->s == all)
		{
			strcat(temp,"_");
			strcat(temp,A->parent->next[1]->t->lexeme);
		}
		//fprintf(fp, "A->t->s=%s\n",toStr(A->t->s) );
		fprintf(fp,"mov AX,%s\n",temp);
	}
}




void ifelse(variable GT[], funTable FT[], recTable RT[], parseTree A, FILE * fp)
{
	if(A->t->s==TK_AND )
	{
		ifelse(GT,FT,RT,A->next[0],fp);
		fprintf(fp, "push AX\n");
		ifelse(GT,FT,RT,A->next[1],fp);
		fprintf(fp, "pop DX\n");
		fprintf(fp,"and AX,DX\n");
	}
	else if(A->t->s==TK_OR )
	{
		ifelse(GT,FT,RT,A->next[0],fp);
		fprintf(fp, "push AX\n");
		ifelse(GT,FT,RT,A->next[1],fp);
		fprintf(fp, "pop DX\n");
		fprintf(fp,"or AX,DX\n");
	}
	else if(A->t->s==TK_GT)
	{
		ifelse(GT,FT,RT,A->next[0],fp);
		fprintf(fp, "push AX\n");
		ifelse(GT,FT,RT,A->next[1],fp);
		fprintf(fp, "pop DX\n");
		fprintf(fp, "cmp AX,DX\n");
		int r =  rand()%10000;
		fprintf(fp, "jle true_%d_%d\n",A->lineno,r);
		fprintf(fp, "jmp false_%d_%d\n",A->lineno,r);
		fprintf(fp, "true_%d_%d:\nmov AX, 0\n",A->lineno,r );
		fprintf(fp, "false_%d_%d:\nmov AX, 1\n",A->lineno,r );


	}
	else if(A->t->s==TK_GE)
	{
		ifelse(GT,FT,RT,A->next[0],fp);
		fprintf(fp, "push AX\n");
		ifelse(GT,FT,RT,A->next[1],fp);
		fprintf(fp, "pop DX\n");
		fprintf(fp, "cmp AX,DX\n");
		int r =  rand()%10000;
		fprintf(fp, "jl true_%d_%d\n",A->lineno,r);
		fprintf(fp, "jmp false_%d_%d\n",A->lineno,r);
		fprintf(fp, "true_%d_%d:\nmov AX, 0\n",A->lineno,r );
		fprintf(fp, "false_%d_%d:\nmov AX, 1\n",A->lineno,r );
	}
	else if(A->t->s==TK_EQ)
	{
		ifelse(GT,FT,RT,A->next[0],fp);
		fprintf(fp, "push AX\n");
		ifelse(GT,FT,RT,A->next[1],fp);
		fprintf(fp, "pop DX\n");
		fprintf(fp, "cmp AX,DX\n");
		int r =  rand()%10000;
		fprintf(fp, "jne true_%d_%d\n",A->lineno,r);
		fprintf(fp, "jmp false_%d_%d\n",A->lineno,r);
		fprintf(fp, "true_%d_%d:\nmov AX, 0\n",A->lineno,r );
		fprintf(fp, "false_%d_%d:\nmov AX, 1\n",A->lineno,r );
	}
	else if(A->t->s==TK_LE)
	{
		ifelse(GT,FT,RT,A->next[0],fp);
		fprintf(fp, "push AX\n");
		ifelse(GT,FT,RT,A->next[1],fp);
		fprintf(fp, "pop DX\n");
		fprintf(fp, "cmp AX,DX\n");
		int r =  rand()%10000;
		fprintf(fp, "jg true_%d_%d\n",A->lineno,r);
		fprintf(fp, "jmp false_%d_%d\n",A->lineno,r);
		fprintf(fp, "true_%d_%d:\nmov AX, 0\n",A->lineno,r );
		fprintf(fp, "false_%d_%d:\nmov AX, 1\n",A->lineno,r );
	}
	else if(A->t->s==TK_EQ)
	{
		ifelse(GT,FT,RT,A->next[0],fp);
		fprintf(fp, "push AX\n");
		ifelse(GT,FT,RT,A->next[1],fp);
		fprintf(fp, "pop DX\n");
		fprintf(fp, "cmp AX,DX\n");
		int r =  rand()%10000;
		fprintf(fp, "jge true_%d_%d\n",A->lineno,r);
		fprintf(fp, "jmp false_%d_%d\n",A->lineno,r);
		fprintf(fp, "true_%d_%d:\nmov AX, 0\n",A->lineno,r );
		fprintf(fp, "false_%d_%d:\nmov AX, 1\n",A->lineno,r );

	}
	else if(A->t->s == TK_ID || A->t->s == TK_NUM)
	{
		fprintf(fp, "mov AX,%s\n",A->t->lexeme );
	}
}







void generateCode(variable GT[], funTable FT[], recTable RT[],parseTree A, FILE *fp)
{

	parseTree temp;
	int j;
	char idname[30]="",fieldname[30]="",name[60]="";
	int f=0;
	
	if(A->t->s == assignmentstmt)
	{
		if(A->next[0]->t->s == TK_ID)
		{
			strcpy(idname,A->next[0]->t->lexeme);
			strcat(name,idname);
			strcat(name,fieldname);
		}
		else
		{
			strcpy(idname,A->next[0]->next[0]->t->lexeme);
			strcpy(fieldname,A->next[0]->next[1]->t->lexeme);
			strcat(name,idname);
			strcat(name,"_");
			strcat(name,fieldname);

		}
		
		temp = A->next[2];
		evaluate(temp,fp);
		fprintf(fp, "mov %s, AX\n",name );
	}

	else if(A->t->s == conditionalstmt)
	{
		ifelse(GT,FT,RT,A->next[1],fp);
		fprintf(fp, "cmp AX,1\n");
		fprintf(fp, "jne else%d\n", A->lineno);

		fprintf(fp, "jmp then%d\n", A->lineno);
		fprintf(fp, "then%d:\n",A->lineno );
		//fprintf(fp,"%s\n",toStr(A->next[3]->t->s));
		generateCode(GT,FT,RT,A->next[3],fp);
		fprintf(fp, "else%d:\n", A->lineno);
		generateCode(GT,FT,RT,A->next[4],fp);

	}
	// else if(A->t->s == iterativestmt)
	// {
	// 	fprintf(fp, "label_%d:\n",A->lineo );
	// 	ifelse(GT,FT,RT,A->next[1],fp);
	// 	fprintf(fp, "cmp AX,1\n");
	// 	fprintf(fp, "jne out_%d\n",A->lineno );
	// 	fprintf(fp, "label_%d\n",A->lineno);
	// }
	else
	{
		for(j=0;A->next[j]!=NULL;j++)
		{
			temp = A->next[j];
			generateCode(GT,FT,RT,temp,fp);
		}
	}

}		