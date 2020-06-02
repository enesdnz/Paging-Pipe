## Operating Systems Term Project
### Projenin Amacı
myData programını çalıştırarak parametre olarak verilen txt dosyasının tümüyle okunması amaçlanmıştır. 
myMore isimli bir program daha oluşturulmuştur. Bu program myData’ya “=myMore” şeklinde parametre olarak verilirse txt dosyası 
içerisindeki veriler 24 satır halinde okunur, kullanıcıya devam edip etmeyeceği sorulur. 
Kullanıcı “Boşluk” tuşuna basarsa veri 24 satır daha okunacak “q” tuşuna basarsa uygulama son bulacaktır.<br><br>

### Nasıl Çalıştırılır?
1. myData.c ve myMore.c dosyaları compile edilir.<br><br>
```gcc myData.c -o myData.c -lpthread```<br>
```gcc myMore.c -o myMore.c -lpthread```<br><br>
2. Derlenen dosyaya parametre verilerek program başlatılır.<br><br>
  2.1 Dosyanın tümü okunacak ise;<br>
```./myData <FileName.txt>```<br><br>
   2.2 Dosya 24 satır halinde okunacak ise;<br>
```./myData <FileName.txt>=myMore```<br>
