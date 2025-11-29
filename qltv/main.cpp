#include "Menu.h"
#include "PhieuMuon.h"
#include "DocGia.h"
#include "Sach.h"
#include <cstdio>
#include <cstdlib> 

int main() {
	// Đọc dữ liệu từ file khi khởi động chương trình
	printf("=== KHOI TAO HE THONG ===\n");
	doc_du_lieu_doc_gia("docgia.txt");
	doc_du_lieu_sach("sach.txt");
	doc_du_lieu_phieu("phieumuon.txt");
	printf("=========================\n\n");

	int lua_chon_chinh;

	do {

		hien_thi_menu_chinh();

		if (scanf_s("%d", &lua_chon_chinh) != 1) {
			printf("\nLua chon khong hop le. Vui long chi nhap so!\n");
			// Xử lý bộ đệm nhập liệu
			while (getchar() != '\n');
			lua_chon_chinh = -1;
			continue;
		}

		// Xử lý bộ đệm sau khi đọc số
		while (getchar() != '\n');

		switch (lua_chon_chinh) {
		case 1:
			menu_doc_gia();
			break;
		case 2:
			menu_sach();
			break;
		case 3:
			menu_phieu_muon();
			break;
		case 4:
			lap_phieu_tra();
			break;
		case 5:
			menu_thong_ke();
			break;
		case 0:
			// Lưu dữ liệu trước khi thoát
			printf("\n=== LUU DU LIEU ===\n");
			ghi_du_lieu_doc_gia("docgia.txt");
			ghi_du_lieu_sach("sach.txt");
			ghi_du_lieu_phieu("phieumuon.txt");
			printf("===================\n");
			printf("\n--- CAM ON BAN DA SU DUNG CHUONG TRINH. TAM BIET! ---\n");
			break;
		default:
			printf("\nLua chon khong hop le. Vui long nhap so tu 0 den 5.\n");
			break;
		}

	} while (lua_chon_chinh != 0);

	return 0;
}
