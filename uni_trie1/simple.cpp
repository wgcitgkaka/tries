#include "simple.h"

void Simple::init_Memory(meNode &M)
{
     M = new Memory();                           //生成一个结构体 
     M->ldata = M->rdata = -1;                   //左右子存储块下一跳信息为空 
     M->lchild = M->rchild = NULL;               //左右子存储块为空 
}

void Simple::insert_Memory(meNode &M)
{
     meNode m;                                   //单步长存储块型指针 
     FILE *file; 
     char buffer[BUFFER_SIZE];
     char prefix[PREFIX_SIZE];
     char *p,*q;                                 //读入文件时的字符型指针 
     int hop,temp;                               //下一跳信息和nodes数组标志量 
     
     nodes[0] = 1;                               //根存储块只有一个 
     for(temp=1;temp<PREFIX_SIZE;temp++)         //初始化nodes数组 
     {
         nodes[temp] = 0;                               
     } 
     
     file = fopen("test.txt","r");               //以只读方式打开txt文件
     while(feof(file) == 0)                       //如果文件内容不为空 
     {
         m = M;
         temp = 0;             
         fgets(buffer,BUFFER_SIZE,file);          //将file指针指向的大小为BUFFER_SIZE的内容读入到buffer数组中 
         sscanf(buffer,"%s %d",prefix,&hop);      //将buffer字符数组中第一串以字符格式存入prefix数组，第二串以整型存入hop变量 
                                                  //%s %d中间不能有逗号! 
         p = prefix;                              //读入前缀
         while(*p != '\0') 
         {
              q = p;
              q++;
              if((*p == '0')&&(*q != '\0'))       //当前字符为0且还有下一位字符
              {
                 if(m->lchild == NULL)            //左子存储块不存在
                 {
                     init_Memory(m->lchild);   
                     m = m->lchild;
                     temp++;                      //进入存储块下一层 
                     nodes[temp]++;               //该层存储块数加1 
                 } 
                 else
                 {
                     m = m->lchild;
                     temp++;
                 } 
              } 
              else if((*p == '1')&&(*q != '\0'))  //当前字符为1且还有下一位字符
              {
                 if(m->rchild == NULL)            //右子存储块不存在
                 {
                     init_Memory(m->rchild);   
                     m = m->rchild;
                     temp++;                      //进入存储块下一层 
                     nodes[temp]++;               //该层存储块数加1 
                 } 
                 else
                 {
                     m = m->rchild;
                     temp++;
                 } 
              } 
              
              if(*q == '\0')                      //下一位为空，当前为前缀最后一位 
              {
                 if(*p == '0')          
                 {
                    m->ldata = hop;   
                 }   
                 else if(*p == '1')
                 {
                    m->rdata = hop;  
                 }
                 else
                 {
                    printf("前缀表集中有不为0、1的字符!\n"); 
                 }
              }
              
              p++;                                //读入下一位
         } 
     }
     fclose(file);                                //释放file文件指针 
     
     /*for(temp=0;temp<PREFIX_SIZE;temp++)        //输出nodes数组 
     {
         //if(nodes[temp] != 0)                               
         printf("%d ",nodes[temp]); 
         if((temp+1)%8 == 0)
            printf("\n");                              
     }*/
}

void Simple::leafPush_Memory(meNode &M)           //叶推 
{
     meNode m = M;
     if(m != NULL)
     {
          if(m->lchild != NULL)                   //有左子存储块，ldata往下推给没有信息的ldata，rdata 
          {
             if(m->lchild->ldata == -1)
                m->lchild->ldata = m->ldata;
             if(m->lchild->rdata == -1)
                m->lchild->rdata = m->ldata;            
          }
          if(m->rchild != NULL)                   //有右子存储块，rdata往下推给没有信息的ldata，rdata 
          {
             if(m->rchild->ldata == -1)
                m->rchild->ldata = m->rdata;
             if(m->rchild->rdata == -1)
                m->rchild->rdata = m->rdata;            
          }
          leafPush_Memory(m->lchild);
          leafPush_Memory(m->rchild);
     }
     push_Memory(M);
}

void Simple::push_Memory(meNode &M)                //将有子存储块的存储块的下一跳信息变为-1 
{
     meNode m = M;
     if(m != NULL)
     {
          if(m->lchild != NULL)
             m->ldata = -1;
          if(m->rchild != NULL)
             m->rdata = -1;
          /*if((m->lchild == NULL)&&(m->ldata == -1))
             m->ldata = 0;
          if((m->rchild == NULL)&&(m->rdata == -1))
             m->rdata = 0;   */
          push_Memory(m->lchild);
          push_Memory(m->rchild);  
     }                                              //-1不仅仅出现在只有指针信息的地方，还有可能在叶子存储块上（test2） 
}

void Simple::group_Memory()
{
     int i,j,k,l,t; 
     
     int param[PREFIX_SIZE][FLOOR_SIZE];            //计算存储开销的二维数组 ，param[a][b]表示把单步长的第a层对应到多步长的第[b]层需要的多步长开销 
     int temp[FLOOR_SIZE+1];                        //记录哪些层是分层点 
     
     for(i=0;i<PREFIX_SIZE;i++)                     //二维表初始化 
     {
         for(j=0;j<FLOOR_SIZE;j++)
         {
             param[i][j] = -2;                     
         }                      
         printf("\n");
     }
                                                    //二维表赋边界值
     for(i=0;i<FLOOR_SIZE;i++)                      //把第i层对应到第i层 
     {
         if(nodes[i] == 0)                          //该层没有存储块，其下也没有存储块了，初始化结束 ,测试小数据使用 
         {
            break;        
         } 
         for(j=i,k=0;j>=0;j--)          
         {
             k = nodes[j] + k;                      //到第k层为止，总共有多少存储块 
         }  
         param[i][i] = 2 * k;                       //单步长第i层对应到多步长第i层就是2倍存储块数 
     }
     for(i=1;i<PREFIX_SIZE;i++)                     //把前i层对应到第1层 
     {
         param[i][0] =  nodes[0] * pow(i+1);        //前i层就是2倍2的i次方,2*nodes[0]*pow[i]          
     } 
     
     for(j=1;j<FLOOR_SIZE;j++)                      //递推赋值 
     {
         for(i=j+1;i<PREFIX_SIZE;i++)                //前i层对应到第j层相当于前i-1层对应到第j-1层，第i层对应到第j层 
         {
             param[i][j] = param[i-1][j-1] + nodes[i] * 2;   
             k = i-1;
             l = 1; 
             while(k>j-1) 
             {
                k--;
                t = param[k][j-1] + nodes[i-l] * pow(l+1);
                if(t < param[i][j])
                {
                    param[i][j] = t;  
                }     
                l++;          
             }                  
         }                     
     }
     for(i=0;i<PREFIX_SIZE;i++)
     {
         if(nodes[i] == 0)                          //该层没有存储块，其下也没有存储块了，初始化结束 ,测试小数据使用 
         {
            break;        
         }
     } 
     temp[FLOOR_SIZE] = i-1;
     temp[0] = -1;
     
     
     
     for(i=FLOOR_SIZE-1;i>0;i--)
     {
           t = param[temp[i+1]][i];                 //最优结果t,回溯它的路径 
           j = temp[i+1];
           k = i-1;
           l = 1;
           while(t < (param[j-1][k] + nodes[j] * pow(l)))
           {
                 j--; 
                 l++;                       
           }
           temp[i] = j-1;   
           //printf("%d\n",temp[i]);          
     } 
     
     for(i=1;i<=FLOOR_SIZE;i++)
     {
           floor[i-1] = temp[i] - temp[i-1];
           printf("%d ",floor[i-1]);                    
     }
     printf("\n");   
         
     /*for(i=0;i<PREFIX_SIZE;i++)                   //输出二维表 
     {
         if(nodes[i] == 0)                          //该层没有存储块，其下也没有存储块了，初始化结束 ,测试小数据使用 
         {
            break;        
         }                                         
         for(j=0;j<FLOOR_SIZE;j++)
         {
             printf("%d ",param[i][j]);                     
         }                      
         printf("\n");
     }*/
}

void Simple::print_Memory(meNode M)
{
     if(M != NULL)
     {
          printf("%d %d\n",M->ldata,M->rdata);
          print_Memory(M->lchild);
          print_Memory(M->rchild);
     }
}

int Simple::pow(int n)
{
    if(n == 0)
       return 1;
    else 
       return 1<<n;      
}
