#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<pthread.h>

int nop,cnt=1,curr=0,end=0,tm,rnt=0;

struct pb 
{
	int pid,state,bt,prior,at,wt,tat,ct,exect;
	struct pb *prelink,*link;
};
struct pb *pa;

struct Queue
{
	struct pb *front ,*rear;
};
struct Queue *rq;

struct pb *remove()
{
     if(rq->front==NULL)
	     return NULL;
     struct pb *temp=rq->front;
     rq->front=rq->front->link;
     temp->link=NULL;
     if(rq->front==NULL)
	    rq->rear=NULL;
     return temp;
}

void pradd(struct pb *p);
void add(struct pb *p)
void check();

int main()
{
	int twt=0,totat=0;
	struct pb x, *pr;
	rq =(struct Queue*) malloc(sizeof(struct Queue));
	pa=(struct pb *)malloc(sizeof(struct pb)*nop);
	
	printf("Enter number of processes and the time quantum :- ");
	scanf("%d%d",&nop,&tm);
	
	printf("Enter Process ID, Arrival Time, Burst time, and Priority for each process");
	for(int i=0;i<nop;i++)
	{
	    scanf("%d",&(pa[i].pid),&(pa[i].at),&(pa[i].bt),&(pa[i].prior));
        pa[i].exect=pa[i].bt;
	    pa[i].state=0;     
	}
	
    for (int i=1;i<nop;i++) 
	{ 
    	x=pa[i]; 
    	int j=i-1; 
        while ((j>=0) && (pa[j].at>x.at))
		{ 
            pa[j+1]=pa[j]; 
            j--; 
        } 
        pa[j+1]=x; 
    } 
    
	while(1)
	{
        check();
        if(end==1)
			break;     
        if(rq->front!=NULL && cnt==1)
		{
            rnt=1;
	     	pr=remove();
            pr->state=3;
            pr->bt--;
	     	curr++;
            if(rnt==pr->exect)
            {
                cnt=1;
                pr->state=4;
                pr->ct=curr;
                pr->tat=curr-pr->at;
                pr->wt=pr->tat-pr->exect;
            }
             else
               cnt=0;
		}
        else if(cnt==0&&pr!=NULL && pr->state==3 )
		{
            if(pr->bt==0)
            {
                cnt=1;
                pr->state=4;
                pr->ct=curr;
                pr->tat=curr-(pr->at);
                pr->wt=(pr->tat)-(pr->exect);
                continue;
             }
            else if(rnt==tm)
            {
                pr->state=1;
                pradd(pr);
                cnt=1;
                continue;
            }

            else if(rq->front !=NULL)
	    	{
                if(pr->prior<rq->front->prior)
                {
                    pr->state=1;
                    add(pr);
                    cnt=1; 
                    continue; 
                }    
            }      
            rnt++;
            pr->bt--;
            curr++;
            
            if(pr->bt==0)
            {
                cnt=1;
                pr->state=4;
                pr->ct=curr;
                pr->tat=curr-(pr->at);
                pr->wt=(pr->tat)-(pr->exect);
            }            
            else if(rnt==tm)
            {
                pr->state=1;
                pradd(pr);
                cnt=1;
            }
            else if(rq->front !=NULL)
	     	{
                if(pr->prior<rq->front->prior)
                {
                    pr->state=1;
                    add(pr);
                    cnt=1;  
                }
                else
                {
                    cnt=0;
                }       
            }
            else
            {
              cnt=0;
	  		}
        }
		else
		{
			curr++;
		}
	}
	printf("\nProcess ID\tCompletion Time\tTurn Around Time\tWaiting Time");
	for(int i=0;i<nop;i++)
	{
        printf("\nop%d\t\t%d\t\t%d\t\t%d",pa[i].pid,pa[i].ct,pa[i].tat,pa[i].wt);
        twt+=pa[i].wt; totat+=pa[i].tat;
           
	}
	printf("\nop\nop Avergae TAT=%f \nop Average WT=%f\nop\nop",(totat/(nop*1.0)),(twt/(nop*1.0)));
}


void pradd(struct pb *p)
{
	if(rq->front==NULL)
	{
		rq->front=p;
		rq->rear=p;
		p->link=NULL;
	}    
	else
	{
		if(p->prior>rq->front->prior)
		{
			p->link=rq->front;
			rq->front->prelink=p;
			rq->front=p;
		}
               else if(p->prior==rq->front->prior)
		{
			p->link=rq->front->link;
			p->prelink=rq->front;
			rq->front->link=p;
                         if(p->link!=NULL)
                      {
                        p->link->prelink=p;
                      }
		}
		else if(p->prior<rq->rear->prior)
		{
			p->link=NULL;
			rq->rear->link=p;
			p->prelink=rq->rear;
			rq->rear=p;
		}
		else
		{
                   struct pb *start=rq->front->link;
		   while(start->prior>p->prior)
		   {
			   start=start->link;
		   }
                   if(start!=NULL&& p->prior==start->prior)
                   {
                          p->link=start->link;
                          start->link=p;
                          p->prelink=start;
                      
                   }
                  else
               {
		   (start->prelink)->link=p;
		   p->link=start;
		   p->prelink=start->prelink;
		   start->prelink=p;
                }

		}
	}
}

void add(struct pb *p)
{
       if(rq->front==NULL)
      { 
         p->prelink=NULL;

         p->link=NULL;
         rq->front=p;           
         rq->rear=p;
         return;
      }
     p->prelink=rq->rear;
     rq->rear->link=p;
     rq->rear=p;
}
struct pb *  remove()
{
     if(rq->front==NULL)
     {
	     return NULL;
     }
     struct pb * temp=rq->front;
     rq->front=rq->front->link;
     temp->link=NULL;
     if(rq->front==NULL)
     {
	     rq->rear=NULL;
     }
     return temp;
}
void check()
{
        int count=0;
        for(int i=0;i<nop;i++)
	   {
                   
		   if(pa[i].state == 0 && curr>=pa[i].at)
		   {   
			   pradd(&pa[i]);
			   pa[i].state=1;   
            }
            if(pa[i].state==4)
                count++;
	   }
	   if(count==nop)
		  end=1; 

}
