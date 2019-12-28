#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "intal.h"
#include <math.h>

struct volt
{
	char* s;
	int n;
	
}typedef volt;

void* intal_create(const char* str)
{
	int count=0;
	for(int i=0;i<strlen(str)-1;i++)
	{
		if(str[i]=='0')
		{
			count++;
		}
		else
		{
			break;
		}
	}
	if(strlen(str)==0)
	{
		return NULL;
	}
	volt* intal=(volt*)malloc(sizeof(volt));
	intal->n=strlen(str)-count;
	intal->s=(char*)malloc((intal->n)*sizeof(char));
	for(int i=0;i<(intal->n);i++)
	{
		if(str[i+count]>=48 && str[i+count]<=57)
		{	
			intal->s[i]=str[i+count]-48;
		}
		else
		{
			free(intal);
			volt* zero = (volt*)malloc(sizeof(volt));
			zero->s= (char*)malloc(sizeof(char));
			zero->n=1;
			zero->s[0]=0;
			return zero;	
		}
	}	
	return intal;
}

void intal_destroy(void* intal)
{
	
	free(intal);
}

char* intal2str(void* intal)
{
	if(intal==NULL)
	{
		char *sac=(char *)malloc(sizeof(char)*4);
		strcpy(sac,"NaN");
		return sac;	
	}
	char *s=(char*)intal;
	char *t=(char*)malloc(sizeof(char)*strlen(s));
	
	strcpy(t,s);
	return t;
}

void* intal_add(void* intal1, void* intal2)
{
	volt* inta1= (volt*)intal1;
	volt* inta2= (volt*)intal2;
	
	if(inta1==NULL || inta2==NULL)
	{
		return NULL;	
	}
	int a=inta1->n;
	int b=inta2->n;
	int flag=0 ;
	int p;
	int c=0;
	volt* intal3=(volt*)malloc(sizeof(volt));
	if (a>b)
	{
		a=inta2->n;
		b=inta1->n;
		flag=1;
	}
	intal3->s=(char*)malloc((b+1)*sizeof(char));
	intal3->n=b+1;
	int diff= b-a;
	for(int i=(a-1);i>=0;i--)
	{
		if(flag)
		{
			p=inta1->s[i+diff]+inta2->s[i]+c;
		}
		else
		{
			p=inta1->s[i]+inta2->s[i+diff]+c;
		}
		intal3->s[i+diff+1]=p%10;
		c=p/10;

	}
	for (int i=diff-1;i>=0;i--)
	{
		if(flag)
		{
			p=inta1->s[i]+c;
		}
		else
		{
			p=inta2->s[i]+c;
		}
		intal3->s[i+1]=p%10;
		c=p/10;
	}
	intal3->s[0]=c;
	if(c==0)
	{
		intal3->s=intal3->s+1;
		intal3->n=b;
	}
	return intal3;
}

void* intal_increment(void* intal)
{
	volt* inta=(volt*)intal;
	if(inta==NULL)
	{
		return NULL;	
	}
	for(int i=inta->n-1;i>=0;i--)
	{
		if(inta->s[i]!=9)
		{
			inta->s[i]=inta->s[i]+1;
			return inta;
		}
		else
		{
			inta->s[i]=0;
		}
	}
	volt* intal1=(volt*)malloc(sizeof(volt));
	intal1->s=(char*)malloc(inta->n+1*sizeof(char));
	intal1->n=inta->n+1;
	intal1->s[0]=1;
	for(int i=1;i<intal1->n;i++)
	{
		intal1->s[i]=0;
	}
	return intal1;
}

void* intal_decrement(void* intal)
{
	volt* inta=(volt*)intal;
	
	if(inta==NULL)
	{
		return NULL;	
	}
	if(inta->n==1)
	{
		if(inta->s[0]==1 || inta->s[0]==0)
		{
			char* ch="0";
			void* intal2= intal_create(ch);
			return intal2;
		}
	}
	for(int i=inta->n-1;i>=0;i--)
	{
		if(inta->s[i]!=0)
		{
			if(i==0 && inta->s[i]==1 )
			{
				inta->s=inta->s+1;
				inta->n=inta->n-1;
				return inta;
			}
			inta->s[i]=inta->s[i]-1;
			return inta;
		}
		else
		{
			inta->s[i]=9;
		}
	} 
}

int intal_compare(void* intal1, void* intal2)
{
	volt* a= (volt*)intal1;
	volt* b= (volt*)intal2;
	if(a==NULL ||b==NULL)
	{
		return 0;	
	}
	if(a->n > b->n)
	{
		return 1;
	}
	else if(a->n < b->n)
	{
		return -1;
	}
	else
	{
		for(int i=0;i<a->n;i++)
		{
			if(a->s[i] > b->s[i])
			{
				return 1;
			}
			else if (a->s[i] < b->s[i])
			{
				return -1;
			}
		}
		return 0;	
	}
}

void* intal_diff(void* intal1, void* intal2)
{
	volt* a=(volt*)intal1;
	volt* b=(volt*)intal2;
	if(a==NULL || b==NULL)
	{
		
		return NULL;	
	}
	int flag;
	flag=intal_compare(intal1,intal2) ;
	volt*c=(volt*)malloc(sizeof(volt)) ;
	int bor=0 ;
	int count=0 ;
	if (flag==0)
	{
		c->s=(char*)malloc(1*sizeof(char)) ;
		c->s[0]=0;
		c->n=1 ;
		return c ;
	}
	else if (flag==1)
	{
		int diff=(a->n)-(b->n) ;
		char p=0 ;
		c->s=(char*)malloc((a->n)*sizeof(char)) ;
		c->n=a->n ;
		for(int i=b->n;i>=0;i--)
		{
			if(bor==0)
			{
				if (a->s[i+diff]>=b->s[i])
				{
					c->s[i+diff]=a->s[i+diff]-b->s[i];
				}
				else
				{
					p=a->s[i+diff]+10 ;
					c->s[i+diff]=p-b->s[i];
					bor=1 ;
				}
			}
			else
			{
				if (a->s[i+diff]>b->s[i])
				{
					c->s[i+diff]=a->s[i+diff]-b->s[i]-1;
					bor=0 ;
				}
				else
				{
					p=a->s[i+diff]+9 ;
					c->s[i+diff]=p-b->s[i] ;
				}
			
		
			}
		}
		for (int i=(diff-1);i>=0;i--)
		{
			if(bor==0)
			{
				c->s[i]=a->s[i] ;
			}
			else
			{
				if(a->s[i]==0) 
				{
					c->s[i]=9 ;
				}
				else
				{
					c->s[i]=a->s[i]-1 ;
					bor=0 ;
				}
			}
		}
		for(int i=0 ;i<c->n;i++)
		{
			if(c->s[i]!=0)
			{
				break ;
			}
			count++ ;
		}
		
		c->s=c->s+count;
		c->n=c->n-count;
		return c;
	}
	else
	{
		int diff=(b->n)-(a->n) ;
		char p=0 ;
		c->s=(char*)malloc((b->n)*sizeof(char)) ;
		c->n=b->n ;
		for(int i=a->n;i>=0;i--)
		{
			if(bor==0)
			{
				if (b->s[i+diff]>=a->s[i])
				{
					c->s[i+diff]=b->s[i+diff]-a->s[i];
				}
				else
				{
					p=b->s[i+diff]+10 ;
					c->s[i+diff]=p-a->s[i];
					bor=1 ;
				}
			}
			else
			{
				if (b->s[i+diff]>a->s[i])
				{
					c->s[i+diff]=b->s[i+diff]-a->s[i]-1;
					bor=0 ;
				}
				else
				{
					p=b->s[i+diff]+9 ;
					c->s[i+diff]=p-a->s[i] ;
				}
			
		
			}
		}
		for (int i=(diff-1);i>=0;i--)
		{
			if(bor==0)
			{
				c->s[i]=b->s[i] ;
			}
			else
			{
				if(b->s[i]==0) 
				{
					c->s[i]=9 ;
				}
				else
				{
					c->s[i]=b->s[i]-1 ;
					bor=0 ;
				}
			}
		}
		for(int i=0 ;i<c->n;i++)
		{
			if(c->s[i]!=0)
			{
				break ;
			}
			count++ ;
		}
		
		c->s=c->s+count;
		c->n=c->n-count;
		return c;
	}
	
}


void* intal_multiply(void* intal1, void* intal2)
{
	
	volt* a=(volt*)intal1;
	volt* b=(volt*)intal2;
	int cnt=0;
	volt* d=(volt*)malloc(sizeof(volt));
	if(a==NULL || b==NULL)
	{
		return NULL;
	}
	d->s=(char*)malloc(sizeof(char));
	d->s[0]=0;
	d->n=1;
	int z;
	for(int j=b->n-1;j>=0;j--)
	{
		cnt=0;
		volt* c=(volt*)malloc(sizeof(volt));
		z= b->n-1-j;
		c->s=(char*)malloc((a->n+1+z)*sizeof(char));
		c->n=a->n+1+z;
		char car=0;
		char ch;
		for(int i=a->n-1;i>=0;i--)
		{
			ch=(b->s[j]*a->s[i])+car;
			c->s[i+1]=ch%10;
			car=ch/10;
		}
		for (int k=a->n+1;k<c->n;k++)
		{
			c->s[k]=0;
		}
		c->s[0]=car;

		for(int i=0;i<c->n-1;i++)
		{
			if(c->s[i]!=0)
			{
				break;
			}
			cnt++;
		}
		c->s=c->s+cnt;
		c->n=c->n-cnt;
		d=intal_add(c,d);
		free(c);
	}
	return d;
}




void* intal_divide(void* intal1, void* intal2)
{
	volt* a=(volt*)intal1;
	volt* b=(volt*)intal2;
	if(a==NULL || b==NULL)
	{
		return NULL;	
	}
	if(b->n==1)
	{
		if(b->s[0]==0)
		{
			return NULL;
		}
		if(b->s[0]==1)
		{
			volt* c=(volt*)malloc(sizeof(volt));
			c->s=(char*)malloc(a->n*sizeof(char));
			c->n=a->n;
			for(int i=0;i<a->n;i++)
			{
				c->s[i]=a->s[i];
			}
			return c;

		}
	}
	int chk;
	chk=intal_compare(a,b);
	if(chk==0)
	{
			volt* c=(volt*)malloc(sizeof(volt));
			c->s=(char*)malloc(sizeof(char));
			c->s[0]=1;
			c->n=1;
			return c;
	} 
	else if(chk==-1)
	{
		//printf("er\n");
		volt* c=(volt*)malloc(sizeof(volt));
		c->s=(char*)malloc(sizeof(char));
		c->s[0]=0;
		c->n=1;
		return c;
	}
	volt* h=(volt*)malloc(sizeof(volt));
	h->s=(char*)malloc(a->n*sizeof(char));
	h->n=0;
	int j=0;
	volt* q=(volt*)malloc(sizeof(volt));
	int count=-1;
	int tmp;
	//int cnt=0;
	volt* temp=(volt*)malloc(sizeof(volt));
	volt* temp1=(volt*)malloc(sizeof(volt));
	temp->s=(char*)malloc((b->n+1)*sizeof(char));
	temp->n=b->n;
	//temp->s=a->s;
	for(int i=0;i<temp->n;i++)
	{
		temp->s[i]=a->s[++count];
	}
	int check=intal_compare(b,temp);
	//count=count+b->n-1;
	if(check==1)
	{
		temp->n=temp->n+1;
		temp->s[temp->n-1]=a->s[++count];
		
	}
	//printf("temp: %s\n", intal2str(temp));

	while(a->n > count)
	{
		//printf("er");
		//printf("temp: %s\n", intal2str(temp));
		check=intal_compare(temp,b);
		q->s=(char*)malloc(1*sizeof(char));
		q->s[0]=0;
		q->n=1;
		while(check!=-1)
		{
			temp=intal_diff(temp,b);
			q=intal_increment(q);
			check=intal_compare(temp,b);
		}
		h->s[j]=q->s[q->n-1];//the length of q is 1 only 
		/*printf("%d\n",q->n);
		if(q->n!=1)
		{
			printf("q: %s\n", intal2str(q));
		}*/
		j++;
		//check=intal_compare(b,temp);
		tmp=temp->n;
		if(tmp==1 && temp->s[0]==0)
		{
			tmp--;
		}
		temp1->s=(char*)malloc((tmp)*sizeof(char));
		temp1->n=tmp;
		for(int i=0;i<tmp;i++)
		{
			temp1->s[i]=temp->s[i];
		}
		//temp1->s[tmp]=a->s[++count];
		temp->s=(char*)malloc((tmp+1)*sizeof(char));
		temp->n=tmp+1;
		for(int i=0;i<temp->n;i++)
		{
			temp->s[i]=temp1->s[i];
		}
		temp->s[tmp]=a->s[++count];
	}
	h->n=j;
	return h;
}

void* intal_pow(void* intal1, void* intal2)
{
	volt* a=(volt*)intal1;
	volt* b=(volt*)intal2;
	if(a==NULL || b==NULL)
	{
		return NULL;	
	}
	if(b->n==1 && b->s[0]==0)
	{
		volt* c=(volt*)malloc(sizeof(volt));
		c->s=(char*)malloc(sizeof(char));
		c->s[0]=1;
		c->n=1;
		return c;
	}
	volt* d=(volt*)malloc(sizeof(volt));
	d->s=(char*)malloc(sizeof(char));
	d->s[0]=2;
	d->n=1;
	volt* c = intal_divide(b,d);
	volt* p=intal_pow(a,c);
	p=intal_multiply(p,p);
	int k =b->s[b->n-1];
	//printf("%d",k);	
	if (k%2==1)
	{
		//printf("%d",k);
		p=intal_multiply(p,a);
	}
	return p;
}

