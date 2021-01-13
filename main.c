#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int Num=10;

char line[2550],OLine[2550];
int stack[2550]={0},pr[7][7],top=0,lineLen=0;
char CharList[1001]={' ','+','*','i','(',')','#','N','F','T','E'};


char intTochar(int i)
{
    return CharList[i];
}

int Toint(char c)
{
    for (int i=0;i<=Num;i++)
    {
        if (CharList[i]==c)
        {
            return i;
        }
    }
    return -1;
}


void push(int newStackNum)
{
    stack[top]=newStackNum;
    top++;
}



void setPr()
{
    pr[1][1]=1;pr[1][2]=-1;pr[1][3]=-1;
    pr[1][4]=-1;pr[1][5]=1;pr[1][6]=1;
    pr[2][1]=1;pr[2][2]=1;pr[2][3]=-1;
    pr[2][4]=-1;pr[2][5]=1;pr[2][6]=1;
    pr[3][1]=1;pr[3][2]=1;pr[3][3]=2;
    pr[3][4]=2;pr[3][5]=1;pr[3][6]=1;
    pr[4][1]=-1;pr[4][2]=-1;pr[4][3]=-1;
    pr[4][4]=-1;pr[4][5]=0;pr[4][6]=2;
    pr[5][1]=1;pr[5][2]=1;pr[5][3]=2;
    pr[5][4]=2;pr[5][5]=1;pr[5][6]=1;
    pr[6][1]=-1;pr[6][2]=-1;pr[6][3]=-1;
    pr[6][4]=-1;pr[6][5]=2;pr[6][6]=2;
}

int cmp(int a,int b)
{
    if (a>=0&&a<=6&&b>=0&&b<=6)
        return pr[a][b];
    else return 2;
}

int topTerminal()
{
    for (int i=top-1;i>=0;i--)
    {
        if (stack[i]<=6&&stack[i]>=0)
            return stack[i];
    }
}

int specification()
{
    if (stack[top-1]==3)
    {
        stack[top-1]=7;
        return 1;
    }
    if (stack[top-1]==7&&stack[top-2]==1&&stack[top-3]==7)
    {
        top=top-2;
        stack[top-1]=7;
        return 1;
    }
    if (stack[top-1]==7&&stack[top-2]==2&&stack[top-3]==7)
    {
        top=top-2;
        stack[top-1]=7;
        return 1;
    }
    if (stack[top-1]==5&&stack[top-2]==7&&stack[top-3]==4)
    {
        top=top-2;
        stack[top-1]=7;
        return 1;
    }
    return 2;
}

int main(int argc,char* argv[])
{
    FILE *fp = NULL;
    fp = fopen(argv[1], "r");
    fgets(OLine,2000,(FILE *)fp);
    lineLen=1;
    line[0]='#';
    for (int i=0;i<strlen(OLine);i++)
    {
        if (OLine[i]!='+'&&OLine[i]!='*'&&OLine[i]!='i'&&OLine[i]!='('&&
        OLine[i]!=')'&&OLine[i]!='z')
        {
            continue;
        }
        line[lineLen]=OLine[i];
        lineLen++;
    }
    line[0]='#';
    line[lineLen]='#';
    line[lineLen+1]='\n';
    setPr();
    push(Toint(line[0]));
    for (int i=1;i<=lineLen;)
    {
        if (top==2&&stack[1]==7&&line[i]=='#') break;
        if (cmp(topTerminal(),Toint(line[i]))==2)
        {
            printf("E\n");
            return 0;
        }
        if (cmp(topTerminal(),Toint(line[i]))==1)
        {
            int Status=specification();
            if (Status==1)
            {
                printf("R\n");
            }
            else
            {
                if (Status==2)
                {
                    printf("RE\n");
                    return 0;
                }
            }

        }
        else
        {
            push(Toint(line[i]));
            if (i==lineLen) break;
            printf("I%c\n",line[i]);
            i++;
        }
    }

    fclose(fp);
    return 0;
}
