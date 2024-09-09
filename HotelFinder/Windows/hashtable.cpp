#include "hashtable.hpp"

HashTable::HashTable(int capacity){
    this->capacity=capacity;//make this capacity the new capacity
    buckets= new list<Entry> [capacity];//create new dynamic array with capacity capacity and data type list<Entry>
    size=0;//initiate size to 0
    collisions=0;//initiate collisions to 0
}	
unsigned long HashTable::hashCode(string key){
  unsigned long hcode=0;//create variable to store hashcode
  for(unsigned int i=0;i<key.length();i++){
    hcode+=((unsigned int)key[i]*pow(33,i%10));//polynomial hashcode way but exponent is always between 0 and 10 to prevent heavy polynomial computation ie, O(n^n)
  }
  unsigned int index=hcode%capacity;//return the hashcode mod the capacity to make the hcode an index of the array
  return index;
}
void HashTable::insert(string key, Hotel* value){
  unsigned long index=hashCode(key);//get the hashcode
  if(buckets[index].empty()){//if the list at that index is empty
    Entry* rekas = new Entry(key,value);//create a new entry and store its address in a pointer
    buckets[index].push_front(*rekas);//push the entry to the front of the list
    cityRecords.insert(cityRecords.getRoot(),value->getCity(),value);//insert the hotel into the cityRecords tree
    size++;//increase size
    return;//break from this function
  }
  else{//else if the list is not empty
    collisions++;//increase collisions
    for(list<Entry>::iterator q=buckets[index].begin();q!=buckets[index].end();++q){
      if(q->key==key){
        cityRecords.remove(cityRecords.getRoot(),q->value->getCity(),q->value);//remove q hotel from the tree
        q->value=value;//update the value of q
        cityRecords.insert(cityRecords.getRoot(),value->getCity(),value);//insert the new hotel into the tree
        cout<<"Existing Record has been successfully updated in the Database!"<<endl;
        return;
      }
    }//while iterating is we find a key that is same to the one we are inserting, update value and exit function
    Entry* rekas =new Entry(key,value);
    buckets[index].push_front(*rekas);
    cityRecords.insert(cityRecords.getRoot(),value->getCity(),value);
    size++;//increase size
  }
}
Hotel* HashTable::find(string key){
    unsigned long index=hashCode(key);
    if(buckets[index].empty()){//if the list at that index is empty
      return nullptr;
    }
    else{//else if the list is not empty
      int comparisons=0;//set comparisons to 0
      for(list<Entry>::iterator q=buckets[index].begin();q!=buckets[index].end();++q){
        comparisons++;//increase comparisons by 1
        if(q->key==key){
          cout<<"Record found after "<<comparisons<<" comparison(s)."<<endl;
          return q->value;//return the hotel 
        }
      }//while iterating is we find a key that is same to the one we are inserting, update value and exit function
    }
    return nullptr;
}
void HashTable::findAll(string city,string stars){
    cityRecords.find(cityRecords.getRoot(),city,stars)->print(stars);//first find the hotel using the find function that returns the hotel node and call the print function
}
void HashTable::erase(string key){
    unsigned long index=hashCode(key);
    if(buckets[index].empty()){//if the list at that index is empty
      cout<<"Record not Found!"<<endl;
      return;
    }
    else{//else if the list is not empty
      for(list<Entry>::iterator q=buckets[index].begin();q!=buckets[index].end();++q){
        if(q->key==key){
          Hotel* temp=find(key);//find hotel and store in temp
          buckets[index].erase(q);//remove the hotel from the hashtable
          size--;//reduce size
          cityRecords.remove(cityRecords.getRoot(),temp->getCity(),temp);//remove the hotel from the tree
          return;
        }}//while iterating is we find a key that is same to the one we are inserting, update value and exit function
        cout<<"Record not Found!"<<endl;
        return;
    }
} 
unsigned int HashTable::getSize(){
    return size;//returns the size of the hashtable
}
unsigned int HashTable::getCollisions(){
    return collisions;//returns the total collisions
}
void HashTable::dump(string path){
  ofstream rekas(path);//create an output file named rekas
  if(!rekas.is_open()){//if the file does not open
    cerr<<"Could not open filepath!"<<endl;//print error message
    return;//quit function
  }
  for(unsigned int i=0;i<capacity;i++){
    for(auto it:buckets[i]){//go through the hashtable
      rekas<<it.value->toString();//call the toString function and send it to the output file
      rekas<<'\n';//pass new line to output file
    }
  }
  cout<<"Dump done!"<<endl;
  rekas.close();//close the output file
}
HashTable::~HashTable(){
    for(unsigned int i=0; i<capacity; i++)//for every index, delete every entity in the list
      buckets[i].clear();	//delete the list
    delete buckets;//delete the array
}