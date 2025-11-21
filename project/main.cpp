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
        cout << "Node not found" << endl;
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

    cout << "---Add New Movie---" << endl;
    // Adding Movie ID
    cout << "Enter ID: ";
    // ID Validation Loop
    while (!(cin >> id)) {
      cout << "Error: Please enter a valid number for ID: ";
      cin.clear();// 1. Resets the "fail state"
      cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer and we use 10000 as a large number to clear the line
    }
    // End of Validation
    cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number

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

    //
    Movie newMovie(id, title, genre, price);
    bst.insert(newMovie);
  }

  void search_movie(BST &bst) {
    int id;
    cout << "Enter ID you want to search: ";

    // ID Validation Loop
    while (!(cin >> id)) {
      cout << "Error: Please enter a valid number for ID: ";
      cin.clear();// 1. Resets the "fail state"
      cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
    }// End of Validation

    cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number

    Movie *foundmovie = bst.searchByID(id);

    if (foundmovie != nullptr) {
      cout << "--- Movie Found ---" << endl;
      cout << "ID: " << foundmovie->id << endl;
      cout << "Title: " << foundmovie->title << endl;
      cout << "Genre: " << foundmovie->genre << endl;
      cout << "Price: $" << foundmovie->price << endl;
    }
  }

  void delete_movie(BST &bst) {
    int id;
    cout << "Enter Movie ID You want to delete: ";
    cin >> id;
    // ID Validation Loop
    // This loop will run as long as the input is not a valid number
    while (!(cin >> id))
    {
      cout << "Error: Please enter a valid number for ID: ";
      cin.clear(); // 1. Resets the "fail state"
      cin.ignore(10000, '\n');// 2. Clears the bad input from the input buffer
    }// End of Validation

    cin.ignore(10000, '\n');// Clear the 'Enter' key press after the valid number
    bst.deleteNode(id);
  };

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
                            cout << "\n--- Add New Customer ---" << endl;
                            int new_id;
                            string new_name, new_phone, new_email;

                            cout << "Enter Customer ID: ";
                            while (!(cin >> new_id)) {
                                cout << "Error: Please enter a valid number for ID: ";
                                cin.clear();
                                cin.ignore(10000, '\n');
                            }
                            cin.ignore(10000, '\n');

                            cout << "Enter Name: ";
                            getline(cin, new_name);

                            cout << "Enter Phone Number: ";
                            getline(cin, new_phone);

                            cout << "Enter Email: ";
                            getline(cin, new_email);

                            Customer newCustomer(new_id, new_name, new_phone, new_email);
                            Customers.insertCustomer(newCustomer);
                            cout << endl;
                            break;
                        }
                        case 2: // Search Customer (CLL)
                        {
                            cout << "\n--- Search Customer ---" << endl;
                            int customerID;
                            cout << "Enter Customer ID to search: ";
                            while (!(cin >> customerID)) {
                                cout << "Error: Please enter a valid number for ID: ";
                                cin.clear();
                                cin.ignore(10000, '\n');
                            }
                            cin.ignore(10000, '\n');

                            Customer foundCustomer = Customers.searchCustomer(customerID);
                            if (foundCustomer.id != 0) { // Check if a valid customer was returned
                                cout << "\n--- Customer Details ---" << endl;
                                cout << "ID: " << foundCustomer.id << endl;
                                cout << "Name: " << foundCustomer.name << endl;
                                cout << "Phone: " << foundCustomer.phoneNumber << endl;
                                cout << "Email: " << foundCustomer.email << endl;
                              cout << "E-mail: "<< endl;
                            }
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
                            cout << "\n--- Delete Customer ---" << endl;
                            int delete_id;
                            cout << "Enter Customer ID to delete: ";

                            while (!(cin >> delete_id)) {
                                cout << "Error: Please enter a valid number for ID: ";
                                cin.clear();
                                cin.ignore(10000, '\n');
                            }
                            cin.ignore(10000, '\n');

                            Customers.deleteCustomer(delete_id);
                            break;
                        }
                        case 5: // Rent a Movie (CLL + BST) - Basic Implementation
                        {
                            cout << "\n--- Rent a Movie ---" << endl;
                            int customerID, movieID;

                            cout << "Enter Customer ID: ";
                            while (!(cin >> customerID)) {
                                cout << "Error: Please enter a valid number for ID: ";
                                cin.clear();
                                cin.ignore(10000, '\n');
                            }
                            cin.ignore(10000, '\n');

                            Customer customerToRent = Customers.searchCustomer(customerID);
                            if (customerToRent.id == 0) {
                                break; // Customer not found
                            }

                            cout << "Enter Movie ID to rent: ";
                            while (!(cin >> movieID)) {
                                cout << "Error: Please enter a valid number for ID: ";
                                cin.clear();
                                cin.ignore(10000, '\n');
                            }
                            cin.ignore(10000, '\n');

                            Movie *movieToRent = Movies.searchByID(movieID);
                            if (movieToRent == nullptr) {
                                // searchByID already prints "Node not found"
                                break; // Movie not found
                            }

                            // --- Actual Rent Logic (Needs implementation in Customer struct/CLL class) ---
                            // For now, we'll just confirm availability:
                            cout << "\n--- Transaction Summary ---" << endl;
                            cout << "Customer: " << customerToRent.name << endl;
                            cout << "Movie: " << movieToRent->title << " (" << movieToRent->price << " SAR)" << endl;
                            cout << "Status: Ready for rental processing." << endl;
                            // You would need to add a function in CLL to assign the movie to the customer's rentedMovies array.

                            break;
                        }
                        case 6: // Return Movie (Needs implementation)
                        {
                            cout << "\nReturn functionality to be implemented." << endl;
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

// ... main function requires an adjustment to pass the CLL object ...
int main() {
  BST Movies;
  CLL Customers; // Need to create a Customer Linked List object

  Customers.insertCustomer({1, "Ali Ahmad", "0501234567", "ali@mail.com"});
  Customers.insertCustomer({2, "Fatimah Alsaud", "0559876543", "fatima@mail.com"});

  displayMenu(Movies, Customers); // Pass both the BST and CLL

  return 0;
}



