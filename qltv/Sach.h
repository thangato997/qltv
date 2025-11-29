#ifndef SACH_H
#define SACH_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_SACH 100
#define MAX_CH_SACH 50

// Định nghĩa struct cho Sách
typedef struct {
	char isbn[15];
	char ten_sach[MAX_CH_SACH];
	char tac_gia[MAX_CH_SACH];
	char nxb[MAX_CH_SACH];
	int nam_xb;
	char the_loai[MAX_CH_SACH];
	long gia_sach;
	int so_quyen;
} Sach;

// Mảng toàn cục chứa danh sách sách
extern Sach danh_sach_sach[MAX_SACH];
extern int so_luong_sach;

// Nguyên mẫu hàm Quản lý Sách
void xem_danh_sach_sach();
void them_sach();
void chinh_sua_sach();
void xoa_sach();
void tim_sach_theo_isbn();
void tim_sach_theo_ten_sach();
int tim_vi_tri_sach(const char* isbn_can_tim);

// Hàm đọc/ghi file
bool doc_du_lieu_sach(const char* filename);
bool ghi_du_lieu_sach(const char* filename);

#endif // SACH_H


