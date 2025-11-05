#ifndef PHIEUMUON_H
#define PHIEUMUON_H

#include <stdio.h>

#define MAX_PHIEU 100
#define MAX_SACH_MUON 5 // Số lượng sách tối đa trong 1 phiếu

// Khai báo mảng 1 chiều toàn cục cho Phiếu Mượn/Trả
// Theo đề bài: mã độc giả, ngày mượn, ngày trả dự kiến, ngày trả thực tế và danh sách ISBN của các sách được mượn.
extern char ma_doc_gia_phieu_arr[MAX_PHIEU][10];
extern char ngay_muon_arr[MAX_PHIEU][11];
extern char ngay_tra_du_kien_arr[MAX_PHIEU][11];
extern char ngay_tra_thuc_te_arr[MAX_PHIEU][11]; // Giữ rỗng nếu chưa trả
// Thay đổi: Dùng mảng 1 chiều thay vì mảng 3 chiều
// Mỗi phiếu có tối đa MAX_SACH_MUON ISBN, mỗi ISBN 15 ký tự
// Lưu liên tiếp: isbn_sach_muon_arr[phieu_i * MAX_SACH_MUON * 15 + sach_j * 15 + char_k]
extern char isbn_sach_muon_arr[MAX_PHIEU * MAX_SACH_MUON * 15]; // Mảng 1 chiều
extern int so_sach_muon_arr[MAX_PHIEU]; // Số lượng sách thực tế trong phiếu
extern char ma_phieu_arr[MAX_PHIEU][10]; // Mã phiếu mượn
extern int da_tra_arr[MAX_PHIEU]; // 0: Chưa trả, 1: Đã trả
extern int sach_bi_mat_arr[MAX_PHIEU * MAX_SACH_MUON]; // 0: Không mất, 1: Mất (mảng 1 chiều)

extern int so_luong_phieu;

// Nguyên mẫu hàm Lập Phiếu
void lap_phieu_muon();
void lap_phieu_tra();
long int tinh_so_ngay_tre_han(const char* date_str1, const char* date_str2);
void tinh_ngay_het_han(const char* ngay_lap, char* ngay_het_han, size_t buffer_size);
void xem_danh_sach_phieu_muon();

char* lay_isbn_phieu(int phieu_idx, int sach_idx);

#endif // PHIEUMUON_H



