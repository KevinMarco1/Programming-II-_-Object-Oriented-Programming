// ASSIGNMENT 2 :: OOP [programming 2]

/*
#############################################################################################################################################

    ASSIGNMNET 2 - PROG2 - CS213
    PROJECT :: ONLINE SHOOPING SYSTEM
    DATE    :: Autumn 2021.12.3
    Lab     :: S35
    AUTHORS ::
        1 - David George Monir 			ID : 20201059
        2 - Kevin Marco Marcory  		ID : 20200401


    PURPOSE & Features ::
        The main objective for this online shopping system is to manage the shopping process , from the sellers
        and their items that provides sellers with their data name , email , items he has and maximum number of
        items he can provide . and provide each item with its ID m name , and quantity of this item the seller
        has and its unit price .

        - regards the options it provides for seller :::  adding an item  , selling an item  , printing items ,
          finding an item by its ID and direct insertion and extraction .

        - regards the options it provides for item   :::  equality checking , quantity increment  or either
          decrement , and  also direct insertion and extraction .

#############################################################################################################################################
*/

// including all needed libraries among the assigment { iostream , istream , ostream , math }
// while ( x , y ) syntax used to still doing x until a specfic action take place which is y

#include <bits/stdc++.h>

using namespace std;

class Item{
    private:

        string name_;
        int quantity_;
        double price_;
        int id_ ;

    public:
        static int ID ;
        // Methods
            // Constructors

                // Deafult Constructor
                /*
                    Parameters : Non
                    process    : Intialization to all  member variables of the item's class
                    Return     : Non
                */

                Item(){
                    name_ = "" ;
                    quantity_ = 0 ;
                    price_ = 0 ;

                    // asssigning value of ID static value to id_ memeber of item
                    id_ = ID;

                    // increment no. of ID ( increment no of items created and " used " ! )
                    ++ID ;

                }

                // parameterized Constructor
                /*
                    Parameters : it takes name , quantity and price of the item's class
                    process    : assign the member variables of the item's object to the passed arguments
                    Return     : Non
                */

                Item(string name, int quantity, double price){
                    name_ = name;
                    quantity_ = quantity;
                    price_ = price;
                }

                // Copy Constructor
                /*
                    Parameters : it takes an item object as parameter
                    process    : copy the data from the parameter to the current object
                    Return     : Non
                */

                Item(Item &item){
                    name_ = item.name_;
                    quantity_ = item.quantity_;
                    price_ = item.price_;
                }

            // Setters

                // name setter
                /*
                    Parameters : it takes a string name
                    process    : assign the name variable of the class item to the string parameter
                    Return     :  Non
                */

                void setname(string name){
                    name_ = name;
                }

                // qunatity setter
                /*
                    Parameters : it takes an integer quantity
                    process    : assign the quantity variable of the class item to the quantity parameter
                    Return     : Non
                */

                void setquantity(int quantity){
                    quantity_ = quantity ;
                }

                // price setter
                /*
                    Parameters : it takes an double price
                    process    : assign the price variable of the class item to the price parameter
                    Return     : Non
                */

                void setprice(double price){
                    price_ = price;
                }

            // Getters

                // name getter
                /*
                    Parameters : Non
                    process    : has no process
                    Return     : return the  name of the item
                */

                string getname(){
                    return name_;
                }

                // quantity getter
                /*
                    Parameters : Non
                    process    : has no process
                    Return     : return the quantity of the item
                */

                int getquantity(){
                    return quantity_;
                }

                // price getter
                /*
                    Parameters : Non
                    process    : has no process
                    Return     : return the price of the item
                */

                double getprice(){
                    return price_;
                }

                // id getter
                /*
                    Parameters : take an integer value
                    Process    : plus the quantity of current object to the integer value parameter
                    Return 	: has no return type
                */

                int getId(){
                    return id_;
                }

            // Operator over loading

                // equality opertor
                bool operator==(Item &item){
                    if (item.name_ == name_){
                        return true;
                    }
                    else{
                        return false;
                    }
                }

                // += operator
                void operator += ( int value ) {
                    quantity_ += value;
                }

                // -= operator
                void operator -= ( int value ) {
                    quantity_ -= value;
                }


                // extraction operator
                friend istream & operator >> ( istream &in , Item &item ){

                    cout << "Enter Item Name     : ";
                    // in >> item.name_;
                    in.ignore() ;
                    getline( in , item.name_ ) ;

                    cout << "Enter Item quantity : ";
                    while ( in >> item.quantity_ , item.quantity_ < 1 ) {
                            cout << "Please enter a valid quantity !! "  ;
                    }

                    cout << "Enter Item price    : ";
                    while ( in >> item.price_ , item.price_ < 1 ) {
                            cout << "Please enter a valid price !! "  ;
                    }

                    return in;
                }

                // insersion operator
                friend ostream & operator << ( ostream &out , const Item & item ){
                    out << "\nItem Name is      : "   << item.name_
                        << "\nItem ID id        : "   << item.id_
                        << "\nItem Quantity is  : "   << item.quantity_ << " item"
                        << "\nItem price is     : "   << item.price_    << endl ;
                    return out;
                }

};

// Intalizing the ID static member of item class with one [1-based counting used items]
int Item :: ID = 1 ;


class Seller{
    private:

        string name_;
        string email_;
        Item *items_;
        int maxItems_;
        int size_;

    public:
        // Methods

            //Constructors

                // Deafult constructor
                /*
                    Parameter : Non
                    Process : Intialize all member variables of Seller's Object
                    Return : Non
                */

                Seller(){
                    size_ = 1;
                    name_ = "";
                    email_ = "";
                    maxItems_ = 0;
                }

                // Parameterized Constructor
                /*
                    Parameter :Non
                    Process :Assign all member variables of Seller's Object
                    Return :Non
                */

                Seller(string name , string email ,int maxItems){
                    size_ = 1;
                    name_ = name;
                    email_ = email;
                    maxItems_ = maxItems;
                    items_ = new Item [maxItems];
                }

            // General methods

                // Adding new element
                /*
                    Parameter : Take an object item
                    Process : check the item if exist or not .
                        if it exist--> add the quantity of the object to corresponding object On the array (by chacking the name of both objects).
                        else --> will look for empty cell in the array to add this item.
                    Return : true if item added  successfully , false if the capcity is full
                */

                bool add(Item &item){
                    for(int i = 0; i < size_ ; i++){
                        if( items_[i] == item ){
                            items_[i] += item.getquantity();
                            return 1;
                        }
                    }
                    if(size_ == maxItems_ + 1 ){
                        return 0;
                    }
                    else{
                        items_[size_ - 1].setname     (item.getname()) ;
                        items_[size_ - 1].setquantity (item.getquantity()) ;
                        items_[size_ - 1].setprice    (item.getprice()) ;
                        size_ ++ ;
                        return 1 ;
                    }
                }


                // selling an element
                /*
                    Parameter : Take a string  , quantity of the item we want to sell
                    Process : check the string of the item we want to sell it exist or not on seller's goods
                        if it exist --> it will check if the quantity that user want , satisfied him or not.
                        else --> then the enterned good is not found on seller's goods.
                    Return : true if item sold successfully .
                        false if item has not found or the quantity that user need is bigger than the quantity of seller's item
                */

                bool sell(string item , int quantity){
                    for(int i = 0 ; i < size_ && i < maxItems_ ; i++){
                        if(items_[i].getname() == item){
                            if(items_[i].getquantity() >= quantity){
                                items_[i] -=quantity;
                                return true;
                            }
                            else{
                                cout << "\nThere is only " << items_[i].getquantity() << " left for this item" << endl;
                                return false;
                            }
                        }
                    }
                    cout << "\nSorry, Item not Found " << endl ;
                    return false ;
                }


                // printing items
                /*
                    Parameter :Non
                    Process : print all information about Seller's goods
                    Return : it's return nothing
                */

                void printItems(){
                    for(int i = 0 ; i < size_ - 1  ; i++){
                        cout << "\n# of Item : " << i + 1  ;
                        cout << items_[i];
                    }
                }


                // Finding element by it's id
                /*
                    Parameter : take an id of the item
                    Process : return the item of the same id by checking this id is in the range of size of array or not.
                        if id in the range --> then it will look for the item that has the same id and return this.
                    Return : return an item object of that id if found.
                        return an item object his name is "not found" if the id in range but didn't add yet.
                        return an item object his name is "out of range" if the id is out of array's range  or negative.
                */

                Item  find ( int id ) {
                    Item temp ;
                    if ( id <= maxItems_ && id >= 1 ) {
                        if ( items_[ id - 1 ].getname() != "" ) {

                            // assigning all item value to object item ( includes id value )
                            temp = items_[ id - 1 ] ;
                            return temp ;

                        }
                        else {

                            // in range [ 1 , max ] , but not used as an id yet
                            temp.setname("notfound") ;
                            return temp ;

                        }
                    }

                    // out of range [ 1 , max ]
                    else {
                        temp.setname("outofrange") ;
                        return temp ;

                    }
                }


            // operator overloading

                // insersion operator
                friend ostream &operator << (ostream &out, Seller& seller){
                    out << "Seller Name  : "  << seller.name_  << '\n' ;
                    out << "Seller Email : "  << seller.email_ << '\n' ;
                    return out;
                }

                // extraction operator
                friend istream & operator >> ( istream & in , Seller & seller) {

                    cout << "Enter Seller Name           : " ;
                    // in >> seller.name_ ;
                    // in.ignore() ;
                    getline ( in , seller.name_ ) ;


                    cout << "Enter Seller Email          : " ;
                    in   >> seller.email_ ;


                    cout << "Enter Seller Store Capacity : " ;
                    while ( in >> seller.maxItems_ , seller.maxItems_ < 1 ) {
                            cout << "Please enter a valid Capacity !! "  ;
                    }

                    seller.items_ = new Item [seller.maxItems_];
                    return in ;

                }


            // Destructor
            /*
                Parameter :Non
                Process : Freeing the Memory we used by using keyword delete
                Return :Non
            */

                ~Seller(){
                    delete [] items_;
                }

};

// Menu Function that present choices every time for user
/*
    Parameter : Non
    Process   : display the 6 choices that system proviedes
    Return    : Non
*/

void menu() {
    cout <<  "\n\nMenu : "
         <<  "\n1. Print My Info "
         <<  "\n2. Add An Item "
         <<  "\n3. Sell An Item "
         <<  "\n4. Print Items "
         <<  "\n5. Find an Item by ID "
         <<  "\n6. Exit "
         <<  "\n\nPlease , Enter Your Choice  : " ;
}


int main(){

    Seller seller ;
    cin >> seller ;

    // menu for first time
    menu() ;
    int choice ;

    // This line of while loop is for repeting showing menu and taking user instructions until he/she request to exit ( 6 )
    while ( cin >> choice , choice !=  6  ) {
        switch (choice) {

            // on Choosing " 1. Print My Info  "

            case 1 : {
                cout << seller ;
                break ;
            }

            // on Choosing " 2. Add An Item  "
            case 2 : {

                Item item ;
                cin >> item ;
                if ( seller.add(item) ) {
                        cout << "Item added Successfully !"   << endl ;
                }
                else {
                        cout << "Sorry The Capcity is Full ." << endl ;
                }
                break ;
            }

            // on Choosing " 3. Sell An Item  "
            case 3 : {

                string item ;
                cout << "Enter needed item name : " ;
                //cin >> item ;

                cin.ignore() ;
                getline ( cin , item ) ;


                int item_quantity ;
                cout << "Enter item qunatity    : " ;

                while ( cin >> item_quantity , item_quantity < 1 ) {
                        cout << "Please enter a valid quantity !! " ;
                }

                if ( seller.sell( item , item_quantity ) ) {
                        cout << "Item sold Successfully !" << endl ;
                }
                break ;

            }

            // on Choosing " 4. Print Items "
            case 4 : {
                seller.printItems() ;
                break ;
            }


            // on Choosing " 5. Find an Item by ID  "
            case 5 : {
                int id ;
                cout << "Please Enter item's ID  : " ;
                cin >> id ;

                if (seller.find(id).getname() == "outofrange" ) {

                        cout << "Sorry ! Id out of range " << endl ;

                }
                else if ( seller.find(id).getname() == "notfound" ) {

                        cout << "Sorry ! Item not Found " << endl ;

                }
                else {

                        cout << ( seller.find(id) ) ;

                }
                break ;
            }

            // on Choosing " 6.exit "
            // this will cause the loop to exit and goodbye messege to apper


            // on choosing any integer value rather than [1-6] choices
            default : {
                cout << "Please Enter a valid choice . \n " ;
                break ;
            }

        }

        // repeatable menu for user
        menu() ;

    }

    // ending
    cout << "Thank You !" << endl ;

    return 0 ;

}
