/**
 * @file lab8.cpp
 * @author Reginald Kotey Appiah-Sekyere
 * @description BST Tree implementation in C++
 * @date 2022-11-03
 */
#pragma once
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<math.h>
#include<queue>
#include<vector>

using namespace std;
template <typename T1, typename T2>
class Node
{
	private:
		T1 key;					//city name
		vector<T2> value;		//list of hotels in the city
		Node<T1,T2>* left;		//left child
		Node<T1,T2>* right;		//right child
		Node<T1,T2>* parent;	//pointer to the parent node
	public:
		Node(T1 key): key(key),left(nullptr),right(nullptr), parent(nullptr) 
		{}
		void print(string stars="")	//print all or only those hotels with specific stars.
		{
			int counter=0;
			cout<<std::left<<setw(50)<<"Name"<<" "<<setw(10)<<"City"<<" "<<setw(5)<<"Stars"<<" "<<setw(10)<<"Price"<<" "<<setw(20)<<"Country"<<" "<<"Address"<<endl;
			cout<<"------------------------------------------------------------------------------------------------------------"<<endl;

			for(auto it:value){
				if(stars=="" or stars==it->getStars())
				{
					it->print2();
					counter++;
				}
			}
			cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<counter<<" records found."<<endl;
		}

		template<typename,typename> friend class BST;
};
//=============================================================================
template <typename T1, typename T2>
class BST
{
	private:
		Node<T1,T2> *root;
	public:
		BST();									//constructor
		~BST();									//destructor
		Node<T1,T2>* getRoot();						//returns the root of the Tree
		void insert(Node<T1,T2>* ptr,T1 key, T2 value);			//Insert key into tree/subtree with root ptr
		int height(Node<T1,T2> *ptr);				    //Find the height of a tree/subtree with root ptr
		Node<T1,T2>* find(Node<T1,T2> *ptr,T1 key,string stars);		//Find and returns the node with key
		Node<T1,T2>* findMin(Node<T1,T2> *ptr);				//Find and return the Node<T1,T2> with minimum key value from a tree/subtree with root ptr
		void remove(Node<T1,T2> *ptr,T1 key, T2 value);			//Remove a node with key from the tree/subtree with root
		void postorderdelete(Node<T1,T2>* node);
		void nodedelete(Node<T1,T2>* node);
		void removeaboveexternal(Node<T1,T2>* node,Node<T1,T2>* nullchild);
};
//=====================================================================
//write implementation of all methods below

template <typename T1, typename T2> BST<T1,T2>::BST(){
	root=nullptr;//makes the root point to nullptr
}
template <typename T1, typename T2> BST<T1,T2>::~BST(){
	postorderdelete(root);//deletes all the nodes in the tree in a postorder way
}
template <typename T1, typename T2> Node<T1,T2>* BST<T1,T2>::getRoot(){
	return root;//returns the root
}
template <typename T1, typename T2> void BST<T1,T2>::insert(Node<T1,T2>* ptr,T1 key, T2 value){//function that inserts a node in the tree
	if(getRoot()==nullptr){//if the tree is empty,
		root=new Node<T1,T2>(key);//assign new node to root
		root->value.push_back(value);//push the hotel to the back of the tree
		return;//exit function
	}
	if(ptr==nullptr){//if the ptr is null trow error because tree will be imbalance
		throw underflow_error("Cannot place node here!");
	}
	else{//otherwise
		Node<T1,T2>* prev=nullptr;//create a node pointer that will point to the previous element and initiate it to 0
		while(ptr!=nullptr){//while we are not at an external node,
			prev=ptr;//copy ptr into prev
			if(key==ptr->key){//if the key is equal to the key of the current node
				ptr->value.push_back(value);//add hotel to that city
				return;//exit function
			}
			else if(key<ptr->key){//other if the key is lesser that that of the cureent node
				ptr=ptr->left;//move to the left
			}
			else{//otherwise move to the right
				ptr=ptr->right;
			}
		}//we exit the loop once we reach an external node
		if(key<prev->key){//if the prev is to the right of the external node
			prev->left=new Node<T1,T2>(key);//create new node and pass it to the left child of prev
			prev->left->value.push_back(value);//push the value into the vector
			prev->left->parent=prev;//make the parent of the new node the prev node
		}
		else{
			prev->right=new Node<T1,T2>(key);//if it is on the right do same but this time pass it to the rigth child
			prev->right->value.push_back(value);
			prev->right->parent=prev;
		}
	}
}
template <typename T1, typename T2> int BST<T1,T2>::height(Node<T1,T2> *ptr){//calculates the height of the node passed
	if(ptr==nullptr){//if the node is null
		return 0;//height is zero
	}
	int total=1;//create new variable and store 1
	int lefttotal=height(ptr->left);//find the height of the left child and
	int righttotal=height(ptr->right);//find the height of the right child
	if(lefttotal>=righttotal)total+=lefttotal;//if left height is greater or equal to rights height add the leftheight to the total
	else{total+=righttotal;}//otherwise add the rightheight to the total
	return total;//return the total height
}
template <typename T1, typename T2> Node<T1,T2>* BST<T1,T2>::find(Node<T1,T2> *ptr,T1 key,string stars){//this function finds cities
	if(getRoot()==nullptr){
		throw underflow_error("Tree is empty!");//if the tree is empty trow an error
	}
	if(ptr==nullptr){
		throw underflow_error("No hotels here!");//if the ptr entered is null trow error
	}
	else{
		while(ptr!=nullptr){//else go through the tree until you find the city
			if(key<ptr->key){
				ptr=ptr->left;
			}
			else if(key>ptr->key){
				ptr=ptr->right;
			}
			else{
				return ptr;//in my method i wont be needing stars so just return the node
			}
		}
		throw overflow_error("Can't find city!");//else throw error
	}
}
template <typename T1, typename T2> Node<T1,T2>* BST<T1,T2>::findMin(Node<T1,T2> *ptr){//returns the min
	if(ptr->left==nullptr){//if the left is an external node
		return ptr;//return the current node
	}
	return findMin(ptr->left);//otherwise call the findMin on the left child
}
template <typename T1, typename T2> void BST<T1,T2>::remove(Node<T1,T2> *ptr,T1 key, T2 value){//this function removes a hotel from the tree
	if(getRoot()==nullptr){
		throw underflow_error("Tree is empty!");//if the tree is empty throw an error
	}
	if(ptr==nullptr){
		throw underflow_error("No hotels here!");
	}
	else{
		while(ptr!=nullptr){//go through the tree to find node/citiy
			if(key<ptr->key){
				ptr=ptr->left;
			}
			else if(key>ptr->key){
				ptr=ptr->right;
			}
			else{//when found,
				 typename vector<T2>::iterator q;//create iterator
				for(q=ptr->value.begin();q!=ptr->value.end();++q){//go through vector of the node
					if(*q==value){//if we find the value, 
						ptr->value.erase(q);//remove it from the vector
						if(ptr->value.empty())nodedelete(ptr);//if the vector is empty, delete node
						return;//exit loop
					}
				}
				throw underflow_error("Hotel not found!");//if the hotel is not found throw error
			}
		}
		throw overflow_error("Can't find city!");//else throw error
	}
}
template <typename T1, typename T2> void BST<T1,T2>::postorderdelete(Node<T1,T2>* node){//deletes all nodes in postorder
	if (node->left!=nullptr&&node->right!=nullptr) {//if not binary "external"
	postorderdelete(node->left);//delete all left decendants
	postorderdelete(node->right);//delete all right decendants
	}
	if(!node->value.empty()){
		typename vector<T2>::iterator q;//create iterator
		for(q=node->value.begin();q!=node->value.end();++q){//go through vector of the city
			node->value.erase(q);//remove it from the vector
		}
	}
	delete node;//delete node
}
template <typename T1, typename T2> void BST<T1,T2>::nodedelete(Node<T1,T2>* node){//deletes a node
	if(node==nullptr)return;//if the node is external exit function
	else if(node->left==nullptr||node->right==nullptr){//if the node is above external remove above external
		if(node->left==nullptr){
			removeaboveexternal(node,node->left);
			return;}
		else{removeaboveexternal(node,node->right);return;}
	}
	else{//if the node has two internal children
		Node<T1,T2>* temp=findMin(node->right);//find next smallest
		node->key=temp->key;//replace their keys
		node->value=temp->value;//and hotels
		removeaboveexternal(temp,temp->left);//remove above external for the next smallest
		return;
	}
}
template <typename T1, typename T2> void BST<T1,T2>::removeaboveexternal(Node<T1,T2>* node,Node<T1,T2>* nullchild){//removes node above external node
	if(nullchild!=nullptr){cout<<"Check your removeaboveexternal"<<endl;return;}//if the node child is null trow warning
	Node<T1,T2>* nodeparent=node->parent;//create parent node
	if(node->left==nullchild){//if the external is on the left
		if(nodeparent->left==node){//replace that node with the nodes right
			nodeparent->left=node->right;
			delete node;//delete node and 
			if(nodeparent->left!=nullptr)
				nodeparent->left->parent=nodeparent;//update the parent
		}
		else{
			nodeparent->right=node->left;//other wise do same but this time replace with nodes left
			delete node;
			if(nodeparent->right!=nullptr)
				nodeparent->right->parent=nodeparent;
		}
	}
	else{
		if(nodeparent->left==node){
			nodeparent->left=node->left;
			delete node;
			if(nodeparent->left!=nullptr)
			nodeparent->left->parent=nodeparent;
		}
		else{
			nodeparent->right=node->right;
			delete node;
			if(nodeparent->right!=nullptr)
			nodeparent->right->parent=nodeparent;
		}
	}
}