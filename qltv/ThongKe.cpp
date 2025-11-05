#include "ThongKe.h"
#include "DocGia.h"
#include "Sach.h"
#include "PhieuMuon.h"
#include <cstdio>
#include <cstring> // Cho strcmp, strcpy_s
#include <stdbool.h>

/**
 * @brief Thống kê số lượng sách trong thư viện (Chức năng 5a).
 * @param None
 * @return void
 */
void thong_ke_so_luong_sach() {
	printf("\n--> So luong sach khac nhau trong thu vien: %d quyen.\n", so_luong_sach);
}

/**
 * @brief Thống kê số lượng sách theo thể loại (Chức năng 5b).
 * @param None
 * @return void
 */
void thong_ke_sach_theo_the_loai() {
	printf("\n--- THONG KE SACH THEO THE LOAI ---\n");
	if (so_luong_sach == 0) {
		printf("Hien khong co sach nao de thong ke.\n");
		return;
	}

	char the_loai_duy_nhat[MAX_THE_LOAI_KHAC][MAX_CH_SACH];
	int so_luong_theo_tl[MAX_THE_LOAI_KHAC];
	int so_luong_tl_duy_nhat = 0;

	// B1: Duyệt qua danh sách sách để tìm các thể loại duy nhất
	for (int i = 0; i < so_luong_sach; i++) {
		bool da_ton_tai = false;
		// Kiểm tra xem thể loại đã có trong danh sách thống kê chưa
		for (int j = 0; j < so_luong_tl_duy_nhat; j++) {
			if (strcmp(the_loai_arr[i], the_loai_duy_nhat[j]) == 0) {
				so_luong_theo_tl[j]++;
				da_ton_tai = true;
				break;
			}
		}

		// Nếu là thể loại mới
		if (!da_ton_tai && so_luong_tl_duy_nhat < MAX_THE_LOAI_KHAC) {
			strcpy_s(the_loai_duy_nhat[so_luong_tl_duy_nhat], sizeof(the_loai_duy_nhat[so_luong_tl_duy_nhat]), the_loai_arr[i]);
			so_luong_theo_tl[so_luong_tl_duy_nhat] = 1;
			so_luong_tl_duy_nhat++;
		}
	}

	// B2: In kết quả thống kê
	printf("\n%-20s | %s\n", "The Loai", "So Quyen");
	printf("-----------------------------------\n");
	for (int i = 0; i < so_luong_tl_duy_nhat; i++) {
		printf("%-20s | %d\n", the_loai_duy_nhat[i], so_luong_theo_tl[i]);
	}
	printf("-----------------------------------\n");
	printf("TONG CONG: %d quyen.\n", so_luong_sach);
}

/**
 * @brief Thống kê số lượng độc giả (Chức năng 5c).
 * @param None
 * @return void
 */
void thong_ke_so_luong_doc_gia() {
	printf("\n--> Tong so doc gia trong thu vien: %d nguoi.\n", so_luong_doc_gia);
}

/**
 * @brief Thống kê số lượng độc giả theo giới tính (Chức năng 5d).
 * @param None
 * @return void
 */
void thong_ke_doc_gia_theo_gioi_tinh() {
	printf("\n--- THONG KE DOC GIA THEO GIOI TINH ---\n");
	if (so_luong_doc_gia == 0) {
		printf("Hien khong co doc gia nao de thong ke.\n");
		return;
	}

	int nam_count = 0;
	int nu_count = 0;

	for (int i = 0; i < so_luong_doc_gia; i++) {
		if (strcmp(gioi_tinh_arr[i], "Nam") == 0) {
			nam_count++;
		}
		else if (strcmp(gioi_tinh_arr[i], "Nu") == 0) {
			nu_count++;
		}
	}

	printf("Gioi Tinh Nam: %d nguoi\n", nam_count);
	printf("Gioi Tinh Nu: %d nguoi\n", nu_count);
	printf("---------------------------\n");
	printf("Tong Doc Gia: %d nguoi\n", so_luong_doc_gia);
}

/**
 * @brief Thống kê số sách đang được mượn (Chức năng 5e).
 * @param None
 * @return void
 */
void thong_ke_so_sach_dang_muon() {
	printf("\n--- THONG KE SO SACH DANG MUON ---\n");

	int tong_sach_dang_muon = 0;

	// Giả sử PhieuMuon.cpp có biến/mảng `da_tra_arr` (0: Chưa trả, 1: Đã trả)
	// và mảng `so_sach_muon_arr` (số lượng sách trong phiếu)

	for (int i = 0; i < so_luong_phieu; i++) {
		// Kiểm tra xem phiếu này đã được trả chưa
		// Giả định: da_tra_arr được định nghĩa và cập nhật trong PhieuMuon.cpp
		extern int da_tra_arr[MAX_PHIEU];

		if (da_tra_arr[i] == 0) { // Nếu chưa trả
			tong_sach_dang_muon += so_sach_muon_arr[i];
		}
	}

	printf("--> Tong so sach hien dang duoc muon: %d quyen.\n", tong_sach_dang_muon);
}

// Khai báo lại hàm so_sanh_ngay từ PhieuMuon.cpp 
extern int so_sanh_ngay(const char* date1, const char* date2);

/**
 * @brief Thống kê danh sách độc giả bị trễ hạn (Chức năng 5f).
 * @param None
 * @return void
 */
void thong_ke_doc_gia_tre_han() {
	printf("\n--- THONG KE DOC GIA BI TRE HAN ---\n");

	// Để kiểm tra trễ hạn, ta cần ngày hiện tại (định dạng DD/MM/YYYY)
	char ngay_hien_tai[11] = "30/10/2025"; // GIẢ LẬP NGÀY HIỆN TẠI

	printf("Ngay Hien Tai (Gia lap): %s\n", ngay_hien_tai);
	printf("\n%-10s | %-10s | %-20s | %-12s | %-12s\n", "Ma Phieu", "Ma DG", "Ho Ten", "Ngay Du Kien", "Trang Thai");
	printf("--------------------------------------------------------------------------\n");

	bool co_tre_han = false;

	for (int i = 0; i < so_luong_phieu; i++) {
		// Chỉ xét các phiếu chưa trả (da_tra_arr[i] == 0)
		extern int da_tra_arr[MAX_PHIEU];

		if (da_tra_arr[i] == 0) {
			// So sánh Ngay Hien Tai với Ngay Tra Du Kien
			if (so_sanh_ngay(ngay_hien_tai, ngay_tra_du_kien_arr[i]) > 0) {
				// Đã quá hạn: tìm tên độc giả theo mã độc giả trong phiếu
				const char* ma_dg_phieu = ma_doc_gia_phieu_arr[i];
				const char* ho_ten = "(Khong ro)";
				for (int j = 0; j < so_luong_doc_gia; j++) {
					if (strcmp(ma_doc_gia_arr[j], ma_dg_phieu) == 0) {
						ho_ten = ho_ten_arr[j];
						break;
					}
				}

				printf("%-10s | %-10s | %-20s | %-12s | %-12s\n",
					ma_phieu_arr[i],
					ma_doc_gia_phieu_arr[i],
					ho_ten,
					ngay_tra_du_kien_arr[i],
					"TRE HAN");
				co_tre_han = true;
			}
		}
	}

	if (!co_tre_han) {
		printf("Hien khong co doc gia nao bi tre han (voi cac phieu chua tra).\n");
	}
	printf("--------------------------------------------------------------------------\n");
}
