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
vector<double> cluster;
ofstream  Networkfile, SWNetfile, degreefile, degreedisfile;
ifstream  ReadData;
int netsizes;





// Define Global Variable



// Define Interface Function

void ReadNetData(void);



void InitEvirom( int );    // Define Initial Environment Function

void ComputCluster(int);






// Define Interface Function 


///////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReadNetData(void)
{
	ReadData.open("SFNet_DATA.txt");
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComputCluster(int netsizes)
{
	
	vector<int>::iterator  iiter;

	for (int i=0; i<netsizes; i++)
	{
		int ClusterSum=0;

       for (int j=0; j< Nodes[i].AdjMember.size();j++)
       {
		   for (iiter=Nodes[Nodes[i].AdjMember[j]].AdjMember.begin();iiter!=Nodes[Nodes[i].AdjMember[j]].AdjMember.end();++iiter)
		   {
               if(find(Nodes[i].AdjMember.begin(), Nodes[i].AdjMember.end(), *iiter)!=Nodes[i].AdjMember.end())
			   {
				   ClusterSum++;
				  
			   }
		  
             
		   }
       }

	    cout<<ClusterSum<<endl;

	    cout<<ClusterSum*1.0/ (Nodes[i].AdjMember.size()*(Nodes[i].AdjMember.size()-1))<<endl;

		// clustersum/2  /  (n(n-1)/2 

	   cluster.push_back(ClusterSum*1.0/ (Nodes[i].AdjMember.size()*(Nodes[i].AdjMember.size()-1)));

       
	}


	 cout<<endl;
     double  sumforcluster=0;
     for(vector<double>::iterator iter=cluster.begin();iter!=cluster.end(); ++iter)
	 {
          sumforcluster+=*iter;
	 }

	 cout<<"Avg Cluster="<<sumforcluster/netsizes<<endl;
 

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void)
{
	ReadNetData();

	ComputCluster(netsizes);



	
	
	
	
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