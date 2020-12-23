#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

int sifre_database[50], hesapNo_database[50], sifre, islem, sifre_giris, a = 1, ay, hesapNo, i, j, k, secim, b = 1, c = 0, x, y, fatura;
float para_database[50], borc_database[50], dolar_database[50], euro_database[50], para;
char musteri_database[50][50], ad[30], soyad[30], ad_giris[30], soyad_giris[30], telno[10], kayitlifaturalar[50][50], faturano[6], sigorta_database[50][50], saglik_sigorta[11], arac_sigorta[10], mahalle[20], ilce[20];
FILE *database, *fatura_eski, *sigorta_eski;

int main(void);
void islem_menu(int i, int index);

void database_log(int index)
{
    database = fopen("database.txt", "w");
    for (j = 0; j < index - 1; j++)
    {
        fprintf(database, "%s %d %.1f %.1f %.1f %.1f %d\n", musteri_database[j], sifre_database[j], para_database[j], borc_database[j], dolar_database[j], euro_database[j], hesapNo_database[j]);
    }
    fclose(database);
}

void hesap_ac()
{
    database = fopen("database.txt", "a");
    printf("Musterinin Ad ve Soyadini Giriniz: \n");
    scanf("%s %s", &ad, &soyad);
    strcat(ad, soyad);
    printf("Hesabiniz Icin 4-6 Haneli PIN Kodu Olusturun: \n");
    while (1)
    {
        scanf("%d", &sifre);
        if (sifre >= 1000 && sifre <= 999999)
        {
            break;
        }
        else
        {
            printf("Lutfen Sifir(0) Ile Baslamayan, 4 ila 6 Haneli ve Sadece Rakamlardan Olusan Bir Sifre Olusturunuz \n");
        }
    }
    hesapNo = 10000 + rand();
    strupr(ad);
    fprintf(database, "%s %d 0.0 0.0 0.0 0.0 %d\n", ad, sifre, hesapNo);
    fclose(database);
    printf("Hesabiniz Basari Ile Olusturulmustur\n\n");
    sleep(1);
    system("cls");
}

void para_yatir(int i, int index)
{
    printf("0.Ust Menu\nYatirmak Istediginiz Tutari Giriniz (Tek Seferde 10 - 5.000.000 TL Araliginda Para Yatirabilirsiniz)! ): \n");
    while (1)
    {
        scanf("%f", &para);
        if (para == 0)
        {
            islem_menu(i, index);
        }
        else if (para >= 10 && para <= 5000000)
        {
            para_database[i] += para;
            database_log(index);
            printf("Para Yatirma Isleminiz Basariyla Gerceklestirildi");
            islem_menu(i, index);
        }
        else
        {
            printf("!!!Tek Seferde En AZ 10 TL ve En Fazla 5.000.000 TL Yatirabilirsiniz!!!\n");
        }
    }
}

void para_cek(int i, int index)
{
    printf("9.Ust Menu \nCekmek Istediginiz Tutari Giriniz (Tek Seferde 10 - 5.000TL Araliginda Para Cekebilirisniz)! ): \n");
    while (1)
    {
        scanf("%f", &para);
        if (para == 9)
        {
            para = 0;
            islem_menu(i, index);
        }
        else if (para >= 10 && para <= 5000)
        {
            if (para_database[i] < para)
            {
                printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
            }
            else
            {
                para_database[i] -= para;

                database_log(index);
                printf("Para Cekme Isleminiz Basariyla Gerceklestirilmistir");
                islem_menu(i, index);
            }
        }
        else
        {
            printf("!!! Tek Seferde En Az 10 TL En Fazla 5000 TL Para Cekebilirsiniz!!!\n");
        }
    }
}

void kredi_cek(int i, int index)
{
    printf("9.Ust Menu \nYillik Faiz Orani: %%20\nCekmek Istediginiz Kredi Tutarini Giriniz (1.000 - 500.000 TL Araliginda Kredi Cekebilirsiniz): \n");
    while (1)
    {
        scanf("%f", &para);
        if (para == 9)
        {
            islem_menu(i, index);
        }
        else if (para >= 1000 && para <= 5000000)
        {
            borc_database[i] += para * 1.2;
            para_database[i] += para;
            printf("Vade Miktarini Seciniz. (12 ila 120 Ay Vade Secenekleri Mevcuttur)\n");
            while (1)
            {
                scanf("%d", &ay);
                if (ay >= 12 && ay <= 120)
                {
                    printf("%.1fTL Olan Krediniz %d Ayin Sonunda %.1fTL ve Ayda %.1fTL Olarak Taksitlendirilmistir.", para, ay, para * 1.2, (para * 1.2) / ay);
                    sleep(2);
                    islem_menu(i, index);
                }
                else
                {
                    printf("!!!En Az 12 Ay En Fazla 120 Ay Vade Secebilirsiniz!!!\n");
                }
            }

            database_log(index);
            break;
        }
        else
        {
            printf("!!! En Az 1000TL En Fazla 500.000TL Kredi Talebinde Bulunabilirsiniz !!!\n");
        }
    }
}

void borc_ode(int i, int index)
{
    a = 1;
    printf("9.Ust Menu\nYatirmak Istediginiz Borc Miktarini Giriniz: \n");
    while (1)
    {
        scanf("%f", &para);
        if (para == 9)
        {
            para = 0;
            a = 0;
            islem_menu(i, index);
        }
        else if (para_database[i] < para)
        {
            printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
            printf("9.Ust Menu \nOdemek Istediginiz Borc Miktarini Giriniz: \n");
            a = 1;
        }
        else if (para <= 0)
        {
            printf("!!! 0 ya da Daha Az Tutar Giremezsiniz !!!\n");
            a = 1;
        }
        else
        {
            a = 1;
            break;
        }
    }
    while (a == 1)
    {
        if (para > borc_database[i])
        {
            printf("Guncel Borc Miktari %.1fTL dir. Varolan Borcunuzun Tamamini Odemek Ister Misiniz?\n1.Evet\n2.Hayir\n", borc_database[i]);
            scanf("%d", &islem);
            if (islem == 1)
            {
                para_database[i] -= borc_database[i];
                borc_database[i] = 0;
                database_log(index);
                printf("Borc Odeme Isleminiz Basariyla Gerceklestirilmistir\n");
                sleep(1);
                break;
            }
            if (islem == 2)
            {
                islem_menu(i, index);
            }
        }
        else
        {
            borc_database[i] -= para;
            para_database[i] -= para;
            database_log(index);
            printf("Borc Odeme Isleminiz Basariyla Gerceklestirilmistir\n");
            islem_menu(i, index);
        }
    }
}

void para_gonder(int i, int index)
{
    if (para_database[i] <= 0)
    {
        printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
        sleep(1);
        islem_menu(i, index);
    }
    b = 1;
    for (j = 0; j < index - 1; j++)
    {

        if (i == j)
        {
        }
        else if (musteri_database[j][0] == '0')
        {
        }
        else
        {
            printf("\n %s %d\n", musteri_database[j], hesapNo_database[j]);
            c++;
        }
    }
    if (c == 0)
    {
        printf("Para Gonderilecek Bir Hesap Bulunamadi\n");
        sleep(1);
        islem_menu(i, index);
    }
    printf("0.Ust Menu\nPara Gondermek Istediginiz Hesap Numarasini Giriniz: \n");
    while (1)
    {
        scanf("%d", &islem);
        if (islem == 0)
        {
            b = 0;
            islem_menu(i, index);
        }
        for (k = 0; k < index - 1; k++)
        {
            if (hesapNo_database[k] == islem)
            {
                a = 1;
                break;
            }
        }
        if (a == 1)
        {
            break;
        }
        else
        {
            printf("9.Ust Menu\nGirdiginiz Hesap Numarasina Tanimli Hesap Bulunamadi! Lutfen Kontrol Edip Yeniden Deneyiniz: \n");
        }
    }
    printf("0.Ust Menu\nGondermek Istediginiz Tutari Giriniz: \n");
    while (b == 1)
    {
        scanf("%f", &para);
        if (para == 0)
        {
            islem_menu(i, index);
        }
        else if (para_database[i] < para)
        {
            printf("0.Ust Menu\nHesabinizda Yeterli Bakiye Bulunmamaktadir! Lutfen Tutari Kontrol Edip Yeniden Deneyiniz: \n");
        }
        else
        {
            break;
        }
    }

    for (j = 0; j < index - 1; j++)
    {

        if (islem == hesapNo_database[j])
        {
            para_database[j] += para;
            para_database[i] -= para;
            database_log(index);
            printf("Para Gonderiliyor Lutfen Bekleyiniz...\n");
            sleep(2);
            printf("Para Gonderme Isleminiz Basariyla Gerceklestirildi\n\n");
            sleep(1);
            system("cls");
            break;
        }
    }
}

void doviz_sat(int i, int index)
{
    printf("\n1.Dolar: 7.63\n2.Euro: 9.35\n9.Ust Menu\nIslem Yapmak Istediginiz Para Birimini Seciniz: \n");
    scanf("%d", &islem);
    if (islem != 1 && islem != 2 && islem != 9)
    {
        printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
        doviz_sat(i, index);
    }
    else if (islem == 9)
    {
        islem_menu(i, index);
    }

    else
    {
        while (1)
        {

            if (islem == 1)
            {

                if (dolar_database[i] == 0)
                {
                    printf("Hesabinizda Dolar Bakiyeniz Bulunmamaktadir\n"); 
                    sleep(1);
                    doviz_sat(i, index);
                }

                printf("Bozdurmak Istediginiz Dolar Miktarini Giriniz: \n");
                scanf("%f", &para);

                if (para > dolar_database[i])
                {

                    printf("Hesabinizda Yeterli Dolar Bakiyesi Bulunmamaktadir. Lutfen Girdiginiz Tutari Kontrol Ediniz\n");
                    sleep(1);
                }

                else
                {
                    dolar_database[i] -= para;
                    para_database[i] += (para * 7.63);
                    break;
                }
            }

            else if (islem == 2)
            {

                if (euro_database[i] == 0)
                {
                    printf("Hesabinizda Euro Bakiyeniz Bulunmamaktadir\n");
                    sleep(1);
                    doviz_sat(i, index);
                }
                printf("Bozdurmak Istediginiz Euro Miktarini Giriniz: \n");
                scanf("%f", &para);

                if (para > euro_database[i])
                {

                    printf("Hesabinizda Yeterli Euro Bakiyesi Bulunmamaktadir. Lutfen Girdiginiz Tutari Kontrol Ediniz\n");
                    sleep(1);
                }

                else
                {
                    euro_database[i] -= para;
                    para_database[i] += (para * 7.63);
                    break;
                }
            }
        }
        database_log(index);
        printf("Doviz Isleminiz Basariyla Gerceklestirilmistir");
        islem_menu(i, index);
    }
}

void doviz_al(int i, int index)
{
    a = 0;
    while (a == 0)
    {
        scanf("%d", &islem);
        if (islem == 1)
        {
            printf("Satin Almak Istediginiz Dolar Miktarini Giriniz: \n");
            while (1)
            {
                scanf("%f", &para);
                if (para_database[i] < (para * (7.63)))
                {
                    printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
                }
                else
                {
                    para_database[i] -= para * (7.63);
                    dolar_database[i] += para;
                    database_log(index);
                    printf("Doviz Isleminiz Basariyla Gerceklestirilmistir");
                    a = 1;
                    islem_menu(i, index);
                }
            }
        }
        else if (islem == 2)
        {
            printf("Satin Almak Istediginiz Euro Miktarini Giriniz: \n");
            while (1)
            {
                scanf("%f", &para);
                if (para_database[i] < (para * (9.35)))
                {
                    printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir.\n");
                }
                else
                {
                    para_database[i] -= para * (9.35);
                    euro_database[i] += para;
                    database_log(index);
                    printf("Doviz Isleminiz Basariyla Gerceklestirilmistir");
                    a = 1;
                    islem_menu(i, index);
                }
            }
        }
        else if (islem == 9)
        {
            islem_menu(i, index);
        }
        else
        {
            printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
        }
    }
}

void fatura_ode(int i, int index)
{
    k = 0;
    b = 1;
    fatura_eski = fopen("fatura_eski.txt", "a");
    fclose(fatura_eski);
    fatura_eski = fopen("fatura_eski.txt", "r");
    while (!feof(fatura_eski))
    {
        fscanf(fatura_eski, "%s", &kayitlifaturalar[k]);
        k++;
    }
    fclose(fatura_eski);
    printf("\n1.Telefon \n2.Internet//Elektrik//Su//Dogalgaz\n3.Ust Menu\n");
    while (1)
    {
        scanf("%d", &islem);
        if (islem == 1)
        {
            printf("Telefon Numarasini Basinda Sifir(0) Olmadan 10 Haneli Olarak Giriniz\n");
            while (1)
            {
                scanf("%s", &telno);
                for (j = 0; j < k; j++)
                {
                    if (strcmp(kayitlifaturalar[j], telno) == 0)
                    {
                        b = 0;
                        break;
                    }
                }
                if ( telno[0] == '1' && strlen(telno) == 1)
                {
                    islem_menu(i, index);
                }
                else if (telno[0] == '0')
                {
                    printf("1.Ana Menu\nLutfen Telefon Numaranizi Basinda Sifir(0) Olmadan Giriniz\n");
                }
                else if (strlen(telno) == 10)
                {
                    if (b == 0)
                    {
                        printf("Girmis Oldugunuz Numaraya Ait Odenecek Fatura Bilgisi Bulunmamaktadir\n");
                        sleep(1);
                        islem_menu(i, index);
                    }
                    else
                    {
                        fatura = rand() % 80 + 20;
                        printf("%s No'lu Hattinizin %d TL Odemesi Bulunmaktadir\n1.Ode\n2.Ana Menu\n", telno, fatura);
                        while (1)
                        {
                            scanf("%d", &secim);
                            if (secim == 1)
                            {
                                if (para_database[i] < fatura)
                                {
                                    printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
                                    sleep(1);
                                    islem_menu(i, index);
                                }
                                else
                                {
                                    fatura_eski = fopen("fatura_eski.txt", "a");
                                    printf("Odeme Isleminiz Gerceklestiriliyor...\n");
                                    para_database[i] -= fatura;
                                    fprintf(fatura_eski, "%s\n", telno);
                                    fclose(fatura_eski);
                                    sleep(1);
                                    printf("Fatura Odeme Isleminiz Basariyla Gerceklestirilmistir\n");
                                    sleep(1);
                                    islem_menu(i, index);
                                }
                            }
                            else if (secim == 2)
                            {
                                islem_menu(i, index);
                            }
                            else
                            {
                                printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayin\n");
                            }
                        }
                    }
                }
                else
                {
                    printf("1.Ana Menu\nLutfen Telefon Numaranizi 10 Haneli Olacak Sekilde Giriniz\n");
                }
            }
        }
        else if (islem == 2)
        {
            printf("0.Ana Menu\nFaturanizda Bulunan 6 Haneli Musteri Numaranizi Giriniz (Orn:A12345, B54321): \n");
            while (1)
            {
                scanf("%s", &faturano);
                for (j = 0; j < k; j++)
                {
                    if (strcmp(kayitlifaturalar[j], faturano) == 0)
                    {
                        b = 0;
                        break;
                    }
                }
                if (faturano[0] == '0' && strlen(faturano) == 1)
                {
                    islem_menu(i, index);
                }
                else if (strlen(faturano) != 6 || !(faturano[1] >= '0' && faturano[1] <= '9') || !(faturano[2] >= '0' && faturano[2] <= '9') || !(faturano[3] >= '0' && faturano[3] <= '9') || !(faturano[4] >= '0' && faturano[4] <= '9') || !(faturano[5] >= '0' && faturano[5] <= '9'))
                {
                    printf("0.Ana Menu\nMusteri Numaranizi 1 Buyuk Harf ve 5 Adet Rakamdam Olusacak Sekilde Giriniz\n");
                }
                else if (!(faturano[0] >= 'A' && faturano[0] <= 'Z') )
                {
                    printf("0.Ana Menu\nMusteri Numaranizi Ilk Hanesi Buyuk Harfle (A-Z) Baslayacak Sekilde Giriniz\n");
                }
                else
                {
                    if (b == 0)
                    {
                        printf("Girmis Oldugunuz Musteri Numarasina Ait Donem Borcu Bulunmamaktadir\n");
                        sleep(1);
                        islem_menu(i, index);
                    }
                    fatura = rand() % 200 + 50;
                    printf("%s Musteri Numarasina Ait %d TL Donem Borcu Bulunmaktadir\n1.Ode\n2.Ana Menu\n", faturano, fatura);
                    while (1)
                    {
                        scanf("%d", &secim);
                        if (secim == 1)
                        {
                            if (para_database[i] < fatura)
                            {
                                printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
                                sleep(1);
                                islem_menu(i, index);
                            }
                            else
                            {
                                fatura_eski = fopen("fatura_eski.txt", "a");
                                printf("Faturaniz Odeniyor...\n");
                                para_database[i] -= fatura;
                                fprintf(fatura_eski, "%s\n", faturano);
                                fclose(fatura_eski);
                                sleep(1);
                                printf("Fatura Odeme Isleminiz Basariyla Gerceklestirilmistir\n");
                                sleep(1);
                                islem_menu(i, index);
                            }
                        }
                        else if (secim == 2)
                        {
                            islem_menu(i, index);
                        }
                        else
                        {
                            printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                        }
                    }
                }
            }
        }
        else if (islem == 3)
        {
            islem_menu(i, index);
        }
        else
        {
            printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
        }
    }
}

void sigorta_islem(int i, int index)
{
    k = 0;
    sigorta_eski = fopen("sigorta_eski.txt", "a");
    fclose(sigorta_eski);
    sigorta_eski = fopen("sigorta_eski.txt", "r");
    while (!feof(sigorta_eski))
    {
        fscanf(sigorta_eski, "%s", &sigorta_database[k]);
        k++;
    }
    fclose(sigorta_eski);
    printf("\n1.Arac Sigortasi\n2.Konut Sigortasi\n3.Saglik Sigortasi\n4.Ana Menu\n");
    while (1)
    {
        scanf("%d", &secim);
        if (secim == 1)
        {
            printf("0.Ana Menu\nAracinizin Plakasini Aralarinda Bosluk Olmadan Giriniz\n");
            while (1)
            {
                scanf("%s", &arac_sigorta);
                strupr(arac_sigorta);
                x = strlen(arac_sigorta) - 1;
                for (j = 0; j < k; j++)
                {
                    if (strcmp(sigorta_database[j], arac_sigorta) == 0)
                    {
                        printf("Girmis Oldugunuz Araca Ait Sigortalama Islemi Daha Onceden Yapilmistir\n");
                        sleep(2);
                        islem_menu(i, index);
                    }
                }

                if (arac_sigorta[0] == '0' && strlen(arac_sigorta) == 1)
                {
                    islem_menu(i, index);
                }

                else
                {
                    if (strlen(arac_sigorta) < 5)
                    {
                        printf("0.Ana Menu\nArac Plakanizi En Az 5 Haneli Olacak Sekilde Giriniz\n"); 
                    }
                    else if (!(arac_sigorta[0] >= '0' && arac_sigorta[0] <= '9') || !(arac_sigorta[1] >= '0' && arac_sigorta[1] <= '9'))
                    {
                        printf("0.Ana Menu\nArac Plakanizin Ilk 2 Hanesi Il Kodunuz Olacak Sekilde Giriniz\n");
                    }
                    else if ((arac_sigorta[2] >= '0' && arac_sigorta[2] <= '9') || (arac_sigorta[0] > '8') || (arac_sigorta[0] == '8' && arac_sigorta[1] > '1'))
                    {
                        printf("0.Ana Menu\nGireceginiz Il Kodu En Fazla 81 Olmalidir. Lutfen Il Kodunuzu Kontrol Ediniz\n");
                    }
                    else if (!(arac_sigorta[x] >= '0' && arac_sigorta[x] <= '9') || !(arac_sigorta[x - 1] >= '0' && arac_sigorta[x - 1] <= '9'))
                    {
                        printf("0.Ana Menu\nArac Plakanizin Son 2 Hanesi Harf Bulunduramaz. Lutfen Kontrol Ediniz\n");
                    }
                    else if ((arac_sigorta[5] >= 'a' && arac_sigorta[5] <= 'z') || (arac_sigorta[5] >= 'A' && arac_sigorta[5] <= 'Z'))
                    {
                        printf("0.Ana Menu\nArac Plakanizin Harf Kismi En Fazla 3 Karakterden Olusabilir. Lutfen Kontrol Ediniz\n");
                    }
                    else if ((arac_sigorta[x - 1] >= 'a' && arac_sigorta[x - 1] <= 'z') || (arac_sigorta[x - 1] >= 'A' && arac_sigorta[x - 1] <= 'Z'))
                    {
                        printf("0.Ana Menu\nArac Plakanizin Sondaki Sayi Kismi 2 il 4 Haneli Olmalidir. Lutfen Kontrol Ediniz\n");
                    }
                    else if ((arac_sigorta[x - 4] >= '0' && arac_sigorta[x - 4] <= '9') && strlen(arac_sigorta) > 6)
                    {
                        printf("0.Ana Menu\nArac Plakanizin Sondaki Sayi Kismi En Fazla 4 Haneli Olabilir. Lutfen Kontrol Ediniz\n");
                    }
                    else if (strlen(arac_sigorta) > 9)
                    {
                        printf("0.Ana Menu\nArac Plakanizi En Fazla 9 Haneli Olarak Girebilirsiniz. Lutfen Kontrol Ediniz\n");
                    }
                    else
                    {
                        fatura = rand() % 500 + 500;
                        printf("Aracinizin Yillik Sigorta Bedeli: %dTL 'dir\n1.Ode\n2.Ana Menu\n");
                        while (1)
                        {
                            scanf("%d", &islem);
                            if (islem == 1)
                            {
                                if (para_database[i] < fatura)
                                {
                                    printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
                                    sleep(2);
                                    islem_menu(i, index);
                                }
                                else
                                {
                                    printf("Odemeniz Yapiliyor...\n");
                                    sigorta_eski = fopen("sigorta_eski.txt", "a");
                                    para_database[i] -= fatura;
                                    fprintf(sigorta_eski, "%s\n", arac_sigorta);
                                    fclose(sigorta_eski);
                                    sleep(1);
                                    printf("Sigorta Isleminiz Basariyla Gerceklestirilmistir\n");
                                    sleep(1);
                                    islem_menu(i, index);
                                }
                            }
                            else if (islem == 2)
                            {
                                islem_menu(i, index);
                            }
                            else
                            {
                                printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                            }
                        }
                    }
                }
            }
        }
        else if (secim == 2)
        {
            printf("0.Ana Menu\nMulkunuzun Bulundugu Ilceyi Yaziniz:\n");
            scanf("%s", &ilce);
            if (ilce[0] == '0' && strlen(ilce) == 1)
            {
                islem_menu(i, index);
            }
            printf("0.Ana Menu\nMulkunuzun Bulundugu Mahalleyi Yaziniz: \n");
            scanf("%s", &mahalle);
            strupr(ilce);
            strupr(mahalle);
            strcat(ilce, mahalle);
            for (j = 0; j < k; j++)
            {
                if (strcmp(sigorta_database[j], ilce) == 0)
                {
                    printf("Bu Adresteki Mulkunuze Ait Sigorta Bulunmaktadir.\n");
                    sleep(2);
                    islem_menu(i, index);
                }
            }
            if (mahalle[0] == '0' && strlen(mahalle) == 1)
            {
                islem_menu(i, index);
            }
            else
            {
                fatura = rand() % 500 + 500;
                printf("Mulkunuzun Yillik Sigorta Bedeli: %dTL 'dir\n1.Ode\n2.Ana Menu\n");
                while (1)
                {
                    scanf("%d", &islem);
                    if (islem == 1)
                    {
                        if (para_database[i] < fatura)
                        {
                            printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
                            sleep(2);
                            islem_menu(i, index);
                        }
                        else
                        {
                            printf("Odemeniz Gerceklestiriliyor...\n");
                            sigorta_eski = fopen("sigorta_eski.txt", "a");
                            para_database[i] -= fatura;
                            fprintf(sigorta_eski, "%s\n", ilce);
                            fclose(sigorta_eski);
                            sleep(1);
                            printf("Sigorta Isleminiz Basariyla Gerceklestirilmistir\n");
                            sleep(1);
                            islem_menu(i, index);
                        }
                    }
                    else if (islem == 2)
                    {
                        islem_menu(i, index);
                    }
                    else
                    {
                        printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                    }
                }
            }
        }
        else if (secim == 3)
        {
            printf("0.Ana Menu\nSaglik Sigortaniz Icin 11 Haneli T.C. Kimlik Numaranizi Giriniz:\n");
            while (1)
            {
                a = 1;
                scanf("%s", &saglik_sigorta);
                for (j = 0; j < k; j++)
                {
                    if (strcmp(sigorta_database[j], saglik_sigorta) == 0)
                    {
                        printf("Bu Kisiye Ait Saglik Sigortasi Bulunmaktadir\n");
                        sleep(2);
                        islem_menu(i, index);
                    }
                }
                if (saglik_sigorta[0] == '0' && strlen(saglik_sigorta) == 1)
                {
                    islem_menu(i, index);
                }
                else if (strlen(saglik_sigorta) != 11)
                {
                    printf("0.Ana Menu\nT.C. Kimlik Numaraniz 11 Haneden Az Olamaz. Lutfen Kontrol Ediniz\n");
                }
                else if (!(saglik_sigorta[0] >= '0' && saglik_sigorta[0] <= '9') || !(saglik_sigorta[1] >= '0' && saglik_sigorta[1] <= '9') || !(saglik_sigorta[2] >= '0' && saglik_sigorta[2] <= '9') || !(saglik_sigorta[3] >= '0' && saglik_sigorta[3] <= '9') || !(saglik_sigorta[4] >= '0' && saglik_sigorta[4] <= '9') || !(saglik_sigorta[5] >= '0' && saglik_sigorta[5] <= '9') || !(saglik_sigorta[6] >= '0' && saglik_sigorta[6] <= '9') || !(saglik_sigorta[7] >= '0' && saglik_sigorta[7] <= '9') || !(saglik_sigorta[8] >= '0' && saglik_sigorta[8] <= '9') || !(saglik_sigorta[9] >= '0' && saglik_sigorta[9] <= '9') || !(saglik_sigorta[10] >= '0' && saglik_sigorta[10] <= '9'))
                {
                    printf("0.Ana Menu\nT.C. Kimlik Numaraniz Harf Iceremez. Lutfen Kontrol Ediniz\n");
                }
                else
                {
                    fatura = rand() % 500 + 500;
                    printf("Yillik Saglik Sigortasi Bedeli: %dTL 'dir\n1.Ode\n2.Ana Menu\n");
                    while (1)
                    {
                        scanf("%d", &islem);
                        if (islem == 1)
                        {
                            if (para_database[i] < fatura)
                            {
                                printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
                                sleep(2);
                                islem_menu(i, index);
                            }
                            else
                            {
                                printf("Odemeniz Gerceklestiriliyor...\n");
                                sigorta_eski = fopen("sigorta_eski.txt", "a");
                                para_database[i] -= fatura;
                                fprintf(sigorta_eski, "%s\n", saglik_sigorta);
                                fclose(sigorta_eski);
                                sleep(1);
                                printf("Sigorta Isleminiz Basariyla Gerceklestirildi\n");
                                sleep(1);
                                islem_menu(i, index);
                            }
                        }
                        else if (islem == 2)
                        {
                            islem_menu(i, index);
                        }
                        else
                        {
                            printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                        }
                    }
                }
            }
        }
        else if (secim == 4)
        {
            islem_menu(i, index);
        }
        else
        {
            printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
        }
    }
}

void islem_menu(int i, int index)
{
    printf("\nAna Menuye Donuluyor...\n\n");
    sleep(1);
    database_log(index);
    system("cls");
    while (1)
    {
        printf("Mevcut Bakiyeniz: \nTurk Lirasi: %.1f\nDolar: %.1f\nEuro: %.1f\n", para_database[i], dolar_database[i], euro_database[i]);
        printf("Guncel Borcunuz: %.1fTL\n", borc_database[i]);
        printf("\n1.Para Yatirma/Para Cekme\n2.Para Gonderme\n3.Kredi Cekme\n4.Borc Odeme\n5.Doviz Islemleri\n6.Fatura Odeme\n7.Sigorta Islemleri\n8.Cikis\nLutfen Yapmak Istediginiz Islem Numarasini Tuslayiniz: \n");
        scanf("%d", &islem);
        if (islem == 1)
        {
            printf("\n1.Para Yatirma\n2.Para Cekme\n3.Ana Menu\n");
            while (1)
            {
                scanf("%d", &secim);
                if (secim == 1)
                {
                    para_yatir(i, index);
                }
                else if (secim == 2)
                {
                    if (para_database[i] <= 0)
                    {
                        printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
                        sleep(1);
                        printf("Hesabiniza Para Yatirmak Ister Misiniz ?\n1.Evet\n2.Hayir\n");
                        while (1)
                        {
                            scanf("%d", &x);
                            if (x == 1)
                            {
                                printf("Para Yatirma Ekranina Yonlendiliyorsunuz...\n");
                                sleep(1);
                                para_yatir(i, index);
                            }
                            else if (x == 2)
                            {
                                islem_menu(i, index);
                            }
                            else
                            {
                                printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                            }
                        }
                    }
                    else
                    {
                        para_cek(i, index);
                    }
                }
                else if (secim == 3)
                {
                    islem_menu(i, index);
                }
                else
                {
                    printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                }
            }
        }
        else if (islem == 2)
        {
            para_gonder(i, index);
        }

        else if (islem == 3)
        {
            kredi_cek(i, index);
        }
        else if (islem == 4)
        {
            if (borc_database[i] == 0)
            {
                printf("Odenecek Borcunuz Bulunmamaktadir\n\n");
                sleep(1);
                printf("Size Ozel Dusuk Faiz Oraniyla Ihtiyac Kredisi Cekmek Ister Misiniz ?\n1.Evet\n2.Hayir\n");
                while (1)
                {
                    scanf("%d", &x);
                    if (x == 1)
                    {
                        printf("Kredi Cekme Ekranina Yonlendiriliyorsunuz...\n");
                        sleep(1);
                        system("cls");
                        kredi_cek(i, index);
                    }
                    else if (x == 2)
                    {
                        islem_menu(i, index);
                    }
                    else
                    {
                        printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                    }
                }
            }
            else
            {
                borc_ode(i, index);
            }
        }
        else if (islem == 5)
        {
            printf("\n1.Doviz Al\n2.Doviz Sat\n3.Ana Menu\n");
            while (1)
            {
                scanf("%d", &secim);
                if (secim == 1)
                {
                    printf("\n1.Dolar: 7.63\n2.Euro: 9.35\n9.Ana Menu\nIslem Yapmak Istediginiz Para Birimini Seciniz:\n");
                    doviz_al(i, index);
                }
                else if (secim == 2)
                {
                    if (dolar_database[i] == 0 && euro_database[i] == 0)
                    {
                        printf("Doviz Bakiyeniz Bulunmamaktadir\n");
                        sleep(1);
                        printf("Doviz Satin Almak Ister Misiniz ?\n1.Evet\n2.Hayir\n");
                        while (1)
                        {
                            scanf("%d", &x);
                            if (x == 1)
                            {
                                printf("Doviz Satin Alma Ekranina Yonlendiriliyorsunuz...\n");
                                sleep(1);
                                printf("\n1.Dolar: 7.63\n2.Euro: 9.35\n9.Ust Menu\nIslem Yapmak Istediginiz Para Birimini Seciniz: \n");
                                doviz_al(i, index);
                            }
                            else if (x == 2)
                            {
                                islem_menu(i, index);
                            }
                            else
                            {
                                printf("Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz\n");
                            }
                        }
                    }

                    else
                    {
                        doviz_sat(i, index);
                    }
                }
                else if (secim == 3)
                {
                    islem_menu(i, index);
                }
                else
                {
                    printf("Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz\n");
                }
            }
        }
        else if (islem == 6)
        {
            fatura_ode(i, index);
        }
        else if (islem == 7)
        {
            sigorta_islem(i, index);
        }
        else if (islem == 8)
        {
            printf("11. GRUP TESEKKUR EDER\n...IYI GUNLER...\n");
            sleep(2);
            main();
        }
        else
        {
            printf("Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz\n\n");
        }
    }
}

void kayit_sil()
{
    int index = 0;
    a = 1;
    if ((database = fopen("database.txt", "r")) != NULL)
    {
        database = fopen("database.txt", "r");
        while (!feof(database))
        {
            fscanf(database, "%s %d %f %f %f %f %d", &musteri_database[index], &sifre_database[index], &para_database[index], &borc_database[index], &dolar_database[index], &euro_database[index], &hesapNo_database[index]);
            index++;
        }
        printf("Silmek Istediginiz Hesabin Ad Soyad Bilgisini Giriniz:\n");
        scanf("%s%s", &ad_giris, &soyad_giris);
        printf("Silmek Istediginiz Hesabin Sifresini Giriniz: \n");
        scanf("%d", &sifre_giris);
        strcat(ad_giris, soyad_giris);
        strupr(ad_giris);
        strupr(soyad_giris);
        for (i = 0; i < index - 1; i++)
        {
            if ((strcmp(ad_giris, musteri_database[i]) == 0) && sifre_giris == sifre_database[i])
            {
                k = strlen(musteri_database[i]);
                for (j = 0; j < k; j++)
                {
                    musteri_database[i][j] = '0';
                }
                sifre_database[i] = 0;
                borc_database[i] = 0;
                dolar_database[i] = 0;
                euro_database[i] = 0;
                hesapNo_database[i] = 0;
                para_database[i] = 0;
                a = 0;
                database_log(index);
                printf("Hesabiniz Basariyla Silinmistir\nAna Menuye Donuluyor...\n\n");
                sleep(2);
                main();
            }
        }
        if (a == 1)
        {
            printf("Girmis Oldugunuz Bilgilerle Eslesen Hesap Bulunamadi!\n1.Yeniden Dene\n2.Ana Menu\n");
            while (1)
            {
                scanf("%d", &islem);
                if (islem == 1)
                {
                    kayit_sil();
                }
                else if (islem == 2)
                {
                    printf("Ana Menuye Donuluyor...\n\n");
                    sleep(1);
                    main();
                }
                else
                {
                    printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                }
            }
        }
    }
    else
    {
        printf("Silinecek Herhangi Bir Hesap Bulunmamaktadir.\n\n");
        sleep(1);
        main();
    }
}

void giris_yap()
{
    int index = 0;
    if ((database = fopen("database.txt", "r")) != NULL)
    {
        database = fopen("database.txt", "r");
        while (!feof(database))
        {
            fscanf(database, "%s %d %f %f %f %f %d", &musteri_database[index], &sifre_database[index], &para_database[index], &borc_database[index], &dolar_database[index], &euro_database[index], &hesapNo_database[index]);
            index++;
        }
        do
        {
            printf("Adinizi ve Soyadinizi Giriniz:\n");
            scanf("%s%s", &ad_giris, &soyad_giris);
            printf("Sifreinizi Giriniz:\n");
            scanf("%d", &sifre_giris);
            strcat(ad_giris, soyad_giris);
            strupr(ad_giris);
            strupr(soyad_giris);
            for (i = 0; i < index - 1; i++)
            {
                if ((strcmp(ad_giris, musteri_database[i]) == 0) && sifre_giris == sifre_database[i])
                {
                    printf("GIRIS ONAYLANDI");
                    sleep(1);
                    system("cls");
                    printf("HOSGELDINIZ\n\n");
                    a = 0;
                    while (1)
                    {
                        printf("Mevcut Bakiyeniz: \nTurk Lirasi: %.1f\nDolar: %.1f\nEuro: %.1f\n", para_database[i], dolar_database[i], euro_database[i]);
        				printf("Guncel Borcunuz: %.1fTL\n", borc_database[i]);
        				printf("\n1.Para Yatirma/Para Cekme\n2.Para Gonderme\n3.Kredi Cekme\n4.Borc Odeme\n5.Doviz Islemleri\n6.Fatura Odeme\n7.Sigorta Islemleri\n8.Cikis\nLutfen Yapmak Istediginiz Islem Numarasini Tuslayiniz: \n");
                        scanf("%d", &islem);
                        if (islem == 1)
                        {
                            printf("\n1.Para Yatirma\n2.Para Cekme\n3.Ana Menu\n");
                            while (1)
                            {
                                scanf("%d", &secim);
                                if (secim == 1)
                                {
                                    para_yatir(i, index);
                                }
                                else if (secim == 2)
                                {
                                    if (para_database[i] <= 0)
                                    {
                                        printf("Hesabinizda Yeterli Bakiye Bulunmamaktadir\n");
                                        sleep(1);
                                        printf("Hesabiniza Para Yatirmak Ister Misiniz ?\n1.Evet\n2.Hayir\n");
                                        while (1)
                                        {
                                            scanf("%d", &x);
                                            if (x == 1)
                                            {
                                                printf("Para Yatirma Ekranin Yonlendiriliyorsunuz...\n");
                                                sleep(1);
                                                para_yatir(i, index);
                                            }
                                            else if (x == 2)
                                            {
                                                islem_menu(i, index);
                                            }
                                            else
                                            {
                                                printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        para_cek(i, index);
                                    }
                                }
                                else if (secim == 3)
                                {
                                    islem_menu(i, index);
                                }
                                else
                                {
                                    printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                                }
                            }
                        }
                        else if (islem == 2)
                        {
                            para_gonder(i, index);
                        }

                        else if (islem == 3)
                        {
                            kredi_cek(i, index);
                        }
                        else if (islem == 4)
                        {
                            if (borc_database[i] == 0)
                            {
                                printf("Odenecek Borcunuz Bulunmamaktadir\n\n");
                                sleep(1);
                                printf("Size Ozel Dusuk Faiz Oraniyla Ihtiyac Kredisi Cekmek Ister Misiniz ?\n1.Evet\n2.Hayir\n");
                                while (1)
                                {
                                    scanf("%d", &x);
                                    if (x == 1)
                                    {
                                        printf("Kredi Cekme Ekranina Yonlendiriliyorsunuz...\n");
                                        sleep(1);
                                        kredi_cek(i, index);
                                    }
                                    else if (x == 2)
                                    {
                                        islem_menu(i, index);
                                    }
                                    else
                                    {
                                        printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                                    }
                                }
                            }
                            else
                            {
                                borc_ode(i, index);
                            }
                        }
                        else if (islem == 5)
                        {
                            printf("\n1.Doviz Al\n2.Doviz Sat\n3.Ana Menu\n");
                            while (1)
                            {
                                scanf("%d", &secim);
                                if (secim == 1)
                                {
                                    printf("\n1.Dolar: 7.63\n2.Euro: 9.35\n9.Ana Menu\nIslem Yapmak Istediginiz Para Birimini Seciniz:\n");
                                    doviz_al(i, index);
                                }
                                else if (secim == 2)
                                {
                                    if (dolar_database[i] == 0 && euro_database[i] == 0)
                                    {
                                        printf("Doviz Bakiyeniz Bulunmamaktadir\n");
                                        sleep(1);
                                        printf("Doviz Satin Almak Ister Misiniz ?\n1.Evet\n2.Hayir\n");
                                        while (1)
                                        {
                                            scanf("%d", &x);
                                            if (x == 1)
                                            {
                                                printf("Doviz Satin Alma Ekranina Yonlendiriliyorsunuz...\n");
                                                sleep(1);
                                                printf("\n1.Dolar: 7.63\n2.Euro: 9.35\n9.Ust Menu\nIslem Yapmak Istediginiz Para Birimini Seciniz: \n");
                                                doviz_al(i, index);
                                            }
                                            else if (x == 2)
                                            {
                                                islem_menu(i, index);
                                            }
                                            else
                                            {
                                                printf("Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz\n");
                                            }
                                        }
                                    }

                                    else
                                    {
                                        doviz_sat(i, index);
                                    }
                                }
                                else if (secim == 3)
                                {
                                    islem_menu(i, index);
                                }
                                else
                                {
                                    printf("Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz\n");
                                }
                            }
                        }
                        else if (islem == 6)
                        {
                            fatura_ode(i, index);
                        }
                        else if (islem == 7)
                        {
                            sigorta_islem(i, index);
                        }
                        else if (islem == 8)
                        {
                            printf("11. GRUP TESEKKUR EDER\n...IYI GUNLER...\n");
                            sleep(1);
                            printf("Ana Menuye Donuluyor...\n\n");
                            sleep(1);
                            main();
                        }
                        else
                        {
                            printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n\n");
                        }
                    }
                }
            }

            if (a == 1)
            {
                printf("Girdiginiz Bilgilerle Eslesen Herhangi Bir Hesap Bulunamadi\n0.Ana Menu\n1.Yeniden Dene\n");
                while (1)
                {
                    scanf("%d", &secim);
                    if (secim == 0)
                    {
                        printf("Ana Menuye Donuluyor...\n\n");
                        sleep(1);
                        main();
                    }
                    else if (secim == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
                    }
                }
            }
        } while (a == 1);
        fclose(database);
    }
    else
    {
        printf("Lutfen Hesap Olusturunuz\n\n");
        sleep(1);
        main();
    }
}

int main()
{	
	system("cls");
    srand(time(NULL));
    while (1)
    {
        printf("\n11.GRUP BANKA SISTEMI\n\n1.Hesap Olustur\n2.Giris Yap\n3.Hesap Sil\n4.Cikis Yap\n");
        scanf("%d", &islem);
        switch(islem)
        {
        	
		
        case (1):
        {
            hesap_ac();
        }
        case(2):
        {
            giris_yap();
            break;
        }
        case (3):
        {
            kayit_sil();
        }
        case (4):
        {
            printf("11. GRUP TESEKKUR EDER\n...IYI GUNLER...\n");
            getch();
			break;
        }
        default:
        {
            printf("Lutfen Yapmak Istediginiz Islemin Numarasini Tuslayiniz\n");
        }
		}
    }
    return 0;
}
