#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
int main()
{
float pf,pfn,pm,pmn,mat,succ,success,fail,failure,et,pasr,losr,mr,fn,fi,pn;
float n=1000000;

printf("Time For A Page Fault For Empty Page, Modified Page, and Enter Memory Access Time ");
scanf("%f%f%f",&pf,&pm,&mat);
pfn=pf*n;
pmn=pm*n;

printf("Now, Reading Updated Page Percentage :\n");
scanf("%f",&succ);
success=succ/100;
fail=100-succ;
failure=fail/100;

printf("Reading Unupdated Page Percetnage :-,%f%\nEnter The Effective Time : ",fail);
scanf("%f",&et);

losr=failure*pfn;
pasr=success*pmn;
mr=mat+pasr+losr;
fn=mat-mr;
fi=mat-et;
pn=fi/fn;

printf("Therefore Page Fault Related To Above Details is :%f ns\n",pn;
return 0;
}
