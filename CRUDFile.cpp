#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<string.h>
using namespace std;
class Product{
    private:
        int code,qty;
        char name[30];
        float price;
    public:
        void Input(){
            cout<<"Enter Product Code : ";cin>>code;
            cout<<"Enter Product Name : ";cin.ignore();
            cin.getline(name, 30);
            cout<<"Enter Quantity : ";cin>>qty;
            cout<<"Enter Price : ";cin>>price;
        }
        float Total(){
            return qty * price;
        }
        float Discount(){
            if(Total() > 0 && Total() <= 10){
                return Total() - Total()*0.1;
            }
            else if(Total() > 10 && Total() <= 20){
                return Total() - Total()*0.2;
            }
            else if(Total() > 20 && Total() <= 30){
                return Total() - Total()*0.3;
            }
            else if(Total() > 40 && Total() <= 50){
                return Total() - Total()*0.4;
            }else{
                return Total() - Total()*0.5;
            }
        }
        void Display(){
            cout<<setw(14)<<code
                <<setw(14)<<name
                <<setw(18)<<qty
                <<setw(15)<<price
                <<setw(15)<<Total()
                <<setw(16)<<Discount()
                <<endl;
        }
        char *getName(){
            return name;
        }
        int getCode(){
            return code;
        }
};
void Head(){
            cout<<setw(14)<<"Code"
                <<setw(14)<<"Name"
                <<setw(18)<<"Quantity"
                <<setw(15)<<"Price"
                <<setw(15)<<"Total"
                <<setw(16)<<"Payment"
                <<endl;
}
int main(){
    Product p;
    fstream file;
    int op, i, n;
    do{
        cout<<"--------------------| Mart |-------------------------"<<endl;
        cout<<"[1]. INPUT"<<endl;
        cout<<"[2]. DISPLAY"<<endl;
        cout<<"[3]. SEARCH"<<endl;
        cout<<"[4]. UPDATE"<<endl;
        cout<<"[5]. DELETE"<<endl;
        cout<<"[6]. INSERT"<<endl;
        cout<<"[7]. SORT"<<endl;
        cout<<"[8]. APPAND"<<endl;
        cout<<"[9]. EXIT"<<endl;
        cout<<"Enter your choice: ";cin>>op;
        switch(op){
            case 1:{
                file.open("product.bin", ios::out | ios::binary);
                if(!file){
                    cout<<"Error Creating File"<<endl;
                    return 0;
                }
                cout<<"Create Success !!"<<endl;
                cout<<"Enter Number of Product: ";cin>>n;
                for(i=0; i<n; i++){
                    cout<<"__________________| # "<<i<<" Product |____________________"<<endl;
                    p.Input();
                    file.write((char*)&p, sizeof(p));
                }
                file.close();
            }break;
            case 2:{
                file.open("product.bin", ios::in | ios::binary);
                Head();
                while(file.read((char*)&p, sizeof(p))){
                    p.Display();
                }
                file.close();
            }break;
            case 3:{
                file.open("product.bin", ios::in | ios::binary);
                char Search[30];
                cout<<"Enter Name Product : ";cin.ignore();
                cin.getline(Search, 30);
                bool k = false;
                Head();
                while(file.read((char*)&p, sizeof(p))){
                    if(strcmp(Search, p.getName()) == 0){
                        p.Display();
                        k = true;
                    }
                }
                if(k == false) cout<<"Search Not Found"<<endl;
                else cout<<"Success !!!"<<endl;
                file.close();
            }break;
            case 4:{
                file.open("product.bin", ios::in | ios::binary);
                fstream temp;
                temp.open("temp.bin", ios::out | ios::binary);
                int Up;
                bool k = false;
                cout<<"Enter Code Product : ";cin>>Up;
                while(file.read((char*)&p, sizeof(p))){
                    if(Up == p.getCode()){
                        p.Input();
                        temp.write((char*)&p, sizeof(p));
                        k = true;
                        cout<<"Success !!"<<endl;
                    }
                    else{
                        cout<<"No way "<<endl;
                        temp.write((char*)&p, sizeof(p));
                    }
                    if(k == false) cout<<"Search Not Found"<<endl;
                    file.close();
                    temp.close();
                    remove("product.bin");
                    rename("temp.bin", "product.bin");
                }
            }break;
            case 5:{
                file.open("product.bin", ios::in | ios::binary);
                fstream temp;
                temp.open("temp.bin", ios::out | ios::binary);
                int De;
                bool k = false;
                cout<<"Enter Code Product : ";cin>>De;
                while(file.read((char*)&p, sizeof(p))){
                    if(De == p.getCode()){
                        k = true;
                        cout<<"Success !!"<<endl;
                    }else{
                        temp.write((char*)&p, sizeof(p));
                    }
                    if(k == false) cout<<"Search Not Found"<<endl;
                    file.close();
                    temp.close();
                    remove("product.bin");
                    rename("temp.bin", "product.bin");
                }
            }break;
            case 6:{
                file.open("product.bin", ios::in | ios::binary);
                fstream temp;
                temp.open("temp.bin", ios::out | ios::binary);
                Product p1;
                int In;
                bool k = false;
                cout<<"Enter Code Product : ";cin>>In;
                while(file.read((char*)&p, sizeof(p))){
                    if(In == p.getCode()){
                        p1.Input();
                        temp.write((char*)&p1, sizeof(p1));
                        temp.write((char*)&p, sizeof(p));
                    }else{
                        temp.write((char*)&p, sizeof(p));
                    }
                    if(k == false) cout<<"Search Not Found"<<endl;
                    file.close();
                    temp.close();
                    remove("product.bin");
                    rename("temp.bin", "product.bin");
                }
            }break;
            case 7:{
                file.open("product.bin", ios::in | ios::binary);
                fstream temp;
                temp.open("temp.bin", ios::out | ios::binary);
                Product p1[20], ttemp, sort;
                int c = 0;
                while(file.read((char*)&p, sizeof(p))){
                    p1[c] = p;
                    c++;
                }
                for(i = 0 ; i < c ; i++) {
                    for(int j = i + 1 ; j < c ; j++){
                        if(p1[i].Discount() > p1[j].Discount()){
                            ttemp = p1[i];
                            p1[i] = p1[j];
                            p1[j] = ttemp;
                        }
                    }
                    sort = p1[i];
                    temp.write((char*)&sort, sizeof(sort));
                }
                file.close();
                temp.close();
                remove("product.bin");
                rename("temp.bin", "product.bin");
            }break;
            case 8:{
                file.open("product.bin", ios::app | ios::binary);
                if(!file){
                    cout<<"Error Creating File"<<endl;
                    return 0;
                }
                cout<<"Create Success !!"<<endl;
                cout<<"Enter Number of Product: ";cin>>n;
                for(i=0; i<n; i++){
                    cout<<"__________________| # "<<i<<" Product |____________________"<<endl;
                    p.Input();
                    file.write((char*)&p, sizeof(p));
                }
                file.close();
            }break;
        }
    }while(getch()==13);
    return 0;
}