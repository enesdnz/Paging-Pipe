//ilgili kutuphanelerin import edilmesi
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* myMore programi tek basina calisamaz sadece myData
programi ile birlikte calisabilir 
eger programa =myMore parametresi 
verilirse bu program calisir*/

#define SATIR_SAYISI 24
#define MAX_SATIR_SAYISI 100
#define BUFFER_SIZE  20000


int main(int argc, char *argv[])
{
	char pid[10];
	char parentPid[10];
	char mesajOkuma [MAX_SATIR_SAYISI][BUFFER_SIZE];

	//programdan gelen parametreleri degiskenlere atiyoruz
	char *alinanPid = argv[1];
	char *alinanParentPid = argv[2];
	char *alinanVeri = argv[3];
	
	//olusturulan processin pid ve ppid degerlerini aliyoruz
	int pidDegeri = getpid();
	int parentPidDegeri = getppid();

	//alinan degerleri sprintf yardimi ile icine yaziyoruz
	sprintf(pid, "%d", pidDegeri);
	sprintf(parentPid, "%d", parentPidDegeri);

	//gonderilen veri okunuyor
	
	//read(alinanVeri, &mesajOkuma, SATIR_SAYISI * BUFFER_SIZE);
		
	/* parametreden cektigimiz pid ve ppid degerlerini
	processin pid ve ppid degerleri ile karsilastiriyoruz
	eger eslesmiyorsa hata mesajı yazdiriyoruz
	eslesiyorsa veriyi ekrana bastiriyoruz */
	if (strcmp(pid, alinanPid) != 0 && strcmp(parentPid, alinanParentPid) != 0)
	{
		printf("myMore dosyasi parenti olmadan calisamaz...");
	}
	else
	{
		for (int i = 0; i < SATIR_SAYISI; ++i)
    	{
        	printf("%s", alinanVeri);
    	}
	}

	/* execl ile calistiralan program tek basina calisamaz 
	   pid, ppid degerleri ustunde calisan program ile aynidir. */
	close((int)alinanVeri);
	return 0;

}