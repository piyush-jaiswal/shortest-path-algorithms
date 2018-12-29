#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "graph.c"
#include "stacks.c"

//int n=49109;
//int n=8;
int n=5;
//int n=1070376;

int tcc=0;
int of;
void DFSUtil(int k, Graph *graph, bool *visited)
{
    //printf("\nhello");
    int u;
    AdjNode *temp;
    Stack *s = createStack();
    push(s, k);

    while (!empty(s))
    {
        u = top(s); //printf("%d ",u);
        pop(s);

        if (!visited[u])
        {
            visited[u] = true;
            temp = graph -> adjList[u];

            while (temp != NULL)
            {
                if (!visited[temp -> v])
                    push(s, temp -> v);
                temp = temp -> next;
            }
        }
    }
}

Graph* Transpose(Graph *graph, int n)
{
    //printf("\n@");
    Graph *gn = createGraph(n);
    int v;
    AdjNode *temp;
    for(v=0;v<n;v++)
    {
        temp=graph->adjList[v];
        while(temp!=NULL)
        {
            addEdge(gn,temp->v,v,temp->w);
            temp=temp->next;
        }
    }

    return gn;
}

void OrderedFill(int v, bool *visited, Stack *st, Graph *graph)
{
    printf("\n*");
    visited[v]=true;
    AdjNode *temp;
    temp=graph->adjList[v];
    while(temp!=NULL)
    {
        if(!visited[temp->v])
            OrderedFill(temp->v,visited,st,graph);

        temp=temp->next;
    }

    push(st,v);
}

void StrongCC(Graph *graph, int n)
{
        int v;
        Stack *st = createStack();
        bool *visited = (bool *) malloc(n*sizeof(bool));

        for(v=0;v<n;v++)
        {
                visited[v]=false;
        }
        printf("\nStage 1");
        for(v=0;v<n;v++)
        {
            if(!visited[v])
                OrderedFill(v,visited,st,graph);
        }
        printf("\nStage 2");
        Graph *gr = Transpose(graph, n);
        //printf("\nStage 3");

        //Now reset visited for second DFS

        for(v=0;v<n;v++)
        {
            visited[v]=false;
        }
        int u;
        while(!empty(st))
        {
            u=top(st);
            pop(st);
            printf("\n%d",u);
            if(!visited[u])
            {
                tcc++;
                DFSUtil(u,gr,visited);
                printf("\n%d",tcc);
            }
        }

        //printf("\nTotal connected component(s) = %d.",tcc);
}

int main()
{
        int i,m;m=121024;
        FILE *fl;
        long fl_size;
        char *buffer;
        size_t res;


        fl=fopen("Trial4.txt","r+");
        if(fl==NULL){
                fprintf(stderr, "File error\n");
        exit(1);
        }

        fseek(fl,0,SEEK_END);
        fl_size=ftell(fl);
        rewind(fl);


    buffer = (char*) malloc(sizeof(char )*fl_size);
    if(buffer==NULL){
            fputs("Memory error",stderr);
    exit(2);
    }

    res=fread(buffer,1,fl_size,fl);
    if(res!=fl_size){
            fputs("Reading error",stderr);
    exit(3);
    }


    char *tok;AdjNode* temp;
    Graph *g = createGraph(n);
    long tempo,tempo1,tempo2;

    tok=strtok(buffer," a  \t\n");
    while(tok!=NULL)
    {
        tempo=strtol(tok,NULL,10);
        tok=strtok(NULL," a  \t\n");
        tempo1=strtol(tok,NULL,10);
        tok=strtok(NULL," a  \t\n");
        tempo2=strtol(tok,NULL,10);
        addEdge(g,tempo-1,tempo1-1,tempo2);
        tok=strtok(NULL," a  \t\n");
    }

    g=Transpose(g,n);

  for (i = 0; i < g -> V; i++)
    {
         printf("%d -> ", i);
         temp = g -> adjList[i];
         while (temp != NULL)
         {
             printf("%ld(%ld) ", temp -> v, temp -> w);
             temp = temp -> next;
         }
         printf("\n");
     }

     //printf("\nHere");
     //StrongCC(g,n);

    fclose(fl);
    free(buffer);
    return 0;
}
