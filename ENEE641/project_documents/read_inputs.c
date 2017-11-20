#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#define max 1000

int *bc;
int *vc;
int **e_count;
typedef struct Edge{
	int u,v;
} edge;

static edge stack[max + 1];
int p;
//edge *ec;


void push(edge v){
	stack[p++] = v;
}

edge pop(){return stack[--p];}

edge back(){
	edge temp;
	temp = stack[--p]; 
	p++; 
	return temp;
}

void stackinit(){p=0;}

int stackempty(){return !p;}

int V;

void ed(int u,int v){
	edge *temp = (edge *)malloc(sizeof(edge));
	temp->u = u;
	temp->v = v;
	push(*temp);
}
typedef struct node{
	struct node *next;
	int vertex;
}node;

node **Adj;
// int *visited;//array to keep track of which node has been visited
// int *disc;
// int *low;
// int *parent;
// int *AP;

void insert(int vi,int vj){ //vi = u & vj = v

node *p,*q;
//printf("%d %d",vi,vj);

q = (node*)malloc(sizeof(node));
q->vertex = vj;
q->next = NULL;

	if(Adj[vi] == NULL){
 		Adj[vi] = q;
	}
	else{

		p = Adj[vi];

		while(p->next != NULL)
			p = p->next;
		p->next = q;

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

	return 	(a>b?b:a);

}
void BRIDGEUTIL(int u,bool visited[],int disc[],int low[],int parent[]){

	static int time = 0;
	visited[u] = true;
	disc[u] = low[u] = ++time;
	int v;
	node *p;
	p = Adj[u];
	p = p->next;
	while(p != NULL){
		v = p->vertex;
		if(!visited[v]){
			v = p->vertex;
			parent[v] = u;
			BRIDGEUTIL(v,visited,disc,low,parent);
			low[u] = minimum(low[u],low[v]);

			if(low[v] > disc[u]){
				printf("%d %d\n",u,v);
			}
		}
		else if(v!= parent[u]){
			low[u] = minimum(low[u],disc[v]);
		}
		p = p->next;
	}
}

void BRIDGE(){
	bool *vis = (bool*)malloc((V+1)*sizeof(bool));
	int *di = (int*)malloc((V+1)*sizeof(int));
	int *l = (int*)malloc((V+1)*sizeof(int));
	int *p = (int*)malloc((V+1)*sizeof(int));
	int i;


	for(i=1;i<=V;i++){
		p[i] = 0;
		vis[i] = 0;
	}

	for(i=1;i<=V;i++){
		if(vis[i] == false){
			BRIDGEUTIL(i,vis,di,l,p);
		}
	}
}
void APUTIL(int u,bool visited[],int disc[],int low[],int parent[],bool ap[]){
	static int time = 0;
	int children = 0;
	visited[u] = true;
	node *p;
	int v;
	disc[u] = low[u] = ++time;
	p = Adj[u];
	p = p->next;
	while(p != NULL){
		v = p->vertex;
		if(!visited[v]){
			children++;
			parent[v] = u;
			APUTIL(v,visited,disc,low,parent,ap);
			low[u] = minimum(low[u],low[v]);
			if((parent[u] == 0) && (children > 1)){
				ap[u] = true;
			}
			if((parent[u] != 0 ) && (low[v] >= disc[u])){
				ap[u] = true;
			}
		}
		else if(v!= parent[u]){
			low[u] = minimum(low[u],disc[v]);
		}
		p = p->next;
	}

}

void AP(){
	bool *vis = (bool*)malloc((V+1)*sizeof(bool));
	int *di = (int*)malloc((V+1)*sizeof(int));
	int *l = (int*)malloc((V+1)*sizeof(int));
	int *p = (int*)malloc((V+1)*sizeof(int));
	bool *ap = (bool*)malloc((V+1)*sizeof(bool));
	int i;
	for(i=1;i<=V;i++){
		p[i] = 0;
		vis[i] = 0;
		ap[i] = 0;
	}
	for(i=1;i<=V;i++){
		if(vis[i] == false){
			APUTIL(i,vis,di,l,p,ap);
		}
	}

	for(i=0;i<=V;i++){
		if(ap[i] == true){
			printf("%d",i);
		}
	}

}


bool BCUTIL(int u,int disc[],int low[],int parent[]){

	static int time = 0;
	int i;
	int v;
	int children = 0;
	edge temp;
	int x;
	disc[u] = low[u] = ++time;
	node *p;
	p = Adj[u];
	p = p->next;
	vc[u]++;
	while(p != NULL){
		v = p->vertex;
		vc[v]++;
		e_count[u][v]++;
		if(disc[v] == 0){
			children++;
			parent[v] = u;
			ed(u,v);

			BCUTIL(v,disc,low,parent);

			low[u] = minimum(low[u],low[v]);

			if((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u])){
				temp = back();
				for(x = 0;x<=V;x++){
					bc[x] = 0;
				}
				while(temp.u !=u || temp.v != v){
					// printf("asdsdf%d  %d ",temp.u,temp.v);

					pop();
					bc[temp.u] = 1;
					bc[temp.v] = 1;
					temp = back();
				}

				// printf("asd%d  %d\n",temp.u,temp.v);
				bc[temp.u] = 1;
				bc[temp.v] = 1;
				pop();
				for(x=0;x<=V;x++){
					if(bc[x] != 0){
						printf("%d ",x);
					}
				}
				printf("\n");
			}
		}

		else if(v != parent[u] && disc[v] < low[u]){
			low[u] = minimum(low[u],disc[v]);
			ed(u,v);
		}
		p = p->next;
	}
}


vois BC(){

	// bool *vis = (bool*)malloc((V+1)*sizeof(bool));

	int *di = (int*)malloc((V+1)*sizeof(int));
	int *l = (int*)malloc((V+1)*sizeof(int));
	int *p = (int*)malloc((V+1)*sizeof(int));
	stackinit();
	int i;
	int x;
	// int u_temp;

	for(i=1;i<=V;i++){
		di[i] = 0;
		p[i] = 0;
		l[i] = 0;
	}
	edge temp;
	for(int i = 1;i<=V;i++){
		if(di[i] == 0){
			BCUTIL(i,di,l,p);
		}
		// edge temp;
		// int j = 0;
	for(x=0;x<=V;x++){
		bc[x] = 0;
	}
		while(!stackempty()){
			// j = 1;
			// printf("asdasdasd");
			temp = pop();
			bc[temp.u] = 1;
			bc[temp.v] = 1;
			// printf("%d  %d",temp.u,temp.v);
			// pop();
		}
		for(x=0;x<=V;x++){
					if(bc[x] != 0){
						printf("%d ",x);
					}
				}
			// printf("\n");
	}
	printf("\n");
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
	int j =0;
	int current_u = 0;
	int current_v = 0;
	while (fgets(l, sizeof l, ifp) != NULL){ printf("%s\n",l); num_v++;}
	rewind(ifp);
	Adj = (node**)malloc((num_v + 1)*sizeof(node *));
	bc = (int*)malloc((num_v+1)*sizeof(int));
	// ec = (edge*)malloc((num_v+1)*sizeof(edge));
	vc = (int*)malloc((num_v+1)*sizeof(int));
	e_count = (int **)malloc((num_v+1)*sizeof(int *));

	for(i = 0; i<=num_v;i++){
		e_count[i] = (int *)malloc((num_v+1)*sizeof(int));
	}

	// visited = (int*)malloc((num_v+1)*sizeof(int));
	// disc = (int*)malloc((num_v+1)*sizeof(int));
	// low = (int*)malloc((num_v+1)*sizeof(int));
	// parent = (int*)malloc((num_v+1)*sizeof(int));
	// AP = (int*)malloc((num_v+1)*sizeof(int));
	for(i=0;i<=num_v;i++){
		Adj[i] = NULL;
		bc[i]  = 0;
		vc[i] = 0;
		// visited[i] = 0;
		// disc[i] = 0;
		// low[i] = 0;
		// parent[i] = 0;
		// AP[i] = 0;
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


	
print_graph(1,7);
// printf(">>>>>>>>>>>>>>>>>>DFS_tree>>>>>>>>>>>>>>>>>>>>>>\n");
// DFS(6);

// APu(7);

i = 0;
V = num_v;
// while(i < num_v){

// 		printf("APP: %d",AP[i]);
// 	i++;
// }
// AP();
BC();
   	// BRIDGE();
int count = 0;


  // TODO: please comment the following line
 

	for (i = 1; i <=num_v; i++) {
		for (j = 1; j <= num_v; j++) {
			printf("%d ", e_count[i][j]);
		}
		printf("\n");
	}
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
      printf("Cost on edge: %d",e_count[src_vertex][dst_vertex]+e_count[dst_vertex][src_vertex]);
			pch = strtok(NULL, " \n\r");
			count++;
		}

	}
	for(i=1;i<=V;i++){
		printf("vertex:%d cost: %d",i,vc[i]);
		printf("\n");
	}


	fclose(ifp);
}
