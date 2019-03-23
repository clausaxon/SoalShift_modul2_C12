# SoalShift_modul2_C12


### 1.Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.

Catatan : Tidak boleh menggunakan crontab.

•	Membuat array of character bernama totalfile (nama file lengkap), hasil, totalfile2 (hasil copy dari totalfile), dan file2 yag berisi “_grey.png”. 

char totalfile[100];
char hasil[100];
char totalfile2[100];
char file2[100] = “_grey.png”;
char *file;

•	Digunakan untuk membuka direkori dan membaca file.

dir *dir = opendir(“/home/hayu/modul2/soal1”);
struct dirent *d;

•	Jika dir kosong maka akan return 0.

if(dir == NULL)
    return 0;

•	Tetapi jika tidak kosong, maka akan mengambil nama file dari direktori dan di copy ke totalfile. Setelah itu, alamat dari titik yang berada di totalfile akan disimpan di file. Setelah itu, mengcopy dari totalfile ke totalfile2.

while((d = readdir(dir)) != NULL) {
   strcpy(totalfile, d->d_name);
   file = strrchr(totalfile, ‘.’);
   strcpy(totalfile2, totalfile);


•	Jika isi dari file sama dengan “.png”, menggantikan posisi titik dengan ‘\0’. Lalu, mengcopy totalfile ke hasil dan menggabungkan hasil dengan file2. Setelah itu, menggabungkan awal dengan totalfile2 dan tujuan dengan hasil. Melakukan rename.

if(file && (strcmp(file, “.png”)==0)){
   *file = ‘\0’;
   strcpy(hasil, totalfile);
   strcat(hasil, file2);
   char awal[500] = (“/home/hayu/modul2/soal1/”);
   char tujuan[500] = (“/home/hayu/modul2/soal1/gambar/”);
   strcat(awal, totalfile2);
   strcat(tujuan, hasil);
   rename(awal, tujuan);
}

•	Untuk menjalaninya dengan mengetikkan 
gcc -o soal1 soal1.c

•	Setelah itu ketik
./soal1

•	Berikut adalah foto dari no 1:

![1 - shift 2](https://user-images.githubusercontent.com/47876805/54426523-abfac080-474a-11e9-81c3-ba44555f495f.png)

![1 (2) - shift 2](https://user-images.githubusercontent.com/47876805/54426528-aef5b100-474a-11e9-8f03-75fc98b6952d.png)

### 2.Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.

Catatan: Tidak boleh menggunakan crontab

![Screenshot from 2019-03-15 19-37-12](https://user-images.githubusercontent.com/34019306/54413701-3cc0a480-4729-11e9-98c2-da0dee5f0794.png)

Jadi kita menggunakan struct stat sb untuk mengakses dan menyimpan name owner dan grup dari data elen.ku.
struct stat sudah memiliki structnya sendiri dari linux, bisa dilihat di man stat pada terminal.

Lalu kita bikin char untuk menyimpan owner dan grup, dalam codingan ini variablenya simpanpw, dan simpangr.

Lalu saya menggunakan string compare untuk membandingkan owner dan group sebelum diubah menjadi www-data agar jika sudah berubah program bisa menghapus elen.ku dalam waktu 3 detik dengan menggunakan daemon.

Terakhir karena ada masalah permission maka kita harus mengubah aksesnya menjadi 0777 menggunakan chmod, tetapi kita harus mentraslate bentuk 0777(string) menjadi bentuk Oktal menggunakan strtoul.




### 3.Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :

i)  mengekstrak file zip tersebut.

ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt.

Catatan:

Gunakan fork dan exec.

Gunakan minimal 3 proses yang diakhiri dengan exec.

Gunakan pipe

Pastikan file daftar.txt dapat diakses dari text editor

child pertama digunakan untuk mengunzip file yang diinginkan :

```c
 if(child1 == 0){
      execl("/usr/bin/unzip","unzip", "campur2.zip", NULL);
}else
```

lalu di child process selanjutnya mendapatkan list file yang diinginkan dari file unzip:

```c
 if(child2==0){
          close(pip[0]);
          close(pip[2]);
          close(pip[3]);
          dup2(pip[1], STDOUT_FILENO);
          close(pip[1]);
          execl("/bin/ls", "ls" ,"campur2", NULL);
}else
```

Lalu menggunakan fungsi grep untuk mengambil file ekstensi .txt saja di dalam child process ketiga :

```c
if(child3==0){
              close(pip[1]);
              dup2(pip[0],STDIN_FILENO);
              close(pip[0]);

              close(pip[2]);
              dup2(pip[3],STDOUT_FILENO);
              close(pip[3]);
              execl("/bin/grep", "grep" ,".txt$", NULL);
}else
```

outputnya dituliskan di file daftar.txt dalam parent procces child 3
```c
else{
              close(pip[1]);
              close(pip[0]);
              close(pip[3]);
              int x = read(pip[2],isi,sizeof(isi));
              close(pip[2]);
              FILE* output;
              output = fopen("daftar.txt","w+");
              fputs(isi,output);
              fclose(output);
}
```



### 4.Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:

File makan_enak.txt terakhir dibuka pada detik ke-1

Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan:

dilarang menggunakan crontab

Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

![Screenshot from 2019-03-15 19-49-06](https://user-images.githubusercontent.com/34019306/54413845-c1132780-4729-11e9-835c-f5fb04ce8757.png)

Pertama kita harus mengambil data local time dengan menggunakan struct stat. bisa dilihat di man stat

Lalu kita harus membandingkan waktu saat pertama kali makan_enak dibuka dengan local time. dikasus ini saya menggunakan difftime untuk menghitung perbedaan waktu dengan basis  detik.

Lalu kita gunakan if, jika memang benar jarak waktu kurang dari 30 maka kita akan membuat file makan_sehat dengan fungsi creat(filename,mode);

lalu menggunakan daemon untuk terus berjalan tiap 5 detik dalam membuat file makan_sehat hingga terbentuk kurang lebih 6 file yang berurutan.






### 5.Kerjakan poin a dan b di bawah:
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log

Ket:

a. Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]

Per menit memasukkan log#.log ke dalam folder tersebut

‘#’ : increment per menit. Mulai dari 1

•	Variabel timenow akan dimasukkan kedalam time, dimana time sudah ke set di system. Namun time masih menggunakan waktu internasional, maka diubah menjadi localtime.

struct tm *currtime;
time_t timenow;
time(&timenow);
currtime = localtime(&timenow);

•	Membuat array of character bernama folder dan path yang akan berisi “/home/hayu/log/”.

char folder[50];
char path[100];
strcpy(path, "/home/hayu/log/");

•	Kemudian simpan hari, bulan, tahun, jam, dan menit didalam array of char yang bernama folder. Setelah itu, folder akan print dalam bentuk string. Lalu, menggabungkan path dengan folder. Kemudian, membuat folder. Maksud dari S_IRWXU | S_IRWXO | S_IRWXG adalah read, write dan execute permission bagi user, owner, dan group.

sprintf(folder, "%02d:%02d:%02d-%02d:%02d", currtime->tm_mday, currtime->tm_mon + 1, currtime->tm_year + 1900, currtime->tm_hour, currtime->tm_min);
strcat(path, folder);
mkdir(path, S_IRWXU | S_IRWXO | S_IRWXG);

•	Membuat loop agar dalam 30 menit akan terbentuk 1 folder log dengan isi 30 file log. Setelah itu, membuat file read dan write. File read gunanya untuk melakukan read dari syslog yang berada di “/var/log/syslog”, sedangkan file write gunanya untuk melakukan write dari file yang akan dilakukan setelah kita menyimpan “%s/log%d.log” dimana %s akan diisi path dan %d akan diisi i+1, yang awalnya I adalah 0. Kemudian print. 

for(int i=0; i<30; i++){
char file[100];
char c;
char syslog[100] = "/var/log/syslog";
FILE *read = fopen(syslog, "r");
sprintf(file, "%s/log%d.log", path, i+1);
FILE *write = fopen(file, "w+");

•	Selama read dan write masih ada isinya, maka akan melakukan print syslog ke file log. Lalu, sleep(60) adalah perintah untuk membuat file setiap menit (60 detik).

if(read != NULL && write != NULL){
while((c = fgetc(read))  != EOF){
fputc(c, write);
}
fclose(write);
      fclose(read);
            }
      sleep(60);
        }
    }
    
•	Untuk menjalaninya ketik gcc –o soal5a soal5a.c, lalu ketik ./soal5a
•	Hasilnya seperti ini, namun saya mengganti sleep menjadi 1 detik:

![image](https://user-images.githubusercontent.com/47876805/54863906-2d70d500-4d81-11e9-8926-a13930861379.png)

•	Isi dari folder tersebut:

![image](https://user-images.githubusercontent.com/47876805/54863911-319cf280-4d81-11e9-99eb-decd6f6a7f14.png)

•	Berikut adalah foto dari kodingan no 5a:

![image](https://user-images.githubusercontent.com/47876805/54863912-35c91000-4d81-11e9-846e-acdf61cf091a.png)

![image](https://user-images.githubusercontent.com/47876805/54863914-3c578780-4d81-11e9-9bab-51edced13494.png)

b. Buatlah program c untuk menghentikan program di atas.

NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

•	Maksud dari kodingan diatas adalah mengimplementasikan bash pkill soal5a dalam bahasa C.
•	Untuk menjalankannya ketik gcc –o soal5b soal5b.c, lalu ketik ./soal5b. 
•	Berikut adalah foto kodingan dari 5b:

![image](https://user-images.githubusercontent.com/47876805/54863916-3feb0e80-4d81-11e9-89ea-76a29fbf8e28.png)


Link sumber buat pengerjaan soal :

soal 1

https://www.sanfoundry.com/c-program-list-files-directory/

soal 2

https://stackoverflow.com/questions/36069748/c-get-owner-and-group-of-file-directory

https://stackoverflow.com/questions/4568681/using-chmod-in-a-c-program

soal 4

https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program

https://stackoverflow.com/questions/31633943/compare-two-times-in-c

https://linux.die.net/man/3/creat





