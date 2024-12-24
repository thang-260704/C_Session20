#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char maSach[10];
    char tenSach[100];
    char tacGia[100];
    int giaTien;
} DanhSachSach;

DanhSachSach danhSach[500];

void nhapChuoi(char *chuoi, int doDai) {
    fgets(chuoi, doDai, stdin);
    if (strlen(chuoi) > 0 && chuoi[strlen(chuoi) - 1] == '\n') 
        chuoi[strlen(chuoi) - 1] = '\0';
}

void hoanVi(DanhSachSach *sach1, DanhSachSach *sach2) {
    DanhSachSach tam = *sach1;
    *sach1 = *sach2;
    *sach2 = tam;
}

void sapXepTang(DanhSachSach *danhSach, int kichThuoc, int *trangThai) {
    for (int i = 0; i < 499; i++) {
        if (trangThai[i]) {
            int viTriMin = i;
            for (int j = i + 1; j < kichThuoc; j++) {
                if (trangThai[j] && danhSach[j].giaTien < danhSach[viTriMin].giaTien) {
                    viTriMin = j;
                }
            }
            hoanVi(&danhSach[i], &danhSach[viTriMin]);
        }
    }
}

void sapXepGiam(DanhSachSach *danhSach, int kichThuoc, int *trangThai) {
    for (int i = 0; i < 499; i++) {
        if (trangThai[i]) {
            int viTriMax = i;
            for (int j = i + 1; j < kichThuoc; j++) {
                if (trangThai[j] && danhSach[j].giaTien > danhSach[viTriMax].giaTien) {
                    viTriMax = j;
                }
            }
            hoanVi(&danhSach[i], &danhSach[viTriMax]);
        }
    }
}

void nhapThongTinSach(DanhSachSach *danhSach, int viTri) {
    printf("Ma sach %d: ", viTri + 1);
    nhapChuoi(danhSach[viTri].maSach, 10);
    printf("Ten sach: ");
    nhapChuoi(danhSach[viTri].tenSach, 100);
    printf("Tac gia: ");
    nhapChuoi(danhSach[viTri].tacGia, 100);
    printf("Gia tien: ");
    scanf("%d", &danhSach[viTri].giaTien);
    getchar();
    printf("\n");
}

char tenSach[50], luaChon;
int trangThai[505], soLuongSach, viTri, tonTai;

int main() {
    int luaChonMenu;
    do {
        printf("MENU\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them thong tin sach\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin theo ma sach\n");
        printf("6. Sap xep sach theo gia\n");
        printf("7. Tim kiem thong tin theo ten sach\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChonMenu);
        getchar();

        switch (luaChonMenu) {
            case 1:
                printf("Nhap so luong sach: ");
                scanf("%d", &soLuongSach);
                getchar();
                printf("\n");
                for (int i = 0; i < soLuongSach; i++) {
                    nhapThongTinSach(danhSach, i);
                    trangThai[i] = 1;
                }
                break;
            case 2:
                printf("Thong tin sach:\n");
                printf("STT  Ma sach          Ten sach            Tac gia     Gia tien\n");
                for (int i = 0; i < 500; i++) {
                    if (trangThai[i]) {
                        printf("%3d %8s %22s %15s     %4d\n", 
                               i + 1, danhSach[i].maSach, danhSach[i].tenSach, danhSach[i].tacGia, danhSach[i].giaTien);
                    }
                }
                break;
            case 3:
                printf("Them sach:\nNhap vi tri sach: ");
                scanf("%d", &viTri);
                getchar();
                if (viTri <= 0 || viTri > 500) 
                    printf("Vi tri khong ton tai trong danh sach!\n");
                else if (trangThai[viTri - 1]) 
                    printf("Vi tri da co thong tin sach!\n");
                else {
                    viTri--;
                    trangThai[viTri] = 1;
                    nhapThongTinSach(danhSach, viTri);
                }
                break;
            case 4:
                printf("Nhap ma sach can xoa: ");
                nhapChuoi(tenSach, 50);
                tonTai = 0;
                for (int i = 0; i < 500; i++) {
                    if (strcmp(danhSach[i].maSach, tenSach) == 0) {
                        tonTai = 1;
                        trangThai[i] = 0;
                        printf("Da xoa thong tin ma sach %s!\n", danhSach[i].maSach);
                        break;
                    }
                }
                if (!tonTai) 
                    printf("Ma sach khong ton tai trong danh sach!\n");
                break;
            case 5:
                printf("Nhap ma sach can cap nhat: ");
                nhapChuoi(tenSach, 50);
                tonTai = 0;
                for (int i = 0; i < 500; i++) {
                    if (strcmp(danhSach[i].maSach, tenSach) == 0 && trangThai[i]) {
                        tonTai = 1;
                        viTri = i;
                        break;
                    }
                }
                if (!tonTai) 
                    printf("Ma sach khong ton tai trong danh sach!\n");
                else {
                    printf("Cap nhat thong tin ma sach %s:\n", danhSach[viTri].maSach);
                    printf("Ten sach: ");
                    nhapChuoi(danhSach[viTri].tenSach, 100);
                    printf("Tac gia: ");
                    nhapChuoi(danhSach[viTri].tacGia, 100);
                    printf("Gia tien: ");
                    scanf("%d", &danhSach[viTri].giaTien);
                    getchar();
                    printf("Cap nhat thong tin thanh cong!\n");
                }
                break;
            case 6:
                do {
                    printf("a. Tang theo gia\nb. Giam theo gia\nLua chon cua ban: ");
                    scanf("%c", &luaChon);
                    getchar();
                } while (luaChon != 'a' && luaChon != 'b');
                if (luaChon == 'a') 
                    sapXepTang(danhSach, 500, trangThai);
                else 
                    sapXepGiam(danhSach, 500, trangThai);
                break;
            case 7:
                printf("Nhap ten sach muon tim kiem: ");
                nhapChuoi(tenSach, 100);
                tonTai = 0;
                for (int i = 0; i < 500; i++) {
                    if (strcmp(danhSach[i].tenSach, tenSach) == 0 && trangThai[i]) {
                        tonTai = 1;
                        printf("Thong tin ten sach %s:\nMa sach: %s\nTac gia: %s\nGia tien: %d VND\n", 
                               danhSach[i].tenSach, danhSach[i].maSach, danhSach[i].tacGia, danhSach[i].giaTien);
                        break;
                    }
                }
                if (!tonTai) 
                    printf("Khong co ten sach trong danh sach!\n");
                break;
        }
    } while (luaChonMenu != 8);

    return 0;
}
