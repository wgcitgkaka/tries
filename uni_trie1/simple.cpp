#include "simple.h"

void Simple::init_Memory(meNode &M)
{
     M = new Memory();                           //����һ���ṹ�� 
     M->ldata = M->rdata = -1;                   //�����Ӵ洢����һ����ϢΪ�� 
     M->lchild = M->rchild = NULL;               //�����Ӵ洢��Ϊ�� 
}

void Simple::insert_Memory(meNode &M)
{
     meNode m;                                   //�������洢����ָ�� 
     FILE *file; 
     char buffer[BUFFER_SIZE];
     char prefix[PREFIX_SIZE];
     char *p,*q;                                 //�����ļ�ʱ���ַ���ָ�� 
     int hop,temp;                               //��һ����Ϣ��nodes�����־�� 
     
     nodes[0] = 1;                               //���洢��ֻ��һ�� 
     for(temp=1;temp<PREFIX_SIZE;temp++)         //��ʼ��nodes���� 
     {
         nodes[temp] = 0;                               
     } 
     
     file = fopen("test.txt","r");               //��ֻ����ʽ��txt�ļ�
     while(feof(file) == 0)                       //����ļ����ݲ�Ϊ�� 
     {
         m = M;
         temp = 0;             
         fgets(buffer,BUFFER_SIZE,file);          //��fileָ��ָ��Ĵ�СΪBUFFER_SIZE�����ݶ��뵽buffer������ 
         sscanf(buffer,"%s %d",prefix,&hop);      //��buffer�ַ������е�һ�����ַ���ʽ����prefix���飬�ڶ��������ʹ���hop���� 
                                                  //%s %d�м䲻���ж���! 
         p = prefix;                              //����ǰ׺
         while(*p != '\0') 
         {
              q = p;
              q++;
              if((*p == '0')&&(*q != '\0'))       //��ǰ�ַ�Ϊ0�һ�����һλ�ַ�
              {
                 if(m->lchild == NULL)            //���Ӵ洢�鲻����
                 {
                     init_Memory(m->lchild);   
                     m = m->lchild;
                     temp++;                      //����洢����һ�� 
                     nodes[temp]++;               //�ò�洢������1 
                 } 
                 else
                 {
                     m = m->lchild;
                     temp++;
                 } 
              } 
              else if((*p == '1')&&(*q != '\0'))  //��ǰ�ַ�Ϊ1�һ�����һλ�ַ�
              {
                 if(m->rchild == NULL)            //���Ӵ洢�鲻����
                 {
                     init_Memory(m->rchild);   
                     m = m->rchild;
                     temp++;                      //����洢����һ�� 
                     nodes[temp]++;               //�ò�洢������1 
                 } 
                 else
                 {
                     m = m->rchild;
                     temp++;
                 } 
              } 
              
              if(*q == '\0')                      //��һλΪ�գ���ǰΪǰ׺���һλ 
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
                    printf("ǰ׺�����в�Ϊ0��1���ַ�!\n"); 
                 }
              }
              
              p++;                                //������һλ
         } 
     }
     fclose(file);                                //�ͷ�file�ļ�ָ�� 
     
     /*for(temp=0;temp<PREFIX_SIZE;temp++)        //���nodes���� 
     {
         //if(nodes[temp] != 0)                               
         printf("%d ",nodes[temp]); 
         if((temp+1)%8 == 0)
            printf("\n");                              
     }*/
}

void Simple::leafPush_Memory(meNode &M)           //Ҷ�� 
{
     meNode m = M;
     if(m != NULL)
     {
          if(m->lchild != NULL)                   //�����Ӵ洢�飬ldata�����Ƹ�û����Ϣ��ldata��rdata 
          {
             if(m->lchild->ldata == -1)
                m->lchild->ldata = m->ldata;
             if(m->lchild->rdata == -1)
                m->lchild->rdata = m->ldata;            
          }
          if(m->rchild != NULL)                   //�����Ӵ洢�飬rdata�����Ƹ�û����Ϣ��ldata��rdata 
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

void Simple::push_Memory(meNode &M)                //�����Ӵ洢��Ĵ洢�����һ����Ϣ��Ϊ-1 
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
     }                                              //-1������������ֻ��ָ����Ϣ�ĵط������п�����Ҷ�Ӵ洢���ϣ�test2�� 
}

void Simple::group_Memory()
{
     int i,j,k,l,t; 
     
     int param[PREFIX_SIZE][FLOOR_SIZE];            //����洢�����Ķ�ά���� ��param[a][b]��ʾ�ѵ������ĵ�a���Ӧ���ಽ���ĵ�[b]����Ҫ�Ķಽ������ 
     int temp[FLOOR_SIZE+1];                        //��¼��Щ���Ƿֲ�� 
     
     for(i=0;i<PREFIX_SIZE;i++)                     //��ά���ʼ�� 
     {
         for(j=0;j<FLOOR_SIZE;j++)
         {
             param[i][j] = -2;                     
         }                      
         printf("\n");
     }
                                                    //��ά���߽�ֵ
     for(i=0;i<FLOOR_SIZE;i++)                      //�ѵ�i���Ӧ����i�� 
     {
         if(nodes[i] == 0)                          //�ò�û�д洢�飬����Ҳû�д洢���ˣ���ʼ������ ,����С����ʹ�� 
         {
            break;        
         } 
         for(j=i,k=0;j>=0;j--)          
         {
             k = nodes[j] + k;                      //����k��Ϊֹ���ܹ��ж��ٴ洢�� 
         }  
         param[i][i] = 2 * k;                       //��������i���Ӧ���ಽ����i�����2���洢���� 
     }
     for(i=1;i<PREFIX_SIZE;i++)                     //��ǰi���Ӧ����1�� 
     {
         param[i][0] =  nodes[0] * pow(i+1);        //ǰi�����2��2��i�η�,2*nodes[0]*pow[i]          
     } 
     
     for(j=1;j<FLOOR_SIZE;j++)                      //���Ƹ�ֵ 
     {
         for(i=j+1;i<PREFIX_SIZE;i++)                //ǰi���Ӧ����j���൱��ǰi-1���Ӧ����j-1�㣬��i���Ӧ����j�� 
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
         if(nodes[i] == 0)                          //�ò�û�д洢�飬����Ҳû�д洢���ˣ���ʼ������ ,����С����ʹ�� 
         {
            break;        
         }
     } 
     temp[FLOOR_SIZE] = i-1;
     temp[0] = -1;
     
     
     
     for(i=FLOOR_SIZE-1;i>0;i--)
     {
           t = param[temp[i+1]][i];                 //���Ž��t,��������·�� 
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
         
     /*for(i=0;i<PREFIX_SIZE;i++)                   //�����ά�� 
     {
         if(nodes[i] == 0)                          //�ò�û�д洢�飬����Ҳû�д洢���ˣ���ʼ������ ,����С����ʹ�� 
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
