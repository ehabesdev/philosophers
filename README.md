# 🍽️ Philosophers: Bir Senkronizasyon Senfonisi 🧠

[![Dil](https://img.shields.io/badge/Dil-C-00599C.svg?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Okul](https://img.shields.io/badge/Okul-42%20Kocaeli-000000.svg?style=for-the-badge&logo=42)](https://www.42kocaeli.com.tr)
[![Norm](https://img.shields.io/badge/Norm-v4-42B600.svg?style=for-the-badge)](https://github.com/42school/norminette/blob/master/pdf/tr.norm.pdf)

Bu proje, [42 Okulları](https://www.42kocaeli.com.tr) müfredatının bir parçası olarak geliştirilmiştir. Bilgisayar bilimlerinin klasikleşmiş senkronizasyon problemlerinden biri olan **Yemek Yiyen Filozoflar** probleminin C dilinde, `pthreads` (POSIX threads) kütüphanesi kullanılarak çözüldüğü bir simülasyondur. Amaç, filozofların açlıktan ölme (starvation) veya sonsuz bir kilitlenmeye (deadlock) girme tehlikesi olmadan nasıl senkronize bir şekilde yemek yiyebileceklerini göstermektir.

---

## 📜 Problem: Felsefi Bir İkilem Masada Çözülüyor

N filozof, dairesel bir masa etrafında oturmuş, ya derin düşüncelere dalmış ya da acıkmışlardır. Her filozofun yemek yiyebilmesi için hem solundaki hem de sağındaki çatalı alması gerekir. Ancak masada, her iki filozof arasında bir tane olmak üzere toplam N adet çatal bulunur. Bu durum, kaynak paylaşımı ve senkronizasyonun kritik olduğu bir senaryo yaratır.

**Karşılaşılan Temel Zorluklar:**
* 🌀 **Deadlock (Kilitlenme):** Her filozofun aynı anda sol (veya sağ) çatalı alıp diğerini beklemesi sonucu kimsenin ilerleyemediği durum.
* ⏳ **Starvation (Aç Kalma):** Bir veya daha fazla filozofun, kaynaklara (çatallara) adil bir şekilde erişemeyip sürekli aç kalması.
* 🤝 **Kaynak Yarışması (Race Condition):** Paylaşılan kaynaklara (çatallar, durum bilgileri) eş zamanlı erişimden kaynaklanabilecek tutarsızlıklar.

Bu proje, bu zorlukların üstesinden gelmek için dikkatli bir senkronizasyon stratejisi ve mutex kullanımını sergiler.

---

## ✨ Projenin Parlayan Özellikleri

* **🧵 Multithreading ile Eş Zamanlılık:** Her bir filozof, kendi yaşam döngüsünü ayrı bir iş parçacığında (thread) sürdürür.
* **🔒 Mutex ile Güvenli Kaynak Erişimi:** Çatallar ve paylaşılan simülasyon verileri, `pthread_mutex_t` kullanılarak kilitlenir, böylece veri bütünlüğü ve tutarlılık sağlanır.
* **🚦 Deadlock Önleme Stratejisi:** Filozofların çatal alma sırasına getirilen bir düzen (bu projede filozof ID'sinin çift/tek olmasına göre çatal alma önceliği değiştirilerek döngüsel bekleme engellenmeye çalışılır) ile kilitlenme riski minimize edilir.
* **⏱️ Hassas Zaman Yönetimi:** `gettimeofday` ile milisaniye hassasiyetinde zaman takibi ve `usleep` ile kontrollü beklemeler sayesinde filozofların eylemleri (yemek, uyuma, ölme süresi) doğru bir şekilde simüle edilir.
* **🔧 Esnek Simülasyon Parametreleri:** Filozof sayısı, yaşam süresi (`time_to_die`), yemek yeme süresi (`time_to_eat`), uyuma süresi (`time_to_sleep`) ve opsiyonel olarak her filozofun yemesi gereken minimum yemek sayısı (`number_of_times_each_philosopher_must_eat`) program çalıştırılırken argüman olarak verilebilir.
* **📢 Anlık Durum Raporlaması:** Her filozofun önemli eylemleri (çatal aldı, yemek yiyor, uyuyor, düşünüyor, öldü) zaman damgasıyla birlikte standart çıktıya yazdırılır, böylece simülasyonun akışı kolayca takip edilebilir.

---

## ⚙️ Kurulum ve Derleme Süreci

Projenizi hayata geçirmek için sisteminizde `gcc` (GNU Compiler Collection) ve `pthreads` kütüphanesinin kurulu olması gerekmektedir.

1.  **Projeyi Klonlayın:**
   
    ```bash
    git clone git@github.com:ehabesdev/philosophers.git philo
    cd philo
    ```

3.  **Derleme:**
    Aşağıdaki komutla derleyebilirsiniz:
    
    ```bash
    make
    ```

---

## 🚀 Simülasyonu Başlatma

Derlenen `philo` programını aşağıdaki formatta komut satırı argümanlarıyla çalıştırın:

```bash
./philo <filozof_sayisi> <olum_suresi_ms> <yemek_suresi_ms> <uyuma_suresi_ms> [hedef_yemek_sayisi]
```

---

## ⚙️ Argümanların Detayları

Programınız, simülasyonun davranışını belirleyen komut satırı argümanları ile çalışır. Bu argümanların doğru ve beklenen formatta girilmesi, simülasyonun sağlıklı bir şekilde başlaması için kritik öneme sahiptir.

* `number_of_philosophers` (Filozof Sayısı)
    * **Açıklama:** Simülasyondaki toplam filozof sayısını ve dolayısıyla masadaki toplam çatal sayısını belirtir.
    * **Veri Tipi:** Pozitif bir tam sayı ($N > 0$).
    * **Kısıtlamalar:** Mantıksal olarak en az 1 filozof olmalıdır. Tek bir filozof olması durumu özel olarak ele alınır (çatal alamayacağı için açlıktan ölecektir). Projeniz, genellikle 200'den fazla filozof için test edilmeyebilir veya kaynak limitlerine takılabilir, ancak bu proje özelindeki bir üst sınıra bağlıdır.
    * **Örnek:** `5` (5 filozoflu bir simülasyon)

* `time_to_die` (Ölüm Süresi - Milisaniye)
    * **Açıklama:** Bir filozofun son yemeğini yediği andan itibaren veya simülasyonun başlangıcından itibaren ne kadar süre (milisaniye cinsinden) aç kalabileceğini belirler. Eğer bir filozof bu süre zarfında tekrar yemek yiyemezse, "ölür" ve simülasyon sonlanır.
    * **Veri Tipi:** Negatif olmayan bir tam sayı (milisaniye).
    * **Kısıtlamalar:** Genellikle pozitif bir değer olması beklenir. `0` verilmesi durumunda filozoflar anında ölebilir.
    * **Örnek:** `800` (bir filozofun açlıktan ölmesi için 800 milisaniye)

* `time_to_eat` (Yemek Yeme Süresi - Milisaniye)
    * **Açıklama:** Bir filozofun, her iki çatalı da aldıktan sonra yemek yemesi için harcadığı süreyi (milisaniye cinsinden) belirtir. Bu süre boyunca filozof, çatalları meşgul eder.
    * **Veri Tipi:** Negatif olmayan bir tam sayı (milisaniye).
    * **Kısıtlamalar:** Genellikle pozitif bir değer olması beklenir. `0` verilmesi durumunda yemek yeme anlık gerçekleşir.
    * **Örnek:** `200` (bir filozofun yemek yemesi 200 milisaniye sürer)

* `time_to_sleep` (Uyuma Süresi - Milisaniye)
    * **Açıklama:** Bir filozofun, yemeğini bitirip çatallarını bıraktıktan sonra uyuması için harcadığı süreyi (milisaniye cinsinden) belirtir.
    * **Veri Tipi:** Negatif olmayan bir tam sayı (milisaniye).
    * **Kısıtlamalar:** Genellikle pozitif bir değer olması beklenir. `0` verilmesi durumunda uyuma anlık gerçekleşir.
    * **Örnek:** `200` (bir filozofun uyuması 200 milisaniye sürer)

* `[number_of_times_each_philosopher_must_eat]` (Hedef Yemek Sayısı - Opsiyonel)
    * **Açıklama:** Bu, isteğe bağlı bir argümandır. Eğer bu argüman verilirse, simülasyon, tüm filozoflar en az bu sayıda yemek yediğinde "başarıyla" tamamlanmış sayılır ve sonlanır. Eğer bir filozof bu hedefe ulaşamadan `time_to_die` süresi geçerse, yine ölür ve simülasyon sonlanır.
    * **Veri Tipi:** Pozitif bir tam sayı.
    * **Kısıtlamalar:** Eğer verilirse, pozitif bir değer olmalıdır.
    * **Örnek:** `7` (her filozofun simülasyonun başarıyla bitmesi için en az 7 kez yemek yemesi gerekir)
    * **Not:** Bu argüman verilmezse, simülasyon yalnızca bir filozof öldüğünde sonlanır.

Tüm zaman argümanları (`time_to_die`, `time_to_eat`, `time_to_sleep`) milisaniye (ms) cinsinden ifade edilir. Argümanların geçerliliği (örneğin, sayısal olup olmadıkları, pozitif olup olmadıkları) programınızın `args.c` veya benzeri bir modülünde kontrol edilmelidir. Hatalı argüman girişlerinde programınızın kullanıcıyı bilgilendiren bir hata mesajı verip sonlanması beklenir.

---

### ✨ Örnek Kullanımlar

Aşağıda, programınızı farklı senaryolarla nasıl çalıştırabileceğinize dair birkaç örnek bulunmaktadır:

1.  **Temel Senaryo (Yemek Hedefi Olmadan):**

    * **Açıklama:** 5 filozofun bulunduğu, her birinin ölmek için 800ms, yemek yemek için 200ms ve uyumak için 200ms süresinin olduğu bir simülasyon. Opsiyonel yemek sayısı hedefi belirtilmediği için simülasyon bir filozof ölene kadar devam eder.
    * **Parametreler:**
        * Filozof Sayısı: `5`
        * Ölüm Süresi: `800` ms
        * Yemek Yeme Süresi: `200` ms
        * Uyuma Süresi: `200` ms
    * **Komut:**
        ```bash
        ./philo 5 800 200 200
        ```

2.  **Yemek Hedefli Senaryo:**

    * **Açıklama:** 4 filozofun bulunduğu, her birinin ölmek için 410ms, yemek yemek için 200ms ve uyumak için 200ms süresinin olduğu bir simülasyon. Ek olarak, her filozofun simülasyonun başarıyla tamamlanması için en az 7 kez yemek yemesi gerekmektedir.
    * **Parametreler:**
        * Filozof Sayısı: `4`
        * Ölüm Süresi: `410` ms
        * Yemek Yeme Süresi: `200` ms
        * Uyuma Süresi: `200` ms
        * Hedef Yemek Sayısı: `7`
    * **Komut:**
        ```bash
        ./philo 4 410 200 200 7
        ```

3.  **Tek Filozof Senaryosu (Kenar Durum Testi):**

    * **Açıklama:** Sadece 1 filozofun bulunduğu özel bir durum. Bu senaryoda, filozofun ikinci bir çatalı alması mümkün olmayacağından, `time_to_die` süresi sonunda açlıktan ölmesi beklenir. Bu, programın bu tür kenar durumları doğru yönetip yönetmediğini test etmek için önemlidir.
    * **Parametreler:**
        * Filozof Sayısı: `1`
        * Ölüm Süresi: `800` ms
        * Yemek Yeme Süresi: `200` ms
        * Uyuma Süresi: `200` ms
    * **Komut:**
        ```bash
        ./philo 1 800 200 200
        ```

Bu örnekler, programınızın temel işlevselliğini ve farklı parametre kombinasyonlarına nasıl tepki verdiğini göstermeye yardımcı olur. Kendi test senaryolarınızı oluşturarak programınızı daha kapsamlı bir şekilde değerlendirebilirsiniz.

---

## 📁 Proje Dosya Yapısı ve İçerikleri

Proje, modüler bir yaklaşımla organize edilmiştir. Temel yapısı şu şekildedir:

```text
philo/
├── include/
│   └── philo.h         # 🌟 Ana başlık dosyası: Tüm yapılar, sabitler ve fonksiyon prototipleri
├── src/
│   ├── philo.c         # 🏁 main(): Simülasyonun orkestrasyonu
│   ├── args.c          # 📥 Argümanların parse edilmesi ve doğrulanması
│   ├── init.c          # 🌱 Simülasyon verilerinin (filozoflar, mutexler) hazırlanması
│   ├── actions.c       # 🍴 Filozof eylemleri: çatal al, ye, uyu, düşün
│   ├── philo_routine.c # 🔄 Her filozofun bireysel yaşam döngüsü (thread fonksiyonu)
│   ├── monitoring.c    # 👀 Simülasyonun genel durumunu izleme (ölüm kontrolü, yemek hedefi)
│   ├── simulation.c    # 🚀 Thread'lerin oluşturulması ve sonlanmalarının beklenmesi
│   ├── status_utils.c  # ✍️ Durum mesajlarının formatlanıp yazdırılması, stop bayrağı kontrolü
│   ├── time_utils.c    # ⏳ Zamanla ilgili hassas yardımcı fonksiyonlar
│   ├── utils.c         # 🛠️ Genel yardımcı fonksiyonlar (hata yönetimi, ft_atoi_check)
│   └── cleanup.c       # 🧹 Simülasyon sonrası kaynakların (bellek, mutexler) temizlenmesi
└── Makefile            # 🔨 Derleme scripti
```

Her bir .c dosyası, problemin belirli bir yönünü ele alarak kodun okunabilirliğini ve bakımını kolaylaştırır. 
philo.h ise tüm bu parçaları bir araya getiren merkezi bir başlık dosyasıdır.

---

## 🙏 Teşekkürler

Bu projeyi incelediğiniz ve zaman ayırdığınız için teşekkür ederim! Umarım "Yemek Yiyen Filozoflar" probleminin bu C implementasyonu, eş zamanlılık ve senkronizasyon konularını anlamanıza yardımcı olmuştur.

Eğer bir 42 öğrencisiyseniz, bu projenin zorlukları ve öğrenme süreci hakkında sizinle de sohbet etmekten mutluluk duyarım. Başarıya giden yolda karşılaşılan her problem, yeni bir öğrenme fırsatıdır!

**Özel Teşekkürler:**

* **42 Kocaeli** ekibine ve eğitmenlerine, bu öğrenme yolculuğunda sundukları destek ve kaynaklar için.
* Bu problemi daha önce çözmüş ve deneyimlerini paylaşmış olan tüm geliştiricilere.
* Açık kaynak topluluğuna ve C dilinin sunduğu güçlü araçlara.


**Bu Projeyle İlgili Soru ve Geri Bildirimleriniz İçin:**

Proje hakkında herhangi bir sorunuz, hata bildirimi, özellik isteğiniz veya genel bir geri bildiriminiz varsa, lütfen bu GitHub deposunun aşağıdaki bölümlerini kullanmaktan çekinmeyin:

* 👉 **[Issues Bölümü](https://github.com/ehabesdev/philosophers/issues):** Hataları bildirmek, soru sormak veya yeni özellikler önermek için idealdir.

Eğer GitHub profilimde herkese açık bir e-posta adresim bulunuyorsa, oradan da genel konular için ulaşabilirsiniz. Ancak projeye özel konular için yukarıdaki depo bazlı iletişim kanallarını tercih etmeniz, takibi kolaylaştıracaktır.


Afiyet olsun ve kodlamaya devam! 🚀

---
