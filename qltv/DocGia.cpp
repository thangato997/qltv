#include "DocGia.h"
#include "Helper.h"
#include "PhieuMuon.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctype.h>

// Định nghĩa mảng toàn cục sử dụng struct
DocGia danh_sach_doc_gia[MAX_DOC_GIA];
int so_luong_doc_gia = 0;

/**
 * @brief Đọc dữ liệu độc giả từ file.
 * @param filename Tên file cần đọc
 * @return bool: true nếu đọc thành công, false nếu thất bại
 */
bool doc_du_lieu_doc_gia(const char* filename) {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filename, "r");
	
	if (err != 0 || file == NULL) {
		printf("Khong the mo file %s de doc. Bat dau voi du lieu trong.\n", filename);
		return false;
	}
	
	so_luong_doc_gia = 0;
	char line[512];
	
	while (so_luong_doc_gia < MAX_DOC_GIA && fgets(line, sizeof(line), file) != NULL) {
		// Loại bỏ newline ở cuối
		line[strcspn(line, "\r\n")] = '\0';
		
		// Bỏ qua dòng trống
		if (strlen(line) == 0) continue;
		
		DocGia* dg = &danh_sach_doc_gia[so_luong_doc_gia];
		
		// Parse dòng theo format: ma|ho_ten|cmnd|ngay_sinh|gioi_tinh|email|dia_chi|ngay_lap|ngay_het_han
		char* token = NULL;
		char* context = NULL;
		int field = 0;
		
		token = strtok_s(line, "|", &context);
		while (token != NULL && field < 9) {
			size_t token_len = strlen(token);
			
			switch (field) {
				case 0: // ma_doc_gia
					if (token_len < sizeof(dg->ma_doc_gia)) {
						strcpy_s(dg->ma_doc_gia, sizeof(dg->ma_doc_gia), token);
					} else {
						strncpy_s(dg->ma_doc_gia, sizeof(dg->ma_doc_gia), token, sizeof(dg->ma_doc_gia) - 1);
					}
					break;
				case 1: // ho_ten
					if (token_len < sizeof(dg->ho_ten)) {
						strcpy_s(dg->ho_ten, sizeof(dg->ho_ten), token);
					} else {
						strncpy_s(dg->ho_ten, sizeof(dg->ho_ten), token, sizeof(dg->ho_ten) - 1);
					}
					break;
				case 2: // cmnd
					if (token_len < sizeof(dg->cmnd)) {
						strcpy_s(dg->cmnd, sizeof(dg->cmnd), token);
					} else {
						strncpy_s(dg->cmnd, sizeof(dg->cmnd), token, sizeof(dg->cmnd) - 1);
					}
					break;
				case 3: // ngay_sinh
					if (token_len < sizeof(dg->ngay_sinh)) {
						strcpy_s(dg->ngay_sinh, sizeof(dg->ngay_sinh), token);
					} else {
						strncpy_s(dg->ngay_sinh, sizeof(dg->ngay_sinh), token, sizeof(dg->ngay_sinh) - 1);
					}
					break;
				case 4: // gioi_tinh
					if (token_len < sizeof(dg->gioi_tinh)) {
						strcpy_s(dg->gioi_tinh, sizeof(dg->gioi_tinh), token);
					} else {
						strncpy_s(dg->gioi_tinh, sizeof(dg->gioi_tinh), token, sizeof(dg->gioi_tinh) - 1);
					}
					break;
				case 5: // email
					if (token_len < sizeof(dg->email)) {
						strcpy_s(dg->email, sizeof(dg->email), token);
					} else {
						strncpy_s(dg->email, sizeof(dg->email), token, sizeof(dg->email) - 1);
					}
					break;
				case 6: // dia_chi
					if (token_len < sizeof(dg->dia_chi)) {
						strcpy_s(dg->dia_chi, sizeof(dg->dia_chi), token);
					} else {
						strncpy_s(dg->dia_chi, sizeof(dg->dia_chi), token, sizeof(dg->dia_chi) - 1);
					}
					break;
				case 7: // ngay_lap_the
					if (token_len < sizeof(dg->ngay_lap_the)) {
						strcpy_s(dg->ngay_lap_the, sizeof(dg->ngay_lap_the), token);
					} else {
						strncpy_s(dg->ngay_lap_the, sizeof(dg->ngay_lap_the), token, sizeof(dg->ngay_lap_the) - 1);
					}
					break;
				case 8: // ngay_het_han
					if (token_len < sizeof(dg->ngay_het_han)) {
						strcpy_s(dg->ngay_het_han, sizeof(dg->ngay_het_han), token);
					} else {
						strncpy_s(dg->ngay_het_han, sizeof(dg->ngay_het_han), token, sizeof(dg->ngay_het_han) - 1);
					}
					break;
			}
			field++;
			token = strtok_s(NULL, "|", &context);
		}
		
		// Chỉ tăng nếu đọc đủ 9 trường
		if (field == 9) {
			so_luong_doc_gia++;
		}
	}
	
	fclose(file);
	
	if (so_luong_doc_gia == 0) {
		printf("File %s rong hoac loi dinh dang. Bat dau voi du lieu trong.\n", filename);
		return false;
	}
	
	printf("Da doc %d doc gia tu file %s\n", so_luong_doc_gia, filename);
	return true;
}

/**
 * @brief Ghi dữ liệu độc giả vào file.
 * @param filename Tên file cần ghi
 * @return bool: true nếu ghi thành công, false nếu thất bại
 */
bool ghi_du_lieu_doc_gia(const char* filename) {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filename, "w");
	
	if (err != 0 || file == NULL) {
		printf("Khong the mo file %s de ghi.\n", filename);
		return false;
	}
	
	for (int i = 0; i < so_luong_doc_gia; i++) {
		DocGia* dg = &danh_sach_doc_gia[i];
		fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
			dg->ma_doc_gia, dg->ho_ten, dg->cmnd, dg->ngay_sinh,
			dg->gioi_tinh, dg->email, dg->dia_chi,
			dg->ngay_lap_the, dg->ngay_het_han);
	}
	
	fclose(file);
	printf("Da ghi %d doc gia vao file %s\n", so_luong_doc_gia, filename);
	return true;
}

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

	printf("%-6s | %-20s | %-12s | %-11s | %-5s | %-18s | %-11s | %-11s\n",
		"Ma DG", "Ho Ten", "CMND", "Ngay Sinh", "GTinh", "Email", "Ngay Lap", "Ngay Het Han");
	printf("--------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < so_luong_doc_gia; i++) {
		DocGia* dg = &danh_sach_doc_gia[i];
		printf("%-6s | %-20s | %-12s | %-11s | %-5s | %-18s | %-11s | %-11s\n",
			dg->ma_doc_gia, dg->ho_ten, dg->cmnd, dg->ngay_sinh, dg->gioi_tinh,
			dg->email, dg->ngay_lap_the, dg->ngay_het_han);
	}
	printf("--------------------------------------------------------------------------------------------------------------\n");
}

int tim_vi_tri_doc_gia(const char* cmnd_can_tim) {
	if (cmnd_can_tim == NULL) return -1;
	for (int i = 0; i < so_luong_doc_gia; i++) {
		if (strcmp(danh_sach_doc_gia[i].cmnd, cmnd_can_tim) == 0) return i;
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
		cmnd_moi[sizeof(cmnd_moi) - 1] = '\0';
		if (strcmp(cmnd_moi, "0") == 0) {
			while (getchar() != '\n' && !feof(stdin));
			return;
		}
		while (getchar() != '\n');
		if (tim_vi_tri_doc_gia(cmnd_moi) == -1) {
			break;
		}
		printf("Doc gia voi CMND %s da ton tai vui long nhap lai (nhap 0 de thoat).\n", cmnd_moi);
	}

	int i = so_luong_doc_gia;
	DocGia* dg = &danh_sach_doc_gia[i];

	strcpy_s(dg->cmnd, sizeof(dg->cmnd), cmnd_moi);
	sprintf_s(dg->ma_doc_gia, sizeof(dg->ma_doc_gia), "DG%03d", i + 1);
	printf("Ma Doc Gia (Tu dong tao): %s\n", dg->ma_doc_gia);

	printf("Nhap Ho Ten: ");
	scanf_s(" %49[^\n]", dg->ho_ten, (unsigned)sizeof(dg->ho_ten));
	while (getchar() != '\n');

	do {
		printf("Nhap Ngay Sinh (DD/MM/YYYY): ");
		scanf_s("%10s", dg->ngay_sinh, (unsigned)sizeof(dg->ngay_sinh));
		while (getchar() != '\n');
		if (!kiem_tra_ngay(dg->ngay_sinh)) {
			printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
		}
		else break;
	} while (true);

	printf("Nhap Gioi Tinh (Nam/Nu): ");
	scanf_s("%4s", dg->gioi_tinh, (unsigned)sizeof(dg->gioi_tinh));
	while (getchar() != '\n');

	printf("Nhap Email: ");
	scanf_s("%49s", dg->email, (unsigned)sizeof(dg->email));
	while (getchar() != '\n');

	printf("Nhap Dia Chi: ");
	scanf_s(" %49[^\n]", dg->dia_chi, (unsigned)sizeof(dg->dia_chi));
	while (getchar() != '\n');

	char lua_chon_ngay;
	printf("Su dung ngay hien tai cho Ngay Lap The? (Y/N): ");
	scanf_s(" %c", &lua_chon_ngay, 1);
	while (getchar() != '\n');

	if (lua_chon_ngay == 'Y' || lua_chon_ngay == 'y') {
		lay_ngay_hien_tai(dg->ngay_lap_the, sizeof(dg->ngay_lap_the));
		printf("Ngay Lap The (Tu dong): %s\n", dg->ngay_lap_the);
	}
	else {
		do {
			printf("Nhap Ngay Lap The (DD/MM/YYYY): ");
			scanf_s("%10s", dg->ngay_lap_the, (unsigned)sizeof(dg->ngay_lap_the));
			while (getchar() != '\n');
			if (!kiem_tra_ngay(dg->ngay_lap_the)) {
				printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
			}
			else break;
		} while (true);
	}

	tinh_ngay_het_han(dg->ngay_lap_the, dg->ngay_het_han, sizeof(dg->ngay_het_han));
	printf("Ngay Het Han (Tu dong tinh): %s\n", dg->ngay_het_han);

	so_luong_doc_gia++;
	printf("\nDa them doc gia %s thanh cong.\n", dg->ho_ten);
	
	// Tự động lưu vào file
	ghi_du_lieu_doc_gia("docgia.txt");
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
	while (getchar() != '\n');

	int index = tim_vi_tri_doc_gia(cmnd_can_sua);

	if (index == -1) {
		printf("Khong tim thay doc gia voi CMND: %s\n", cmnd_can_sua);
		return;
	}

	DocGia* dg = &danh_sach_doc_gia[index];
	printf("Tim thay doc gia: %s (Ma: %s). Ban co the sua nhieu thong tin. Nhap 'S' de luu va thoat.\n", 
		dg->ho_ten, dg->ma_doc_gia);

	DocGia temp = *dg; // Tạo bản sao tạm
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

		if (scanf_s(" %7s", choice, (unsigned)sizeof(choice)) != 1) {
			while (getchar() != '\n');
			printf("Lua chon khong hop le.\n");
			continue;
		}
		while (getchar() != '\n');

		if (choice[0] == 'S' || choice[0] == 's') {
			saved = true;
			printf("--> Luu thay doi va thoat.\n");
			break;
		}

		lua_chon = atoi(choice);

		switch (lua_chon) {
		case 1:
			printf("Nhap Ho Ten moi: ");
			scanf_s(" %49[^\n]", temp.ho_ten, (unsigned)sizeof(temp.ho_ten));
			while (getchar() != '\n');
			break;
		case 2:
			do {
				printf("Nhap Ngay Sinh moi (DD/MM/YYYY): ");
				scanf_s("%10s", temp.ngay_sinh, (unsigned)sizeof(temp.ngay_sinh));
				while (getchar() != '\n');
				if (!kiem_tra_ngay(temp.ngay_sinh)) {
					printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
				}
				else break;
			} while (true);
			break;
		case 3:
			printf("Nhap Gioi Tinh moi: ");
			scanf_s("%4s", temp.gioi_tinh, (unsigned)sizeof(temp.gioi_tinh));
			while (getchar() != '\n');
			break;
		case 4:
			printf("Nhap Email moi: ");
			scanf_s("%49s", temp.email, (unsigned)sizeof(temp.email));
			while (getchar() != '\n');
			break;
		case 5:
			printf("Nhap Dia Chi moi: ");
			scanf_s(" %49[^\n]", temp.dia_chi, (unsigned)sizeof(temp.dia_chi));
			while (getchar() != '\n');
			break;
		case 6:
			do {
				printf("Nhap Ngay Lap The moi (DD/MM/YYYY): ");
				scanf_s("%10s", temp.ngay_lap_the, (unsigned)sizeof(temp.ngay_lap_the));
				while (getchar() != '\n');
				if (!kiem_tra_ngay(temp.ngay_lap_the)) {
					printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
				}
				else break;
			} while (true);
			tinh_ngay_het_han(temp.ngay_lap_the, temp.ngay_het_han, sizeof(temp.ngay_het_han));
			printf("Ngay Het Han (tam) da duoc cap nhat thanh: %s\n", temp.ngay_het_han);
			break;
		case 0:
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
		*dg = temp; // Lưu bản sao vào struct chính
		printf("\nDa cap nhat thong tin cho doc gia co CMND: %s\n", cmnd_can_sua);
		ghi_du_lieu_doc_gia("docgia.txt");
	}
	else if (cancelled) {
		printf("\nDa huy bo cac thay doi cho doc gia co CMND: %s\n", cmnd_can_sua);
	}
}

/**
 * @brief Xóa thông tin một độc giả (Chức năng 1d).
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

	// Dịch chuyển các phần tử
	for (int i = vi_tri_xoa; i < so_luong_doc_gia - 1; i++) {
		danh_sach_doc_gia[i] = danh_sach_doc_gia[i + 1];
	}

	so_luong_doc_gia--;
	printf("Da xoa doc gia co CMND: %s thanh cong.\n", cmnd_can_xoa);
	ghi_du_lieu_doc_gia("docgia.txt");
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
		DocGia* dg = &danh_sach_doc_gia[index];
		printf("Tim thay doc gia:\n");
		printf(" Ma Doc Gia: %s\n", dg->ma_doc_gia);
		printf(" Ho Ten: %s\n", dg->ho_ten);
		printf(" CMND: %s\n", dg->cmnd);
		printf(" Ngay Sinh: %s\n", dg->ngay_sinh);
		printf(" Gioi Tinh: %s\n", dg->gioi_tinh);
		printf(" Email: %s\n", dg->email);
		printf(" Dia Chi: %s\n", dg->dia_chi);
		printf(" Ngay Lap The: %s\n", dg->ngay_lap_the);
		printf(" Ngay Het Han: %s\n", dg->ngay_het_han);
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
		while (getchar() != '\n');
		return;
	}
	while (getchar() != '\n');

	printf("\n%-6s | %-20s | %-12s | %-11s | %-5s | %-18s | %-11s | %-11s\n",
		"Ma DG", "Ho Ten", "CMND", "Ngay Sinh", "GTinh", "Email", "Ngay Lap", "Ngay Het Han");
	printf("--------------------------------------------------------------------------------------------------------------\n");

	bool tim_thay = false;
	for (int i = 0; i < so_luong_doc_gia; i++) {
		DocGia* dg = &danh_sach_doc_gia[i];
		char* s1 = chuyen_sang_chu_thuong(dg->ho_ten);
		char* s2 = chuyen_sang_chu_thuong(ho_ten_can_tim);
		if (s1 != NULL && s2 != NULL && strstr(s1, s2) != NULL) {
			printf("%-6s | %-20s | %-12s | %-11s | %-5s | %-18s | %-11s | %-11s\n",
				dg->ma_doc_gia, dg->ho_ten, dg->cmnd, dg->ngay_sinh, dg->gioi_tinh,
				dg->email, dg->ngay_lap_the, dg->ngay_het_han);
			tim_thay = true;
		}
		free(s1);
		free(s2);
	}

	if (!tim_thay) {
		printf("Khong tim thay doc gia nao co Ho Ten chua: %s\n", ho_ten_can_tim);
	}
	printf("--------------------------------------------------------------------------------------------------------------\n");
}