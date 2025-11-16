#include <iostream>
#include <string>
using namespace std;

//movie struct
struct Movie{
  int id;
  string title;
  string genre;
  float price;

  //default constructor
  Movie(){
    id = 0;
    title = "";
    genre = "";
    price = 0;
  }
  //parametric constructor
  Movie(int id, string title, string genre, float price){
    this->id = id;
    this->title = title;
    this->genre = genre;
    this->price = price;
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
}


int main () {
return 0;
}