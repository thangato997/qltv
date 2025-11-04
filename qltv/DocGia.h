#ifndef DOCGIA_H
#define DOCGIA_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_DOC_GIA 100
#define MAX_CH_DOCGIA 50 // Chiều dài tối đa của chuỗi (Tên, Email,...)
#define MAX_CMND 15

// Khai báo mảng 1 chiều toàn cục cho độc giả (Sử dụng extern để dùng chung)
// Theo đề bài: mã độc giả, họ tên, CMND, ngày tháng năm sinh, giới tính, email, địa chỉ, ngày lập thẻ và ngày hết hạn
extern char ma_doc_gia_arr[MAX_DOC_GIA][10];
extern char ho_ten_arr[MAX_DOC_GIA][MAX_CH_DOCGIA];
extern char cmnd_arr[MAX_DOC_GIA][MAX_CMND];
extern char ngay_sinh_arr[MAX_DOC_GIA][11]; // Định dạng DD/MM/YYYY
extern char gioi_tinh_arr[MAX_DOC_GIA][5]; // Nam/Nu
extern char email_arr[MAX_DOC_GIA][MAX_CH_DOCGIA];
extern char dia_chi_arr[MAX_DOC_GIA][MAX_CH_DOCGIA];
extern char ngay_lap_the_arr[MAX_DOC_GIA][11];
extern char ngay_het_han_arr[MAX_DOC_GIA][11];

extern int so_luong_doc_gia; // Biến đếm số lượng độc giả

// Nguyên mẫu hàm Quản lý Độc giả
void xem_danh_sach_doc_gia();
void them_doc_gia();
void chinh_sua_doc_gia();
void xoa_doc_gia();
void tim_doc_gia_theo_cmnd();
void tim_doc_gia_theo_ho_ten();
int tim_vi_tri_doc_gia(const char* cmnd_can_tim);

#endif // DOCGIA_H