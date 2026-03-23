#include "Helper.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <ctime>

void loai_bo_ky_tu_pipe(char* s) {
	if (s == NULL) return;
	char* src = s;
	char* dst = s;
	while (*src) {
		if (*src != '|') {
			*dst++ = *src;
		}
		src++;
	}
	*dst = '\0';
}

char* chuyen_sang_chu_thuong(const char* s) {
	if (s == NULL) return NULL;
	size_t len = strlen(s);
	char* new_s = (char*)malloc((len + 1) * sizeof(char));
	if (new_s == NULL) return NULL;
	for (size_t i = 0; i <= len; i++) {
		new_s[i] = (char)tolower((unsigned char)s[i]);
	}
	return new_s;
}

void tinh_ngay_het_han(const char* ngay_lap, char* ngay_het_han, size_t buffer_size) {
	int ngay = 0, thang = 0, nam = 0;
	if (sscanf_s(ngay_lap, "%d/%d/%d", &ngay, &thang, &nam) == 3) {
		nam += 4;
		sprintf_s(ngay_het_han, buffer_size, "%02d/%02d/%04d", ngay, thang, nam);
	}
	else {
		strcpy_s(ngay_het_han, buffer_size, "DD/MM/YYYY");
	}
}

bool kiem_tra_ngay(const char* s) {
	if (s == NULL) return false;
	if (strlen(s) != 10) return false;
	if (s[2] != '/' || s[5] != '/') return false;
	int d = 0, m = 0, y = 0;
	if (sscanf_s(s, "%d/%d/%d", &d, &m, &y) != 3) return false;
	if (y < 1900 || y >9999) return false;
	if (m < 1 || m >12) return false;
	int mdays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((y % 400) == 0 || ((y % 4) == 0 && (y % 100) != 0)) mdays[1] = 29;
	if (d <1 || d > mdays[m - 1]) return false;
	return true;
}


int phan_tich_ngay_sang_ymd(const char* s, int* y, int* m, int* d) {
	if (!s || !y || !m || !d) return 0;
	int a = 0, b = 0, c = 0;
	if (strchr(s, '/')) {
		// DD/MM/YYYY
		if (sscanf_s(s, "%d/%d/%d", &a, &b, &c) == 3) {
			*d = a; *m = b; *y = c; return 1;
		}
	}
	else if (strchr(s, '-')) {
		// YYYY-MM-DD or DD-MM-YYYY
		if (sscanf_s(s, "%d-%d-%d", &a, &b, &c) == 3) {
			if (a > 31) { // a is year
				*y = a; *m = b; *d = c; return 1;
			}
			else {
				*d = a; *m = b; *y = c; return 1;
			}
		}
	}
	return 0;
}

int so_sanh_ngay(const char* date1, const char* date2) {
	int y1 = 0, m1 = 0, d1 = 0;
	int y2 = 0, m2 = 0, d2 = 0;
	if (!phan_tich_ngay_sang_ymd(date1, &y1, &m1, &d1) || !phan_tich_ngay_sang_ymd(date2, &y2, &m2, &d2)) {
		return strcmp(date1, date2);
	}
	if (y1 != y2) return (y1 < y2) ? -1 : 1;
	if (m1 != m2) return (m1 < m2) ? -1 : 1;
	if (d1 != d2) return (d1 < d2) ? -1 : 1;
	return 0;
}

static int nam_nhuan_local(int year) {
	if ((year % 400) == 0) return 1;
	if ((year % 100) == 0) return 0;
	if ((year % 4) == 0) return 1;
	return 0;
}

static long int so_ngay_local(int d, int m, int y) {
	const int ngay_tich_luy[12] = { 0,31,59,90,120,151,181,212,243,273,304,334 };
	long int total = 0;
	for (int yr = 1; yr < y; yr++) {
		total += (nam_nhuan_local(yr) ? 366 : 365);
	}
	if (m >= 1 && m <= 12) total += ngay_tich_luy[m - 1];
	if (m > 2 && nam_nhuan_local(y)) total += 1;
	total += d;
	return total;
}


long int tinh_so_ngay_tre_han(const char* date_str1, const char* date_str2) {
	int d1 = 0, m1 = 0, y1 = 0;
	int d2 = 0, m2 = 0, y2 = 0;
	if (sscanf_s(date_str1, "%d/%d/%d", &d1, &m1, &y1) != 3) return -1;
	if (sscanf_s(date_str2, "%d/%d/%d", &d2, &m2, &y2) != 3) return -1;
	long int days1 = so_ngay_local(d1, m1, y1);
	long int days2 = so_ngay_local(d2, m2, y2);
	return days1 - days2;
}

/**
* @brief Generate a random ISBN in the format "XXX-XXXXXXXXXX".
* @return A dynamically allocated string containing the ISBN. Caller must free it.
*/
char* generate_random_isbn() {
	const size_t SIZE = 15; // "XXX-XXXXXXXXXX\0"
	char* isbn = (char*)malloc(SIZE);
	if (!isbn) return NULL;

	static int seeded = 0;
	if (!seeded) {
		seeded = 1;
		srand((unsigned)time(NULL));
	}

	// Fill first 3 digits
	for (int i = 0; i < 3; ++i) {
		isbn[i] = (char)('0' + (rand() % 10));
	}
	isbn[3] = '-';
	// Fill next 10 digits
	for (int i = 0; i < 10; ++i) {
		isbn[4 + i] = (char)('0' + (rand() % 10));
	}
	isbn[14] = '\0';
	return isbn;
}

void lay_ngay_hien_tai(char* buf, size_t bufsize) {
	if (!buf || bufsize == 0) return;
	time_t t = time(NULL);
	tm lt;
	localtime_s(&lt, &t);
	strftime(buf, bufsize, "%d/%m/%Y", &lt);
}

int lay_nam_hien_tai() {
	time_t t = time(NULL);
	tm lt;
	localtime_s(&lt, &t);
	return lt.tm_year + 1900;
}