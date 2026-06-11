#pragma once
//Khi chương trình lớn lên, các file sẽ gọi chéo (include) lẫn nhau rất nhiều.Dòng lệnh này giống như một "chốt chặn", báo cho trình biên dịch C++ biết rằng: "Dù file này có được gọi bao nhiêu lần đi nữa, hãy chỉ nạp nó vào bộ nhớ đúng 1 lần thôi
#include <string>
struct Customer{
    std:: string maKH;
    std:: string tenKH;
    std:: string SDT;   
    //bổ sung điểm tích luỹ
    int diemTichluy;
    //tạm thời chưa học hàm trình bày
    void displayRow() const {
        std::cout << "| " << std::left << std::setw(8)  << maKH
                  << "| " << std::left << std::setw(22) << tenKH
                  << "| " << std::left << std::setw(8)  << SDT
                  << "| " << std::left << std::setw(8)  << diemTichluy
                  << " |\n";
};
};
//cái phần node này là mình sẽ chọn 1 cấu trúc để lưu trữ thông tin khách hàng:thì mình học có mảng động,danh sách móc nối là đơn giản nhất//chọn 1 trong 2
//so sánh từng cái nên chọn cái nào thì ok hơn
// Cấu trúc Mắt xích (Node) cho Danh sách liên kết Khách hàng
struct NodeCustomer{
    Customer data;
    NodeCustomer* next;
};
