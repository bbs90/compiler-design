/*
 * B.Bhargav Sastry
 * COSC 5390.001   
 * Programming Language
 * COURSE ASSIGNMENT II
 * Fall 2015
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
 
 
using namespace std;
/*
 * The function part2 is provided with the input take form the 
 * input file in form of an array. This function takes as input 
 * a pascal program and gives as output the token and the token type 
 * present in the pascal program. The output of this function is 
 * printed in file "output.txt" 
 */ 
void part2(int a[][14]);

/*
 * The function kwsearch is used to identify if a given token is 
 * a keyword or not. It takes as input a token and returns the 
 * value "1" if the token is a keyword or the value "0" if the token 
 * is not a keyword. 
 */ 
int kwsearch(string str);
int lex_state=1;

/*
 * The class list is used for creating the symbol table using linked
 * list. It contains the function "enter" which is used to enter the 
 * identifiers in the symbol table. The function "stable" is used 
 * to print the symbol table in file "output.txt"
 */ 
class list
{
	string word;
	list *link;
	
	public:
		void enter(string a, int b);
		void stable();
		
	
};

list *first = NULL;

void list::enter(string a, int b)
{
	list *temp, *i;
	if(b==0)
	{
		temp = new list;
		temp->word=a;
		temp->link = NULL;
		if(first==NULL)
		{
			first=temp;
		}
		else
		{
			for(i=first;(i->link!=NULL) && (i->word!=a); i=i->link);
			if((i->link==NULL) && i->word!=a)
				i->link=temp;
		}
	}
	
}

void list::stable()
{
	list *j;
	ofstream op("output1.txt", ios::app);
	op<<endl<<endl;
	op<<"SYMBOL TABLE"<<endl<<endl;
	op<<"TOKEN"<<"\t\t\t"<<"TYPE"<<endl;
	for(j=first;j!=NULL;j=j->link)
	{
		op<<j->word<<"\t\t\t"<<"IDENTIFER"<<endl;
	}
}


int main()
{

	int  a[21][14], i=0, j=0, num;
	string store;
	list p;
	ifstream ip("table.txt");
	ofstream op("output1.txt");
	ifstream ip1("LAB1.txt");

	for(i=0;i<21;i++)
	{
		for(j=0;j<14;j++)
		{
			ip>>num;
			a[i][j]=num;
		}
	}


	part2(a);
	p.stable();

}

void part2(int a[][14])
{
	int i=0,j=0, k,cp=0;
	char store[200], temp1, temp2;
	list s;
	string m;
	string col = "{}(*):=<>";
	string colname[] ={"LEFT CURLY BRACKET", "RIGHT CURLY BRACKET", 
		"LEFT  PARENTHESIS", "STAR", "RIGHT  PARENTHESIS", "COLON", 
		"EQUAL TO", "LESS THAN", "GREATER THAN"};
	string pun = ";.,+-/*^[]\'\"#$";
	string punname[] = {"SEMICOLON", "PERIOD", "COMMA", 
		 "PLUS", "MINUS", "SLASH", "STAR", "CARET", 
		 "LEFT SQUARE BRACKET", "RIGHT SQUARE BRACKET", 
		 "SINGLE QUOTE", "DOUBLE QUOTE", 
		"POUND", "DOLLAR"};	
	string tok, lin;
	ifstream ip2("LAB1.txt");
	ifstream ip4("LAB1.txt");
	ofstream op("output1.txt", ios::app);
	
	
	//The variable cp is used as current pointer
	while(!ip4.eof())
	{
		getline(ip4, lin);
		op<<lin<<endl;
	}
		
	op<<"TOKEN"<<"\t\t\t"<<"TYPE"<<endl;
	lex_state=1;
	while(!ip2.eof())                    
	{								
		
		getline(ip2, lin);
		for(cp=0;lin[cp]!='\0';cp++)
		{
			
			store[i]=lin[cp];
			if(isalpha(lin[cp]))
			{
				lex_state=a[lex_state][1];		
			}
			if(isdigit(lin[cp]))
			{
				lex_state=a[lex_state][2];
			}
			if(ispunct(lin[cp]))
			{
				int fl=1;
				temp2=lin[cp];
				for(k=0;k<9;k++)
				{
					temp1=col[k];
					if(temp1==temp2)
					{	
						fl=0;
					}
				}

				if(fl)
				{
					lex_state=a[lex_state][13];
				}
		
			}
			
			if(isspace(lin[cp]))
			{
				lex_state=a[lex_state][12];
			}
			for(k=0;k<9;k++)
			{
				temp1=col[k];
				temp2=lin[cp];
				if(temp1==temp2)
				{	
					lex_state=a[lex_state][k+3];
				}
			}
			
			switch(lex_state)
			{
				// state 3 for accepting identifers and keyword.
				case 3:
				{
				
					tok='\0';
					store[i]='\0';
					tok=store;
					while(isspace(tok[0]))
					{
						tok=tok.substr(1, tok.size());
					}
					/* Since we need to back up in state 3
					 * cp-- is done. This is implemented
					 * logically and not taken from the
					 * symbol table
					 */ 
					cp--;
					i=-1;
					j=kwsearch(tok);
					s.enter(tok, j);
					if(j)
					{
						op<<tok<<"\t\t\t"<<"KEYWORD"<<endl;
					}
					else
					{
						op<<tok<<"\t\t\t"<<"IDENTIFIER"<<endl;
					}
					store[0]='\0';
					lex_state=1;
				}
				break;
				//case 5 for accepting constants
				case 5:
				{
					tok='\0';
					store[i]='\0';
					i=-1;
					tok=store;
					while(isspace(tok[0]))
					{
						tok=tok.substr(1, tok.size());
					}
					/* Since we need to back up in state 5
					 * cp-- is done. This is implemented
					 * logically and not taken from the
					 * symbol table
					 */ 
					cp--;
					op<<tok<<"\t\t\t"<<"CONSTANT"<<endl;
					store[0]='\0';
					lex_state=1;
				}
				break;
				// state 7 takes coments but does not ptint then
				// into the file as comments are not required.
				case 7:
				{
					store[0]='\0';
					i=-1;
					lex_state=1;
				}
				break;
				// state 11 aslo takes coments but does not ptint 
				// them into the file as comments are not 
				// required.
				case 11:
				{
					store[0]='\0';
					i=-1;
					lex_state=1;
				}
				break;
				// case 13 accepts assignment operator.
				case 13:
				{
					tok='\0';
					store[i+1]='\0';
					i=-1;
					tok=store;
					while(isspace(tok[0]))
					{
						tok=tok.substr(1, tok.size());
					}
					op<<tok<<"\t\t\t"<<"ASSIGNMENT OPERATOR"<<endl;
					store[0]='\0';
					lex_state=1;
				}
				break;
				// case 15 accepts relational operator.
				case 15:
				{
					tok='\0';
					store[i+1]='\0';
					i=-1;
					tok=store;
					while(isspace(tok[0]))
					{
						tok=tok.substr(1, tok.size());
					}
					op<<tok<<"\t\t\t"<<"LESS THAN OR EQUAL TO"<<endl;
					store[0]='\0';
					lex_state=1;
				}
				break;
				// case 16 accepts relational operator.
				case 16:
				{
					tok='\0';
					store[i+1]='\0';
					i=-1;
					tok=store;
					while(isspace(tok[0]))
					{
						tok=tok.substr(1, tok.size());
					}
					op<<tok<<"\t\t\t"<<"NOT EQUAL TO"<<endl;
					store[0]='\0';
					lex_state=1;
				}
				break;
				// case 18 accepts relational operator.
				case 18:
				{
					tok='\0';
					store[i+1]='\0';
					i=-1;
					tok=store;
					while(isspace(tok[0]))
					{
						tok=tok.substr(1, tok.size());
					}
					op<<tok<<"\t\t\t"<<"GREATER THAN OR EQUAL TO"<<endl;
					store[0]='\0';
					lex_state=1;
				}
				break;
				// case 19 accepts general punction.
				case 19:
				{
					tok='\0';
					store[i+1]='\0';
					tok=store;
					while(isspace(tok[0]))
					{
						tok=tok.substr(1, tok.size());
					}
					j=1;
					for(i=0; i<9;i++)
					{
						m=col[i];
						if(tok==m)
						{	
							j=0;
							op<<tok<<"\t\t\t"<<colname[i]<<endl;	
							break;
						}
					}
					if(j)
					{
						for(i=0; i<14;i++)
						{
							m=pun[i];
							if(tok==m)
							{	
								op<<tok<<"\t\t\t"<<punname[i]<<endl;
								break;
							}
						}
					}
					store[0]='\0';
					lex_state=1;
					i=-1;
				}
				break;
				// case 20 accepts general punction.
				case 20:
				{
					tok='\0';
					store[i]='\0';
					i=-1;
					tok=store;
					/* Since we need to back up in state 20
					 * cp-- is done. This is implemented
					 * logically and not taken from the
					 * symbol table
					 */ 
					cp--;
					while(isspace(tok[0]))
					{
						tok=tok.substr(1, tok.size());
					}
					j=1;
					for(i=0; i<9;i++)
					{
						m=col[i];
						if(tok==m)
						{	
							j=0;
							op<<tok<<"\t\t\t"<<colname[i]<<endl;	
							break;
						}
					}
					if(j)
					{
						for(i=0; i<14;i++)
						{
							m=pun[i];
							if(tok==m)
							{	
								op<<tok<<"\t\t\t"<<punname[i]<<endl;
								break;
							}
						}
					}
					store[0]='\0';
					lex_state=1;
					i=-1;
				}
				break;
			}
			i++;
		}
/*
 * This part of the code will execute if end of line has been reached
 * while lex_state value is "2". The value of "2" means that the 
 * current state is 2 which is for accepting identifers and keyword.
 * For example 
 * begin
 * 	if(...
 * 
 * Here begin is a keyword. The function takes the entire line 
 * and starts at "b" and continues to accept characters till it as 
 * reached the end of line. Before going to the next line the token
 * "begin" must be accepted since end of line is considered as 
 * white space according to the symbol table and transition 
 * must be made.
 * 
 * This transition cannot be made in the for loop  given above
 * as the loop exits when it encounters the end of line and 
 * moves to the next line.
 */ 		
		if((lex_state==2))
		{
			tok='\0';
			store[i]='\0';
			tok=store;
			while(isspace(tok[0]))
			{
				tok=tok.substr(1, tok.size());
			}
			i=-1;
			j=kwsearch(tok);
			if(j)
			{
				op<<tok<<"\t\t\t"<<"KEYWORD"<<endl;
			}
			else
			{
				op<<tok<<"\t\t\t"<<"IDENTIFIER"<<endl;
			}
			store[0]='\0';
			lex_state=1;
		}
		i=0;
	}
}

int kwsearch(string str)
{
	int i, flag=0;
	string keywords[45];
	ifstream ip3("keywords.txt");

	for(i=0;i<44;i++)
	{	
		ip3>>keywords[i];
	}
	for(i=0;i<44;i++)
	{
		if(str==keywords[i])
		{
			flag=1;
			break;
		}	
	}
	if(flag)
		return 1;
	return 0;
}
