# Huidu SDK — Türkçe Notlar ve Örnek Kodlar

> [!CAUTION]
> ## 🚀 SDK'yı İlk Kez mi Kullanıyorsunuz? Adım Adım Türkçe Rehberler
>
> **Adım 1 — Anahtar alma:** [docs-tr/01-sdk-kayit-ve-baslangic.md](docs-tr/01-sdk-kayit-ve-baslangic.md)
> SDK ile **tek bir API çağrısı bile yapmadan önce**, Huidu'dan **`sdkKey` ve `sdkSecret`** almalısınız. Bu iki bilgi olmadan **cihaza hiçbir komut iletemezsiniz**. Rehber içeriği: `sdkKey/sdkSecret` nedir; Huidu ile iletişim (WhatsApp/WeChat `hdwell.com`, Türkiye'deki entegratörler, e-posta); kayıt formundaki Çince alanların Türkçesi; hazır başvuru şablonu; cihaza anahtar yazma (⚠️ sadece bir kere); HMACMD5 imza üretimi; güvenlik kuralları; yaygın hatalar.
>
> **Adım 2 — Test ve bağlantı:** [docs-tr/02-sdk-test-ve-cihaz-baglantisi.md](docs-tr/02-sdk-test-ve-cihaz-baglantisi.md)
> Anahtarları aldıktan sonra **ilk başarılı API çağrısını** yapana kadar olan süreç. Rehber içeriği: cihaz model ID kontrolü (engineering card / `D` harfi); firmware güncelleme; cihazın IP'sini bulma (HDPlayer, router DHCP, ARP); ağ ve port testi (`Test-NetConnection 30080`); HTTP API'yi cihazda etkinleştirme (ARM/Linux serisi için `SetHttpApiEnable` XML komutu); Apipost kurulumu; hazır API koleksiyonunu içe aktarma; environment variables; Pre-Request Script (otomatik imza); ilk `getDeviceInfo` çağrısı; Postman alternatifi; PowerShell manuel test; troubleshooting; 12 maddelik checklist.

> [!IMPORTANT]
> ## 🔍 Önce Bunu Okuyun: Orijinal SDK Kodu Nerede?
>
> Şu an `main` branch'indesiniz ve bu branch **sadece Türkçe dokümanları** içerir (BENIOKU.md, README.md). Orijinal Huidu SDK'sının kaynak dosyaları burada **yoktur**.
>
> **Orijinal SDK kodu — Java, Go, C, Python kaynak kodları, demo projeler, HTTP API protokol dokümanları, örnek konfigürasyonlar — bu repo'nun `master` branch'inde durmaktadır.**
>
> ### SDK Koduna Nasıl Ulaşırım?
>
> **🅐 GitHub üzerinden (web tarayıcı):**
> [`master` branch'ini aç →](https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror/tree/master)
>
> **🅑 Komut satırından (yerel klon):**
> ```bash
> # Sadece SDK kodunu (master branch'ini) klonla:
> git clone -b master https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror.git
>
> # VEYA: doğrudan resmi Gitee deposundan klonla (üretim sistemleri için önerilen):
> git clone https://gitee.com/szhuidu/cn.huidu.device.sdk.git
> ```
>
> **🅒 Hem main hem master birlikte:**
> ```bash
> git clone https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror.git
> cd huidu-sdk-gitee-mirror
> git checkout master   # SDK koduna geç
> git checkout main     # Türkçe notlara geri dön
> ```
>
> ### Hangi Branch'te Ne Var?
>
> | Branch | İçerik | Nasıl Bakarsınız | Durum |
> |---|---|---|---|
> | **`master`** | 🇨🇳 Orijinal SDK kodu (Huidu'nun resmi Gitee deposunun **birebir kopyası**): Java SDK, Go SDK, C SDK, Python SDK, demo projeler, protocol.html, README.md (Çince), README.en.md (İngilizce), tüm dokümanlar | [GitHub'da görüntüle](https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror/tree/master) | Her gün otomatik olarak Gitee'den sync'lenir |
> | **`main`** *(varsayılan, bu sayfa)* | 🇹🇷 Türkçe BENIOKU.md, Türkçe README.md, ileride eklenecek Türkçe örnek kodlar ve çevirmeler | [GitHub'da görüntüle](https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror) | Manuel güncellenir, otomasyon dokunmaz |
>
> **Neden iki branch?** Çünkü SDK kodu Huidu'nun, ona dokunmuyoruz (master = saf kopya). Türkçe ek içerikler ise ayrı bir branch'te tutuluyor ki SDK koduyla karıştırılmasın ve günlük sync'te silinmesin.

> **Bu repository, Shenzhen Huidu Technology Co., Ltd. (深圳市灰度科技有限公司) firmasının resmi Gitee deposunun yalnızca okuma amaçlı bir aynasıdır (read-only mirror).**
>
> **Resmi / orijinal kaynak:** **https://gitee.com/szhuidu/cn.huidu.device.sdk**
>
> SDK koduna ait tüm fikri mülkiyet hakları sahibine, yani **Shenzhen Huidu Technology Co., Ltd.** firmasına aittir. Bu repository telif hakkı talebinde bulunmaz, sahiplik iddia etmez ve değişiklik yapılmamış bir kopya barındırır.

---

## 1. Bu Repo Niye Var?

Türkiye'de LED ekran kontrol kartlarına çok sayıda yazılım entegrasyonu yapılıyor. Ancak Huidu firmasının resmi dokümantasyonu ve örnek kodları **ağırlıklı olarak Çince**:

- API protokol açıklamaları (HTTP API ve TCP) Çince yazılmış
- Java / Go / C / Python örnek kodlarda yorum satırları Çince
- Hata mesajları, sabit listeleri, model adları, ekran tipleri çoğunlukla Çince
- Cloud platform (sdk.huidu.cn) yönlendirmeleri ve API açıklamaları Çince

Bu durum, Türkçe konuşan geliştiriciler için kullanım eşiğini ciddi şekilde yükseltiyor. Çince bilmeyen bir geliştiricinin SDK'yı verimli kullanması için ya makine çevirisine güvenmesi ya da deneme yanılma yapması gerekiyor — ikisi de güvenilir değil.

Bu repository, **resmi SDK koduna hiç dokunmadan**, yanına aşağıdaki Türkçe içerikleri eklemek amacıyla oluşturulmuştur:

- Türkçe açıklamalı **örnek kodlar** (C#, Python, Java, Go, C)
- API protokol notlarının Türkçe **çevirmeleri**
- Cihaz modeli ↔ desteklenen özellik **karşılaştırma tabloları** (C16L, A3, A4, H4K, H8 vb.)
- Yaygın **hata kodları sözlüğü** (Türkçe karşılıkları ile)
- **HOWTO / SSS** dokümanları (sık karşılaşılan senaryolar)

> Bu içerikler tamamen kişisel/öğrenme amaçlı eklenir. Üretici firmanın resmi tutumunu temsil etmez.

---

## 2. Resmi Kaynak (Asıl Sahibi)

| | |
|---|---|
| **Sahip / Telif hakkı** | Shenzhen Huidu Technology Co., Ltd. (深圳市灰度科技有限公司) |
| **Resmi Gitee profili** | https://gitee.com/szhuidu |
| **Bu SDK'nın resmi deposu** | https://gitee.com/szhuidu/cn.huidu.device.sdk |
| **Resmi Java varyantı** | https://gitee.com/szhuidu/cn.huidu.device.api.sdk.java |
| **Cloud API ana adresi** | https://sdk.huidu.cn |
| **Cihaz lokal HTTP API** | `http://127.0.0.1:30080/api/...` |
| **Üretici resmi web sitesi** | http://www.huidu.cn |

**Lütfen üretim sistemlerinde, ticari projelerde ve resmi destek talepleri için yukarıdaki resmi kaynakları kullanın.** Bu repository resmi bir destek kanalı değildir.

---

## 3. Repository Yapısı (Branch Düzeni)

Bu repository iki ayrı git branch'i kullanır. Birbirine **karışmazlar**.

### 🅐 `master` branch — Orijinal SDK'nın Birebir Kopyası

- İçerik: `https://gitee.com/szhuidu/cn.huidu.device.sdk` deposunun **kelimesi kelimesine aynısı**
- Bir Windows PowerShell otomasyonu her gün saat 09:00'da bu branch'i resmi Gitee deposuna göre **sıfırlar** (`git fetch origin && git reset --hard origin/master && git clean -fd`)
- Bu branch'e **manuel olarak ne eklenirse bir sonraki sync'te silinir**. Kasıtlı olarak böyledir: orijinal kodun bütünlüğünü korumak için
- Klonlamak isteyen geliştiriciler bu branch'i veya doğrudan resmi Gitee deposunu kullanabilir
- **Bu branch'teki tüm dosyalar Huidu'nun fikri mülkiyetidir.** Hiçbir telif değişikliği yapılmamıştır

```powershell
git clone -b master https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror.git
# veya doğrudan resmi kaynaktan:
git clone https://gitee.com/szhuidu/cn.huidu.device.sdk.git
```

### 🅑 `main` branch — Türkçe Notlar ve Örnek Kodlar (varsayılan)

- İçerik: Bu BENIOKU.md, README.md, Türkçe örnek kodlar, çevirmeli dokümanlar
- Bu branch'e **otomasyon dokunmaz**. Eklenen her dosya kalıcıdır
- GitHub'da varsayılan (default) branch olarak ayarlanmıştır — repository ana sayfasında ilk gösterilen branch
- SDK koduyla **karıştırılmaz** — sadece Türkçe ek içerik

```powershell
git clone https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror.git
# main branch otomatik olarak gelir (varsayılan)
```

---

## 4. Kullanım Amacı ve "Fair Use / Eğitim İstisnası" Beyanı

Bu repository:

1. **Eğitim ve öğrenme** amacıyla oluşturulmuştur (öğrenci, hobici, profesyonel — fark etmez)
2. **Kâr amacı gütmez**. Reklam, sponsor, ücretli içerik yoktur
3. **Reklam, satış veya ürün promosyonu** içermez
4. **Orijinal kaynağa açık ve görünür şekilde atıf yapar** (yukarıda detaylı verilmiştir)
5. **Master branch kelimesi kelimesine** resmi kaynaktan senkronize edilir — kod değiştirilmemiş, manipüle edilmemiş, yeniden paketlenmemiştir
6. **Türkçe ek içerikler** ayrı bir branch'te tutulur, SDK kodunun kendisiyle karıştırılmaz
7. **Üretici firmanın resmi yapısının bir parçası değildir** ve bu izlenim verilmemiştir

### Hukuki Çerçeve

Aşağıdaki istisnalar kapsamında değerlendirilmesi gerekir kanaatindeyiz:

- **🇨🇳 Çin Halk Cumhuriyeti — 《中华人民共和国著作权法》(Telif Hakkı Yasası), Madde 24 (eski Madde 22):**
  Bilimsel araştırma, kişisel öğrenme ve eğitim amaçlı, kâr getirmeyen, sınırlı kapsamda kullanım istisnası ("个人学习、研究或者欣赏" — kişisel öğrenme, araştırma veya inceleme)
- **🇹🇷 Türkiye Cumhuriyeti — 5846 Sayılı Fikir ve Sanat Eserleri Kanunu, Madde 38:**
  Şahsi kullanım istisnası — gerçek kişilerin kâr amacı gütmeden, kişisel kullanım amacıyla çoğaltma hakkı
- **🌐 Berne Sözleşmesi, Madde 10(2):**
  Eğitim amaçlı alıntı/kullanım hakkı (her iki ülke de imzacıdır)
- **🇺🇸 ABD DMCA / 17 U.S.C. § 107 — Fair Use:**
  GitHub ABD merkezli olduğu için: kullanım amacı (eğitim), eserin doğası (teknik dokümantasyon), kullanılan miktar (orijinal koda dokunulmamış, sadece atıflı kopya), pazara etkisi (resmi depoyla rekabet etmiyor, ona yönlendiriyor) → fair use lehine değerlendirme

### İtiraz / Kaldırma Talebi (Takedown)

Eğer **Shenzhen Huidu Technology Co., Ltd.** veya hak sahibi/temsilcisi bu mirror'a itiraz ederse:

1. **Repository derhal kaldırılır.** İtiraz aldıktan sonra 48 saat içinde `gh repo delete` ile silinir
2. **Bu BENIOKU.md ve tüm Türkçe içerikler de silinir** (commit geçmişiyle birlikte yedek kalmaz)
3. **Talep, aşağıdaki kanallardan yapılabilir:**
   - E-posta: **turkmen87ai@gmail.com**
   - GitHub Issue: https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror/issues
   - Resmi DMCA prosedürü: https://github.com/contact/dmca (GitHub'a doğrudan)

Hak sahibinin tutumuna karşı saygı gösterilecektir — bu repo onların izniyle değil, kamu yararı/öğrenme amacıyla açılmıştır; sahibi karşı çıkıyorsa kapanır.

---

## 5. Sorumluluk Reddi (Disclaimer)

- ❌ **Resmi destek değildir.** Bu repository Huidu Technology firmasının resmi bir kanalı değildir, firmayla bağlantısı yoktur, firma adına konuşmaz
- ❌ **Garanti yoktur.** SDK kodu "as-is" (olduğu gibi) sunulmuştur. Üretim/hayati sistemlerde kullanımdan doğan zararlar repo sahibinin sorumluluğu **değildir**
- ❌ **Promosyon değildir.** Hiçbir Huidu ürününün satışını veya pazarlamasını yapmaz
- ✅ **Tavsiye edilen kaynak:** Üretim ortamlarında ve ticari projelerde **resmi Gitee deposunu kullanın:** `https://gitee.com/szhuidu/cn.huidu.device.sdk`
- ✅ **Fork'larsanız:** Lütfen siz de resmi kaynağa açık atıf yapın

---

## 6. Türkçe Örnek Kodlar — Yapılacaklar Listesi

### Başlangıç Rehberleri

- [x] **[01 — SDK Kaydı ve Başlangıç (SDK Key & Secret Alma)](docs-tr/01-sdk-kayit-ve-baslangic.md)** *(resimli, detaylı)*
- [x] **[02 — SDK Testi Açmak ve Cihaza Bağlanmak (Apipost / Postman / PowerShell)](docs-tr/02-sdk-test-ve-cihaz-baglantisi.md)** *(resimli, 12 bölüm)*
- [ ] 03 — Program / sayfa gönderme (text, image, video)
- [ ] 04 — Cihaz yönetimi (parlaklık, zamanlama, restart)
- [ ] 05 — Server Mode / uzaktan yönetim


> Aşağıdaki örnekler zaman içinde bu branch'e eklenecektir. Tamamlananlar `[x]` ile işaretlenir.

### Bağlantı ve Temel İşlemler

- [ ] **C#** — `HttpClient` ile cihaza bağlanma, `GET /api/getDeviceInfo` (cihaz bilgisi okuma)
- [ ] **C#** — HMACMD5 imza hesaplama (sdkKey + body + date + sdkSecret)
- [ ] **Python** — Düşük seviye HTTP istek + imza üretimi
- [ ] **PowerShell** — Tek komutla cihaza ping (CLI senaryosu)

### Java Demo

- [ ] Resmi Java demo'yu Windows'ta derleme adımları (Maven / IntelliJ)
- [ ] `cn.huidu.device.sdk.demo` paketinde adım adım örnek
- [ ] Türkçe yorumlu basit "Hello LED" gönderme demosu

### Cihaz Komutları

- [ ] **Saat senkronizasyonu** — NTP / manuel zaman gönderme
- [ ] **Parlaklık ayarı** — gündüz/gece otomatik schedule
- [ ] **Program/sayfa yükleme** — text, image, video kombinasyonları
- [ ] **Cihaz yeniden başlatma** ve uzaktan teşhis

### Cihaz Modelleri ve Özellikleri

- [ ] C16L (en yaygın, küçük ekranlar)
- [ ] A3 / A4 (orta segment)
- [ ] H4K (4K destekli)
- [ ] H8 (yüksek hassasiyet)
- [ ] Hangi modelin hangi komutu desteklediği matrisi

### Referans Dokümanlar (Türkçe Çeviri)

- [ ] HTTP API endpoint listesi — Türkçe açıklamalar
- [ ] Hata kodları sözlüğü — Çince → Türkçe
- [ ] Protocol.html dokümanının Türkçe özeti
- [ ] TCP/Socket SDK için Türkçe başlangıç rehberi (eski `cn.huidu.sdk` repo'su)

---

## 7. Sıkça Sorulan Sorular (SSS)

### Bu repository'yi klonladım, SDK'yı nasıl kullanırım?

`master` branch'inde SDK kodu, `main` branch'inde Türkçe notlar var. SDK için:

```powershell
git checkout master
# veya doğrudan resmi kaynak (önerilen):
git clone https://gitee.com/szhuidu/cn.huidu.device.sdk.git
```

### Türkçe örnek kodlar nerede?

`main` branch'inde `examples/` klasörü altında olacak (henüz oluşturulmadı, yapılacaklar listesindeler).

### Bir hata kodu için Türkçe açıklama arıyorum

`main` branch'inde `docs/hata-kodlari.md` dosyası eklenecek (yapılacaklar listesinde).

### Resmi destek alabilir miyim?

Buradan **alamazsınız.** Resmi destek için Huidu'nun resmi kanallarını kullanın:

- Web: http://www.huidu.cn
- Gitee Issues: https://gitee.com/szhuidu/cn.huidu.device.sdk/issues

### Repo'yu istediğim gibi kullanabilir miyim?

- **SDK kodu (master branch):** Huidu'nun lisans şartlarına tabidir (resmi depoda açık lisans dosyası bulunmadığı için varsayılan telif hakları uygulanır — kişisel/öğrenme amaçlı kullanım ötesinde Huidu'dan izin almanız gerekir)
- **Türkçe içerikler (main branch):** Aşağıdaki "Lisans Notu" bölümüne bakın

---

## 8. Lisans Notu

| Bölüm | Lisans / Hak sahibi |
|---|---|
| **SDK kodu** (`master` branch — tüm Java/Go/C/Python kaynak kodu, README'ler, protokol dokümanları) | © Shenzhen Huidu Technology Co., Ltd. — Resmi depoda lisans dosyası bulunmadığı için **varsayılan tam telif haklarına** tabidir. Kişisel öğrenme / araştırma dışında kullanım için hak sahibinden izin alınmalıdır |
| **Türkçe içerikler** (`main` branch — bu BENIOKU.md, gelecek örnek kodlar, çevirmeler) | **Creative Commons Atıf 4.0 (CC BY 4.0)** — Yazar: Turkmen87ai (turkmen87ai@gmail.com). Atıf vererek serbestçe kullanılabilir/değiştirilebilir |

> Türkçe örnek kodlardaki SDK'ya yapılan çağrıların kendisi SDK'nın kullanım şartlarına tabidir; örnek kod yapısı CC BY 4.0'dır.

---

## 9. İletişim

- **GitHub:** https://github.com/Turkmen87ai
- **E-posta:** turkmen87ai@gmail.com
- **Bu repo:** https://github.com/Turkmen87ai/huidu-sdk-gitee-mirror

Soru, öneri, hata düzeltme veya Türkçe katkı sunmak isterseniz **Issues** veya **Pull Request** üzerinden ulaşabilirsiniz.

---

## 10. Sürüm Notları / Bu Dosyanın Geçmişi

| Tarih | Değişiklik |
|---|---|
| 2026-05-17 | İlk sürüm — `main` branch'i oluşturuldu, Türkçe BENIOKU yazıldı, GitHub default branch olarak ayarlandı, hukuki çerçeve detaylandırıldı |

> Bu dosya geliştirildikçe revize edilecektir. **Silinmemek üzere** versiyon kontrolünde tutulur; otomasyon (master branch sync) bu dosyaya dokunmaz.

---

*Son not: Huidu'nun teknolojisini geliştirdikleri için kendilerine teşekkür ederim. Bu mirror, ürünlerinin Türkiye'deki kullanım kolaylığını artırmak için açılmıştır; ticari rakipliğe değil, kullanıcı topluluğunun büyümesine yöneliktir.*
