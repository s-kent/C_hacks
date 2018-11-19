
#include"StringTable.h"


int StringTable::hash(string item){
 int asci=0;
 for(int i=0; i< item.size();i++){
    char curr_char = item[i];
    int curr_value = int(curr_char);
    asci+= curr_value;
   }
 asci = asci%999;
 return asci;

 }

StringTable::StringTable(){
  for(int i=0;i<MAX;i++){
   bucket[i]=nullptr;
 }

}
void StringTable::destruct(){  // free the string table
  for(int i=0; i<MAX; i++){
   if(bucket[i]!=nullptr){
    stringTableEntry* curr = bucket[i];
    stringTableEntry* next = bucket[i]->next;
    bucket[i]=nullptr;
    while( next !=nullptr){
      delete curr;
      curr = nullptr;
      curr = next;
      next = curr->next;
     }
     delete curr;
     curr = nullptr;
   }
}

}

StringTable::~StringTable(){   // destructor 
destruct();

}  


stringTableEntry* StringTable::insert(string item){           // insert a new string 
   int index = hash(item);
   stringTableEntry* new_node = new stringTableEntry;
   new_node->data = item;
   stringTableEntry* found=nullptr;
   found = search(item);
   if( found!=nullptr){
      return found;
    }
   if(bucket[index] == nullptr){

      bucket[index] = new_node;
      num_entries = num_entries + 1;
    }
   else{
      num_col = num_col+1;
      stringTableEntry* curr = bucket[index];
      stringTableEntry* next = bucket[index]->next;
      while( next!= nullptr){
         curr = next;
         next = curr->next;
       }
     curr->next = new_node;    
    }

  return new_node;

}
stringTableEntry* StringTable::search(string item){     // search given string , return reference if found, return nullptr if not found
 int index = hash(item);
 stringTableEntry* found = nullptr;
 if( bucket[index]==nullptr){
   return found ;
  }
else{
   stringTableEntry* curr = bucket[index];
   stringTableEntry* next = bucket[index]->next;
   while( next!= nullptr){
      if( curr->data == item){
        found = curr;
          }  
      curr = next;
      next = curr->next;
      }
      
        if(curr->data==item){
           found = curr;
         }
       
    }
   return found;
 }


string StringTable::search(stringTableEntry* ref){     // search given ref , returns empty string if not found
string str = "";   
for(int i=0; i< MAX; i++){
 if(bucket[i]!=nullptr){
    stringTableEntry* curr = bucket[i];
    stringTableEntry* next = bucket[i]->next;
    while( next != nullptr){
      if(curr->data == ref->data){
        return curr->data;
       }
      curr = next;
      next = curr->next;
     }
      
    if(curr->data == ref->data){
           return curr->data;
      }
       
     
  }  
return str;
}
    

}
void StringTable::print(){             // print function 
double p = ((double)num_col)/((double)num_entries);

for(int i= 0 ; i< MAX; i++) {
  if(bucket[i]!=nullptr){
    stringTableEntry* curr = bucket[i];
    stringTableEntry* next = bucket[i]->next;

    while(next != nullptr){
     cout <<" , entry n "<<i<<": "<< curr->data;
     curr = next;
     next = curr->next;
      }
   
      cout <<" , entry b "<<i<<": "<< curr->data << endl; 
     
   }

}

cout << " collision percentage is: " << p << endl;


}







