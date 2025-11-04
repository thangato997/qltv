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
char ma_sach_phieu_arr[MAX_PHIEU][10] = {
 "S001",
 "S002",
 "S003"
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
char isbn_sach_muon_arr[MAX_PHIEU][MAX_SACH_MUON][15] = {
	// Phiếu1 (PM001)
	{ "978-1234567890", "", "", "", "" },
	// Phiếu2 (PM002)
	{ "978-0987654321", "", "", "", "" },
	// Phiếu3 (PM003)
	{ "978-1112131415", "", "", "", "" }
};

int so_luong_phieu = 3;

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

		// Nhập danh sách sách mượn
		printf("Nhap cac ISBN sach muon (Nhap '0' de ket thuc):\n");
		while (so_sach_muon < MAX_SACH_MUON) {
			printf("ISBN %d: ", so_sach_muon + 1);
			if (scanf_s("%14s", isbn_temp, (unsigned)sizeof(isbn_temp)) != 1) {
				while (getchar() != '\n');
				printf("Nhap khong hop le. Vui long nhap lai.\n");
				continue;
			}
			while (getchar() != '\n');
			if (strcmp(isbn_temp, "0") == 0) break;

			int vi_tri_sach = tim_vi_tri_sach(isbn_temp);
			if (vi_tri_sach == -1) {
				printf("Sach voi ISBN %s khong ton tai. Vui long nhap lai.\n", isbn_temp);
				continue;
			}

			if (so_quyen_arr[vi_tri_sach] <= 0) {
				printf("Sach '%s' hien da het. Khong the muon.\n", ten_sach_arr[vi_tri_sach]);
				continue;
			}

			strcpy_s(isbn_sach_muon_arr[index_phieu][so_sach_muon], sizeof(isbn_sach_muon_arr[index_phieu][so_sach_muon]), isbn_temp);
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
		// Get current date
		time_t t = time(NULL);
		struct tm lt;
		localtime_s(&lt, &t);
		char ngay_hien_tai[11];
		strftime(ngay_hien_tai, sizeof(ngay_hien_tai), "%d/%m/%Y", &lt);

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

	// B2: Xử lý trả sách
	strcpy_s(ngay_tra_thuc_te_arr[index_phieu], sizeof(ngay_tra_thuc_te_arr[index_phieu]), ngay_tra_tt);
	da_tra_arr[index_phieu] = 1;

	printf("Da cap nhat phieu tra %s.\n", ma_phieu_temp);

	// B3: Cập nhật số lượng sách và tính phạt
	long tong_tien_phat = 0;
	long so_ngay_tre = tinh_so_ngay_tre_han(ngay_tra_tt, ngay_tra_du_kien_arr[index_phieu]);

	if (so_ngay_tre > 0) {
		tong_tien_phat = so_ngay_tre * 2000 * so_sach_muon_arr[index_phieu]; //2000 VND/ngày/quyển
		printf("TRE HAN: Ngay tra du kien la %s. Tre %ld ngay.\n", ngay_tra_du_kien_arr[index_phieu], so_ngay_tre);
		printf("TONG TIEN PHAT: %ld VND.\n", tong_tien_phat);
	}
	else {
		printf("SACH DUOC TRA DUNG HAN/SOM HAN. Khong co phat.\n");
	}

	// Tăng lại số lượng sách đã trả
	for (int i = 0; i < so_sach_muon_arr[index_phieu]; i++) {
		char* isbn_sach = isbn_sach_muon_arr[index_phieu][i];
		int vi_tri_sach = tim_vi_tri_sach(isbn_sach);

		if (vi_tri_sach != -1) {
			so_quyen_arr[vi_tri_sach]++;
		}
	}

	printf("Da hoan tat qua trinh tra sach va cap nhat so luong trong kho.\n");
}
