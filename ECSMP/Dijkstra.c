/**
 * \file      Dijkstra.c
 * \author    PHAN Joseph, SEYDI Sarta, MONCAYO Loïc
 * \version   1.1
 * \date      10 Décembre 2014
 * \brief     Contient la fonction "dijkstra" pour lancer le plus court chemin et en récupérer le score ainsi que les méthodes utiles à cette fonction.
 *
 * \details   Fichier nécessaire à l'utilisation de l'algo du plus court chemin.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node_t node_t, *heap_t;
typedef struct edge_t edge_t;
struct edge_t {
	node_t *nd;	    /* Cible de l'arrête */
	edge_t *sibling;/* for singly linked list */
	int len;	    /* Coût de l'arrête */
};
struct node_t {
	edge_t *edge;	/* singly linked list of edges */
	node_t *via;	/* Noeud précédent selon le plus court chemin */
	double dist;	/* Distance depuis le noeud d'origine */
	char name[8];	/* Nom du noeud */
	int heap_idx;	/* link to heap position for updating distance */
};


/* --- Manipulation des arrêtes --- */
#	define BLOCK_SIZE 32

edge_t *edge_root = 0, *e_next = 0;

/**
 * \brief    Méthode d'ajout d'une arrête
 * \param    *a       Pointeur sur le noeud de départ.
 * \param    *b       Pointeur sur le noeaud d'arrivée.
 * \param    d        Distance(double) entre les deux noeuds.
 */
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

/**
 * \brief   Méthode pour libérer la mémoire des arrêtes
 */
void free_edges()
{
	for (; edge_root; edge_root = e_next) {
		e_next = edge_root[BLOCK_SIZE].sibling;
		free(edge_root);
	}
}

/* --- Queue de priorité --- */
heap_t *heap;
int heap_len;

/**
 * \brief    Méthode d'ajout d'une arrête
 * \param    *a       Pointeur sur le noeud de base.
 * \param    *b       Pointeur sur le noeaud via lequel on arrive sur le noeud de base.
 * \param    d        Distance(double) entre les deux noeuds.
 */
void set_dist(node_t *nd, node_t *via, double d)
{
	int i, j;

	/* Déjà un plus court chemin */
	if (nd->via && d >= nd->dist) return;

	/* Trouve une entrée heap existante ou en crée une */
	nd->dist = d;
	nd->via = via;

	i = nd->heap_idx;
	if (!i) i = ++heap_len;

	/* On dépile */
	for (; i > 1 && nd->dist < heap[j = i/2]->dist; i = j)
		(heap[i] = heap[j])->heap_idx = i;

	heap[i] = nd;
	nd->heap_idx = i;
}

/**
 * \brief    Méthode pour étudier la queue.
 */
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

/* --- Fonctions pour lancer dijkstra --- */

/**
 * \brief    Fonction de calcul des distances sur tout le graphe
 * \param    *start  Pointeur sur le noeud de départ du graphe.
 */
void calc_all(node_t *start)
{
	node_t *lead;
	edge_t *e;


	set_dist(start, start, 0);
	while ((lead = pop_queue()))
		for (e = lead->edge; e; e = e->sibling)
			set_dist(e->nd, lead, lead->dist + e->len);
}

/**
 * \brief    Méthode pour trouver le plus court chemin et déplacer le personnage selon ce dernier.
 * \param    *nd       Pointeur sur le noeud à atteindre.
 * \return   score    Le score (int,nombre de déplacements) du joueur.
 */
int show_path(node_t *nd, int score)
{
	if (nd->via == nd)
        return 0;
	else if (!nd->via)
        return 0;
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

/* Construction du graphe en fonction de la carte */
/**
 * \brief    Fonction de construction du graphe
 * \return   *nodes     Liste de tous les noeuds après construction du graphe.
 */
node_t* buildGraph(){

    int i;

    #	define N_NODES 400
	node_t *nodes = calloc(sizeof(node_t), N_NODES);

    // Définition de tous les noeuds
	for (i = 0; i < N_NODES; i++)
		sprintf(nodes[i].name, "%d", i);

    // Défintion des obstacles (poids=1000 et non 1, donc jamais utilisés comme chemin
    for (i=8;i<12;i=i+1){
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=388;i<392;i=i+1){
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    }

    for (i=319;i<380;i=i+20){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=80;i<141;i=i+20){
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=99;i<160;i=i+20){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }


    for (i=299;i<360;i=i+20){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=83;i<97;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=103;i<117;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=123;i<137;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=143;i<157;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }


    for (i=28;i<32;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }


    for (i=168;i<172;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }


    for (i=228;i<232;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=248;i<252;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=268;i<279;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=288;i<299;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=308;i<319;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    for (i=328;i<339;i=i+1){
    add_edge(nodes+i-1, nodes+i, 1000);
    add_edge(nodes+i+1, nodes+i, 1000);
    add_edge(nodes+i-20, nodes+i, 1000);
    add_edge(nodes+i+20, nodes+i, 1000);
    }

    add_edge(nodes+81, nodes+101, 1);
    add_edge(nodes+102, nodes+101, 1);
    add_edge(nodes+121, nodes+101, 1);
    add_edge(nodes+100, nodes+101, 1000);

    add_edge(nodes+82, nodes+102, 1);
    add_edge(nodes+103, nodes+102, 1000);
    add_edge(nodes+122, nodes+102, 1);
    add_edge(nodes+101, nodes+102, 1);

    add_edge(nodes+101, nodes+121, 1);
    add_edge(nodes+122, nodes+121, 1);
    add_edge(nodes+141, nodes+121, 1);
    add_edge(nodes+120, nodes+121, 1000);

    add_edge(nodes+102, nodes+122, 1);
    add_edge(nodes+123, nodes+122, 1000);
    add_edge(nodes+142, nodes+122, 1);
    add_edge(nodes+121, nodes+122, 1);

    add_edge(nodes+29, nodes+49, 1);
    add_edge(nodes+50, nodes+49, 1);
    add_edge(nodes+69, nodes+49, 1);
    add_edge(nodes+48, nodes+49, 1000);

    add_edge(nodes+30, nodes+50, 1);
    add_edge(nodes+51, nodes+50, 1000);
    add_edge(nodes+70, nodes+50, 1);
    add_edge(nodes+49, nodes+50, 1);

    add_edge(nodes+49, nodes+69, 1);
    add_edge(nodes+70, nodes+69, 1);
    add_edge(nodes+89, nodes+69, 1);
    add_edge(nodes+68, nodes+69, 1000);

    add_edge(nodes+50, nodes+70, 1);
    add_edge(nodes+71, nodes+70, 1000);
    add_edge(nodes+90, nodes+70, 1);
    add_edge(nodes+69, nodes+70, 1);

    add_edge(nodes+97, nodes+117, 1);
    add_edge(nodes+118, nodes+117, 1);
    add_edge(nodes+137, nodes+117, 1);
    add_edge(nodes+116, nodes+117, 1000);

    add_edge(nodes+98, nodes+118, 1);
    add_edge(nodes+119, nodes+118, 1000);
    add_edge(nodes+138, nodes+118, 1);
    add_edge(nodes+117, nodes+118, 1);

    add_edge(nodes+117, nodes+137, 1);
    add_edge(nodes+138, nodes+137, 1);
    add_edge(nodes+157, nodes+137, 1);
    add_edge(nodes+136, nodes+137, 1000);

    add_edge(nodes+118, nodes+138, 1);
    add_edge(nodes+139, nodes+138, 1000);
    add_edge(nodes+158, nodes+138, 1);
    add_edge(nodes+137, nodes+138, 1);

    add_edge(nodes+169, nodes+189, 1);
    add_edge(nodes+190, nodes+189, 1);
    add_edge(nodes+209, nodes+189, 1);
    add_edge(nodes+188, nodes+189, 1000);

    add_edge(nodes+170, nodes+190, 1);
    add_edge(nodes+191, nodes+190, 1000);
    add_edge(nodes+210, nodes+190, 1);
    add_edge(nodes+189, nodes+190, 1);

    add_edge(nodes+189, nodes+209, 1);
    add_edge(nodes+210, nodes+209, 1);
    add_edge(nodes+229, nodes+209, 1);
    add_edge(nodes+208, nodes+209, 1000);

    add_edge(nodes+190, nodes+210, 1);
    add_edge(nodes+211, nodes+210, 1000);
    add_edge(nodes+230, nodes+210, 1);
    add_edge(nodes+209, nodes+210, 1);

    add_edge(nodes+329, nodes+349, 1);
    add_edge(nodes+350, nodes+349, 1);
    add_edge(nodes+369, nodes+349, 1);
    add_edge(nodes+348, nodes+349, 1000);

    add_edge(nodes+330, nodes+350, 1);
    add_edge(nodes+351, nodes+350, 1000);
    add_edge(nodes+370, nodes+350, 1);
    add_edge(nodes+349, nodes+350, 1);

    add_edge(nodes+349, nodes+369, 1);
    add_edge(nodes+370, nodes+369, 1);
    add_edge(nodes+389, nodes+369, 1);
    add_edge(nodes+368, nodes+369, 1000);

    add_edge(nodes+350, nodes+370, 1);
    add_edge(nodes+371, nodes+370, 1000);
    add_edge(nodes+390, nodes+370, 1);
    add_edge(nodes+369, nodes+370, 1);

    // Définition de toutes les arrêtes
	for (i = 0; i < N_NODES; i++) {
            if(i!=80 && i!=100 && i!=120 && i!=140 && i!=99 && i!=119 && i!=139 && i!=159 &&
                i!=299 && i!=319 && i!=339 && i!=359 && i!=83 && i!=84 &&
                i!=85 && i!=86 && i!=87 && i!=88 && i!=89 && i!=90 && i!=91 && i!=92 && i!=93 && i!=94 &&
                i!=95 && i!=96 && i!=103 && i!=104 && i!=105 && i!=106 &&
                i!=107 && i!=108 && i!=109 && i!=110 && i!=111 && i!=112 && i!=113 && i!=114 && i!=115 && i!=116 &&
                i!=123 && i!=124 && i!=125 && i!=126 && i!=127 && i!=128 &&
                i!=129 && i!=130 && i!=131 && i!=132 && i!=133 && i!=134 && i!=135 && i!=136 &&
                i!=143 && i!=144 && i!=145 && i!=146 && i!=147 && i!=148 && i!=149 && i!=150 &&
                i!=151 && i!=152 && i!=153 && i!=154 && i!=155 && i!=156 && i!=28 && i!=29 && i!=30 && i!=31 &&
                i!=168 && i!=169 && i!=170 && i!=171 && i!=228 && i!=229 && i!=230 && i!=231 &&
                i!=248 && i!=249 && i!=250 && i!=251
                && i!=388 && i!=389 && i!=390 && i!=391 && i!=8 && i!=9 && i!=10 && i!=11
                && i!=268 && i!=269 && i!=270 && i!=271 && i!=272 && i!=273 && i!=274 && i!=275 && i!=276 && i!=277 && i!=278
                && i!=288 && i!=289 && i!=290 && i!=291 && i!=292 && i!=293 && i!=294 && i!=295 && i!=296 && i!=297 && i!=298
                && i!=308 && i!=309 && i!=310 && i!=311 && i!=312 && i!=313 && i!=314 && i!=315 && i!=316 && i!=317 && i!=318
                && i!=328 && i!=329 && i!=330 && i!=331 && i!=332 && i!=333 && i!=334 && i!=335 && i!=336 && i!=337 && i!=338
                && i!=279 && i!=299 && i!=319 && i!=339
            ){

                    if(i!=19 && i!=39 && i!=59 && i!=79 && i!=99 && i!=119 && i!=139 && i!=159 && i!=179 && i!=199
                        && i!=219 && i!=239 && i!=259 && i!=279 && i!=299 && i!=319 && i!=339 && i!=359 && i!=379 && i!=399
                        /*&& i!=34 && i!=4 && i!=24 && i!=34 && i!=44 && i!=43 && i!=42 && i!=41 && i!=40
                        && i!=64 && i!=74 && i!=75 && i!=76 && i!=77 && i!=78 && i!=79 && i!=94*/){
                    add_edge(nodes + i, nodes + i+1, 1);}
                    if(i!=0 && i!=20 && i!=40 && i!=60 && i!=80 && i!=100 && i!=120 && i!=140 && i!=160 && i!=180
                        && i!=200 && i!=220 && i!=240 && i!=260 && i!=280 && i!=300 && i!=320 && i!=340 && i!=360 && i!=380
                        /*&& i!=34 && i!=4 && i!=24 && i!=34 && i!=44 && i!=43 && i!=42 && i!=41 && i!=40
                        && i!=64 && i!=74 && i!=75 && i!=76 && i!=77 && i!=78 && i!=79 && i!=94*/){
                    add_edge(nodes + i, nodes + i-1, 1);}
                    if(i>19
                        /*&& i!=34 && i!=4 && i!=24 && i!=34 && i!=44 && i!=43 && i!=42 && i!=41 && i!=40
                        && i!=64 && i!=74 && i!=75 && i!=76 && i!=77 && i!=78 && i!=79 && i!=94*/){
                    add_edge(nodes + i, nodes + i-20, 1);}
                    if(i<380
                        /*&& i!=34 && i!=4 && i!=24 && i!=34 && i!=44 && i!=43 && i!=42 && i!=41 && i!=40
                        && i!=64 && i!=74 && i!=75 && i!=76 && i!=77 && i!=78 && i!=79 && i!=94*/){
                    add_edge(nodes + i, nodes + i+20, 1);}
            }
	}

    return nodes;
}

// Fonction qui lance le "jeu"
/**
 * \brief    Fonction de lancement de l'agorithme de dijkstra et obtention du score.
 * \param    tabR     Tableau contenant l'emplacement des ressources.
 * \param    score    Le score(int) du joueur.
 * \return   score    Le score(int) du joueur.
 */
int dijkstra (int tabR[],int score)
{
    score=0;

    // Ressource 1
    node_t* nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes);
    score=show_path(nodes + tabR[0],score);

    free(heap);

    // Ressource 2
    nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes + tabR[0]);
    score=score+show_path(nodes + tabR[1],score);

    free(heap);

    // Ressource 3
    nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes + tabR[1]);
    score=score+show_path(nodes + tabR[2],score);

    free(heap);

    // Ressource 4
    nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes + tabR[2]);
    score=score+show_path(nodes + tabR[3],score);

    free(heap);

    // Arrivée
    nodes=buildGraph();

    heap = calloc(sizeof(heap_t), N_NODES + 1);
	heap_len = 0;

    calc_all(nodes+ tabR[3]);
    score=score+show_path(nodes + 399,score);

    // Libération pour la mémoire
    free(heap);
    free(nodes);
	free_edges();

	return score;
}
