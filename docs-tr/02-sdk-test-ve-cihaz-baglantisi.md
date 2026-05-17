# 02 — SDK Testi Açmak ve Cihaza Bağlanmak

> [!NOTE]
> Bu rehber, **[01-sdk-kayit-ve-baslangic.md](01-sdk-kayit-ve-baslangic.md)** adımını tamamladığınızı varsayar. Elinizde `sdkKey` ve `sdkSecret` olmalı; eğer hâlâ yoksa önce o rehbere dönün.

Bu doküman, anahtarlarınızı aldıktan sonra **ilk başarılı API çağrısını yapana kadar** geçen sürecin tamamını anlatır. Adımlar şu sırada:

```
Cihaz seçimi → Ağ kontrolü → HTTP API'yi cihazda etkinleştir → Test aracı kur (Apipost) → İmza scriptini içe aktar → İlk çağrıyı yap
```

---

## 📑 İçindekiler

1. [Ön Koşullar — Cihaz, Ağ, Firmware](#1-ön-koşullar--cihaz-ağ-firmware)
2. [Cihazın IP Adresini Bulma](#2-cihazın-ip-adresini-bulma)
3. [Cihaza Erişimi Kontrol Etme](#3-cihaza-erişimi-kontrol-etme)
4. [HTTP API'yi Cihazda Etkinleştirme (önemli!)](#4-http-apiyi-cihazda-etkinleştirme-önemli)
5. [Apipost Kurulumu ve Koleksiyon İçe Aktarma](#5-apipost-kurulumu-ve-koleksiyon-i̇çe-aktarma)
6. [Environment Variable Kurma — `sdkKey`, `sdkSecret`, IP](#6-environment-variable-kurma--sdkkey-sdksecret-ip)
7. [İmza Üretimi (Pre-Request Script)](#7-i̇mza-üretimi-pre-request-script)
8. [İlk Başarılı API Çağrısı](#8-i̇lk-başarılı-api-çağrısı)
9. [Postman Kullanmak İsteyenler İçin Notlar](#9-postman-kullanmak-i̇steyenler-i̇çin-notlar)
10. [PowerShell ile Hızlı Manuel Test](#10-powershell-ile-hızlı-manuel-test)
11. [Sıkıntı Çözme (Troubleshooting)](#11-sıkıntı-çözme-troubleshooting)
12. [Hızlı Kontrol Listesi (Checklist)](#12-hızlı-kontrol-listesi-checklist)

---

## 1. Ön Koşullar — Cihaz, Ağ, Firmware

### 1.1 Cihaz Model ID'nizi Kontrol Edin

Huidu SDK, **sadece "engineering card" (geliştirici kartı)** olarak işaretlenmiş cihazlarda çalışır. Ayırt edici özellik: **model ID'sinin ortasında `D` harfi** olması.

| Örnek model | SDK destekler mi? |
|---|---|
| `C16L-D00-A000F`     | ✅ Evet (`D` ortasında) |
| `C16L-A00-A000F`     | ❌ Hayır (standart kart) |

![Model ID'sinde D harfi](images/id.png)

> Cihazın etiketine bakın veya HDPlayer/HDSet yazılımında "Device Info / 设备信息" altında görün. Eğer modelinizde `D` yoksa **anahtar yazsanız bile SDK çağrıları çalışmaz** — bayinizden engineering card talep edin.

### 1.2 Firmware Sürümü

**Android serisi cihazlarınız** varsa (A3L, A4L, A5L, A6L, H4K, H8, B8L, A7, A8 vb.) bir sonraki adıma (HTTP API etkinleştirme — Bölüm 4) geçmeden önce **firmware'i en son sürüme güncelleyin**. Resmi doküman bunu özellikle vurgulamıştır:

> *"Just upgrade to the latest firmware for the Android series and skip this step."*
> **Türkçesi:** Android serisi için sadece firmware'i en son sürüme güncelleyin, bu adımı (HTTP SDK etkinleştirme) atlayın.

**Standart seri (ARM/Linux)** cihazlarınız varsa (C16L, C08L, D16, D36 vb.) HTTP API'yi manuel olarak etkinleştirmeniz gerekir (Bölüm 4'e bakın).

### 1.3 Ağ Konumu

Cihaz ile bilgisayarınız **aynı ağda** olmalıdır:

- Aynı router'a kablo / Wi-Fi ile bağlı
- Veya birbirini görebilecek subnet'lerde
- VPN ardındaysanız, VPN'in cihazın bulunduğu ağa erişimi olmalı
- Cihaz GSM modemde / 4G/5G ile internete çıkıyorsa **LAN üzerinden erişemezsiniz** (uzaktan erişim için sunucu modu gerekir — ayrı konu)

### 1.4 Firewall

Bilgisayarınızdan cihaza **TCP/30080 portu** açık olmalı. Şirket ağında firewall varsa IT'ye danışın.

---

## 2. Cihazın IP Adresini Bulma

### Yöntem 1: HDPlayer / HDSet ile LAN tarama (en kolay)

Huidu'nun resmi yazılımları (HDPlayer, HDSet) açıldığında LAN üzerinde **broadcast paketi** atar ve aynı ağdaki tüm Huidu cihazlarını listeler:

```
Device Name   |   Model   |   IP Address     |   MAC                |   Firmware
LED-Tabela-1  |   C16L-D  |   192.168.1.50   |   D8:80:39:XX:XX:XX  |   v3.5.2
```

### Yöntem 2: Router yönetim paneli (DHCP listesi)

Router'ınızın yönetim arayüzüne girin (genelde `192.168.1.1`). "DHCP Clients" / "Connected Devices" listesinde, MAC adresi **D8:80:39** ile başlayan cihazlar Huidu olabilir (üretici OUI).

### Yöntem 3: ARP scan (PowerShell)

```powershell
# Aktif arp tablosu - Huidu MAC prefix
arp -a | Select-String 'd8-80-39'
```

### Yöntem 4: nmap (gelişmiş)

```powershell
# 30080 portu açık olan tüm cihazlar
nmap -p 30080 --open 192.168.1.0/24
```

---

## 3. Cihaza Erişimi Kontrol Etme

IP'yi öğrendikten sonra üç şeyi sırayla doğrulayın:

### 3.1 Ping

```powershell
Test-Connection 192.168.1.50 -Count 4
# veya
ping 192.168.1.50
```

✅ Yanıt geliyorsa cihaz ağda ve sizden ulaşılabilir.

❌ Yanıt gelmiyorsa: kablo / Wi-Fi / VLAN / firewall sorunu — bu adıma dön ve düzelt.

### 3.2 Port 30080 Açık mı?

```powershell
Test-NetConnection 192.168.1.50 -Port 30080
```

Beklenen çıktı:
```
TcpTestSucceeded : True
```

❌ `TcpTestSucceeded : False` görüyorsanız: cihaz ağda var ama HTTP API çalışmıyor. Bölüm 4'e geçin (HTTP API'yi etkinleştirme).

### 3.3 Browser'dan Cihaz Sayfası Açılıyor mu?

Tarayıcıya yazın:
```
http://192.168.1.50:30080/login/
```

✅ Bir login/init sayfası gözükmeli (Bölüm 5 — Yöntem 1 — webPageInit.png'deki sayfa).

❌ Açılmıyorsa: **farklı bir tarayıcı deneyin** (Chrome / Edge / Firefox). Resmi doküman tarayıcı uyumsuzluğunun yaygın olduğunu söylemiştir.

---

## 4. HTTP API'yi Cihazda Etkinleştirme (önemli!)

> [!IMPORTANT]
> ### Hangi Cihazlarda Bu Adım Gerekli?
>
> | Cihaz serisi | Bu adım | Neden |
> |---|---|---|
> | **Android serisi** (A3L, A4L, A5L, A6L, H4K, H8, B8L, A7, A8 ...) | ❌ Gerek yok — sadece firmware'i en son sürüme güncelleyin | HTTP API zaten varsayılan olarak açık geliyor (yeni firmware'larda) |
> | **Standart seri (ARM/Linux)** (C16L, C08L, D16, D36 ...) | ✅ Manuel etkinleştirme zorunlu | Varsayılan kapalı; aşağıdaki XML komutu ile açılmalı |

### 4.1 SDK_Test Aracını Açma

`SDK_Test.exe`, eski tip TCP/XML tabanlı bir Huidu test programıdır. Yeni HTTP API'yi açabilmek için bu eski kanal kullanılır (HTTP API kapalıyken HTTP üzerinden açamazsınız — *chicken-and-egg* sorunu).

**Adımlar:**

1. SDK_Test.rar dosyasını edinin:
   - **GitHub mirror (önerilen):** [tools/SDK_Test.rar](https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror/blob/master/tools/SDK_Test.rar)
   - **Resmi Gitee:** https://gitee.com/szhuidu/cn.huidu.device.sdk/blob/master/tools/SDK_Test.rar
   - **Yerel klonunuzdaysa:** `cn.huidu.device.sdk\tools\SDK_Test.rar`
2. RAR dosyasını **WinRAR / 7-Zip / WinZip** ile çıkartın (`Sağ tık → Extract Here`)
3. Çıkan klasörde **`SDKTest.exe`** dosyasını çift tıklayarak çalıştırın
4. Üst başlığı **"SDKTest - V5.0"** olan bir pencere açılır
5. Aynı klasördeki Çince operasyon kılavuzu (`SDK_Test操作说明.docx`) referans niteliğindedir — gerek duyarsanız çevirisini alın

<!-- TODO-RESIM: docs-tr/images/sdktest-main.png — SDKTest.exe ana ekran (sol panel cihaz listesi, orta XML editör, sağ method listesi) -->

### 4.2 Cihazı Tespit Etme ve Bağlanma

SDKTest.exe açıldığında **otomatik olarak ağdaki Huidu cihazlarını tarar** ve sol paneldeki listede gösterir.

**Sol panelde** cihazlar şu formatta görünür:
```
A4L-25-XXXXXX  <---> 192.168.1.22
```

- 🟢 **Yeşil zeminli satır** = cihaz aktif ve ulaşılabilir, **bağlanabilirsiniz**
- ⚪ Renksiz satır = cihaz görüldü ama yanıt vermiyor

**Bağlanma:**

1. Yeşil zeminli cihaz satırının üzerine **çift tıklayın** (iki kez hızlı tıklama)
2. Alt orta paneldeki log bölmesinde bağlantı izleri görünür:
   ```
   2026/05/17 17:27:16.305   (send-kSDKServiceAsk)
   2026/05/17 17:27:16.309   (read-kSDKServiceAnswer)
   2026/05/17 17:27:16.310   (send-kSDKCmdAsk)
   2026/05/17 17:27:16.326   (read-kSDKCmdAnswer)
   connect A4L-25-XXXXXX
   ```
3. Sol alt köşedeki **IP** (örn. `A4L-25-XXXXX`), **Port** (varsayılan `10001`), **Proto** (`SDK2.0`), **Net** (`TCP`) alanları otomatik dolar
4. Aynı köşedeki **"断开" (Bağlantıyı kes)** butonu aktif olur — bu, bağlantınızın canlı olduğunun göstergesi

> 💡 **Cihaz listede yeşil görünmüyorsa veya hiç çıkmıyorsa:**
> - Sol alttaki **IP** alanına cihaz IP'sini elle yazın, **Port** `10001`, **Proto** `SDK2.0`, **Net** `TCP` seçili olsun
> - Üst tarafta beliren **"连接" (Bağlan)** butonuna tıklayın
> - Yanıt gelirse log'da `connect ...` satırı görürsünüz

<!-- TODO-RESIM: docs-tr/images/sdktest-connect.png — SDKTest.exe cihaza bağlı durum (yeşil cihaz + connect log) -->

### 4.3 GetHttpApiEnable Komutunu Gönderme

Cihaza bağlandıktan sonra ekranın **üst orta kısmındaki XML editör kutusuna** aşağıdaki XML'i yapıştırın:

```xml
<?xml version='1.0' encoding='utf-8'?>
<sdk guid="##GUID">
    <in method="GetHttpApiEnable"/>
</sdk>
```

Sağ tarafta listeden de **GetDeviceInfo / GetHttpApiEnable** gibi hazır methodları çift tıklayarak XML'i otomatik kutuya getirebilirsiniz.

Sağ alttaki **"发送" (Gönder)** butonuna tıklayın. Cevap, ekranın **alt orta XML kutusunda** belirir.

### 4.4 Cevabı Yorumlama — Üç Olası Senaryo

Cihazın döndüğü cevaba göre üç farklı durum olur:

#### ✅ Senaryo A — HTTP API zaten açık (en iyi durum)

```xml
<?xml version="1.0" encoding="utf-8"?>
<sdk guid="19aa000a54d79ce835655d855f109a97">
    <out result="kSuccess" method="GetHttpApiEnable">
        <func enable="true"/>
    </out>
</sdk>
```

`result="kSuccess"` **ve** `enable="true"` → her şey hazır. SDKTest'i kapatabilir, **Bölüm 5'e geçebilirsiniz**.

#### 🟡 Senaryo B — Method çalışıyor ama HTTP API kapalı

```xml
<sdk guid="..."><out result="kSuccess" method="GetHttpApiEnable">
    <func enable="false"/>
</out></sdk>
```

`result="kSuccess"` fakat `enable="false"` → cihaz HTTP API'yi destekliyor, sadece kapalı. **Bölüm 4.6**'ya geçip `SetHttpApiEnable` ile açın.

#### ❌ Senaryo C — `kUnsupportMethod` (firmware çok eski)

```xml
<?xml version="1.0" encoding="UTF-8"?><sdk guid="2146899e-4d69-44e2-bff9-c65b0433653e"><out method="GetHttpApiEnable" result="kUnsupportMethod"/></sdk>
```

`result="kUnsupportMethod"` → **firmware sürümünüz çok eski.** Cihaz HTTP API methodlarını tanımıyor. Çözüm: firmware'i en son sürüme yükseltmek. **Bölüm 4.5**'e geçin.

<!-- TODO-RESIM: docs-tr/images/sdktest-kunsupportmethod.png — kUnsupportMethod cevabının XML kutusundaki görünümü -->

### 4.5 Firmware Güncellemesi (Senaryo C — `kUnsupportMethod` aldıysanız)

Firmware güncellemesi **HDPlayer** üzerinden yapılır (Huidu'nun resmi ücretsiz yazılımı). HDPlayer kurulu değilse Huidu resmi sitesinden veya bayinizden temin edebilirsiniz.

> ℹ️ Aşağıdaki adımlar **HDPlayer Türkçe arayüzü** içindir. İngilizce/Çince arayüz farklı dil etiketleri kullanır ama menü konumları aynıdır.

#### Adım 1: HDPlayer'ı Açın, Cihazı Seçin

HDPlayer açılınca otomatik olarak ağdaki Huidu cihazlarını listeler. Güncelleyeceğiniz cihazın üzerine tıklayın.

#### Adım 2: Firmware Yükseltme Menüsüne Girin

Üst menü çubuğundan:

**`Kontrol (C)`** → **`Firmware Yükseltme`**

> 🔑 **Şifre sorulacak: `168`** (Türkçe arayüzde de şifre `168` olarak kalır)
> Şifreyi yazıp Tamam'a basın.

<!-- TODO-RESIM: docs-tr/images/hdplayer-kontrol-menu.png — HDPlayer Kontrol menusu, Firmware Yukseltme satiri isaretli -->

#### Adım 3: Firmware Yükseltme Penceresi Açılır

Açılan **"Firmware Yükseltme"** penceresinin yapısı:

| Bölüm | İçerik |
|---|---|
| **yükseltme dosyası** | Üst kısımda boş bir metin kutusu — buraya dosya yolunu yapıştıracaksınız |
| **Select** butonu | Dosyayı manuel seçmek için |
| **Manage** butonu | İndirilen dosyaları yöneten pencereyi açar (bizim kullanacağımız) |
| **dosya bilgileri** | Yapıştırılan dosyanın türü, sürümü ve desteklediği cihaz modelleri burada görünür |
| **cihaz listesi** | Aşağıda — güncellenecek cihazlar tablo halinde (`aygıt adı`, `cihaz kimliği`, `Ana sürüm numarası`, `FPGA sürüm numarası`, `OTAVersion`, `yükseltme Bilgiler`) |
| **Listeyi yenile** | Cihaz listesini tazeler |
| **Update** butonu | Sağ altta — yükseltmeyi başlatır |

<!-- TODO-RESIM: docs-tr/images/hdplayer-firmware-yukseltme.png — Firmware Yukseltme ana penceresi -->

#### Adım 4: "Manage" Butonuna Tıklayın

Sağ üstteki **`Manage`** butonuna tıklayın → **"Download management"** penceresi açılır.

Bu pencerede iki sekme vardır:

- **`Firmware download`** — ana firmware paketleri (örn. `V2.8.5.10`)
- **`FPGA download`** — Box + Magic player paketleri (örn. `Box_V7_11_18_0;Magic_V2.12.8.0`)

Tabloda her satırda `firmwareVertion`, `describeVertion` (Regular), `statu`, **`operation`** sütunları görünür.

`operation` sütununda iki buton vardır:

| Buton | İşlevi |
|---|---|
| **`Downloaded, click Copy path`** | Dosya **zaten indirilmişse** → bu butona tıklayınca dosya yolu Windows panosuna kopyalanır |
| **`Tekrar yükle`** | Dosyayı **yeniden indir** (eski/bozuk indirme varsa) |

<!-- TODO-RESIM: docs-tr/images/hdplayer-download-management.png — Download management penceresi, Firmware download + FPGA download sekmeleri, Operation sütunundaki iki buton -->

#### Adım 5: Dosya Yolunu Kopyalayıp Yapıştırın ve Update'leyin

1. **`Firmware download`** sekmesinde ilk satırın `operation` sütunundaki **`Downloaded, click Copy path`** butonuna tıklayın → dosya yolu panoya kopyalanır
2. Download management penceresini kapatın veya arka plana alın
3. **Firmware Yükseltme** penceresine geri dönün
4. **`yükseltme dosyası`** alanına yapıştırın (`Ctrl + V`)
5. **`dosya bilgileri`** bölümünde dosya bilgileri otomatik dolar:
   - **Dosya Türü:** `FPGA|BoxPlayer|MagicPlayer`
   - **Sürüm numarası Dosya:** örn. `7.11.18.0|2.12.8.0`
   - **Support Device Type:** uzun model listesi (`A3, C15, C35, A4, A5, A6, D15, D35, B6, C16, C36, D16, D36, C16L, C08L, A7, A8, A3L, A4L, A5L, A6L, B6L, H4K, ...`) — buradaki listede **kendi model adınızın olduğunu** doğrulayın
6. **`cihaz listesi`**nde güncellenecek cihazın **checkbox'ı işaretli** olsun
7. Sağ alttaki **`Update`** butonuna tıklayın
8. **`yükseltme Bilgiler`** sütununda yüzde ve durum güncellenir — yeşil dolgu **%100** ve **"Arama tamamlandı"** görene kadar bekleyin

<!-- TODO-RESIM: docs-tr/images/hdplayer-update-progress.png — Update sirasinda %100 yesil bar + Arama tamamlandi -->

#### Adım 6: İkinci Paketi de Yükleyin

Genelde iki paket vardır ve **ikisini de güncellemek gerekir**:

| Paket | Açıklama | Örnek Sürüm Adı |
|---|---|---|
| **Firmware** | Ana firmware paketi | `V2.8.5.10` gibi |
| **Box + Magic** (FPGA tarafında listelenir) | Box player + Magic player paketi | `Box_V7_11_18_0;Magic_V2.12.8.0` gibi |

İlk paket yüklendikten sonra:

1. Tekrar **`Manage`** → Download management
2. Bu sefer diğer satırın (veya `FPGA download` sekmesinin) **`Downloaded, click Copy path`** butonuna tıklayın
3. Aynı 5. adımı tekrarlayın (yapıştır → Update)

#### Adım 7: Cihazı Yeniden Başlatın ve Tekrar Test Edin

Güncelleme bittikten sonra cihaz büyük ihtimalle **otomatik restart** olur. Restart sonrası:

1. SDKTest.exe'yi tekrar açın, cihaza bağlanın (Bölüm 4.2)
2. Aynı `GetHttpApiEnable` XML'ini gönderin (Bölüm 4.3)
3. Artık `result="kSuccess"` cevabı almalısınız → 4.4'teki Senaryo A veya B'ye düşersiniz, oradan devam edin

> 🚧 **Eğer hâlâ `kUnsupportMethod` alıyorsanız:** Cihazınız bu HTTP API'yi destekleyen donanım sürümü değildir. Bayinizle iletişime geçin ve **engineering card** (`D` harfli model — Bölüm 1.1) olduğunuzu doğrulayın. Eski donanımlarda yalnızca TCP/XML SDK çalışır, HTTP API mevcut değildir.

### 4.6 HTTP API'yi Etkinleştirme (Senaryo B için — `enable="false"`)

`result="kSuccess"` aldınız ama `enable="false"` döndüyse, açmak için şu komutu gönderin (SDKTest.exe içinde, üst XML kutusuna yapıştırıp "发送" / Gönder):

```xml
<?xml version='1.0' encoding='utf-8'?>
<sdk guid="##GUID">
    <in method="SetHttpApiEnable">
        <func enable="true"/>
    </in>
</sdk>
```

Başarı cevabı:

```xml
<?xml version="1.0" encoding="utf-8"?>
<sdk guid="7b1b1e7dba5363fc651dc1dc72f949d5">
    <out method="SetHttpApiEnable" result="kSuccess"/>
</sdk>
```

Doğrulamak için **4.3**'teki `GetHttpApiEnable` komutunu tekrar gönderin — bu sefer `enable="true"` dönmelidir.

### 4.7 Yan Etki Uyarısı — Önemli!

> [!WARNING]
> ### 🚨 HTTP SDK Etkinleştirmenin Yan Etkisi
>
> Resmi dokümandan: *"Enabling the HTTP SDK will take over certain standard functions to ensure full HTTP control. After enabling it, some settings in other software (e.g., HDPlayer) may not take effect, such as scheduled power on/off."*
>
> **Türkçesi:** HTTP SDK'yı etkinleştirmek, tam HTTP kontrolünü sağlamak için **bazı standart işlevleri devralır.** Bu işlemden sonra **HDPlayer gibi diğer yazılımlardaki bazı ayarlar** (ör. zamanlı aç/kapa) **artık etki etmeyebilir.**
>
> Yani: bu cihazı bundan sonra **sadece SDK üzerinden** yöneteceksiniz. HDPlayer + SDK karışık kullanımı yapacaksanız öncesinde test edin — özellikle parlaklık zamanlaması ve aç/kapa programlarını.

---

## 5. Apipost Kurulumu ve Koleksiyon İçe Aktarma

Apipost, Çinli ekibin Postman muadili olarak geliştirdiği bir REST API test aracıdır. Huidu, **hazır bir API koleksiyonu** (Apipost formatında) sağlamıştır — içinde tüm endpoint'ler, imza scripti ve örnek istekler bulunur.

### 5.1 Apipost'u İndir

Resmi indirme: **https://www.apipost.cn/**

Windows için `.exe`, macOS için `.dmg`. Ücretsiz sürüm günlük kullanım için yeterlidir.

> 💡 **Apipost yerine Postman kullanmak istiyorsanız** Bölüm 9'a geçin — Huidu Postman koleksiyonu da sağlamıştır.

### 5.2 Hazır Koleksiyonu İçe Aktarma

Resmi SDK içinde `doc/HD_HttpApi1.0_Apipost_Collection.json` dosyası vardır. Bu dosyayı Apipost'a yükleyin:

1. Apipost'u açın
2. Sol üst köşeden **Import / 导入** butonuna tıklayın
3. Dosya seçimine `HD_HttpApi1.0_Apipost_Collection.json`'ı verin

![Apipost koleksiyon import — 1](images/import1.png)

![Apipost koleksiyon import — 2](images/import2.png)

İçe aktarma tamamlanınca sol panelde Huidu'nun tüm endpoint kategorileri görünür:

- Universal Device Interface (cihaz bilgisi, restart, vb.)
- Program Interface (program/sayfa yükleme, silme)
- File Interface (dosya yükleme, indirme)
- ve diğerleri

> **Yerinden almak:** [`master` branch'inde `doc/HD_HttpApi1.0_Apipost_Collection.json`](https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror/blob/master/doc/HD_HttpApi1.0_Apipost_Collection.json)

---

## 6. Environment Variable Kurma — `sdkKey`, `sdkSecret`, IP

Apipost'un environment (ortam değişkeni) özelliğini kullanarak `sdkKey` ve `sdkSecret`'ı tek bir yerde tutarsınız — böylece her istekte tek tek girmek zorunda kalmazsınız.

### 6.1 Yeni Environment Oluşturma

![Apipost environment ayarı](images/Apipost1.png)

Sağ üstte **Environment / 环境** düğmesine tıklayın → **New Environment** seçin → ismini "Huidu - Production" gibi koyun.

### 6.2 Server IP, Port ve Anahtarları Yazma

![Apipost server IP, port ve anahtar konfigürasyonu](images/Apipost2.png)

Aşağıdaki değişkenleri oluşturun:

| Değişken adı | Örnek değer | Açıklama |
|---|---|---|
| `serverIp`   | `192.168.1.50` | Cihazın LAN IP'si veya cloud için `sdk.huidu.cn` |
| `serverPort` | `30080`        | Lokal cihazlar için 30080; cloud için 443 |
| `sdkKey`     | `a7fa6795aaa891e2` | Huidu'dan aldığınız geliştirici kimliği |
| `sdkSecret`  | `***`           | Huidu'dan aldığınız gizli anahtar — kimseyle paylaşmayın |

> 🔒 **Güvenlik:** Apipost environment'ı `.apipost` klasöründe yerel olarak saklanır. **Bu dosyayı bir başkasıyla paylaşmayın, git'e commit etmeyin.**

---

## 7. İmza Üretimi (Pre-Request Script)

Her API çağrısının başlığında **otomatik HMACMD5 imzası** olması gerekir. Apipost'un "Pre-Action / Pre-Request Script" özelliği bu hesaplamayı her istek öncesi otomatik yapar.

### 7.1 Pre-Action Sekmesini Açın

![Apipost Pre-Action konfigürasyonu](images/Apipost3.png)

Koleksiyonun "Pre-Action" sekmesine girin ve aşağıdaki scripti yapıştırın (zaten hazır koleksiyonda var, sadece kontrol edin):

```javascript
pm.request.headers.upsert({
    key: "requestId",
    value: pm.variables.get("requestId")
});

if (pm.request.headers.has("sdkKey")) {
    pm.request.headers.upsert({ key: "sdkKey", value: pm.environment.get("sdkKey") });

    var dateData = new Date();
    pm.request.headers.upsert({ key: "date", value: dateData.toUTCString() });

    var signText = pm.environment.get("sdkKey") + dateData.toUTCString();
    if (pm.request.body != undefined && pm.request.body.raw != undefined) {
        signText = pm.request.body.raw + signText;
    }
    var sign = CryptoJS.HmacMD5(signText, pm.environment.get("sdkSecret")).toString();

    pm.request.headers.upsert({ key: "sign", value: sign });

} else if (pm.request.url.query.has("sdkKey")) {
    pm.request.url.query.upsert({ key: "sdkKey", value: pm.environment.get("sdkKey") });

    var dateData = new Date();
    pm.request.url.query.upsert({ key: "date", value: dateData.toUTCString() });

    var signText = pm.environment.get("sdkKey") + dateData.toUTCString();
    if (pm.request.body != undefined && pm.request.body.raw != undefined) {
        signText = pm.request.body.raw + signText;
    }
    var sign = CryptoJS.HmacMD5(signText, pm.environment.get("sdkSecret")).toString();

    pm.request.url.query.upsert({ key: "sign", value: sign });
}
```

### 7.2 Script Ne Yapıyor?

- Her istekten **hemen önce** çalışır
- Geçerli zamanı UTC formatında `date` başlığına yazar
- Environment'tan `sdkKey` ve `sdkSecret`'ı alır
- `body + sdkKey + date` metnini `sdkSecret` ile **HMACMD5** ile imzalar
- İmzayı `sign` başlığına yazar
- Query string'de `sdkKey` olan dosya endpoint'leri için aynı işlemi URL parametrelerinde yapar (Rule 2)

Sayesinde siz hiçbir başlığı manuel yazmazsınız — script her isteği otomatik imzalar.

---

## 8. İlk Başarılı API Çağrısı

Şimdi gerçek bir API çağrısı yapacağız. En basit, yan etkisi olmayan endpoint: **cihaz bilgisi al**.

### 8.1 Koleksiyondan İsteği Seçin

Sol panelden: **Universal Device Interface → Retrieve Device Info** (`GET /api/getDeviceInfo` veya benzeri).

### 8.2 Environment'ın Seçili Olduğundan Emin Olun

Sağ üstte oluşturduğunuz environment ("Huidu - Production") seçili olmalı.

### 8.3 Send Butonuna Tıklayın

Beklenen sonuç (örnek):

```json
{
  "code": 0,
  "msg": "ok",
  "data": {
    "deviceName": "LED-Tabela-1",
    "model": "C16L-D00-A000F",
    "firmware": "v3.5.2",
    "uptime": "5d 12h",
    "...": "..."
  }
}
```

🎉 `code: 0` ve `msg: "ok"` görüyorsanız **SDK çalışıyor demektir.**

### 8.4 Yaygın Hatalar

| Sonuç | Sebep | Çözüm |
|---|---|---|
| `code: 401` veya **timeout** | Cihaza ağdan ulaşılamıyor | Bölüm 3'e dön (ping/port test) |
| `code: 403` "invalid sign" | İmza hatalı | `sdkSecret`'ı kontrol et, environment'a doğru yazdın mı? |
| `code: 403` "date out of range" | Bilgisayar saati cihaz saatinden çok farklı | Saati NTP ile senkronize et (`w32tm /resync` Windows'ta) |
| `404 /api/getDeviceInfo` | Eski firmware, endpoint adı farklı | Firmware'i güncelle veya alternatif endpoint dene |
| HTML cevap geliyor (JSON değil) | İstek HTTP API'ya değil login sayfasına gitti | Endpoint URL'sini kontrol et (`/api/...` ile başlamalı) |

---

## 9. Postman Kullanmak İsteyenler İçin Notlar

Apipost yerine Postman tercih ediyorsanız:

1. **Koleksiyon dosyası:** Resmi SDK içinde `doc/HD_HttpApi1.0_Postman_Collection.json` var, onu kullanın
2. **Pre-Request Script:** Apipost'taki `pm.environment.get(...)` ve `pm.request.headers.upsert(...)` API'ları Postman ile **birebir aynıdır** — değişiklik yapmadan çalışır
3. **CryptoJS modülü:** Postman'in built-in `pm.cryptojs` veya global `CryptoJS` ile gelir (Apipost'la aynı)
4. **Environment kurulumu:** Tamamen aynı (`sdkKey`, `sdkSecret`, `serverIp`, `serverPort`)
5. **Tek farkı:** "Pre-Action" yerine **"Pre-request Script"** sekmesi adıyla geçer

> Eğer Postman kullanırsanız Apipost'a ihtiyacınız yok — script ve koleksiyon birebir uyumlu.

---

## 10. PowerShell ile Hızlı Manuel Test

Hiç GUI aracı kurmadan sadece PowerShell ile cihazı test etmek istiyorsanız:

```powershell
# config (kendi degerlerinizi koyun)
$serverIp   = '192.168.1.50'
$serverPort = 30080
$sdkKey     = 'a7fa6795aaa891e2'
$sdkSecret  = $env:HUIDU_SDK_SECRET   # env'den al, koda yazma

# Endpoint
$path = '/api/getDeviceInfo'
$url  = "http://${serverIp}:${serverPort}$path"

# Imza (body bos - GET istek)
$now      = (Get-Date).ToUniversalTime().ToString('R')   # "Wed, 09 Aug 2023 07:27:44 GMT"
$signText = '' + $sdkKey + $now                          # body bos
$hmac     = New-Object System.Security.Cryptography.HMACMD5
$hmac.Key = [System.Text.Encoding]::UTF8.GetBytes($sdkSecret)
$sign     = ([BitConverter]::ToString(
              $hmac.ComputeHash([System.Text.Encoding]::UTF8.GetBytes($signText))
            ) -replace '-', '').ToLowerInvariant()

# Istek
$headers = @{
    'requestId'    = [Guid]::NewGuid().ToString()
    'sdkKey'       = $sdkKey
    'date'         = $now
    'sign'         = $sign
    'Content-Type' = 'application/json'
}

try {
    $r = Invoke-RestMethod -Uri $url -Method GET -Headers $headers -TimeoutSec 10
    "Basari: $($r | ConvertTo-Json -Depth 5)"
} catch {
    "Hata: $($_.Exception.Message)"
}
```

Bu betiği `huidu-ping.ps1` olarak kaydedip çalıştırırsanız, doğru anahtarlarla cihazdan cevap almalısınız.

> 💡 PowerShell ile çalışırken `sdkSecret`'i env değişkeninden okuyun:
> ```powershell
> [Environment]::SetEnvironmentVariable('HUIDU_SDK_SECRET','gercek-secret','User')
> ```

---

## 11. Sıkıntı Çözme (Troubleshooting)

### Cihaz pinge yanıt veriyor ama port 30080 kapalı

→ HTTP API cihazda etkin değil. **Bölüm 4**'e dön ve `SetHttpApiEnable` ile aç. Android serisi cihazlarda firmware güncellemesini unutma.

### `/login/` sayfası açılıyor ama API çağrıları 404 veriyor

→ Cihaz daha eski bir firmware'da, endpoint adları farklı olabilir. Firmware güncelle. Veya farklı bir endpoint dene (örn. `/api/v1/getDeviceInfo`).

### Apipost koleksiyonu boş içe aktarılıyor

→ JSON dosyası bozuk olabilir. Resmi kaynaktan tekrar indir:
- [GitHub mirror](https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror/blob/master/doc/HD_HttpApi1.0_Apipost_Collection.json)
- [Resmi Gitee](https://gitee.com/szhuidu/cn.huidu.device.sdk/blob/master/doc/HD_HttpApi1.0_Apipost_Collection.json)

### Pre-Action script çalışmıyor (`CryptoJS undefined`)

→ Apipost'un eski sürümü olabilir. Apipost'u güncelleyin (4.x ve üstü `CryptoJS` global olarak sağlar).

### Her istek `code: 403 invalid sign` dönüyor

Sırasıyla kontrol edin:

1. `sdkSecret` environment'ta tamamen doğru mu yazıldı? (kopyalarken trim hatası yapmış olabilirsin — başında/sonunda boşluk var mı?)
2. `sdkKey` ve `sdkSecret` aynı çiftten mi geliyor? (yanlış eşleştirme)
3. Pre-Action script doğru kopyalandı mı? (özellikle `body + sdkKey + date` sırası kritik)
4. Bilgisayar saatiniz cihazınkinden 5 dakikadan fazla mı farklı?

### Cihaz LAN'da ama internet yok — cloud API çalışmıyor

→ Cloud API (`sdk.huidu.cn`) ayrı bir yol; bu rehber lokal API'yi anlatıyor. Lokal API tamamen offline çalışır, cihaz internete bağlanmasa bile sorun değil.

### Cihaz GSM modem üzerinden uzaktan yönetiliyor

→ Bu durumda doğrudan LAN üzerinden cihaza ulaşamazsınız. Huidu'nun "Server Mode" (sunucu modu) yapısı gerekir — cihaz dışarıdaki bir sunucuya bağlanır, siz sunucu üzerinden cihaza komut iletirsiniz. Ayrı bir konu, ileride başka bir rehberde ele alacağız.

---

## 12. Hızlı Kontrol Listesi (Checklist)

Test ortamı kurulum sürecini bu listeye göre tamamlayabilirsiniz:

- [ ] Cihaz model ID'si `D` harfi içeriyor (engineering card)
- [ ] Firmware en güncel (özellikle Android serisi)
- [ ] Cihaz IP adresi biliniyor (`192.168.x.x`)
- [ ] Ping başarılı (`Test-Connection`)
- [ ] Port 30080 açık (`Test-NetConnection`)
- [ ] HTTP API etkin (`/login/` sayfası açılıyor)
- [ ] `sdkKey` ve `sdkSecret` cihaza yazıldı (Rehber 01, Bölüm 5)
- [ ] Apipost (veya Postman) kuruldu
- [ ] Hazır koleksiyon içe aktarıldı (`HD_HttpApi1.0_*_Collection.json`)
- [ ] Environment variables yazıldı (`sdkKey`, `sdkSecret`, `serverIp`, `serverPort`)
- [ ] Pre-Action script var, `CryptoJS` çalışıyor
- [ ] İlk API çağrısı (örn. `getDeviceInfo`) `code: 0` dönüyor 🎉

Tüm maddeler ✅ ise SDK üretime hazır.

---

## 🔙 Sonraki Adımlar

- **Anahtar henüz alınmadıysa** → [01-sdk-kayit-ve-baslangic.md](01-sdk-kayit-ve-baslangic.md)
- **Programlar / sayfalar göndermeyi öğrenmek** → (gelecek rehber: 03-program-gonderme.md)
- **Cihaz parlaklık / zamanlama** → (gelecek rehber: 04-cihaz-yonetimi.md)
- **Server Mode / uzaktan yönetim** → (gelecek rehber: 05-server-mode.md)

📂 **Orijinal SDK kaynak kodu:** [`master` branch](https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror/blob/master/README.en.md)
🔗 **Resmi Gitee deposu:** https://gitee.com/szhuidu/cn.huidu.device.sdk

---

📝 **Belge geçmişi**
- 2026-05-17 — İlk sürüm. Resmi Huidu README.en.md Bölüm 2.2, 2.5 ve 4 referans alınarak hazırlandı. Görseller `master/doc/images/` klasöründen kopyalandı.

💌 **Soru / katkı:** turkmen87ai@gmail.com veya [GitHub Issues](https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror/issues)
