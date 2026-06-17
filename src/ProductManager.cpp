#include <fstream>
#include <iostream>
#include <iomanip>
#include "ProductManager.h"
#include <fstream>  // Dùng để tạo luồng Đọc/Ghi file
#include <sstream>  // Dùng để chặt chuỗi văn bản theo dấu '|'

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
NodeProduct*ProductManager::findNode(const std::string& maSP) const{
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
    NodeProduct* prev=head;
    NodeProduct*cur=head->next;
    while(cur!=nullptr){
        if (cur->data.maSP==maSP){
            prev->next=cur->next;
            delete cur;
            return true;
        }
        prev = cur; 
        cur = cur->next;
    }
    return false;
    }

//hàm tìm kiếm sp
void ProductManager::searchProduct(const std::string& tuKhoa)const{
    NodeProduct* cur = head;
    bool timThay = false;

    std::cout << "\n---------------- KET QUA TIM KIEM ----------------\n";
    std::cout << "| Ma SP   | Ten san pham          | DVT     |    Don gia |\n";
    std::cout << "----------------------------------------------------------\n";
    while (cur != nullptr) {
        // std::string::npos nghĩa là "không tìm thấy"
        bool khopMa = (cur->data.maSP == tuKhoa);
        bool khopTen = (cur->data.tenSP.find(tuKhoa) != std::string::npos);
        if (khopMa || khopTen) {
            cur->data.displayRow(); 
            timThay = true;
        }
        cur = cur->next;
    }
    if (!timThay) {
        std::cout << "=> Khong tim thay san pham nao khop voi tu khoa: " << tuKhoa << "\n";
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
const Product* ProductManager::getProduct(const std::string& maSP) const {
    NodeProduct* target = findNode(maSP);    
    if (target != NULL) {
        // Trả về ĐỊA CHỈ (&) của gói hàng data bên trong Node
        return &(target->data); 
    }    
    return NULL; 
}

// GHI FILE: moi san pham 1 dong, phan cach bang dau |
// Vi du: SP01|Gao ST25|Kg|35000|0.1
void ProductManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Loi: Khong mo duoc file " << filename << " de ghi!\n";
        return;
    }
    NodeProduct* cur = head;
    while (cur != nullptr) {
        file << cur->data.maSP          << "|"
             << cur->data.tenSP         << "|"
             << cur->data.donVi         << "|"
             << cur->data.donGia        << "\n";
        cur = cur->next;
    }
    file.close();
}

// DOC FILE: doc tung dong, tach theo dau |, dien vao cac truong, them vao danh sach
void ProductManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "=> File " << filename << " chua ton tai. He thong se tao moi khi luu.\n";
        return; 
    }

    std::string line;
    NodeProduct* tail = nullptr; // Khai báo cái Đuôi để nối Node không bị đảo ngược

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        Product sp;
        std::string tempDonGia; // Biến tạm hứng chữ để ép sang số

        // Dùng getline cắt từng khúc y hệt như bên Khách hàng
        std::getline(ss, sp.maSP, '|');
        std::getline(ss, sp.tenSP, '|');
        std::getline(ss, sp.donVi, '|');
        std::getline(ss, tempDonGia, '|'); // Lấy chữ số ra

        // Ép kiểu chuỗi sang double cho đơn giá
        if (!tempDonGia.empty()) {
            sp.donGia = std::stod(tempDonGia);
        } else {
            sp.donGia = 0;
        }

        // Tạo Node mới
        NodeProduct* newNode = new NodeProduct;
        newNode->data = sp;
        newNode->next = nullptr; // Vì nó sẽ đứng cuối cùng

        // Nối Node vào cuối danh sách (insertTail)
        if (head == nullptr) {
            head = newNode; // Nếu danh sách trống, nó vừa là đầu vừa là đuôi
            tail = newNode;
        } else {
            tail->next = newNode; // Móc nó vào sau cái đuôi hiện tại
            tail = newNode;       // Dời biển báo Đuôi xuống vị trí mới
        }
    }

    file.close();
    std::cout << "=> Da doc du lieu tu " << filename << " len he thong.\n";
}