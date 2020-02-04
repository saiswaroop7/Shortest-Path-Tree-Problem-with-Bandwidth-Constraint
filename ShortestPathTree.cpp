
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "conio.h"
#include "string.h"
#include <time.h>

int sd, nd, con[20][20], band[20][20], solv[30][20];
void print_matrix(int m[20][20])
{
	for (int i = 1; i <= nd; i++)
	{
		printf("\n");
		for (int j = 1; j <= nd; j++)
			printf("%d\t", m[i][j]);
	}
}
void print_chrom(int m[20])
{
	printf("\n\n");
	printf("Printing Chrom ...");
	for (int j = 1; j <= nd; j++)
		printf("%d\t", m[j]);
}
int compute_cost(int m[20], int cst[20][20])
{
	int sum = 0;
	for (int i = 2; i < m[1] - 1; i++)
		sum += cst[m[i]][m[i + 1]];
	return(sum);
}
/*****************************************/
void print_solv(int m[20])
{
	printf("\n\n");
	printf("{");
	for (int j = 2; j <= m[1]-2; j++)
		if (j != m[1]-2 )
			printf("%d ->", m[j]);
		else
			printf("%d", m[j]);
    printf("}");
}
/*****************************************/
int connection_chrom(int m[20])
{
	for (int i = 1; i < nd; i++)
	{
		if (m[i] == 0)continue;
		for (int j = i + 1; j <= nd; j++)
		{
			if (m[j] == 0)continue;
			if (con[m[i]][m[j]] == 0)return 0; else { break; }
		}
	}
	return 1;
}
int compute_bandwidth(int m[20])
{
	int i, j, ban = 100;
	for (i = 1; i < nd; i++)
	{
		if (m[i] == 0)continue;
		for (j = i + 1; j <= nd; j++)
		{
			if (m[j] == 0)continue;
			if (ban > band[m[i]][m[j]])ban = band[m[i]][m[j]];
			break;
		}
	}
	return ban;
}
void sort_chrom(int m[20])
{
	for (int i = 1; i < nd; i++)
	{
		if (m[i] == 0)continue;
		if (m[i] == m[nd]) { m[i] = 0; continue; }
		for (int j = i + 1; j < nd; j++)
		{
			if (m[j] == 0)continue;
			if (m[i] == m[j])m[j] = 0;
		}
	}
}
void store_chrom(int m[20], int m1[20])
{
	for (int i = 1; i <= nd; i++)
		m1[i] = m[i];
}
void check_chrom(int m[20], int ban)
{
	sd++;
	int i, j, k, n1 = 2;
	for (i = 1; i <= nd; i++)
		if (m[i] != 0) { solv[sd][n1] = m[i]; n1++; }
	solv[sd][n1] = ban;
	solv[sd][1] = n1;
	for (i = 1; i < sd; i++)
	{
		k = 0;
		for (j = 2; j < solv[i][1]; j++)
			if (solv[sd][j] == solv[i][j])k++;

		if (k == solv[i][1] - 2) { sd--; break; }
	}
}
int main()
{
	int i, j, k, n, id, x, y, z, t1, t2, test, ng, disn, B, chrom[30][20], chrom1[30][20];
	int cost[20][20], dist[20], conds[20];
	char name[10];
	printf("\nEnter Filename:");
	scanf("%s", name);
	FILE *f;
	f = fopen(name, "r");
	fscanf(f, "%d", &nd);
	//The number of nodes
	//printf("Enter the number of nodes:");
	//scanf("%d",&nd);
	printf("\n Enter the connection matrix:");
	for (i = 1; i <= nd; i++)
    {
		for (j = 1; j <= nd; j++)
		{
			fscanf(f, "%d", &con[i][j]); //The connection matrix
			cost[i][j] = 0;             //The cost matrix
			band[i][j] = 0;             //The bandwidth matrix
		}
   }
	printf("\n\nThe Connection Matrix:");
	printf("\n============================");
	print_matrix(con);
	fclose(f);
	srand(time(NULL));
	for (i = 1; i <= nd; i++)
	{
	{
			for (j = i + 1; j <= nd; j++)
			if (con[i][j] > 0)
			{
				cost[i][j] = rand() % (12); 
				if (cost[i][j] == 0)continue;
				cost[j][i] = cost[i][j];
				band[i][j] = 2 * cost[i][j];
				band[j][i] = band[i][j];
			}
    }}
	printf("\n\nThe Cost Matrix:");
	printf("\n=====================");
	print_matrix(cost);

	printf("\n\nThe Bandwidth Matrix:");
	printf("\n============================");
	print_matrix(band);

	//the number of destination nodes
	disn = nd - 1;

	printf("\n\nThe Destination Nodes taken:\n");
	printf("\n============================\n");
    
	for (i = 1; i <= disn; i++)
	{
		dist[i] = i + 1;
	    printf("%d ",dist[i]);
	}
	for (i = 1; i <= disn; i++)
	{
		conds[i] = 0;
		for (j = 1; j <= nd; j++)
			if (con[dist[i]][j] > 0)conds[i]++; //No of nodes which connect dist node.
		conds[i] += 2;
	}

    printf("\nComputing Shortest Paths in the Network.");
	/**************************Genetic Algorithm**************************/
	int pop = 25;
	for (id = 1; id <= disn; id++)
	{
		n = 1;
		sd = 0;
		/********************* Initial Populations *****/
		   //printf("\n\nThe chromothoms:");
		   //printf("\n=====================");

		chrom[n][1] = 1;
		for (j = 2; j < nd; j++)
			chrom[n][j] = 0;
	    chrom[n][nd] = dist[id];
		test = connection_chrom(chrom[n]);
		
		if (test > 0)n++;

		for (;;)
		{
			chrom[n][1] = 1;
			j = 2;
			for (;;)
			{
				chrom[n][j] = rand() % (nd + 1);
				//printf(" Rand Chrom: %d\n",chrom[n][j]);
				//printf(" N value: %d\n",n);				
				if (chrom[n][j] == 1 || chrom[n][j] == dist[id])continue;
				if (j == nd - 1)break;
				j++;
			}
			chrom[n][nd] = dist[id];
			sort_chrom(chrom[n]);
			test = connection_chrom(chrom[n]);
			if (test == 0)continue;
			//print_chrom(chrom);
			if (n == pop)break;
			n++;
		}
	   /******************The Crossover operation**************/

		ng = 1;
		for (;;)
		{
			n = 1;
			for (;;)
			{
				store_chrom(chrom[n], chrom1[n]);
				float pc = float(rand() % 10) / 10;
				//printf(" PC: %f",pc);
				if (pc >= 0.9)
				{
					for (;;)
					{
						t1 = rand() % pop;
						t2 = rand() % pop;
						if (t1 == 0 || t2 == 0)continue; else break;
					}

					x = rand() % (nd - 1);
					for (i = 1; i <= x; i++)
						chrom1[n][i] = chrom[t1][i];

					for (i = x + 1; i <= nd; i++)
						chrom1[n][i] = chrom[t2][i];
				}

				/********************The Mutation operation**************/
				float pm = float(rand() % 10) / 10;
				if (pm <= 0.2)
				{
					for (;;)
					{
						y = rand() % (nd - 1);
						if (y == 0 || y == 1)continue; else break;
					}
					for (;;)
					{
						z = rand() % (nd + 1);
						if (z == 1 || z == dist[id])continue; else break;
					}
					chrom1[n][y] = z;
				}
				/************************compute_bandwidth************/
				sort_chrom(chrom1[n]);
				test = connection_chrom(chrom1[n]);
				if (test == 0)continue;
				B = compute_bandwidth(chrom1[n]);
				if (B >= 5) check_chrom(chrom1[n], B);
				//check_chrom(chrom1[n],band); 
				//print_chrom(chrom1[n]);
				if (n == pop)break;
				n++;
			}

			for (k = 1; k <= n; k++)
				store_chrom(chrom1[k], chrom[k]);

			if (ng == 10)break;
			ng++;
		}
		//break;
		
		/**************************The results******************/
		int sp, min = 1000;
		for (i = 1; i <= sd; i++)
		{
			//print_solv(solv[i]);
			int ns = solv[i][1] + 1;
			solv[i][ns] = compute_cost(solv[i], cost);//getch();
			solv[i][1] = ns;
			if (min > solv[i][ns]) 
			{ min = solv[i][ns]; sp = i; }
		    else
			{
		    	//print_matrix(solv);
				printf("\nPrevious Paths :\n");
				
			    for(i=1;i<=nd-2;i++)
			    {
			    	if(solv[i][ns]==0){continue;}
			    	for(j = 2;j<=nd-2;j++)
			    	{
			    	if(solv[i][j]>nd||solv[i][j]==0)
					{
					continue;
					}
					else
			         printf("%d ",solv[i][j]);
			       }
		    	   if(i<nd-1)
		    	   {
					   printf("Cost : %d",solv[i][ns]);
		           }
		 	       printf("\n");
				}
			}
		}
		printf("\n\nThe candidate path set:");
		printf("\nShortest Path Found: ");
		print_solv(solv[sp]);
		int co = solv[sp][1];
		printf("\t Bandwidth = %d Cost = %d", solv[sp][co - 1], solv[sp][co]);
		printf("\n================================\n");
	}
	printf("Press any key to exit.");
	_getch();
}
/*****************************************************************************/


