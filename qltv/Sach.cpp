#include "Sach.h"
#include "Helper.h"
#include <cstdio>
#include <cstring>
#include <cstdlib> // Cho while(getchar() != '\n');
#include <ctime>

// Định nghĩa các mảng1 chiều (biến toàn cục)
char isbn_arr[MAX_SACH][15] = {
 "978-1234567890",
 "978-0987654321",
 "978-1112131415"
};

char ten_sach_arr[MAX_SACH][MAX_CH_SACH] = {
 "Lap trinh C++",
 "CSDL va Thuc hanh",
 "Giai thuat"
};

char tac_gia_arr[MAX_SACH][MAX_CH_SACH] = {
 "Nguyen Van Dung",
 "Tran Minh",
 "Le Thi Hoa"
};

// THÊM MẢNG NXB (để khớp với Sach.h)
char nxb_arr[MAX_SACH][MAX_CH_SACH] = {
 "NXB Giao Duc",
 "NXB KHKT",
 "NXB Tre"
};

int nam_xb_arr[MAX_SACH] = {
2015,
2018,
2012
};

char the_loai_arr[MAX_SACH][MAX_CH_SACH] = {
 "Khoa hoc may tinh",
 "Khoa hoc may tinh",
 "Khoa hoc may tinh"
};

long gia_sach_arr[MAX_SACH] = {
150000,
200000,
180000
};

int so_quyen_arr[MAX_SACH] = {
10,
5,
7
};

int so_luong_sach = 3;

/**
 * @brief Hàm tìm vị trí (index) của sách dựa trên ISBN.
 * @param isbn_can_tim Con trỏ trỏ tới chuỗi ISBN cần tìm.
 * @return int: Index nếu tìm thấy, -1 nếu không tìm thấy.
 */
int tim_vi_tri_sach(const char* isbn_can_tim) {
	for (int i = 0; i < so_luong_sach; i++) {
		if (strcmp(isbn_arr[i], isbn_can_tim) == 0) {
			return i;
		}
	}
	return -1;
}

/**
 * @brief Xem danh sách các sách trong thư viện (Chức năng 2a).
 * @param None
 * @return void
 */
void xem_danh_sach_sach() {
	printf("\n--- DANH SACH SACH ---\n");
	if (so_luong_sach == 0) {
		printf("Hien khong co sach nao.\n");
		return;
	}

	// Cập nhật hiển thị đầy đủ hơn: thêm cột Nam và Gia Sach
	printf("%-15s | %-20s | %-15s | %-20s | %-4s | %-10s | %s\n", "ISBN", "Ten Sach", "Tac Gia", "The Loai", "Nam", "Gia", "So Quyen");
	printf("--------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < so_luong_sach; i++) {
		printf("%-15s | %-20s | %-15s | %-20s | %-4d | %-10ld | %d\n",
			isbn_arr[i], ten_sach_arr[i], tac_gia_arr[i],
			the_loai_arr[i], nam_xb_arr[i], gia_sach_arr[i], so_quyen_arr[i]);
	}
	printf("--------------------------------------------------------------------------------------------------------------\n");
}

/**
 * @brief Thêm sách mới vào hệ thống (Chức năng 2b).
 * @param None
 * @return void
 */
void them_sach() {
	if (so_luong_sach >= MAX_SACH) {
		printf("Danh sach sach da day. Khong the them moi.\n");
		return;
	}

	char isbn_moi[15];
	printf("\n--- THEM SACH MOI ---\n");

	// Sinh ISBN tự động và đảm bảo không trùng lặp
	char* gen_isbn = NULL;
	do {
		if (gen_isbn) {
			free(gen_isbn);
			gen_isbn = NULL;
		}
		gen_isbn = generate_random_isbn();
		if (!gen_isbn) {
			// Nếu không thể sinh, cho phép nhập tay như dự phòng
			printf("Khong the sinh ISBN. Vui long nhap ISBN tay: ");
			scanf_s("%14s", isbn_moi, (unsigned)sizeof(isbn_moi));
			while (getchar() != '\n');
			break;
		}
		strcpy_s(isbn_moi, sizeof(isbn_moi), gen_isbn);
	} while (tim_vi_tri_sach(isbn_moi) != -1);

	if (gen_isbn) {
		free(gen_isbn);
		gen_isbn = NULL;
	}

	if (tim_vi_tri_sach(isbn_moi) != -1) {
		printf("Sach voi ISBN %s da ton tai.\n", isbn_moi);
		return;
	}

	printf("Da sinh ISBN cho sach moi: %s\n", isbn_moi);

	int i = so_luong_sach; // Vị trí thêm mới

	// Thêm vào vị trí cuối
	strcpy_s(isbn_arr[i], isbn_moi);

	printf("Nhap Ten Sach: ");
	scanf_s(" %49[^\n]", ten_sach_arr[i], (unsigned)sizeof(ten_sach_arr[i]));
	while (getchar() != '\n');

	printf("Nhap Tac Gia: ");
	scanf_s(" %49[^\n]", tac_gia_arr[i], (unsigned)sizeof(tac_gia_arr[i]));
	while (getchar() != '\n');

	printf("Nhap Nha Xuat Ban: ");
	scanf_s(" %49[^\n]", nxb_arr[i], (unsigned)sizeof(nxb_arr[i]));
	while (getchar() != '\n');

	// Validate Nam Xuat Ban
	int year = 0;
	int current_year;
	current_year = lay_nam_hien_tai();
	do {
		printf("Nhap Nam Xuat Ban: ");
		if (scanf_s("%d", &year) != 1) {
			while (getchar() != '\n');
			printf("Nhap khong hop le. Vui long nhap lai.\n");
			continue;
		}
		while (getchar() != '\n');
		if (year <1000 || year > current_year) {
			printf("Nam xuat ban phai tu1000 den %d. Vui long nhap lai.\n", current_year);
		}
		else {
			nam_xb_arr[i] = year;
			break;
		}
	} while (true);

	printf("Nhap The Loai: ");
	scanf_s(" %49[^\n]", the_loai_arr[i], (unsigned)sizeof(the_loai_arr[i]));
	while (getchar() != '\n');

	// Validate Gia Sach
	long price = 0;
	do {
		printf("Nhap Gia Sach: ");
		if (scanf_s("%ld", &price) != 1) {
			while (getchar() != '\n');
			printf("Nhap khong hop le. Vui long nhap lai.\n");
			continue;
		}
		while (getchar() != '\n');
		if (price < 0) {
			printf("Gia sach phai lon hon hoac bang0. Vui long nhap lai.\n");
		}
		else {
			gia_sach_arr[i] = price;
			break;
		}
	} while (true);

	printf("Nhap So Quyen: ");
	// Validate So Quyen (must be >=0)
	int copies = 0;
	do {
		if (scanf_s("%d", &copies) != 1) {
			while (getchar() != '\n');
			printf("Nhap khong hop le. Vui long nhap lai.\n");
			continue;
		}
		while (getchar() != '\n');
		if (copies < 0) {
			printf("So quyen phai la so nguyen khong am. Vui long nhap lai.\n");
		}
		else {
			so_quyen_arr[i] = copies;
			break;
		}
	} while (true);

	so_luong_sach++;
	printf("\nDa them sach %s thanh cong.\n", ten_sach_arr[i]);
}

/**
 * @brief Chỉnh sửa thông tin một quyển sách (Chức năng 2c).
 * @param None
 * @return void
 */
void chinh_sua_sach() {
	char isbn_can_sua[15];
	int lua_chon;
	printf("\n--- CHINH SUA THONG TIN SACH ---\n");
	printf("Nhap ISBN sach can sua: ");
	scanf_s("%14s", isbn_can_sua, (unsigned)sizeof(isbn_can_sua));
	while (getchar() != '\n');

	int index = tim_vi_tri_sach(isbn_can_sua);

	if (index == -1) {
		printf("Khong tim thay sach voi ISBN: %s\n", isbn_can_sua);
		return;
	}

	printf("Tim thay sach: %s. Chon thong tin muon sua:\n", ten_sach_arr[index]);
	printf("1. Ten Sach\n");
	printf("2. Tac Gia\n");
	printf("3. Nha Xuat Ban\n");
	printf("4. Nam Xuat Ban\n");
	printf("5. The Loai\n");
	printf("6. Gia Sach\n");
	printf("7. So Quyen\n");
	printf("0. Huy bo\n");
	printf("Nhap lua chon: ");

	if (scanf_s("%d", &lua_chon) != 1) {
		while (getchar() != '\n');
		printf("Lua chon khong hop le.\n");
		return;
	}
	while (getchar() != '\n'); // Xóa bộ đệm sau khi đọc số

	switch (lua_chon) {
	case 1:
		printf("Nhap Ten Sach moi: ");
		scanf_s(" %49[^\n]", ten_sach_arr[index], (unsigned)sizeof(ten_sach_arr[index]));
		while (getchar() != '\n');
		break;
	case 2:
		printf("Nhap Tac Gia moi: ");
		scanf_s(" %49[^\n]", tac_gia_arr[index], (unsigned)sizeof(tac_gia_arr[index]));
		while (getchar() != '\n');
		break;
	case 3:
		printf("Nhap Nha Xuat Ban moi: ");
		scanf_s(" %49[^\n]", nxb_arr[index], (unsigned)sizeof(nxb_arr[index]));
		while (getchar() != '\n');
		break;
	case 4:
		// Validate Nam Xuat Ban khi chỉnh sửa
	{
		int year = 0;
		int current_year;
		current_year = lay_nam_hien_tai();
		do {
			printf("Nhap Nam Xuat Ban moi: ");
			if (scanf_s("%d", &year) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (year <1000 || year > current_year) {
				printf("Nam xuat ban phai tu1000 den %d. Vui long nhap lai.\n", current_year);
			}
			else {
				nam_xb_arr[index] = year;
				break;
			}
		} while (true);
	}
	break;
	case 5:
		printf("Nhap The Loai moi: ");
		scanf_s(" %49[^\n]", the_loai_arr[index], (unsigned)sizeof(the_loai_arr[index]));
		while (getchar() != '\n');
		break;
	case 6:
		// Validate Gia Sach khi chỉnh sửa
	{
		long price = 0;
		do {
			printf("Nhap Gia Sach moi: ");
			if (scanf_s("%ld", &price) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (price < 0) {
				printf("Gia sach phai lon hon hoac bang0. Vui long nhap lai.\n");
			}
			else {
				gia_sach_arr[index] = price;
				break;
			}
		} while (true);
	}
	break;
	case 7:
	{
		int copies = 0;
		do {
			printf("Nhap So Quyen moi: ");
			if (scanf_s("%d", &copies) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (copies < 0) {
				printf("So quyen phai la so nguyen khong am. Vui long nhap lai.\n");
			}
			else {
				so_quyen_arr[index] = copies;
				break;
			}
		} while (true);
	}
	break;
	case 0:
		printf("--> Huy bo chinh sua.\n");
		return;
	default:
		printf("Lua chon khong hop le.\n");
		return;
	}
	printf("\nDa cap nhat thong tin cho sach co ISBN: %s\n", isbn_can_sua);
}

/**
 * @brief Xóa thông tin sách (Chức năng 2d).
 * @param None
 * @return void
 */
void xoa_sach() {
	char isbn_can_xoa[15];
	printf("\n--- XOA THONG TIN SACH ---\n");
	printf("Nhap ISBN sach can xoa: ");
	scanf_s("%14s", isbn_can_xoa, (unsigned)sizeof(isbn_can_xoa));
	while (getchar() != '\n');

	int vi_tri_xoa = tim_vi_tri_sach(isbn_can_xoa);

	if (vi_tri_xoa == -1) {
		printf("Khong tim thay sach voi ISBN: %s de xoa.\n", isbn_can_xoa);
		return;
	}

	// Dịch chuyển các phần tử, phải làm ĐỒNG BỘ trên TẤT CẢ các mảng
	for (int i = vi_tri_xoa; i < so_luong_sach - 1; i++) {
		// Dịch chuyển chuỗi (dùng strcpy_s)
		strcpy_s(isbn_arr[i], isbn_arr[i + 1]);
		strcpy_s(ten_sach_arr[i], ten_sach_arr[i + 1]);
		strcpy_s(tac_gia_arr[i], tac_gia_arr[i + 1]);
		strcpy_s(nxb_arr[i], nxb_arr[i + 1]);
		strcpy_s(the_loai_arr[i], the_loai_arr[i + 1]);

		// Dịch chuyển các thuộc tính số
		nam_xb_arr[i] = nam_xb_arr[i + 1];
		gia_sach_arr[i] = gia_sach_arr[i + 1];
		so_quyen_arr[i] = so_quyen_arr[i + 1];
	}

	so_luong_sach--;
	printf("Da xoa sach co ISBN: %s thanh cong.\n", isbn_can_xoa);
}

/**
 * @brief Tìm kiếm sách theo ISBN (Chức năng 2e).
 * @param None
 * @return void
 */
void tim_sach_theo_isbn() {
	char isbn_can_tim[15];
	printf("\n--- TIM KIEM SACH THEO ISBN ---\n");
	printf("Nhap ISBN sach can tim: ");
	scanf_s("%14s", isbn_can_tim, (unsigned)sizeof(isbn_can_tim));
	while (getchar() != '\n');

	int index = tim_vi_tri_sach(isbn_can_tim);

	if (index != -1) {
		printf("Tim thay sach:\n");
		// Cập nhật hiển thị chi tiết
		printf(" ISBN: %s\n", isbn_arr[index]);
		printf(" Ten Sach: %s\n", ten_sach_arr[index]);
		printf(" Tac Gia: %s\n", tac_gia_arr[index]);
		printf(" Nha Xuat Ban: %s\n", nxb_arr[index]);
		printf(" Nam Xuat Ban: %d\n", nam_xb_arr[index]);
		printf(" The Loai: %s\n", the_loai_arr[index]);
		printf(" Gia Sach: %ld VND\n", gia_sach_arr[index]);
		printf(" So Quyen: %d\n", so_quyen_arr[index]);
	}
	else {
		printf("Khong tim thay sach voi ISBN: %s\n", isbn_can_tim);
	}
}

/**
 * @brief Tìm kiếm sách theo tên sách (Chức năng 2f).
 * @param None
 * @return void
 */
void tim_sach_theo_ten_sach() {
	char ten_sach_can_tim[MAX_CH_SACH];
	printf("\n--- TIM KIEM SACH THEO TEN SACH ---\n");
	printf("Nhap Ten Sach can tim (co the nhap mot phan): ");

	if (scanf_s(" %49[^\n]", ten_sach_can_tim, (unsigned)sizeof(ten_sach_can_tim)) != 1) {
		printf("Loi khi nhap ten.\n");
		while (getchar() != '\n');
		return;
	}
	while (getchar() != '\n');

	printf("\n%-15s | %-20s | %-15s | %-20s | %-4s | %-10s\n", "ISBN", "Ten Sach", "Tac Gia", "The Loai", "Nam", "Gia");
	printf("----------------------------------------------------------------------\n");

	bool tim_thay = false;
	for (int i = 0; i < so_luong_sach; i++) {
		// Sử dụng strstr để tìm kiếm chuỗi con
		if (strstr(ten_sach_arr[i], ten_sach_can_tim) != NULL) {
			printf("%-15s | %-20s | %-15s | %-20s | %-4d | %-10ld\n",
				isbn_arr[i], ten_sach_arr[i], tac_gia_arr[i],
				the_loai_arr[i], nam_xb_arr[i], gia_sach_arr[i]);
			tim_thay = true;
		}
	}

	if (!tim_thay) {
		printf("Khong tim thay sach voi Ten Sach: %s\n", ten_sach_can_tim);
	}
	printf("----------------------------------------------------------------------\n");
}