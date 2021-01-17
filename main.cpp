/*
Burak Boz
Cash Buffer
Bu program bir web taray�c�s�n�n �nbellek tamponunu modellemektedir.
txt dosyas�ndan al�nan veriler birer internet sitesi iste�i olarak kabul etdilmektedir.
Belli bir e�ik de�erinden fazla kez istek alan sayfalar tampon belle�in ilk s�ras�na al�n�r.
Linkli liste yap�s� kullan�lm��t�r.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
struct node {//Ana d���m yap�m�z
 
    char req[100];
    int sayac=0;
    struct node *next;
    struct node *prev;
};

struct node* start = NULL;
 

struct node* dugumOlustur(char veri[100]) //D���m�n olu�mas�n� sa�layan fonksiyonumuz
{
    struct node* yeniDugum = (struct node*)malloc(sizeof(struct node));//Bellek �zerinde d���m�m�z i�in alan a��yoruz
    strcpy(yeniDugum->req,veri);//d���me girece�imiz site adresini d���m�n gerekli alan�na at�yoruz
    yeniDugum->sayac=1;//ilk defa eklenen d���m i�in sayac�n� 1 olarak ilklendiriyoruz
    yeniDugum->next = NULL;
    yeniDugum->prev = NULL;
 
    return yeniDugum;
}

int kontrolEt(char veri[100],int esikDegeri)//D���m olu�turmak i�in gerekli ko�ullar�n kontrol�
{
	int kontrolSayac=0;
	char tmpVeri[100];
	strcpy(tmpVeri,veri);
	struct node* temp = start;
    while (temp->next != NULL && strcmp(temp->req,tmpVeri))//Gelen site adresi ile mevcut d���mlerin adreslerini bu d�ng� i�erisinde kontrol edece�iz
    {
        temp = temp->next;
	}
	
	
	if(strcmp(temp->req,tmpVeri) == 0)//Gelen site adresi ile d���mdeki site adresinin ayn� olup olmad���n� kontrol ediyoruz
	    {
	    	temp->sayac++;//E�er d���m mevcutsa saya� de�erini 1 artt�r�yoruz
	    	kontrolSayac++;
	    	
	    	if(temp->sayac>=esikDegeri)
	    	{
	    		//Ba�a �ek
	    		if(temp != start){
	    			temp->prev->next=temp->next;
		    		if(temp->next != NULL){
						temp->next->prev=temp->prev;
					}
		    		temp->next=start;
		    		start->prev = temp;
		    		start=temp;
		    		temp->prev=NULL;
				}
	    		
			}
		}
	if	(kontrolSayac!=0)
	{
		return 1;
	}
	return 0;
}

void sonaEkle(char veri[100],int esikDegeri)//En sona yeni bir d���m eklemek i�in kullan���m�z fonksiyon
{
    struct node* sonaEklenecek = dugumOlustur(veri);
 
    
    if (start == NULL)//Listemizin i�erisinde hi� eleman yoksa ilk eleman�m�z� ekliyoruz
    {
        start = sonaEklenecek;
    }
 
    else//E�er liste i�erisinde eleman varsa
    {
    	if(kontrolEt(veri,esikDegeri))//kontrolEt fonksiyonundan 1 d�nerse d���m eklemiyoruz
    	{
    		
		}
		else{//kontrolEt fonksiyonundan 0 d�nerse d���m ekliyoruz
			
	        struct node* temp = start;//Start de�erini kaybetmemek i�in temp de�erine kopyal�yoruz
	 
	        
	        while (temp->next != NULL)//Son d���m�n next de�erini buluyoruz
	        {
	            temp = temp->next;
	        }
	 
	        
	        sonaEklenecek->prev = temp;//Sona ekleyece�imiz d���m�n prev de�erine liste i�erisindeki var olan son de�eri ekliyoruz
	 
	        
	        temp->next = sonaEklenecek;	//Listede var olan son d���m�n next de�erine yeni ekleyece�imiz d���m� i�aret ediyoruz
		}
        
    }
}



void basaEkle(char veri[100])//E�er hi� d���m�m�z yoksa ilk olarak bu fonksiyonla ilk d���m� ekleyece�iz
{
    struct node* basaEklenecek = dugumOlustur(veri);
 
    if (start == NULL)
    {
        start = basaEklenecek;
        return;
    }
 
    start->prev = basaEklenecek;
    basaEklenecek->next = start;
    start = basaEklenecek;
}

void sondanSil()//E�er kullan�c�n�n girdi�i maksimum istek say�s�na ula��ld�ysa sondaki d���m� silmek i�in bu fonksiyonu kullanaca��z
{
    if (start == NULL)
    {
        printf("\n Liste zaten bos ....");
        return;
    }

 
    struct node* temp = start;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
 
    struct node* onceki = temp->prev;
    free(temp);
    onceki->next = NULL;
}

void yazdir()//D���mlerimizi yazd�rmak i�in bu fonksiyonu kullan�yoruz
{
    struct node* temp = start;
 
    while (temp != NULL)
    {
        printf("Site: %s\t Sayac: %d\n", temp->req, temp->sayac);
        //printf(" %d", temp->sayac);
        temp = temp->next;
    }
}


int main(){
	int nodeSayac=0,esik,maxAdet;
	printf("Esik degeri giriniz:");
	scanf("%d", &esik);
	printf("Tutulabilecek maksimum site sayisini giriniz:");
	scanf("%d", &maxAdet);
	FILE *fp=fopen("dosya.txt","r");
	char bilgi[1000];
	while(!feof(fp)){
		fscanf(fp,"%s",bilgi);
		
		if (nodeSayac<maxAdet)
		{
			
			sonaEkle(bilgi,esik);
			nodeSayac++;
		}
		else
		{
			sondanSil();
			sonaEkle(bilgi,esik);
		}
	}
	yazdir();
	char cevap;
	printf("\nBellekteki verilerin silinmesini istiyormusunuz:(y: evet / n:hayir)");
	cevap = getch();
	if(cevap =='Y' || cevap=='y')
	{
		//belle�i bo�alt
		while(start->next != NULL){
			sondanSil();
		}
		
		free(start);
		printf("\nVeriler temizlendi");
		
	}else if(cevap=='N' || cevap=='n')
	{
		//Veriler dursun
	}
	return 0;

}
