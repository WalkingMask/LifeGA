/* ga01.c
 * 2016/??/??(???)
 * walkingmask
 *
 * discripthon
 *  the first GA program
 * 
 * How to use
 *  is writen at line 86~
 *  日本語で
 *   ./ga -c 1000 50   ウェイト500上限のアイテムを1000個stdoutに出力
 *                       これをitems.txtにコピペして保存(>items.txt推奨)
 *   ./ga              items.txtからアイテムリストを読み込んでGA起動
 *
 * 2016/05/30(Mon) Up to date
 *  added discripitons and how to use
 *  published to github
 */


/*
 * header
 * time.h and sys/time.h: for rand
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

/*
 * constant value macro
 */
#define ITERATION 10000
#define MAX_W 20000 // limit of weight
#define ITEMS 1000
#define GENES ITEMS
#define SELECTED 10 // the number of elites
#define INDVS ((SELECTED-1)*3+4)*SELECTED // the number of individuals

/*
 * structs
 */
typedef struct {
    int price;
    int weight;
} item;

typedef struct {
	char chrom[GENES]; // Chromosome 0 or 1
	int w_sum; // weight sum
	int p_sum; // price sum
} indv;

/*
 * global variables and 
 */
char fn[] = "items.txt"; // filename
item items[ITEMS]; // the items
indv indvs[INDVS]; // the individuals
int e_i, ev_arr[INDVS], selected[SELECTED]; // ev_arr's index, evaluated arr, selected individuals
struct timeval myTime;// for rand

/* 
 * function prototypes
 * definitions are bottom
 */
void createi(int i, int max_w);
int inputi();
void init_chrom(int start, int range);
void print_i(int i);
void print_g(int g);
void eval();
void ssort();
void crossing(int i, char indv1[GENES], char indv2[GENES]);
void breed();
void mutation(int i, int j);
void extinction();


/*
 * main
 */
int main(int argc, char *argv[])
{
	// to a random value to more random
	gettimeofday(&myTime, NULL);
	srand((unsigned) myTime.tv_usec);

	/*
     * Usage   : ./ga [-c items_num weight_range]
     * Example : ./ga   (...if there is the file that the item list is printed)
     *           ./ga -c 32 50   (...if we want to create an item list)
     */
    // the createi() just prit an item list to stdout
	if(argc == 4 && strcmp(argv[1], "-c") == 0){ createi(atoi(argv[2]), atoi(argv[3])); return 0; }
    // argument must be 1 or 4
	if(argc != 1 ){ printf("Usage: ./ga [-c items_num weight_range]\n"); return 1; }
	// input the item list from the file, the filename must be "items.txt"
	if(inputi() == 1){ printf("error! couldn't open the file!\n"); return 1; }

	// init generation 1
	init_chrom(0, INDVS);
//	print_g(0); // test print

	// alternation of generations
	int g;
	for(g=1; g<ITERATION+1; g++){
		printf("----- generation %d\n", g); // test print
		eval();
		ssort();
		breed();
		if(g%10 == 0) extinction();
//		print_g(g); // test print
        sleep(1); // processing slowly
	}
	return 0;
}


/*
 * the functions definition
 */

// create an item list
void createi(int i, int max_w)
{
	int j;
	for(j=0; j<i; j++){
		gettimeofday(&myTime, NULL); // for rand
		printf("%d,%d\n", (int)(random()%(RAND_MAX-1000000)+myTime.tv_usec)%1000+101, (int)(random()%(RAND_MAX-1000000)+myTime.tv_usec)%max_w+1);
	}
}

// input items with read file
int inputi()
{
	int i;
	FILE *fp;
	if(NULL == (fp = fopen(fn, "r"))) return 1;
	for(i=0; fscanf(fp, "%d,%d", &items[i].price, &items[i].weight)!=EOF || i<ITEMS; i++);
	fclose(fp);
	return 0;
}

// initialize genes
void init_chrom(int start, int range)
{
	int i, j;
	for(i=start; i<start+range; i++){
		for(j=0; j<GENES; j++){
			gettimeofday(&myTime, NULL); // for rand
			indvs[i].chrom[j] = (random()%(RAND_MAX-1000000)+myTime.tv_usec)%2;
		}
	}
}

// print individual
void print_i(int i)
{
	int j;
	for(j=0; j<GENES; j++){
		printf("%d", indvs[i].chrom[j]);
	}
	printf("\n");
}

// print generation
void print_g(int g)
{
	int j;
	printf("--- generation %d\n", g);
	for(j=0; j<INDVS; j++){
		printf("%d ", j);
		print_i(j);
	}
}

// evaluation with weight
void eval()
{
	int i, j;
	e_i = 0;
	for(i=0; i<INDVS; i++){
		indvs[i].w_sum = 0;
		for(j=0; j<GENES; j++){
			indvs[i].w_sum += indvs[i].chrom[j] * items[j].weight;
		}
		if(indvs[i].w_sum <= MAX_W){
			ev_arr[e_i] = i;
			e_i++;
		}
	}
}

// selection with sorting
void ssort()
{
	int i, j, temp1, temp2;

	// estimate price sum
	for(i=0; i<e_i; i++){
		indvs[ev_arr[i]].p_sum = 0;
		for(j=0; j<GENES; j++){
			indvs[ev_arr[i]].p_sum += indvs[ev_arr[i]].chrom[j] * items[j].price;
		}
	}

	// selection sorting
	for(i=0; i<e_i; i++){
		temp1 = indvs[ev_arr[i]].p_sum;
		for(j=i; j>0 && temp1 > indvs[ev_arr[j-1]].p_sum; j--){
			temp2 = ev_arr[j];
			ev_arr[j] = ev_arr[j-1];
			ev_arr[j-1] = temp2;
		}
	}

	// choose top individuals
	for(i=0; i<e_i && i<SELECTED; i++){
		selected[i] = ev_arr[i];
	}

	// test print
	for(i=0; i<SELECTED && i<e_i; i++){
		printf("%d: price=%d, weight=%d ", selected[i], indvs[selected[i]].p_sum, indvs[selected[i]].w_sum);
		printf("\n");
//		print_i(selected[i]);
	}
}

// crossing two individuals
void crossing(int i, char indv1[GENES], char indv2[GENES])
{
	// estimage cross point
	int cross_p1, cross_p2, temp;
	gettimeofday(&myTime, NULL); // for rand
	cross_p1 = (random()%(RAND_MAX-1000000)+myTime.tv_usec)%(GENES-2)+1;
reestim:
	gettimeofday(&myTime, NULL); // for rand
	cross_p2 = (random()%(RAND_MAX-1000000)+myTime.tv_usec)%(GENES-2)+1;
	if(cross_p1 == cross_p2) goto reestim; // in order to not the same
	if(cross_p1 > cross_p2){
		temp = cross_p1;
		cross_p1 = cross_p2;
		cross_p2 = temp;
	}
//	printf("p1=%d, p2=%d\n", cross_p1, cross_p2); // test print

	// crossing chrom with 2 points
	int j;
	// pattern 1
	for(j=0; j<cross_p1; j++) indvs[i].chrom[j] = indv1[j];
	for(; j<cross_p2; j++) indvs[i].chrom[j] = indv1[j];
	for(; j<GENES; j++) indvs[i].chrom[j] = indv2[j];
//	print_i(i); // test print
	// pattern 2
	for(j=0; j<cross_p1; j++) indvs[i+1].chrom[j] = indv1[j];
	for(; j<cross_p2; j++) indvs[i+1].chrom[j] = indv2[j];
	for(; j<GENES; j++) indvs[i+1].chrom[j] = indv1[j];
//	print_i(i+1); // test print
	// pattern 3
	for(j=0; j<cross_p1; j++) indvs[i+2].chrom[j] = indv1[j];
	for(; j<cross_p2; j++) indvs[i+2].chrom[j] = indv2[j];
	for(; j<GENES; j++) indvs[i+2].chrom[j] = indv2[j];
//	print_i(i+2); // test print
}

// breeding
void breed()
{
	int i, j, p, q;
	indv selects[SELECTED];

	// store elites
	for(i=0; i<e_i && i<SELECTED; i++){
		selects[i] = indvs[selected[i]];
	}

	// replication top elite indvs[0]
	if(i > 0) indvs[0] = selects[0];
	i=1;

	// breeding with elite indvs[1] ~ indvs[n*(3*(n-1))]
	for(p=0, j=i; p<e_i && p<SELECTED; p++){
		for(q=0; q<e_i && q<SELECTED; q++){
			if(p == q) continue;
			crossing(j, selects[p].chrom, selects[q].chrom);
			// test print
//			printf("brend %d: %d %d %d ",j,p,p,q);for(int x=0; x<GENES; x++){printf("%d",indvs[j].chrom[x]);}printf("\n");
//			printf("brend %d: %d %d %d ",j+1,p,q,p);for(int x=0; x<GENES; x++){printf("%d",indvs[j+1].chrom[x]);}printf("\n");
//			printf("brend %d: %d %d %d ",j+2,p,q,q);for(int x=0; x<GENES; x++){printf("%d",indvs[j+2].chrom[x]);}printf("\n");
			j+=3;
		}
	}

	// mutation
	for(i=0; i<e_i && i<SELECTED; i++, j++){
		mutation(j, i);
	}

	// padding with mutant
	init_chrom(j, INDVS-j);
}

void mutation(int i, int j)
{
	// replication
	indvs[i] = indvs[j];

	// mutate gene
	gettimeofday(&myTime, NULL); // for rand
	char mu_gene = (random()%(RAND_MAX-1000000)+myTime.tv_usec)%GENES;
//	printf("mutaiton gene : %d\n", mu_gene); // test print
	indvs[i].chrom[mu_gene] = (indvs[i].chrom[mu_gene] = 0)? 1: 0;
}

void extinction()
{
	init_chrom(1,INDVS-1);
}
