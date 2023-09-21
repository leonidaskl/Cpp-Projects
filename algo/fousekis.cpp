#include <stdio.h>  
#include <limits.h>  
#include <stdbool.h>  
#include <stdlib.h>  
  
// lets make fuseki the great proud  
int main(int argc, char *argv[]){  
    int N,M,K,X;  
    int *** g,*** pd,kpd;  
      
    scanf("%d %d %d %d",&N ,&M ,&K ,&X );  
    //calloc gia g,pd  
    g = calloc(N,sizeof(int **));  
    pd = calloc(N,sizeof(int **));  
      
    int i,j;  
    for (i=0;i<N;i++){  
        pd[i] = calloc(M,sizeof(int *));  
        g[i] = calloc(M,sizeof(int *));  
         
        for (j=0;j<M;j++){  
              
            g[i][j] = calloc((X+1),sizeof(int));  
            pd[i][j]= calloc(2,sizeof(int));  
            pd[i][j][0] = -1;  
            pd[i][j][1] = -1;  
        }  
    }  
    int s_x,s_y,s,e_x,e_y,e;  
  
    for (i=0;i<K;i++){  
        scanf("%d",&s);  
        scanf("%d",&e);  
        s_x=s/M;  
        s_y=s%M;  
        e_x = e/M;  
        e_y = e%M;  
        g[s_x][s_y][0] = 0;  
        pd[s_x][s_y][0]= e_x;  
        pd[s_x][s_y][1]= e_y;  
          
    }  
      
    for (kpd=0;kpd<(X+1);kpd++){  
        g[0][0][kpd] = 0;  
    }  
    //axrikopoihsh!!!  
    g[0][0][0] = 1;  
    for (i=0;i<N;i++){  
        for (j=0;j<M;j++){  
            if (pd[i][j][0]!=-1){  
      
                for (kpd=1;kpd<(X+1);kpd++){  
                    g[i][j][kpd] = g[pd[i][j][0]][pd[i][j][1]][kpd-1];  
                      
                }  
            }  
              
            else if ((i!=0)&&(j!=0)){  
                for (kpd=0;kpd<(X+1);kpd++){  
                    g[i][j][kpd] = (g[i-1][j][kpd] + g[i][j-1][kpd])%1000000103;  
                    //mod1000000103 ftw #uperxilisi  
                      
                }  
            }  
            else if (i!=0){  
                for (kpd=0;kpd<(X+1);kpd++){  
                    g[i][j][kpd] = g[i-1][j][kpd];  
                      
                }  
            }  
            else if (j!=0){  
                for (kpd=0;kpd<(X+1);kpd++){  
                    g[i][j][kpd] = g[i][j-1][kpd];  
                }  
            }  
        }  
       
    }  
      
    int sum=0;  
      
    for (kpd=0;kpd<(X+1);kpd++){  
          
        sum = (sum + g[N-1][M-1][kpd])%1000000103;  
          
    }  
    free (g);  
    free (pd);  
      
    printf("%d\n",sum);  
      
    return 0;  
} 
