#include "Menu.h"
#include "DocGia.h"
#include "Sach.h"
#include "PhieuMuon.h"
#include "ThongKe.h"
#include <cstdio>
#include <cstdlib>

// Hàm hiển thị menu chính (Chức năng 1-5)
void hien_thi_menu_chinh() {
	printf("\n\n=============== MENU CHINH QUAN LY THU VIEN ==============\n");
	printf("1. Quan ly Doc gia\n");
	printf("2. Quan ly Sach\n");
	printf("3. Lap phieu Muon sach\n");
	printf("4. Lap phieu Tra sach\n");
	printf("5. Cac Thong ke co ban\n");
	printf("0. Thoat chuong trinh\n");
	printf("=========================================================\n");
	printf("Nhap lua chon cua ban: ");
}

// Menu Quản lý Độc giả (Chức năng 1.)
void menu_doc_gia() {
	char lua_chon;
	do {
		printf("\n\n========== QUAN LY DOC GIA (1.) ==========\n");
		printf("a. Xem danh sach doc gia\n");
		printf("b. Them doc gia\n");
		printf("c. Chinh sua thong tin mot doc gia\n");
		printf("d. Xoa thong tin mot doc gia\n");
		printf("e. Tim kiem doc gia theo CMND\n");
		printf("f. Tim kiem doc gia theo ho ten\n");
		printf("0. Quay lai Menu chinh\n");
		printf("==========================================\n");
		printf("Nhap lua chon cua ban: ");

		// Xóa bộ đệm và đọc ký tự
		scanf_s(" %c", &lua_chon, 1);
		while (getchar() != '\n');

		switch (lua_chon) {
		case 'a': xem_danh_sach_doc_gia(); break;
		case 'b': them_doc_gia(); break;
		case 'c': chinh_sua_doc_gia(); break;
		case 'd': xoa_doc_gia(); break;
		case 'e': tim_doc_gia_theo_cmnd(); break;
		case 'f': tim_doc_gia_theo_ho_ten(); break;
		case '0': printf("\n--> Quay lai Menu chinh...\n"); break;
		default: printf("\nLua chon khong hop le. Vui long chon lai!\n");
		}
	} while (lua_chon != '0');
}

// Menu Quản lý Sách (Chức năng 2.)
void menu_sach() {
	char lua_chon;
	do {
		printf("\n\n=========== QUAN LY SACH (2.) ===========\n");
		printf("a. Xem danh sach cac sach trong thu vien\n");
		printf("b. Them sach\n");
		printf("c. Chinh sua thong tin mot quyen sach\n");
		printf("d. Xoa thong tin sach\n");
		printf("e. Tim kiem sach theo ISBN\n");
		printf("f. Tim kiem sach theo ten sach\n");
		printf("0. Quay lai Menu chinh\n");
		printf("=========================================\n");
		printf("Nhap lua chon cua ban: ");


		scanf_s(" %c", &lua_chon, 1);
		while (getchar() != '\n');

		switch (lua_chon) {
		case 'a': xem_danh_sach_sach(); break;
		case 'b': them_sach(); break;
		case 'c': chinh_sua_sach(); break;
		case 'd': xoa_sach(); break;
		case 'e': tim_sach_theo_isbn(); break;
		case 'f': tim_sach_theo_ten_sach(); break;
		case '0': printf("\n--> Quay lai Menu chinh...\n"); break;
		default: printf("\nLua chon khong hop le. Vui long chon lai!\n");
		}
	} while (lua_chon != '0');
}

// Menu Thống kê (Chức năng 5.)
void menu_thong_ke() {
	char lua_chon;
	do {
		printf("\n\n========== CAC THONG KE (5.) ===========\n");
		printf("a. Thong ke so luong sach trong thu vien\n");
		printf("b. Thong ke so luong sach theo the loai\n");
		printf("c. Thong ke so luong doc gia\n");
		printf("d. Thong ke so luong doc gia theo gioi tinh\n");
		printf("e. Thong ke so sach dang duoc muon\n");
		printf("f. Thong ke danh sach doc gia bi tre han\n");
		printf("0. Quay lai Menu chinh\n");
		printf("=========================================\n");
		printf("Nhap lua chon cua ban: ");

		scanf_s(" %c", &lua_chon, 1);
		while (getchar() != '\n');

		switch (lua_chon) {
		case 'a':
			thong_ke_so_luong_sach();
			break;
		case 'b':
			thong_ke_sach_theo_the_loai();
			break;
		case 'c':
			thong_ke_so_luong_doc_gia();
			break;
		case 'd':
			thong_ke_doc_gia_theo_gioi_tinh();
			break;
		case 'e':
			thong_ke_so_sach_dang_muon();
			break;
		case 'f':
			thong_ke_doc_gia_tre_han();
			break;
		case '0':
			printf("\n--> Quay lai Menu chinh...\n");
			break;
		default: printf("\nLua chon khong hop le. Vui long chon lai!\n");
		}
	} while (lua_chon != '0');
}
