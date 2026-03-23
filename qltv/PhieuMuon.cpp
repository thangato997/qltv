#include "PhieuMuon.h"
#include "DocGia.h"
#include "Sach.h"
#include "Helper.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

// Định nghĩa mảng toàn cục
PhieuMuon danh_sach_phieu[MAX_PHIEU];
int so_luong_phieu = 0;

// Khai báo extern cho mảng sách
extern Sach danh_sach_sach[MAX_SACH];
extern int so_luong_sach;

// Khai báo extern cho mảng độc giả  
extern DocGia danh_sach_doc_gia[MAX_DOC_GIA];
extern int so_luong_doc_gia;

/**
 * @brief Đọc dữ liệu phiếu mượn từ file.
 * @param filename Tên file cần đọc
 * @return bool: true nếu đọc thành công, false nếu thất bại
 */
bool doc_du_lieu_phieu(const char* filename) {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filename, "r");
	
	if (err != 0 || file == NULL) {
		printf("Khong the mo file %s de doc. Bat dau voi du lieu trong.\n", filename);
		return false;
	}
	
	so_luong_phieu = 0;
	char line[512];
	
	while (so_luong_phieu < MAX_PHIEU && fgets(line, sizeof(line), file) != NULL) {
		// Loại bỏ newline ở cuối
		line[strcspn(line, "\r\n")] = '\0';
		
		// Bỏ qua dòng trống
		if (strlen(line) == 0) continue;
		
		PhieuMuon* p = &danh_sach_phieu[so_luong_phieu];
		
		// Parse dòng thông tin phiếu: ma_phieu|ma_doc_gia|ngay_muon|ngay_tra_du_kien|ngay_tra_thuc_te|da_tra|so_sach
		char* token = NULL;
		char* context = NULL;
		int field = 0;
		
		token = strtok_s(line, "|", &context);
		while (token != NULL && field < 7) {
			size_t token_len = strlen(token);
			
			switch (field) {
				case 0: // ma_phieu
					if (token_len < sizeof(p->ma_phieu)) {
						strcpy_s(p->ma_phieu, sizeof(p->ma_phieu), token);
					} else {
						strncpy_s(p->ma_phieu, sizeof(p->ma_phieu), token, sizeof(p->ma_phieu) - 1);
					}
					break;
				case 1: // ma_doc_gia
					if (token_len < sizeof(p->ma_doc_gia)) {
						strcpy_s(p->ma_doc_gia, sizeof(p->ma_doc_gia), token);
					} else {
						strncpy_s(p->ma_doc_gia, sizeof(p->ma_doc_gia), token, sizeof(p->ma_doc_gia) - 1);
					}
					break;
				case 2: // ngay_muon
					if (token_len < sizeof(p->ngay_muon)) {
						strcpy_s(p->ngay_muon, sizeof(p->ngay_muon), token);
					} else {
						strncpy_s(p->ngay_muon, sizeof(p->ngay_muon), token, sizeof(p->ngay_muon) - 1);
					}
					break;
				case 3: // ngay_tra_du_kien
					if (token_len < sizeof(p->ngay_tra_du_kien)) {
						strcpy_s(p->ngay_tra_du_kien, sizeof(p->ngay_tra_du_kien), token);
					} else {
						strncpy_s(p->ngay_tra_du_kien, sizeof(p->ngay_tra_du_kien), token, sizeof(p->ngay_tra_du_kien) - 1);
					}
					break;
				case 4: // ngay_tra_thuc_te
					if (token_len < sizeof(p->ngay_tra_thuc_te)) {
						strcpy_s(p->ngay_tra_thuc_te, sizeof(p->ngay_tra_thuc_te), token);
					} else {
						strncpy_s(p->ngay_tra_thuc_te, sizeof(p->ngay_tra_thuc_te), token, sizeof(p->ngay_tra_thuc_te) - 1);
					}
					break;
				case 5: // da_tra
					p->da_tra = (atoi(token) != 0) ? 1 : 0;
					break;
				case 6: // so_sach_muon
					{
						int n = atoi(token);
						if (n < 0) n = 0;
						if (n > MAX_SACH_MUON) n = MAX_SACH_MUON;
						p->so_sach_muon = n;
					}
					break;
			}
			field++;
			token = strtok_s(NULL, "|", &context);
		}
		
		// Nếu không đọc đủ 7 trường, bỏ qua dòng này
		if (field != 7) continue;
		
		// Đọc danh sách sách (mỗi sách 1 dòng)
		for (int i = 0; i < p->so_sach_muon && i < MAX_SACH_MUON; i++) {
			if (fgets(line, sizeof(line), file) == NULL) break;
			
			// Loại bỏ newline
			line[strcspn(line, "\r\n")] = '\0';
			
			// Parse: isbn|bi_mat
			token = strtok_s(line, "|", &context);
			if (token != NULL) {
				size_t token_len = strlen(token);
				if (token_len < sizeof(p->sach_muon[i].isbn)) {
					strcpy_s(p->sach_muon[i].isbn, sizeof(p->sach_muon[i].isbn), token);
				} else {
					strncpy_s(p->sach_muon[i].isbn, sizeof(p->sach_muon[i].isbn), token, sizeof(p->sach_muon[i].isbn) - 1);
				}
				
				token = strtok_s(NULL, "|", &context);
				if (token != NULL) {
					p->sach_muon[i].bi_mat = atoi(token);
				} else {
					p->sach_muon[i].bi_mat = 0;
				}
			}
		}
		
		so_luong_phieu++;
	}
	
	fclose(file);
	
	if (so_luong_phieu == 0) {
		printf("File %s rong hoac loi dinh dang. Bat dau voi du lieu trong.\n", filename);
		return false;
	}
	
	printf("Da doc %d phieu muon tu file %s\n", so_luong_phieu, filename);
	return true;
}

/**
 * @brief Ghi dữ liệu phiếu mượn vào file.
 * @param filename Tên file cần ghi
 * @return bool: true nếu ghi thành công, false nếu thất bại
 */
bool ghi_du_lieu_phieu(const char* filename) {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filename, "w");
	
	if (err != 0 || file == NULL) {
		printf("Khong the mo file %s de ghi.\n", filename);
		return false;
	}
	
	for (int i = 0; i < so_luong_phieu; i++) {
		PhieuMuon* p = &danh_sach_phieu[i];
		
		// Ghi thông tin phiếu
		fprintf(file, "%s|%s|%s|%s|%s|%d|%d\n",
			p->ma_phieu, p->ma_doc_gia, p->ngay_muon,
			p->ngay_tra_du_kien, p->ngay_tra_thuc_te,
			p->da_tra, p->so_sach_muon);
		
		// Ghi danh sách sách
		for (int j = 0; j < p->so_sach_muon; j++) {
			fprintf(file, "%s|%d\n",
				p->sach_muon[j].isbn,
				p->sach_muon[j].bi_mat);
		}
	}
	
	fclose(file);
	printf("Da ghi %d phieu muon vao file %s\n", so_luong_phieu, filename);
	return true;
}

/**
 * @brief Lập phiếu mượn sách (Chức năng3).
 */
void lap_phieu_muon() {
	if (so_luong_phieu >= MAX_PHIEU) {
		printf("He thong phieu muon da day.\n");
		return;
	}

	int max_can_tao = MAX_PHIEU - so_luong_phieu;
	int so_phieu_muon = 0;
	printf("\nNhap so phieu muon can lap (toi da %d): ", max_can_tao);
	if (scanf_s("%d", &so_phieu_muon) != 1) {
		while (getchar() != '\n');
		printf("Nhap khong hop le. Huy bo.\n");
		return;
	}
	while (getchar() != '\n');

	if (so_phieu_muon <= 0 || so_phieu_muon > max_can_tao) {
		printf("So phieu muon phai tu1 den %d. Huy bo.\n", max_can_tao);
		return;
	}

	for (int p = 0; p < so_phieu_muon; p++) {
		printf("\n--- LAP PHIEU MUON THU %d/%d ---\n", p + 1, so_phieu_muon);

		char ma_dg_temp[10] = { 0 };
		printf("Nhap Ma Doc Gia: ");
		if (scanf_s("%9s", ma_dg_temp, (unsigned)sizeof(ma_dg_temp)) != 1) {
			while (getchar() != '\n');
			printf("Nhap khong hop le. Bo qua phieu nay.\n");
			continue;
		}
		while (getchar() != '\n');

		// Tìm độc giả theo mã
		int vi_tri_doc_gia = -1;
		for (int i = 0; i < so_luong_doc_gia; i++) {
			if (strcmp(danh_sach_doc_gia[i].ma_doc_gia, ma_dg_temp) == 0) {
				vi_tri_doc_gia = i;
				break;
			}
		}

		if (vi_tri_doc_gia == -1) {
			printf("Khong tim thay Doc Gia voi Ma: %s. Bo qua phieu nay.\n", ma_dg_temp);
			continue;
		}

		int index_phieu = so_luong_phieu;
		PhieuMuon* phieu = &danh_sach_phieu[index_phieu];
		
		// Tạo mã phiếu tự động
		sprintf_s(phieu->ma_phieu, sizeof(phieu->ma_phieu), "PM%03d", index_phieu + 1);
		strcpy_s(phieu->ma_doc_gia, sizeof(phieu->ma_doc_gia), ma_dg_temp);

		// Ngày mượn (DD/MM/YYYY) với xác thực
		do {
			printf("Nhap Ngay Muon (DD/MM/YYYY): ");
			if (scanf_s("%10s", phieu->ngay_muon, (unsigned)sizeof(phieu->ngay_muon)) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (!kiem_tra_ngay(phieu->ngay_muon)) {
				printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
			}
			else break;
		} while (true);

		// Ngày trả dự kiến (DD/MM/YYYY) với xác thực
		do {
			printf("Nhap Ngay Tra Du Kien (DD/MM/YYYY): ");
			if (scanf_s("%10s", phieu->ngay_tra_du_kien, (unsigned)sizeof(phieu->ngay_tra_du_kien)) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (!kiem_tra_ngay(phieu->ngay_tra_du_kien)) {
				printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
			}
			else break;
		} while (true);

		// Nhập danh sách sách mượn
		int num_to_borrow = 0;
		do {
			printf("Nhap so luong sach muon (1-%d): ", MAX_SACH_MUON);
			if (scanf_s("%d", &num_to_borrow) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (num_to_borrow <1 || num_to_borrow > MAX_SACH_MUON) {
				printf("So luong phai tu1 den %d. Vui long nhap lai.\n", MAX_SACH_MUON);
			}
			else break;
		} while (true);

		int so_sach_da_them = 0;
		for (int j = 0; j < num_to_borrow; j++) {
			char isbn_temp[15] = { 0 };
			printf("ISBN %d: ", j + 1);
			if (scanf_s("%14s", isbn_temp, (unsigned)sizeof(isbn_temp)) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				j--;
				continue;
			}
			while (getchar() != '\n');

			if (strcmp(isbn_temp, "0") == 0) {
				printf("Khong duoc nhap '0' khi da chon so luong. Vui long nhap lai.\n");
				j--;
				continue;
			}

			int vi_tri_sach = tim_vi_tri_sach(isbn_temp);
			if (vi_tri_sach == -1) {
				printf("Sach voi ISBN %s khong ton tai. Vui long nhap lai.\n", isbn_temp);
				j--;
				continue;
			}

			if (danh_sach_sach[vi_tri_sach].so_quyen <= 0) {
				printf("Sach '%s' hien da het. Khong the muon. Vui long chon sach khac.\n", 
					danh_sach_sach[vi_tri_sach].ten_sach);
				j--;
				continue;
			}

			strcpy_s(phieu->sach_muon[so_sach_da_them].isbn, isbn_temp);
			phieu->sach_muon[so_sach_da_them].bi_mat = 0;
			so_sach_da_them++;

			// Cập nhật số lượng sách
			danh_sach_sach[vi_tri_sach].so_quyen--;
			printf("Da them sach '%s' vao phieu. Con lai: %d quyen.\n", 
				danh_sach_sach[vi_tri_sach].ten_sach, danh_sach_sach[vi_tri_sach].so_quyen);
		}

		if (so_sach_da_them == 0) {
			printf("Khong co sach nao duoc them vao phieu. Huy phieu nay.\n");
			continue;
		}

		phieu->so_sach_muon = so_sach_da_them;
		strcpy_s(phieu->ngay_tra_thuc_te, "");
		phieu->da_tra = 0;
		so_luong_phieu++;

		printf("\nLap Phieu Muon %s thanh cong cho Doc Gia %s voi %d cuon sach.\n",
			phieu->ma_phieu, ma_dg_temp, so_sach_da_them);
	}
	
	ghi_du_lieu_phieu("phieumuon.txt");
	ghi_du_lieu_sach("sach.txt");
}

void lap_phieu_tra() {
	char ma_phieu_temp[10] = { 0 };
	printf("\n--- LAP PHIEU TRA SACH ---\n");
	printf("Nhap Ma Phieu Muon can tra: ");
	scanf_s("%9s", ma_phieu_temp, (unsigned)sizeof(ma_phieu_temp));
	while (getchar() != '\n');

	// B1: Tìm phiếu
	int index_phieu = -1;
	for (int i = 0; i < so_luong_phieu; i++) {
		if (strcmp(danh_sach_phieu[i].ma_phieu, ma_phieu_temp) == 0) {
			index_phieu = i;
			break;
		}
	}

	if (index_phieu == -1) {
		printf("Khong tim thay Ma Phieu Muon: %s\n", ma_phieu_temp);
		return;
	}

	PhieuMuon* phieu = &danh_sach_phieu[index_phieu];

	if (phieu->da_tra == 1) {
		printf("Phieu Muon %s da duoc tra truoc do.\n", ma_phieu_temp);
		return;
	}

	char ngay_tra_tt[11] = { 0 };
	// Ngày trả thực tế (DD/MM/YYYY) với xác thực
	do {
		char ngay_hien_tai[11];
		lay_ngay_hien_tai(ngay_hien_tai, sizeof(ngay_hien_tai));

		printf("Nhap Ngay Tra Thuc Te (DD/MM/YYYY): ");
		scanf_s("%10s", ngay_tra_tt, (unsigned)sizeof(ngay_tra_tt));
		while (getchar() != '\n');
		if (!kiem_tra_ngay(ngay_tra_tt)) {
			printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
			continue;
		}
		if (so_sanh_ngay(ngay_tra_tt, phieu->ngay_muon) < 0) {
			printf("Ngay tra phai khong nho hon ngay muon (%s). Vui long nhap lai.\n", phieu->ngay_muon);
			continue;
		}
		if (so_sanh_ngay(ngay_tra_tt, ngay_hien_tai) > 0) {
			printf("Ngay tra phai khong lon hon ngay hien tai (%s). Vui long nhap lai.\n", ngay_hien_tai);
			continue;
		}
		break;
	} while (true);

	// B2: Kiểm tra sách bị mất
	printf("\n--- KIEM TRA SACH BI MAT ---\n");
	for (int i = 0; i < phieu->so_sach_muon; i++) {
		int vi_tri_sach = tim_vi_tri_sach(phieu->sach_muon[i].isbn);
		
		if (vi_tri_sach != -1) {
			printf("Sach %d: %s (%s)\n", i + 1, phieu->sach_muon[i].isbn, 
				danh_sach_sach[vi_tri_sach].ten_sach);
			printf("Sach nay co bi mat khong? (1=Co, 0=Khong): ");
			int bi_mat = 0;
			if (scanf_s("%d", &bi_mat) != 1) {
				while (getchar() != '\n');
				bi_mat = 0;
			}
			while (getchar() != '\n');
			phieu->sach_muon[i].bi_mat = (bi_mat ? 1 : 0);
		}
	}

	// B3: Xử lý trả sách
	strcpy_s(phieu->ngay_tra_thuc_te, ngay_tra_tt);
	phieu->da_tra = 1;

	printf("\nDa cap nhat phieu tra %s.\n", ma_phieu_temp);

	// B4: Cập nhật số lượng sách và tính phạt
	long tong_tien_phat = 0;
	long so_ngay_tre = tinh_so_ngay_tre_han(ngay_tra_tt, phieu->ngay_tra_du_kien);

	// Tính phạt trễ hạn (5000 VND/ngày theo đề bài)
	if (so_ngay_tre > 0) {
		long tien_phat_tre = so_ngay_tre * 5000 * phieu->so_sach_muon;
		tong_tien_phat += tien_phat_tre;
		printf("TRE HAN: Ngay tra du kien la %s. Tre %ld ngay.\n", phieu->ngay_tra_du_kien, so_ngay_tre);
		printf("TIEN PHAT TRE HAN: %ld VND (5,000 VND/ngay x %ld ngay x %d sach).\n", 
			tien_phat_tre, so_ngay_tre, phieu->so_sach_muon);
	}
	else {
		printf("SACH DUOC TRA DUNG HAN/SOM HAN.\n");
	}

	// Tính phạt sách mất (200% giá sách theo đề bài)
	long tien_phat_mat = 0;
	for (int i = 0; i < phieu->so_sach_muon; i++) {
		if (phieu->sach_muon[i].bi_mat == 1) {
			int vi_tri_sach = tim_vi_tri_sach(phieu->sach_muon[i].isbn);
			
			if (vi_tri_sach != -1) {
				long phat_sach_nay = danh_sach_sach[vi_tri_sach].gia_sach * 2;
				tien_phat_mat += phat_sach_nay;
				printf("SACH BI MAT: %s - Gia: %ld VND - Phat: %ld VND (200%%)\n", 
					danh_sach_sach[vi_tri_sach].ten_sach, 
					danh_sach_sach[vi_tri_sach].gia_sach, phat_sach_nay);
			}
		}
	}
	
	if (tien_phat_mat > 0) {
		tong_tien_phat += tien_phat_mat;
		printf("TONG TIEN PHAT SACH MAT: %ld VND\n", tien_phat_mat);
	}

	if (tong_tien_phat > 0) {
		printf("\n==> TONG TIEN PHAT: %ld VND\n", tong_tien_phat);
	} else {
		printf("\n==> Khong co phat.\n");
	}

	// Tăng lại số lượng sách đã trả (chỉ những sách không bị mất)
	for (int i = 0; i < phieu->so_sach_muon; i++) {
		if (phieu->sach_muon[i].bi_mat == 0) {
			int vi_tri_sach = tim_vi_tri_sach(phieu->sach_muon[i].isbn);
			if (vi_tri_sach != -1) {
				danh_sach_sach[vi_tri_sach].so_quyen++;
			}
		}
	}

	printf("\nDa hoan tat qua trinh tra sach va cap nhat so luong trong kho.\n");
	ghi_du_lieu_phieu("phieumuon.txt");
	ghi_du_lieu_sach("sach.txt");
}

void xem_danh_sach_phieu_muon() {
	printf("\n--- DANH SACH PHIEU MUON ---\n");
	if (so_luong_phieu == 0) {
		printf("Hien khong co phieu muon nao.\n");
		return;
	}

	printf("%-6s | %-6s | %-11s | %-11s | %-5s | %-11s | %-8s | %s\n",
		"MaP", "MaDG", "NgayMuon", "NgayDuKien", "Tra?", "NgayTraTT", "SoSach", "ISBNs");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < so_luong_phieu; i++) {
		PhieuMuon* p = &danh_sach_phieu[i];
		
		/* Per entry: up to 14 ISBN chars + 2-char ", " separator; one extra byte for null terminator */
		char isbns[(sizeof(p->sach_muon[0].isbn) - 1 + 2) * MAX_SACH_MUON + 1] = "";
		for (int j = 0; j < p->so_sach_muon; j++) {
			if (j > 0) {
				strcat_s(isbns, sizeof(isbns), ", ");
			}
			strcat_s(isbns, sizeof(isbns), p->sach_muon[j].isbn);
		}

		printf("%-6s | %-6s | %-11s | %-11s | %-5s | %-11s | %-8d | %s\n",
			p->ma_phieu, p->ma_doc_gia, p->ngay_muon, p->ngay_tra_du_kien,
			p->da_tra ? "Yes" : "No", 
			p->ngay_tra_thuc_te[0] ? p->ngay_tra_thuc_te : "-",
			p->so_sach_muon, isbns);
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");
}
