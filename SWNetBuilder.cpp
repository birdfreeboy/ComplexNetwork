//STL C++ include files
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <numeric>


using namespace std;
//STL C++ include files








// define const number
#define INFINITY  INT_MAX   	
#define MAX_VERTEX_NUM 100000 //最大顶点个数> 30000000, 三千万个节点
// define const number   






// Define Node Type
typedef struct Node
{
	   int  NodeID;				// Node ID
       int  NodeStatus;			// Node Status
	   int  NodePreStatus;      // NOde Previous Status;
	   vector<int> AdjMember;   //Adjacent Member ID List 
	   int  NodeFlag;           // Node Flag bit
   }Node;
// Define Node Type






// Define Global Variable
Node TmpNode;
Node Nodes[MAX_VERTEX_NUM];  //Nodes is Nodes of the Network,  TmpNode is temp used Node.
ofstream  Networkfile, SWNetfile, degreefile;

// Define Global Variable



// Define Interface Function

void InitEvirom( int );    // Define Initial Environment Function

void RegNetBulider( int );  //Define Regular Network Builder 

void CreateRandomRoot(void);  

void SWNetBuilder(int,int,double);

// Define Interface Function 



//随机数根
void CreateRandomRoot(void)
{

	srand((unsigned) time(0));
	
}
//随机数根




void InitEvirom (int NetworkSizes)
{
	   
	for (int i=0; i<NetworkSizes; i++) {
	Nodes[i].NodeID=i;
	Nodes[i].NodePreStatus=0;
	Nodes[i].NodeStatus=0;
	Nodes[i].NodeFlag=0;
	}

}





//Create RegularNet	
void RegNetBulider(int NetworkSizes, int reg_k)	
{
	
	
	for(int i=0;i<NetworkSizes;i++)
	{
		
		for(int j=1;j<=reg_k/2;j++)
		{
			if(i+j<NetworkSizes)
			{
				Nodes[i].AdjMember.push_back(i+j);
			}
			else 
			{
				Nodes[i].AdjMember.push_back(i+j-NetworkSizes);
			}
			
		}
		
		for(j=1;j<=reg_k/2;j++)
		{
			if(i-j>=0)
			{
				Nodes[i].AdjMember.push_back(i-j);
			}
			else 
			{
				Nodes[i].AdjMember.push_back(i-j+NetworkSizes);
			}
		}
	}
	

	
for(int j=0;j<NetworkSizes;j++)   //排序
	{
		sort( Nodes[j].AdjMember.begin() , Nodes[j].AdjMember.end() );
	}
	
	

// 输入到文件中


Networkfile.open("RegNet_DATA.txt");
Networkfile<<"#Regular Network Bulider"<<endl;
Networkfile<<"NETWORKSIZES"<<endl;
Networkfile<<NetworkSizes<<endl;
Networkfile<<"#Adjacent Members="<<reg_k<<endl;
Networkfile<<"#NodeID"<<'\t'<< "Adjacent Members" <<'\t'<<'\t' <<endl;
Networkfile<<" "<<endl;
Networkfile<<"DATA"<<endl;


	for( i=0;i<NetworkSizes;i++)        //打印节点
	{
		Networkfile<<i<<'\t';
		for(int j=0;j<reg_k;j++)
		{
			Networkfile<<Nodes[i].AdjMember[j]<<'\t';
		}
		Networkfile<<endl;
	}

	// 输入到文件中
	
}

//Create RegularNet






//Create SWNet

void SWNetBuilder(int NetworkSizes, int reg_k,double prob_link=0.05)
{
   
   CreateRandomRoot();

   double rnd;
   rnd=rand()*1.0/RAND_MAX*1.0;

   for (int i=0; i<NetworkSizes; i++)
   {
       if (i< reg_k/2)
	   {
          for (int j=i+reg_k/2+1; j<NetworkSizes-reg_k/2+i; j++)
          {

			  rnd=rand()*1.0/RAND_MAX*1.0;
	     	  if (rnd<prob_link)
			  {
				  Nodes[i].AdjMember.push_back(j);
				  Nodes[j].AdjMember.push_back(i);
			  }
          }
        
	   }
	   else
	   {
          for(int jj =i+reg_k/2+1;jj<NetworkSizes;jj++)
		  {
			  rnd=rand()*1.0/RAND_MAX*1.0;
			  if (rnd<prob_link)
			  {
				  Nodes[i].AdjMember.push_back(jj);
				  Nodes[jj].AdjMember.push_back(i);
			  }


		  }
	   }

   }


   SWNetfile.open("SWNet_DATA.txt");
   SWNetfile<<"#Small World Network Bulider"<<endl;
   SWNetfile<<"NETWORKSIZES"<<endl;
   SWNetfile<<NetworkSizes<<endl;
   SWNetfile<<"#Based Regular Network Adjacent Members="<<reg_k<<endl;
   SWNetfile<<"#NodeID"<<'\t'<< "Adjacent Members" <<'\t'<<'\t'<<endl;
   SWNetfile<<" "<<endl;
   SWNetfile<<"DATA"<<endl;
   
   
   for( i=0;i<NetworkSizes;i++)        //打印节点
   {
	   
	   SWNetfile<<i<<'\t';
	   for(vector<int>::iterator iter=Nodes[i].AdjMember.begin();iter!=Nodes[i].AdjMember.end();++iter)
	   {
		   SWNetfile<<(*iter)<<'\t';
	   }
	    
	   SWNetfile<<" "<<endl;

   }
   

// output degree file
   
   degreefile.open("SW_degree.TXT");

   for( i=0;i<NetworkSizes;i++)        //打印节点
   {
	   
	   degreefile<<i<<'\t';
	   degreefile<<Nodes[i].AdjMember.size();
	   degreefile<<" "<<endl;
	   
   }

// putput degree file



}






//Create SWNET



int main(void)
{
	int NetSize=1000;
	int REG_K=2;
	InitEvirom(NetSize);
    RegNetBulider(NetSize, REG_K);  // Generator a text file named RegNet_DATA.txt 
	SWNetBuilder(NetSize,REG_K,0.05);    // Generator a text file named SWNet_DATA.txt

	return 0;
}