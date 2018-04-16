/*
Brief description:
Changing prorities of the given processes
*/

#include<stdio.h>
#include<pthread.h>
#include<time.h>
void *fun()
{
char d;//d=a;e=b;
char e[62]={'1','2','3','4','5','7','8','9','0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
d=e[rand()%62];
printf("Random character is %c",d);	
}
main()
{
int size=0,size_l=0,i=0,a;
clock_t r,t;
double exetime;
while(1)
{
printf("\nEnter 1 to create process and 2 to exit:");
scanf("%d",&a);
if(a==2)
{
break;
}
else
{
pthread_t z[20],lower[20],higher[20];
pthread_create(&z[i],NULL,fun,NULL);
t=clock();
pthread_join(z[i],NULL);
r=clock()-t;
exetime=(double)r/CLOCKS_PER_SEC;//to get in seconds
printf("\nThe time taken by the process is=%f",exetime);
if(exetime<1)
{
printf("\nEntered to the higher priority");
higher[size]=z[i];
size++;
}
else
{
printf("\nEntered to the low priority");
lower[size_l]=z[i];
size_l++;
}
i++;
}
}
}
