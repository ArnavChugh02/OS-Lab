#include <stdio.h>
#include <stdlib.h>

int main(){
    int h,p;
    printf("Enter number of holes and processes:");
    scanf("%d %d",&h,&p);
    printf("Enter size of each hole:");
    int sh[h],sp[p],sho[h],pa[p];
    for(int i=0;i<h;i++){
        scanf("%d",&sh[i]);
        sho[i]=sh[i];
    }
    printf("Enter size of each processes:");
    for(int i=0;i<p;i++){
        scanf("%d",&sp[i]);
    }
    printf("Running first fit\n");
    for(int i=0;i<p;i++){
        for(int j=0;j<h;j++){
            if(sh[j]>=sp[i]){
                sh[j]-=sp[i];
                pa[i]=j;
                break;
            }
            else
                pa[i]=-1;
        }
    }
    printf("First fit sequence:\n");
    for(int i=0;i<p;i++){
        if(pa[i]==-1){
            printf("No Space left that occupy the process:%d\n",i);
        }
        else
            printf("P:%d H:%d\n",i,pa[i]);
    }
    printf("Sizes left in holes:");
    for(int i=0;i<h;i++)
        printf("%d\t",sh[i]);
    printf("\nRunning Best fit sequence");
    for(int i=0;i<p;i++){
        int mini=99999;
        int m=-1;
        for (int j=0;j<h;j++){
            if(sho[j]>=sp[i]){
                if(mini>sho[j]){
                    mini=sho[j];
                    m=j;
                }
            }
        }
        if(m>0){
            sho[m]-=sp[i];
            pa[i]=m;
        }
    }
    printf("Best fit sequence:\n");
    for(int i=0;i<p;i++){
        if(pa[i]==-1){
            printf("No Space left that occupy the process:%d\n",i);
        }
        else
            printf("P:%d H:%d\n",i,pa[i]);
    }
    printf("Sizes left in holes:");
    for(int i=0;i<h;i++)
        printf("%d\t",sho[i]);
    return 0;
}
