#ifndef THONGKE_H
#define THONGKE_H

#include <stdio.h>
#include "PhieuMuon.h" 

#define MAX_THE_LOAI_KHAC 10
extern char ma_phieu_arr[MAX_PHIEU][10];
extern int da_tra_arr[MAX_PHIEU];

// Nguyên mẫu hàm Thống kê
void thong_ke_so_luong_sach();
void thong_ke_sach_theo_the_loai();
void thong_ke_so_luong_doc_gia();
void thong_ke_doc_gia_theo_gioi_tinh();
void thong_ke_so_sach_dang_muon();
void thong_ke_doc_gia_tre_han();

#endif // THONGKE_H

