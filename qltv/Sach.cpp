#include "Sach.h"
#include "Helper.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

// Định nghĩa mảng toàn cục
Sach danh_sach_sach[MAX_SACH];
int so_luong_sach = 0;

/**
 * @brief Đọc dữ liệu sách từ file.
 * @param filename Tên file cần đọc
 * @return bool: true nếu đọc thành công, false nếu thất bại
 */
bool doc_du_lieu_sach(const char* filename) {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filename, "r");
	
	if (err != 0 || file == NULL) {
		printf("Khong the mo file %s de doc. Bat dau voi du lieu trong.\n", filename);
		return false;
	}
	
	so_luong_sach = 0;
	char line[512];
	
	while (so_luong_sach < MAX_SACH && fgets(line, sizeof(line), file) != NULL) {
		// Loại bỏ newline ở cuối
		line[strcspn(line, "\r\n")] = '\0';
		
		// Bỏ qua dòng trống
		if (strlen(line) == 0) continue;
		
		Sach* s = &danh_sach_sach[so_luong_sach];
		
		// Parse dòng theo format: isbn|ten_sach|tac_gia|nxb|nam_xb|the_loai|gia_sach|so_quyen
		char* token = NULL;
		char* context = NULL;
		int field = 0;
		
		token = strtok_s(line, "|", &context);
		while (token != NULL && field < 8) {
			size_t token_len = strlen(token);
			
			switch (field) {
				case 0: // isbn
					if (token_len < sizeof(s->isbn)) {
						strcpy_s(s->isbn, sizeof(s->isbn), token);
					} else {
						strncpy_s(s->isbn, sizeof(s->isbn), token, sizeof(s->isbn) - 1);
					}
					break;
				case 1: // ten_sach
					if (token_len < sizeof(s->ten_sach)) {
						strcpy_s(s->ten_sach, sizeof(s->ten_sach), token);
					} else {
						strncpy_s(s->ten_sach, sizeof(s->ten_sach), token, sizeof(s->ten_sach) - 1);
					}
					break;
				case 2: // tac_gia
					if (token_len < sizeof(s->tac_gia)) {
						strcpy_s(s->tac_gia, sizeof(s->tac_gia), token);
					} else {
						strncpy_s(s->tac_gia, sizeof(s->tac_gia), token, sizeof(s->tac_gia) - 1);
					}
					break;
				case 3: // nxb
					if (token_len < sizeof(s->nxb)) {
						strcpy_s(s->nxb, sizeof(s->nxb), token);
					} else {
						strncpy_s(s->nxb, sizeof(s->nxb), token, sizeof(s->nxb) - 1);
					}
					break;
				case 4: // nam_xb
					s->nam_xb = atoi(token);
					break;
				case 5: // the_loai
					if (token_len < sizeof(s->the_loai)) {
						strcpy_s(s->the_loai, sizeof(s->the_loai), token);
					} else {
						strncpy_s(s->the_loai, sizeof(s->the_loai), token, sizeof(s->the_loai) - 1);
					}
					break;
				case 6: // gia_sach
					s->gia_sach = atol(token);
					break;
				case 7: // so_quyen
					s->so_quyen = atoi(token);
					break;
			}
			field++;
			token = strtok_s(NULL, "|", &context);
		}
		
		// Chỉ tăng nếu đọc đủ 8 trường
		if (field == 8) {
			so_luong_sach++;
		}
	}
	
	fclose(file);
	
	if (so_luong_sach == 0) {
		printf("File %s rong hoac loi dinh dang. Bat dau voi du lieu trong.\n", filename);
		return false;
	}
	
	printf("Da doc %d sach tu file %s\n", so_luong_sach, filename);
	return true;
}

/**
 * @brief Ghi dữ liệu sách vào file.
 * @param filename Tên file cần ghi
 * @return bool: true nếu ghi thành công, false nếu thất bại
 */
bool ghi_du_lieu_sach(const char* filename) {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filename, "w");
	
	if (err != 0 || file == NULL) {
		printf("Khong the mo file %s de ghi.\n", filename);
		return false;
	}
	
	for (int i = 0; i < so_luong_sach; i++) {
		Sach* s = &danh_sach_sach[i];
		fprintf(file, "%s|%s|%s|%s|%d|%s|%ld|%d\n",
			s->isbn, s->ten_sach, s->tac_gia, s->nxb,
			s->nam_xb, s->the_loai, s->gia_sach, s->so_quyen);
	}
	
	fclose(file);
	printf("Da ghi %d sach vao file %s\n", so_luong_sach, filename);
	return true;
}

/**
 * @brief Hàm tìm vị trí (index) của sách dựa trên ISBN.
 * @param isbn_can_tim Con trỏ trỏ tới chuỗi ISBN cần tìm.
 * @return int: Index nếu tìm thấy, -1 nếu không tìm thấy.
 */
int tim_vi_tri_sach(const char* isbn_can_tim) {
	for (int i = 0; i < so_luong_sach; i++) {
		if (strcmp(danh_sach_sach[i].isbn, isbn_can_tim) == 0) {
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

	printf("%-15s | %-20s | %-15s | %-20s | %-4s | %-10s | %s\n", "ISBN", "Ten Sach", "Tac Gia", "The Loai", "Nam", "Gia", "So Quyen");
	printf("--------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < so_luong_sach; i++) {
		Sach* s = &danh_sach_sach[i];
		printf("%-15s | %-20s | %-15s | %-20s | %-4d | %-10ld | %d\n",
			s->isbn, s->ten_sach, s->tac_gia, s->the_loai, 
			s->nam_xb, s->gia_sach, s->so_quyen);
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

	int i = so_luong_sach;
	Sach* s = &danh_sach_sach[i];

	strcpy_s(s->isbn, sizeof(s->isbn), isbn_moi);

	printf("Nhap Ten Sach: ");
	scanf_s(" %49[^\n]", s->ten_sach, (unsigned)sizeof(s->ten_sach));
	while (getchar() != '\n');

	printf("Nhap Tac Gia: ");
	scanf_s(" %49[^\n]", s->tac_gia, (unsigned)sizeof(s->tac_gia));
	while (getchar() != '\n');

	printf("Nhap Nha Xuat Ban: ");
	scanf_s(" %49[^\n]", s->nxb, (unsigned)sizeof(s->nxb));
	while (getchar() != '\n');

	int year = 0;
	int current_year = lay_nam_hien_tai();
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
			s->nam_xb = year;
			break;
		}
	} while (true);

	printf("Nhap The Loai: ");
	scanf_s(" %49[^\n]", s->the_loai, (unsigned)sizeof(s->the_loai));
	while (getchar() != '\n');

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
			s->gia_sach = price;
			break;
		}
	} while (true);

	int copies = 0;
	do {
		printf("Nhap So Quyen: ");
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
			s->so_quyen = copies;
			break;
		}
	} while (true);

	so_luong_sach++;
	printf("\nDa them sach %s thanh cong.\n", s->ten_sach);
	ghi_du_lieu_sach("sach.txt");
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

	Sach* s = &danh_sach_sach[index];
	printf("Tim thay sach: %s. Chon thong tin muon sua:\n", s->ten_sach);
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
	while (getchar() != '\n');

	switch (lua_chon) {
	case 1:
		printf("Nhap Ten Sach moi: ");
		scanf_s(" %49[^\n]", s->ten_sach, (unsigned)sizeof(s->ten_sach));
		while (getchar() != '\n');
		break;
	case 2:
		printf("Nhap Tac Gia moi: ");
		scanf_s(" %49[^\n]", s->tac_gia, (unsigned)sizeof(s->tac_gia));
		while (getchar() != '\n');
		break;
	case 3:
		printf("Nhap Nha Xuat Ban moi: ");
		scanf_s(" %49[^\n]", s->nxb, (unsigned)sizeof(s->nxb));
		while (getchar() != '\n');
		break;
	case 4:
	{
		int year = 0;
		int current_year = lay_nam_hien_tai();
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
				s->nam_xb = year;
				break;
			}
		} while (true);
	}
	break;
	case 5:
		printf("Nhap The Loai moi: ");
		scanf_s(" %49[^\n]", s->the_loai, (unsigned)sizeof(s->the_loai));
		while (getchar() != '\n');
		break;
	case 6:
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
				s->gia_sach = price;
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
				s->so_quyen = copies;
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
	ghi_du_lieu_sach("sach.txt");
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

	// Dịch chuyển các phần tử
	for (int i = vi_tri_xoa; i < so_luong_sach - 1; i++) {
		danh_sach_sach[i] = danh_sach_sach[i + 1];
	}

	so_luong_sach--;
	printf("Da xoa sach co ISBN: %s thanh cong.\n", isbn_can_xoa);
	ghi_du_lieu_sach("sach.txt");
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
		Sach* s = &danh_sach_sach[index];
		printf("Tim thay sach:\n");
		printf(" ISBN: %s\n", s->isbn);
		printf(" Ten Sach: %s\n", s->ten_sach);
		printf(" Tac Gia: %s\n", s->tac_gia);
		printf(" Nha Xuat Ban: %s\n", s->nxb);
		printf(" Nam Xuat Ban: %d\n", s->nam_xb);
		printf(" The Loai: %s\n", s->the_loai);
		printf(" Gia Sach: %ld VND\n", s->gia_sach);
		printf(" So Quyen: %d\n", s->so_quyen);
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
		Sach* s = &danh_sach_sach[i];
		if (strstr(s->ten_sach, ten_sach_can_tim) != NULL) {
			printf("%-15s | %-20s | %-15s | %-20s | %-4d | %-10ld\n",
				s->isbn, s->ten_sach, s->tac_gia, s->the_loai, 
				s->nam_xb, s->gia_sach);
			tim_thay = true;
		}
	}

	if (!tim_thay) {
		printf("Khong tim thay sach voi Ten Sach: %s\n", ten_sach_can_tim);
	}
	printf("----------------------------------------------------------------------\n");
}