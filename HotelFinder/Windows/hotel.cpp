#include"hotel.hpp"

Hotel::Hotel(string name,string city, string stars,string price,string country,string address){
    this->name=name;//equates this name to of the hotel to what the user entered
    this->city=city;
    this->stars=stars;
    this->price=price;
    this->country=country;
    this->address=address;
}
string Hotel::getName(){
    return name;
}	
string Hotel::getCity(){
    return city;
}	
string Hotel::getStars(){
    return stars;
}
string Hotel::getPrice(){
    return price;
}
string Hotel::getCountry(){
    return country;
}
string Hotel::getAddress(){
    return address;
}
string Hotel::toString(){
    return name+','+ city+','+stars+','+price+','+country+','+address;
}
void Hotel::print(){
    cout<<"Hotel Name :  "<<name<<'\n'<<"City       :  "<<city<<'\n'<<"Stars      :  "<<stars<<'\n'<<"Price      :  "<<price<<"$/night\nCountry    :  "<<country<<"\nAddress    :  "<<address<<endl;
}
void Hotel::print2(){
    cout<<std::left<<setw(50)<<name<<" "<<setw(10)<<city<<" "<<setw(5)<<stars<<" "<<setw(10)<<price<<" "<<setw(20)<<country<<" "<<address<<endl;
}