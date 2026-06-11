#include <iostream>
#include <iomanip>
#include "ProductManager.h"

using namespace std;
// 1. Cài đặt hàm khởi tạo
ProductManager::ProductManager() {
    head = NULL;
}
//2.Cài đặt các hàm
//thêm 1 node vô dsmn:nhưng thêm đầu-O(1)
void ProductManager::addProduct(const Product& sp){
  //Bước 1: tạo Node mới cho dữ liệu sản phẩm mới
    NodeProduct* newNode= new NodeProduct;
    newNode->data=sp;
    newNode->next=NULL;
    //ko cần this->head thì mình đang ở bên trong 1 hàm của 1 class .Hàm ko có thì nó tự động hiểu là của class
    if (head==NULL){
        head=newNode;
    }  
    else{
        newNode->next=head;
        head=newNode;
    } 
}

//hàm private
NodeProduct*ProductManager::findNode(const std::string& maSP){
    NodeProduct*cur=head;
    while(cur!=nullptr){
        if (cur->data.maSP==maSP){
            return cur;
        }
        cur=cur->next;  
    }
    return nullptr;
}
//hàm xoá sản phẩm:dùng kt 2 con trỏ
bool ProductManager::deleteProduct(const std::string& maSP){
    //th ds rỗng//dù rất ít khi xảy ra
    if (head==nullptr) return false;
    //th node cần xoá ở đầu danh sách
    if(head->data.maSP==maSP){
        NodeProduct*tmp=head;
        head=head->next;
        delete tmp;//giải phóng bộ nhớ luôn ;nếu delete head là xoá toàn bộ danh sách
        return true;
    }
    NodeProduct* pre=head;
    NodeProduct*cur=head->next;
    while(cur!=nullptr){
        if (cur->data.maSP==maSP){
            pre->next=cur->next;
            delete cur;
            return true;
        }
        pre = cur; 
        cur = cur->next;
    }
    return false;
    }

//hàm tìm kiếm sp
void ProductManager::searchProduct(const std::string& maSP){
   //khi có hàm findnode rồi
   NodeProduct* found=findNode(maSP);
   if (found==nullptr){
    cout<<"Khong tim thay san pham co ma:"<<maSP<<endl;
   }
   else {
        cout << "--- THONG TIN SAN PHAM TIM THAY ---\n";
        // Giả sử class Product có hàm hiển thị thông tin dòng đơn
        found->data.displayRow(); 
    }
}
//hàm cập nhật
bool ProductManager::updateProduct(const std::string& maSP,const Product& newData){
    NodeProduct* found=findNode(maSP);
    if(found!=nullptr){
        found->data=newData;
        return true;
    }
    return false;
}
//hàm hiển thị danh sách
void ProductManager::displayAll(){
    if (head == nullptr) {
        cout << "Kho hang dang trong!\n";
        return;
    }   
    // In Header (Tiêu đề cột)
    // 2. Vẽ tiêu đề bảng (Header)
    cout << "\n====================================================================\n";
    cout << "                      DANH SÁCH TẤT CẢ SẢN PHẨM\n";
    cout << "====================================================================\n";
    cout << "| " << left << setw(8)  << "Ma SP"
         << "| " << left << setw(22) << "Ten san pham"
         << "| " << left << setw(8) << "Don vi"
         << "| " << left << setw(10) << "Don gia"
         << " |\n";
    cout << "--------------------------------------------------------------------\n";
    NodeProduct*cur=head;
    while(cur!=nullptr){
       cur->data.displayRow();
       cur=cur->next;
    }
}

    


    
