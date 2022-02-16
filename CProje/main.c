#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int secim=0;
enum cinsiyet{erkek=1,kadin};
struct OgrBilgileri{
	char ad[50];
	char soyad[50];
	char kimlikno[11];
	int yas;
	enum cinsiyet c1;
	char tel[14];
	int aylik_nakit;
	int ogr_numarasi;
	char veli_ad[50];
	char veli_soyad[50];
	int sinav;
}ogr;
struct PerBilgi{
		char ad[50];
		char soyad[50];
		char kimlikno[11];
		enum cinsiyet c2;
		enum meslek{ogretmen=1,mudur,mudur_yard,ik,tp}m1;
		int yas;
		char tel[14];
		int maas;
		int per_no;
}per;
void Menu(){
		int i;
		for(i=0;i<100;i++){
			printf("*");
		}
		printf("\n* %97s*","");
		printf("\n*%50s%48s*","[1] OGRENCI","");
		printf("\n*%51s%47s*","[2] PERSONEL","");
		printf("\n*%57s%41s*","[3] SINIF YONETIMI","");
		printf("\n*%58s%40s*","[4] CARI HAREKETLER","");
		printf("\n*%48s%50s*","[5] CIKIS","");
		printf("\n* %97s*","");
		printf("\n* %97s*\n","");
		for(i=0;i<100;i++){
			printf("*");
		}
		printf("\n%30s GIRMEK ISTEDIGINIZ MENUYU TUSLAYINIZ: ","");
		scanf("%d",&secim);
}
void ogrEkle(){
	FILE *fp;
	struct OgrBilgileri kontrol[100];
	if((fp=fopen("Ogrenci.txt","a+"))==NULL){
			printf("Dosyayi Acma Hatasi");
			exit(1);
	}
	char kimlik2[11];
	int para=0,taksit=1,cinsiyet,i=0,j=0,c=0,q,ogrno;
	char secim2;
	while(fread(&kontrol[i],sizeof(kontrol[i]),1,fp)==1){
		i++;
	}
	rewind(fp);
	while(1==1){
		system("cls");
		printf("\nOgrencinin Adi: ");
		getchar();
		gets(ogr.ad);
		printf("\nOgrencinin Soyadi: ");
		scanf("%s",ogr.soyad);
		do{
			c=0;
			printf("\nOgrencinin Kimlik Numarasi: ");
			scanf("%s",kimlik2);
			if(strlen(kimlik2)!=11){
				printf("\nKIMLIK NUMARASI 11 HANELI OLMALIDIR!!!\n");	
			}
			for(j=0;j<i;j++){
				q=strcmp(kontrol[j].kimlikno,kimlik2);
				if(q==0){
					printf("\nDIGER KIMLIK NUMARALARIYLA AYNI KIMLIK NUMARASINA SAHIP OLAMAZSINIZ!");
					c++;
				}
			}
			if(c==0){
				strcpy(ogr.kimlikno,kimlik2);
			}		
		}while(c!=0 || strlen(kimlik2)!=11);
		printf("\nOgrencinin Yasi: ");
		scanf("%d",&ogr.yas);
		printf("\nOgrencinin Cinsiyeti(Erkek[1]-Kadin[2]): ");
		scanf("%d",&cinsiyet);
		ogr.c1=cinsiyet;
		do{
			printf("\nOgrencinin Telefon Numarasi(Orn: 05356818375):");
			scanf("%s",ogr.tel);
			if(strlen(ogr.tel)!=11){
				printf("\nTELEFON NUMARASI 11 HANELI OLMALIDIR!!!\n");
			}
		}while(strlen(ogr.tel)!=11);
		
		printf("\nVelinin Adi: ");
		getchar();
		gets(ogr.veli_ad);
		printf("\nVelinin Soyadi: ");
		scanf("%s",ogr.veli_soyad);
		do{
			printf("\nToplam Odenecek Miktari Giriniz: ");
			scanf("%d",&para);
			if(para<3000){
				printf("\n3000TL'den Daha Dusuk Fiyatta Ogrenci Kaydolamaz!'");
			}
		}while(para<3000);
		printf("\nKac Aylik Taksitlerle Odenecek? ");
		scanf("%d",&taksit);
		ogr.aylik_nakit=para/taksit;
		do{
			c=0;
			ogrno=rand()%900+100;
			for(j=0;j<i;j++){
				if(ogrno==kontrol[j].ogr_numarasi){
					c++;
				}
			}
			if(c==0){
				ogr.ogr_numarasi=ogrno;
			}
		}while(c!=0);
		ogr.sinav=-1;
		if(fwrite(&ogr,sizeof(ogr),1,fp)!=1){
			printf("Dosyaya Yazma Hatasi!");
			exit(1);
		}
		printf("\n\n\nOgrenci Eklemeye Devam Etmek Istiyor musunuz?(e/h) ");
		scanf(" %c",&secim2);
		if(tolower(secim2)=='e'){
			system("cls");
			continue;
		}
		else if(tolower(secim2)=='h'){
			printf("\nMenuden Cikis Yapiliyor...");
			secim=0;
			break;
		}
		else{
			printf("\nYanlis Secim Yaptiniz, Cikisiniz Yapiliyor...");
			secim=0;
			break;
		}
	}
	fclose(fp);
}
void ogrYazdir(){
	system("cls");
	int secim2;
	FILE *fp;
		if((fp=fopen("Ogrenci.txt","r"))==NULL){
			printf("\nOgrenci Bilgilerini Yazdirmak Icin Once Ogrenci Eklemeniz Gerekiyor!!!");
			ogrEkle();
		}
	rewind(fp);
		struct OgrBilgileri ogr2;
		while(fread(&ogr2,sizeof(ogr2),1,fp)==1){
			printf("\n\n\n\n-------------------%d NUMARALI OGRENCI-------------------",ogr2.ogr_numarasi);
			printf("\n-------------------------------------------------------------");
			printf("\n-- Ogrencinin Adi: %s",ogr2.ad);
			printf("\n-- Ogrencinin Soyadi: %s",ogr2.soyad);
			printf("\n-- Ogrencinin Kimlik Numarasi: %s",ogr2.kimlikno);
			printf("\n-- Ogrencinin Yasi: %d",ogr2.yas);
			printf("\n-- Ogrencinin Teli: %s",ogr2.tel);
			switch(ogr2.c1){
				case 1:
					printf("\n-- Ogrencinin Cinsiyeti: Erkek");
					break;
				default:
					printf("\n-- Ogrencinin Cinsiyeti: Kadin");
			}
			printf("\n-- Velinin Adi: %s",ogr2.veli_ad);
			printf("\n-- Velinin Soyadi: %s",ogr2.veli_soyad);
			printf("\n-- Aylik Odeyecegi Fiyat: %d",ogr2.aylik_nakit);
			printf("\n-------------------------------------------------------------");
		}
		fclose(fp);
		printf("\nNe Yapmak Istersiniz? \n<--Geri Don[1]\nMenuye Don [2]\nCikis Yap[3]\n");
		do{
			scanf("%d",&secim2);
			if(secim2==1){
				break;
			}
			else if(secim2==2){
				secim=0;
				break;
			}
			else if(secim2==3){
				exit(1);
			}
			else{
				printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Don[1]-Menuye Don[2]-Cikis Yap[3]): ");
			}
		}while(secim2!=1 || secim2!=2 || secim2!=3);
}

void perEkle(){
	FILE *fp;
	char secim2;
	if((fp=fopen("Personel.txt","a+"))==NULL){
				printf("Dosyayi Acma Hatasi");
				exit(1);
	}
	char kimlik2[11];
	int cinsiyet,meslek,i=0,c,q,j,pernumara;
	struct PerBilgi kontrol2[100];
	while(fread(&kontrol2[i],sizeof(kontrol2[i]),1,fp)==1){
		i++;
	}
	rewind(fp);
	while(1==1){
		system("cls");
		printf("\nPersonelin Adi: ");
		getchar();
		gets(per.ad);
		printf("\nPersonelin Soyadi: ");
		scanf("%s",per.soyad);
		do{
			c=0;
			printf("\nPersonelin Kimlik Numarasi: ");
			scanf("%s",kimlik2);
			if(strlen(kimlik2)!=11){
				printf("\nKIMLIK NUMARASI 11 HANELI OLMALIDIR!\n");
			}
			for(j=0;j<i;j++){
				q=strcmp(kontrol2[j].kimlikno,kimlik2);
				if(q==0){
					printf("\nDIGER KIMLIK NUMARALARIYLA AYNI KIMLIK NUMARASINA SAHIP OLAMAZSINIZ!");
					c++;
				}
			}
			if(c==0){
				strcpy(per.kimlikno,kimlik2);
			}
		}while(c!=0 || strlen(kimlik2)!=11);
				printf("\nPersonelin Yasi: ");
				scanf("%d",&per.yas);
				printf("\nPersonelin Cinsiyeti(Erkek[1]-Kadin[2]): ");
				scanf("%d",&cinsiyet);
				per.c2=cinsiyet;
				do{
					printf("\nPersonelin Telefon Numarasi(Orn: 05356818375): ");
					scanf("%s",per.tel);
					if(strlen(per.tel)!=11){
						printf("\nTELEFON NUMARASI 11 HANELI OLMALIDIR!\n");
					}
				}while(strlen(per.tel)!=11);
				printf("\nPersonel'e Verilecek Maasi Giriniz: ");
				scanf("%d",&per.maas);
				do{
				c=0;
				pernumara=rand()%99+1;
				for(j=0;j<i;j++){
					if(pernumara==kontrol2[j].per_no){
						c++;
					}
				}
				if(c==0){
					per.per_no=pernumara;
				}
			}while(c!=0);
				printf("\nPersonelin Meslegi(Ogretmen[1]-Mudur[2]-Mudur Yardimcisi[3]-Insan Kanyankari[4]-Temizlik Personeli[5]): ");
				scanf("%d",&meslek);
				per.m1=meslek;
				if(fwrite(&per,sizeof(per),1,fp)!=1){
					printf("Dosyaya Yazma Hatasi!");
					exit(1);
				}
				printf("\n\n\nPersonel Eklemeye Devam Etmek Istiyor musunuz?(e/h) ");
				scanf(" %c",&secim2);
				if(tolower(secim2)=='e'){
					system("cls");
					continue;
				}
				else if(tolower(secim2)=='h'){
					printf("\nMenuden Cikis Yapiliyor...");
					fclose(fp);
					secim=0;
					break;
				}
				else{
					printf("\nYanlis Secim Yaptiniz, Cikisiniz Yapiliyor...");
					fclose(fp);
					secim=0;
					break;
				}
			}
}
void perYazdir(){
	system("cls");
	int secim2;
	FILE *fp;
	if((fp=fopen("Personel.txt","r"))==NULL){
		printf("\nPersonel Bilgilerini Yazdirmak Icin Once Personel Eklemeniz Gerekiyor!!!");
		perEkle();
	}
	rewind(fp);
	struct PerBilgi per2;
	while(fread(&per2,sizeof(per2),1,fp)==1){
		printf("\n\n\n\n-------------------%d NUMARALI PERSONEL-------------------",per2.per_no);
		printf("\n-------------------------------------------------------------");
		printf("\n-- Personelin Adi: %s",per2.ad);
		printf("\n-- Personelin Soyadi: %s",per2.soyad);
		printf("\n-- Personelin Kimlik Numarasi: %s",per2.kimlikno);
		printf("\n-- Personelin Yasi: %d",per2.yas);
		switch(per2.c2){
			case 1:
				printf("\n-- Personelin Cinsiyeti: Erkek");
				break;
			default:
				printf("\n-- Personelin Cinsiyeti: Kadin");
		}
		switch(per2.m1){
			case 1:
				printf("\n-- Personelin Meslegi: Ogretmen");
				break;
			case 2:
				printf("\n-- Personelin Meslegi: Mudur");
				break;
			case 3:
				printf("\n-- Personelin Meslegi: Mudur Yardimcisi");
				break;
			case 4:
				printf("\n-- Personelin Meslegi: Insan Kaynaklari");
				break;
			default:
				printf("\n-- Personelin Meslegi: Temizlik Personeli");
		}
		printf("\n-- Personelin Teli: %s",per2.tel);
		printf("\n-- Personelin Maasi: %d",per2.maas);
		printf("\n-------------------------------------------------------------");
	}
	fclose(fp);
	printf("\nNe Yapmak Istersiniz? \n<--Geri Don[1]\nMenuye Don [2]\nCikis Yap[3]\n");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Don[1]-Menuye Don[2]-Cikis Yap[3]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);

}
void ogrGuncelle(){
	int secim2,bul_no,guncelleme,cinsiyet,a=0,i,k=0,c,j,q;
	char kimlik2[11];
	char secim3;
	struct OgrBilgileri guncel[100];
	FILE *fp;
	if((fp=fopen("Ogrenci.txt","r"))==NULL){
		printf("Dosyayi Acma Hatasi");
		exit(1);
	}
	rewind(fp);
	system("cls");
	printf("\nGuncellenecek Kisinin Numarasini Giriniz: ");
	scanf("%d",&bul_no);
	while(fread(&guncel[a],sizeof(guncel[a]),1,fp)==1){
		a++;
	}
	for(i=0;i<a;i++){
		if(guncel[i].ogr_numarasi==bul_no){
			printf("\n\n\n\n-------------------%d NUMARALI OGRENCI-------------------",guncel[i].ogr_numarasi);
			printf("\n-------------------------------------------------------------");
			printf("\n-- Ogrencinin Adi: %s",guncel[i].ad);
			printf("\n-- Ogrencinin Soyadi: %s",guncel[i].soyad);
			printf("\n-- Ogrencinin Kimlik Numarasi: %s",guncel[i].kimlikno);
			switch(guncel[i].c1){
				case 1:
					printf("\n-- Ogrencinin Cinsiyeti: Erkek");
					break;
				default:
					printf("\n-- Ogrencinin Cinsiyeti: Kadin");
			}
			printf("\n-- Ogrencinin Yasi: %d",guncel[i].yas);
			printf("\n-- Ogrencinin Teli: %s",guncel[i].tel);
			printf("\n-- Velinin Adi: %s",guncel[i].veli_ad);
			printf("\n-- Velinin Soyadi: %s",guncel[i].veli_soyad);
			printf("\n-- Aylik Odeyecegi Fiyat: %d",guncel[i].aylik_nakit);
			printf("\n-------------------------------------------------------------\n");
			while(1==1){
				printf("Hangi Bilgiyi Guncellemek Istersiniz?\nAd[1]-Soyad[2]-Kimlik Numarasi[3]-Yas[4]-Cinsiyet[5]-Telefon[6]-Veli Ad[7]-Veli Soyad[8]-Aylik Fiyat[9]\nSecim: ");
				scanf("%d",&guncelleme);
				switch(guncelleme){
					case 1:
						printf("\nOgrencinin Yeni Adi: ");
						getchar();
						gets(guncel[i].ad);
						break;
					case 2:
						printf("\nOgrencinin Yeni Soyadi: ");
						scanf("%s",guncel[i].soyad);
						break;
					case 3:
						do{
							c=0;
							printf("\nOgrencinin Yeni Kimlik Numarasi: ");
							scanf("%s",kimlik2);
							for(j=0;j<a;j++){
								q=strcmp(guncel[j].kimlikno,kimlik2);
								if(q==0){
									printf("\nDIGER KIMLIK NUMARALARIYLA AYNI KIMLIK NUMARASINA SAHIP OLAMAZSINIZ!");
									c++;
								}
							}
							if(strlen(kimlik2)!=11){
								printf("\nKIMLIK NUMARASI 11 HANELI OLMALIDIR!\n");
							}
							if(c==0){
								strcpy(guncel[i].kimlikno,kimlik2);
							}
						}	while(c!=0 || strlen(kimlik2)!=11);
						break;
					case 4:
						printf("\nOgrencinin Yeni Yasi: ");
						scanf("%d",&guncel[i].yas);
						break;
					case 5:
						printf("\nOgrencinin Yeni Cinsiyeti(Erkek[1]-Kadin[2]): ");
						scanf("%d",&cinsiyet);
						guncel[i].c1=cinsiyet;
						break;
					case 6:
						do{
							printf("\nOgrencinin Yeni Telefon Numarasi: ");
							scanf("%s",guncel[i].tel);
							if(strlen(guncel[i].tel)!=11){
								printf("\nTELEFON NUMARASI 11 HANELI OLMALIDIR!\n");
							}
						}while(strlen(guncel[i].tel)!=11);
						break;
					case 7:
						printf("\nVelinin Yeni Adi: ");
						getchar();
						gets(guncel[i].veli_ad);
						break;
					case 8:
						printf("\nVelinin Yeni Soyadi: ");
						scanf("%s",guncel[i].veli_soyad);
						break;
					case 9:
						printf("\nOgrencinin Verecegi Yeni Aylik Fiyat: ");
						scanf("%d",&guncel[i].aylik_nakit);
						break;
					default:
						printf("\nYanlis Secim Yaptiniz! ");
				}
				printf("Bilgi Guncellemeye Devam Etmek Istiyor musunuz?(e/h) ");
				scanf(" %c",&secim3);
				if(tolower(secim3)=='e'){
					continue;
				}
				else if(tolower(secim3)=='h'){
					k++;
					printf("\nGuncelleme Yapilmistir...");
					fclose(fp);
					FILE *fp2;
					fp2=fopen("Ogrenci.txt","w");
					for(i=0;i<a;i++){
						if(fwrite(&guncel[i],sizeof(guncel[i]),1,fp2)!=1){
							printf("Dosyaya Yazma Hatasi!");
							exit(1);
						}
					}
					fclose(fp2);
					break;
				}
				else{
					k++;
					printf("\nYanlis Secim Yaptiniz, Cikisiniz Yapiliyor...");
					fclose(fp);
					FILE *fp2;
					fp2=fopen("Ogrenci.txt","w");
					for(i=0;i<a;i++){
						if(fwrite(&guncel[i],sizeof(guncel[i]),1,fp2)!=1){
							printf("Dosyaya Yazma Hatasi!");
							exit(1);
						}
					}
					fclose(fp2);
					break;
				}
			}
		}
	}
	if(k==0){
		printf("\nOgrenci Bulunamadi!");
	}
	printf("\nNe Yapmak Istersiniz? \n<--Geri Don[1]\nMenuye Don [2]\nCikis Yap[3]\n");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Don[1]-Menuye Don[2]-Cikis Yap[3]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
}
void aktarma1(int durak,int c,struct OgrBilgileri silik[100],struct OgrBilgileri yedek[100],FILE *fp){
	int i;
	for(i=0;i<durak;i++){
		strcpy(yedek[i].ad,silik[i].ad);
		strcpy(yedek[i].soyad,silik[i].soyad);
		strcpy(yedek[i].kimlikno,silik[i].kimlikno);
		yedek[i].yas=silik[i].yas;
		yedek[i].c1=silik[i].c1;
		strcpy(yedek[i].tel,silik[i].tel);
		yedek[i].aylik_nakit=silik[i].aylik_nakit;
		yedek[i].ogr_numarasi=silik[i].ogr_numarasi;
		strcpy(yedek[i].veli_ad,silik[i].veli_ad);
		strcpy(yedek[i].veli_soyad,silik[i].veli_soyad);
		yedek[i].sinav=silik[i].sinav;
	}
	for(i=(durak+1);i<c;i++){
		strcpy(yedek[i-1].ad,silik[i].ad);
		strcpy(yedek[i-1].soyad,silik[i].soyad);
		strcpy(yedek[i-1].kimlikno,silik[i].kimlikno);
		yedek[i-1].yas=silik[i].yas;
		yedek[i-1].c1=silik[i].c1;
		strcpy(yedek[i-1].tel,silik[i].tel);
		yedek[i-1].aylik_nakit=silik[i].aylik_nakit;
		yedek[i-1].ogr_numarasi=(silik[i].ogr_numarasi);
		strcpy(yedek[i-1].veli_ad,silik[i].veli_ad);
		strcpy(yedek[i-1].veli_soyad,silik[i].veli_soyad);
		yedek[i-1].sinav=silik[i].sinav;
	}
	fclose(fp);
	FILE *fp2;
	fp2=fopen("Ogrenci.txt","w");
	for(i=0;i<(c-1);i++){
		if(fwrite(&yedek[i],sizeof(yedek[i]),1,fp2)!=1){
			printf("Dosyaya Yazma Hatasi!");
			exit(1);
		}
	}
	fclose(fp2);
}
void ogrSil(){
	int sil_no,i=0,c=0,secim2,durak;
	char secim3;
	system("cls");
	printf("\nSilmek Istediginiz Ogrencinin Numarasini Giriniz: ");
	scanf("%d",&sil_no);
	struct OgrBilgileri silik[100];
	struct OgrBilgileri yedek[100];
	FILE *fp;
	if((fp=fopen("Ogrenci.txt","r"))==NULL){
		printf("Dosyayi Acma Hatasi!");
		exit(1);
	}
	while(fread(&silik[c],sizeof(silik[c]),1,fp)==1){
		c++;
	}
	for(i=0;i<c;i++){
		if(sil_no==silik[i].ogr_numarasi){
			printf("\n\n%50s\n%55s","SILMEK ISTEDIGINIZDEN EMIN MISINIZ?(E/H)","Secim: ");
			fflush(stdin);
			secim3=getchar();
			if(tolower(secim3)=='e'){
				aktarma1(i,c,silik,yedek,fp);
				printf("\n%d Numarali Ogrenci Silindi.",silik[i].ogr_numarasi);
				break;
			}
			else{
				break;
			}
		}
		else if(sil_no!=silik[i].ogr_numarasi && i!=(c-1)){
		}
		else{
			printf("\n%d Numarali Ogrenci Bulunamadi...",sil_no);
		}
	}
	printf("\nNe Yapmak Istersiniz? \n<--Geri Don[1]\nMenuye Don [2]\nCikis Yap[3]\n");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Don[1]-Menuye Don[2]-Cikis Yap[3]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
	
}
void aktarma2(int durak,int c,struct PerBilgi silik[100],	struct PerBilgi yedek[100],FILE *fp){
	int i;
	for(i=0;i<durak;i++){
		strcpy(yedek[i].ad,silik[i].ad);
		strcpy(yedek[i].soyad,silik[i].soyad);
		strcpy(yedek[i].kimlikno,silik[i].kimlikno);
		yedek[i].c2=silik[i].c2;
		yedek[i].m1=silik[i].m1;
		yedek[i].yas=silik[i].yas;
		strcpy(yedek[i].tel,silik[i].tel);
		yedek[i].maas=silik[i].maas;
		yedek[i].per_no=silik[i].per_no;
	}
	for(i=(durak+1);i<c;i++){
		strcpy(yedek[i-1].ad,silik[i].ad);
		strcpy(yedek[i-1].soyad,silik[i].soyad);
		strcpy(yedek[i-1].kimlikno,silik[i].kimlikno);
		yedek[i-1].c2=silik[i].c2;
		yedek[i-1].m1=silik[i].m1;
		yedek[i-1].yas=silik[i].yas;
		strcpy(yedek[i-1].tel,silik[i].tel);
		yedek[i-1].maas=silik[i].maas;
		yedek[i-1].per_no=(silik[i].per_no);
	}
	fclose(fp);
	FILE *fp2;
	fp2=fopen("Personel.txt","w");
	for(i=0;i<(c-1);i++){
		if(fwrite(&yedek[i],sizeof(yedek[i]),1,fp2)!=1){
			printf("Dosyaya Yazma Hatasi!");
			exit(1);
		}
	}
	fclose(fp2);
}
void perSil(){
	system("cls");
	int sil_no,i=0,c=0,secim2,a=0,durak;
	char secim3;
	printf("\nSilmek Istediginiz Personelin Numarasini Giriniz: ");
	scanf("%d",&sil_no);
	struct PerBilgi silik[100];
	struct PerBilgi yedek[100];
	FILE *fp;
	if((fp=fopen("Personel.txt","r"))==NULL){
		printf("Dosyayi Acma Hatasi!");
		exit(1);
	}
	while(fread(&silik[c],sizeof(silik[c]),1,fp)==1){
		c++;
	}
	for(i=0;i<(c);i++){
		if(sil_no==silik[i].per_no){
			printf("\n\n%50s\n%55s","SILMEK ISTEDIGINIZDEN EMIN MISINIZ?(E/H)","Secim: ");
			fflush(stdin);
			secim3=getchar();
			if(tolower(secim3)=='e'){
				aktarma2(i,c,silik,yedek,fp);
				printf("\n%d Numarali Personel Silindi.",silik[i].per_no);
				break;
			}
			else{
				break;
			}
		}
		else if(sil_no!=silik[i].per_no && i!=(c-1)){
		}
		else{
			printf("\n%d Numarali Personel Bulunamadi...",sil_no);
		}	
	}
	printf("\nNe Yapmak Istersiniz? \n<--Geri Don[1]\nMenuye Don [2]\nCikis Yap[3]\n");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Don[1]-Menuye Don[2]-Cikis Yap[3]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
	
}
void perGuncelle(){
	system("cls");
    int secim2,bul_no,guncelleme,cins,meslek,i,c=0,k=0,a,j,q;
    char secim3,kimlik2[11];
    struct PerBilgi guncel[100];
	FILE *fp;
	if((fp=fopen("Personel.txt","r"))==NULL){
		printf("Dosyayi Acma Hatasi");
		exit(1);
	}
	rewind(fp);
	printf("\nGuncellenecek Kisinin Numarasini Giriniz: ");
	scanf("%d",&bul_no);
	while(fread(&guncel[c],sizeof(guncel[c]),1,fp)==1){
		c++;
	}
	for(i=0;i<c;i++){
	    if(guncel[i].per_no==bul_no){
		    printf("\n\n\n\n-------------------%d NUMARALI PERSONEL-------------------",guncel[i].per_no);
		    printf("\n-------------------------------------------------------------");
		    printf("\n-- Personelin Adi: %s",guncel[i].ad);
		    printf("\n-- Personelin Soyadi: %s",guncel[i].soyad);
		    printf("\n-- Personelin Kimlik Numarasi: %s",guncel[i].kimlikno);
		    switch(guncel[i].c2){
		    	case 1:
		    		printf("\n-- Personelin Cinsiyeti: Erkek");
					break;
				default:
					printf("\n-- Personelin Cinsiyeti: Kadin");
			}
		    printf("\n-- Personelin Yasi: %d",guncel[i].yas);
		    switch(guncel[i].m1){
		    	case 1:
		    		printf("\n-- Personelin Meslegi: Ogretmen");
		  			break;
				case 2:
					printf("\n-- Personelin Meslegi: Mudur");
					break;
				case 3:
					printf("\n-- Personelin Meslegi: Mudur Yardimcisi");
					break;
				case 4:
					printf("\n-- Personelin Meslegi: Insan Kaynaklari");
					break;
				default:
					printf("\n-- Personelin Meslegi: Temizlik Personeli");
    		}
		    printf("\n-- Personelin Teli: %s",guncel[i].tel);
		    printf("\n-- Personelin Maasi: %d",guncel[i].maas);
		    printf("\n-------------------------------------------------------------");
		    while(1==1){
		    	printf("Hangi Bilgiyi Guncellemek Istersiniz?\nAd[1]-Soyad[2]-Kimlik Numarasi[3]-Yas[4]-Cinsiyet[5]-Telefon[6]-Maas[7]-Meslek[8]\nSecim: ");
		    	scanf("%d",&guncelleme);
		    	switch(guncelleme){
		    		case 1:
		    			printf("\nPersonelin Yeni Adi: ");
		    			getchar();
		    			gets(guncel[i].ad);
		    			break;
		    		case 2:
		    			printf("\nPersonelin Yeni Soyadi: ");
		    			scanf("%s",guncel[i].soyad);
		    			break;
		    		case 3:
		   				do{
							a=0;
							printf("\nPersonelin Yeni Kimlik Numarasi: ");
							scanf("%s",kimlik2);
							for(j=0;j<c;j++){
								q=strcmp(guncel[j].kimlikno,kimlik2);
								if(q==0){
									printf("\nDIGER KIMLIK NUMARALARIYLA AYNI KIMLIK NUMARASINA SAHIP OLAMAZSINIZ!");
									a++;
								}
							}
							if(strlen(kimlik2)!=11){
								printf("\nKIMLIK NUMARASI 11 HANELI OLMALIDIR!\n");
							}
							if(a==0){
								strcpy(guncel[i].kimlikno,kimlik2);
							}		
						}while(a!=0 || strlen(kimlik2)!=11);
				   		break;
				   	case 4:
				   		printf("\nPersonelin Yeni Yasi: ");
				   		scanf("%d",&guncel[i].yas);
				   		break;
				   	case 5:
				   		printf("\nPersonelin Yeni Cinsiyeti(Erkek[1]-Kadin[2]): ");
				   		scanf("%d",&cins);
				   		guncel[i].c2=cins;
				   		break;
				   	case 6:
				   		do{
				   			printf("\nPersonelin Yeni Telefon Numarasi(Orn:05356818375) : ");
				   			scanf("%s",guncel[i].tel);
				   			if(strlen(guncel[i].tel)!=11){
				   				printf("\nTELEFON NUMARASI 11 HANELI OLMALIDIR!\n");
							}
						}while(strlen(guncel[i].tel)!=11);
				   		break;
				   	case 7:
				   		printf("\nPersonel'e Verilecek Yeni Maasi Giriniz: ");
				   		scanf("%d",&guncel[i].maas);
				   		break;
				   	case 8:
				   		printf("\nPersonelin Yeni Meslegi(Ogretmen[1]-Mudur[2]-Mudur Yardimcisi[3]-Insan Kanyankari[4]-Temizlik Personeli[5]): ");
				   		scanf("%d",&meslek);
				   		guncel[i].m1=meslek;
				   		break;
				   	default:
				   		printf("\nYanlis Secim Yaptiniz! ");
			   	}
				printf("Bilgi Guncellemeye Devam Etmek Istiyor musunuz?(e/h) ");
	    		scanf(" %c",&secim3);
	    		if(tolower(secim3)=='e'){
	    			rewind(fp);
	    			continue;
	    		}
	    		else if(tolower(secim3)=='h'){
	    			k++;
	    			printf("\nGuncelleme Yapilmistir...");
	    			fclose(fp);
	    			FILE *fp2;
	    			fp2=fopen("Personel.txt","w");
	    			for(i=0;i<c;i++){
	    				if(fwrite(&guncel[i],sizeof(guncel[i]),1,fp2)!=1){
		    					printf("Dosyaya Yazma Hatasi!");
		    					exit(1);
		    			}
				   	}
		   			fclose(fp2);
		   			break;
		   		}
		   		else{
		   			k++;
		   			printf("\nYanlis Secim Yaptiniz, Cikisiniz Yapiliyor...");
		   			fclose(fp);
		   			FILE *fp2;
		   			fp2=fopen("Personel.txt","w");
		   			for(i=0;i<c;i++){
		   				if(fwrite(&guncel[i],sizeof(guncel[i]),1,fp2)!=1){
		   					printf("Dosyaya Yazma Hatasi!");
		   					exit(1);
		    			}
				   	}
					fclose(fp2);
					break;
				}
			}
		}
	}
	if(k==0){
		printf("\nPersonel Bulunamadi...");
	}
	printf("\nNe Yapmak Istersiniz? \n<--Geri Don[1]\nMenuye Don [2]\nCikis Yap[3]\n");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Don[1]-Menuye Don[2]-Cikis Yap[3]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
}
void sinavGir(){
	system("cls");
	int c=0,secim2,i,j=0,k=0;
	struct OgrBilgileri snv[100];
	FILE *fp;
	if((fp=fopen("Ogrenci.txt","r"))==NULL){
		printf("Dosyayi Acma Hatasi!");
		exit(1);
	}
	
	while(fread(&snv[c],sizeof(snv[c]),1,fp)==1){
		c++;	
	}
	fclose(fp);
	FILE *fp2;
	fp2=fopen("Ogrenci.txt","w");
	for(i=0;i<c;i++){
		if(snv[i].sinav<0){
			printf("\n%s %s isimli ogrencinin sinav sonucunu giriniz(100-500): ",snv[i].ad,snv[i].soyad);
			do{	
				scanf("%d",&snv[i].sinav);
				if(snv[i].sinav<100 || snv[i].sinav>500){
					printf("\n\nSinav Sonucunu 100-500 Arasinda Girmeliydiniz. Simdi Tekrar Giriniz: ");
				}
			}while(snv[i].sinav<100 || snv[i].sinav>500);
			k=0;
			j++;
		}
		system("cls");
		if(fwrite(&snv[i],sizeof(snv[i]),1,fp2)!=1){
			printf("Dosyaya Yazma Hatasi!");
			exit(1);
		}
	}
	fclose(fp2);
	printf("\nNe Yapmak Istersiniz? \n<--Geri Git[1]\nMenuye Don [2]\nCikis Yap[3]\nSecim: ");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Git[1]-Menuye Don[2]-Cikis Yap[3]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
}
void sinavSonucu(){
	system("cls");
	int c=0,i,secim2,j=0,t=0;
	struct OgrBilgileri snv[100];
	struct OgrBilgileri snv2[100];
	FILE *fp;
	if((fp=fopen("Ogrenci.txt","r"))==NULL){
		printf("Dosyayi Acma Hatasi!");
		exit(1);
	}
	
	while(fread(&snv[c],sizeof(snv[c]),1,fp)==1){
		c++;	
	}
	fclose(fp);
	for(i=0;i<c;i++){
		if(snv[i].sinav<0){
			j++;	
		}	
	}
	if(j!=0){
		printf("\n\nDAHA ONCE DENEME SINAV SONUCU GIRILMEMIS OGRENCI BULUNMAKTADIR.\n SONUCLARI GOSTERMEK ICIN ONCE BUTUN OGRENCILERIN SINAV SONUCLARINI GIRMELISINIZ!");
		printf("\n\n\nNe Yapmak Istersiniz? \nMenuye Don [1]\nCikis Yap[2]\nSinav Sonucu Girme Menusune Git[3]\nSecim: ");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			secim=0;
			break;
		}
		else if(secim2==2){
			exit(1);
		}
		else if(secim2==3){
			t++;
			sinavGir();
			break;
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Menuye Don[1]-Cikis Yap[2]-Sinav Sonucu Girme Menusune Git[3]): ");
		}
	}while(secim!=1 || secim!=2 || secim2!=3);
	}
	else{
		FILE *fp3;
		if((fp3=fopen("Ogrenci.txt","r"))==NULL){
			printf("Dosyayi Acma Hatasi!");
			exit(1);
		}
		while(fread(&snv2[i],sizeof(snv2[i]),1,fp3)==1){
			printf("\n----------------------------------------\n");
			printf("\n%s %s Isimli Ogrencinin Sinav Notu: %d\n",snv2[i].ad,snv2[i].soyad,snv2[i].sinav);
		}
		fclose(fp3);
	}
	if(t==0){
		printf("\n\n\nNe Yapmak Istersiniz? \n<--Geri Git[1]\nMenuye Don [2]\nCikis Yap[3]\n\nSecim: ");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Git[1]-Menuye Don[2]-Cikis Yap[3]: ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
	}	
}
void sinifGoster(){
	system("cls");
	int temp,c=0,i,j,secim2,temp2;
	char tutucu[100],tutucu2[100];
	char siniflar[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	FILE *fp;
	struct OgrBilgileri sinifla[100];
	if((fp=fopen("Ogrenci.txt","r"))==NULL){
		printf("Dosyayi Acma Hatasi! ");
		exit(1);
	}
	while(fread(&sinifla[c],sizeof(sinifla[c]),1,fp)==1){
		c++;
	}
	for(i=0;i<c-1;i++){
		for(j=0;j<c-i-1;j++){
			if(sinifla[j+1].sinav>sinifla[j].sinav){
				temp=sinifla[j].sinav;
				temp2=sinifla[j].ogr_numarasi;
				strcpy(tutucu,sinifla[j].ad);
				strcpy(tutucu2,sinifla[j].soyad);
				sinifla[j].sinav=sinifla[j+1].sinav;
				sinifla[j].ogr_numarasi=sinifla[j+1].ogr_numarasi;
				strcpy(sinifla[j].ad,sinifla[j+1].ad);
				strcpy(sinifla[j].soyad,sinifla[j+1].soyad);
				sinifla[j+1].sinav=temp;
				sinifla[j+1].ogr_numarasi=temp2;
				strcpy(sinifla[j+1].ad,tutucu);
				strcpy(sinifla[j+1].soyad,tutucu2);
			}
		}
	}
	j=0;
	for(i=0;i<c;i++){
		if(i%10==0){
			printf("\n----------------------------------------------------------------------------\n%5c SINIFI: \n\n",siniflar[j]);
			printf("%20s          ","NUMARA");
			printf("%-20s","AD");
			printf("%-20s\n","SOYAD");
			printf("%20s          ","------");
			printf("%-20s","--");
			printf("%-20s\n","-----");
			j++;
		}
		//printf("\n\n%15d Numarali Ogrenci %s %5s\n",sinifla[i].ogr_numarasi,sinifla[i].ad,sinifla[i].soyad);
		printf("%20d          ",sinifla[i].ogr_numarasi);
		printf("%-20s",sinifla[i].ad);
		if(sinifla[i].sinav<0){
     	printf("%-20s",sinifla[i].soyad);
     	printf("(ogrencinin notu girilmemistir)\n");
        }
        else {
		printf("%-20s\n",sinifla[i].soyad);
		}
	}
	fclose(fp);
	
	printf("\n\n\nNe Yapmak Istersiniz? \n<--Geri Git[1]\nMenuye Don [2]\nCikis Yap[3]\n");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Git[1]-Menuye Don[2]-Cikis Yap[3]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
}
void dersProgrami(){
	int secim2,i,k=5,j,t,f,zar=0,a=5,q;
	float c=0;
	FILE *fp;
	struct OgrBilgileri ogr2;
	char *dersler[8]={"Matematik","Fizik","Tarih","Kimya","Biyoloji","Felsefe","Edebiyat","Dil ve Anlatim"};
	char *saatler[14]={"09:00-09:40","09:50-10:30","10:40-11:20","11:30-12:10","12:20-13:00","13:10-13:50","14:00-14:40","14:50-15:30","15:40-16:20","16:30-17:10","17:20-18:00","18:10-18:50","19:00-19:40","19:50-20:30"};
	char *gunler[7]={"Pazartesi","Sali","Carsamba","Persembe","Cuma","Cumartesi","Pazar"};
	char siniflar[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	if((fp=fopen("Ogrenci.txt","r"))==NULL){
		printf("\n\tBu Sayfayi Goruntulemeden Once Ogrenci Eklemelisiniz.\n\tOgrenci Ekleme Sayfasina Yonlendiriliyorsunuz...");
		ogrEkle();
	}
	while(fread(&ogr2,sizeof(ogr2),1,fp)==1){
		c++;
	}
	c=ceil(c/10);
	srand(time(NULL));
	system("cls");
	printf("\n------------------------------SINIFLARIN DERS PROGRAMLARI------------------------------");
	for(i=0;i<c;i++){
		printf("\n\n\n\t%c SINIFI\n%s",siniflar[i],"************************");
		for(f=0;f<3;f++){
			t=0;
			q=a-zar;
			zar=rand()%q+zar;
			printf("\n\n---%s---\n",gunler[zar]);
			for(j=i+1;j<k;j++){
				printf("\n%s - %s",saatler[t],dersler[rand()%8]);
				t++;
			}
			a++;
			zar++;	
			printf("\n");
		}
		k+=2;
		zar=0;
		a=5;
	}
	
	fclose(fp);
	printf("\nNe Yapmak Istersiniz? \n<--Geri Don[1]\nMenuye Don [2]\nCikis Yap[3]\n");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			break;
		}
		else if(secim2==2){
			secim=0;
			break;
		}
		else if(secim2==3){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Geri Don[1]-Menuye Don[2]-Cikis Yap[3]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
}
void cariHareketler(){
	srand(time(NULL));
	struct OgrBilgileri cari[100];
	struct PerBilgi mali[100];
	char tcumle[100],soncumle[100];
	int c=0,gelir=0,gider=0,elektrik,su,gaz,tadilat,i,toplamgider,secim2,mutfak;
	FILE *fp;
	if((fp=fopen("Ogrenci.txt","r"))==NULL){
		printf("Dosyaya Yazma Hatasi!");
		exit(1);
	}
	while(fread(&cari[c],sizeof(cari[c]),1,fp)==1){
		gelir+=cari[c].aylik_nakit;
		c++;
	}
	fclose(fp);
	FILE *fp2;
	if((fp2=fopen("Personel.txt","r"))==NULL){
		printf("Dosyaya Yazma Hatasi!");
		exit(1);
	}
	c=0;
	while(fread(&mali[c],sizeof(mali[c]),1,fp)==1){
		gider+=mali[c].maas;
		c++;
	}
	fclose(fp2);
	elektrik=rand()%100+100;
	gaz=rand()%150+100;
	su=rand()%100+100;
	tadilat=rand()%50+50;
	mutfak=rand()%25+50;
	toplamgider=elektrik+su+gaz+gider+tadilat+mutfak+200;
	printf("\n------------------------------CARI TABLO---------------------------------\n%73s\n","|");
	printf("%40s%33s\n%73s","GIDERLER","|","|");
	printf("\n%10s %-10d%43s","Elektrik Faturasi: ",elektrik,"|");
	printf("\n%10s%-10d%50s","Su Faturasi: ",su,"|");
	printf("\n%10s%-10d%44s","Dogalgaz Faturasi: ",gaz,"|");
	printf("\n%10s%-10d%43s","Tadilat Masraflari: ",tadilat,"|");
	printf("\n%10s%-10d%44s","Mutfak Masraflari: ",mutfak,"|");
	printf("\n%-10s%51s","Reklam Masraflari: 200","|");
	printf("\n%73s\n%40s%33s\n%73s","|","PERSONEL MAASLARI","|","|");
	for(i=0;i<c;i++){
		sprintf(tcumle,"->%s %s isimli personelin maasi: %d",mali[i].ad,mali[i].soyad,mali[i].maas);
		printf("\n%-72s|",tcumle);
	}
	printf("\n%10s%-10d%40s","Toplam Personel Maasi: ",gider,"|");
	printf("\n%73s\nToplam Gider: %-10d%49s\n","|",toplamgider,"|");
	printf("%40s%33s\n%73s","GELIRLER","|","|");
	printf("\n%10s%-10d%44s\n","Ogrenci Gelirleri: ",gelir,"|");
	if(toplamgider>=gelir){
		sprintf(soncumle,"%d TL ZARAR ETTINIZ!!!",toplamgider-gelir);
		printf("%-72s|",soncumle);
	}
	else{
		sprintf(soncumle,"%d TL KAR ETTINIZ!!!",gelir-toplamgider);
		printf("%-72s|",soncumle);
	}	
	printf("\n%73s\n-------------------------------------------------------------------------\n","|");
	printf("\nNe Yapmak Istersiniz? \nMenuye Don [1]\nCikis Yap[2]\n");	
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			secim=0;
			break;
		}
		else if(secim2==2){
			exit(1);
		}
		else{
			printf("\nYanlis Secim Yaptiniz. Lutfen Tekrar Tuslayiniz(Menuye Don[1]-Cikis Yap[2]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3);
}
void icMenu1(){
	int secim2;
	printf("\nOgrenci Ekle[1]\nOgrenci Bilgilerini Yazdir[2]\nOgrenci Bilgilerini Guncelle[3]\nOgrenci Sil[4]\nMenuye Geri Don[5]\nSecim: ");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			ogrEkle();
			break;
		}
		else if(secim2==2){
			ogrYazdir();
			break;
		}
		else if(secim2==3){
			ogrGuncelle();
			break;
		}
		else if(secim2==4){
			ogrSil();
			break;
		}
		else if(secim2==5){
			secim=0;
			break;
		}
		else{
			printf("\nYanlis Secim Yaptiniz.Lutfen Tekrar Tuslayiniz(Ogrenci Ekle[1]-Ogrenci Bilgierini Yazdir[2]-Ogrenci Bilgilerini Guncelle[3]-Ogrenci Sil[4]): ");
		}
	}while(secim2!=1 || secim2!=2 || secim2!=3 || secim2!=4);
}
void icMenu2(){
	int secim2;
		printf("\nPersonel Ekle[1]\nPersonel Bilgilerini Yazdir[2]\nPersonel Bilgilerini Guncelle[3]\nPersonel Sil[4]\nMenuye Geri Don[5]\nSecim: ");
		do{
			scanf("%d",&secim2);
			if(secim2==1){
				perEkle();
				break;
			}
			else if(secim2==2){
				perYazdir();
				break;
			}
			else if(secim2==3){
			    perGuncelle();
			    break;
			}
			else if(secim2==4){
				perSil();
				break;
			}
			else if(secim2==5){
				secim=0;
				break;
			}
			else{
				printf("\nYanlis Secim Yaptiniz.Lutfen Tekrar Tuslayiniz(Personel Ekle[1]Personel Bilgilerini Yazdir[2]Personel Bilgilerini Guncelle[3] Personel Sil[4]): ");
			}
		}while(secim2!=1 || secim2!=2 || secim2!=3 || secim2!=4);
	}
void icMenu3(){
	int secim2;
	printf("\nDeneme Sinav Sonuclarini Goster[1]\nSiniflari Goster[2]\nSinav Sonucu Gir[3]\nDers Programi Goster[4]\nMenuye Geri Don[5]\nSecim: ");
	do{
		scanf("%d",&secim2);
		if(secim2==1){
			sinavSonucu();
			break;
		}
		else if(secim2==2){
			sinifGoster();
			break;
		}
		else if(secim2==3){
			sinavGir();
			break;
		}
		else if(secim2==4){
			dersProgrami();
			break;
		}
		else if(secim2==5){
			secim=0;
			break;
		}
		else{
			printf("\nYanlis Secim Yaptiniz!");
		}
	}while(secim2!=1 || secim2!=2 ||secim2!=3 ||secim2!=4);
}
int main(void) {
	Menu();
	do{
		system("cls");
		switch(secim){
		case 1:
			icMenu1();
			break;
		case 2:
			icMenu2();
			break;
		case 3:
			icMenu3();
			break;
		case 4:
			cariHareketler();
			break;
		default:
			Menu();
			break;
		}
	}while(secim!=5);

	return EXIT_SUCCESS;
}


