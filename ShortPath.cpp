//STL C++ include files
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include <sstream>


using namespace std;
//STL C++ include files








// define const number
#define INFINITY  INT_MAX   	
#define MAX_VERTEX_NUM 10000 //最大顶点个数> 30000000, 三千万个节点
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
vector<int> formaldegree,degree, degreedis;
ofstream  Networkfile, SWNetfile, degreefile, degreedisfile, pathfile;
ifstream  ReadData;
int netsizes;
int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM], dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM], map[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
const int INF = 100000;





// Define Global Variable



// Define Interface Function

void ReadNetData(void);

void InitEvirom( int );    // Define Initial Environment Function

void ShortPath(int);






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

void ShortPath(int netsizes)
{


	for(int i=0; i<netsizes; i++)
		for (int j =0; j<netsizes;j++)
		{
            map[i][j]=(i==j)?0:INF;
		}

	for (i=0; i<netsizes; i++)
	{
		for (vector<int>::iterator iter = Nodes[i].AdjMember.begin(); iter!=Nodes[i].AdjMember.end();++iter)
		{
			map[i][*iter]=1;
		}
	}


/*	for (i=0;i<netsizes;i++)
	{for(int j=0;j<netsizes;j++)
			cout<<map[i][j]<<'\t';
     cout<<endl;

	}

*/

}


void floyd(int n){
    int i,j,k;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			dist[i][j]=map[i][j],path[i][j]=0;
		for(k=0;k<n;k++)
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					if(dist[i][k]+dist[k][j]<dist[i][j])
                     dist[i][j]=dist[i][k]+dist[k][j],path[i][j]=k;




	/*				for( i=0; i<n; i++)
					{for (int j=0; j<n; j++)
										cout<<path[i][j]<<'\t';
                      cout<<endl;
					}*/
}

void output(int i,int j){
	if(i==j) return;
	if(path[i][j]==0) pathfile<<j<<' ';
	else{
		output(i,path[i][j]);
		output(path[i][j],j);
	}
	 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void)
{

	ReadNetData();

	ShortPath(netsizes);
	floyd(netsizes);

	pathfile.open("NetPath_DATA.txt");

	for(int u=0; u<netsizes;u++)
		for(int v=0; v<netsizes; v++)
		{	if(dist[u][v]==INF) cout<<"No path"<<endl;
				else{
					pathfile<<u<<' ';
					output(u,v);
					pathfile<<endl;
				}
		}
	

	
	cout<<"***********max direction**************"<<endl;

	int maxij=0;
	for(  u=0; u<netsizes;u++)
		for(int v=0; v<netsizes; v++){
	           if(maxij<=dist[u][v])
				   maxij=dist[u][v];
		}
	cout <<"max direction  i->j"<<'\t' << maxij<<endl;


	cout<<"************avg path*************"<<endl;
	
	int ijsum=0;
	double avgij;
	for( u=0; u<netsizes;u++)
		for(int v=u+1; v<netsizes; v++){
	          ijsum=ijsum+dist[u][v];
				  
		}
		avgij=ijsum*2.0/(netsizes*(netsizes+1));
		
		cout <<"avg path i->j"<<'\t' << avgij<<endl;





	return 0;
}


