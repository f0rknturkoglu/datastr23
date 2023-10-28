#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Öğrenci bilgilerini saklamak için yapı.
struct Ogrenci {
    int numara;
    char isim[50];
    int yas;
    struct Ogrenci* sonraki;
};


struct Ogrenci* ilkOgrenci = NULL; //İlk öğrenci nodeu

// Yeni bir öğrenci düğümü oluşturuyoruz.
struct Ogrenci* yeniOgrenciOlustur(int numara, char isim[], int yas) {
    struct Ogrenci* ogrenci = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    ogrenci->numara = numara;
    strcpy(ogrenci->isim, isim);
    ogrenci->yas = yas;
    ogrenci->sonraki = NULL;
    return ogrenci;
}

// Liste başına yeni bir öğrenci ekledik.
void ogrenciEkle(int numara, char isim[], int yas) {
    struct Ogrenci* yeni = yeniOgrenciOlustur(numara, isim, yas);
    yeni->sonraki = ilkOgrenci;
    ilkOgrenci = yeni;
}

// Tüm öğrenci bilgilerini ekrana yazdırıp sayacla sayıyoruz.
void ogrenciListeleVeSay() {
    struct Ogrenci* temp = ilkOgrenci;
    int sayac = 1;
    while (temp != NULL) {
        printf("%d- %s %d %d\n", sayac, temp->isim, temp->yas, temp->numara);
        sayac++;
        temp = temp->sonraki;//NULL'a ilerliyoruz
    }
}

// Verilen öğrenci adına göre arıyoruz..
void ogrenciAra(char arananIsim[]) {
    struct Ogrenci* temp = ilkOgrenci;
    while (temp != NULL) {//listeyi gezmek için while dongusu kullandık
        if (strcmp(temp->isim, arananIsim) == 0) { //temp'in isim datasıyla arananIsimi karşılaştırdık.
            printf("Aranan isim bulundu: %s %d %d\n", temp->isim, temp->yas, temp->numara);
            return;
        }
        temp = temp->sonraki; //listenin sonuna ilerlioruz.
    }
    printf("Aranan isim bulunamadi.\n");
}

// Verilen öğrenci adını listede bulup bir sonraki düğümü siler
void ogrenciSil(char silinecekIsim[]) {
    struct Ogrenci* temp = ilkOgrenci;
    struct Ogrenci* onceki = NULL;

    while (temp != NULL) {
        if (strcmp(temp->isim, silinecekIsim) == 0) {
            if (onceki == NULL) { //eğer silinecek öğrenci listenin başındaysa yani "onceki" NULL ise, 
            //ilkOgrenci'nin işaretçisi temp'in sonrakisi ile güncellenir. ilk ogrenci atlanır



                ilkOgrenci = temp->sonraki;
            } else {
                onceki->sonraki = temp->sonraki;//aksi durumda onceki->sonraki işaretçisi temp->sonraki ne atanır. önceki nodeun bağını atlar ve "temp" düğümünü listeden çıkarır
            }
            free(temp);
            printf("%s isimli ogrenci silindi.\n", silinecekIsim);
            return;
        }
        onceki = temp;
        temp = temp->sonraki;
    }

    printf("Silinecek isim bulunamadi.\n");
}

// En uzun isimli öğrenciyi bulur ve ekrana yazdırır
void enUzunIsimliOgrenci() {
    struct Ogrenci* temp = ilkOgrenci;
    char enUzunIsim[50];
    int maxUzunluk = 0;

    while (temp != NULL) {
        int uzunluk = strlen(temp->isim);//tempin isim datasını uzunluga atayıp, if dongusune sokuyoruz. 
        if (uzunluk > maxUzunluk) { //uzunluk max uzunluktan büyükse max uzunluga atıyoruz.
            maxUzunluk = uzunluk;
            strcpy(enUzunIsim, temp->isim);
        }
        temp = temp->sonraki;//listede ilerliyoruz
    }

    printf("Listedeki en uzun isim: %s\n", enUzunIsim);
    printf("Uzunluk: %d\n", maxUzunluk);
}





int main() {
    int secim;
    char isim[50];

    while (1) { //sonsuz dongu
        printf("Yapmak istediginiz islemi secin:\n");
        printf("1. Ogrenci ekle\n");
        printf("2. Ogrenci listele ve say\n");
        printf("3. Ogrenci ara\n");
        printf("4. Ogrenci sil\n");
        printf("5. En uzun isimli ogrenciyi bul\n");
        printf("0. Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        switch (secim) { //fonksiyonlari cagiriyoruz.
            case 0:
                return 0;
            case 1:
                int numara,yas;
                printf("Ogrenci numarasi: ");
                scanf("%d", &numara);
                printf("Ogrenci ismi: ");
                scanf("%s", isim);
                printf("Ogrenci yas: ");
                scanf("%d", &yas);
                ogrenciEkle(numara, isim, yas);
                break;
            case 2:
                ogrenciListeleVeSay();
                break;
            case 3:
                printf("Aranacak isim: ");
                scanf("%s", isim);
                ogrenciAra(isim);
                break;
            case 4:
                printf("Silinecek isim: ");
                scanf("%s", isim);
                ogrenciSil(isim);
                break;
            case 5:
                enUzunIsimliOgrenci();
                break;
            default:
                printf("Gecersiz secim. Lutfen tekrar deneyin.\n");
        }
    }

    return 0;
}
