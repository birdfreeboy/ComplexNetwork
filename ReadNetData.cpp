//STL C++ include files
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <numeric>
#include   <functional>
#include <string>
#include <sstream>


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
ifstream  ReadData;
int netsizes;





// Define Global Variable



// Define Interface Function

void ReadNetData(void);



void InitEvirom( int );    // Define Initial Environment Function

void ComputDegree(int);





// Define Interface Function 




void ReadNetData(void)
{
	ReadData.open("SWNet_DATA.txt");
	while (!ReadData.eof())
	{
		char line[MAX_VERTEX_NUM];
		int nodeid;

		ReadData.getline(line,MAX_VERTEX_NUM);

		string s =line;

		
		
     //  s.erase(remove_if(s.begin(),   s.end(),   ptr_fun(::isspace)),   s.end());

		if(s.empty())
			continue;
		if(s[0]=='#')
		    continue;

        if(!s.compare("NETWORKSIZES"))
		{
			ReadData.getline(line,MAX_VERTEX_NUM);
			s=line;
		//	s.erase(remove_if(s.begin(),   s.end(),   ptr_fun(::isspace)),   s.end());
			netsizes=atoi(s.c_str());
		//	cout<<netsizes<<endl;
			InitEvirom(netsizes);
			continue;
		}
		  
		 if(!s.compare("DATA"))
		 {
			 continue;
		 
		 }

		 if (!s.empty())
		 {

			 
			 stringstream ss(s);
		
			 int nid;
			 ss>>nid;
		
		
			 
            while (ss>>nodeid)
            {

		
				Nodes[nid].AdjMember.push_back(nodeid);
            }
			
		 }


          

	}
	
}



void InitEvirom (int NetworkSizes)
{

	for (int i =0; i<NetworkSizes;i++)
	{
		Nodes[i].NodeID=i;
		Nodes[i].NodePreStatus=0;
		Nodes[i].NodeStatus=0;
		Nodes[i].NodeFlag=0;
	
	
	}



}





int main(void)
{
	ReadNetData();



	
	
	
	
	/*  test demo

  for(int i=0; i<1000;i ++)
	{
		cout<<i<<'\t'<<"*********"<<endl;
		for(vector<int>::iterator iter=Nodes[i].AdjMember.begin(); iter!=Nodes[i].AdjMember.end(); ++iter)
				{
		cout<<"{"<<*iter<<"}"<<'\t';
		
				}
				cout<<endl;
	}
 
   */

	return 0;
}