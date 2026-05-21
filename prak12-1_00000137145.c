#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
// Menyiapkan string yang akan ditulis ke dummy.txt
 char my_write_str[] = "1234567890";

 // Menyiapkan array (buffer) untuk menampung teks yang nanti akan dibaca dari file
 char my_read_str[100];

 // Menentukan nama file yang akan digunakan
 char my_filename[] = "dummy.txt";

 // Variabel untuk menyimpan identitas file (FD) setelah dibuka
 int my_file_descriptor, close_err;

 // Membuka file dummy.txt, ada beberapa flag yang digunakan:
 // 1. O_RDWR : BUka file untuk mode read dan write
 // 2. O_CREAT : Buat file baru jika belum ada
 // 3. O_TRUNC : jika file sudah ada, hapus seluruh isinya
 my_file_descriptor = open (my_filename, O_RDWR | O_CREAT | O_TRUNC);

 // Menulis 10 Byte karakter dari arr my_srite_str ke dalam file
 write (my_file_descriptor, (void *) my_write_str, 10);

 // Memastikan / menyinkronkan data yang baru di tulis benar-benar tersimpan ke disk
 fsync (my_file_descriptor);

 // Mengatur ulang posisi kursor (pointer) di dalam file.
 // SEEK_SET dengan offset 0 berarti memindahkan kursor kembali ke indeks awal file.
 lseek (my_file_descriptor, 0, SEEK_SET);

 // Membaca 10 byte dari file (mulai dari awal karena lseek) dan menaruhnya ke my_read_str
 read (my_file_descriptor, (void *) my_read_str, 10);

 // Menambahkan null-terminator di akhir array agar terbaca sebagai string C yang valid
 my_read_str[10] = '\0';

 // Menampilkan hasil read
 printf ("String read = %s.\n", my_read_str);

 // Menutup file untuk mengamankan data dan membebaskan resource sistem operasi
 close(my_file_descriptor);

 return 0; // Mengakhiri program dengan status sukses
}