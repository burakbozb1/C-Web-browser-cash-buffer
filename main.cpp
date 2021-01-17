/*
Burak Boz
Cash Buffer
Bu program bir web tarayýcýsýnýn önbellek tamponunu modellemektedir.
txt dosyasýndan alýnan veriler birer internet sitesi isteði olarak kabul etdilmektedir.
Belli bir eþik deðerinden fazla kez istek alan sayfalar tampon belleðin ilk sýrasýna alýnýr.
Linkli liste yapýsý kullanýlmýþtýr.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
struct node {//Ana düðüm yapýmýz
 
    char req[100];
    int sayac=0;
    struct node *next;
    struct node *prev;
};

struct node* start = NULL;
 

struct node* dugumOlustur(char veri[100]) //Düðümün oluþmasýný saðlayan fonksiyonumuz
{
    struct node* yeniDugum = (struct node*)malloc(sizeof(struct node));//Bellek üzerinde düðümümüz için alan açýyoruz
    strcpy(yeniDugum->req,veri);//düðüme gireceðimiz site adresini düðümün gerekli alanýna atýyoruz
    yeniDugum->sayac=1;//ilk defa eklenen düðüm için sayacýný 1 olarak ilklendiriyoruz
    yeniDugum->next = NULL;
    yeniDugum->prev = NULL;
 
    return yeniDugum;
}

int kontrolEt(char veri[100],int esikDegeri)//Düðüm oluþturmak için gerekli koþullarýn kontrolü
{
	int kontrolSayac=0;
	char tmpVeri[100];
	strcpy(tmpVeri,veri);
	struct node* temp = start;
    while (temp->next != NULL && strcmp(temp->req,tmpVeri))//Gelen site adresi ile mevcut düðümlerin adreslerini bu döngü içerisinde kontrol edeceðiz
    {
        temp = temp->next;
	}
	
	
	if(strcmp(temp->req,tmpVeri) == 0)//Gelen site adresi ile düðümdeki site adresinin ayný olup olmadýðýný kontrol ediyoruz
	    {
	    	temp->sayac++;//Eðer düðüm mevcutsa sayaç deðerini 1 arttýrýyoruz
	    	kontrolSayac++;
	    	
	    	if(temp->sayac>=esikDegeri)
	    	{
	    		//Baþa çek
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

void sonaEkle(char veri[100],int esikDegeri)//En sona yeni bir düðüm eklemek için kullanýðýmýz fonksiyon
{
    struct node* sonaEklenecek = dugumOlustur(veri);
 
    
    if (start == NULL)//Listemizin içerisinde hiç eleman yoksa ilk elemanýmýzý ekliyoruz
    {
        start = sonaEklenecek;
    }
 
    else//Eðer liste içerisinde eleman varsa
    {
    	if(kontrolEt(veri,esikDegeri))//kontrolEt fonksiyonundan 1 dönerse düðüm eklemiyoruz
    	{
    		
		}
		else{//kontrolEt fonksiyonundan 0 dönerse düðüm ekliyoruz
			
	        struct node* temp = start;//Start deðerini kaybetmemek için temp deðerine kopyalýyoruz
	 
	        
	        while (temp->next != NULL)//Son düðümün next deðerini buluyoruz
	        {
	            temp = temp->next;
	        }
	 
	        
	        sonaEklenecek->prev = temp;//Sona ekleyeceðimiz düðümün prev deðerine liste içerisindeki var olan son deðeri ekliyoruz
	 
	        
	        temp->next = sonaEklenecek;	//Listede var olan son düðümün next deðerine yeni ekleyeceðimiz düðümü iþaret ediyoruz
		}
        
    }
}



void basaEkle(char veri[100])//Eðer hiç düðümümüz yoksa ilk olarak bu fonksiyonla ilk düðümü ekleyeceðiz
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

void sondanSil()//Eðer kullanýcýnýn girdiði maksimum istek sayýsýna ulaþýldýysa sondaki düðümü silmek için bu fonksiyonu kullanacaðýz
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

void yazdir()//Düðümlerimizi yazdýrmak için bu fonksiyonu kullanýyoruz
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
		//belleði boþalt
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
