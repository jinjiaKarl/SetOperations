#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
// 函数返回值
#define  OK  1
#define  ERROR  0
#define  TRUE   1
#define  FALSE  0
#define INFEASIBLE  -1  infeasible
#define  OVERFLOW  -2
#define  NULL   0
#define LIST_INIT_SIZE  27   //顺序表的初始大小


typedef  int   Status;      //返回状态类型
typedef  char  ElemType;   //元素类型


typedef struct{
    ElemType  *elem;
    int       length;
    int       listsize;
}SqList;   

Status InitList(SqList &l)
{
    //初始化顺序表
    l.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!l.elem)   exit(OVERFLOW);
    l.length=0;
    l.listsize=LIST_INIT_SIZE;
    return OK;
}


int ListLength(SqList l)
{
    //求顺序表的长度
    return(l.length);
}

Status ListInsert_Sq(SqList &L,int i, ElemType e)
{
    //在顺序表L的第i个位置前插入元素e,i的合法值为1..L.length+1
    if(i<1||i>L.length+1)
        return ERROR;
    ElemType *q=&L.elem[i-1];
    *q=e;
    ++L.length;
    return OK;
}

Status CreatSqList(SqList &l,ElemType a[],int n)
{   
    //创建顺序表 
    int len=ListLength(l);
    for(int i=0;i<n;i++)
    {
        if(a[i]>='a'&&a[i]<='z')
            ListInsert_Sq(l,++len,a[i]);
    }
    return OK;
}

Status GetElem(SqList L,int i,ElemType &e)
{
    // 返回顺序表中元素
    if(i<=0||i>L.length)
        return ERROR;
    else
        e=*(L.elem+i-1);
    return OK;
}

Status equal(ElemType e1,ElemType e2)
{   
    //判断两个集合是否相等
    if(e1==e2)
        return TRUE;
    else
        return FALSE;
}

int LocateElem_Sq(SqList L, ElemType e,  Status (*compare)(ElemType,ElemType))
{   
    //返回元素对应的下标，传入函数的指针
    ElemType *p=L.elem;   //p指向第一个元素
    int i=1;     //i始终为p所指向元素的位序
    while(i<=L.length&&!(*compare)(*p++,e))
        ++i;
    if(i<=L.length)
        return(i);
    else
        return 0;
}

Status ListDelete(SqList &L,int i,ElemType &e)
{
    //在顺序表Ｌ中删除第ｉ个元素，用ｅ返回其值．
    if(i<1||i>L.length)
        return ERROR;//删除位置不合理
    ElemType *p=&L.elem[i-1],*q=L.elem+L.length-1;
    e=*p;
    while(p<q){*p=*(p+1); ++p;}  //删除位置后的元素左移
    --L.length;
    return OK;
}

void Union(SqList &La,SqList Lb)
{
    //将所有在线性表Lb中而不在La中的元素插入La
    int  la_len , lb_len;
    ElemType e;
    la_len=ListLength(La);
    lb_len=ListLength(Lb);
    for(int i=1;i<=lb_len;++i)
    {
        GetElem(Lb,i,e);
        if(LocateElem_Sq(La,e,equal)==0)
            ListInsert_Sq(La,++la_len,e);
    }
}




Status Intersection(SqList l1,SqList l2, SqList &l3)
{
    //求集合的交集
    int l1_len, l2_len,l3_len,i=1,j=1;
    ElemType  e,u;
    l1_len=ListLength(l1);
    l2_len=ListLength(l2);
    l3_len=ListLength(l3);
    for(i=1;i<=l1_len;i++)
    {
        GetElem(l1,i,e);
        for(j=l2_len;j>=1;j--)
        {
            GetElem(l2,j,u);
            if(e==u)
                {
                    ListInsert_Sq(l3,++l3_len,u);
                    break;
                }
            else
                continue;
        }
    }   
    return OK;
}



Status  Difference(SqList &l1,SqList l2)
{
    //求顺序表的差集，A-B=(AUB)-(AUB)B
    SqList lc;
    int  count=0,lc_len,l1_len,l2_len;
    ElemType e,u,f;
    InitList(lc);
    Intersection(l1,l2,lc);
    lc_len=ListLength(lc);
    l1_len=ListLength(l1);
    l2_len=ListLength(l2);
    for(int i=1;i<=lc_len;i++)
    {
        GetElem(lc,i,e);
        for(int j=1;j<=l1_len;j++)
        {
            GetElem(l1,j,u);
            if(u==e)
            {
                ListDelete(l1,j,f);
            }
        }
    }
    return  OK;
}

void Outputlist(SqList &L)
{   
    ElemType temp;
    if(0==L.length)
        printf("空集!");
    else
    {   
        //冒泡排序
       for(int i=0;i<L.length-1;++i){
            for(int j=0;j<L.length-i-1;++j){
                if(*(L.elem+j) > *(L.elem+j+1)){
                temp=*(L.elem+j);
                *(L.elem+j)=*(L.elem+j+1);
                *(L.elem+j+1)=temp;
            }
            }
        }
        //排序之后输出
        for(int i=0;i<L.length;++i)
        {

            printf("%c",*(L.elem+i));
        }
     }

}

//程序的主函数
int main()
{
    system("@title  集合的并交叉运算");
    for(1;;)
    {
        int c;
        printf("****************************************************************\n");
        printf("        ######## 执行程序: 1             ######## 退出程序: 2\n");
        printf("****************************************************************\n");
        printf("请按键选择: ");
        scanf("%d",&c);
        getchar(); //去除掉换行符
        printf("\n");
        if(c==1)
        {
            SqList  l1,l2,l3;
            int n1,n2,i,j;
            ElemType a1[30], a2[30];
            InitList(l1);
            InitList(l2);
            InitList(l3);
            printf("请输入第一个长度小于27的集合: ");
            gets(a1);
            n1=strlen(a1);
            //对长度进行判断
            while(n1>=27){
                printf("输入长度大于27，请输入长度小于27的集合：");
                gets(a1);
                n1=strlen(a1);

            }
            //从最后一个开始依次与前面的比较 重复赋值为0，判读输入是否有重复的
            for(i=n1-1;i>=0;i--)  
            {
                for(j=0;j<i;j++)
                {
                    if(a1[j]==a1[i])
                        a1[i]=0;
                }
            }
            CreatSqList(l1,a1,n1);
            printf("请输入第二个长度小于27集合: ");
            gets(a2);
            n2=strlen(a2);
            //对长度进行判断
            while(n2>=27){
                printf("输入长度大于27，请输入长度小于27的集合：");
                gets(a2);
                n2=strlen(a2);

            }
            for(i=n2-1;i>=0;i--)  
            {
                for(j=0;j<i;j++)
                {
                    if(a1[j]==a1[i])
                        a1[i]=0;
                }
            }
            CreatSqList(l2,a2,n2);
            printf("集合的交集是: ");
            Intersection(l1,l2,l3);
            Outputlist(l3);
            printf("\n");
            printf("集合的并集是: ");
            Union(l1,l2);
            Outputlist(l1);
            printf("\n");   
            printf("集合的差集是: ");
            Difference(l1,l2);
            Outputlist(l1);
            printf("\n\n*****************按*任*意*键*清*屏!********************");
            system("pause>null");
            system("cls");
        }
        else
            exit(0);
    }
    return 0;
}
