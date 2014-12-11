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
#define MAX_VERTEX_NUM 300000 //最大顶点个数> 30000000, 三千万个节点
// define const number   






// Define Node Type
typedef struct Node
{
	   int  NodeID;				// Node ID
       int  NodeStatus;			// Node Status
	   int  NodePreStatus;      // NOde Previous Status;
	   vector<int> AdjMember;   //Adjacent Member ID List 
	   int  NodeFlag;           // Node Flag bit
	   int  PointX;             // X Coordinate
	   int  PointY;             // Y Coordinate
   }Node;
// Define Node Type






// Define Global Variable
Node TmpNode;
Node Nodes[MAX_VERTEX_NUM];  //Nodes is Nodes of the Network,  TmpNode is temp used Node.
ofstream  Networkfile;

// Define Global Variable



// Define Interface Function

void InitEvirom( int );    // Define Initial Environment Function

void GridNetBulider( int );  //Define Grid Network Builder 

// Define Interface Function 




void InitEvirom (int NetworkSize)  // Networksize * Networksize= Networksizes
{
	
   
	for (int i=0; i<NetworkSize*NetworkSize; i++) {
	Nodes[i].NodeID=i;
	Nodes[i].NodePreStatus=0;
	Nodes[i].NodeStatus=0;
	Nodes[i].NodeFlag=0;
	Nodes[i].PointX=i % NetworkSize;
	Nodes[i].PointY= (int)((i-Nodes[i].PointX)/NetworkSize);

	}

}





//Create GridNet	
void GridNetBulider(int NetworkSize)	
{
	int NetworkSizes=NetworkSize*NetworkSize;


	
///////////////////
//1  four corner
	Nodes[0].AdjMember.push_back(1);
	Nodes[0].AdjMember.push_back(NetworkSize);

	Nodes[NetworkSize-1].AdjMember.push_back(NetworkSize-2);
	Nodes[NetworkSize-1].AdjMember.push_back(NetworkSize-1+NetworkSize);

	Nodes[0+NetworkSize*(NetworkSize-1)].AdjMember.push_back(1+NetworkSize*(NetworkSize-1));
	Nodes[0+NetworkSize*(NetworkSize-1)].AdjMember.push_back(0+NetworkSize*(NetworkSize-2));

	Nodes[NetworkSize-1+NetworkSize*(NetworkSize-1)].AdjMember.push_back(NetworkSize-2+NetworkSize*(NetworkSize-1));
	Nodes[NetworkSize-1+NetworkSize*(NetworkSize-1)].AdjMember.push_back(NetworkSize-1+NetworkSize*(NetworkSize-2));


//2  four edge
	for (int i =1;i<NetworkSize-1;i++)  //down edge;
	{
		Nodes[i].AdjMember.push_back(i-1);
		Nodes[i].AdjMember.push_back(i+1);
		Nodes[i].AdjMember.push_back(i+NetworkSize);
	}

	for ( i =1;i<NetworkSize-1;i++)  //up edge;
	{
		Nodes[i+NetworkSize*(NetworkSize-1)].AdjMember.push_back(i+NetworkSize*(NetworkSize-1)-1);
		Nodes[i+NetworkSize*(NetworkSize-1)].AdjMember.push_back(i+NetworkSize*(NetworkSize-1)+1);
		Nodes[i+NetworkSize*(NetworkSize-1)].AdjMember.push_back(i+NetworkSize*(NetworkSize-2));
	}


	for ( int j=1;j<NetworkSize-1;j++) //left edge;
	{
		Nodes[0+NetworkSize*j].AdjMember.push_back(NetworkSize*(j-1));
		Nodes[0+NetworkSize*j].AdjMember.push_back(NetworkSize*(j+1));
		Nodes[0+NetworkSize*j].AdjMember.push_back(1+NetworkSize*j);


	}

	for (  j=1;j<NetworkSize-1;j++) //right edge;
	{
        Nodes[NetworkSize-1+NetworkSize*j].AdjMember.push_back(NetworkSize-1+NetworkSize*(j-1));
        Nodes[NetworkSize-1+NetworkSize*j].AdjMember.push_back(NetworkSize-1+NetworkSize*(j+1));
        Nodes[NetworkSize-1+NetworkSize*j].AdjMember.push_back(NetworkSize-2 + NetworkSize*j);
		
	}


// center point

	for(i=1;i<NetworkSize-1;i++)
		for(j=1;j<NetworkSize-1;j++)
		{
			Nodes[i+NetworkSize*j].AdjMember.push_back(i+1+NetworkSize*j);
			Nodes[i+NetworkSize*j].AdjMember.push_back(i-1+NetworkSize*j);
			Nodes[i+NetworkSize*j].AdjMember.push_back(i+NetworkSize*(j-1));
		    Nodes[i+NetworkSize*j].AdjMember.push_back(i+NetworkSize*(j+1));
		}

	


		Networkfile.open("GridNet_DATA.txt");

		Networkfile<<"#Grid Network Builder"<<endl;
		Networkfile<<"#Grid Network NetworkSize( NetworkSize*NetworkSize) "<<endl;
		Networkfile<<"NETWORKSIZES"<<endl;
		Networkfile<<NetworkSize<<endl;

		Networkfile<<"  "<<endl;
		Networkfile<<"DATA"<<endl;



        for(i=0;i<NetworkSize*NetworkSize;i++)
		{
		   Networkfile<<i<<'\t';
		   
		   for(vector<int>::iterator iter=Nodes[i].AdjMember.begin(); iter!=Nodes[i].AdjMember.end();++iter)

		   {
           Networkfile<<(*iter)<<'\t';
		   }
		   
		   Networkfile<<endl;

		}
 





//////////////////






	

	
}


int main(void)
{
	int NetSize=400;  //NetSizes=NetSize*NetSize
	InitEvirom(NetSize);
    GridNetBulider(NetSize);

	return 0;
}