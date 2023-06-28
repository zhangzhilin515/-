#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MaxSize 50
#define INF 10000
typedef struct placeNode node;
typedef struct MapGraph Graph;
struct use
{
	char num[10];
	char dat[12];
	char splace[20];
	char eplace[20];
	float stime;
	float etime;
	int money;
	struct use *next; 
};
struct placeNode
{
	int id;
	char name[20];
};
struct MapGraph
{
	int number;
	int arcsM[20][20];
	float arcsT[20][20];
	node list[20];
};
int main();
void luru();
void enquiry();
void modifies();
void del();
void init()
{
	char ch;
	FILE *fp1,*fp2;
	if(fp1=fopen("railway.txt","r"))
	{
		ch=getc(fp1);
		fp2=fopen("file.txt","w+");
		while(ch!=EOF)
		{
			fputc(ch,fp2);
			ch=getc(fp1);
		}
		fclose(fp1);
		fclose(fp2);
		printf("�ļ���ʼ���ɹ�\n");
		main();
	}
	else
	{
		printf("�ļ���ʼ��ʧ��\n");
		main();
	}
} 
void luru()
{
	FILE *fp;
	struct use *p,*f,*head;
	int n=0,a,s=0,i;
	p=f=(struct use *)malloc(sizeof(struct use));
	head=NULL;
	printf("������������");
	scanf("%d",&a); 
	printf("�밴���Σ����ڣ���ʼ�أ�Ŀ�ĵأ���ʼʱ�䣬����ʱ�䣬Ʊ������¼�롣\n");
	if(scanf("%s%s%s%s%f%f%d",&p->num,&p->dat,&p->splace,&p->eplace,&p->stime,&p->etime,&p->money)!=EOF)n++;
	if(a==1)head=p;
	while(n!=a)
	{
		s++;
		if(s==1)head=p;
		else  f->next=p;
		f=p;
		p=(struct use *)malloc(sizeof(struct use));
		if(scanf("%s%s%s%s%f%f%d",&p->num,&p->dat,&p->splace,&p->eplace,&p->stime,&p->etime,&p->money)!=EOF) 	n++;
	}
	if(a==1)p->next=NULL;
	else
	{
	  f->next=p;
	  p->next=NULL;	
	}
	if((fp=fopen("file.txt","w"))==NULL)
	{
		printf("cannot open this file.\n");
		exit(0);
	}
	for(i=0;i<n;i++)
	{
		fwrite(head,sizeof(struct use),1,fp);
		if(a!=1) head=head->next;
	}
	fclose(fp);
	main();   
}
struct use* file()
{
	int n=0,s,i,j;
	FILE *fp;
	struct use *p,*f,*head;
	p=f=(struct use *)malloc(sizeof(struct use));
	head=NULL;
	if((fp=fopen("file.txt","r"))==NULL)
	{
		printf("cannot open this file.\n");
		exit(0);
	}
    while(!feof(fp))
	{
		if(n==1)head=p;
		else f->next=p;
		f=p;
		p=(struct use *)malloc(sizeof(struct use));
		if(fread(p,sizeof(struct use),1,fp)!=EOF)n++;
	}
	if(n==1){p->next=NULL;head=p;}
	else
	{
	  f->next=p;
	  p->next=NULL;	
	}
	fclose(fp);
	return head;
}
void CreateGraph(Graph *g)
{
	//�ļ�д�� 
	struct use *head;
	head=file();
	//����ͼ
	int i,j;
	int gs=0,ge=0;
	g->number=0;
	while(head->next!=NULL)
	{
		gs=0;
		ge=0;
		for(j=0;j<g->number;j++)//�����ǰͼ�Ľ���б����Ѿ����ڸý�㣬�򲻴���ý�� 
		{
			if(strcmp(head->splace,g->list[j].name)==0)gs=1;
			if(strcmp(head->eplace,g->list[j].name)==0)ge=1;
		}
		if(gs==0)
		{
			g->list[g->number].id=g->number;
			strcpy(g->list[g->number].name,head->splace);
			g->number++;
		}
		if(ge==0)
		{
			g->list[g->number].id=g->number;
			strcpy(g->list[g->number].name,head->eplace);
			g->number++;
		}
		head=head->next;
	}
}
void print(Graph g)
{
	int i,j;
	for(i=0;i<g.number;i++)
	{
		printf("%d %s",g.list[i].id,g.list[i].name);
	}
	printf("\n");
	for(i=0;i<g.number;i++)
	{
		for(j=0;j<g.number;j++)
		{
			printf("%.1f ",g.arcsT[i][j]);
		}
		printf("\n");
	}
}
int find(Graph g,char str[])
{
	int i;
	for(i=0;i<g.number;i++)
	{
	if(strcmp(g.list[i].name,str)==0)
	{
		break;
	}
	} 
	return i;
}
void input(Graph *g)
{
	//�����ļ� 
	struct use *head;
	head=file();
	//����ͼ�ľ��� 
	int i,j;
	for(i=0;i<g->number;i++)
	{
		for(j=0;j<g->number;j++)
		{
			g->arcsM[i][j]=INF;
			g->arcsT[i][j]=INF;
		}
	}
	while(head->next!=NULL)
	{
		if(g->arcsM[find(*g,head->splace)][find(*g,head->eplace)]>head->money)
		{
			g->arcsM[find(*g,head->splace)][find(*g,head->eplace)]=head->money;
		}
		float time=head->etime-head->stime;
		if(g->arcsT[find(*g,head->splace)][find(*g,head->eplace)]>time)
		{
			g->arcsT[find(*g,head->splace)][find(*g,head->eplace)]=time;
		}
		head=head->next;
	}
}
void enquiry()
{
	struct use *head;
	head=file();
	printf("|����\t|����\t\t|���\t|�յ�\t|����ʱ��\t|����ʱ��\t|Ʊ��\t|\n");
	if(head->next==NULL)  printf("|%s\t|%s\t\t|%s\t|%s\t|%f\t|%f\t|%d\t|\n",head->num,head->dat,head->splace,head->eplace,head->stime,head->etime,head->money);
	else
	while(head->next!=NULL)
	{
		printf("|%s\t|%s\t|%s\t|%s\t|%.2f\t\t|%.2f\t\t|%d\t|\n",head->num,head->dat,head->splace,head->eplace,head->stime,head->etime,head->money);
	    head=head->next;
	}
	main();
}
void statistics()
{
	int n=0,s,e,k=0;
	FILE *fp;
	struct use *p,*f,*head;
	char a[12],b[20],c[20];
	printf("�������ѯʱ�䣺");
	scanf("%s",a);
	printf("��������ʼ�أ�");
	scanf("%s",b);
	printf("������Ŀ�ĵأ�");
	scanf("%s",c); 
	p=f=(struct use *)malloc(sizeof(struct use));
	head=NULL;
	if((fp=fopen("file.txt","r"))==NULL)
	{
		printf("cannot open this file.\n");
		exit(0);
	}
    while(!feof(fp))
	{
		if(n==1) head=p;
		else f->next=p;
		f=p;
		p=(struct use *)malloc(sizeof(struct use));
		if(fread(p,sizeof(struct use),1,fp)!=EOF)   n++;
	}
	if(n==1) {p->next=NULL;head=p;}
	else
	{
	  f->next=p;
	  p->next=NULL;	
	}
	fclose(fp);
	printf("|����\t|����\t\t|���\t|�յ�\t|����ʱ��\t|����ʱ��\t|Ʊ��\t|\n");
	while(head->next!=NULL)
	{
		if((strcmp(a,head->dat)==0))
		{
			if((strcmp(b,head->splace)==0)&&strcmp(c,head->eplace)==0)
			{
			printf("|%s\t|%s\t|%s\t|%s\t|%.2f\t\t|%.2f\t\t|%d\t|\n",head->num,head->dat,head->splace,head->eplace,head->stime,head->etime,head->money);
			k=1;
			}
		}
		head=head->next;
	}
	if(k==0)  printf("                                      ������Ӧ������      \n");
	printf("��1������ѯ����0�������˵�\n");
	scanf("%d",&e);
	if(e==0)  main();
	else if(e==1)statistics();
	else 
	{
		printf("��Ч���֣�\n");
		main();
	}
}
void modifies()
{
	//�ļ�д��
	struct use *head,*head2;
	head=file();
	//�޸� 
	int e,s;
	char a[MaxSize],b[MaxSize];
	float ls;
	FILE *fp;
	head2=head;
	printf("������Ҫ�޸ĳ��Σ�");
	scanf("%s",a);
	printf("��ѡ��Ҫ�޸ĵ�����\n");
	printf("1.����\t2.��ʼʱ��\t3.����ʱ��\t4.��ʼ�ص�\t5.����ص�\t6.Ʊ��\n");
	printf("�����룺");
	scanf("%d",&e);
	printf("���޸ģ�");
	while(e>0||e<7)
	{
		if(e==6)
		{
			scanf("%d",&s);
			break;
		}
		if(e==2||e==3||e==6)
		{
			scanf("%f",&ls);
			break;
		}
		scanf("%s",b);break; 
	}
	while(head->next!=NULL)
	{ 
	    if(e==1)
	      if(strcmp(a,head->num)==0)  strcpy(head->dat,b);
		if(e==2)
		  if(strcmp(a,head->num)==0)  head->stime=ls;
		if(e==3)
		  if(strcmp(a,head->num)==0)  head->etime=ls;
		if(e==4)
		  if(strcmp(a,head->num)==0)  strcpy(head->splace,b);
		if(e==5)
		  if(strcmp(a,head->num)==0)  strcpy(head->eplace,b);
		if(e==6)
		  if(strcmp(a,head->num)==0)  head->money=s;
		head=head->next;
    }
   if((fp=fopen("file.txt","w"))==NULL)
	{
		printf("cannot open this file.\n");
		exit(0);
	}
	while(head2->next!=NULL)
	{
		fwrite(head2,sizeof(struct use),1,fp);
		head2=head2->next;
	}
	fclose(fp);  
	main();   
}
void del()
{
	FILE *fp;
	struct use *p,*f,*head;
	int n=0,s=0,b,c=0;
	char a[10];
	p=f=(struct use *)malloc(sizeof(struct use));
	head=NULL;
	if((fp=fopen("file.txt","r"))==NULL)
	{
		printf("cannot open this file.\n");
		exit(0);
	} 
    while(!feof(fp))
	{
		if(n==1) head=p;
		else f->next=p;
		f=p;
		p=(struct use *)malloc(sizeof(struct use));
		if(fread(p,sizeof(struct use),1,fp)!=EOF)   n++;
	}
	if(n==1) {p->next=NULL;head=p;}
	else
	{
	  f->next=p;
	  p->next=NULL;	
	}
	fclose(fp);
	printf("������Ҫɾ���ĳ��Σ�");
	scanf("%s",a); 
	p=f=(struct use *)malloc(sizeof(struct use));
	f=head;
	p=head;
	while(p->next!=NULL)
	{
		if(s>1)f=f->next;
		if(strcmp(p->num,a)==0)
		{
			c=1;
			printf("|����\t|����\t\t|���\t|�յ�\t|����ʱ��\t|����ʱ��\t|Ʊ��\t|\n");
			printf("|%s\t|%s\t|%s\t|%s\t|%.2f\t\t|%.2f\t\t|%d\t|\n",p->num,p->dat,p->splace,p->eplace,p->stime,p->etime,p->money);
			printf("��ȷ���Ƿ���ɾ����1.��    2.��\n");
			printf("�����룺");
			scanf("%d",&b);
			if(b==1)
			{
			  if(s==0)head=head->next;
			  if(s>0)f->next=p->next;
		      break;
			}
			else if(b==2)break;
			else
			{
				printf("��Ч���֣�\n");main();
			} 
		}
		p=p->next;
		s++;
	}
	if(c==0)printf("��ѯ������Ӧ����,�޷�ɾ����\n");
	if((fp=fopen("file.txt","wb"))==NULL)
	{
		printf("cannot open this file.\n");
		exit(0);
	}
	while(head->next!=NULL)
	{
		fwrite(head,sizeof(struct use),1,fp);
		head=head->next;
	}
	fclose(fp);  
	main(); 
}
void MDispath(Graph g,int dist[],int path[],int S[],char a[],int sp,int ep)
{
	//�ļ�д��
	struct use *head;
	head=file();
	//��� 
	int i,j,k;
	int apath[MaxSize],d;
	if(S[ep]==1&&ep!=sp)
	{
		d=0;
		apath[d]=ep;
		k=path[ep];
		if(k==-1)printf("��·��\n");
		else
		{
			while(k!=sp)
			{
				d++;
				apath[d]=k;
				k=path[k];
			}
			d++;
			apath[d]=sp;
			for(j=d;j>=1;j--)
				{
					while(head->next!=NULL)
					{
						if(strcmp(head->dat,a)==0&&strcmp(head->splace,g.list[apath[j]].name)==0&&strcmp(head->eplace,g.list[apath[j-1]].name)==0&&head->money==dist[apath[j-1]])
					{
						printf("|%s\t|%s\t|%s\t|%s\t|%.2f\t\t|%.2f\t\t|%d\t|\n",head->num,head->dat,head->splace,head->eplace,head->stime,head->etime,head->money);
						head=head->next;
						break;
					}
					head=head->next;
					}
				}
			/* 
			printf("%d",apath[d]);
			for(j=d-1;j>=0;j--)
			{
				printf(",%d",apath[j]);
			}
			*/
		}
	}
}
void TDispath(Graph g,float dist[],int path[],int S[],char a[],int sp,int ep)
{
	//�ļ�д��
	struct use *head;
	head=file(); 
	//��� 
	int i,j,k;
	int apath[MaxSize],d;
	if(S[ep]==1&&ep!=sp)
	{
		d=0;
		apath[d]=ep;
		k=path[ep];
		if(k==-1)printf("��·��\n");
		else
		{
			while(k!=sp)
			{
				d++;
				apath[d]=k;
				k=path[k];
			}
			d++;
			apath[d]=sp;
			for(j=d;j>=1;j--)
				{
					while(head->next!=NULL)
					{
						if(strcmp(head->dat,a)==0&&strcmp(head->splace,g.list[apath[j]].name)==0&&strcmp(head->eplace,g.list[apath[j-1]].name)==0&&head->etime-head->stime==dist[apath[j-1]])
					{
						printf("|%s\t|%s\t|%s\t|%s\t|%.2f\t\t|%.2f\t\t|%d\t|\n",head->num,head->dat,head->splace,head->eplace,head->stime,head->etime,head->money);
						head=head->next;
						break;
					}
					head=head->next;
					}
				}
		}
	}
}
void MDijkstra(Graph g,char a[],int sp,int ep)//������Ǯ 
{
	int dist[MaxSize],path[MaxSize];
	int S[MaxSize];//1��ʾ��S�У�0��ʾ���� 
	int mindist,i,j,u;
	for(i=0;i<g.number;i++)
	{
		dist[i]=g.arcsM[sp][i];
		S[i]=0;
		if(g.arcsM[sp][i]<INF)
		{
			path[i]=sp;
		}
		else
		{
			path[i]=-1;
		}
	}
	S[sp]=1;path[sp]=0;
	for(i=0;i<g.number-1;i++)
	{
		mindist=INF;
		for(j=0;j<g.number;j++)
		{
			if(S[j]==0&&dist[j]<mindist)
			{
				u=j;
				mindist=dist[j];
			}
		}
		S[u]=1;
		for(j=0;j<g.number;j++)
		{
			if(S[j]==0)
			{
				if(g.arcsM[u][j]<INF&&dist[u]+g.arcsM[u][j]<dist[j])
			{
			dist[j]=g.arcsM[u][j];
			path[j]=u;	
			}
				/*ԭ�汾 
			if(g.arcsM[u][j]<INF&&dist[u]+g.arcsM[u][j]<dist[j])
			{
			dist[j]=dist[u]+g.arcsM[u][j];
			path[j]=u;	
			}
			*/
			} 
		}
	}
	/*
	for(i=0;i<g.number;i++)
	{
		printf("%d,",dist[i]);
	}
	*/
	MDispath(g,dist,path,S,a,sp,ep);
}
void TDijkstra(Graph g,char a[],int sp,int ep)//������ʱ�� 
{
	int path[MaxSize];
	float dist[MaxSize];
	int S[MaxSize];//1��ʾ��S�У�0��ʾ���� 
	int i,j,u;
	float mindist;
	for(i=0;i<g.number;i++)
	{
		dist[i]=g.arcsT[sp][i];
		S[i]=0;
		if(g.arcsT[sp][i]<INF)
		{
			path[i]=sp;
		}
		else
		{
			path[i]=-1;
		}
	}
	S[sp]=1;path[sp]=0;
	for(i=0;i<g.number-1;i++)
	{
		mindist=INF;
		for(j=0;j<g.number;j++)
		{
			if(S[j]==0&&dist[j]<mindist)
			{
				u=j;
				mindist=dist[j];
			}
		}
		S[u]=1;
		for(j=0;j<g.number;j++)
		{
			if(S[j]==0)
			{
				if(g.arcsT[u][j]<INF&&dist[u]+g.arcsT[u][j]<dist[j])
			{
			dist[j]=g.arcsT[u][j];
			path[j]=u;	
			}
			} 
		}
	}
	/*
	for(i=0;i<g.number;i++)
	{
		printf("%.1f,",dist[i]);
	}
	*/
	TDispath(g,dist,path,S,a,sp,ep);
}
void minMoney(Graph g)
{
	//ͼ�Ĵ�����д�� 
	CreateGraph(&g);
	input(&g);
	//����
	char a[12],b[20],c[20];
	printf("�������ѯ���ڣ�");
	scanf("%s",a);
	printf("��������ʼ�أ�");
	scanf("%s",b);
	printf("������Ŀ�ĵأ�");
	scanf("%s",c); 
	//��� 
	printf("|����\t|����\t\t|���\t|�յ�\t|����ʱ��\t|����ʱ��\t|Ʊ��\t|\n");
	//�Ͻ�˹�����㷨 
	MDijkstra(g,a,find(g,b),find(g,c));
	main();
}
void minTime(Graph g)
{
	//ͼ�Ĵ�����д�� 
	CreateGraph(&g);
	input(&g); 
	//����
	char a[12],b[20],c[20];
	printf("�������ѯ���ڣ�");
	scanf("%s",a);
	printf("��������ʼ�أ�");
	scanf("%s",b);
	printf("������Ŀ�ĵأ�");
	scanf("%s",c);  
	//��� 
	printf("|����\t|����\t\t|���\t|�յ�\t|����ʱ��\t|����ʱ��\t|Ʊ��\t|\n");
	//�Ͻ�˹�����㷨 
	TDijkstra(g,a,find(g,b),find(g,c));
	main();
}
void FindPath(Graph g,int u,int v,int path[],int d,int visited[],int allpath[],int *number)
//d �ǵ���ǰΪֹ���߹���·������,����ʱ��ֵΪ-1
{ 
	int w,i;
	int index=0;
	d++; //·�������� 1
	path[d]=u; //����ǰ������ӵ�·����
	visited[u]=1; //���ѷ��ʱ��
	if (u==v) //�ҵ�һ��·�������
	{
		for(i=0;i<=d;i++)
		{
			allpath[*number]=path[i];
			//printf("%d ",path[i]);
			*number=*number+1;//���ʹ��ָ�����������ʹ��++���� 
		}
		//printf("\n");
		visited[u]=0;
		return;
	}
	while(g.arcsM[u][index]==INF)
		{
			index++;
		}
	while(index<g.number)
	{
		w=index;
		if(visited[w]==0) //��w����δ����,�ݹ������
			FindPath(g,w,v,path,d,visited,allpath,number);
		index++;
		while(g.arcsM[u][index]==INF)
		{
			index++;
		}
	}
	visited[u]=0; //�ָ�����,ʹ�ö��������ʹ��
}
void sortindex(float a[],int b[],int n)
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		j=0;
		while(j<i&&a[i]>a[b[j]])//�ҵ�a[i]С��a[b[j]]��λ�� 
		{
			j++;
		}
		for(k=i;k>j;k--)//����֮���λ��,�����ֺ���һλ 
		{
			b[k]=b[k-1];
		}
		b[j]=i;
	}
}
void findallpath(Graph g)
{
	//ͼ�Ĵ�����д�� 
	CreateGraph(&g);
	input(&g);
	//�ļ�д�� 
	struct use *head;
	head=file();
	//���� 
	char a[20],b[20];
	printf("��������ʼ�أ�");
	scanf("%s",a);
	printf("������Ŀ�ĵأ�");
	scanf("%s",b); 
	//
	int path[MaxSize],visited[MaxSize],allpath[MaxSize];
	int i,j;
	for(i=0;i<g.number;i++)
	{
		visited[i]=0;
	}
	int number=0; 
	FindPath(g,find(g,a),find(g,b),path,-1,visited,allpath,&number); 
	int allpathD[MaxSize][MaxSize];//��ά��allpath����
	for(i=0;i<MaxSize;i++)
	{
		for(j=0;j<MaxSize;j++)
		{
			allpathD[i][j]=-1;//ȫ����ʼ��Ϊ-1 
		}
	}
	float time[MaxSize];
	int pathindex;//allpathD������0�������� 
	int index=-1;//time������0�������� 
	for(i=0;i<number;i++)
	{
		if(allpath[i]==0)
		{
			pathindex=0;
			index++;
			time[index]=0;
			allpathD[index][pathindex]=allpath[i]; 
		}
		else
		{
			pathindex++;
			allpathD[index][pathindex]=allpath[i]; 
			time[index]+=g.arcsT[allpath[i-1]][allpath[i]];
		}
	}
	int sort[index+1];//sort�д���time�д�С����ı�� 
	for(i=0;i<=index;i++)
	{
		sort[i]=i;
	}
	sortindex(time,sort,index+1);
	//��� 
	for(i=0;i<=index;i++)
	{
		j=0;
		printf("%s",g.list[allpathD[sort[i]][j]].name);
		j++;
		while(allpathD[sort[i]][j]!=-1)
		{
			printf("==%s",g.list[allpathD[sort[i]][j]].name);
			j++;
		}
		printf("	����ʱ��Ϊ%.1fh",time[sort[i]]);
		printf("\n");
	}
	struct use *head2;
	printf("|����\t|����\t\t|���\t|�յ�\t|����ʱ��\t|����ʱ��\t|Ʊ��\t|\n");
	for(i=0;i<=index;i++)
	{
		j=0;
		while(allpathD[sort[i]][j+1]!=-1)
		{
			head2=head;
			while(head2->next!=NULL)
		{
			if(strcmp(head2->splace,g.list[allpathD[sort[i]][j]].name)==0&&strcmp(head2->eplace,g.list[allpathD[sort[i]][j+1]].name)==0&&head2->etime-head2->stime==g.arcsT[allpathD[sort[i]][j]][allpathD[sort[i]][j+1]])
			{
			printf("|%s\t|%s\t|%s\t|%s\t|%.2f\t\t|%.2f\t\t|%d\t|\n",head2->num,head2->dat,head2->splace,head2->eplace,head2->stime,head2->etime,head2->money);
			head2=head2->next;
			break;
			}
		head2=head2->next;
		}
		j++;
		}
		printf("=================================================================================\n");
	}
	main();
}
void neartimepath()
{
	//�ļ�д��
	struct use *head,*head2;//head2���ڼ�¼���ʱ��ĳ��� 
	head=file();
	//����
	int s=0;//�����ж��Ƿ���ҵ����� 
	char a[MaxSize],b[MaxSize],c[MaxSize];
	float currentTime;
	printf("�����뵱ǰʱ��: ");
	scanf("%f",&currentTime);
	while(currentTime<0||currentTime>24)
	{
		printf("������ĵ�ǰʱ����������������:");
		scanf("%f",&currentTime);
	}
	printf("�������ѯ���ڣ�");
	scanf("%s",a);
	printf("��������ʼ�أ�");
	scanf("%s",b);
	printf("������Ŀ�ĵأ�");
	scanf("%s",c);
	//����
	float mindist=INF;
	while(head->next!=NULL)
	{
	float time=head->stime-currentTime;
	if(strcmp(head->dat,a)==0&&strcmp(head->splace,b)==0&&strcmp(head->eplace,c)==0)
	{
		if(head->stime>currentTime)
		{
			s=1;
			if(time<mindist)
			{ 
				mindist=time;
				head2=head;
			}
		}
	}
	head=head->next;	
	}
	//���
	if(s==0)
	{
		printf("������س���\n");
	}
	if(s==1)
	{
		printf("|����\t|����\t\t|���\t|�յ�\t|����ʱ��\t|����ʱ��\t|Ʊ��\t|\n");
		printf("|%s\t|%s\t|%s\t|%s\t|%.2f\t\t|%.2f\t\t|%d\t|\n",head2->num,head2->dat,head2->splace,head2->eplace,head2->stime,head2->etime,head2->money);
	}
	main();
}
int main()
{
	int n,m;
	Graph g;
	printf("��·����ϵͳ\n");
	printf("1.����Ϣ¼��\n");
	printf("2.��ʾ�𳵳�����Ϣ\n");
	printf("3.��ѯ��վ��Ϣ\n");
	printf("4.�޸ĳ�����Ϣ\n");
	printf("5.ɾ��������Ϣ\n");
	printf("6.��ѯ�����м���ʡǮ�Ĵ�˷�ʽ\n");
	printf("7.��ѯ�����м���ʡʱ��Ĵ�˷�ʽ\n");
	printf("8.Ѱ����������֮�����п��Բ��õĴ�˷�ʽ\n");
	printf("9.��ѯ����췢�����г���������Ϣ\n");
	printf("10.�˳�ϵͳ\n");
	printf("11.debug\n");
	printf("���Ƚ��л���Ϣ¼�룬��ִ����������\n");
	printf("��������룺");
	scanf("%d",&n);
	if(n>0&&n<12)
	{
	  if(n==1)
	  {
	  	printf("�ı���ʼ��������1���ֶ�����������2\n");
	  	scanf("%d",&m);
	  	if(m==1)init();
	  	if(m==2)luru();
	  	if(m<1&&m>2)
	  	{
	  	  printf("�����������Ч���֣����������룡\n");
		  main();
		}
	  }
	  if(n==2)enquiry();
	  if(n==3)statistics();
	  if(n==4)modifies();
	  if(n==5)del();
	  if(n==6)minMoney(g);
	  if(n==7)minTime(g);
	  if(n==8)findallpath(g);
	  if(n==9)neartimepath();
	  if(n==10)
	  {
	  	printf("��л����ʹ��\n");
	  	return 0;
	  }
	  if(n==11)
	  {
	  	CreateGraph(&g);
	  	input(&g);
	  	print(g);
	  	main();
	  }
	}
	else
	{
		printf("�����������Ч���֣����������룡\n");
		main();
	}
}
