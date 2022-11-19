# BOWLING ARCADE BASED ON EMBEDDED SYSTEM

# KELOMPOK 13
# Nama Anggota Kelompok
	1. Muhammad A.M Hikar Syahrial	119140031
	2. Tri Aji Bagaskara		119140214
	3. Salman Iliyin Gustian	119140053
	4. M. Riski Aziz 		119140160

# Penjelasan Program
	Program dimulai dengan memasukkan library apa saja yang di butuhkan serta mendeklarasikan variabel-variabel yang diperlukan. Setelah semuanya siap lakukan setup pin di void setup(). Buat fungsi yang menjalankan fitur-fitur pada sistem diluar void setup() dan void loop(), seperti fungsi hitung, fungsi ultrasonik, fungsi ldr dan lain-lain. Fungsi-fungsi tersebut di panggil di dalam void loop(). Pada void loop() atur alur kerja program yang dibuat dengan memasukkan fungsi-fungsi yang dibuat dan perintah-perintah lainnya. Upload kode ke arduino dan sistem siap digunakan.

# Arsitektur Sistem
	Gambar dapat dilihat di direktori Arsitektur Sistem/Arsitektur Sistem.png


# Cara Kerja
	1. Tekan tombol Push Button untuk memulai permainan
	2. Selanjutnya arahkan tangan anda ke depan sensor ultrasonik dengan jarak 3-8 cm maka permainan dimulai dan waktu mulai berjalan.
	3. Berikutnya pemain akan memasukkan bola ke dalam lubang, jika bola masuk kedalam lubang maka score bertambah satu (hanya 1 lubang yang memiliki score 1, 2 lubang lainnya bernilai 0)
	4. Permainan akan berakhir ketika melewati batas waktu lima belas detik (score dan waktu terlihat pada layar lcd)

# Fitur
	1. Permainan dapat menghitung skor secara otomatis serta dapat mendeteksi gerakan bola yang masuk ke lubang dengan sensor PIR
	2. Dapat menampilkan durasi waktu dan jumlah skor yang telah terkumpul
	3. Dapat membuka gerbang penghalang bola menggunakan servo secara otomatis ketika permainan dimulai
	4. Dapat menyalakan LED menyinari ketika gelap
	5. Permainan dapat memulai otomatis dengan menekan tombol push button kemudian mendeteksi gerakan pemain dengan sensor ultrasonic


