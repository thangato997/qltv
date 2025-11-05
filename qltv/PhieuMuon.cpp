#include "PhieuMuon.h"
#include "DocGia.h" // Cần thiết để kiểm tra DG
#include "Sach.h" // Cần thiết để kiểm tra và cập nhật sách
#include "Helper.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

// Định nghĩa các mảng 1 chiều
char ma_phieu_arr[MAX_PHIEU][10] = {
 "PM001",
 "PM002",
 "PM003"
};
char ma_doc_gia_phieu_arr[MAX_PHIEU][10] = {
 "DG001",
 "DG002",
 "DG003"
};
char ngay_muon_arr[MAX_PHIEU][11] = {
 "01/10/2025",
 "20/09/2025",
 "10/10/2025"
};
char ngay_tra_du_kien_arr[MAX_PHIEU][11] = {
 "15/10/2025",
 "04/10/2025",
 "24/10/2025"
};
int da_tra_arr[MAX_PHIEU] = { 0,1,0 };
char ngay_tra_thuc_te_arr[MAX_PHIEU][11] = {
 "", // Chưa trả
 "02/10/2025", // Đã trả
 "" // Chưa trả
};
int so_sach_muon_arr[MAX_PHIEU] = { 1,1,1 };

// Mảng 1 chiều thay vì mảng 3 chiều
char isbn_sach_muon_arr[MAX_PHIEU * MAX_SACH_MUON * 15] = { 0 };
int sach_bi_mat_arr[MAX_PHIEU * MAX_SACH_MUON] = { 0 }; // 0: Không mất, 1: Mất

int so_luong_phieu = 3;

/**
 * @brief Hàm helper để lấy con trỏ tới ISBN trong mảng 1 chiều.
 * @param phieu_idx Index của phiếu (0 -> MAX_PHIEU-1)
 * @param sach_idx Index của sách trong phiếu (0 -> MAX_SACH_MUON-1)
 * @return char*: Con trỏ tới ISBN string (15 ký tự)
 */
char* lay_isbn_phieu(int phieu_idx, int sach_idx) {
	return &isbn_sach_muon_arr[(phieu_idx * MAX_SACH_MUON + sach_idx) * 15];
}

/**
 * @brief Hàm helper để kiểm tra/set trạng thái sách bị mất.
 * @param phieu_idx Index của phiếu
 * @param sach_idx Index của sách trong phiếu
 * @return int: Trạng thái mất (0 hoặc 1)
 */
int lay_trang_thai_mat(int phieu_idx, int sach_idx) {
	return sach_bi_mat_arr[phieu_idx * MAX_SACH_MUON + sach_idx];
}

void dat_trang_thai_mat(int phieu_idx, int sach_idx, int trang_thai) {
	sach_bi_mat_arr[phieu_idx * MAX_SACH_MUON + sach_idx] = trang_thai;
}

// Khởi tạo dữ liệu mẫu cho isbn_sach_muon_arr
void khoi_tao_du_lieu_phieu_mau() {
	static int da_khoi_tao = 0;
	if (da_khoi_tao) return;
	da_khoi_tao = 1;

	// Phiếu 0 (PM001)
	strcpy_s(lay_isbn_phieu(0, 0), 15, "978-1234567890");
	// Phiếu 1 (PM002)
	strcpy_s(lay_isbn_phieu(1, 0), 15, "978-0987654321");
	// Phiếu 2 (PM003)
	strcpy_s(lay_isbn_phieu(2, 0), 15, "978-1112131415");
}

/**
 * @brief Lập phiếu mượn sách (Chức năng3).
 */
void lap_phieu_muon() {
	khoi_tao_du_lieu_phieu_mau();

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
			if (strcmp(ma_doc_gia_arr[i], ma_dg_temp) == 0) {
				vi_tri_doc_gia = i;
				break;
			}
		}

		if (vi_tri_doc_gia == -1) {
			printf("Khong tim thay Doc Gia voi Ma: %s. Bo qua phieu nay.\n", ma_dg_temp);
			continue;
		}

		int index_phieu = so_luong_phieu;
		int so_sach_muon = 0;
		char isbn_temp[15] = { 0 };

		// Tạo mã phiếu tự động
		sprintf_s(ma_phieu_arr[index_phieu], sizeof(ma_phieu_arr[index_phieu]), "PM%03d", index_phieu + 1);
		strcpy_s(ma_doc_gia_phieu_arr[index_phieu], sizeof(ma_doc_gia_phieu_arr[index_phieu]), ma_dg_temp);

		// Ngày mượn (DD/MM/YYYY) với xác thực
		do {
			printf("Nhap Ngay Muon (DD/MM/YYYY): ");
			if (scanf_s("%10s", ngay_muon_arr[index_phieu], (unsigned)sizeof(ngay_muon_arr[index_phieu])) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (!kiem_tra_ngay(ngay_muon_arr[index_phieu])) {
				printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
			}
			else break;
		} while (true);

		// Ngày trả dự kiến (DD/MM/YYYY) với xác thực
		do {
			printf("Nhap Ngay Tra Du Kien (DD/MM/YYYY): ");
			if (scanf_s("%10s", ngay_tra_du_kien_arr[index_phieu], (unsigned)sizeof(ngay_tra_du_kien_arr[index_phieu])) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (!kiem_tra_ngay(ngay_tra_du_kien_arr[index_phieu])) {
				printf("Dinh dang ngay khong hop le. Vui long nhap lai theo DD/MM/YYYY.\n");
			}
			else break;
		} while (true);

		// Nhập danh sách sách mượn: chọn số lượng trước, sau đó nhập ISBN theo số lượng
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

		for (int j = 0; j < num_to_borrow; j++) {
			printf("ISBN %d: ", j + 1);
			if (scanf_s("%14s", isbn_temp, (unsigned)sizeof(isbn_temp)) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				j--; // retry this position
				continue;
			}
			while (getchar() != '\n');

			if (strcmp(isbn_temp, "0") == 0) {
				printf("Khong duoc nhap '0' khi da chon so luong. Vui long nhap lai.\n");
				j--; // retry
				continue;
			}

			int vi_tri_sach = tim_vi_tri_sach(isbn_temp);
			if (vi_tri_sach == -1) {
				printf("Sach voi ISBN %s khong ton tai. Vui long nhap lai.\n", isbn_temp);
				j--; // retry
				continue;
			}

			if (so_quyen_arr[vi_tri_sach] <= 0) {
				printf("Sach '%s' hien da het. Khong the muon. Vui long chon sach khac.\n", ten_sach_arr[vi_tri_sach]);
				j--; // retry
				continue;
			}

			strcpy_s(lay_isbn_phieu(index_phieu, so_sach_muon), 15, isbn_temp);
			dat_trang_thai_mat(index_phieu, so_sach_muon, 0); // Khởi tạo: không mất
			so_sach_muon++;

			// Cập nhật số lượng sách
			so_quyen_arr[vi_tri_sach]--;
			printf("Da them sach '%s' vao phieu. Con lai: %d quyen.\n", ten_sach_arr[vi_tri_sach], so_quyen_arr[vi_tri_sach]);
		}

		if (so_sach_muon == 0) {
			printf("Khong co sach nao duoc them vao phieu. Huy phieu nay.\n");
			continue;
		}

		so_sach_muon_arr[index_phieu] = so_sach_muon;
		strcpy_s(ngay_tra_thuc_te_arr[index_phieu], sizeof(ngay_tra_thuc_te_arr[index_phieu]), ""); // Chua tra
		da_tra_arr[index_phieu] = 0; // Chua tra
		so_luong_phieu++;

		printf("\nLap Phieu Muon %s thanh cong cho Doc Gia %s voi %d cuon sach.\n",
			ma_phieu_arr[index_phieu], ma_dg_temp, so_sach_muon);
	}
}

void lap_phieu_tra() {
	khoi_tao_du_lieu_phieu_mau();

	char ma_phieu_temp[10] = { 0 };
	printf("\n--- LAP PHIEU TRA SACH ---\n");
	printf("Nhap Ma Phieu Muon can tra: ");
	scanf_s("%9s", ma_phieu_temp, (unsigned)sizeof(ma_phieu_temp));

	// B1: Tìm phiếu
	int index_phieu = -1;
	for (int i = 0; i < so_luong_phieu; i++) {
		if (strcmp(ma_phieu_arr[i], ma_phieu_temp) == 0) {
			index_phieu = i;
			break;
		}
	}

	if (index_phieu == -1) {
		printf("Khong tim thay Ma Phieu Muon: %s\n", ma_phieu_temp);
		return;
	}

	if (da_tra_arr[index_phieu] == 1) {
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
		// ngay tra phai >= ngay muon
		if (so_sanh_ngay(ngay_tra_tt, ngay_muon_arr[index_phieu]) < 0) {
			printf("Ngay tra phai khong nho hon ngay muon (%s). Vui long nhap lai.\n", ngay_muon_arr[index_phieu]);
			continue;
		}
		// ngay tra phai <= ngay hien tai
		if (so_sanh_ngay(ngay_tra_tt, ngay_hien_tai) > 0) {
			printf("Ngay tra phai khong lon hon ngay hien tai (%s). Vui long nhap lai.\n", ngay_hien_tai);
			continue;
		}
		break;
	} while (true);

	// B2: Kiểm tra sách bị mất
	printf("\n--- KIEM TRA SACH BI MAT ---\n");
	for (int i = 0; i < so_sach_muon_arr[index_phieu]; i++) {
		char* isbn_sach = lay_isbn_phieu(index_phieu, i);
		int vi_tri_sach = tim_vi_tri_sach(isbn_sach);

		if (vi_tri_sach != -1) {
			printf("Sach %d: %s (%s)\n", i + 1, isbn_sach, ten_sach_arr[vi_tri_sach]);
			printf("Sach nay co bi mat khong? (1=Co, 0=Khong): ");
			int bi_mat = 0;
			if (scanf_s("%d", &bi_mat) != 1) {
				while (getchar() != '\n');
				bi_mat = 0;
			}
			while (getchar() != '\n');
			dat_trang_thai_mat(index_phieu, i, bi_mat ? 1 : 0);
		}
	}

	// B3: Xử lý trả sách
	strcpy_s(ngay_tra_thuc_te_arr[index_phieu], sizeof(ngay_tra_thuc_te_arr[index_phieu]), ngay_tra_tt);
	da_tra_arr[index_phieu] = 1;

	printf("\nDa cap nhat phieu tra %s.\n", ma_phieu_temp);

	// B4: Cập nhật số lượng sách và tính phạt
	long tong_tien_phat = 0;
	long so_ngay_tre = tinh_so_ngay_tre_han(ngay_tra_tt, ngay_tra_du_kien_arr[index_phieu]);

	// Tính phạt trễ hạn (5000 VND/ngày theo đề bài)
	if (so_ngay_tre > 0) {
		long tien_phat_tre = so_ngay_tre * 5000 * so_sach_muon_arr[index_phieu];
		tong_tien_phat += tien_phat_tre;
		printf("TRE HAN: Ngay tra du kien la %s. Tre %ld ngay.\n", ngay_tra_du_kien_arr[index_phieu], so_ngay_tre);
		printf("TIEN PHAT TRE HAN: %ld VND (5,000 VND/ngay x %ld ngay x %d sach).\n",
			tien_phat_tre, so_ngay_tre, so_sach_muon_arr[index_phieu]);
	}
	else {
		printf("SACH DUOC TRA DUNG HAN/SOM HAN.\n");
	}

	// Tính phạt sách mất (200% giá sách theo đề bài)
	long tien_phat_mat = 0;
	for (int i = 0; i < so_sach_muon_arr[index_phieu]; i++) {
		if (lay_trang_thai_mat(index_phieu, i) == 1) {
			char* isbn_sach = lay_isbn_phieu(index_phieu, i);
			int vi_tri_sach = tim_vi_tri_sach(isbn_sach);

			if (vi_tri_sach != -1) {
				long phat_sach_nay = gia_sach_arr[vi_tri_sach] * 2; // 200%
				tien_phat_mat += phat_sach_nay;
				printf("SACH BI MAT: %s - Gia: %ld VND - Phat: %ld VND (200%%)\n",
					ten_sach_arr[vi_tri_sach], gia_sach_arr[vi_tri_sach], phat_sach_nay);
			}
		}
	}

	if (tien_phat_mat > 0) {
		tong_tien_phat += tien_phat_mat;
		printf("TONG TIEN PHAT SACH MAT: %ld VND\n", tien_phat_mat);
	}

	if (tong_tien_phat > 0) {
		printf("\n==> TONG TIEN PHAT: %ld VND\n", tong_tien_phat);
	}
	else {
		printf("\n==> Khong co phat.\n");
	}

	// Tăng lại số lượng sách đã trả (chỉ những sách không bị mất)
	for (int i = 0; i < so_sach_muon_arr[index_phieu]; i++) {
		if (lay_trang_thai_mat(index_phieu, i) == 0) { // Không bị mất
			char* isbn_sach = lay_isbn_phieu(index_phieu, i);
			int vi_tri_sach = tim_vi_tri_sach(isbn_sach);

			if (vi_tri_sach != -1) {
				so_quyen_arr[vi_tri_sach]++;
			}
		}
	}

	printf("\nDa hoan tat qua trinh tra sach va cap nhat so luong trong kho.\n");
}

void xem_danh_sach_phieu_muon() {
	khoi_tao_du_lieu_phieu_mau();

	printf("\n--- DANH SACH PHIEU MUON ---\n");
	if (so_luong_phieu == 0) {
		printf("Hien khong co phieu muon nao.\n");
		return;
	}

	printf("%-6s | %-6s | %-11s | %-11s | %-5s | %-11s | %-8s | %s\n",
		"MaP", "MaDG", "NgayMuon", "NgayDuKien", "Tra?", "NgayTraTT", "SoSach", "ISBNs");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < so_luong_phieu; i++) {
		char isbns[MAX_SACH_MUON * 16] = "";
		for (int j = 0; j < so_sach_muon_arr[i]; j++) {
			if (j > 0) {
				strcat_s(isbns, sizeof(isbns), ", ");
			}
			strcat_s(isbns, sizeof(isbns), lay_isbn_phieu(i, j));
		}

		printf("%-6s | %-6s | %-11s | %-11s | %-5s | %-11s | %-8d | %s\n",
			ma_phieu_arr[i], ma_doc_gia_phieu_arr[i], ngay_muon_arr[i], ngay_tra_du_kien_arr[i],
			da_tra_arr[i] ? "Yes" : "No", ngay_tra_thuc_te_arr[i][0] ? ngay_tra_thuc_te_arr[i] : "-",
			so_sach_muon_arr[i], isbns);
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");
}
