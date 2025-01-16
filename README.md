# proje-3
Proje Açıklaması

Bu proje, TM4C123G mikrodenetleyicisi kullanarak bir 16x2 LCD ekranında "DOGA" kelimesini görüntülemeyi amaçlamaktadır. Kod, HD44780 uyumlu LCD'yi 4-bit modda çalıştırır ve karakterleri tek tek char tipi ile LCD'ye yazar.

Donanım Gereksinimleri

TM4C123G Mikrodenetleyici (Tiva C LaunchPad)

16x2 LCD (HD44780 uyumlu)

Bağlantı Kabloları

Breadboard

5V Güç Kaynağı (Tiva C'nin 5V çıkışı kullanılabilir)

Donanım Bağlantıları

Aşağıda LCD pinlerinin TM4C123G GPIO pinlerine nasıl bağlanacağını gösteren açıklamalar bulunmaktadır:

RS (Register Select): PB0 pinine bağlanır. Bu pin, komut ve veri modu arasında geçiş yapmak için kullanılır.

RW (Read/Write): PB1 pinine bağlanır. LCD'nin okuma/yazma modunu kontrol eder (genellikle yazma için kullanılır).

EN (Enable): PB2 pinine bağlanır. LCD'ye veri gönderimi sırasında etkinlik sağlar.

D4, D5, D6, D7 (Veri Hatları): Sırasıyla PB4, PB5, PB6 ve PB7 pinlerine bağlanır.

VSS: Toprak bağlantısı (GND).

VDD: 5V besleme bağlantısı.

V0: Kontrast ayarı için potansiyometreye bağlanır.

A (LED+): Arka ışık için 5V'a bağlanır (direnç üzerinden).

K (LED-): Arka ışık için GND'ye bağlanır.

Bağlantıları doğru şekilde yaparak LCD'nin çalışmasını sağlayabilirsiniz.

Yazılım Gereksinimleri

 Code Composer Studio (CCS)

TM4C123G TivaWare Library 

Kodun Özeti

LCD_Init: LCD ekranını 4-bit modda başlatır.

LCD_Command: LCD'ye komut gönderir (örneğin, ekran temizleme, imleç ayarı).

LCD_Data: LCD'ye veri (karakter) gönderir.

Main:

GPIO yapılandırmasını yapar.

LCD'yi başlatır.

"DOGA" kelimesini tek tek karakter olarak LCD'ye yazar.

Gecikme Fonksiyonları

delayMs: Milisaniye cinsinden gecikme sağlar.

delayUs: Mikrosaniye cinsinden gecikme sağlar.

Çalıştırma Adımları

Donanımı yukarıdaki bağlantı şemasına göre kurun.

Kod dosyasını uygun bir IDE'ye yükleyin (Keil veya CCS).

Kodun mikrodenetleyiciye derlenmesini ve yüklenmesini sağlayın.

Kod yüklendikten sonra LCD'de "DOGA" kelimesi görüntülenecektir.

Önemli Notlar

LCD'nin kontrastını potansiyometre ile ayarlamayı unutmayın.

GPIO pinlerinin doğru yapılandırıldığından emin olun.

Kullanılan gecikme fonksiyonları işlemci frekansına bağlıdır. Bu kod, TM4C123G'nin varsayılan 16 MHz sistem saatine göre ayarlanmıştır.

Hata Ayıklama

LCD'de hiçbir şey görünmüyorsa:

LCD'nin güç bağlantılarını kontrol edin.

Potansiyometre ile kontrastı ayarlayın.

GPIO pin bağlantılarını doğrulayın.

Ekranda garip karakterler görünüyorsa:

Veri hatlarının (D4-D7) doğru bağlandığını kontrol edin.

Kodun doğru şekilde derlendiğinden emin olun.

Lisans

Bu proje MIT Lisansı altında sunulmaktadır. Kullanım ve dağıtım serbesttir.

