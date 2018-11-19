#include<iostream>
#include<utility>
#include<vector>
#include<list>
#include<string>
#include<sstream>
#include<unistd.h>
#include<cstring>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

using namespace std;
void print(char* str){
int i =0;
while(str[i]!='\0'){
  cout << str[i];i++;
}
cout << endl;
}
struct variables_space{   // define structure to holds variable

vector<string> name;
vector<string> value;
int size; 

};
void add(variables_space& my_space,vector<string>& key_val );
void last(variables_space& my_space,string& str);

int res( string& name); // fonction to check that variable name are reasonable

int main(){

variables_space space;   // declare a variable space
space.size=0;

string str;              // variable to hold a new token
string line;          // variable to hold a new line 
string str1;         // first token 
string prompt="mysh$ ";
string directory="project4";
vector<pair<pid_t,string>> process;
pid_t id = getpid();
int status;
char back;

while(str1!="bye" ){   


cout<<directory<<":"<<prompt ;
vector<string> words;
getline(cin,line);           // getline 


if(  process.size()>0) {  
    for(size_t i=0;i<process.size();i++) { 
      pid_t attempt = process[i].first;
      pid_t active = waitpid(attempt,&status,WNOHANG);  
      if(active !=-1 && active !=0){                        // remove finished processess
           
        vector<pair<pid_t,string>> updated;
        for(size_t j=0;j<process.size();j++){
           if( j!=i){
              updated.push_back(process[j]);
           }
   }    process = updated ;
     }
   }
  
      } 

istringstream iss(line);
iss >>str1;           // etract first token
while(iss >> str){
  if( str[0]!='%' &&  str!="%") 
   words.push_back(str);              // extract tokens 
 }

if(str1 == "set" && words.size()==2 ){
  if( res(words[0] )){
    add(space,words);                   // set a new variable 
    
   }
  
 }
else if( str1=="show" && words.size()==1){
  last(space,words[0]);
  
}

else if( str1=="setprompt" && words.size()==1){
  prompt=words[0];
 } 
else if(str1==" bye"){ }                 // quit mysh
else if(str1==""){}

else if( str1=="cd" && words.size()==1){
    string path = words[0];
    
   
    char* path_name = new char[str.length()+1];
    strcpy(path_name,path.c_str());
    if(path[0]=='/'){
    char* new_dir= getwd(path_name);              // change directory with absolute path_name
    if(new_dir!=NULL){
     directory = string(new_dir);}
    else{
      cout<<" unable to find entered path name" << endl;}
  }
    else {
      int res=chdir(path_name);                 // change directory with relative path_name 
      char* new_dir = new char[100];
   
      getcwd(new_dir,100);
      if(res==0){ 
        directory = string(new_dir);}
      else{
        cout <<" unable to find entered path name" << endl;}
 
} 
 }

 else if( str1 =="listp" && words.size()==0){
   if(process.size()==0){
      cout <<" no process is running" << endl; 
   }
   else{
      for(size_t i=0; i<process.size();++i){             // list running process
        
          cout<<"program name: "<< process[i].second<<" pid: "<<process[i].first << endl;
    }
  }
 }
 else if(str1!=""){
   int len = words.size();
   back='a';
   if(len!=0){
     if(words[len-1][0]=='&'){
       back ='&';words.pop_back();}}
   char* program = new char[str1.size()];
   char* param[words.size()+2]; param[words.size()+1]=NULL;
   param[0] = new char[str1.size()]; 
   strcpy(param[0],str1.c_str()); 
   for(size_t i=1;i<=words.size();i++){
   param[i] = new char[words[i-1].size()];
   strcpy( param[i] , words[i-1].c_str());
 
}
    
   strcpy(program,str1.c_str());
    id = fork();
   if(back!='&' && id!=0){
      
      waitpid(id,&status,0);     // wait for child process to end 
}
   else if(back=='&' && id!=0) {            
       process.push_back(make_pair(id,str1));             // add background process
 }
   if(id==0){
 
  
    char* path = getenv("PATH");
    char* env[] = {path,NULL};
  
    execvpe(program,param,env);            // execute program 
    if(str1!="bye" && str1!="")    
      cout << " command or program do not exist" << endl;
   }
 
}

  else {
   if(str1!="bye" &&str1!="")
    cout << " invalid syntax line" << endl;
 }
}
return 0;

}

int res(string& name){

 if(!isalpha(name[0])){
   cout << " the first character of a variable name must be a letter" << endl;
   return 0;
 }
 return 1;
}

void last(variables_space& my_space,string& str){
bool found = false; 
for( int i =0; i< my_space.size; i++){
  if(my_space.name[i]==str)
    cout << "latest value = " << my_space.value[i] << endl;
    found = true;
}
if(!found){
 cout <<" variable undefined" << endl;
 }
}


void add(variables_space& my_space,vector<string>& key_val){
 bool found = false;
 string key = key_val[0]; 
 string val = key_val[1];
 
 for(int i=0; i < my_space.size; i++){
  if(my_space.name[i]==key){
    my_space.value[i]=val;
    found = true;
  }
}
 if(!found){
  my_space.name.push_back(key);
  my_space.value.push_back(val);
  my_space.size++;
 }
 
}
