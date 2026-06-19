#include <fstream>
#include<iostream>
#include <iomanip>
#include "CustomerManager.h"
#include <fstream>  // Dùng để tạo luồng Đọc/Ghi file
#include <sstream>  // Dùng để chặt chuỗi văn bản theo dấu '|'
using namespace std;

//1.Cài đặt hàm khởi tạo
CustomerManager::CustomerManager(){
    head=NULL;
}
//Hàm thêm 1 khách hàng mới vào cuối danh sách
void CustomerManager::addCustomer(const Customer& kh){
    NodeCustomer* newNode=new NodeCustomer;
    newNode->data=kh;
    newNode->next=nullptr;
    NodeCustomer* cur=head;
    if (head==nullptr){
        head=newNode;
    }
    else{
        //duyệt đến tận cùng
        while (cur->next!=nullptr){
            cur=cur->next;
}
        cur->next=newNode;
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
void CustomerManager::searchCustomer(const std::string& tuKhoa) {
    NodeCustomer* cur = head;
    bool timThay = false;

    // In bảng tiêu đề
    std::cout << "\n---------------- KET QUA TIM KIEM ----------------\n";
    std::cout << "| Ma KH   | Ten khach hang        | SDT           |\n";
    std::cout << "---------------------------------------------------\n";

    while (cur != nullptr) {
        // Tìm kiếm theo chuỗi con (find) 
        bool khopMa  = (cur->data.maKH  == tuKhoa);
        bool khopTen = (cur->data.tenKH.find(tuKhoa) != std::string::npos);
        bool khopSDT = (cur->data.SDT.find(tuKhoa)   != std::string::npos);

        if (khopMa || khopTen || khopSDT) {
            cur->data.displayRow();
            timThay = true;
        }
        cur = cur->next;
    }
    if (!timThay) {
        std::cout << "=> Khong tim thay khach hang nao khop voi: " << tuKhoa << "\n";
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
    // 2. Vẽ tiêu đề bảng (Header)
    cout << "\n====================================================================\n";
    cout << "                      DANH SACH KHACH HANG\n";
    cout << "====================================================================\n";
    cout << "| " << left << setw(8)  << "Ma KH"
         << "| " << left << setw(22) << "Ten KH"
         << "| " << left << setw(13) << "SDT"
         << "|\n";
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

void CustomerManager::saveToFile(const std::string& filename) const {
    // Mở file ở chế độ ghi đè (ofstream)
    std::ofstream outFile(filename); 
    
    if (!outFile.is_open()) {
        std::cout << "=> Loi: Khong the tao hoac mo file " << filename << "!\n";
        return;
    }

    NodeCustomer* cur = head;
    while (cur != nullptr) {
        // In trực tiếp từng thuộc tính của data ra file
        outFile << cur->data.maKH << "|"
                << cur->data.tenKH << "|"
                << cur->data.SDT << "\n"; // Nhớ có \n để xuống dòng cho khách tiếp theo
        cur = cur->next;
    }

    outFile.close(); // Xong việc phải đóng nắp bút lại
    std::cout << "=> Da luu thanh cong vao " << filename << "\n";
}

void CustomerManager::loadFromFile(const std::string& filename) {
    // Mở file ở chế độ đọc (ifstream)
    std::ifstream inFile(filename);
    
    if (!inFile.is_open()) {
        std::cout << "=> File " << filename << " chua ton tai. He thong se tao moi khi luu.\n";
        return;
    }

    std::string line;
    // Vòng lặp: Cứ mỗi lần lấy được 1 dòng văn bản bỏ vào biến 'line' thì chạy code bên trong
    while (std::getline(inFile, line)) {
        if (line.empty()) continue; // Bỏ qua nếu lỡ đọc phải dòng trắng

        std::stringstream ss(line); // Biến dòng văn bản thành một "dòng chảy" để chặt
        Customer kh;

        // Dùng getline cắt tới khi gặp dấu '|' thì dừng
        std::getline(ss, kh.maKH, '|');
        std::getline(ss, kh.tenKH, '|');
        std::getline(ss, kh.SDT, '|');
        addCustomer(kh);
    }

    inFile.close();
    std::cout << "=> Da doc du lieu tu " << filename << " len he thong.\n";
    capNhatBodem(); // Cập nhật bộ đếm sau khi đọc file
}


// Tìm mã KH lớn nhất trong danh sách để cập nhật bộ đếm
void CustomerManager::capNhatBodem() {
    int maxSo = 0;
    NodeCustomer* cur = head;
    while (cur != nullptr) {
        std::string ma = cur->data.maKH; // Ví dụ: "KH0012"
        if (ma.size() > 2 && ma.substr(0, 2) == "KH") {
            int so = std::stoi(ma.substr(2)); // "0012" → 12
            if (so > maxSo) maxSo = so;
        }
        cur = cur->next;
    }
    Customer::demKH = maxSo;
}
