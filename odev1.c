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
    // Yeni bir baðlý liste oluþturur ve döndürür.
    struct BagliListe* yeniListe = (struct BagliListe*)malloc(sizeof(struct BagliListe));
    yeniListe->bas = NULL;
    return yeniListe;
}

void BasaEkle(struct BagliListe* liste, int num, char ad[], int yas) {
    // Yeni bir öðrenci düðümünü listenin baþýna ekler.
    struct Ogrenci* yeniOgrenci = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    yeniOgrenci->numara = num;
    strcpy(yeniOgrenci->ad, ad);
    yeniOgrenci->yas = yas;
    yeniOgrenci->sonraki = liste->bas;
    liste->bas = yeniOgrenci;
}

void SonaEkle(struct BagliListe* liste, int num, char ad[], int yas) {
    // Yeni bir öðrenci düðümünü listenin sonuna ekler.
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
    // Baðlý listeyi öðrenci numaralarýna göre sýralar.
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
                // Öðrenci düðümlerini yer deðiþtirir.
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
    // Baðlý listedeki öðrenci bilgilerini ekrana yazdýrýr.
    struct Ogrenci* suanki = liste->bas;
    int sayac = 1;

    while (suanki != NULL) {
        printf("%d-%s %d %d\n", sayac, suanki->ad, suanki->yas, suanki->numara);
        suanki = suanki->sonraki;
        sayac++;
    }
}

void IsimleAra(struct BagliListe* liste, char ad[]) {
    // Verilen öðrenci adýný arar ve bilgilerini ekrana yazdýrýr.
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
        printf("Öðrenci bulunamadý.\n");
    }
}

void IsimleAraVeSonrakiDugumuSil(struct BagliListe* liste, char ad[]) {
    // Verilen öðrenci adýný arar, bulunursa ilgili düðümü ve bir sonraki düðümü siler.
    struct Ogrenci* suanki = liste->bas;

    while (suanki != NULL && suanki->sonraki != NULL) {
        if (strcmp(suanki->ad, ad) == 0) {
            struct Ogrenci* gecici = suanki->sonraki;
            suanki->sonraki = gecici->sonraki;
            free(gecici);
            printf("Ýlgili öðrenci ve bir sonraki düðüm silindi.\n");
            return;
        }
        suanki = suanki->sonraki;
    }

    printf("Öðrenci bulunamadý veya bir sonraki düðüm yok.\n");
}

void EnUzunIsimliOgrenciyiYazdir(struct BagliListe* liste) {
    // Baðlý listedeki en uzun isme sahip öðrenciyi bulur ve ekrana yazdýrýr.
    struct Ogrenci* suanki = liste->bas;
    char enUzunIsim[50] = "";

    while (suanki != NULL) {
        if (strlen(suanki->ad) > strlen(enUzunIsim)) {
            strcpy(enUzunIsim, suanki->ad);
        }
        suanki = suanki->sonraki;
    }

    if (strlen(enUzunIsim) > 0) {
        printf("En uzun isimli öðrenci: %s\n", enUzunIsim);
    } else {
        printf("Öðrenci bulunamadý.\n");
    }
}

void TekSayilariBasaCiftSayilariSonaEkle(struct BagliListe* liste) {
    // Kullanýcýdan tek ve çift sayýlarý alýr, tekleri baþa çiftleri sona ekler.
    int giris;
    do {
        printf("Sayý girin (Bitirmek için -1 girin): ");
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
    // Rastgele sayýlar ekler ve listeyi sýralar.
    int i;
    srand(time(NULL));
    for (i = 0; i < 100; i++) {
        int rastgeleNumara = rand() % 1000; // 0-999 arasý rastgele sayýlar
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
        printf("1. Tek Sayilari Basa, Cift Sayýlarý Sona Ekle\n");
        printf("2. Rastgele Sayilar Ekleyip Sirala\n");
        printf("3. Ogrenci Ekle\n");
        printf("4. Listeyi Sýrala ve Goruntule\n");
        printf("5. Tum Ogrenci Bilgilerini Goruntule\n");
        printf("6. Ýsimle OGrenci Arama\n");
        printf("7. Isimle OGrenci Arayýp Bir Sonraki Dugumu Sil\n");
        printf("8. En Uzun Ýsimli Ogrenciyi Goster\n");
        printf("0. Cikis\n");

        printf("Seciminizi girin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 3:
                printf("Öðrenci Numarasý: ");
                scanf("%d", &num);
                printf("Öðrenci Ýsmi: ");
                scanf("%s", ad);
                printf("Öðrenci Yaþý: ");
                scanf("%d", &yas);
                BasaEkle(ogrenciListesi, num, ad, yas);
                
                break;
            case 4:
                ListeSiralama(ogrenciListesi);
                printf("Sýralanmýþ Öðrenci Listesi:\n");
                OgrenciBilgileriniYazdir(ogrenciListesi);
                break;
            case 5:
                printf("Tüm Öðrenci Bilgileri:\n");
                OgrenciBilgileriniYazdir(ogrenciListesi);
                break;
            case 6:
                printf("Aramak istediðiniz öðrenci adýný girin: ");
                scanf("%s", ad);
                IsimleAra(ogrenciListesi, ad);
                break;
            case 7:
                printf("Silmek istediðiniz öðrenci adýný girin: ");
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
                printf("Sýralanmýþ Rastgele Sayýlar:\n");
                OgrenciBilgileriniYazdir(ogrenciListesi);
                break;
            case 0:
                printf("Çýkýþ yapýlýyor...\n");
                break;
            default:
                printf("Geçersiz seçim. Tekrar deneyin.\n");
        }
    } while (secim != 0);

    // Belleði temizle
    while (ogrenciListesi->bas != NULL) {
        struct Ogrenci* gecici = ogrenciListesi->bas;
        ogrenciListesi->bas = ogrenciListesi->bas->sonraki;
        free(gecici);
    }

    free(ogrenciListesi);

    return 0;
}

