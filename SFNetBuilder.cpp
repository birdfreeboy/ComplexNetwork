//STL C++ include files
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <cmath>


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
double DegreeSum;
double problink[MAX_VERTEX_NUM];
vector<int> linknum;
double tmpProb;
double netalpha;




// Define Global Variable



// Define Interface Function

void InitEvirom( int );    // Define Initial Environment Function


void CreateRandomRoot(void);  

void SFNetBuilder(int,int,int);


// Define Interface Function 



//随机数根
void CreateRandomRoot(void)
{

	srand((unsigned) time(0));
	
}
//随机数根




void InitEvirom (int initNum)
{
	 for(int i =0; i<initNum-1; i++)
	 {
		 Nodes[i].NodeID=i;
		 Nodes[i].NodePreStatus=0;
		 Nodes[i].NodeStatus=0;
		 Nodes[i].NodeFlag=0;
		 Nodes[i].AdjMember.push_back(i+1);
	
	 }

	         Nodes[initNum-1].NodeID=initNum-1;
	 		 Nodes[initNum-1].NodePreStatus=0;
			 Nodes[initNum-1].NodeStatus=0;
			 Nodes[initNum-1].NodeFlag=0;
		     Nodes[initNum-1].AdjMember.push_back(0);


 


}



/*
想法：根据SF的定义，开始M个点，后来M0个点，MO<=M, 连接概率是他们的度/度和，选择连接边。


 */




void SFNetBuilder(int initNum, int linkNum, int NetWorkSizes)
{
	CreateRandomRoot();
	double rnd;

	for (int i=initNum;i<NetWorkSizes; i++)
	{
		  DegreeSum=0;
          
          for(int j=0; j<i;j++)
		  {
			  DegreeSum=DegreeSum+pow(Nodes[j].AdjMember.size(), netalpha);

		  }

		  for( j=0; j<i; j++)
		  {
			  problink[j]=pow(Nodes[j].AdjMember.size(), netalpha)*1.0/DegreeSum;


		  }

          
		  
		  


		  
          do 
          {
			  rnd=rand()*1.0/RAND_MAX; 

			  tmpProb=0;

			  for(j=0;j<i;j++)
			  {
				  tmpProb=tmpProb+problink[j];

				  if(rnd<tmpProb && j==0)   //first prob
				  {
					  if(find(linknum.begin(),linknum.end(),j)!=linknum.end())
					  {
						  break;
					  }
					  else
					  {linknum.push_back(j); break;}


				  }
				  
	

				  
				  
				  
				  if (rnd>tmpProb)  // other element    
				  {
					  continue;
				  }else
				  {
                     if(find(linknum.begin(),linknum.end(),j)!=linknum.end())
					 {
						 break;
					 }
					 else
					 {linknum.push_back(j); break;}
				  }
			  }


          } while (linknum.size()!=linkNum);




		  for (vector<int>::iterator iter=linknum.begin();iter!=linknum.end();++iter)
		  {
			  Nodes[i].AdjMember.push_back(*iter);
			  Nodes[*iter].AdjMember.push_back(i);

		  }

         
		  linknum.clear();

		  
          
	}


	// 输入到文件中
	
	
	Networkfile.open("SFNet_DATA.txt");
	Networkfile<<"#SF Network Bulider"<<endl;
	Networkfile<<"NETWORKSIZES"<<endl;
	Networkfile<<NetWorkSizes<<endl;
	Networkfile<<"#NodeID"<<'\t'<< "Adjacent Members" <<'\t'<<'\t'<< endl;
	Networkfile<<" "<<endl;
	Networkfile<<"DATA"<<endl;


	
	
	for( i=0;i<NetWorkSizes;i++)        //打印节点
	{
	    Networkfile<<i<<'\t';
		for (vector<int>::iterator iter=Nodes[i].AdjMember.begin();iter!=Nodes[i].AdjMember.end();++iter)
		{
			Networkfile<< *iter<<'\t';

		}
		Networkfile<<endl;
	}
	
	// 输入到文件中

	// degree file
	
	degreefile.open("degree.txt");
	
	for (i=0; i<NetWorkSizes; i++)
	{
		int kk=0;
		for(int jj=0;jj<NetWorkSizes; jj++){
			if(Nodes[jj].AdjMember.size()==i)
				kk++;
		}
		
		if(kk>0)
			degreefile<<i<<'\t'<<(double)kk<<endl;
		// degreefile<<i<<'\t'<<(double)kk/NetWorkSizes<<endl;
		
		
		//degree file


}



}




int main(void)
{
	netalpha=0;   //Network ALPHA =1  SF; ALPHA =0  RANDOM NETWORK
	InitEvirom(4);
	SFNetBuilder(4,4,1000);
 

	return 0;
}