#include<stdio.h>
#include<math.h>

#define SIZE 20
#define deg 5

struct polynomial{
	int func[SIZE*2];
};

int main(void){
	int braid[] = {-1,-1,-4,3,-2,-3,4,1,1,1,-3,-2,3,-1,-1,-1,-4,3,2,-3,4,1,1,1,-3,2,3,-1};
	//int braid[] = {1,2,1,-2,-1,-2};
	int cur = 0;
	int length = sizeof(braid)/sizeof(braid[0]);
	int bcur = braid[cur];
	int c[deg-1][deg-1][SIZE*2];
	int nonzero=0;
	struct polynomial ans[deg-1][deg-1];
	struct polynomial next[deg-1][deg-1];

	//braid[cur] burau representation
	for(int i=0;i<deg-1;i++){
		for(int j=0;j<deg-1;j++){
			for(int k=0;k<SIZE*2;k++){
				ans[i][j].func[k] = 0;
			}
		}
	}
	//diagonal equal 1
	for(int i=0;i<deg-1;i++){
		ans[i][i].func[SIZE] = 1;
	}
	//U
	if(bcur>0){
		if(bcur>1)ans[bcur-2][bcur-1].func[SIZE+1] = 1;
		ans[bcur-1][bcur-1].func[SIZE+1] = -1;
		ans[bcur-1][bcur-1].func[SIZE] = 0;
		ans[bcur][bcur-1].func[SIZE] = 1;
	}
	if(bcur<0){
		if(-bcur>1)ans[-bcur-2][-bcur-1].func[SIZE] = 1;
		ans[-bcur-1][-bcur-1].func[SIZE-1] = -1;
		ans[-bcur-1][-bcur-1].func[SIZE] = 0;
		ans[-bcur][-bcur-1].func[SIZE-1] = 1;
	}	
		
	for(cur=1;cur<length;cur++){
		bcur = braid[cur];
		for(int i=0;i<deg-1;i++){
			for(int j=0;j<deg-1;j++){
				for(int k=0;k<SIZE*2;k++){
					next[i][j].func[k] = 0;
				}
			}
		}
		for(int i=0;i<deg-1;i++){next[i][i].func[SIZE]=1;}
		if(bcur>0){
			if(bcur>1)next[bcur-2][bcur-1].func[SIZE+1] = 1;
			next[bcur-1][bcur-1].func[SIZE+1] = -1;
			next[bcur-1][bcur-1].func[SIZE] = 0;
			next[bcur][bcur-1].func[SIZE] = 1;
		}
		if(bcur<0){
			if(-bcur>1)next[-bcur-2][-bcur-1].func[SIZE] = 1;
			next[-bcur-1][-bcur-1].func[SIZE-1] = -1;
			next[-bcur-1][-bcur-1].func[SIZE] = 0;
			next[-bcur][-bcur-1].func[SIZE-1] = 1;
		}	
		
		//matrix times
		for(int i=0;i<deg-1;i++){
			for(int j=0;j<deg-1;j++){
				for(int k=0;k<SIZE*2;k++){
					c[i][j][k]=0;
				}
				for(int s=0;s<deg-1;s++){
					for(int m=0;m<SIZE*2;m++){
						for(int n=SIZE-m;n<SIZE*2;n++){
							if(n>=0)c[i][j][m+n-SIZE]+=(ans[i][s].func[m]*next[s][j].func[n]);
						}
					}
				}
			}
		}
		//answer matrix
		for(int i=0;i<deg-1;i++){
			for(int j=0;j<deg-1;j++){
				for(int k=0;k<SIZE*2;k++){
					ans[i][j].func[k] = c[i][j][k];
				}
			}
		}
	}
		
	//project matrix	
	int sub=0;
	double t=2;
	int mod=7;
	for(int i=0;i<deg-1;i++){
		for(int j=0;j<deg-1;j++){
			printf("(%d,%d)=",i,j);
			for(int k=0;k<SIZE*2;k++){
				if(ans[i][j].func[k]!=0){
					nonzero = 1;
					if(ans[i][j].func[k]>=0)printf("+");
					printf("%d",ans[i][j].func[k]);
					if(k!=10)printf("t^(%d)",k-SIZE);
				}
				//substitution
				sub += ans[i][j].func[k]*pow(t,(double)(k));
			}
			if(nonzero!=1)printf("+0");
			nonzero=0;
			printf("\n");
			printf("%d \n",sub%mod);
			sub=0;
		}
		printf("\n");
	}
}