#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Ogrenci {
    int numara;
    char ad[50];
    int yas;
    struct Ogrenci* sonraki;
};

struct BagliListe {
    struct Ogrenci* bas;
};

struct BagliListe* BagliListeOlustur() {
    // Yeni bir ba�l� liste olu�turur ve d�nd�r�r.
    struct BagliListe* yeniListe = (struct BagliListe*)malloc(sizeof(struct BagliListe));
    yeniListe->bas = NULL;
    return yeniListe;
}

void BasaEkle(struct BagliListe* liste, int num, char ad[], int yas) {
    // Yeni bir ��renci d���m�n� listenin ba��na ekler.
    struct Ogrenci* yeniOgrenci = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    yeniOgrenci->numara = num;
    strcpy(yeniOgrenci->ad, ad);
    yeniOgrenci->yas = yas;
    yeniOgrenci->sonraki = liste->bas;
    liste->bas = yeniOgrenci;
}

void SonaEkle(struct BagliListe* liste, int num, char ad[], int yas) {
    // Yeni bir ��renci d���m�n� listenin sonuna ekler.
    struct Ogrenci* yeniOgrenci = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    yeniOgrenci->numara = num;
    strcpy(yeniOgrenci->ad, ad);
    yeniOgrenci->yas = yas;
    yeniOgrenci->sonraki = NULL;

    if (liste->bas == NULL) {
        liste->bas = yeniOgrenci;
    } else {
        struct Ogrenci* gecici = liste->bas;
        while (gecici->sonraki != NULL) {
            gecici = gecici->sonraki;
        }
        gecici->sonraki = yeniOgrenci;
    }
}

void ListeSiralama(struct BagliListe* liste) {
    // Ba�l� listeyi ��renci numaralar�na g�re s�ralar.
    struct Ogrenci* suanki = liste->bas;
    struct Ogrenci* sonrakiOgrenci;
    int degisti;

    if (suanki == NULL) {
        return;
    }

    do {
        degisti = 0;
        suanki = liste->bas;

        while (suanki->sonraki != NULL) {
            sonrakiOgrenci = suanki->sonraki;
            if (suanki->numara < sonrakiOgrenci->numara) {
                // ��renci d���mlerini yer de�i�tirir.
                int geciciNumara = suanki->numara;
                suanki->numara = sonrakiOgrenci->numara;
                sonrakiOgrenci->numara = geciciNumara;

                char geciciAd[50];
                strcpy(geciciAd, suanki->ad);
                strcpy(suanki->ad, sonrakiOgrenci->ad);
                strcpy(sonrakiOgrenci->ad, geciciAd);

                int geciciYas = suanki->yas;
                suanki->yas = sonrakiOgrenci->yas;
                sonrakiOgrenci->yas = geciciYas;

                degisti = 1;
            }
            suanki = suanki->sonraki;
        }
    } while (degisti);
}

void OgrenciBilgileriniYazdir(struct BagliListe* liste) {
    // Ba�l� listedeki ��renci bilgilerini ekrana yazd�r�r.
    struct Ogrenci* suanki = liste->bas;
    int sayac = 1;

    while (suanki != NULL) {
        printf("%d-%s %d %d\n", sayac, suanki->ad, suanki->yas, suanki->numara);
        suanki = suanki->sonraki;
        sayac++;
    }
}

void IsimleAra(struct BagliListe* liste, char ad[]) {
    // Verilen ��renci ad�n� arar ve bilgilerini ekrana yazd�r�r.
    struct Ogrenci* suanki = liste->bas;
    int bulundu = 0;

    while (suanki != NULL) {
        if (strcmp(suanki->ad, ad) == 0) {
            bulundu = 1;
            printf("%d-%s %d %d\n", bulundu, suanki->ad, suanki->yas, suanki->numara);
        }
        suanki = suanki->sonraki;
    }

    if (!bulundu) {
        printf("��renci bulunamad�.\n");
    }
}

void IsimleAraVeSonrakiDugumuSil(struct BagliListe* liste, char ad[]) {
    // Verilen ��renci ad�n� arar, bulunursa ilgili d���m� ve bir sonraki d���m� siler.
    struct Ogrenci* suanki = liste->bas;

    while (suanki != NULL && suanki->sonraki != NULL) {
        if (strcmp(suanki->ad, ad) == 0) {
            struct Ogrenci* gecici = suanki->sonraki;
            suanki->sonraki = gecici->sonraki;
            free(gecici);
            printf("�lgili ��renci ve bir sonraki d���m silindi.\n");
            return;
        }
        suanki = suanki->sonraki;
    }

    printf("��renci bulunamad� veya bir sonraki d���m yok.\n");
}

void EnUzunIsimliOgrenciyiYazdir(struct BagliListe* liste) {
    // Ba�l� listedeki en uzun isme sahip ��renciyi bulur ve ekrana yazd�r�r.
    struct Ogrenci* suanki = liste->bas;
    char enUzunIsim[50] = "";

    while (suanki != NULL) {
        if (strlen(suanki->ad) > strlen(enUzunIsim)) {
            strcpy(enUzunIsim, suanki->ad);
        }
        suanki = suanki->sonraki;
    }

    if (strlen(enUzunIsim) > 0) {
        printf("En uzun isimli ��renci: %s\n", enUzunIsim);
    } else {
        printf("��renci bulunamad�.\n");
    }
}

void TekSayilariBasaCiftSayilariSonaEkle(struct BagliListe* liste) {
    // Kullan�c�dan tek ve �ift say�lar� al�r, tekleri ba�a �iftleri sona ekler.
    int giris;
    do {
        printf("Say� girin (Bitirmek i�in -1 girin): ");
        scanf("%d", &giris);
        if (giris != -1) {
            if (giris % 2 == 1) {
                BasaEkle(liste, giris, "", 0);
            } else {
                SonaEkle(liste, giris, "", 0);
            }
        }
    } while (giris != -1);
}

void RastgeleSayilarOlusturVeSiralama(struct BagliListe* liste) {
    // Rastgele say�lar ekler ve listeyi s�ralar.
    int i;
    srand(time(NULL));
    for (i = 0; i < 100; i++) {
        int rastgeleNumara = rand() % 1000; // 0-999 aras� rastgele say�lar
        SonaEkle(liste, rastgeleNumara, "", 0);
    }
    ListeSiralama(liste);
}

int main() {
    struct BagliListe* ogrenciListesi = BagliListeOlustur();

    int secim;
    char ad[50];
    int num, yas;

    do {
        printf("\nOgrenci Bilgi Yonetimi Menusu:\n");
        printf("1. Tek Sayilari Basa, Cift Say�lar� Sona Ekle\n");
        printf("2. Rastgele Sayilar Ekleyip Sirala\n");
        printf("3. Ogrenci Ekle\n");
        printf("4. Listeyi S�rala ve Goruntule\n");
        printf("5. Tum Ogrenci Bilgilerini Goruntule\n");
        printf("6. �simle OGrenci Arama\n");
        printf("7. Isimle OGrenci Aray�p Bir Sonraki Dugumu Sil\n");
        printf("8. En Uzun �simli Ogrenciyi Goster\n");
        printf("0. Cikis\n");

        printf("Seciminizi girin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 3:
                printf("��renci Numaras�: ");
                scanf("%d", &num);
                printf("��renci �smi: ");
                scanf("%s", ad);
                printf("��renci Ya��: ");
                scanf("%d", &yas);
                BasaEkle(ogrenciListesi, num, ad, yas);
                
                break;
            case 4:
                ListeSiralama(ogrenciListesi);
                printf("S�ralanm�� ��renci Listesi:\n");
                OgrenciBilgileriniYazdir(ogrenciListesi);
                break;
            case 5:
                printf("T�m ��renci Bilgileri:\n");
                OgrenciBilgileriniYazdir(ogrenciListesi);
                break;
            case 6:
                printf("Aramak istedi�iniz ��renci ad�n� girin: ");
                scanf("%s", ad);
                IsimleAra(ogrenciListesi, ad);
                break;
            case 7:
                printf("Silmek istedi�iniz ��renci ad�n� girin: ");
                scanf("%s", ad);
                IsimleAraVeSonrakiDugumuSil(ogrenciListesi, ad);
                break;
            case 8:
                EnUzunIsimliOgrenciyiYazdir(ogrenciListesi);
                break;
            case 1:
                TekSayilariBasaCiftSayilariSonaEkle(ogrenciListesi);
                break;
            case 2:
                RastgeleSayilarOlusturVeSiralama(ogrenciListesi);
                printf("S�ralanm�� Rastgele Say�lar:\n");
                OgrenciBilgileriniYazdir(ogrenciListesi);
                break;
            case 0:
                printf("��k�� yap�l�yor...\n");
                break;
            default:
                printf("Ge�ersiz se�im. Tekrar deneyin.\n");
        }
    } while (secim != 0);

    // Belle�i temizle
    while (ogrenciListesi->bas != NULL) {
        struct Ogrenci* gecici = ogrenciListesi->bas;
        ogrenciListesi->bas = ogrenciListesi->bas->sonraki;
        free(gecici);
    }

    free(ogrenciListesi);

    return 0;
}

