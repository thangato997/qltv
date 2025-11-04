#include "DocGia.h"
#include "Helper.h"
#include "PhieuMuon.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctype.h>

// Định nghĩa các mảng1 chiều (biến toàn cục)
// (Dữ liệu khởi tạo của bạn được giữ nguyên)
char ma_doc_gia_arr[MAX_DOC_GIA][10] = {
 "DG001",
 "DG002",
 "DG003"
};
char ho_ten_arr[MAX_DOC_GIA][MAX_CH_DOCGIA] = {
 "Nguyen Van A",
 "Tran Thi B",
 "Le Van C"
};
char cmnd_arr[MAX_DOC_GIA][MAX_CMND] = {
 "0123456789",
 "0987654321",
 "0912345678"
};
char ngay_sinh_arr[MAX_DOC_GIA][11] = {
 "15/01/1990",
 "20/05/1992",
 "30/11/1988"
};
char gioi_tinh_arr[MAX_DOC_GIA][5] = {
 "Nam",
 "Nu",
 "Nam"
};
char email_arr[MAX_DOC_GIA][MAX_CH_DOCGIA] = {
 "nva@example.com",
 "ttb@example.com",
 "lvc@example.com"
};
char dia_chi_arr[MAX_DOC_GIA][MAX_CH_DOCGIA] = {
 "Ha Noi",
 "Ho Chi Minh",
 "Da Nang"
};
char ngay_lap_the_arr[MAX_DOC_GIA][11] = {
 "15/10/2025",
 "15/10/2025",
 "15/10/2025"
};
char ngay_het_han_arr[MAX_DOC_GIA][11] = {
 "15/10/2029",
 "15/10/2029",
 "15/10/2029"
};

int so_luong_doc_gia = 3;

/**
 * @brief Xem danh sách độc giả trong thư viện (Chức năng 1a).
 * @param None
 * @return void
 */
void xem_danh_sach_doc_gia() {
	printf("\n--- DANH SACH DOC GIA ---\n");
	if (so_luong_doc_gia == 0) {
		printf("Hien khong co doc gia nao.\n");
		return;
	}

	// Updated table header to include Ngay Sinh
	printf("%-6s | %-20s | %-12s | %-11s | %-5s | %-18s | %-11s | %-11s\n",
		"Ma DG", "Ho Ten", "CMND", "Ngay Sinh", "GTinh", "Email", "Ngay Lap", "Ngay Het Han");
	printf("--------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < so_luong_doc_gia; i++) {
		printf("%-6s | %-20s | %-12s | %-11s | %-5s | %-18s | %-11s | %-11s\n",
			ma_doc_gia_arr[i], ho_ten_arr[i], cmnd_arr[i], ngay_sinh_arr[i], gioi_tinh_arr[i],
			email_arr[i], ngay_lap_the_arr[i], ngay_het_han_arr[i]);
	}
	printf("--------------------------------------------------------------------------------------------------------------\n");
}

int tim_vi_tri_doc_gia(const char* cmnd_can_tim) {
	if (cmnd_can_tim == NULL) return -1;
	for (int i = 0; i < so_luong_doc_gia; i++) {
		if (strcmp(cmnd_arr[i], cmnd_can_tim) == 0) return i;
	}
	return -1;
}

/**
 * @brief Thêm độc giả mới vào hệ thống (Chức năng1b).
 * @param None
 * @return void
 */
void them_doc_gia() {
	if (so_luong_doc_gia >= MAX_DOC_GIA) {
		printf("Danh sach doc gia da day. Khong the them moi.\n");
		return;
	}

	char cmnd_moi[MAX_CMND];

	printf("\n--- THEM DOC GIA MOI ---\n");
	printf("Nhap CMND (Day la khoa chinh, khong the sua sau nay, nhap 0 de thoat): ");

	while (true) {
		scanf_s("%14s", cmnd_moi, (unsigned)sizeof(cmnd_moi));
		cmnd_moi[sizeof(cmnd_moi) - 1] = '\0'; // Để chắc chắn không bị zero-termination
		if (strcmp(cmnd_moi, "0") == 0) {
			while (getchar() != '\n' && !feof(stdin));
			return;
		}
		while (getchar() != '\n'); // Xóa bộ đệm stdin
		if (tim_vi_tri_doc_gia(cmnd_moi) == -1) {
			break; // CMND chưa tồn tại, thoát vòng lặp
		}
		printf("Doc gia voi CMND %s da ton tai vui long nhap lai (nhap 0 de thoat).\n", cmnd_moi);
	}

	int i = so_luong_doc_gia; // Vị trí sẽ thêm độc giả mới

	// Sao chép CMND
	strcpy_s(cmnd_arr[i], cmnd_moi);

	// Tự động tạo Mã Độc Giả mới
	sprintf_s(ma_doc_gia_arr[i], sizeof(ma_doc_gia_arr[i]), "DG%03d", i + 1);
	printf("Ma Doc Gia (Tu dong tao): %s\n", ma_doc_gia_arr[i]);

	printf("Nhap Ho Ten: ");
	scanf_s(" %49[^\n]", ho_ten_arr[i], (unsigned)sizeof(ho_ten_arr[i]));
	while (getchar() != '\n'); // Xóa bộ đệm

	// Ngay Sinh with validation
	do {
		printf("Nhap Ngay Sinh (DD/MM/YYYY): ");
		scanf_s("%10s", ngay_sinh_arr[i], (unsigned)sizeof(ngay_sinh_arr[i]));
		while (getchar() != '\n');
		if (!kiem_tra_ngay(ngay_sinh_arr[i])) {
			printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
		}
		else break;
	} while (true);

	printf("Nhap Gioi Tinh (Nam/Nu): ");
	scanf_s("%4s", gioi_tinh_arr[i], (unsigned)sizeof(gioi_tinh_arr[i]));
	while (getchar() != '\n');

	printf("Nhap Email: ");
	scanf_s("%49s", email_arr[i], (unsigned)sizeof(email_arr[i]));
	while (getchar() != '\n');

	printf("Nhap Dia Chi: ");
	scanf_s(" %49[^\n]", dia_chi_arr[i], (unsigned)sizeof(dia_chi_arr[i]));
	while (getchar() != '\n');

	// Ngay Lap The with validation
	do {
		printf("Nhap Ngay Lap The (DD/MM/YYYY): ");
		scanf_s("%10s", ngay_lap_the_arr[i], (unsigned)sizeof(ngay_lap_the_arr[i]));
		while (getchar() != '\n');
		if (!kiem_tra_ngay(ngay_lap_the_arr[i])) {
			printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
		}
		else break;
	} while (true);

	// Tự động tính ngày hết hạn dựa trên ngày lập thẻ
	tinh_ngay_het_han(ngay_lap_the_arr[i], ngay_het_han_arr[i], sizeof(ngay_het_han_arr[i]));
	printf("Ngay Het Han (Tu dong tinh): %s\n", ngay_het_han_arr[i]);

	so_luong_doc_gia++;
	printf("\nDa them doc gia %s thanh cong.\n", ho_ten_arr[i]);
}

/**
 * @brief Chỉnh sửa thông tin một độc giả (Chức năng 1c).
 * @param None
 * @return void
 */
void chinh_sua_doc_gia() {
	char cmnd_can_sua[MAX_CMND];
	int lua_chon;
	printf("\n--- CHINH SUA DOC GIA ---\n");
	printf("Nhap CMND doc gia can sua: ");
	scanf_s("%14s", cmnd_can_sua, (unsigned)sizeof(cmnd_can_sua));
	while (getchar() != '\n'); // Xóa bộ đệm

	int index = tim_vi_tri_doc_gia(cmnd_can_sua);

	if (index == -1) {
		printf("Khong tim thay doc gia voi CMND: %s\n", cmnd_can_sua);
		return;
	}

	printf("Tim thay doc gia: %s (Ma: %s). Ban co the sua nhieu thong tin. Nhap 'S' de luu va thoat.\n", ho_ten_arr[index], ma_doc_gia_arr[index]);

	// Tao cac bien tam de cho phep huy bo neu can
	char tmp_ho_ten[MAX_CH_DOCGIA];
	char tmp_ngay_sinh[11];
	char tmp_gioi_tinh[5];
	char tmp_email[MAX_CH_DOCGIA];
	char tmp_dia_chi[MAX_CH_DOCGIA];
	char tmp_ngay_lap[11];
	char tmp_ngay_het[11];

	// Sao chep gia tri hien tai vao bien tam
	strcpy_s(tmp_ho_ten, sizeof(tmp_ho_ten), ho_ten_arr[index]);
	strcpy_s(tmp_ngay_sinh, sizeof(tmp_ngay_sinh), ngay_sinh_arr[index]);
	strcpy_s(tmp_gioi_tinh, sizeof(tmp_gioi_tinh), gioi_tinh_arr[index]);
	strcpy_s(tmp_email, sizeof(tmp_email), email_arr[index]);
	strcpy_s(tmp_dia_chi, sizeof(tmp_dia_chi), dia_chi_arr[index]);
	strcpy_s(tmp_ngay_lap, sizeof(tmp_ngay_lap), ngay_lap_the_arr[index]);
	strcpy_s(tmp_ngay_het, sizeof(tmp_ngay_het), ngay_het_han_arr[index]);

	char choice[8];
	bool saved = false;
	bool cancelled = false;

	while (true) {
		printf("\n1. Ho Ten\n");
		printf("2. Ngay Sinh (DD/MM/YYYY)\n");
		printf("3. Gioi Tinh (Nam/Nu)\n");
		printf("4. Email\n");
		printf("5. Dia Chi\n");
		printf("6. Ngay Lap The (DD/MM/YYYY) - (Se cap nhat lai Ngay Het Han)\n");
		printf("0. Huy bo (Huy tat ca cap nhat)\n");
		printf("Nhap lua chon (hoac 'S' de luu): ");

		if (scanf_s(" %7s", choice, (unsigned)sizeof(choice)) !=1) {
			while (getchar() != '\n'); // Xóa bộ đệm nếu nhập sai
			printf("Lua chon khong hop le.\n");
			continue;
		}
		while (getchar() != '\n'); // Xóa bộ đệm sau khi đọc

		// Nếu người dùng nhập S hoặc s thì lưu và thoát
		if (choice[0] == 'S' || choice[0] == 's') {
			saved = true;
			printf("--> Luu thay doi va thoat.\n");
			break;
		}

		// Nếu người dùng nhập một số, chuyển thành int
		lua_chon = atoi(choice);

		switch (lua_chon) {
		case 1:
			printf("Nhap Ho Ten moi: ");
			scanf_s(" %49[^\n]", tmp_ho_ten, (unsigned)sizeof(tmp_ho_ten));
			while (getchar() != '\n');
			break;
		case 2:
			// Validate ngay sinh
			do {
				printf("Nhap Ngay Sinh moi (DD/MM/YYYY): ");
				scanf_s("%10s", tmp_ngay_sinh, (unsigned)sizeof(tmp_ngay_sinh));
				while (getchar() != '\n');
				if (!kiem_tra_ngay(tmp_ngay_sinh)) {
					printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
				}
				else break;
			} while (true);
			break;
		case 3:
			printf("Nhap Gioi Tinh moi: ");
			scanf_s("%4s", tmp_gioi_tinh, (unsigned)sizeof(tmp_gioi_tinh));
			while (getchar() != '\n');
			break;
		case 4:
			printf("Nhap Email moi: ");
			scanf_s("%49s", tmp_email, (unsigned)sizeof(tmp_email));
			while (getchar() != '\n');
			break;
		case 5:
			printf("Nhap Dia Chi moi: ");
			scanf_s(" %49[^\n]", tmp_dia_chi, (unsigned)sizeof(tmp_dia_chi));
			while (getchar() != '\n');
			break;
		case 6:
			// Validate ngay lap the
			do {
				printf("Nhap Ngay Lap The moi (DD/MM/YYYY): ");
				scanf_s("%10s", tmp_ngay_lap, (unsigned)sizeof(tmp_ngay_lap));
				while (getchar() != '\n');
				if (!kiem_tra_ngay(tmp_ngay_lap)) {
					printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
				}
				else break;
			} while (true);
			// Tính lại ngày hết hạn lưu vào biến tam
			tinh_ngay_het_han(tmp_ngay_lap, tmp_ngay_het, sizeof(tmp_ngay_het));
			printf("Ngay Het Han (tam) da duoc cap nhat thanh: %s\n", tmp_ngay_het);
			break;
		case 0:
			// Huy bo tat ca cap nhat
			cancelled = true;
			printf("--> Huy bo tat ca cap nhat.\n");
			break;
		default:
			printf("Lua chon khong hop le.\n");
			break;
		}

		if (cancelled) break;
	}

	if (saved && !cancelled) {
		// Sao chep tu bien tam vao mang chinh
		strcpy_s(ho_ten_arr[index], sizeof(ho_ten_arr[index]), tmp_ho_ten);
		strcpy_s(ngay_sinh_arr[index], sizeof(ngay_sinh_arr[index]), tmp_ngay_sinh);
		strcpy_s(gioi_tinh_arr[index], sizeof(gioi_tinh_arr[index]), tmp_gioi_tinh);
		strcpy_s(email_arr[index], sizeof(email_arr[index]), tmp_email);
		strcpy_s(dia_chi_arr[index], sizeof(dia_chi_arr[index]), tmp_dia_chi);
		strcpy_s(ngay_lap_the_arr[index], sizeof(ngay_lap_the_arr[index]), tmp_ngay_lap);
		strcpy_s(ngay_het_han_arr[index], sizeof(ngay_het_han_arr[index]), tmp_ngay_het);
		printf("\nDa cap nhat thong tin cho doc gia co CMND: %s\n", cmnd_can_sua);
	} else if (cancelled) {
		printf("\nDa huy bo cac thay doi cho doc gia co CMND: %s\n", cmnd_can_sua);
	} else {
		// Truong hop thoat vong lap ma khong luu va khong huy (khong the xay ra vi logic), thong bao
		printf("\nKhong co thay doi nao duoc luu cho doc gia co CMND: %s\n", cmnd_can_sua);
	}
}

/**
 * @brief Xóa thông tin một độc giả (Chức năng 1d).
 * 
 * @param None
 * @return void
 */
void xoa_doc_gia() {
	char cmnd_can_xoa[MAX_CMND];
	printf("\n--- XOA DOC GIA ---\n");
	printf("Nhap CMND doc gia can xoa: ");
	scanf_s("%14s", cmnd_can_xoa, (unsigned)sizeof(cmnd_can_xoa));
	while (getchar() != '\n');

	int vi_tri_xoa = tim_vi_tri_doc_gia(cmnd_can_xoa);

	if (vi_tri_xoa == -1) {
		printf("Khong tim thay doc gia voi CMND: %s de xoa.\n", cmnd_can_xoa);
		return;
	}

	// Dịch chuyển các phần tử, phải làm ĐỒNG BỘ trên TẤT CẢ các mảng
	for (int i = vi_tri_xoa; i < so_luong_doc_gia - 1; i++) {
		// Dịch chuyển chuỗi (dùng strcpy_s)
		strcpy_s(ma_doc_gia_arr[i], ma_doc_gia_arr[i + 1]);
		strcpy_s(ho_ten_arr[i], ho_ten_arr[i + 1]);
		strcpy_s(cmnd_arr[i], cmnd_arr[i + 1]);
		strcpy_s(ngay_sinh_arr[i], ngay_sinh_arr[i + 1]);
		strcpy_s(gioi_tinh_arr[i], gioi_tinh_arr[i + 1]);
		strcpy_s(email_arr[i], email_arr[i + 1]);
		strcpy_s(dia_chi_arr[i], dia_chi_arr[i + 1]);
		strcpy_s(ngay_lap_the_arr[i], ngay_lap_the_arr[i + 1]);
		strcpy_s(ngay_het_han_arr[i], ngay_het_han_arr[i + 1]);
	}

	so_luong_doc_gia--;
	printf("Da xoa doc gia co CMND: %s thanh cong.\n", cmnd_can_xoa);
}

/**
 * @brief Tìm kiếm độc giả theo CMND (Chức năng 1e).
 * @param None
 * @return void
 */
void tim_doc_gia_theo_cmnd() {
	char cmnd_can_tim[MAX_CMND];
	printf("\n--- TIM KIEM DOC GIA THEO CMND ---\n");
	printf("Nhap CMND doc gia can tim: ");
	scanf_s("%14s", cmnd_can_tim, (unsigned)sizeof(cmnd_can_tim));
	while (getchar() != '\n');

	int index = tim_vi_tri_doc_gia(cmnd_can_tim);

	if (index != -1) {
		printf("Tim thay doc gia:\n");
		// In chi tiết thông tin
		printf(" Ma Doc Gia: %s\n", ma_doc_gia_arr[index]);
		printf(" Ho Ten: %s\n", ho_ten_arr[index]);
		printf(" CMND: %s\n", cmnd_arr[index]);
		printf(" Ngay Sinh: %s\n", ngay_sinh_arr[index]);
		printf(" Gioi Tinh: %s\n", gioi_tinh_arr[index]);
		printf(" Email: %s\n", email_arr[index]);
		printf(" Dia Chi: %s\n", dia_chi_arr[index]);
		printf(" Ngay Lap The: %s\n", ngay_lap_the_arr[index]);
		printf(" Ngay Het Han: %s\n", ngay_het_han_arr[index]);
	}
	else {
		printf("Khong tim thay doc gia voi CMND: %s\n", cmnd_can_tim);
	}
}

/**
 * @brief Tìm kiếm độc giả theo họ tên (Chức năng 1f).
 * @param None
 * @return void
 */
void tim_doc_gia_theo_ho_ten() {
	char ho_ten_can_tim[MAX_CH_DOCGIA];
	printf("\n--- TIM KIEM DOC GIA THEO HO TEN ---\n");
	printf("Nhap Ho Ten doc gia can tim (co the nhap mot phan): ");

	if (scanf_s(" %49[^\n]", ho_ten_can_tim, (unsigned)sizeof(ho_ten_can_tim)) != 1) {
		printf("Loi khi nhap ten.\n");
		while (getchar() != '\n'); // Xóa bộ đệm
		return;
	}
	while (getchar() != '\n'); // Xóa bộ đệm

	printf("\n%-6s | %-20s | %-12s | %-11s | %-5s | %-18s | %-11s | %-11s\n",
		"Ma DG", "Ho Ten", "CMND", "Ngay Sinh", "GTinh", "Email", "Ngay Lap", "Ngay Het Han");
	printf("--------------------------------------------------------------------------------------------------------------\n");

	bool tim_thay = false;
	for (int i = 0; i < so_luong_doc_gia; i++) {
		// Sử dụng strstr để tìm kiếm chuỗi con 
		char* s1 = chuyen_sang_chu_thuong(ho_ten_arr[i]);
		char* s2 = chuyen_sang_chu_thuong(ho_ten_can_tim);
		if (strstr(s1, s2) != NULL) {
			printf("%-6s | %-20s | %-12s | %-11s | %-5s | %-18s | %-11s | %-11s\n",
				ma_doc_gia_arr[i], ho_ten_arr[i], cmnd_arr[i], ngay_sinh_arr[i], gioi_tinh_arr[i],
				email_arr[i], ngay_lap_the_arr[i], ngay_het_han_arr[i]);
			tim_thay = true;
		}
		//Giải phóng bộ nhớ đã cấp phát
		free(s1);
		free(s2);
	}

	if (!tim_thay) {
		printf("Khong tim thay doc gia nao co Ho Ten chua: %s\n", ho_ten_can_tim);
	}
	printf("--------------------------------------------------------------------------------------------------------------\n");
}