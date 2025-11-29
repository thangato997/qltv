#ifndef PHIEUMUON_H
#define PHIEUMUON_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_PHIEU 100
#define MAX_SACH_MUON 5

// Định nghĩa struct cho Sách trong Phiếu
typedef struct {
	char isbn[15];
	int bi_mat; // 0: không mất, 1: mất
} SachTrongPhieu;

// Định nghĩa struct cho Phiếu Mượn
typedef struct {
	char ma_phieu[10];
	char ma_doc_gia[10];
	char ngay_muon[11];
	char ngay_tra_du_kien[11];
	char ngay_tra_thuc_te[11];
	int da_tra; // 0: chưa trả, 1: đã trả
	SachTrongPhieu sach_muon[MAX_SACH_MUON];
	int so_sach_muon;
} PhieuMuon;

// Mảng toàn cục chứa danh sách phiếu mượn
extern PhieuMuon danh_sach_phieu[MAX_PHIEU];
extern int so_luong_phieu;

// Nguyên mẫu hàm Lập Phiếu
void lap_phieu_muon();
void lap_phieu_tra();
long int tinh_so_ngay_tre_han(const char* date_str1, const char* date_str2);
void tinh_ngay_het_han(const char* ngay_lap, char* ngay_het_han, size_t buffer_size);
void xem_danh_sach_phieu_muon();

// Hàm đọc/ghi file
bool doc_du_lieu_phieu(const char* filename);
bool ghi_du_lieu_phieu(const char* filename);

#endif // PHIEUMUON_H



