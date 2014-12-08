#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node_t node_t, *heap_t;
typedef struct edge_t edge_t;
struct edge_t {
	node_t *nd;	/* target of this edge */
	edge_t *sibling;/* for singly linked list */
	int len;	/* edge cost */
};
struct node_t {
	edge_t *edge;	/* singly linked list of edges */
	node_t *via;	/* where previous node is in shortest path */
	double dist;	/* distance from origining node */
	char name[8];	/* the, er, name */
	int heap_idx;	/* link to heap position for updating distance */
};



/* --- edge management --- */
#ifdef BIG_EXAMPLE
#	define BLOCK_SIZE (1024 * 32 - 1)
#else
#	define BLOCK_SIZE 32
#endif
edge_t *edge_root = 0, *e_next = 0;

/* Don't mind the memory management stuff, they are besides the point.
   Pretend e_next = malloc(sizeof(edge_t)) */
void add_edge(node_t *a, node_t *b, double d)
{
	if (e_next == edge_root) {
		edge_root = malloc(sizeof(edge_t) * (BLOCK_SIZE + 1));
		edge_root[BLOCK_SIZE].sibling = e_next;
		e_next = edge_root + BLOCK_SIZE;
	}
	--e_next;

	e_next->nd = b;
	e_next->len = d;
	e_next->sibling = a->edge;
	a->edge = e_next;
}

void free_edges()
{
	for (; edge_root; edge_root = e_next) {
		e_next = edge_root[BLOCK_SIZE].sibling;
		free(edge_root);
	}
}

/* --- priority queue stuff --- */
heap_t *heap;
int heap_len;

void set_dist(node_t *nd, node_t *via, double d)
{
	int i, j;

	/* already knew better path */
	if (nd->via && d >= nd->dist) return;

	/* find existing heap entry, or create a new one */
	nd->dist = d;
	nd->via = via;

	i = nd->heap_idx;
	if (!i) i = ++heap_len;

	/* upheap */
	for (; i > 1 && nd->dist < heap[j = i/2]->dist; i = j)
		(heap[i] = heap[j])->heap_idx = i;

	heap[i] = nd;
	nd->heap_idx = i;
}

node_t * pop_queue()
{
	node_t *nd, *tmp;
	int i, j;

	if (!heap_len) return 0;

	/* remove leading element, pull tail element there and downheap */
	nd = heap[1];
	tmp = heap[heap_len--];

	for (i = 1; i < heap_len && (j = i * 2) <= heap_len; i = j) {
		if (j < heap_len && heap[j]->dist > heap[j+1]->dist) j++;

		if (heap[j]->dist >= tmp->dist) break;
		(heap[i] = heap[j])->heap_idx = i;
	}

	heap[i] = tmp;
	tmp->heap_idx = i;

	return nd;
}

/* --- Dijkstra stuff; unreachable nodes will never make into the queue --- */
void calc_all(node_t *start)
{
	node_t *lead;
	edge_t *e;


	set_dist(start, start, 0);
	while ((lead = pop_queue()))
		for (e = lead->edge; e; e = e->sibling)
			set_dist(e->nd, lead, lead->dist + e->len);
}

int show_path(node_t *nd, int score)
{
	if (nd->via == nd)
		printf("%s", nd->name);
	else if (!nd->via)
	;
		//printf("%s(unreached)", nd->name);
	else {
        score=show_path(nd->via,score);
		if(nd==nd->via+1)
            versDroite();
            SDL_Delay(20);
        if(nd==nd->via-1)
            versGauche();
            SDL_Delay(20);
        if(nd==nd->via+20)
            versBas();
            SDL_Delay(20);
        if(nd==nd->via-20)
            versHaut();
            SDL_Delay(20);
        score=score+1;
        return score;
	}
}

node_t* buildGraph(){

    int i;

    #	define N_NODES 400
	node_t *nodes = calloc(sizeof(node_t), N_NODES);

	for (i = 0; i < N_NODES; i++)
		sprintf(nodes[i].name, "%d", i);


    /*add_edge(nodes+3, nodes+4, 1000);
    add_edge(nodes+14, nodes+4, 1000);
    add_edge(nodes+5, nodes+4, 1000);

    add_edge(nodes+23, nodes+24, 1000);
    add_edge(nodes+14, nodes+24, 1000);
    add_edge(nodes+34, nodes+24, 1000);

    add_edge(nodes+33, nodes+34, 1000);
    add_edge(nodes+35, nodes+34, 1000);

    add_edge(nodes+45, nodes+44, 1000);
    add_edge(nodes+54, nodes+44, 1000);

    add_edge(nodes+33, nodes+43, 1000);
    add_edge(nodes+53, nodes+43, 1000);

    add_edge(nodes+32, nodes+42, 1000);
    add_edge(nodes+52, nodes+42, 1000);

    add_edge(nodes+31, nodes+41, 1000);
    add_edge(nodes+51, nodes+41, 1000);

    add_edge(nodes+30, nodes+40, 1000);
    add_edge(nodes+50, nodes+40, 1000);

    add_edge(nodes+54, nodes+64, 1000);
    add_edge(nodes+63, nodes+64, 1000);
    add_edge(nodes+65, nodes+64, 1000);

    add_edge(nodes+73, nodes+74, 1000);
    add_edge(nodes+84, nodes+74, 1000);

    add_edge(nodes+65, nodes+75, 1000);
    add_edge(nodes+85, nodes+75, 1000);

    add_edge(nodes+66, nodes+76, 1000);
    add_edge(nodes+86, nodes+76, 1000);

    add_edge(nodes+67, nodes+77, 1000);
    add_edge(nodes+87, nodes+77, 1000);

    add_edge(nodes+68, nodes+78, 1000);
    add_edge(nodes+88, nodes+78, 1000);

    add_edge(nodes+69, nodes+79, 1000);
    add_edge(nodes+89, nodes+79, 1000);

    add_edge(nodes+84, nodes+94, 1000);
    add_edge(nodes+93, nodes+94, 1000);
    add_edge(nodes+95, nodes+94, 1000);*/


	for (i = 0; i < N_NODES; i++) {
            if(i!=19 && i!=39 && i!=59 && i!=79 && i!=99 && i!=119 && i!=139 && i!=159 && i!=179 && i!=199
                && i!=219 && i!=239 && i!=259 && i!=279 && i!=299
                /*&& i!=34 && i!=4 && i!=24 && i!=34 && i!=44 && i!=43 && i!=42 && i!=41 && i!=40
                && i!=64 && i!=74 && i!=75 && i!=76 && i!=77 && i!=78 && i!=79 && i!=94*/)
            add_edge(nodes + i, nodes + i+1, 1);
            if(i!=0 && i!=20 && i!=40 && i!=60 && i!=80 && i!=100 && i!=120 && i!=140 && i!=160 && i!=180
                && i!=200 && i!=220 && i!=240 && i!=260 && i!=280 && i!=300 && i!=320 && i!=340 && i!=360 && i!=380
                /*&& i!=34 && i!=4 && i!=24 && i!=34 && i!=44 && i!=43 && i!=42 && i!=41 && i!=40
                && i!=64 && i!=74 && i!=75 && i!=76 && i!=77 && i!=78 && i!=79 && i!=94*/)
			add_edge(nodes + i, nodes + i-1, 1);
            if(i>19
                /*&& i!=34 && i!=4 && i!=24 && i!=34 && i!=44 && i!=43 && i!=42 && i!=41 && i!=40
                && i!=64 && i!=74 && i!=75 && i!=76 && i!=77 && i!=78 && i!=79 && i!=94*/)
			add_edge(nodes + i, nodes + i-20, 1);
			if(i<380
                /*&& i!=34 && i!=4 && i!=24 && i!=34 && i!=44 && i!=43 && i!=42 && i!=41 && i!=40
                && i!=64 && i!=74 && i!=75 && i!=76 && i!=77 && i!=78 && i!=79 && i!=94*/)
			add_edge(nodes + i, nodes + i+20, 1);
	}

    return nodes;
}

int dijkstra (int tabR[],int score)
{
    score=0;
    //r1
    node_t* nodes=buildGraph();
/*
    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes);
    show_path(nodes + tabR[0]);

    free(heap);

    //r2
    nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes + tabR[0]);
    show_path(nodes + tabR[1]);

    free(heap);

    //r3
    nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes + tabR[1]);
    show_path(nodes + tabR[2]);

    free(heap);

    //r4
    nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes + tabR[2]);
    show_path(nodes + tabR[3]);

    free(heap);*/

    //Arrivee
    //nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

    calc_all(nodes/* + tabR[3]*/);
    score=show_path(nodes + 399,score);


    free(heap);
    free(nodes);
	free_edges();

	return score-1;

}
