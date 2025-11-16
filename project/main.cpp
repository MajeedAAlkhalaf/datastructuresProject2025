
#include <complex.h>
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
  //parametric constructor
  Movie(int id, string title, string genre, float price){
    id = id;
    title = title;
    genre = genre;
    price = price;
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
        searchAssistant(node->left, id, found);
      }else if(node->movie.id < id){
        searchAssistant(node->right, id, found);
      }
    }

    Node* deleteAssistant(Node* node, int id){
      if(node == nullptr){
        //if the BST is already empty then it just exits the function
        return nullptr;
      }

      if(node->movie.id < id){
        node->left = deleteAssistant(node->left, id);
      } else if(node->movie.id > id){
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

  void displayMovies(){
    /*DISPLAY FUNCTION
      Displays all movies in the BST in ascending order of ID.*/
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







void displayMenu(BST &Movies) {
string name;
int choice ;
int a;
int b;
int id;
    do {
        cout<<"1.Customer"<<endl;
        cout<<"2.Employee"<<endl;
        cout<<"Enter the number of the number you want to enter: ";
        cin>>choice;

        switch (choice) {
            case 1:
            {
                cout<<"Enter your Name: ";
                cin>>name;
                cout<<"Enter your ID: ";
                cin>>id;

                do {
                    cout<<"------------------------------------------"<<endl;
                    cout<<"1-search moive "<<endl;
                    cout<<"2-display movies"<<endl;
                    cout<<"3-Rent a movie"<<endl;
                    cout<<"4-exit"<<endl;
                    cout<<"------------------------------------------"<<endl;
                    cout<<"Enter the number of the number you want to enter: ";
                    cin>>a;
                    switch (a)
                {
                        case 1:
                        {
                            cout<<"Search"<<endl;
                            break;
                        }
                        case 2:
                        {
                           Movies.displayMovies();
                            break;
                        }
                        case 3:
                        {
                            cout<<"Rent"<<endl;
                            break;
                        }

                }
                } while (a != 4);

                break;
            }
            case 2:
            {
                do {
                    cout<<"------------------------------------------"<<endl;
                    cout<<"1-search moive "<<endl;
                    cout<<"2-display movies"<<endl;
                    cout<<"3-add movie"<<endl;
                    cout<<"4-delete movie"<<endl;
                    cout<<"5-exit"<<endl;
                    cout<<"------------------------------------------"<<endl;
                    cout<<"Enter the number of the number you want to enter: ";
                    cin>>b;
                    switch (b) {
                        case 1:
                        {
                          cout << "Enter movie ID to search: ";
                          cin >> id;
                           cout<< Movies.searchByID(id);
                            break;
                        }
                        case 2:
                        {
                            Movies.displayMovies();
                            break;
                        }
                        case 3:
                        {
                          int newId;
                          string newTitle, newGenre;
                          float newPrice;
                          cout << "Enter ID: "; cin >> newId;
                          cout << "Enter Title: "; cin.ignore(); getline(cin, newTitle);
                          cout << "Enter Genre: "; getline(cin, newGenre);
                          cout << "Enter Price: "; cin >> newPrice;
                          Movie newMovie(newId,newTitle,newGenre,newPrice);
                         Movies.insert(newMovie);
                            break;
                        }
                        case 4:
                        {
                          cout << "Enter movie ID to delete: ";
                          cin >> id;
                          Movies.deleteNode(id);
                            break;
                        }


                    }
                } while (b != 5);
            }
        }
    } while (choice != 3);
}




int main() {


BST Movies;

displayMenu(Movies);

    return 0;
}
