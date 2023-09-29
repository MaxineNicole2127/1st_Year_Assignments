/****************************************
    MAXINE NICOLE B. BERNALES
    CSDC102 ZC11 (Intermediate Programming)
    5.01.2023
    E3[Basketball Ticket Registration System]

    Program Description: A C++ Program that allows user to buy tickets, cancel order, view ticket list, and pass the ticket list to a binary file.
    Implemented:
    - Filestream (binary)
    - Exception Handling
    - Classes and Structs
    - List
    - Simple Interactive Terminal UI
*****************************************/

#include <iostream>
#include <iterator>
#include <fstream>
#include <stdexcept>
#include <list>
#include <cstring>
#include <iomanip>

void commands(char &continues); //displays list of commands to be performed depending on user's choice
void Enter_Details(); //takes input for customer details
void Display_All_Orders(); //presents the current orders in a table
void Search_for_Order(); //takes customer name and determines whether name is registered. If yes, display.
void Cancel_Order(); //takes customer name and determines whether name is registered. If yes, erase order from list.
void Save_To_Binary_File(); //saves current orders to binary file
void Open_Binary_File(); //displays contents of binary file


class Customer{
private: //has customer's no., name, address, and no.of tickets bought
    std::string name, address;
    std::list<std::string> Names;
    int tickets, customer_Number{0};
public:
    bool Is_Present_In_List(std::list<std::string> &List, std::string N){ //determines whether a name has been listed before
        for(auto x: List) if(x == N) return true;
        return false;
    }
    bool getInput(){ //takes input and returns validity of a customer purchase
        bool valid{true};
        try{
            //take input for name and if in Names list, throw exception
            printf("  Full Name: "); std::getline(std::cin >> std::ws, name);
            bool found{Is_Present_In_List(Names, name)};
            if(found == 1) throw std::invalid_argument("\n  Error! Multiple requests for same person is not allowed.");
            else Names.push_back(name);

            //take input for address
            printf("  Address: "); std::getline(std::cin >> std::ws, address);
            printf("  No. of Tickets: "); std::cin >> tickets;

            //take input for NoOfTickets and if x > 4 or x < 1, throw exception
            if(tickets > 4 || tickets < 1){
                Names.pop_back();
                if(tickets > 4) throw std::invalid_argument("\n  Error! Tickets must not exceed 4.");
                if(tickets < 1) throw std::invalid_argument("\n  Error! You must purchase atleast one ticket.");
            }
            customer_Number++;
        }catch(std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
            valid = false; //changes valid to false if there is an invalid argument
        }
        return valid;
    }

    void print_CustomerDetails(){ //display customer no, name, address, and NoOfTickets in a single line
        std::cout << "   " << std::left << std::setw(7) << customer_Number << std::setw(30) << name << std::setw(30) << address << std::setw(10) << tickets << std::endl;
    }
    void setTicketNo(int t){this->customer_Number = t;} //changes customerNo
    //the ff. functions return specific data
    std::string returnName(){return name;}
    std::string returnAddress(){return address;}
    int returnNoOfTickets(){return tickets;}
    int returnTicketNo(){return customer_Number;}

};

std::list<Customer> List_Of_Customers; //a list of objects of class Customers

int main(){
    int choice;  system("CLEAR");
    printf("\n  BASKETBALL TICKET REGISTRATION SYSTEM\n");
    printf("\n  [1] Enter customer details\n  [2] Read Database");
    printf("\n\n  Choice: "); std::cin >> choice;

    //output will vary depending on user's choice
    if(choice == 1){
        Enter_Details();
    }else if(choice == 2){
        system("clear");
        char choice_c;
        Open_Binary_File();
        printf("\n\n\t   Go to Customer Information Entry?[y/n] : "); std::cin >> choice_c;
        if(choice_c == 'y') Enter_Details();
        else return 0;
    }

    //program will run and keep calling void function commands() unless user ends program
    bool done{false};
    char continues;
    while(done!=true){
        commands(continues);
        if(continues == 'n') done = true;
    }
}

typedef struct{ //stores the contents of an object to a struct; will be helpful in transferring data to binary file
    int customerNumber;
    char name[50];
    char address[50];
    int tickets;
} CUSTOMER;

void commands(char &continues){ //displays list of commands to be performed depending on user's choice
    printf("\n\tGo to options? [y/n] : "); std::cin >> continues;
    if(continues == 'y'){
        system("clear");
        printf("\n  What do you want to do next? ");
        printf("\n\n  [1] Display all orders\n  [2] Search for an Order\n  [3] Cancel order\n  [4] Save to Database\n  [5] Open Database\n  [6] End Program\n");
        printf("\n  What's your choice? : "); int choice; std::cin >> choice;

        system("clear");
        if(choice == 1) Display_All_Orders();
        else if(choice == 2) Search_for_Order();
        else if(choice == 3) Cancel_Order();
        else if(choice == 4) Save_To_Binary_File();
        else if(choice == 5) Open_Binary_File();
        else if(choice == 6) continues = 'n';
    }
}

void Enter_Details(){ //takes input for customer details
    system("clear");
    bool Continue{true};
    int noOfCustomers{0};
    Customer C; char choice;

    while(Continue){
        printf("\n     Enter customer details\n");
        printf("  -----------------------------\n");
        if(C.getInput() == 1){ //only adds the object to the list if all inputs are valid
            List_Of_Customers.push_back(C);
            noOfCustomers++;
        }
        char choice;
        printf("\n  Would you like to add another?[y/n] : "); std::cin >> choice;
        if(choice == 'n') Continue = false;
        system("clear");
    }

    //displays mailing label
    printf("\n\t************************* MAILING LABELS **************************\n\n");
    for(int i{0}; i < noOfCustomers; i++){
        std::list<Customer>::iterator person{List_Of_Customers.begin()}; //uses iterator to traverse list and take specific content
        std::advance(person, i);

        (*person).setTicketNo(i+1);

        printf("                     ---------------------------------------\n");
        std::cout << "                     " << std::left << std::setw(3) << "|" << std::setw(35) << " " << "|\n";
        std::cout << "                     " << std::left << std::setw(3) << "|  Customer No. " << std::setw(22) << (*person).returnTicketNo() << "|\n";
        std::cout << "                     " << std::left << std::setw(3) << "|" << std::setw(35) << (*person).returnName() << "|\n";
        std::cout << "                     " << std::left << std::setw(3) << "|" << std::setw(35) << (*person).returnAddress() << "|\n";
        std::cout << "                     " << std::left << std::setw(3) << "|  No. of tickets bought: " << std::setw(12) << (*person).returnNoOfTickets() << "|\n";
        std::cout << "                     " << std::left << std::setw(3) << "|" << std::setw(35) << " " << "|\n";
        printf("                     ---------------------------------------\n");
    }
}

void Display_All_Orders(){ //presents the current orders in a table
    printf("\n   ");
    std::cout << std::left << std::setw(7) << "NO." << std::setw(30) << "NAME" << std::setw(30) << "ADDRESS" << std::setw(10) << "# OF TICKETS" << std::endl;
    printf(" -----------------------------------------------------------------------------------\n");

    int noOfCustomers = List_Of_Customers.size();
    for(int i{0}; i < noOfCustomers; i++){
        std::list<Customer>::iterator person{List_Of_Customers.begin()};
        std::advance(person, i);

        (*person).setTicketNo(i+1);
        (*person).print_CustomerDetails();
    }

}

void Search_for_Order(){ //takes customer name and determines whether name is registered. If yes, display.
    std::string Name_Searched;
    bool found{false};
    printf("\n   Enter customer name: "); std::getline(std::cin >> std::ws, Name_Searched);
    int position{0};
    for(auto x: List_Of_Customers){ //traverses list to find name and position/index
        if(x.returnName() == Name_Searched){found = true; break;}
        position++;
    }

    std::cout << "\n   This name has " << (found ? "been" : "not been") << " used to order a ticket.";

    if(found){ //presents details of customer purchase(object) if name is registered
        std::list<Customer>::iterator Matched_Data{List_Of_Customers.begin()}; //uses iterator to pinpoint specific object
        std::advance(Matched_Data, position);
        printf("\n           ---------------------------------------\n");
        std::cout << "           " << std::left << std::setw(3) << "|" << std::setw(35) << " " << "|\n";
        std::cout << "           " << std::left << std::setw(3) << "|  Customer No. " << std::setw(22) << (*Matched_Data).returnTicketNo() << "|\n";
        std::cout << "           " << std::left << std::setw(3) << "|" << std::setw(35) << (*Matched_Data).returnName() << "|\n";
        std::cout << "           " << std::left << std::setw(3) << "|" << std::setw(35) << (*Matched_Data).returnAddress() << "|\n";
        std::cout << "           " << std::left << std::setw(3) << "|  No. of tickets bought: " << std::setw(12) << (*Matched_Data).returnNoOfTickets() << "|\n";
        std::cout << "           " << std::left << std::setw(3) << "|" << std::setw(35) << " " << "|\n";
        printf("           ---------------------------------------\n");
    }
}

void Cancel_Order(){ //takes customer name and determines whether name is registered. If yes, erase order from list.
    std::string Name_Cancel;
    bool found{false};
    printf("\n   Enter customer name: "); std::getline(std::cin >> std::ws, Name_Cancel);
    int position{0};
    for(auto x: List_Of_Customers){ //traverses list to find name and position/index
        if(x.returnName() == Name_Cancel){found = true; break;}
        position++;
    }

    std::cout << "\n   This name has " << (found ? "been" : "not been") << " used to order a ticket.\n";


    if(found){ //erases customer purchase(object) if name is registered
        std::list<Customer>::iterator person{List_Of_Customers.begin()}; //uses iterator to pinpoint specific object
        std::advance(person, position);
        List_Of_Customers.erase(person);
        std::cout << "\n\n   Order has been erased from the system. \n";
    }
}

void Save_To_Binary_File(){ //saves current orders to binary file
    Display_All_Orders(); char choice;
    printf("\n  Are you sure you want to save these orders to the database?[y/n] : "); std::cin >> choice;

    int len = List_Of_Customers.size();
    if(choice == 'y'){
        CUSTOMER To_Binary_File[len]; //creates array of dataType CUSTOMER(from struct) with same size as the List_Of_Customers list
        for(int i{0}; i < len; i++){ //sets every content of struct array to List_Of_Customers element contents
            std::list<Customer>::iterator indiv{List_Of_Customers.begin()};
            std::advance(indiv, i);

            To_Binary_File[i].customerNumber = i+1;
            std::strcpy(To_Binary_File[i].name,((*indiv).returnName()).c_str());
            std::strcpy(To_Binary_File[i].address, ((*indiv).returnAddress()).c_str());
            To_Binary_File[i].tickets = (*indiv).returnNoOfTickets();
        }

        std::fstream rw;
        rw.open("BERNALES_E3.bin", std::ios::out | std::ios::binary);
        rw.write(reinterpret_cast<char*>(&len), sizeof(len)); //saves length of list
        rw.write(reinterpret_cast<char*>(&To_Binary_File), sizeof(To_Binary_File)); //transfers struct array to binary file
        rw.close();
        std::cout << " \n  Orders saved to Database!\n\n";
	}
}

void Open_Binary_File(){ //displays contents of binary file
    printf("\n                                            DATABASE                                     \n\n");
    int previous_length{0};

    printf("\n   ");
    std::cout << "     " << std::left << std::setw(7) << "NO." << std::setw(30) << "NAME" << std::setw(30) << "ADDRESS" << std::setw(10) << "# OF TICKETS" << std::endl;
    printf("      -----------------------------------------------------------------------------------\n");

    std::fstream rw;
    rw.open("BERNALES_E3.bin", std::ios::in | std::ios::binary);
    rw.read(reinterpret_cast<char*>(&previous_length), sizeof(previous_length)); //retrieves size of current content stored before then creates a struct array with this size

    CUSTOMER From_Binary_File[previous_length];

	rw.read(reinterpret_cast<char*>(&From_Binary_File), sizeof(From_Binary_File)); //transfers contents of binary file to struct array
	rw.close();
	for (int i{0}; i < previous_length; i++) //displays database in a table
		std::cout << "        " << std::left << std::setw(7) << From_Binary_File[i].customerNumber << std::setw(30) << From_Binary_File[i].name << std::setw(30) << From_Binary_File[i].address << std::setw(10) << From_Binary_File[i].tickets << std::endl;

}
