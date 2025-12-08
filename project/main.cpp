#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Maximum number of movies a customer can rent at once
const int max_rent = 10;


// MOVIE STRUCT
// Represents a movie in the rental system with all its details
struct Movie{
  int id;           // Unique movie identifier
  string title;     // Movie name
  string genre;     // Movie category
  float price;      // Rental price in SAR
  int quantity;     // Available copies

  // Default constructor - sets everything to empty/zero
  Movie(){
    id = 0;
    title = "";
    genre = "";
    price = 0;
    quantity = 0;
  }

  // Constructor with parameters - creates movie with given values
  Movie(int id, string title, string genre, float price, int quantity){
    this->id = id;
    this->title = title;
    this->genre = genre;
    this->price = price;
    this->quantity = quantity;
  }
};

// CUSTOMER STRUCT
// Represents a customer who can rent movies from the store
struct Customer {
  int id;                           // Unique customer identifier
  string name;                      // Customer's name
  string phoneNumber;               // Contact number
  string email;                     // Email address
  Movie rentedMovies[max_rent];     // Array of rented movies
  int counter;                      // How many movies currently rented

  // Default constructor - sets everything to empty/zero
  Customer() {
    id = 0;
    name = "";
    phoneNumber = "";
    email = "";
    counter = 0;
  }

  // Constructor with parameters - creates customer with given values
  Customer(int id, string name, string phoneNumber, string email) {
    this->id = id;
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->email = email;
    counter = 0;
  }
};

// NODE STRUCT (for Binary Search Tree)
// A single node in the movie BST - holds one movie and links to children
struct Node {
  Movie movie;      // Movie data in this node
  Node *left;       // Left child (smaller ID)
  Node *right;      // Right child (larger ID)

  // Constructor - creates node with a movie
  Node(const Movie& m){
    movie = m;
    left = nullptr;
    right = nullptr;
  }
};

// CUSTOMERNODE STRUCT (for Linked List)
// A single node in the customer list - holds one customer and link to next
struct CustomerNode {
  Customer customer;    // Customer data in this node
  CustomerNode *next;   // Pointer to next node

  // Constructor - creates node with a customer
  CustomerNode(const Customer& c) {
    customer = c;
    next = nullptr;
  }
};

// CLL CLASS - CIRCULAR LINKED LIST
// Stores all customers in a circular linked list structure
// The last node points back to the first node, forming a circle
class CLL {
private:
  CustomerNode* head;   // First node in the list
  CustomerNode* tail;   // Last node in the list
  int size;             // Number of customers

public:
  // Constructor
  // How it works: Sets head and tail to null, size to 0
  CLL() {
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  // Destructor
  // How it works: Goes through each node and deletes it to free memory
  ~CLL() {
    if (head == nullptr) {
      return;
    }

    CustomerNode* current = head;
    CustomerNode* next = nullptr;

    // Go through circular list and delete each node
    do {
      next = current->next;
      delete current;
      current = next;
    }while (current != head);
  }

  // insertCustomer
  // How it works:
  //   - Creates a new node with the customer data
  //   - If list is empty, the new node points to itself (circular)
  //   - Otherwise, adds to end and updates tail pointer
  void insertCustomer(const Customer& customer) {
    CustomerNode* newNode = new CustomerNode(customer);

    // If list is empty, new node points to itself
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      newNode->next = newNode;
      size++;
    } else {
      // Add to end and keep circular structure
      tail->next = newNode;
      newNode->next = head;
      tail = newNode;
      size++;
    }
    cout << "Customer " << customer.name << " added successfully!";
  }

  // deleteCustomer
  // How it works:
  //   - Searches through the list to find the customer
  //   - Handles 4 cases: only node, head node, tail node, middle node
  //   - Reconnects surrounding nodes and frees memory
  void deleteCustomer(int customerID) {
    if (head == nullptr) {
      return;
    }
    CustomerNode* current = head;
    CustomerNode* previous = tail;

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
          tail->next = head;
          delete current;
        }
        //if it is the tail node
        else if (current == tail) {
          previous->next = head;
          tail = previous;
          delete current;
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

  // customerExists
  // How it works: Loops through all nodes comparing IDs
  // Returns: true if found, false if not found (no printing)
  bool customerExists(int customerID) {
    if (head == nullptr) {
      return false;
    }

    CustomerNode* current = head;
    do {
      if (current->customer.id == customerID) {
        return true;
      }
      current = current->next;
    }while (current != head);

    return false;
  }

  // searchCustomerPtr
  // How it works: Loops through list, returns pointer when ID matches
  Customer* searchCustomerPtr(int customerID) {
    if (head == nullptr) {
      cout << "Customer with ID: " << customerID << " not found :(" << endl;
      return nullptr;
    }

    CustomerNode* current = head;
    do {
      if (current->customer.id == customerID) {
        cout << "Customer with ID: " << customerID << " found!" << endl;
        return &(current->customer);
      }
      current = current->next;
    }while (current != head);

    cout << "Customer with ID: " << customerID << " not found :(" << endl;
    return nullptr;
  }

  // searchCustomer
  // How it works: Same as searchCustomerPtr but returns a copy
  // Returns: Pointer to the customer (allows modifying the original)
  //          Returns nullptr if not found
  Customer searchCustomer(int customerID) {
    CustomerNode* current = head;

    if (head == nullptr) {
      cout << "Customer with ID: " << customerID << " not found :(" << endl;
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

  // isEmpty
  // How it works: Returns true if head is null
  // Returns: true if empty, false if has customers
  bool isEmpty() {
    if (head == nullptr) {
      return true;
    }
    return false;
  }

  // getSize
  // Returns: The count of customers
  int getSize() {
    return size;
  }

  // updateCustomerInfo
  // How it works: Finds the customer by ID and updates their fields
  void updateCustomerInfo(int id, string name, string phoneNumber, string email) {
    if (head == nullptr) {
      cout << "Customer not found :(" << endl;
      return;
    }

    CustomerNode* current = head;
    do {
      if (current->customer.id == id) {
        current->customer.name = name;
        current->customer.phoneNumber = phoneNumber;
        current->customer.email = email;
        cout << "Customer information updated successfully :D" << endl;
        return;
      }
      current = current->next;
    }while (current != head);

    cout << "Customer not found :(" << endl;
  }

  // upload
  // How it works:
  //   - Loops through each customer
  //   - Writes their info and rented movies to the file
  void upload(ofstream &file) {
    if (head == nullptr) {
      cout << "There is no customer data to upload" << endl;
      return;
    }

    CustomerNode* current = head;
    do {
      // Write customer basic info
      file << current->customer.id << endl;
      file << current->customer.name << endl;
      file << current->customer.phoneNumber << endl;
      file << current->customer.email << endl;
      file << current->customer.counter << endl;

      // Write rented movies
      for (int i = 0; i < current->customer.counter; i++) {
        file << current->customer.rentedMovies[i].id << endl;
        file << current->customer.rentedMovies[i].title << endl;
        file << current->customer.rentedMovies[i].genre << endl;
        file << current->customer.rentedMovies[i].price << endl;
        file << current->customer.rentedMovies[i].quantity << endl;
      }

      current = current->next;
    }while (current != head);
  }

  // download
  // How it works:
  //   - Reads each customer's info from the file
  //   - Also reads their rented movies
  //   - Adds each customer to the list
  void download(ifstream &file) {
    int id;
    while (file >> id) {
      file.ignore();  // ignore newline after id

      Customer current;
      current.id = id;
      getline(file, current.name);
      getline(file, current.phoneNumber);
      getline(file, current.email);
      file >> current.counter;
      file.ignore();

      // Read rented movies
      for (int i = 0; i < current.counter; i++) {
        file >> current.rentedMovies[i].id;
        file.ignore();
        getline(file, current.rentedMovies[i].title);
        getline(file, current.rentedMovies[i].genre);
        file >> current.rentedMovies[i].price;
        file >> current.rentedMovies[i].quantity;
        file.ignore();
      }

      insertCustomer(current);
      cout << endl;
    }
  }
};


// BST CLASS - BINARY SEARCH TREE
// Stores all movies organized by ID for fast searching
// Left children have smaller IDs, right children have larger IDs
class BST {
private:
  // insertAssistant (Private Helper)
  // How it works:
  //   - If we hit an empty spot (nullptr), create new node here
  //   - If movie ID is smaller, go left
  //   - If movie ID is larger, go right
  // Returns: The node (possibly new) at this position
  Node* insertAssistant(Node* node, const Movie& movie){
    // Empty spot found - create new node here
    if(node == nullptr){
      return new Node(movie);
    }

    // Go left if ID is smaller, right if larger
    if(movie.id < node->movie.id){
      node->left = insertAssistant(node->left, movie);
    }else if(movie.id > node->movie.id){
      node->right = insertAssistant(node->right, movie);
    }

    return node;
  }

  // searchAssistant (Private Helper)
  // How it works:
  //   - If current node matches, we found it
  //   - If ID is smaller, search left subtree
  //   - If ID is larger, search right subtree
  // Returns: Pointer to the node containing the movie, or nullptr
  Node* searchAssistant(Node* node, int id, bool &found){
    if(node == nullptr){
      return nullptr;
    }

    // Found the movie
    if(node->movie.id == id){
      found = true;
      return node;
    }

    // Search left or right based on ID
    if(node->movie.id > id){
      return searchAssistant(node->left, id, found);
    }else{
      return searchAssistant(node->right, id, found);
    }
  }

  // findMin (Private Helper)
  // How it works: Keeps going left until there's no more left child
  // Returns: Pointer to the node with smallest ID in this subtree
  Node* findMin(Node* node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  // deleteAssistant (Private Helper)
  // How it works:
  //   - First, navigate to find the node to delete
  //   - Then handle 3 cases:
  //     1. No children: just delete the node
  //     2. One child: replace node with its child
  //     3. Two children: replace with smallest node from right subtree
  // Returns: The updated subtree after deletion
  Node* deleteAssistant(Node* node, int id){
    if(node == nullptr){
      return nullptr;
    }

    // Navigate to find the node
    if(node->movie.id > id){
      node->left = deleteAssistant(node->left, id);
    } else if(node->movie.id < id){
      node->right = deleteAssistant(node->right, id);
    }else{
      // Found the node to delete

      //no children - simply remove
      if(node->left == nullptr && node->right == nullptr){
        delete node;
        return nullptr;
      }
      //one child (right only) - replace with right child
      else if(node->left == nullptr){
        Node*temp = node->right;
        delete node;
        return temp;
      }
      //one child (left only) - replace with left child
      else if(node->right == nullptr){
        Node*temp = node->left;
        delete node;
        return temp;
      }
      //two children - replace with in-order successor
      else {
        Node* temp = findMin(node->right);
        // Copy the successor's data
        node->movie = temp->movie;
        // Delete the successor
        node->right = deleteAssistant(node->right, temp->movie.id);
      }
    }
    return node;
  }

  // DESTROYTHETREEAssistant (Private Helper)
  // How it works: Post-order traversal - delete children first, then self
  void DESTROYTHETREEAssistant(Node* node){
    if(node != nullptr){
      DESTROYTHETREEAssistant(node->left);
      DESTROYTHETREEAssistant(node->right);
      delete node;
    }
  }

  // CountNodesAssistant (Private Helper)
  // How it works: Returns 1 + count of left subtree + count of right subtree
  // Returns: Total number of nodes in this subtree
  int CountNodesAssistant(Node* node){
    if(node == nullptr){
      return 0;
    }
    return 1 + CountNodesAssistant(node->left) + CountNodesAssistant(node->right);
  }

  // displayAssistant (Private Helper)
  // How it works: In-order traversal - left, current, right
  //               This gives us movies sorted from lowest to highest ID
  void displayAssistant(Node* node){
    if(node != nullptr){
      displayAssistant(node->left);

      cout << "------------------------------------------" << endl;
      cout << "ID:       " << node->movie.id << endl;
      cout << "Title:    " << node->movie.title << endl;
      cout << "Genre:    " << node->movie.genre << endl;
      cout << "Price:    " << node->movie.price << " SAR" << endl;
      cout << "Quantity: " << node->movie.quantity << endl;
      cout << "------------------------------------------" << endl;

      displayAssistant(node->right);
    }
  }

  // uploadAssistant (Private Helper)
  // How it works: In-order traversal, writing each movie's data to file
  void uploadAssistant(Node* node, ofstream &file) {
    if (node != nullptr) {
      uploadAssistant(node->left, file);

      file << node->movie.id << endl;
      file << node->movie.title << endl;
      file << node->movie.genre << endl;
      file << node->movie.price << endl;
      file << node->movie.quantity << endl;

      uploadAssistant(node->right, file);
    }
  }

public:
  Node* root;   // Root node of the tree

  // Constructor
  BST(){
    root = nullptr;
  }

  // Destructor
  ~BST(){
    DESTROYTHETREEAssistant(root);
  }

  // insert
  // How it works: Calls the recursive helper to find the right spot
  void insert(const Movie& movie){
    root = insertAssistant(root, movie);
    cout << movie.title << " has been added to the system successfully." << endl;
  }

  // deleteNode
  // How it works: First checks if movie exists, then calls helper to delete
  void deleteNode(int id){
    Movie* temp = searchByID(id);
    if (temp!= nullptr) {
      cout << "Deleting " << temp->title << "... " << endl;
      root = deleteAssistant(root, id);
      cout << "Movie deleted successfully!" << endl;
    } else {
      cout << "ID not found." << endl;
    }
  }

  // displayMovies
  // How it works: Calls the in-order traversal helper
  void displayMovies(){
    if(root == nullptr){
      cout << "The movie system is currently empty." << endl;
    } else {
      cout << "\n--- Current Movie Inventory (Sorted by ID) ---" << endl;
      displayAssistant(root);
      cout << "--- End of Inventory ---\n" << endl;
    }
  }

  // isEmpty
  // Returns: true if empty, false if has movies
  bool isEmpty(){
    if(root == nullptr) {
      return true;
    }else{
      return false;
    }
  }

  // searchByID
  // How it works: Uses the recursive search helper
  // Returns: Pointer to the Movie (allows modification), nullptr if not found
  Movie* searchByID(int id){
    bool found = false;
    Node* temp = searchAssistant(root, id, found);
    if(found != false){
      return &(temp->movie);
    }else{
      return nullptr;
    }
  }

  // countAllNodes
  // Returns: Count of all movies
  int countAllNodes(){
    return CountNodesAssistant(root);
  }

  // upload
  void upload(ofstream &file) {
    if (isEmpty()) {
      cout << "There is nothing to upload" << endl;
      return;
    }
    uploadAssistant(root, file);
  }

  // download
  // How it works: Reads each movie's data and inserts it into the tree
  void download(ifstream &file) {
    int id;
    while (file >> id) {
      file.ignore();  // ignore newline after id

      Movie tempMovie;
      tempMovie.id = id;
      getline(file, tempMovie.title);
      getline(file, tempMovie.genre);
      file >> tempMovie.price;
      file >> tempMovie.quantity;
      file.ignore();

      insert(tempMovie);
    }
  }

};

// add_movie
// How it works:
//   1. Asks for a unique ID (loops until unique ID is entered)
//   2. Gets title, genre, price, and quantity from user
//   3. Creates a Movie object and inserts it into the BST
void add_movie(BST &bst) {
  int id;
  string title;
  string genre;
  float price;
  int quantity;
  Movie *existingMovie = nullptr;

  cout << "---Add New Movie---" << endl;

  // Keep asking for ID until a unique one is entered
  do {
    while (true) {
      cout << "Enter ID: ";
      while (!(cin >> id)) {
        cout << "Error: Please enter a valid number for ID: ";
        cin.clear();
        cin.ignore(10000, '\n');
      }
      cin.ignore(10000, '\n');
      if (id>=100000 && id<=999999) {
        break;
      }
      else {
        cout << "Invalid. Please enter exactly 6 digits." << endl;
      }
    }
    existingMovie = bst.searchByID(id);
    if (existingMovie != nullptr) {
      cout << "Movie with ID " << id << " already exists: " << existingMovie->title << ". Please enter a new, unique ID." << endl;
    }
  }while (existingMovie != nullptr);

  // Get remaining movie details
  cout << "Enter title: ";
  getline(cin, title);

  cout << "Enter genre: ";
  getline(cin, genre);

  cout << "Enter price: ";
  while (!(cin >> price)) {
    cout << "Error: Please enter a valid number for Price: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }
  cin.ignore(10000, '\n');

  cout << "Enter quantity available: ";
  while (!(cin >> quantity)) {
    cout << "Error: Please enter a valid number for quantity: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }

  // Create and add the movie
  Movie newMovie(id, title, genre, price, quantity);
  bst.insert(newMovie);
}

// search_movie
// How it works:
//   1. Asks user for the movie ID
//   2. Searches the BST for that ID
//   3. If found, displays all movie details; otherwise shows error
void search_movie(BST &bst) {
  int id;
  while (true) {
    cout << "Enter ID you want to search: ";
      while (!(cin >> id)) {
        cout << "Error: Please enter a valid number for ID: ";
        cin.clear();
        cin.ignore(10000, '\n');
      }
      cin.ignore(10000, '\n');

    if (id >= 100000 && id <= 999999) {
      break;
    }
    else {
      cout << "Invalid. Please enter exactly 6 digits." << endl;
    }
  }

  Movie *foundmovie = bst.searchByID(id);

  // Display movie if found
  if (foundmovie != nullptr) {
    cout << "--- Movie Found ---" << endl;
    cout << "--- Movie Details ---" << endl;
    cout << "ID: " << foundmovie->id << endl;
    cout << "Title: " << foundmovie->title << endl;
    cout << "Genre: " << foundmovie->genre << endl;
    cout << "Price: " << foundmovie->price << " SAR" << endl;
    cout << "Quantity: " << foundmovie->quantity << endl;
  } else {
    cout << "Movie not found." << endl;
  }
}

// delete_movie
// How it works:
//   1. Asks user for the movie ID to delete
//   2. Calls the BST's delete function to remove it
void delete_movie(BST &bst) {
  int id;

  while (true) {
    cout << "Enter Movie ID You want to delete: ";
      while (!(cin >> id)) {
        cout << "Error: Please enter a valid number for ID: ";
        cin.clear();
        cin.ignore(10000, '\n');
      }
      cin.ignore(10000, '\n');

    if (id >= 100000 && id <= 999999) {
      break;
    }
    else {
      cout << "Invalid. Please enter exactly 6 digits." << endl;
    }
  }
  bst.deleteNode(id);
}

// add_customer
// How it works:
//   1. Asks for a unique ID (loops until unique ID is entered)
//   2. Gets name, phone number, and email from user
//   3. Creates a Customer object and inserts it into the CLL
void add_customer(CLL &cll) {
  int id;
  string name;
  string phoneNumber;
  string email;

  cout << "---Add New Customer---" << endl;

  // Keep asking for ID until a unique one is entered
  do {
    while (true) {
      cout << "Enter ID: ";
        while (!(cin >> id)) {
          cout << "Error: Please enter a valid number for ID: ";
          cin.clear();
          cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

      if (id >= 100000 && id <= 999999) {
        break;
      }
      else {
        cout << "Invalid. Please enter exactly 6 digits." << endl;
      }
    }
    // Use silent check - doesn't print anything
    if (cll.customerExists(id)) {
      cout << "Customer with ID " << id << " already exists. Please enter a new, unique ID." << endl;
    }
  }while (cll.customerExists(id));

  // Get remaining customer details
  cout << "Enter name: ";
  getline(cin, name);

  cout << "Enter phone number: ";
  getline(cin, phoneNumber);

  cout << "Enter email: ";
  getline(cin, email);

  // Create and add the customer
  Customer customer(id, name, phoneNumber, email);
  cll.insertCustomer(customer);
  cout << endl;
}

// search_customer
// How it works:
//   1. Asks user for the customer ID
//   2. Searches the CLL for that ID
//   3. If found, displays customer info and rented movies
//   4. If not found, offers to add the customer
void search_customer(CLL &cll) {
  int id;

  while (true) {
    cout << "Enter ID you want to search: ";
    while (!(cin >> id)) {
      cout << "Error: Please enter a valid number for ID: ";
      cin.clear();
      cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    if (id >= 100000 && id <= 999999) {
      break;
    }
    else {
      cout << "Invalid. Please enter exactly 6 digits." << endl;
    }
  }

  Customer foundcustomer = cll.searchCustomer(id);

  // Display customer if found
  if (foundcustomer.id != 0) {
    cout << "--- Customer Found ---" << endl;
    cout << "ID: " << foundcustomer.id << endl;
    cout << "Name: " << foundcustomer.name << endl;
    cout << "Phone Number: " << foundcustomer.phoneNumber << endl;
    cout << "Email: " << foundcustomer.email << endl;


    cout << "Rented Movies: ";
    if (foundcustomer.counter == 0) {
      cout << "None" << endl;
    } else {
      cout << endl;
      for (int i = 0; i < foundcustomer.counter; i++) {
        cout << "  " << (i+1) << ". " << foundcustomer.rentedMovies[i].title
             << " (ID: " << foundcustomer.rentedMovies[i].id << ")" << endl;
      }
    }
  }
  else {
    // Customer not found - offer to add them
    char choice;
    cout << "Customer with ID: " << id << " not found :(" << endl;
    cout << "Do you want to add this customer? (y/n): ";
    cin >> choice;
    cin.ignore(10000, '\n');

    if (tolower(choice) == 'y') {
      add_customer(cll);
    }
  }
  cout << endl;
}

// delete_customer
// How it works:
//   1. Asks user for the customer ID to delete
//   2. Calls the CLL's delete function to remove them
void delete_customer(CLL &cll) {
  int id;
  while (true) {
  cout << "Enter ID you want to delete: ";
  while (!(cin >> id)) {
    cout << "Error: Please enter a valid number for ID: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }
  cin.ignore(10000, '\n');

    if (id >= 100000 && id <= 999999) {
      break;
    }
    else {
      cout << "Invalid. Please enter exactly 6 digits." << endl;
    }
  }

  cll.deleteCustomer(id);
  cout << endl;
}

// Rent_Movie
// How it works:
//   1. Gets the movie ID from user and finds the movie
//   2. Checks if movie is available (quantity > 0)
//   3. Gets the customer ID and finds the customer
//   4. Checks if customer hasn't reached rental limit
//   5. Adds movie to customer's rented list and decreases quantity
void Rent_Movie(BST &bst, CLL &cll)
{
  int MovieID;

  while (true) {
    cout << "Enter The Movie ID you want to Rent:";
    cin >> MovieID;
    if (MovieID >= 100000 && MovieID <= 999999) {
      break;
    }
    else {
      cout << "Invalid. Please enter exactly 6 digits." << endl;
    }
  }

  // Find the movie
  Movie *MovieToRent = bst.searchByID(MovieID);

  if (MovieToRent == nullptr)
  {
    cout << "Movie not found." << endl;
    return;
  }

  // Check if movie is available
  if (MovieToRent->quantity < 1)
  {
    cout << "The Movie can't be rented due to insufficient quantity" << endl;
    return;
  }

  int CustomerID;

  while (true) {
    cout << "Enter The ID for the customer you want to Rent a movie to:";
    cin >> CustomerID;
    if (CustomerID >= 100000 && CustomerID <= 999999) {
      break;
    }
    else {
      cout << "Invalid. Please enter exactly 6 digits." << endl;
    }
  }

  Customer* Renter = cll.searchCustomerPtr(CustomerID);

  if (Renter == nullptr)
  {
    cout << "Customer not found." << endl;
    return;
  }

  // Check if customer can rent more movies
  if (Renter->counter >= max_rent)
  {
    cout << "The customer has rented the maximum number allowed, customer must return a movie to be able to rent another one" << endl;
    return;
  }


  // Add movie to customer's rented list and decrease quantity
  Renter->rentedMovies[Renter->counter] = *MovieToRent;
  MovieToRent->quantity--;
  Renter->counter++;

  cout << "The Movie " << MovieToRent->title << " is now rented to the customer " << Renter->name << endl;
}

// Return_Movie
// How it works:
//   1. Gets the customer ID and finds the customer
//   2. Checks if customer has any rented movies
//   3. Gets the movie ID to return and finds it in customer's list
//   4. Increases movie quantity back in the system
//   5. Removes movie from customer's rented list (shifts remaining movies)
void Return_Movie(BST &bst, CLL &cll)
{
  int RenterID;
  while (true) {
    cout << "Enter The Renter ID:";
    cin >> RenterID;
    if (RenterID >= 100000 && RenterID <= 999999) {
      break;
    }
    else {
      cout << "Invalid. Please enter exactly 6 digits." << endl;
    }
  }

  Customer* Renter = cll.searchCustomerPtr(RenterID);

  if (Renter == nullptr)
  {
    cout << "The Customer does not exist" << endl;
    return;
  }

  // Check if customer has any rented movies
  if (Renter->counter == 0)
  {
    cout << "This customer has no rented movies." << endl;
    return;
  }

  int MovieID;
  int foundIndex = -1;

  while (true) {
    cout << "Enter The ID of the movie you want to Return:";
    cin >> MovieID;
    if (MovieID >= 100000 && MovieID <= 999999) {
      break;
    }
    else {
      cout << "Invalid. Please enter exactly 6 digits." << endl;
    }
  }

  // Find the movie in the renter's list
  for (int i = 0; i < Renter->counter; i++)
  {
    if (Renter->rentedMovies[i].id == MovieID)
    {
      foundIndex = i;
      break;
    }
  }

  if (foundIndex == -1)
  {
    cout << "This movie is not rented by the customer." << endl;
    return;
  }

  // Increase the movie quantity back in the system
  Movie* movieInSystem = bst.searchByID(MovieID);
  if (movieInSystem != nullptr) {
    movieInSystem->quantity++;
  }

  string returnedTitle = Renter->rentedMovies[foundIndex].title;

  // Shift remaining movies down to fill the gap
  for (int i = foundIndex; i < Renter->counter - 1; i++)
  {
    Renter->rentedMovies[i] = Renter->rentedMovies[i + 1];
  }

  // Clear the last slot
  Renter->rentedMovies[Renter->counter - 1] = Movie();
  Renter->counter--;

  cout << "The movie " << returnedTitle << " has been successfully returned by " << Renter->name << "." << endl;
}

// upload
// How it works:
//   1. Opens Customer_data.txt and writes all customer data
//   2. Opens Movie_data.txt and writes all movie data
void upload(BST &bst, CLL &cll) {
  //uploading the customers' data
  ofstream customers("Customer_data.txt");
  if (customers) {
    cll.upload(customers);
    customers.close();
    cout << "Customer data uploaded successfully :)" << endl;
  } else {
    cout << "Could not create customer file :(" << endl;
  }

  //uploading the movies' data
  ofstream movies("Movie_data.txt");
  if (movies) {
    bst.upload(movies);
    movies.close();
    cout << "Movie data uploaded successfully :)" << endl;
  } else {
    cout << "Could not create movie file :(" << endl;
  }
}

// download
// How it works:
//   1. Opens Customer_data.txt and reads all customer data into CLL
//   2. Opens Movie_data.txt and reads all movie data into BST
void download(BST &bst, CLL &cll) {
  // downloading the customers' data
  ifstream customers("Customer_data.txt");
  if (customers) {
    cll.download(customers);
    customers.close();
    cout << "Customer data downloaded successfully :D" << endl;
  } else {
    cout << "No existing customer file found (starting fresh)" << endl;
  }

  // downloading the movies' data
  ifstream movies("Movie_data.txt");
  if (movies) {
    bst.download(movies);
    movies.close();
    cout << "Movie data downloaded successfully :D" << endl;
  } else {
    cout << "No existing movie file found (starting fresh)" << endl;
  }
}

// adminPassword
// How it works:
//   1. Shows auth menu: Login, Change Password, Exit
//   2. For Login: checks if entered password matches stored password
//   3. For Change Password: verifies old password, then updates to new one
bool adminPassword(int &choice) {
  static string storedPassword = "bonelessPizza123";
  string inputPassword;

  cout << "\n--- Admin Authentication ---" << endl;
  cout << "1. Login" << endl;
  cout << "2. Change Password" << endl;
  cout << "3. Exit" << endl;
  cout << "Enter your choice: ";

  while (!(cin >> choice)) {
    cout << "Error: Please enter a valid number (1-3): ";
    cin.clear();
    cin.ignore(10000, '\n');
  }
  cin.ignore(10000, '\n');

  switch (choice) {
    case 1:   // Login option
    {
      cout << "Enter password: ";
      getline(cin, inputPassword);

      if (inputPassword == storedPassword) {
        cout << "Authentication successful! Welcome." << endl;
        return true;
      } else {
        cout << "Incorrect password. Access denied." << endl;
        return false;
      }
    }
    case 2:   // Change password option
    {
      string oldPassword, newPassword, confirmPassword;

      cout << "Enter old password: ";
      getline(cin, oldPassword);

      if (oldPassword != storedPassword) {
        cout << "Incorrect old password. Password change failed." << endl;
        return false;
      }

      cout << "Enter new password: ";
      getline(cin, newPassword);

      cout << "Confirm new password: ";
      getline(cin, confirmPassword);

      if (newPassword != confirmPassword) {
        cout << "Passwords do not match. Password change failed." << endl;
        return false;
      }

      if (newPassword.empty()) {
        cout << "Password cannot be empty. Password change failed." << endl;
        return false;
      }

      storedPassword = newPassword;
      cout << "Password changed successfully!" << endl;
      return false;  // Return to auth menu after password change
    }
    case 3:   // Exit option
    {
      cout << "Exiting authentication." << endl;
      return false;
    }
    default:
    {
      cout << "Invalid choice." << endl;
      return false;
    }
  }
}

// displayMenu
// How it works:
//   1. Shows main menu: Employee, Manager, Save Data, Exit
//   2. Employee menu: customer operations and rentals (no password needed)
//   3. Manager menu: movie operations (requires password)
//   4. Save Data: saves everything to files
//   5. Loops until user chooses to exit
void displayMenu(BST &Movies, CLL &Customers) {
    string name;
    int choice;
    int a;
    int b;
    int id;

    do {
        // Display main menu
        cout << "\n________________________________________" << endl;
        cout << "_______Welcome to the Movie Store_______" << endl;
        cout << "1. Employee (Customer & Rental Operations)" << endl;
        cout << "2. Manager (Movie/Admin Operations)" << endl;
        cout << "3. Save data " << endl;
        cout << "4. Exit" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cout << "Error: Please enter a valid number (1-4): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

        switch (choice) {
            case 1:   // Employee menu
            {
                // Employee login
                cout << "\n--- Employee Login ---" << endl;
                cout << "Enter your Name: ";
                getline(cin, name);
                cout << "Enter your ID: ";

                while (!(cin >> id)) {
                    cout << "Error: Please enter a valid number for ID: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                cin.ignore(10000, '\n');

                // Employee submenu loop
                do {
                    cout << "\n------------------------------------------" << endl;
                    cout << "--- Employee Menu ---" << endl;
                    cout << "1. Add New Customer" << endl;
                    cout << "2. Search Customer" << endl;
                    cout << "3. Update Customer Info" << endl;
                    cout << "4. Delete Customer" << endl;
                    cout << "5. Rent a Movie" << endl;
                    cout << "6. Return Movie" << endl;
                    cout << "7. Display All Movies" << endl;
                    cout << "8. Back to Main Menu" << endl;
                    cout << "------------------------------------------" << endl;
                    cout << "Enter your choice:";

                    while (!(cin >> a)) {
                        cout << "Error: Please enter a valid number (1-8): ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    cin.ignore(10000, '\n');

                    switch (a) {
                        case 1:
                        {
                          add_customer(Customers);
                            break;
                        }
                        case 2:
                        {
                            search_customer(Customers);
                            break;
                        }
                        case 3:   // Update customer info
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

                            // Check if customer exists
                            if (Customers.searchCustomer(update_id).id == 0) {
                                break;
                            }

                            // Get new information
                            cout << "Enter new Name: ";
                            getline(cin, new_name);

                            cout << "Enter new Phone Number: ";
                            getline(cin, new_phone);

                            cout << "Enter new Email: ";
                            getline(cin, new_email);

                            Customers.updateCustomerInfo(update_id, new_name, new_phone, new_email);
                            break;
                        }
                        case 4:
                        {
                            delete_customer(Customers);
                            break;
                        }
                        case 5:
                        {
                            Rent_Movie(Movies, Customers);
                            break;
                        }
                        case 6:
                        {
                           Return_Movie(Movies, Customers);
                            break;
                        }
                        case 7:
                        {
                            Movies.displayMovies();
                            break;
                        }
                        case 8:
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

            case 2:   // Manager menu (requires password)
            {
              bool access = false;
              int adminChoice=0;

                // Keep asking for password until correct or user exits
                do {
                  access = adminPassword(adminChoice);
                  if (adminChoice == 3) {
                    break;
                  }
                }while(access!=true);

                // Exit if user chose to exit authentication
                if (adminChoice == 3) {
                  break;
                }

                cout << "\n--- Manager Login ---" << endl;

                // Manager submenu loop
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
                    cout << "Enter your choice:";

                    while (!(cin >> b)) {
                        cout << "Error: Please enter a valid number (1-6): ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    cin.ignore(10000, '\n');

                    switch (b) {
                        case 1:
                        {
                            search_movie(Movies);
                            break;
                        }
                        case 2:
                        {
                            Movies.displayMovies();
                            break;
                        }
                        case 3:
                        {
                          add_movie(Movies);
                            break;
                        }
                        case 4:
                        {
                          delete_movie(Movies);
                            break;
                        }
                        case 5:
                        {
                            int count = Movies.countAllNodes();
                            cout << "\nTotal number of movies in the system: " << count << endl;
                            break;
                        }
                        case 6:
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
            case 3:   // Save data option
            {
                upload(Movies, Customers);
                break;
            }
            case 4:   // Exit option
              cout << "\nExiting the Movie Store application. Goodbye!" << endl;
              break;
            default:
            {
                cout << "Invalid choice. Please enter 1, 2, 3, or 4." << endl;
                break;
            }
        }
    } while (choice != 4);
}

// main
// How it works:
//   1. Creates the data structures (BST for movies, CLL for customers)
//   2. Loads any saved data from files
//   3. Starts the main menu for user interaction
// Returns: 0 on successful completion
int main () {
  BST Movies ;        // Binary Search Tree to store movies
  CLL Customers;      // Circular Linked List to store customers

  // Load saved data from files
  download(Movies, Customers);

  // Start the main menu
  displayMenu(Movies, Customers);

  return 0;
}