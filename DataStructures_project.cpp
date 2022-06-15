#include <bits/stdc++.h>
using namespace std;
//***************************************************************

// Data Structures and Algorithms project
// Written by Arshia Afrougheh
// Islamic Azad University Central branch
// Dr.Maryam Hajiesmaeili

//***************************************************************



//***************************************************************

// At the end of this file , you will see the implementation of some 
//data structures and algorithms like linked list , binary tree and heapsort in C++ .

//***************************************************************


class account
{
	int account_no;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account
};

void account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>account_no;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<account_no;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<account_no;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<account_no<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

	
int account::retacno() const
{
	return account_no;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


//***************************************************************
//    	function declaration
//***************************************************************

void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//***************************************************************


int main()
{
	char ch;
	int num;
	intro();
	while(ch!='8')
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. CREATE NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. CHECK THE DETAILS OF EXISTING ACCOUNT";
		cout<<"\n\n\t05. VIEW CUSTOMERS LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. UPDATE INFORMATION OF EXISTING ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) : ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
            cout<<"\n\n Press any key to exit...";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}
	return 0;
}


//***************************************************************
//    	function to write in file
//***************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//***************************************************************

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//***************************************************************

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//***************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//***************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//***************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//***************************************************************


void intro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : Arshia Afrougheh";
    cout<<"\n\nPress any key to continue...";
	cin.get();
}


//Linked list implementation in C++


//***************************************************************

	//A linked list is a linear dynamic data structure to store data items.

	//We also know that arrays are a linear data structure that store data items in contiguous locations.

	//Unlike arrays, the linked list does not store data items in contiguous memory locations.
	
	//it is possible to grow or shrink the linked list dynamically.

	//as long as memory is available, we can have as many data items added to the linked list.

	//the linked list also doesn’t waste memory space as we need not specify 
	//beforehand how many items we need in the linked list.

	// Time Complexity : Search : O(n) , Insertion : O(1) , Deletion : O(1)

//***************************************************************

// A linked list node
struct Node
{
   int data;
   struct Node *next;
};

//insert a new node in front of the list
void push(struct Node** head, int node_data)
{
   // 1. create and allocate node
   struct Node* newNode = new Node;
 
   // 2. assign data to node
   newNode->data = node_data;
 
   // 3. set next of new node as head
   newNode->next = (*head);
 
   // 4. move the head to point to the new node
   (*head) = newNode;
}
 
//insert new node after a given node
void insertAfter(struct Node* prev_node, int node_data)
{
  // 1. check if the given previous node is NULL
if (prev_node == NULL)
{
   cout<<"the given previous node is required,cannot be NULL"; return; } 
 
   // 2. create and allocate new node
   struct Node* newNode =new Node; 
 
   // 3. assign data to the node
   newNode->data = node_data;
 
   // 4. Make next of new node as next of prev_node 
   newNode->next = prev_node->next;
 
    // 5. move the next of prev_node as new_node
    prev_node->next = newNode;
}
 
/* insert new node at the end of the linked list */
void append(struct Node** head, int node_data)
{
/* 1. create and allocate node */
struct Node* newNode = new Node;
 
struct Node *last = *head; /* used in step 5*/
 
/* 2. assign data to the node */
newNode->data = node_data;
 
/* 3. set next pointer of new node to null as its the last node*/
newNode->next = NULL;
 
/* 4. if list is empty, new node becomes first node */
if (*head == NULL)
{
*head = newNode;
return;
}
 
/* 5. Else traverse till the last node */
while (last->next != NULL)
last = last->next;
 
/* 6. Change the next of last node */
last->next = newNode;
return;
}
 
// display linked list contents
void display(struct Node *node)
{
   //traverse the list to display each node
   while (node != NULL)
   {
      cout<<node->data<<"-->";
      node = node->next;
   }
 
if(node== NULL)
cout<<"null"; 
} 
/* main program for linked list*/
int main() 
{ 
/* empty list */
struct Node* head = NULL; 
 
// Insert 10.
append(&head, 10); 
 
// Insert 20 at the beginning. 
push(&head, 20); 
 
// Insert 30 at the beginning. 
push(&head, 30); 
 
// Insert 40 at the end. 
append(&head, 40); 

// Insert 50, after 20. 

insertAfter(head->next, 50);
 
cout<<"Final linked list: "<<endl;
display(head);
 
return 0;
}


// Binary Tree Implementation in c++

//***************************************************************

	//Binary trees are widely used data structures across the software Engineering .
	// binary tree is a tree (Data Structure) in which every node has at maximum level 2 children i.e. 
	//the left child(left sub-tree) and the right child(right sub-tree).
	//From the figure you can see that a node consists of three parts.
	//1.Pointer to left child
	//2.Data
	//3.Pointer to right child
	//Complexity
	//Search : For searching we need to traverse all elements thus worst case complexity will be O(n).
	//Insertion : Worst case complexity will be O(n).
	//Deletion : Worst case complexity will be O(n).

//***************************************************************
// Binary tree nodes
struct node { 
    int data;
    struct node *left; 
    struct node *right; 
};

struct node * insertInBinaryTree(struct binaryTreeNode * root, int num)
{
    struct node * temp = NULL;
    struct queue * Q = NULL;
     
    struct node * newNode = (struct binaryTreeNode *)malloc(sizeof(struct binaryTreeNode));
     
    newNode -> data = num;
    newNode -> left = NULL;
    newNode -> right = NULL;
     
    if(root == NULL) {
        root = newNode;
        return root;
    }
     
    Q = enQueue(Q, root);
     
    while(!isQueueEmpty(Q)) {
        temp = Q -> front -> data;
        Q = deQueue(Q);
         
        if(temp -> left != NULL)
            Q = enQueue(Q, temp -> left);
        else {
            temp -> left = newNode;
            free(Q);
            return root;
        }
         
        if(temp -> right != NULL)
            Q = enQueue(Q, temp -> right);
        else {
            temp -> right = newNode;

            free(Q);
            return root;
        }
    }
     
    free(Q);
    return root;
}

void deletDeepest(struct Node *root, 
                  struct Node *d_node) { 
    queue<struct Node*> q; 
    q.push(root); 
  
    struct Node* temp; 
    while(!q.empty()) { 
    
        temp = q.front(); 
        q.pop(); 
        if(temp == d_node) { 
            temp = NULL; 
            delete(d_node); 
            return; 
        } 
        if (temp->right) { 
            if (temp->right == d_node) { 
                temp->right = NULL; 
                delete(d_node); 
                return; 
            } 
            else
                q.push(temp->right); 
        } 
  
        if (temp->left) { 
            if (temp->left == d_node) { 
                temp->left=NULL; 
                delete(d_node); 
                return; 
            } 
            else
                q.push(temp->left); 
        } 
    } 
} 

void delete(struct Node* root, int key) { 
    queue<struct Node*> q; 
    q.push(root); 
  
    struct Node *temp; 
    struct Node *key_node = NULL; 
  
    while (!q.empty()) { 
        temp = q.front(); 
        q.pop(); 
  
        if (temp->key == key) 
            key_node = temp; 
  
        if (temp->left) 
            q.push(temp->left); 
  
        if (temp->right) 
            q.push(temp->right); 
    } 
  
    int x = temp->key; 
    deletDeepest(root, temp); 
    key_node->key = x; 
} 

struct node* newNode(int data) { 

    struct node* node = (struct node*)malloc(sizeof(structnode)); 
  
    node->data = data; 
    node->left = NULL; 
    node->right = NULL; 
    return(node); 
} 
      
int main() 
{ 
  struct node *tree = null;
  struct node *root = newNode(1);
  root->left = newNode(2); 
  root->right = newNode(3); 
  root->left->left  = newNode(4);
  root->left->right = newNode(5);
  tree = insertInBinaryTree(root,6);
  delete(tree,3);                            
  return 0; 
}

// Heapsort implementation in C++

//***************************************************************
// Heapsort works by visualizing the elements of the array as 
// a special kind of complete binary tree called a heap.

// If we want our tree to follow a heap data structure it should be implemented under thease cicumstances:
// 1.It should be a complete binary tree
// 2.All nodes in the tree follow the property that they are greater than their children i.e. the largest
// element is at the root and both its children are smaller than the root and so on.
// Such a heap is called a max-heap. If instead, all nodes are smaller than their children, it is called a min-heap
// Time Complexity : O(nlog(n)).
//***************************************************************

void Change_To_Heap(int array[] , int length , int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if(left < length && array[largest] < array[left])
    {
        largest = left;
    }
    if(right < length && array[largest] < array[right])
    {
        largest = right;
    }
    //If root is not largest, swap with largest and continue heapifying
    if(largest != root)
    {
        swap(array[root], array[largest]);
        Change_To_Heap(array , length , largest);
    }
}
// implementing heapsort
void heapSort(int array[] , int length)
{
    // build heap
   for (int i = length / 2 - 1; i >= 0; i--)
   Change_To_Heap(array, length, i);
  
   // extracting elements from heap one by one
   for (int i=length-1; i>=0; i--)
   {
      // Move current root to end
      swap(array[0], array[i]);
  
      // again call max heapify on the reduced heap
      Change_To_Heap(array, i, 0);
   }
}
// Display the array
void displayArray(int arr[], int n)
{
   for (int i=0; i<n; i++)
   cout << arr[i] << " ";
   cout <<endl;
}
int main()
{
    int arr[] = {4,17,3,1,9,6};
   int length = *(&arr + 1) - arr;
   cout<<"Input array"<<endl;
   displayArray(arr,length);
  
   heapSort(arr, length);
  
   cout << "Sorted array"<<endl;
   displayArray(arr, length);
}
