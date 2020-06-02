//ilgili kütüphanelerin import edilmesi
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

/* Programin calismasi icin terminal ekranina 
   ./myData <TXT DOSYASININ ADI> yazilir.
   eger dosyayi 24 satir halinde okumak isterseniz 
   ./myData <TXT DOSYASININ ADI>=myMore yazilir.
*/

//pipe okuma-yazma islemleri icin
#define OKUMA 0
#define YAZMA 1

//Okunacak dosyanin byte cinsinden boyutunu dondurur
int dosyaBoyutu(FILE *dosya)
{
    fseek(dosya, 0L, SEEK_END);
    int dosyaBoyutu = ftell(dosya);
    fseek(dosya, 0L, SEEK_SET);

    return dosyaBoyutu;
}

int main(int argc, char *argv[])
{
	//kullanilacak degiskenlerin tanimlanmasi
	char readBuffer[20000];
	char kullaniciGiris[10];
	int process[2];
	int processRead;

	//process olusturma ve forklama islemi
	pid_t pid;
	pid = fork();

	// Çatallandırma başarısız olursa hata verecek
	if (pid < 0)
    {
        fprintf(stderr, "Forklama islemi basarisiz oldu.");
        return 1;
    }

	//child process islemleri bu blok icerisinde gerceklestirilecek
	//bu process myMore programını calistiracaktir
	if (pid == 0)
    {
		//child processe yazma islemini kapatiyoruz
		close(process[YAZMA]);

		//pipe okundugu surece dongu icindeki islemler devam edecek
		while ((processRead = read(process[OKUMA], readBuffer, 20000)) > 0)
		{
			if (fork() != 0)
				printf("Pipe forklanırken hata meydana geldi..\n");
			//fork islemi basari ile gerceklesmisse 
			//pid, ppid degerleri ve yazilacak olan veri myMore'a gonderilir
			else{
				//pid ve ppid degiskenlerini tanimliyoruz
				char pid[10];
				char ppid[10];
				//olusturulan processin pid ve ppid degerlerini aliyoruz
				int pidDegeri = getpid();
				int ppidDegeri = getppid();
				//alinan degerleri sprintf yardimi ile icine yazdiriyoruz
				sprintf(pid, "%d", pidDegeri);
				sprintf(ppid, "%d", ppidDegeri);

				// execl sayesinde myMore uygulamizi calistiriyoruz ve parametrelerimizi gonderiyoruz
				execl("./myMore", pid, ppid, readBuffer, NULL);
			}
		
		}
    }

	//parent process islemleri bu blok icerisinde gerceklestirilecek
	if (pid > 0)
	{
		//Parametreyi okumaya calisiyoruz
		char *ptr = strtok(argv[1], "=");
		char *dosyaAdi = ptr;
		char *processAdi = "";

		//degiskene atama islemlerini burada yapiyoruz
		while (ptr != NULL)
		{
			ptr = strtok(NULL, "=");
			
			if (ptr == NULL)
			{
				printf("Program basari ile calisti...\n");
			}
			else
			{
				processAdi = ptr;
			}
			
		}

		//Dosya acma islemleri
		FILE *dosya = fopen(dosyaAdi, "r");
		FILE *yeniDosya = fopen(dosyaAdi, "r");

		char yeniDosyaSatir[200];
		int satirSayisi = 0;

		while (fgets(yeniDosyaSatir, 200, yeniDosya))
		{
			satirSayisi++;
		}
		fclose(yeniDosya);
			
		//eger parametrede myMore yazılmamıs ise butun satirlari yazdiriyoruz
		if (strcmp(processAdi, "myMore") != 0)
		{
			char satir[200];

			while (fgets(satir, 200 ,dosya) != NULL) 
			{	
				//dosyadaki butun veriler ekrana bastirilir
				printf(satir,stdout); 
			}
			printf("\nDosya okundu ve butun satirlar yazdirildi.\n");
			//dosya kapatiliyor
			fclose(dosya);
				
		}
		else{	
			//eger parametrede myMore yazilmissa veriler pipe ile gonderilecek
			//24 satir sekilde yazdiralacak
			char pipeVeri[20000];
			char satir[200]; 

			printf("=myMore parametresi girildi dosyadan 24 satir okunacak..\n");

			int sayac = 0;

			//satirlar okundugu surece dongu icindeki eylemler gerceklesecek
			while (strcmp(kullaniciGiris, "q") !=0 && fgets(satir, 200, dosya) !=NULL) 
			{
				strcat(pipeVeri, satir);
				sayac++;
				
				if (sayac == satirSayisi || sayac % 24 ==0 )
				{
					// pipe'a yazma islemini gerceklestiriyoruz
					write(process[YAZMA], pipeVeri, 20000);
					strcpy(pipeVeri, "");
					strcpy(kullaniciGiris, "");
					
					//eger sayac, satirSayisinden kucukse kullaniciyi ne yapacagini soruyoruz
					if (sayac < satirSayisi)
					{	
						//kullanicinin yaptigi tus girisine gore uygulama devam edecek ya da sonlanacak
						while (strcmp(kullaniciGiris, " ") != 0 && strcmp(kullaniciGiris, "q") != 0)
						{
							printf("Devam etmek icin 'space', Programdan cikis yapmak icin 'q' tusuna basiniz.\n");
							scanf ("%[^\n]%*c", kullaniciGiris); //kullanicidan girdigi tus bilgisi aliniyor
						}
						
					}
					
				}
			}
			//dosya kapatiliyor
			fclose(dosya);
		}
	}
	return 0;
}
