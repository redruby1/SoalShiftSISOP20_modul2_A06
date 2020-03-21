# SoalShiftSISOP20_modul2_A06

## Soal 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:

**a. Program menerima 4 argumen berupa:**

i. Detik: 0-59 atau * (any value)

ii. Menit: 0-59 atau * (any value)

iii. Jam: 0-23 atau * (any value)

iv. Path file .sh
	
```
int main(int argc,char *argv[]) {
	if(argc == 5) {
		...
		...
	}
}
```
- Program menerima 5 buah inputan, 1 berupa *nama program* dan 4 lainnya berupa *argumen* sesuai ketentuan diatas

**b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai**
```
if(arg[1] > 59 || arg[2] > 59 || arg[3] > 23) {
	printf("Argumen tidak valid\n");
	exit(EXIT_FAILURE);
}
```
- ``` arg[1] ``` menyimpan argumen berupa *detik*
- ``` arg[2] ``` menyimpan argumen berupa *menit*
- ``` arg[3] ``` menyimpan argumen berupa *jam*

**c. Program hanya menerima 1 config cron**
```
./soal1 \* 30 6 /home/anisa/sisop/soal1_bash.sh
```
- Contoh diatas merupakan contoh inputan program ``` soal1 ``` yang hanya dapat menerima satu jenis inputan
- Program diatas akan berjalan setiap detik pada 06.30

**d. Program berjalan di background (daemon)**
```
pid_t pid, sid, anak;
pid = fork();
	
if(pid < 0) {
	exit(EXIT_FAILURE);
}
	  
if(pid > 0) {
	exit(EXIT_SUCCESS);
}

umask(0);
	
sid = setsid();
if(sid < 0) {
	exit(EXIT_FAILURE);
}

if((chdir("/")) < 0) {
	exit(EXIT_FAILURE);
}
	
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

while(1) {
	...
	...
}
```
- Program menggunakan template daemon

**e. Tidak boleh menggunakan fungsi system()**
```
time(&times);
local = localtime(&times);

hour = local->tm_hour;
min = local->tm_min;
sec = local->tm_sec;
			
if((sec == arg[1] || arg[1] == -1) && (min == arg[2] || arg[2] == -1) && (hour == arg[3] || arg[3] == -1)) {
	anak = fork();
}
	    	
if(anak == 0) {
	char *arg[] = {"bash", argv[4], NULL};
	execv("/bin/bash", arg);
}

sleep(1);
```
- Program tidak menggunakan fungsi system()

> Full code [soal1_revisi.c](https://github.com/redruby1/SoalShiftSISOP20_modul2_A06/blob/master/soal1/soal1_revisi.c)

*Menjalankan soal1*
![soal1](https://github.com/redruby1/SoalShiftSISOP20_modul2_A06/blob/master/img/soal1.PNG)

## Soal 2
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program

**a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah  program  C  yang  per  30  detik membuat  sebuah  folder  dengan  nama timestamp [YYYY-mm-dd_HH:ii:ss]**

```
time(&times);
local = localtime(&times);
		
sprintf(name, "%d-%d-%d_%d:%d:%d", local->tm_year+1900, local->tm_mon+1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);

if(anak1 == 0) {
	char *arg[] = {"mkdir", "-p", name, NULL};
	execv("/bin/mkdir", arg);
}
else {
	...
	...
}
sleep(30)
```
- ``` local = localtime(&times); ``` untuk mengambil waktu sekarang
- ``` sprintf(name, "%d-%d-%d_%d:%d:%d", local->tm_year+1900, local->tm_mon+1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec); ``` untuk memasukkan format nama pada variabel ``` name ```
- ``` char *arg[] = {"mkdir", "-p", name, NULL}; execv("/bin/mkdir", arg); ``` membuat folder dengan format nama sesuai ``` name ```
- ``` sleep(30) ``` membuat program berjalan setiap 30 detik

**b. Tiap-tiap  folder  lalu  diisi  dengan  20  gambar  yang  di  download  dari https://picsum.photos/,  dimana  tiap  gambar  di  download  setiap  5  detik.  Tiap gambar berbentuk persegi dengan ukuran  (t%1000)+100  piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYYmm-dd_HH:ii:ss]**
```
if(anak2 == 0) {
	for(i=0; i<20; i++) {
	pid_t unduh;
	unduh = fork();
					
	if(unduh == 0) {
			time(&times);
			local2 = localtime(&times);
			
			t = (unsigned)time(NULL);
			uk = (t%1000)+100;
		
			sprintf(name2, "https://picsum.photos/%un/%un", uk, uk);
			sprintf(name3, "%d-%d-%d_%d:%d:%d", local2->tm_year+1900, local2->tm_mon+1, local2->tm_mday, local2->tm_hour, local2->tm_min, local2->tm_sec);
			sprintf(namafile, "%s/%s.jpg", name, name3);
		
			char *arg[] = {"wget", "-O", namafile, name2, NULL};
			execv("/usr/bin/wget", arg);
		}
		sleep(5);
	}
	...
	...
}
```
- ``` for(i=0; i<20; i++) ``` untuk loop sebanyak 20 kali, agar bisa download 20 gambar
- ``` local2 = localtime(&times); ``` untuk mengambil waktu sekarang
- ``` t = (unsigned)time(NULL); ``` untuk mengambil unix dari timestamp
- ``` uk = (t%1000)+100; ``` untuk menghitung ukuran gambar
- ``` sprintf(name2, "https://picsum.photos/%un/%un", uk, uk); ``` untuk menyimpan format nama
- ``` char *arg[] = {"wget", "-O", namafile, name2, NULL}; execv("/usr/bin/wget", arg); ``` untuk download gambar dari picsum photo

**c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip)**
```
if(anak3 == 0) {
	char zip[30];
	sprintf(zip, "%s.zip", name);
					
	char *arg[] = {"zip", "-rm", zip, name, NULL};
	execv("/usr/bin/zip", arg);
}
```
- ``` sprintf(zip, "%s.zip", name); ``` untuk menyimpan format nama folder zip
- ``` char *arg[] = {"zip", "-rm", zip, name, NULL}; execv("/usr/bin/zip", arg); ``` untuk mengzip folder dan ``` -rm ``` untuk menghapus folder yang bukan zip

**d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut mengenerate  sebuah  program  "killer" yang  siap  di  run(executable)  untuk menterminasi  semua  operasi program  tersebut.  Setelah  di  run,  program  yang menterminasi ini lalu akan mendelete dirinya sendiri**


**e. Kiwa  menambahkan  bahwa  program  utama  bisa  dirun  dalam  dua  mode,  yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b.  Ketika  dijalankan  dalam  MODE_A,  program  utama  akan  langsung menghentikan  semua operasinya  ketika  program  killer  dijalankan.  Untuk MODE_B,  ketika  program  killer  dijalankan,  program  utama akan  berhenti  tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai (semua folder terisi gambar, terzip lalu di delete)**

> Full code [soal2_revisi.c](https://github.com/redruby1/SoalShiftSISOP20_modul2_A06/blob/master/soal2/soal2_revisi.c)

## Soal 3
Jaya  adalah  seorang  programmer  handal  mahasiswa  informatika.  Suatu  hari  dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).

**a. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”**

```
int main() {
	pid_t anak1, anak2, anak3, anak4, anak5;
	int status;
	
	...
	...
	
	anak1 = fork();
	
	if(anak1 == 0) {
		char *argv[] = {"mkdir", "-p", "modul2/indomie", NULL};
	    	execv("/bin/mkdir", argv);
    	
    	sleep(5);
	}
	else {
		while ((wait(&status)) > 0);
		anak2 = fork();
		
		if(anak2 == 0) {
			char *argv[] = {"mkdir", "-p", "modul2/sedaap", NULL};
	    		execv("/bin/mkdir", argv);
		}
		else {
			
			...
			...
		}
	}
}
```

- ``` char *argv[] = {"mkdir", "-p", "modul2/indomie", NULL}; execv("/bin/mkdir", argv); sleep(5); ```
Child process membuat directori bernama _indomie_ dan ``` sleep(5) ``` untuk menunggu 5 detik sebelum proses selanjutnya

- ``` char *argv[] = {"mkdir", "-p", "modul2/sedaap", NULL}; execv("/bin/mkdir", argv); ```
Parent process membuat directori bernama _sedaap_ setelah child process selesai melakukan tugasnya

**b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”** 

```
char *argv[] = {"unzip", "jpg.zip", "-d", "modul2/", NULL};
execv("/usr/bin/unzip", argv);
```

- unzip ``` jpg.zip ``` dan memasukkan hasilnya ke directori  ``` modul2 ```

*Hasil a & b*

![soal3_1](https://github.com/redruby1/SoalShiftSISOP20_modul2_A06/blob/master/img/soal3_1.PNG)

**c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”**

```
...
...
if(anak4 == 0) { //membaca isi directory
	pid_t baru1, baru2;
	int status1;
					
	DIR *d;
	struct dirent *dir;
	int i;
					
	if((d = opendir("modul2/jpg")) != NULL) {
		while((dir = readdir(d)) != NULL) {
        	if(dir->d_type == DT_REG){
		       	strcpy(filename[j], dir->d_name); //file
		       	j++;
		}
	        else {
	        	strcpy(filename2[k], dir->d_name); //dir
	        	k++;
		}
	}
	closedir(d);
}
					
for(i=0; i<j; i++) { //memindahkan tipe file ke directory sedaap
	baru1 = fork();
						
	char name[30];
	sprintf(name, "modul2/jpg/%s", filename[i]);
						
	if(baru1 == 0) {
		char *argv[] = {"mv", name, "modul2/sedaap", NULL};
		execv("/bin/mv", argv);
	}
}
					
for(i=2; i<k; i++) { //memindahkan tipe directori ke directori indomie
	baru1 = fork();
						
	char name[30];
	sprintf(name, "modul2/jpg/%s", filename2[i]);
						
	if(baru1 == 0) {
		char *argv[] = {"mv", name, "modul2/indomie", NULL};
		execv("/bin/mv", argv);
	}
	else {
		...
		...
	}
}
...
...
```

- ``` char filename[256][256], filename2[256][256]; ``` digunakan untuk menyimpan nama-nama file dan directori. ``` filename[] ``` untuk menyimpan nama file, dan ``` filename2[] ``` untuk menyimpan nama directori
- membaca isi directori
  ```
  if((d = opendir("modul2/jpg")) != NULL) { //membuka directori jpg
    while((dir = readdir(d)) != NULL) { //jika directori jpg tidak kosong
            if(dir->d_type == DT_REG){ //jika datanya bertipe reguler alias file
              strcpy(filename[j], dir->d_name); //file disimpan ke filename[]
              j++; //jumlah file
      }
      else { //jika bertipe lainnya alias directori
            strcpy(filename2[k], dir->d_name); //direrctory disimpan ke filename2[]
              k++; //jumlah directori
      }
    }
    closedir(d); //menutup directori jpg
  }
  ```
- memindahkan tipe file ke directori _sedaap_
  ```
  for(i=0; i<j; i++) { //loop sebanyak jumlah file
    baru1 = fork();
    char name[30]; //menyimpan nama file
    sprintf(name, "modul2/jpg/%s", filename[i]); //menyalin nama file ke variabel

    if(baru1 == 0) {
      char *argv[] = {"mv", name, "modul2/sedaap", NULL}; //memindahkan file ke directori sedaap
      execv("/bin/mv", argv);
    }
  }
  ```
- memindahkan tipe directori ke directori _indomie_
  ```
  for(i=2; i<k; i++) { //loop sebanyak jumlah directori-2 (dimulai dari index 2 agar . dan .. tidak ikut)	
    baru1 = fork();
    char name[30]; //menyimpan nama directoryi
    sprintf(name, "modul2/jpg/%s", filename2[i]); //menyalin nama directori ke variabel

    if(baru1 == 0) {
      char *argv[] = {"mv", name, "modul2/indomie", NULL}; //memindahkan directori ke directori indomie
      execv("/bin/mv", argv);
    }
    else {
      ...
      ...
    }
  }
  ```

**d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”**

```
...
...
else {
	while ((wait(&status1)) > 0);
	baru2 = fork();
				
	char name2[30];
	sprintf(name2, "modul2/indomie/%s/coba1.txt", filename2[i]);
							
	if(baru2 == 0) {
		char *argv[] = {"touch", name2, NULL};
    		execv("/usr/bin/touch", argv);
    				
    		sleep(3);
	}
	else {
		while ((wait(&status1)) > 0);
		baru2 = fork();
								
		char name3[30];
		sprintf(name3, "modul2/indomie/%s/coba2.txt", filename2[i]);
								
		if(baru2 == 0) {
			char *argv[] = {"touch", name3, NULL};
			execv("/usr/bin/touch", argv);
		}
	}
}
...
...
```

- saat memindahkan tipe directori ke directori _indomie_ akan langsung membuat file coba1.txt dan coba2.txt di dalam directori
- membuat file coba1.txt
  ```
  char name2[30]; //menyimpan nama directory
  sprintf(name2, "modul2/indomie/%s/coba1.txt", filename2[i]); //menyalin nama directori untuk membuat coba1.txt di dalam directori

  if(baru2 == 0) {
    char *argv[] = {"touch", name2, NULL}; //membuat file coba1.txt
    execv("/usr/bin/touch", argv);

        sleep(3); //menunggu 3 detik untuk memproses proses selanjutnya
  }
  ```

- membuat file coba2.txt juga menggunakan cara yang sama seperti diatas

*Hasil c & d*

![soal3_2](https://github.com/redruby1/SoalShiftSISOP20_modul2_A06/blob/master/img/soal3_2.PNG)

![soal3_4](https://github.com/redruby1/SoalShiftSISOP20_modul2_A06/blob/master/img/soal3_4.PNG)

![soal3_3](https://github.com/redruby1/SoalShiftSISOP20_modul2_A06/blob/master/img/soal3_3.PNG)

> Full code [soal3.c](https://github.com/redruby1/SoalShiftSISOP20_modul2_A06/blob/master/soal3/soal3.c)

*Menjalankan soal3*

Menggunakan command ``` ./soal3 ``` pada terminal, ``` soal3 ``` merupakan nama program
