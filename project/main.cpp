#include <iostream>
#include <string>

using namespace std;
int main() {
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
                    switch (a) {
                        case 1:
                            cout<<"Search"<<endl;
                            break;
                        case 2:
                            cout<<"display"<<endl;
                            break;
                            case 3:
                            cout<<"Rent"<<endl;
                            break;


                    }
                } while (a != 4);

                break;
            case 2:
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
                        cout<<"s"<<endl;
                        break;
                        case 2:
                        cout<<"display"<<endl;
                        break;
                        case 3:
                        cout<<"add"<<endl;
                        break;
                        case 4:
                        cout<<"deletaa"<<endl;
                        break;
                        default:
                        cout<<"default"<<endl;

                }
                } while (b != 5);
        }
    } while (choice != 3);
    std::cout << "Hello and welcome to " ;



    return 0;
}
