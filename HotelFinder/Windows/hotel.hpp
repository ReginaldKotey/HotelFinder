//============================================================================
// Name         : hotel.hpp
// Author       : Reginald Kotey Appiah-Sekyere
// Version      : 1.0
// Date Created : 03-12-2023
// Date Modified: 
// Description  : 
//============================================================================
#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Hotel
{
	private:
		string name;	//name of the hotel	
		string city;	//city of the hotel
		string stars;	//starts of the hotel
		string price;	//price per night
		string country;	//country
		string address;	//full address of the hotel
	public:
		Hotel(string name,string city, string stars,string price,string country,string address);	//constructor
		string getName();	//returns the name of the hotel
		string getCity();	//returns the city of the hotel
		string getStars();//returns the star rating of the hotel
		string getPrice();//returns the price of the hotel
		string getCountry();//returns the country to which the hotel is located
		string getAddress();//returns the address of the hotel
		string toString();//returns the details of hotels
		void print();//this function prints the details of the hotel
		void print2();//this functions prints the details too
};
//==========================================================
//implement the methods list above in a file called hotel.cpp