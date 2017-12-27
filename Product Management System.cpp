#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cstdlib>
using namespace std;

class Product{
    int id;
    string name;
    double unitPrice;
    int stock;
    bool status;

public:

    Product(){
    this->id=0;
    this->name="Nil";
    this->unitPrice=0.00;
    this->stock=0;
    this->status=0;
    }

    void setid(int id){
    this->id=id;
    }
    void setname(string name){
    this->name=name;
    }
    void setunitPrice(double unitPrice){
    this->unitPrice=unitPrice;
    }
    void setstock(int stock){
    this->stock=stock;
    }
    void setstatus(bool status){
    this->status=status;
    }

    int getid(){
    return this->id;
    }
    string getname(){
    return this->name;
    }
    double getunitPrice(){
    return this->unitPrice;
    }
    int getstock(){
    return this->stock;
    }
    bool getstatus(){
    return this->status;
    }
    bool operator==(int y){
    if (y==this->getid())
        return true;
    else
        return false;
    }

};

    list<Product> productList;


    void initializeProductList(){
        Product p;
        int id;
        string name;
        double unitPrice;
        int stock;
        bool status;

        fstream fin;
        fin.open("product.dat");
        while(fin>>id && fin>>name &&fin>>unitPrice &&fin>>stock &&fin>>status){
            p.setid(id);
            p.setname(name);
            p.setunitPrice(unitPrice);
            p.setstock(stock);
            p.setstatus(status);
            productList.push_back(p);
        }
        fin.close();
    }

    Product* searchById(int A){
        list<Product>::iterator It;
        It = productList.begin();
        Product *ptr;

        while (It!= productList.end()){
            if (A==It->getid()){
                ptr=&*It;
                return ptr;
                break;
                }
            else{
                It++;
                if(It==productList.end()){
                            return NULL;
                            break;
                    }
                continue;
            }
        }
}

void save(){
    fstream fout("product.dat");
    list<Product>::iterator It;
    It = productList.begin();
    while (It!= productList.end()){
        fout<<It->getid()<<endl;
        fout<<It->getname()<<endl;
        fout<<It->getunitPrice()<<endl;
        fout<<It->getstock()<<endl;
        fout<<It->getstatus()<<endl;
        It++;
    }
    fout.close();
}
void addNewProduct(Product p){
    list<Product>::iterator It;
    It = productList.begin();
    while (It!= productList.end()){
      if(p.getid()>It->getid()){
        productList.push_back(p);
         break;
         It++;
        }
        else{
            break;
            It++;
            }
        }
    save();
}

void editProduct(Product* p,string name){
    p->setname(name);
    save();
}

void deleteProduct(Product* p){
    list<Product>::iterator It;
    It = productList.begin();
    while (It!= productList.end()){
        if (p->getid()==It->getid()){
            It=productList.erase(It);
            break;
            }
        It++;
    }
    save();
}

void printProduct(Product* p){
    if(p==0){
        cout<<"Product Not Found"<<endl;
        cout<<endl;
    }
    else {
        cout<<"Id: "<<p->getid()<<endl;
        cout<<"Name: "<<p->getname()<<endl;
        cout<<"Unit Price: "<<p->getunitPrice()<<endl;
        cout<<"Stock: "<<p->getstock()<<endl;
        cout<<"Status: "<<p->getstatus()<<endl;
        cout<<endl;
    }
    save();
}

void printAllProducts(){
    list<Product>::iterator It;
    It = productList.begin();
    cout<<"Id:\t"<<"Name:"<<"\t\t"<<"Unit Price:\t"<<"Stock:\t"<<"Status:"<<endl;
    while (It != productList.end()){
        cout<<It->getid()<<"\t"<<It->getname()<<"\t\t"<<It->getunitPrice()<<"\t\t"<<It->getstock()<<"\t"<<It->getstatus()<<"\t"<<endl;
        It++;
    }
    save();
}

int main(){
    Product p1,*p2;
    int x,choice,id,stock;
    string name;
    double unitPrice;
    bool status;

    initializeProductList();
tuse:
    cout<<"Product Management System"<<endl;
    cout<<"========================="<<endl;
    cout<<"1. Search Product"<<endl;
    cout<<"2. View All Products"<<endl;
    cout<<"3. Add new Products"<<endl;
    cout<<"4. Edit Product"<<endl;
    cout<<"5. Delete Product"<<endl;
    cout<<"6. Clear Screen"<<endl;
    cout<<"7. Exit"<<endl;
    cout<<"======================"<<endl;
    cout<<"Enter Your Choice Here:"<<endl;

    cin>>choice;

    switch(choice){
case 1:
    cout<<"----------------------"<<endl;
    cout<<"Showing Product Detail:"<<endl;
    cin>>x;
    p2=searchById(x);
    printProduct(p2);
    break;
case 2:
    printAllProducts();
    cout<<endl;
    save();
    break;
case 3:
    cout<<"Enter Product ID: ";
    cin>>id;
    p1.setid(id);
    cout<<"Enter Product Name: ";
    cin>>name;
    p1.setname(name);
    cout<<"Enter Product Unit Price: ";
    cin>>unitPrice;
    p1.setunitPrice(unitPrice);
    cout<<"Enter Product Quantity: ";
    cin>>stock;
    p1.setstock(stock);
    cout<<"Enter Product Status: ";
    cin>>status;
    p1.setstatus(status);
    cout<<"=========================="<<endl;
    cout<<"Product Added Successfully! ";
    cout<<endl;
    addNewProduct(p1);
    save();
    break;
case 4:
    cout<<"Enter Product ID: ";
    cin>>x;
    p2=searchById(x);
    cout<<"Enter Product New Name: ";
    cin>>name;
    editProduct(p2,name);
    cout<<"==========================="<<endl;
    cout<<"Product Edited Successfully! ";
    cout<<endl;
    save();
    break;
case 5:
    cout<<"Enter Product ID: ";
    cin>>x;
    p2=searchById(x);
    deleteProduct(p2);
    cout<<"============================"<<endl;
    cout<<"Product Deleted Successfully!";
    cout<<endl;
    save();
    break;
case 6:
    system("CLS");
    break;
case 7:
    save();
    exit(0);
    break;
default:
    exit(1);
    }
    goto tuse;

    return 0;
}

