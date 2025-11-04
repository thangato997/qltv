#ifndef SACH_H
#define SACH_H

#include <stdio.h>

#define MAX_SACH 100
#define MAX_CH_SACH 50

// Khai báo mảng 1 chiều toàn cục cho sách
// Theo đề bài: ISBN, tên sách, tác giả, nhà xuất bản, năm xuất bản, thể loại, giá sách, số quyển sách.
extern char isbn_arr[MAX_SACH][15];
extern char ten_sach_arr[MAX_SACH][MAX_CH_SACH];
extern char tac_gia_arr[MAX_SACH][MAX_CH_SACH];
extern char nxb_arr[MAX_SACH][MAX_CH_SACH];
extern int nam_xb_arr[MAX_SACH];
extern char the_loai_arr[MAX_SACH][MAX_CH_SACH];
extern long gia_sach_arr[MAX_SACH]; // Dùng long cho giá sách lớn
extern int so_quyen_arr[MAX_SACH];

extern int so_luong_sach; // Biến đếm số lượng sách hiện tại

// Nguyên mẫu hàm Quản lý Sách
void xem_danh_sach_sach();
void them_sach();
void chinh_sua_sach();
void xoa_sach();
void tim_sach_theo_isbn();
void tim_sach_theo_ten_sach();
int tim_vi_tri_sach(const char* isbn_can_tim);


#endif // SACH_H


