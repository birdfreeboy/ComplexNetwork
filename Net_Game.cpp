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
	   int  profit;             //game profit
	   int  NodeFlag;           // Node Flag bit
   }Node;
// Define Node Type






// Define Global Variable
Node TmpNode;
Node Nodes[MAX_VERTEX_NUM];  //Nodes is Nodes of the Network,  TmpNode is temp used Node.
ofstream  Networkfile, SWNetfile, degreefile;
ofstream  Netgamefile;


ifstream  ReadData;
int netsizes;
vector<int> selecNodes;
int profitlist[MAX_VERTEX_NUM];


int sumC; int sumD;




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
		Nodes[i].profit=0;
		Nodes[i].NodeFlag=0;
	
	
	}

}


///////////////////////////////////////////////////////////////////////////////

//随机数根
void CreateRandomRoot(void)
{
	
	srand((unsigned) time(0));
	
}
//随机数根


// rnd=rand()*1.0/RAND_MAX*1.0;

//////////////////////////////////////////////////////
//   初始化每个节点的状态
////

int  InitStatus(int netsizes, double initprob)
{
	CreateRandomRoot();

	double rnd;
  
	for (int i=0 ;i< netsizes; i++)
	{
         rnd=rand()*1.0/RAND_MAX*1.0;
		 if (rnd<=initprob)
		 {
			 Nodes[i].NodeStatus=1;    // 坦白状态为  1
		 }
		 else
		 {
			 Nodes[i].NodeStatus=-1;    //背叛状态为 -1
		 }
	}




    return 0;
}


////////////////////////////////////////////////////////////////////////////////

int SelectNodes(int netsizes, double selprob)
{
	double rnd;
	
	for (int i=0 ;i< netsizes; i++)
	{
		rnd=rand()*1.0/RAND_MAX*1.0;
		if (rnd<selprob)
		{
			selecNodes.push_back(i);

			for(vector<int>::iterator iter=Nodes[i].AdjMember.begin(); iter!=Nodes[i].AdjMember.end();++iter)  //profit for select node
			{
				if (Nodes[i].NodeStatus==1)
				{
					if (Nodes[*iter].NodeStatus==1)
					{
						Nodes[i].profit+=5;
						//Nodes[*iter].NodeFlag+=5;
					}
					if (Nodes[*iter].NodeStatus==-1)
					{
						Nodes[i].profit+=1;
						//Nodes[*iter].NodeFlag+=10;

					}

				}

				if (Nodes[i].NodeStatus==-1)
				{
					if (Nodes[*iter].NodeStatus==1)
					{
						Nodes[i].profit+=10;
						//Nodes[*iter].NodeFlag+=1;

					}
					if (Nodes[*iter].NodeStatus==-1)
					{
						Nodes[i].profit+=0;
						//Nodes[*iter].NodeFlag+=0;

					}
					
				}


			}

			
			Nodes[i].NodeFlag=1;


		}

	}






////////////////////////////////////


 //    for( i =0; i< selecNodes.size(); i++)
	for(vector<int>::iterator it=selecNodes.begin(); it!=selecNodes.end();it++)
	{
		
		 for(vector<int>::iterator iter=Nodes[*it].AdjMember.begin();iter!=Nodes[*it].AdjMember.end();iter++)
		 {
              if (Nodes[*iter].NodeFlag!=1)
              {
				  for (vector<int>::iterator iiter=Nodes[*iter].AdjMember.begin();iiter!=Nodes[*iter].AdjMember.end();iiter++)
				  {

					  if (Nodes[*iter].NodeStatus==1)
					  {
						  if (Nodes[*iiter].NodeStatus==1)
						  {
							  Nodes[*iter].profit+=5;
							  //Nodes[*iter].NodeFlag+=5;
						  }
						  if (Nodes[*iiter].NodeStatus==-1)
						  {
							  Nodes[*iter].profit+=1;
							  //Nodes[*iter].NodeFlag+=10;
							  
						  }
						  
					  }
					  
					  if (Nodes[*iter].NodeStatus==-1)
					  {
						  if (Nodes[*iiter].NodeStatus==1)
						  {
							  Nodes[*iter].profit+=10;
							  //Nodes[*iter].NodeFlag+=1;
							  
						  }
						  if (Nodes[*iiter].NodeStatus==-1)
						  {
							  Nodes[*iter].profit+=0;
							  //Nodes[*iter].NodeFlag+=0;
							  
						  }
						  
					  }


				  }
              }
		 }


	 }


	 /////////////////////////////////////

	for ( it=selecNodes.begin(); it!=selecNodes.end();it++)
     {
		 int maxprofit=10000;
		 int profits=0;
		 int Nodeid;
		 for(vector<int>::iterator iter=Nodes[*it].AdjMember.begin();iter!=Nodes[*it].AdjMember.end();iter++)
		 {
			 int profits= (int)(Nodes[*iter].profit);
			 if (maxprofit>profits )
			 {
				 maxprofit=profits;
				 Nodeid=*iter;
    
			 }
		
		 }

        
		 Nodes[*it].NodePreStatus=Nodes[Nodeid].NodeStatus;
		 profitlist[*it]=maxprofit;



     }


/*	for (it=selecNodes.begin(); it!=selecNodes.end(); it++)
	{

          cout<<*it<<'\t';
	}
	 cout<<endl;

	 for (it=profitlist.begin(); it!=profitlist.end();it++)

	 {
		 
		 cout<<*it<<'\t';
	 }
	 cout<<endl;
*/
/// change status
       

	for (it=selecNodes.begin(); it!=selecNodes.end(); it++)
	 {
		
		 
		 if (Nodes[*it].profit > profitlist[*it])
		 {
			 
		//	 cout<<Nodes[*it].profit<<"      "<<profitlist[*it]<<"yyyyyyy"<<endl;

			 Nodes[*it].NodeStatus=Nodes[*it].NodePreStatus;

			

		 }
	 }


//   
	 for (i =0; i<netsizes; i++)
	 {
		 Nodes[i].NodeFlag=0;
		 Nodes[i].profit=0;
         Nodes[i].NodePreStatus=0;	
		 profitlist[i]=0;
	 }
	 

	 
	 selecNodes.clear();







	return 0;
}



////////////////////////////////////////////////

int meanSatus(int netsizes)
{   sumC=0; sumD=0;

	for (int i =0; i<netsizes; i++)
	{
		if(Nodes[i].NodeStatus==1)
		{
			sumC+=1;
		}
		else
		{
			sumD+=1;
		}

	}
//	cout<<"sumC"<<'\t'<<sumC<<endl;
//	cout<<"sumD"<<'\t'<<sumD<<endl;
	return 0;
}




////////////////////////////////////////////////////////////////////////////////




int main(void)
{
	Netgamefile.open("NetGame_DATA.txt");

	ReadNetData();

    
	InitStatus(netsizes, 0.5);   //坦白的概率



	for (int t=0; t<1000; t++)
	{
		SelectNodes(netsizes, 0.2);

        Netgamefile<<t<<'\t';


		meanSatus(netsizes);

		Netgamefile<<sumC<<'\t'<<sumD<<endl;
		
		
	

	
		
	}



	


	return 0;
}