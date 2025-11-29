#ifndef DOCGIA_H
#define DOCGIA_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_DOC_GIA 100
#define MAX_CH_DOCGIA 50
#define MAX_CMND 15

// Định nghĩa struct cho Độc Giả
typedef struct {
	char ma_doc_gia[10];
	char ho_ten[MAX_CH_DOCGIA];
	char cmnd[MAX_CMND];
	char ngay_sinh[11]; // Định dạng DD/MM/YYYY
	char gioi_tinh[5]; // Nam/Nu
	char email[MAX_CH_DOCGIA];
	char dia_chi[MAX_CH_DOCGIA];
	char ngay_lap_the[11];
	char ngay_het_han[11];
} DocGia;

// Mảng toàn cục chứa danh sách độc giả
extern DocGia danh_sach_doc_gia[MAX_DOC_GIA];
extern int so_luong_doc_gia;

// Nguyên mẫu hàm Quản lý Độc giả
void xem_danh_sach_doc_gia();
void them_doc_gia();
void chinh_sua_doc_gia();
void xoa_doc_gia();
void tim_doc_gia_theo_cmnd();
void tim_doc_gia_theo_ho_ten();
int tim_vi_tri_doc_gia(const char* cmnd_can_tim);

// Hàm đọc/ghi file
bool doc_du_lieu_doc_gia(const char* filename);
bool ghi_du_lieu_doc_gia(const char* filename);

#endif // DOCGIA_H