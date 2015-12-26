/*
 * B.Bhargav Sastry
 * COSC 5390.001   
 * Programming Language
 * COURSE ASSIGNMENT I
 * Fall 2015
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class list
{
	string word;
	int lnum;
	list *link, *link1, *link2;
	
	public:
		void create(string a);
		void sort();
		void process(string a, int ln);
		void display();
	
};

list *first = NULL;

/*
 * This function makes a list of all the words
 * present in the text file.
 */
 
void list::create(string a)
{
	
	list *temp;
	list *i;
	int k;
	
	for(k=0; a[k]!='\0';k++);
	
	if(ispunct(a[k-1]))
	{
		a = a.substr(0, a.size()-1);
	}
	temp = new list;
	temp->word=a;
	temp->link = NULL;
	temp->link1 = NULL;
	temp->link2 = NULL;
	
	if(first==NULL)
	{
		first=temp;
		
	}
	
	else
	{
		
		for(i=first;i->link!=NULL && (i->word!=a); i=i->link);
		
		if((i->word!=a))
			i->link=temp;
					
	}
	
}

/*
 * this function sorts the unique words in alphabatical order
 */ 

void list::sort()
{
	list *i, *j;
	string a;
	
	for(i=first;i!=NULL;i=i->link)
	{
		for(j=first;j->link!=NULL;j=j->link)
		{
			if(i->word<j->word)
			{
					a=i->word;
					i->word=j->word;
					j->word=a;
				
			}
		}
	}
	
}

/*
 * This function is used for storing the line numbers in which the 
 * words are present
 */ 

void list::process(string a, int ln)
{
	list *i, *k, *temp; 	
	int j;
	
	for(j=0; a[j]!='\0';j++);
	/*
	 * ispunct() is a function used to check if a character is
	 * punctuation or not.
	 */  
	
	if(ispunct(a[j-1]))
	{
		
		a = a.substr(0, a.size()-1);
		
	}
	
	i=first;
	
	for(i=first;i->link!=NULL && i->word!=a;i=i->link);
	
	if(i->word==a)
	{
		k=i;
		if(i->link2==NULL)
		{
			temp = new list;
			temp->lnum=ln;
			temp->link=NULL;
			temp->link1 = NULL;
			temp->link2=NULL;
			i->link1=temp;
			i->link2=temp;	
		}
		else if(i->link2!=NULL)
		{
				i=i->link2;
				if(i->lnum<ln)
				{
					temp = new list;
					temp->lnum=ln;
					temp->link=NULL;
					temp->link1 = NULL;
					temp->link2=NULL;
					i->link1=temp;
					k->link2=temp;
				}
		}
	}

}

/*
 * This function is used to output the result into a text file
 */ 

void list::display()
{
	
	list *j, *i;
	ofstream op("output.txt",  ios::app);
	for(j=first;j!=NULL;j=j->link)
	{
		op<<j->word<<" ";
		i=j->link1;
		while(i!=NULL)
		{
	
			op<<i->lnum<<" ";
			i=i->link1;
			
		}
		op<<endl;
	}
	op.close();
}



int main()
{
	
	int ln=1, ln1=1, line=0;
	string word, b, lin, store;
	list s;
	
	ifstream ip("input.txt");
	ifstream ip0("input.txt");
	ifstream ip1("input.txt");
	ifstream ip2("input.txt");
	ofstream op("output.txt");
	
	 while (getline(ip2, b))
	{
        line++;
	}

/*
 * Printing the line number and line from input file
 */ 
	while(!ip0.eof())                    
	{						
		getline(ip0, store);
		if(ln1<=line)
		{	
			op<<ln1<<" "<<store<<endl;
			ln1++;
		}
		
	}
	 
	
	op<<endl;
	op.close();

/*
 * Creating the list of the unique words from the input file
 * using the function create(string).
 */ 
	while(!ip.eof())                    
	{								
		ip>>word;
		s.create(word);
	}
/*
 * Calling the sort function to sort the list of words in 
 * alphabetical order.
 */ 	
	
	s.sort();
	
	ln=1;
/*
 * Storing the line number of the words and storing them using
 * the function process(string, int)
 */ 	
	
	while(!ip1.eof())                    
	{								
		
		getline(ip1, lin);
		istringstream iss(lin);
		while(iss >> word)
		{
			s.process(word, ln);
		}
		ln++;
	}

/* 
 * Writing completed list onto a file named output.txt
 */
  
	s.display();
	
}

