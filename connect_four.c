#include <stdio.h>
#include <stdbool.h>

// Definisi Papan
#define BARIS 6
#define KOLOM 7

// Karakter Papan
#define KOSONG ' '
#define PLAYER1 'X' // Praktikan 1
#define PLAYER2 'O' // Praktikan 2

// Prototipe Fungsi
void inisialisasi_papan(char papan[BARIS][KOLOM]);
void tampilkan_papan(char papan[BARIS][KOLOM]);
bool cek_menang(char papan[BARIS][KOLOM], char player);
bool jatuhkan_bidak(char papan[BARIS][KOLOM], int kolom, char player);

// =========================================================
// Fungsi Utama (main)
// =========================================================

int main() {
    char papan[BARIS][KOLOM];
    int langkah = 0;
    int input_kolom;
    char player_sekarang = PLAYER1;
    bool game_selesai = false;

    inisialisasi_papan(papan);

    printf("======================================\n");
    printf("        CONNECT FOUR (JEJER EMPAT)\n");
    printf("======================================\n");
    printf("Player 1: 'X' | Player 2: 'O'\n\n");

    // Loop Utama Permainan
    while (!game_selesai && langkah < BARIS * KOLOM) {
        tampilkan_papan(papan);
        
        printf("Giliran Player %c. Masukkan kolom (1-%d): ", player_sekarang, KOLOM);
        if (scanf("%d", &input_kolom) != 1) {
            // Bersihkan buffer jika input bukan angka
            while (getchar() != '\n');
            printf("❌ Input tidak valid. Masukkan angka kolom.\n");
            continue;
        }

        int kolom_idx = input_kolom - 1; // Konversi 1-based ke 0-based

        if (kolom_idx < 0 || kolom_idx >= KOLOM) {
            printf("❌ Kolom %d di luar batas (1-%d).\n", input_kolom, KOLOM);
            continue;
        }

        if (jatuhkan_bidak(papan, kolom_idx, player_sekarang)) {
            langkah++;

            if (cek_menang(papan, player_sekarang)) {
                tampilkan_papan(papan);
                printf("\n======================================\n");
                printf("🎉 SELAMAT! Player %c MENANG!\n", player_sekarang);
                printf("======================================\n");
                game_selesai = true;
            } else if (langkah == BARIS * KOLOM) {
                tampilkan_papan(papan);
                printf("\n======================================\n");
                printf("🤝 Permainan Seri (Papan Penuh)!\n");
                printf("======================================\n");
                game_selesai = true;
            } else {
                // Ganti giliran
                player_sekarang = (player_sekarang == PLAYER1) ? PLAYER2 : PLAYER1;
            }
        } else {
            printf("❌ Kolom %d sudah penuh. Pilih kolom lain.\n", input_kolom);
        }
    }

    return 0;
}

// =========================================================
// Fungsi-fungsi Permainan
// =========================================================

/**
 * Mengisi papan dengan karakter KOSONG.
 */
void inisialisasi_papan(char papan[BARIS][KOLOM]) {
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            papan[i][j] = KOSONG;
        }
    }
}

/**
 * Menampilkan kondisi papan saat ini ke konsol.
 */
void tampilkan_papan(char papan[BARIS][KOLOM]) {
    printf("\n");
    // Tampilkan label kolom
    for (int j = 1; j <= KOLOM; j++) {
        printf(" %d ", j);
    }
    printf("\n");
    
    // Tampilkan papan dan garis
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            printf("|%c|", papan[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Mencoba menjatuhkan bidak ke kolom yang dipilih.
 * @return true jika berhasil, false jika kolom penuh.
 */
bool jatuhkan_bidak(char papan[BARIS][KOLOM], int kolom, char player) {
    // Cari baris terendah yang kosong di kolom tersebut
    for (int i = BARIS - 1; i >= 0; i--) {
        if (papan[i][kolom] == KOSONG) {
            papan[i][kolom] = player;
            return true;
        }
    }
    return false; // Kolom penuh
}

/**
 * Memeriksa apakah pemain tertentu telah menang (4 bidak berjejer).
 * @return true jika ada 4 bidak berjejer, false jika tidak.
 */
bool cek_menang(char papan[BARIS][KOLOM], char player) {
    int i, j;
    
    // 1. Cek Horizontal
    for (i = 0; i < BARIS; i++) {
        for (j = 0; j <= KOLOM - 4; j++) {
            if (papan[i][j] == player && 
                papan[i][j+1] == player && 
                papan[i][j+2] == player && 
                papan[i][j+3] == player) {
                return true;
            }
        }
    }

    // 2. Cek Vertikal
    for (j = 0; j < KOLOM; j++) {
        for (i = 0; i <= BARIS - 4; i++) {
            if (papan[i][j] == player && 
                papan[i+1][j] == player && 
                papan[i+2][j] == player && 
                papan[i+3][j] == player) {
                return true;
            }
        }
    }

    // 3. Cek Diagonal (dari Kiri Atas ke Kanan Bawah)
    for (i = 0; i <= BARIS - 4; i++) {
        for (j = 0; j <= KOLOM - 4; j++) {
            if (papan[i][j] == player && 
                papan[i+1][j+1] == player && 
                papan[i+2][j+2] == player && 
                papan[i+3][j+3] == player) {
                return true;
            }
        }
    }

    // 4. Cek Diagonal (dari Kiri Bawah ke Kanan Atas)
    for (i = 3; i < BARIS; i++) { // Mulai dari baris 3 ke atas (indeks 5,4,3)
        for (j = 0; j <= KOLOM - 4; j++) {
            if (papan[i][j] == player && 
                papan[i-1][j+1] == player && 
                papan[i-2][j+2] == player && 
                papan[i-3][j+3] == player) {
                return true;
            }
        }
    }

    return false;
}