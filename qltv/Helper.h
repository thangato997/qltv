#ifndef HELPER_H
#define HELPER_H

#include <stddef.h>

// Helper functions moved out of module files
char* chuyen_sang_chu_thuong(const char* s);
int tim_vi_tri_doc_gia(const char* cmnd_can_tim);
void tinh_ngay_het_han(const char* ngay_lap, char* ngay_het_han, size_t buffer_size);

char* generate_random_isbn();

// Date helpers
int phan_tich_ngay_sang_ymd(const char* s, int* y, int* m, int* d);
int so_sanh_ngay(const char* date1, const char* date2);
long int tinh_so_ngay_tre_han(const char* date_str1, const char* date_str2);
bool kiem_tra_ngay(const char* s);

#endif // HELPER_H
