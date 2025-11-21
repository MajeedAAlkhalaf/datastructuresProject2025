#include <iostream>
#include <string>
using namespace std;

const int max_rent = 10;

//movie struct
struct Movie{
  int id;
  string title;
  string genre;
  float price;

  Movie(){
    id = 0;
    title = "";
    genre = "";
    price = 0;
  }

  Movie(int id, string title, string genre, float price){
    this->id = id;
    this->title = title;
    this->genre = genre;
    this->price = price;
  }
};

//Customer struct
struct Customer {
  int id;
  string name;
  string phoneNumber;
  string email;
  Movie rentedMovies[max_rent];

  Customer() {
    id = 0;
    name = "";
    phoneNumber = "";
    email = "";
  }

  Customer(int id, string name, string phoneNumber, string email) {
    this->id = id;
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->email = email;
  }
};



//node for BST
struct Node {
  Movie movie;
  Node *left;
  Node *right;

  Node(const Movie& m){ ///////////////////////////////////////////////////////////////
    movie = m;
    left = nullptr;
    right = nullptr;
  }
};


//node for Linked List
struct CustomerNode {
  Customer customer;
  CustomerNode *next;

  CustomerNode(const Customer& c) {
    customer = c;
    next = nullptr;
  }
};

//Circular Linked List
class CLL {
private:
  CustomerNode* head;
  CustomerNode* tail;
  int size;

public:
  CLL() {
    /*CONSTRUCTOR
     *will initialize the linked list*/
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  ~CLL() {
    /*DESTRUCTOR
     *will free all the memory if it is not being used*/
    if (head == nullptr) {
      return;
    }

    CustomerNode* current = head;
    CustomerNode* next = nullptr;

    do {
      next = current->next;
      delete current;
      current = next;
    }while (current != head);

    // all memory will be freed
  }

  void insertCustomer(const Customer& customer) {
    /* INSERT FUNCTION
     * will take a Customer struct as a parameter
     * adds it to the linked list, displays messages*/

    CustomerNode* newNode = new CustomerNode(customer);

    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      newNode->next = newNode; //circularize that bih
      size++;
    } else {
      tail->next = newNode;
      newNode->next = head;
      tail = newNode;
      size++;
    }
    cout << "Customer " << customer.name << " added successfully!";
  }

  void deleteCustomer(int customerID) {
    /*DELETE FUNCTION
     *takes the id of the customer as a parameter
     *will delete the customer if found, displays messages*/
    if (head == nullptr) {
      return;
    }
    CustomerNode* current = head;
    CustomerNode* previous = nullptr;
    do{
      if (current->customer.id == customerID) {
        //if it is the only node
        if (current->next == current) {
          delete current;
          head = nullptr;
          tail = nullptr;

        }
        //if it is the head node
        else if (current == head) {
          head = current->next;
          delete current;
          tail->next = head;

        }
        //if it is any other node
        else {
          previous->next = current->next;
          delete current;
        }
        size--;
        cout << "Customer with ID: " << customerID << " deleted!";
        return;
      }
      previous = current;
      current = current->next;

    }while (current != head);

    cout << "Customer with ID: " << customerID << " not found :(" << endl;
  }

  Customer searchCustomer(int customerID) {
    /*SEARCH FUNCTION
     *will search for the customer in the linked list based on the provided ID
     *if found, the customer struct will be returned
     *if not found, will return a newly initialized customer struct with null values*/
    CustomerNode* current = head;

    if (head == nullptr) {
      return Customer();
    }

    do {
      if (current->customer.id == customerID) {
        cout << "Customer with ID: " << customerID << " found!" << endl;
        return current->customer;
      }
      current = current->next;
    }while (current != head);

    cout << "Customer with ID: " << customerID << " not found :(" << endl;
    return Customer();
  }

  bool isEmpty() {
    if (head == nullptr) {
      return true;
    }
    return false;
  }

  int getSize() {
    return size;
  }

  void updateCustomerInfo(int id, string name, string phoneNumber, string email) {
    /* UPDATE FUNCTION
     * will take all the info of the customer as parameters
     * then it will search for the customer according to ID
     * then it will change the customer info according to parameters*/
    bool found = false;
    CustomerNode* current = head;
    do {
      if (current->customer.id == id) {
        found = true;
        break;
      }
      current = current->next;
    }while (current != head);

    if (found) {
      current->customer.id = id;
      current->customer.name = name;
      current->customer.phoneNumber = phoneNumber;
      current->customer.email = email;
      cout << "Customer information updated successfully :D" << endl;
    } else {
      cout << "Customer not found :(" << endl;
    }
  }
};

 //Binary search tree
  class BST {
  private:
    //this section will contain helper functions which are private

    Node* insertAssistant(Node* node, const Movie& movie){
      if(node == nullptr){
        return new Node(movie);
      }

      if(movie.id < node->movie.id){
        node->left = insertAssistant(node->left, movie);
      }else if(movie.id > node->movie.id){
        node->right = insertAssistant(node->right, movie);
      }

      return node;
    }

    Node* searchAssistant(Node* node, int id, bool &found){
      if(node == nullptr){
        return nullptr;
      }

      if(node->movie.id == id){
        found = true;
        return node;
      }

      if(node->movie.id > id){
        return searchAssistant(node->left, id, found);
      }else if(node->movie.id < id){
        return searchAssistant(node->right, id, found);
      }
    }

    Node* deleteAssistant(Node* node, int id){
      if(node == nullptr){
        //if the BST is already empty then it just exits the function
        return nullptr;
      }

      if(node->movie.id > id){
        node->left = deleteAssistant(node->left, id);
      } else if(node->movie.id < id){
        node->right = deleteAssistant(node->right, id);
      }else{
        //this case means we found the node we want to delete

        //no children
        if(node->left == nullptr && node->right == nullptr){
          delete node;
          return nullptr;
        }
        //one child
        else if(node->left == nullptr){
          Node*temp = node->right;
          delete node;
          return temp;
        } else if(node->right == nullptr){
          Node*temp = node->left;
          delete node;
          return temp;
        }
        //two children
        else {
          //first we will find the next successor (furthest left node of the right node)
          Node* temp = node->right;
          do{
            temp = temp->left;
          }while(node->left!=nullptr);
          //replace the content of the successor to the target node
          node->movie = temp->movie;
          //delete the successor
          node->right = deleteAssistant(node->right, id);
        }
      }
    }

    void DESTROYTHETREEAssistant(Node* node){
      if(node == nullptr){
        DESTROYTHETREEAssistant(node->left);
        DESTROYTHETREEAssistant(node->right);
        delete node;
      }
    }

    Node* CountNodesAssistant(Node* node, int count){
      if(node != nullptr){
        count += 1;
        CountNodesAssistant(node->left, count);
        CountNodesAssistant(node->right, count);
      }
      return nullptr;
    }

    void displayAssistant(Node* node){
      if(node != nullptr){
        // 1. Traverse Left Subtree
        displayAssistant(node->left);

        // 2. Visit Node (Print Movie Details)
        cout << "------------------------------------------" << endl;
        cout << "ID:    " << node->movie.id << endl;
        cout << "Title: " << node->movie.title << endl;
        cout << "Genre: " << node->movie.genre << endl;
        cout << "Price: " << node->movie.price << " SAR" << endl;
        cout << "------------------------------------------" << endl;

        // 3. Traverse Right Subtree
        displayAssistant(node->right);
      }
    }

  public:
    //this section will contain the functions which you appear to you and you can use
    Node* root;

    BST(){
      //constructor of the BST class
      root = nullptr;
    }

    ~BST(){
      //destructor of the BST class
      DESTROYTHETREEAssistant(root);
    }

    void insert(const Movie& movie){
      /*INSERT FUNCTION
        inserts a movie into the BST
        It will give you a message after it has been added*/
      root = insertAssistant(root, movie);
      cout << movie.title << " has been added to the system successfully." << endl;
    }

    void deleteNode(int id){
      /* DELETE FUNCTION
         THe function takes an id of a movie
         It then searches the BST to see if it exists
         If it exists, then the movie is deleted
         A message is displayed in both cases to inform the user*/
      Movie* temp = searchByID(id);
      if (temp!= nullptr) {
        cout << "Deleting " << temp->title << "... " << endl;
        root = deleteAssistant(root, id);
      } else {
        cout << "ID not found." << endl;
      }
    }
    void displayMovies(){
      /*DISPLAY FUNCTION
        Displays all movies in the BST in ascending order of ID*/
      if(root == nullptr){
        cout << "The movie system is currently empty." << endl;
      } else {
        cout << "\n--- Current Movie Inventory (Sorted by ID) ---" << endl;
        displayAssistant(root);
        cout << "--- End of Inventory ---\n" << endl;
      }
    }


    bool isEmpty(){
      /*IS EMPTY FUNCTION
        Checks if the BST is empty or not*/
      if(root == nullptr) {
        return true;
      }else{
        return false;
      }
    }

    Movie* searchByID(int id){
      /*SEARCH FUNCTION
        The function will receive an ID of a movie
        It returns the movie if found
        It return NULL if the movie is not found*/
      bool found = false;
      Node* temp = searchAssistant(root, id, found);
      if(found != false){
        return &(temp->movie);
      }else{
        return nullptr;
      }
    }

    int countAllNodes(){
      /*COUNT FUNCTION
       *This function will count the number of movies in the system, returning an integer*/
      bool count = 0;
      CountNodesAssistant(root, count);
      return count;
    }
  };

//Adding movie function
void add_movie(BST &bst) { //Pass the BST by reference
  int id;
  string title;
  string genre;
  float price;
  Movie *existingMovie = nullptr;

  cout << "---Add New Movie---" << endl;

  do {
    //Adding Movie ID
    cout << "Enter ID: ";
    // ID Validation Loop
    while (!(cin >> id)) {
      cout << "Error: Please enter a valid number for ID: ";
      cin.clear();// 1. Resets the "fail state"
      cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
    }// End of Validation
    cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number

    // Check if ID exists (searchByID is the key check)
    existingMovie = bst.searchByID(id);

    if (existingMovie != nullptr) {
      cout << "Movie with ID " << id << " already exists: " << existingMovie->title << ". Please enter a new, unique ID." << endl;
    }
  }while (existingMovie != nullptr);

  // Adding Movie Title
  cout << "Enter title: ";
  getline(cin, title);

  // Adding Movie Genre
  cout << "Enter genre: ";
  getline(cin, genre);

  // Adding Movie Price
  cout << "Enter price: ";

  // Price Validation Loop
  while (!(cin >> price)) {
    cout << "Error: Please enter a valid number for Price: ";
    cin.clear(); // 1. Resets the "fail state"
    cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
  }// End of Validation
  cin.ignore(10000, '\n');// Clear the 'Enter' key after the valid price

  //Inserting movie details
  Movie newMovie(id, title, genre, price);
  bst.insert(newMovie);
}

//Searching movie function
void search_movie(BST &bst) {//Pass the BST by reference
  int id;
  cout << "Enter ID you want to search: ";

  // ID Validation Loop
  while (!(cin >> id)) {
    cout << "Error: Please enter a valid number for ID: ";
    cin.clear();// 1. Resets the "fail state"
    cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
  }// End of Validation
  cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number

  // Calls BST method to search for a movie by ID
  Movie *foundmovie = bst.searchByID(id);

  //Showing Movie details
  if (foundmovie != nullptr) {
    cout << "--- Movie Found ---" << endl;
    cout << "--- Movie Details ---" << endl;
    cout << "ID: " << foundmovie->id << endl;
    cout << "Title: " << foundmovie->title << endl;
    cout << "Genre: " << foundmovie->genre << endl;
    cout << "Price: $" << foundmovie->price << endl;
  }
}

//Deleting movie function
void delete_movie(BST &bst) {//Pass the BST by reference
  int id;
  cout << "Enter Movie ID You want to delete: ";

  // ID Validation Loop
  while (!(cin >> id)) {
    cout << "Error: Please enter a valid number for ID: ";
    cin.clear(); // 1. Resets the "fail state"
    cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
  }
  cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number

  //Call BST method to delete movie By ID
  bst.deleteNode(id);
}

//Adding customer function
void add_customer(CLL &cll) {//Pass the CLL by reference
  int id;
  string name;
  string phoneNumber;
  string email;
  Customer existingCustomer;

  cout << "---Add New Customer---" << endl;

  do {
    // ID Validation Loop
    //Adding customer ID
    cout << "Enter ID: ";
    while (!(cin >> id)) {
      cout << "Error: Please enter a valid number for ID: ";
      cin.clear();// 1. Resets the "fail state"
      cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
    }
    cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number

    // Check if ID exists (searchCustomer is the key check)
    existingCustomer = cll.searchCustomer(id);
    if (existingCustomer.id != 0) {
      cout << "Please enter a new, unique ID." << endl;
    }
  }while (existingCustomer.id != 0);

  //Adding customer name
  cout << "Enter name: ";
  getline(cin, name);

  //Adding customer phone number
  cout << "Enter phone number: ";
  getline(cin, phoneNumber);

  //Adding customer email
  cout << "Enter email: ";
  getline(cin, email);

  //Inserting customer details
  Customer customer(id, name, phoneNumber, email);
  cll.insertCustomer(customer);
  cout << endl;
}

//Searching customer function
void search_customer(CLL &cll) {//Pass the CLL by reference
  int id;
  cout << "Enter ID you want to search: ";

  // ID Validation Loop
  while (!(cin >> id)) {
    cout << "Error: Please enter a valid number for ID: ";
    cin.clear();// 1. Resets the "fail state"
    cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
  }
  cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number

  // Calls CLL method to search for a customer by ID
  Customer foundcustomer = cll.searchCustomer(id);

  //Showing Customer details
  if (foundcustomer.id != 0) {
    cout << "--- Customer Found ---" << endl;
    cout << "ID: " << foundcustomer.id << endl;
    cout << "Name: " << foundcustomer.name << endl;
    cout << "Phone Number: " << foundcustomer.phoneNumber << endl;
    cout << "Email: " << foundcustomer.email << endl;
    cout << "Rented Movies: " << foundcustomer.rentedMovies << endl;
  }
  else {
    // Customer not found, ask to add
    char choice;
    cout << "Customer with ID: " << id << " not found :(" << endl;
    cout << "Do you want to add this customer? (y/n): ";
    cin >> choice;
    // Clear the input buffer up to the newline character to prevent issues with future inputs.
    cin.ignore(10000, '\n');

    // Convert the input character to lowercase and check if it is 'y' (yes).
    if (tolower(choice) == 'y') {
      // If the choice is 'y', call the function to add a new customer,
      // passing the Circular Linked List (CLL) by reference.
      add_customer(cll);
    }
    // If the choice is not 'y', the function simply returns, and no customer is added.
  }
  cout << endl;
}

//Deleting customer function
void delete_customer(CLL &cll) {//Pass the CLL by reference
  int id;
  cout << "Enter ID you want to delete: ";

  // ID Validation Loop
  while (!(cin >> id)) {
    cout << "Error: Please enter a valid number for ID: ";
    cin.clear();// 1. Resets the "fail state"
    cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
  }
  cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number

  // Calls CLL method to delete customer by ID
  cll.deleteCustomer(id);
  cout << endl;
}

void Rent_Movie()   //Rentting a movie function
{

  int MovieID;

  cout << "Enter The Movie ID you want to Rent: ";
  cin >> MovieID;

  Movie *MovieToRent = bst.searchByID(MovieID);  //Finding the wanted movie

  if (MovieToRent == NULL)  // Check if Movie doesn't exist
  {
  cout << "Movie not found." << endl;
  return;
  }


  if (MovieToRent->quantity < 1 )  //Checking if Movie copies exist
  {
    cout << "The Movie can't be rented due to insufficient quantity" << endl;
    return;
  }


   int CustomerID;

   cout << "Enter The ID for the customer you want to Rent a movie to: ";
   cin >> CustomerID;

   Customer *Renter = searchCustomer(CustomerID);  //Finding the customer info.


   if (Renter == NULL)
   {
      cout << "Customer not found." << endl;
      return;
   }


   if (Renter-> counter == 10)  //Checking if customer may rent a movie
   {
     cout << "The customer have rented the maximum number allowed, customer must retun a movie to be able to rent another one"<<endl;
     return;
   }

   Renter->RentedMovies[Renter-> counter] = MovieToRent;  //add the movie to the customer's Rented Movies List
   MovieToRent->quantity--;  //Decrease The number of avilable copies of the movie
   Renter->counter++;  //increase the number of rented movies by the renter

   cout << "The Movie "<<MovieToRent-> name <<" is now rented to the customer "<<Renter->name<<endl;

}


void Return_Movie()   //Returnig a rented moviefunction
{

  int RenterID;

  cout << "Enter The Renter ID: ";
  cin >> RenterID;

  Customer *Renter = searchCustomer(RenterID);  //Finding the Renter Info.

  if (Renter== NULL)  // Check if renter doesn't exist
  {
    cout << "The Customer does not exist" << endl;
    return;
  }
  int MovieID, checker = 0;
  Movie *RentedMovie = NULL;

  cout << "Enter The ID of the movie you want to Return: ";
  cin >> MovieID;

  for(int i=0;i<Renter->counter;i++)  //Loop go through all of the rented movies that the renter have
  {
    if(Renter->RentedMovies[i]-> id==MovieID)  // check the movies IDs
    {
      RentedMovie = Renter->RentedMovies[i];  //finding the movie that the Renter want to return
      checker=1;  //When the movie found assaign 1 to this variable (true)
    }
    if (checker==1)  //Check if this variable is 1 (true) to start the process
    {
      Renter->RentedMovies[i]=Renter->RentedMovies[i+1];  //removing the movie from the renter's rented movies & shifting the rest of the elements if exist
    }
  }
  if (checker==1)  //Check if this variable is 1 (true)
  {
  RentedMovie->quantity++;  //Increase The number of avilable copies of the movie
  Renter->counter--;  //Decrease the number of rented movies by the renter
  cout << "The movie " << RentedMovie->name << " has been successfully returned by " << Renter->name << "." << endl;
  }
  else
  {
    cout << "This movie is not rented by the customer." << endl;
    return;
  }
}


void displayMenu(BST &Movies, CLL &Customers) {
    string name;
    int choice;
    int a; // For Employee menu
    int b; // For Manager menu
    int id;

    // The main loop for the application
    do {
        cout << "\n________________________________________" << endl;
        cout << "_______Welcome to the Movie Store_______" << endl;
        cout << "1. Employee (Customer & Rental Operations)" << endl;
        cout << "2. Manager (Movie/Admin Operations)" << endl;
        cout << "3. Exit" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Enter your choice: ";

        // Input validation for the main menu choice
        while (!(cin >> choice)) {
            cout << "Error: Please enter a valid number (1-3): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

        switch (choice) {
            case 1: // Employee Menu (Customer Operations)
            {
                cout << "\n--- Employee Login ---" << endl;
                cout << "Enter your Name: ";
                getline(cin, name);
                cout << "Enter your ID: ";

                // Input validation for employee ID
                while (!(cin >> id)) {
                    cout << "Error: Please enter a valid number for ID: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                cin.ignore(10000, '\n');

                do {
                    cout << "\n------------------------------------------" << endl;
                    cout << "--- Employee Menu ---" << endl;
                    cout << "1. Add New Customer" << endl;
                    cout << "2. Search Customer" << endl;
                    cout << "3. Update Customer Info" << endl;
                    cout << "4. Delete Customer" << endl;
                    cout << "5. Rent a Movie" << endl;
                    cout << "6. Return Movie (Not implemented)" << endl;
                    cout << "7. Display All Movies" << endl;
                    cout << "8. Back to Main Menu" << endl;
                    cout << "------------------------------------------" << endl;
                    cout << "Enter your choice: ";

                    // Input validation for employee menu choice
                    while (!(cin >> a)) {
                        cout << "Error: Please enter a valid number (1-8): ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    cin.ignore(10000, '\n');

                    switch (a) {
                        case 1: // Add New Customer (CLL)
                        {
                          add_customer(Customers);
                            break;
                        }
                        case 2: // Search Customer (CLL)
                        {
                            search_customer(Customers);
                            break;
                        }
                        case 3: // Update Customer Info (CLL)
                        {
                            cout << "\n--- Update Customer Info ---" << endl;
                            int update_id;
                            string new_name, new_phone, new_email;

                            cout << "Enter Customer ID to update: ";
                            while (!(cin >> update_id)) {
                                cout << "Error: Please enter a valid number for ID: ";
                                cin.clear();
                                cin.ignore(10000, '\n');
                            }
                            cin.ignore(10000, '\n');

                            // Check if customer exists first
                            if (Customers.searchCustomer(update_id).id == 0) {
                                break; // searchCustomer already printed 'not found' message
                            }

                            cout << "Enter new Name: ";
                            getline(cin, new_name);

                            cout << "Enter new Phone Number: ";
                            getline(cin, new_phone);

                            cout << "Enter new Email: ";
                            getline(cin, new_email);

                            Customers.updateCustomerInfo(update_id, new_name, new_phone, new_email);
                            break;
                        }
                        case 4: // Delete Customer (CLL)
                        {
                            delete_customer(Customers);
                            break;
                        }
                        case 5: // Rent a Movie (CLL + BST) - Basic Implementation
                        {
                            Rent_Movie();
                            break;
                        }
                        case 6: // Return Movie (Needs implementation)
                        {
                           Return_Movie();
                            break;
                        }
                        case 7: // Display All Movies (BST)
                        {
                            Movies.displayMovies();
                            break;
                        }
                        case 8: // Exit Employee Menu
                        {
                            cout << "Returning to the main menu." << endl;
                            break;
                        }
                        default:
                        {
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                        }
                    }
                } while (a != 8);
                break;
            }

            case 2: // Manager Menu (Movie/Admin Operations) - Unchanged from previous correction
            {
                cout << "\n--- Manager Login ---" << endl;

                do {
                    cout << "\n------------------------------------------" << endl;
                    cout << "--- Manager Menu ---" << endl;
                    cout << "1. Search Movie" << endl;
                    cout << "2. Display All Movies" << endl;
                    cout << "3. Add New Movie" << endl;
                    cout << "4. Delete Movie" << endl;
                    cout << "5. Display Number of Movies" << endl;
                    cout << "6. Back to Main Menu" << endl;
                    cout << "------------------------------------------" << endl;
                    cout << "Enter your choice: ";

                    // Input validation for manager menu choice
                    while (!(cin >> b)) {
                        cout << "Error: Please enter a valid number (1-6): ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    cin.ignore(10000, '\n');

                    switch (b) {
                        case 1: // Search Movie
                        {
                            search_movie(Movies);
                            break;
                        }
                        case 2: // Display All Movies
                        {
                            Movies.displayMovies();
                            break;
                        }
                        case 3: // Add New Movie
                        {
                          add_movie(Movies);
                            break;
                        }
                        case 4: // Delete Movie
                        {
                          delete_movie(Movies);
                            break;
                        }
                        case 5: // Display Count
                        {
                            int count = Movies.countAllNodes();
                            cout << "\nTotal number of movies in the system: " << count << endl;
                            break;
                        }
                        case 6: // Exit Manager Menu
                        {
                            cout << "Returning to the main menu." << endl;
                            break;
                        }
                        default:
                        {
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                        }
                    }
                } while (b != 6);
                break;
            }
            case 3:
            {
                cout << "\nExiting the Movie Store application. Goodbye!" << endl;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                break;
            }
        }
    } while (choice != 3);
}

int main () {
  BST Movies ;
  CLL Customers;

  add_customer(Customers);
  search_customer(Customers);
  add_customer(Customers);
  return 0;
}