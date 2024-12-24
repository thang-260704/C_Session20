#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char maSP[10];
    char tenSP[100];
    int giaNhap;
    int giaBan;
    int soLuong;
} SanPham;

void nhapChuoi(char *chuoi, int doDai) {
    fgets(chuoi, doDai, stdin);
    if (strlen(chuoi) > 0 && chuoi[strlen(chuoi) - 1] == '\n')
        chuoi[strlen(chuoi) - 1] = '\0';
}

void nhapThongTinSanPham(SanPham *sanPham, int viTri) {
    printf("Ma san pham: ");
    nhapChuoi(sanPham[viTri].maSP, 10);
    printf("Ten san pham: ");
    nhapChuoi(sanPham[viTri].tenSP, 100);
    printf("Gia nhap (kVND): ");
    scanf("%d", &sanPham[viTri].giaNhap);
    printf("Gia ban (kVND): ");
    scanf("%d", &sanPham[viTri].giaBan);
    printf("So luong: ");
    scanf("%d", &sanPham[viTri].soLuong);
    getchar();
    printf("\n");
}

void hoanVi(SanPham *sanPham1, SanPham *sanPham2) {
    SanPham tam = *sanPham1;
    *sanPham1 = *sanPham2;
    *sanPham2 = tam;
}

void sapXepGiam(SanPham *danhSach, int kichThuoc, int *trangThai) {
    for (int i = 0; i < kichThuoc - 1; i++) {
        if (trangThai[i]) {
            int viTriMax = i;
            for (int j = i + 1; j < kichThuoc; j++) {
                if (trangThai[j] && danhSach[j].giaBan > danhSach[viTriMax].giaBan) {
                    viTriMax = j;
                }
            }
            hoanVi(&danhSach[i], &danhSach[viTriMax]);
        }
    }
}

void sapXepTang(SanPham *danhSach, int kichThuoc, int *trangThai) {
    for (int i = 0; i < kichThuoc - 1; i++) {
        if (trangThai[i]) {
            int viTriMin = i;
            for (int j = i + 1; j < kichThuoc; j++) {
                if (trangThai[j] && danhSach[j].giaBan < danhSach[viTriMin].giaBan) {
                    viTriMin = j;
                }
            }
            hoanVi(&danhSach[i], &danhSach[viTriMin]);
        }
    }
}

SanPham danhSachSanPham[50];
int doanhThu, luaChonMenu, soLuongSanPham, viTri, soLuongNhapHang, trangThai[55];
char tenSanPham[100], luaChonSapXep;

int main() {
    do {
        printf("MENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu san pham\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChonMenu);
        getchar();

        switch (luaChonMenu) {
            case 1:
                printf("Nhap so luong san pham: ");
                scanf("%d", &soLuongSanPham);
                getchar();
                printf("Nhap thong tin san pham:\n");
                for (int i = 0; i < soLuongSanPham; i++) {
                    printf("Nhap thong tin san pham %d:\n", i + 1);
                    trangThai[i] = 1;
                    nhapThongTinSanPham(danhSachSanPham, i);
                }
                break;

            case 2:
                printf("\nDanh sach san pham:\n");
                printf("STT  Ma san pham       Ten san pham       Gia nhap  Gia ban  So luong\n");
                for (int i = 0; i < soLuongSanPham; i++) {
                    if (trangThai[i]) {
                        printf("%3d  %10s  %15s  %8d  %7d  %9d\n",
                               i + 1, danhSachSanPham[i].maSP, danhSachSanPham[i].tenSP, danhSachSanPham[i].giaNhap,
                               danhSachSanPham[i].giaBan, danhSachSanPham[i].soLuong);
                    }
                }
                break;

            case 3:
                printf("Nhap ma san pham: ");
                nhapChuoi(tenSanPham, 100);
                viTri = -1;
                for (int i = 0; i < soLuongSanPham; i++) {
                    if (strcmp(tenSanPham, danhSachSanPham[i].maSP) == 0) {
                        viTri = i;
                        break;
                    }
                }
                if (viTri == -1) {
                    printf("Ma san pham khong ton tai!\n");
                } else {
                    printf("Nhap so luong nhap hang: ");
                    scanf("%d", &soLuongNhapHang);
                    getchar();
                    if (soLuongNhapHang * danhSachSanPham[viTri].giaNhap > doanhThu) {
                        printf("Gia nhap vuot qua doanh thu hien co!\n");
                    } else {
                        doanhThu -= soLuongNhapHang * danhSachSanPham[viTri].giaNhap;
                        danhSachSanPham[viTri].soLuong += soLuongNhapHang;
                        printf("Nhap hang thanh cong!\n");
                    }
                }
                break;

            case 4:
                printf("Cap nhat thong tin san pham:\nNhap ma san pham: ");
                nhapChuoi(tenSanPham, 100);
                viTri = -1;
                for (int i = 0; i < soLuongSanPham; i++) {
                    if (strcmp(tenSanPham, danhSachSanPham[i].maSP) == 0) {
                        viTri = i;
                        break;
                    }
                }
                if (viTri == -1) {
                    printf("Ma san pham khong ton tai!\n");
                } else {
                    nhapThongTinSanPham(danhSachSanPham, viTri);
                    printf("Cap nhat thong tin thanh cong!\n");
                }
                break;

            case 5:
                do {
                    printf("a. Tang theo gia ban\nb. Giam theo gia ban\nLua chon cua ban: ");
                    scanf("%c", &luaChonSapXep);
                    getchar();
                } while (luaChonSapXep != 'a' && luaChonSapXep != 'b');
                if (luaChonSapXep == 'a') {
                    sapXepTang(danhSachSanPham, soLuongSanPham, trangThai);
                } else {
                    sapXepGiam(danhSachSanPham, soLuongSanPham, trangThai);
                }
                break;

            case 6:
                printf("Tim kiem san pham:\nNhap ma san pham: ");
                nhapChuoi(tenSanPham, 100);
                viTri = -1;
                for (int i = 0; i < soLuongSanPham; i++) {
                    if (strcmp(tenSanPham, danhSachSanPham[i].maSP) == 0) {
                        viTri = i;
                        break;
                    }
                }
                if (viTri == -1) {
                    printf("Ma san pham khong ton tai!\n");
                } else {
                    printf("Thong tin san pham:\n");
                    printf("Ma san pham: %s\n", danhSachSanPham[viTri].maSP);
                    printf("Ten san pham: %s\n", danhSachSanPham[viTri].tenSP);
                    printf("Gia nhap: %d\n", danhSachSanPham[viTri].giaNhap);
                    printf("Gia ban: %d\n", danhSachSanPham[viTri].giaBan);
                    printf("So luong: %d\n", danhSachSanPham[viTri].soLuong);
                }
                break;

            case 7:
                printf("Ban san pham:\nNhap ma san pham: ");
                nhapChuoi(tenSanPham, 100);
                viTri = -1;
                for (int i = 0; i < soLuongSanPham; i++) {
                    if (strcmp(tenSanPham, danhSachSanPham[i].maSP) == 0) {
                        viTri = i;
                        break;
                    }
                }
                if (viTri == -1) {
                    printf("Ma san pham khong ton tai!\n");
                } else {
                    printf("Nhap so luong ban: ");
                    scanf("%d", &soLuongNhapHang);
                    getchar();
                    if (soLuongNhapHang > danhSachSanPham[viTri].soLuong) {
                        printf("So luong khong du!\n");
                    } else {
                        danhSachSanPham[viTri].soLuong -= soLuongNhapHang;
                        doanhThu += soLuongNhapHang * danhSachSanPham[viTri].giaBan;
                        printf("Ban thanh cong!\n");
                    }
                }
                break;

            case 8:
                printf("Doanh thu hien tai: %d\n", doanhThu);
                break;
        }
    } while (luaChonMenu != 9);

    return 0;
}
