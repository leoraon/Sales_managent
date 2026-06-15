#include<iostream>
#include <iomanip>
#include "CustomerManager.h"
using namespace std;

//1.Cài đặt hàm khởi tạo
CustomerManager::CustomerManager(){
    head=NULL;
}
//Hàm thêm 1 khách hàng mới
void CustomerManager::addCustomer(const Customer& kh){
    NodeCustomer* newNode=new NodeCustomer;
    newNode->data=kh;
    newNode->next=nullptr;
    if (head==nullptr){
        head=newNode;
    }
    else{
        newNode->next=head;
        head=newNode;
    }
}
//hàm xoá khách hàng với kĩ thuật 2 con trỏ
bool CustomerManager::deleteCustomer(const std::string& maKH){
    if (head==nullptr) return false;
    if (head->data.maKH==maKH){
        NodeCustomer*tmp=head;
        head=head->next;
        delete tmp;
        return true;
    }
    NodeCustomer*prev=head;
    NodeCustomer*cur=head->next;
    while(cur!=nullptr){
        if (cur->data.maKH==maKH){
            prev->next=cur->next;
            delete cur;
            return true;
        }
        prev=cur;
        cur=cur->next;
    }
    return false;
}
//hàm private
NodeCustomer*CustomerManager::findNode(const std::string& maKH){
    NodeCustomer*cur=head;
    while(cur!=nullptr){
        if (cur->data.maKH==maKH){
            return cur;
        }
        cur=cur->next;  
    }
    return nullptr;
}
void CustomerManager::searchCustomer(const std::string& maKH){
     //khi có hàm findnode rồi
   NodeCustomer* found=findNode(maKH);
   if (found==nullptr){
    cout<<"Khong tim thay khach hang co ma:"<<maKH<<endl;
   }
   else {
        cout << "--- THONG TIN KHACH HANG CAN TIM ---\n";
        // Giả sử class Product có hàm hiển thị thông tin dòng đơn
        found->data.displayRow(); 
    }
}
//hàm cập nhật
bool CustomerManager::updateCustomer(const std::string& maKH,const Customer& newData){
    NodeCustomer* found=findNode(maKH);
    if(found!=nullptr){
        found->data=newData;
        return true;
    }
    return false;
}
//hàm hiển thị danh sách
void CustomerManager::displayAll(){
    if (head == nullptr) {
        cout << "Danh sach khach hang hien dang trong!\n";
        return;
    }   
    // In Header (Tiêu đề cột)
    // 2. Vẽ tiêu đề bảng (Header)
    cout << "\n====================================================================\n";
    cout << "                      DANH SACH KHACH HANG\n";
    cout << "====================================================================\n";
    cout << "| " << left << setw(8)  << "Ma KH"
         << "| " << left << setw(22) << "Ten KH"
         << "| " << left << setw(8) << "SDT"
         << "| " << left << setw(10) << "Diem tich luy"
         << " |\n";
    cout << "--------------------------------------------------------------------\n";
    NodeCustomer*cur=head;
    while(cur!=nullptr){
       cur->data.displayRow();
       cur=cur->next;
    }
}

// Tra cứu khách hàng theo mã (const - không sửa dữ liệu)

Customer* CustomerManager::getCustomer(const std::string& maKH) {
    NodeCustomer* tmp = head; 
    while (tmp != NULL) {
        if (tmp->data.maKH == maKH) {
            return &(tmp->data); // Trả về địa chỉ của KH để bên ngoài có thể sửa điểm
        }
        tmp = tmp->next;
    }
    return NULL; 
}

Customer* CustomerManager::getCustomerByPhone(const std::string& sdt) {
    NodeCustomer* temp = head; 
    while (temp != NULL) {
        if (temp->data.SDT == sdt) {  // So sánh khớp số điện thoại
            return &(temp->data); 
        }
        temp = temp->next;
    }
    return NULL;
}
