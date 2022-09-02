#include <bits/stdc++.h>
#include "BST.cpp"

using namespace std;

vector<string> parse;
void split (string str, char seperator)  
{  
    parse.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            parse.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
}  

int main(){
  
    BST *b = new BST();
    string s;
    while(getline(cin,s)){
        split(s,' ');
        if(parse[0]=="ADD"){
				if(b->insert(stoi(parse[1]),stoi(parse[2]))){
					cout<<"SUCCESSFULLY INSERTED!"<<endl;
				}else{
					cout<<"INSERTION FAILED!"<<endl;
				}
			}else if(parse[0]=="DEL"){
				if(b->remove(stoi(parse[1]),stoi(parse[2]))){
					cout<<"SUCCESSFULLY DELETED!"<<endl;
				}else{
					cout<<"JOURNEY NOT FOUND!"<<endl;
				}
			}else if(parse[0]=="FIND"){
				if(b->find(stoi(parse[1]),stoi(parse[2]))){
					cout<<"JOURNEY FOUND!"<<endl;
				}else{
					cout<<"JOURNEY NOT FOUND!"<<endl;
				}
			}else if(parse[0]=="TRAVERSE"){
				if(parse[1]!="PRE" && parse[1]!="POST" && parse[1]!="IN"){
					cout<<"INVALID REQUEST!"<<endl;
				}
				int x = (parse[1]=="PRE")?0 : ((parse[1]=="POST")?1:2);
				b->traverse(x);
			}else if(parse[0]=="GETMIN"){
				cout<<b->getMinimum()<<endl;
			}else if(parse[0]=="BOUNDS"){
				cout<<b->countJourneysInPriceBound(stoi(parse[1]),stoi(parse[2]))<<endl;
			}else if(parse[0]=="PRINT"){
				b->printBST("");
			}else{
				cout<<"INVALID REQUEST"<<endl;
			}
    }
	

}
