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
ofstream  Networkfile;

// Define Global Variable



// Define Interface Function

void InitEvirom( int );    // Define Initial Environment Function

void RegNetBulider( int );  //Define Regular Network Builder 

// Define Interface Function 




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
Networkfile<<"#NetworkSize(Max Numbers of Nodes)"<<endl;
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



int main(void)
{
	int NetSize=2000;
	InitEvirom(NetSize);
    RegNetBulider(NetSize, 6);  // Generator a text file named RegNet_DATA.txt 
	return 0;
}