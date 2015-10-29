#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<string>
using namespace std;

int i=0;
int search_flag=0;
int global_count_1=0;
int global_count_2=0;

struct trie
{
	char data;
	int level;
	int finish;
	struct trie *next;
	struct trie *child;
};

struct trie *search(struct trie *t, char c, int i,int n)
{	
	if(i<n)
    {
		if(t->level==-1 && t->child==NULL)
		{
			search_flag=0;
			return t;
		}
		else if(t->level==-1 && t->child!=NULL)
		{
			return search(t->child,c,i,n);
		}
		else if(t->level<i && t->child==NULL)
		{
			search_flag=0;
			return t;
		}
		else if(t->level<i && t->child!=NULL)
		{
			return search(t->child,c,i,n);
		}
		else if(t->level==i && t->data==c)
		{
			search_flag=1;
			return t;
		}
		else if(t->level==i && t->data!=c)
		{
			if(t->next==NULL)
			{
				search_flag=0;
				return t;
			}
			else
			{
				int flag=0;
				while(t->next!=NULL)
				{
					if(t->next->data==c)
					{
						flag=1;
						search_flag=1;
						return t->next;
					}
					else
					{
						t=t->next;
					}
				}
				
				if(flag==0)
				{
					search_flag=0;
					return t;
			    }
			}
		}
	}
	else if(i==n)
	{
		if(t->level<i)
		return search(t->child,c,i,n);
		else if(t->level==i)
		{
			 if(t->data==c && t->finish==1)
			{
				search_flag=1;
				return t;
			}
			else if(t->data==c && t->finish!=1)
			{
				search_flag=0;
				return t;
			}
			else if(t->data!=c && t->next==NULL)
			{
				search_flag=0;
				return t;
			}
			else if(t->data!=c && t->next!=NULL)
			{
				int flag=0;
				while(t->next!=NULL)
				{
					if(t->next->data==c && t->next->finish==1)
					{
						search_flag==0;
						flag=1;
						return t->next;
					}
					else if(t->next->data==c && t->next->finish!=1)
					{
						search_flag=0;
						return t->next;
					}
					else if(t->next->data!=c)
					t=t->next;
				}
				if(flag==0)
				{
					search_flag=0;
					return t;
				}
			}
		}
	}
}

struct trie *create_child(struct trie *t, char c,int i,int n)
{
	t->child=(struct trie *)malloc(sizeof(trie));
	t=t->child;
	t->data=c;
	t->finish=0;
	
	if(i==n)
	{
		t->finish=1;
	}
	
	t->child=NULL;
	t->next=NULL;
	t->level=i;
	return t;
}


struct trie *create_next(struct trie *t, char c,int i,int n)
{
	t->next=(struct trie *)malloc(sizeof(trie));
	t=t->next;
	t->data=c;
	t->finish=0;
	
	if(i==n)
	t->finish=1;
	
	t->child=NULL;
	t->next=NULL;
	t->level=i;
	return t;
}


struct trie *addWord(struct trie *t, char c,int i,int n)
{
	if(t->level==-1 && t->child==NULL)
	{
		t->child=create_child(t,c,i,n);
		return t->child;
	}
	else if(t->level<i && t->child==NULL)
	{
		t->child=create_child(t,c,i,n);
		return t->child;
	}
	else if(t->level<i && t->child!=NULL)
	{
		return addWord(t->child,c,i,n);
	}
	else if(t->level==i)
	{
		if(t->data==c)
		return t;
		else if(t->data!=c && t->next==NULL)
		{
			t->next=create_next(t,c,i,n);
			return t->next;
		}
		else
		{
			int flag=0;
			while(t->next!=NULL)
			{
				if(t->next->data==c)
				{
					flag=1;
					return t->next;
				}
				else
				{
					t=t->next;
				}
			}
			
			if(flag==0)
			{
				t->next=create_next(t,c,i,n);
				return t->next;
			}
		}
	}

}


int main()
{
	trie *t=(struct trie *)malloc(sizeof(trie));
	t->data='0';
	t->level=-1;
	t->finish=10;
	t->child=NULL;
	t->next=NULL;

	struct trie *temp=t;
	
	string line;
    ifstream myfile("all_words_no_meaning.txt");
    if (myfile.is_open())
    {
	    while ( getline (myfile,line) )
	    {
	        for(int i=0;i<line.length();i++)
	        t=addWord(t,line[i],i,line.length()-1);
	        
	        t=temp;
	        global_count_1++;
	    }
	    myfile.close();
    }
    else 
	cout << "Unable to open file";
	
	t=temp;
	
	cout<<"Enter the word for search : ";
	string b;
	cin>>b;
	
	int i=0;
	do
	{
		t=search(t,b[i],i,b.length()-1);
		i++;
	}while(search_flag && i<b.length());
	
	if(search_flag)
	cout<<"Correctly spelled.";
	else
	cout<<"Not correctly spelled.";
	
	system("pause");
	return 0;
}
