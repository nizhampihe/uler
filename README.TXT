/*-=----=----=----=----=----=-*
 *   __   __                  *
 *  / /  /  \___  __          *
 * / /__/ / / _ \/ *\         *
 * \_____/ / /__/ /\/         *
 *  ULER \ \_____/            *
 *   GAME \___/ v1.2.0        *
 *                            *
 *        (c) 2019 NizhamPihe *
 *-=----=----=----=----=----=-*/

DESCRIPTION
===========
    Program Game Console Snake
  Sederhana

PREREQUISITES
=============
  - MinGW-W64 Compiler

INSTALATION
===========
  > gcc -o ULER.EXE -c ULER.C

GAMEPLAY
========

  HOW TO PLAY
  ===========
    - Gunakan tombol panah
      untuk mengubah arah
      gerak ular
    - Ambil buah untuk
      mendapatkan score
    - Semakin banyak buah
      yang diambil tubuh
      ular semakin panjang
    - Jangan sampai menabrak
      tembok
    - Jangan sampai memakan
      diri sendiri

  CONTROL
  =======
    - Panah : Jalan
    - P     : Pause
    - R     : Restart
    - Esc   : Keluar

  FEATURES
  ========
    - ASCII Block Graphic
    - Command Line Configuration
    - Infinite mode
    - Difficulty
    - Colorful
    - Restart Button
    - Pause Button
    - Play Again
    - High Score

COMMAND LINE CONFIGURATION
==========================
  usage : uler [/i] [/d <e/m/h>]
               [/c] [/s <height>
               <widht>] [/?]

  /i      Mengaktifkan Infinite
          Mode
  /d      Mengatur Tingkat
          Kesulitan (see below)
  /c      Menonaktifkan Warna
  /s      Mengatur Ukuran Papan
          (see below)
  /?      Melihat Bantuan

  NOTE : - Ukuran pada /s diukur
           dalam satuan pixel
           dihiung dari dalam
           tembok
         - Ukuran minimum yang
           dapat ditetapkan
           adalah 9 x 9 pixel
           dengan ukuran
           maksimum 20 x 20
           pixel
         - Semakin besar ukuran
           akan memperlambat
           jalannya program
         - Jika /s tidak
           ditetapkan maka
           ukuran menjadi
           default 9 x 9 pixel
         - Jika /s hanya
           menetapkan
           tingginya saja maka
           lebar akan dianggap
           sama dengan tingginya
         - Tingkat kesulitan
           dilihat dari
           kecepatan gerak ular
         - Terdapat 3 tingkat
           kesulitan yaitu
           e -> easy (5 p/s)
           m -> medium (10 p/s)
           h -> hard (20 p/s)
         - Jika /d tidak
           ditetapkan maka
           tingkat kesulitan
           menjadi default easy

CHANGE LOG
==========

  v1.2.0 [Display Update]
  (February 1, 2019)
  =======================
    - Add Color
    - Bug Fixes

  v1.1.2
  (February 1, 2019)
  ==================
    - Add Difficulty
      Configurartion
    - Bug Fixes

  v1.1.1
  (February 1, 2019)
  ==================
    - Add Size Configurartion
    - Bug Fixes

  v1.1.0 [Command Update]
  (February 1, 2019)
  =======================
    - Add Infinite Mode
    - Command Line Configuration
    - Bug Fixes

  v1.0.2
  (February 1, 2019)
  ==================
    - Restart Button
    - Bug Fixes

  v1.0.1
  (February 1, 2019)
  ==================
    - Play Again
    - High Score
    - Bug Fixes

  v1.0.0 [First Release]
  (February 1, 2019)
  ======================
    - First Proper Release

  v1.0.0-beta
  (February 1, 2019)
  ==================
    - Beta Release

CONTRIBUTING
============
    Terbuka untuk segala
  kontribusi mulai dari kode
  sumber hingga yang lainnya.
  Silahkan buka Pull Request
  untuk untuk berkontribusi.
  Jika ada masalah silahkan
  buka Issue untuk diskusikan.

INFORMATION
===========
  App Name   = Uler Game
  File Name  = ULER.C
  Version    = v1.2.0
  Update     = February 1, 2019
  Category   = GAME
  Genre      = ARCADE
  Platform   = WINDOWS CONSOLE
               (Command Prompt)
  App Size   = 162798 bytes
  Code Lines = 942 lines

COPYRIGHT
=========
  Copyright (c) 2019, NizhamPihe
  Released Under The MIT License
  See LICENSE.TXT for full
  details