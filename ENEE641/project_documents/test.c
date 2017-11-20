#include "stdio.h"
#include "stdlib.h"
#include "string.h"

 typedef struct nodel{
          int vertex;
         struct nodel* next;
  }nl;

enum color {White,Gray,Black};
typedef struct node{
	struct nl *next;
	int vertex;
	int pi;
	int visited;
//	char* color;
	enum color cl;
	int disc;
	int fin;
	int pred;
}node;


node *Adj;
/*int *visited;//array to keep track of which node has been visited
int *disc;
int *low;
int *parent;
int *AP;*/


//void insert(int vi,int vj){ //vi = u & vj = v
//
//node *p,*q;
////printf("%d %d",vi,vj);
//
//q = (node*)malloc(sizeof(node));
//q->vertex = vj;
//q->next = NULL;
//q->cl = White; 
//q->pred = 0;
//q->visited = 0;
//
//	if(Adj[vi] == NULL){
// 		Adj[vi] = q;
//	}
//	else{
//
//		p = Adj[vi];
//
//		while(p->next != NULL)
//			p = p->next;
//		p->next = q;
//
//		}
//}
void insrt(int vi, int vj){

nl *p,*q;
q=(nl*)malloc(sizeof(nl));
q->vertex = vj;
q->next = NULL;

	if(Adj[vi].next == NULL){
		Adj[vi].next = q;
	}
	else{
		p = Adj[vi].next;
		while(p->next != NULL)
			p = p->next;
		p->next = q;
	}
}

void DFS_test(int v){
int i;
for(i=0;i<=v;i++){




}
}

void print_graph(int a , int b){
	node* p;
	int i;
//	p = Adj[a];
	for(i = a; i<=b;i++){
		p = Adj[i];
		while(p != NULL){
			printf("%d->",p->vertex);
			p = p->next;
		}
	printf("\n"); 
	}	
		
}

int minimum(int a,int b){

	return 	(a>b?a:b);

}
void DFS(int i){
	node *p;
//	printf("%d->",i);
	p = Adj[i];

	p->visited = 1;
	while(p!=NULL){
		i = p->vertex;
		if(!(Adj[i]->visited)){
			printf("visited: %d",Adj[i]->visited);
			DFS(i);
		}
		p = p->next;
	}

}

int main(int argc, char *argv[])
{
	FILE *ifp;

	if (argc < 2)
	{
		printf("too few arguments !");
		return 0;
	}

	// read input from file
	ifp = fopen(argv[1], "r");

	int num_v = 0;
	char l[256];
	char *token;
	int i = 0;
	int current_u = 0;
	int current_v = 0;
	while (fgets(l, sizeof l, ifp) != NULL){ printf("%s\n",l); num_v++;}
	rewind(ifp);

	Adj = (node*)malloc((num_v + 1)*sizeof(node));
//	visited = (int*)malloc((num_v+1)*sizeof(int));
//	disc = (int*)malloc((num_v+1)*sizeof(int));
//	low = (int*)malloc((num_v+1)*sizeof(int));
//	parent = (int*)malloc((num_v+1)*sizeof(int));
//	AP = (int*)malloc((num_v+1)*sizeof(int));
	for(i=0;i<num_v;i++){
		Adj[i] = NULL;
//		visited[i] = 0;
//		disc[i] = 0;
//		low[i] = 0;
//		parent[i] = 0;
//		AP[i] = 0;
	}
	i = 0;

	
	while(fgets(l, sizeof l, ifp) != NULL){
		token = strtok(l," ");
		while(token != NULL){
	//		printf("%s",token);
			if(i==0){
		//		current_u = *token;
				current_u = atoi(token);
			}
			current_v = atoi(token);
			insert(current_u,current_v);
	//		test(current_u,current_v);
			token = strtok(NULL," ");
			i++;
			
		}
		i = 0;

	}
	rewind(ifp);
	
print_graph(1,6);
printf(">>>>>>>>>>>>>>>>>>DFS_tree>>>>>>>>>>>>>>>>>>>>>>\n");
DFS(6);

//APu(7);

i = 0;
//while(i < num_v){
//
//		printf("APP: %d",AP[i]);
//	i++;
//}
  // TODO: please comment the following line
  printf("Total number of vertices = %d\n", num_v);

	char line[1024];
	while (fgets(line, sizeof line, ifp) != NULL)
	{
    int src_vertex, dst_vertex;
		char * pch;
		pch = strtok(line, " \n\r");
		sscanf(pch, "%d", &src_vertex);
		pch = strtok(NULL, " \n\r");

		while (pch != NULL)
		{
			// there is an edge from src_vertex to dst_vertex
			sscanf(pch, "%d", &dst_vertex);
      // TODO : please comment the following line
      printf("Edge exists between (%d,%d)\n", src_vertex, dst_vertex);
			pch = strtok(NULL, " \n\r");
		}

	}

	fclose(ifp);
}
