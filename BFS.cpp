#include<iostream>
#include<stdlib.h>
#include<queue>
using namespace std;


class node
{
   public:
	
	node *left, *right;
	int data;

};	 

class Breadthfs
{
 
 public:
 
 node *insert(node *, int);
 void bfs(node *);
 
};


node *insert(node *root, int data)
// inserts a node in tree
{

	if(!root)
	{
		
		root=new node;
		root->left=NULL;
		root->right=NULL;
		root->data=data;
		return root;
	}

	queue<node *> q;
	q.push(root);
	
	while(!q.empty())
	{

		node *temp=q.front();
		q.pop();
	
		if(temp->left==NULL)
		{
			
			temp->left=new node;
			temp->left->left=NULL;
			temp->left->right=NULL;
			temp->left->data=data;	
			return root;
		}
		else
		{

		q.push(temp->left);

		}

		if(temp->right==NULL)
		{
			
			temp->right=new node;
			temp->right->left=NULL;
			temp->right->right=NULL;
			temp->right->data=data;	
			return root;
		}
		else
		{

		q.push(temp->right);

		}

	}
	
}


void bfs(node *head)
{

		queue<node*> q;
		q.push(head);
		
		int qSize;
		
		while (!q.empty()) 
		{
			qSize = q.size();
			#pragma omp parallel for
                //creates parallel threads
			for (int i = 0; i < qSize; i++) 
			{
				node* currNode;
				#pragma omp critical
				{
				  currNode = q.front();
				  q.pop();
				  cout<<"\t"<<currNode->data;
				  
				}// prints parent node
				#pragma omp critical
				{
				if(currNode->left)// push parent's left node in queue
					q.push(currNode->left);
				if(currNode->right)
					q.push(currNode->right);
				}// push parent's right node in queue		

			}
		}

}

int main(){

	node *root=NULL;
	int data;
	char ans;
	
	do
	{
		cout<<"\n enter data=>";
		cin>>data;
		
		root=insert(root,data);
	
		cout<<"do you want insert one more node?";
		cin>>ans;
	
	}while(ans=='y'||ans=='Y');
	
	bfs(root);
	
	return 0;
}

/*
 enter data=>10
do you want insert one more node?y

 enter data=>20
do you want insert one more node?y

 enter data=>30
do you want insert one more node?y

 enter data=>40
do you want insert one more node?y

 enter data=>50
do you want insert one more node?n
        10      20      30      40      50

 ✅ Step 1: Update your package list
bash
Copy
Edit
sudo apt update
✅ Step 2: Install g++
bash
Copy
Edit
sudo apt install g++
This installs the GNU C++ compiler (g++). OpenMP is built-in with g++ version 4.2 and above.

✅ Step 3: Verify g++ installation
Check the version:

bash
Copy
Edit
g++ --version
If the version is 4.2 or higher, OpenMP is supported.

✅ Step 4: Compile a C++ program with OpenMP
Use the -fopenmp flag when compiling:

bash
Copy
Edit
g++ -fopenmp your_program.cpp -o output_program
Example:

bash
Copy
Edit
g++ -fopenmp bfs.cpp -o bfs
./bfs
✅ Step 5: (Optional) Test if OpenMP is enabled
You can run this command:

bash
Copy
Edit
g++ -fopenmp -dM -E - < /dev/null | grep -i openmp
If OpenMP is supported, you’ll see a line like:

cpp
Copy
Edit
#define _OPENMP 201511
🔧 (Optional: If you use Clang instead of g++)
Clang doesn't support OpenMP by default. If you're using clang++, install OpenMP with:

bash
Copy
Edit
sudo apt install libomp-dev
You're all set! Want a simple test OpenMP C++ program to verify it runs?







You said:
if openmp is not supported for g++ then


ChatGPT said:
If OpenMP is not supported for your current g++, here’s what you can do:

✅ Option 1: Install a newer version of g++ that supports OpenMP
Check current version:

bash
Copy
Edit
g++ --version
If it’s very old (below 4.2), update it.

Upgrade to a newer version of g++:

bash
Copy
Edit
sudo apt update
sudo apt install g++-12
Make it the default (optional):

bash
Copy
Edit
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100
✅ Option 2: Build GCC with OpenMP support manually (advanced)
If you're on a very old system or using a minimal Linux distro:

Download GCC source:

bash
Copy
Edit
sudo apt install build-essential
sudo apt install libgmp-dev libmpfr-dev libmpc-dev
wget https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz
tar -xvzf gcc-12.2.0.tar.gz
cd gcc-12.2.0
./contrib/download_prerequisites
mkdir build && cd build
../configure --enable-languages=c,c++ --disable-multilib
make -j$(nproc)
sudo make install
After this, g++ will support OpenMP by default.

✅ Option 3: Use Clang with OpenMP (as a backup)
If you can’t upgrade g++, you can use Clang:

Install Clang and OpenMP support:

bash
Copy
Edit
sudo apt install clang libomp-dev
Compile using Clang:

bash
Copy
Edit
clang++ -fopenmp your_program.cpp -o your_program -lomp

*/
