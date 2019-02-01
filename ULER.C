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

void uler (int ,char **) ;

int main (int   argc,
          char *argv[])
{
  uler (argc, argv) ;
  return 0 ;
}

/*-=----=----=----=----=----=-*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

typedef enum
{
  awal,
  maen,
  paul,
  paur,
  paus,
  goy,
  gon,
  over
} MDE ;

typedef enum
{
  kosong,
  dinding,
  kanan,
  kiri,
  atas,
  bawah,
  buah
} ITM ;

typedef struct
{
  int height ;
  int widht ;
  int color ;
  int diff ;
  int infi ;
  int error ;
} SET ;

typedef struct
{
  int x ;
  int y ;
} LOC ;

/*-=----=----=----=----=----=-*/

void up (int h)
{ /*Reset Layar*/
  COORD loc ;
  CONSOLE_SCREEN_BUFFER_INFO
    csbi ;
    
  GetConsoleScreenBufferInfo (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), &csbi
  ) ;
  
  loc.X = 0 ;
  loc.Y =
  csbi.dwCursorPosition.Y - h ;
  
  SetConsoleCursorPosition (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), loc
  ) ;
}

void warna (int color)
{ /*Mengatur Warna*/
  SetConsoleTextAttribute (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), color
  ) ;
}

int inisiasi ()
{ /*Awal Program*/
  CONSOLE_CURSOR_INFO cinfo ;
  CONSOLE_SCREEN_BUFFER_INFO
  csbi ;
  
  GetConsoleCursorInfo (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), &cinfo
  ) ;
  GetConsoleScreenBufferInfo (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), &csbi
  ) ;
  
  cinfo.bVisible = FALSE ;
  
  SetConsoleTitle (
    "Uler Game"
  ) ;
  SetConsoleCursorInfo (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), &cinfo
  ) ;
  
  return csbi.wAttributes ;
}

void terminasi (int color)
{ /*Akhir Program*/
  CONSOLE_CURSOR_INFO cinfo ;
  
  GetConsoleCursorInfo (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), &cinfo
  ) ;
  
  cinfo.bVisible = TRUE ;
  
  SetConsoleCursorInfo (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), &cinfo
  ) ;
  
  warna (color) ;
  getch () ;
}

/*-=----=----=----=----=----=-*/

int angka (char *str)
{ /*String ke Integer*/
  int i = 0 ;
  int a = 0 ;
  while (str [i] != 0)
  {
    a *= 10 ;
    a += str [i] - 48 ;
    i++ ;
  }
  return a ;
}

int waritm (ITM a)
{
  switch (a)
  {
    case dinding :
      return 15 ;
    case kanan :
    case kiri :
    case atas :
    case bawah :
      return 10 ;
    case buah :
      return 12 ;
    default :
      return 0 ;
  }
  return 0 ;
}

void clier (char *str)
{ /*Command Help*/
  int i ;
  printf (
    "usage : %s [/i] [/d "
    "<e/m/h>]\n        ", str
  ) ;
  for (
    i = 0 ; str [i] != 0 ;
    i++
  )
    printf (" ") ;
  printf (
    " [/c] [/s <height>\n"
    "        "
  ) ;
  for (
    i = 0 ; str [i] != 0 ;
    i++
  )
    printf (" ") ;
  printf (
    " <widht>] [/?]\n\n"
    "/i      Mengaktifkan "
    "Infinite\n"
    "        Mode\n"
    "/d      Mengatur Tingkat\n"
    "        Kesulitan (see"
    " below)\n"
    "/c      Menonaktifkan"
    " Warna\n"
    "/s      Mengatur Ukuran"
    " Papan\n"
    "        (see below)\n"
    "/?      Melihat"
    " Bantuan\n\n"
    "NOTE : - Ukuran pada /s"
    " diukur\n"
    "         dalam satuan"
    " pixel\n"
    "         dihiung dari"
    " dalam\n"
    "         tembok\n"
    "       - Ukuran minimum"
    " yang\n"
    "         dapat"
    " ditetapkan\n"
    "         adalah 9 x 9"
    " pixel\n"
    "         dengan ukuran\n"
    "         maksimum"
    " 20 x 20\n"
    "         pixel\n"
    "       - Semakin besar"
    " ukuran\n"
    "         akan"
    " memperlambat\n"
    "         jalannya"
    " program\n"
    "       - Jika /s tidak\n"
    "         ditetapkan maka\n"
    "         ukuran menjadi\n"
    "         default 9 x 9"
    " pixel\n"
    "       - Jika /s hanya\n"
    "         menetapkan\n"
    "         tingginya saja"
    " maka\n"
    "         lebar akan"
    " dianggap\n"
    "         sama dengan"
    " tingginya\n"
    "       - Tingkat"
    " kesulitan\n"
    "         dilihat dari\n"
    "         kecepatan gerak"
    " ular\n"
    "       - Terdapat 3"
    " tingkat\n"
    "         kesulitan yaitu\n"
    "         e -> easy (5"
    " p/s)\n"
    "         m -> medium (10"
    " p/s)\n"
    "         h -> hard (20"
    " p/s)\n"
    "       - Jika /d tidak\n"
    "         ditetapkan maka\n"
    "         tingkat"
    " kesulitan\n"
    "         menjadi default"
    " easy\n"
  ) ;
}

SET getsize (SET   set,
             int  *i,
             int   argc,
             char *argv[])
{ /*Mngambil Ukuran*/
  int a = set.height ;
  int b = set.widht ;
  if (argc > *i + 1)
  if (
    argv [*i + 1][0] >= 48 &&
    argv [*i + 1][0] <= 57
  )
  {
    a = angka (argv [*i + 1]) ;
    a = (a < 9) ?  9 : (
      (a > 20) ? 20 : a) ;
    (*i)++ ;
    if (argc > *i + 1)
    if (
      argv [*i + 1][0] >= 48 &&
      argv [*i + 1][0] <= 57
    )
    {
      b = angka (
        argv [*i + 1]
      ) ;
      b = (b < 9) ?  9 : (
        (b > 20) ? 20 : b) ;
      (*i)++ ;
    }
    else b = a ;
    else b = a ;
  }
  set.height = a ;
  set.widht = b ;
  return set ;
}

SET args (int   argc,
          char *argv[])
{ /*Argument Setting*/
  SET set = (SET) {
    9, 9, 1, 50, 0, 0
  } ;
  
  for (
    int i = 1 ; i < argc ; i++
  )
  {
    if (
      argv [i][0] == '/' &&
      argv [i][2] == 0
    )
      switch (argv [i][1])
      {
        case 'i' :
          set.infi = 1 ;
          break ;
        case 'd' :
          if (argc > i + 1)
          if (
            argv [i + 1][1] == 0
          )
          switch (
            argv [i + 1][0]
          )
          {
            case 'e' :
              set.diff = 100 ;
              i++ ;
              break ;
            case 'm' :
              set.diff = 50 ;
              i++ ;
              break ;
            case 'h' :
              set.diff = 10 ;
              i++ ;
              break ;
          }
          break ;
        case 'c' :
          set.color = 0 ;
          break ;
        case 's' :
          set = getsize (
            set, &i, argc, argv
          ) ;
          break ;
        case '?' :
          set.error = 1 ;
          break ;
        default :
          set.error = 1 ;
      }
    else set.error = 1 ;
  }
  
  return set ;
}

void cetak (ITM *papan,
            int  score,
            int  hi,
            int  h,
            int  w,
            int  col,
            MDE  mode)
{ /*Menampilkan Layar*/
  int i, j, s = 4, r = 4 ;
  ITM a, b ;
  
  char scr[] = "00000" ;
  char his[] = "00000" ;
  if (col) warna (11) ;
  printf ("Hi   ") ;
  if (col) warna (9) ;
  printf (" : ") ;
  if (col) warna (13) ;
  while (hi > 0)
  {
    his [r] = hi % 10 + 48 ;
    hi /= 10 ;
    r-- ;
  }
  printf ("%s\n", his) ;
  if (col) warna (11) ;
  printf ("Score") ;
  if (col) warna (9) ;
  printf (" : ") ;
  if (col) warna (13) ;
  while (score > 0)
  {
    scr [s] = score % 10 + 48 ;
    score /= 10 ;
    s-- ;
  }
  printf ("%s\n", scr) ;
  
  for (i = 0 ; i < h ; i++)
  {
    for (j = 0 ; j < w ; j++)
    {
      if (i % 2)
      {
        b = papan [j + i * w] ;
        a = papan [j + (i - 1)
        * w] ;
        
        if (
          (mode == goy || 
          mode == gon ||
          mode == over) &&
          (i == h / 2 ||
          i == h / 2 - 1) &&
          j == w /2 - 4
        )
        {
          if (col) warna (14) ;
          printf ("Game Over") ;
          j += 8 ;
        }
        else if (
          (mode == paul ||
          mode == paur ||
          mode == paus) &&
          (i == h / 2 ||
          i == h / 2 - 1) &&
          j == w / 2 - 2
        )
        {
          if (col) warna (14) ;
          printf ("Pause") ;
          j += 4 ;
        }
        else if (
          mode == paul &&
          (i == h / 2 + 2 ||
          i == h / 2 + 1) &&
          j == w / 2 - 4
        )
        {
          if (col) warna (14) ;
          printf ("Lanjutkan") ;
          j += 8 ;
        }
        else if (
          (mode == goy ||
          mode == paur) &&
          (i == h / 2 + 2 ||
          i == h / 2 + 1) &&
          j == w / 2 - 2
        )
        {
          if (col) warna (14) ;
          printf ("Ulang") ;
          j += 4 ;
        }
        else if (
          (mode == gon ||
          mode == paus) &&
          (i == h / 2 + 2 ||
          i == h / 2 + 1) &&
          j == w / 2 - 3
        )
        {
          if (col) warna (14) ;
          printf ("Selesai") ;
          j += 6 ;
        }
        else 
        {
          if (col)
          {
            warna (
              waritm (a) |
              waritm (b) << 4
            ) ;
            printf (
              "%c", 223
            ) ;
          }
          else printf (
            "%c", (a > 0) ?
            ((b > 0) ? 219 :
            223) : ((b > 0)
            ? 220 : 32)
          ) ;
        }
      }
    }
    if (i % 2)
      printf ("\n") ;
    if (h % 2 && i == h -1)
    {
      for (j = 0 ; j < w ; j++)
      {
        a = papan [j + i * w] ;
        if (col)
        {
          warna (waritm (a)) ;
          printf ("%c", 223) ;
        }
        else printf (
          "%c", (a > 0) ? 223 :
          32
        ) ;
      }
      printf ("\n") ;
    }
  }
  
  switch (mode)
  {
    case awal :
      if (col) warna (11) ;
      printf ("Panah") ;
      if (col) warna (13) ;
      printf (" : ") ;
      if (col) warna (11) ;
      printf ("Jalan       ") ;
      break ;
    case maen :
      if (col) warna (11) ;
      printf ("P") ;
      if (col) warna (13) ;
      printf (":") ;
      if (col) warna (11) ;
      printf ("Pause") ;
      if (col) warna (9) ;
      printf (" | ") ;
      if (col) warna (11) ;
      printf ("Esc") ;
      if (col) warna (13) ;
      printf (":") ;
      if (col) warna (11) ;
      printf ("Keluar") ;
      break ;
    case over :
      if (col) warna (11) ;
      printf (
        "Press any key . . . "
      ) ;
      break ;
    case goy :
    case gon :
    case paul :
    case paur :
    case paus :
      if (col) warna (11) ;
      printf ("Enter") ;
      if (col) warna (13) ;
      printf (" : ") ;
      if (col) warna (11) ;
      printf ("Pilih       ") ;
      break ;
  }
}

ITM jalan (int  a,
           LOC *loc,
           ITM *papan,
           int  h,
           int  w,
           int  infi)
{ /*Gerak Ular*/
  ITM b ;
  LOC temp = *loc ;
  
  switch (
    papan [temp.x + temp.y * w]
  )
  {
    case kanan :
      if (
        infi && loc->x == w - 2
      ) loc->x = 1 ;
      else loc->x++ ;
      break ;
    case kiri :
      if (
        infi && loc->x == 1
      ) loc->x = w - 2 ;
      else loc->x-- ;
      break ;
    case atas :
      if (
        infi && loc->y == 1
      ) loc->y = h - 2 ;
      else loc->y-- ;
      break ;
    case bawah :
      if (
        infi && loc->y == h - 2
      ) loc->y = 1 ;
      else loc->y++ ;
      break ;
    default :
      break ;
  }
  
  if (a)
  {
    b = papan [loc->x + loc->y
        * w] ;
    papan [loc->x + loc->y * w]
      = papan [temp.x + temp.y
      * w] ;
    return b ;
  }
  else
  {
    papan [temp.x + temp.y * w]
      = kosong ;
  }
  
  return kosong ;
}

void berbuah (ITM *papan,
              int  h,
              int  w)
{
  srand (time (NULL)) ;
  LOC bwh = (LOC) {
    rand () % (w - 2) + 1,
    rand () % (h - 2) + 1
  } ;
  
  while (
    papan [bwh.x + bwh.y * w]
    != kosong
  )
    bwh = (LOC) {
      rand () % (w - 2) + 1,
      rand () % (h - 2) + 1
    } ;
    
  papan [bwh.x + bwh.y * w]
    = buah ;
}

void pause (ITM *papan,
            int  score,
            int *hi,
            int  h,
            int  w,
            int  col,
            int *play,
            int *restart,
            MDE *mode)
{
  int g ;
  *mode = paul ;
  
  do
  {
    up (
      (h % 2) ? h / 2 + 3 :
      h / 2 + 2
    ) ;
    cetak (
      papan, score, *hi, h, w,
      col, *mode
    ) ;
    
    g = getch () ;
    switch (g)
    {
      case 77 :
      case 75 :
      case 72 :
      case 80 :
        *mode = (*mode == paus)
          ? paul : ((*mode ==
          paul) ? paur : paus) ;
        break ;
    }
  }
  while (g != 13) ;
  
  switch (*mode)
  {
    case paul :
      *mode = maen ;
      break ;
    case paur :
      *play = 0 ;
      *restart = 1 ;
      break ;
    case paus :
      *play = 0 ;
      break ;
    default :
      break ;
  }
}

int mulai (int  u,
           int *hi,
           SET  set)
{
  int i, j, g, a ;
  int h = set.height + 2 ;
  int w = set.widht + 2 ;
  ITM l ;
  
  MDE mode = awal ;
  int play = 1 ;
  int score = 0 ;
  int count = 0 ;
  int restart = 0 ;
  
  ITM *papan = (ITM *)
    malloc (
      sizeof (ITM) * w * h
    ) ;
  
  for (i = 0 ; i < h ; i++)
    for (j = 0 ; j < w ; j++)
    {
      if (
        j == 0 || j == w - 1 ||
        i == 0 || i == h - 1
      ) papan [j + i * w]
        = dinding ;
      else papan [j + i * w]
        = kosong ;
    }
    
  LOC pala = (LOC) {w/2, h/2} ;
  for (
    i = pala.x, j = 0 ;
    j < u ; i--, j++
  ) papan [i + pala.y * w]
      = kanan ;
  LOC ekor = (LOC)
    {i + 1, pala.y} ;
  berbuah (papan, h, w) ;
  cetak (
    papan, score, *hi, h, w,
    set.color, mode
  ) ;
  
  mode = maen ;
  getch () ;
  
  do
  { /*Game Loop*/
    if (kbhit ())
    { /*Input Keyboard*/
      switch (getch ())
      {
        case 77 :
          if (
            papan[pala.x +
            pala.y * w] != kiri
          )
            papan[pala.x +
            pala.y * w]
            = kanan ;
          break ;
        case 75 :
          if (
            papan[pala.x +
            pala.y * w] != kanan
          )
            papan[pala.x +
            pala.y * w] = kiri ;
          break ;
        case 72 :
          if (
            papan[pala.x +
            pala.y * w] != bawah
          )
            papan[pala.x +
            pala.y * w] = atas ;
          break ;
        case 80 :
          if (
            papan[pala.x +
            pala.y * w] != atas
          )
            papan[pala.x +
            pala.y * w]
            = bawah ;
          break ;
        case 114 :
          restart = 1 ;
          play = 0 ;
          break ;
        case 112 :
          pause (
            papan, score, hi,
            h, w, set.color,
            &play, &restart,
            &mode
          ) ;
          break ;
        case 27 :
          play = 0 ;
          mode = goy ;
          *hi = (*hi < score) ?
            score : *hi ;
          break ;
      }
    }
    
    up (
      (h % 2) ? h / 2 + 3 :
      h / 2 + 2
    ) ;
    
    if (count)
    { /*Update*/
      l = jalan (
        1, &pala, papan, h, w,
        set.infi
      ) ;
      
      if (l >= 1 && l <= 5)
      {
        play = 0 ;
        mode = goy ;
        *hi = (*hi < score) ?
          score : *hi ;
      }
      else if (l == 6)
      {
        score += 10 ;
        berbuah (papan, h, w) ;
      }
      else jalan (
        0, &ekor, papan, h, w,
        set.infi
      ) ;
      
      count = 0 ;
    }
    else count++ ;
    
    cetak (
      papan, score, *hi, h, w,
      set.color, mode
    ) ;
    Sleep (set.diff) ; /*Delay*/
  }
  while (play) ;
  
  if (!restart && mode != paus)
  {
    do
    {
      g = getch () ;
      switch (g)
      {
        case 77 :
        case 75 :
        case 72 :
        case 80 :
          mode = (mode == goy) ?
            gon : goy ;
          break ;
      }
      
      up (
        (h % 2) ? h / 2 + 3 :
        h / 2 + 2
      ) ;
      cetak (
        papan, score, *hi, h, w,
        set.color, mode
      ) ;
    }
    while (g != 13) ;
  }
  
  up (
      (h % 2) ? h / 2 + 3 :
      h / 2 + 2
  ) ;
  
  if (mode == goy || restart)
    a = 1 ;
  else
  {
    cetak (
      papan, score, *hi, h, w,
      set.color, over
    ) ;
    a = 0 ;
  }
  
  free (papan) ;
  
  return a ;
}

/*-=----=----=----=----=----=-*/

void uler (int   argc,
           char *argv[])
{
  int l, col, u = 3, hi = 0 ;
  
  SET set = args (argc, argv) ;
  
  if (set.error)
    clier (argv [0]) ;
  else
  {
    col = inisiasi () ;
    
    do l = mulai (u, &hi, set) ;
    while (l) ;
    
    terminasi (col) ;
  }
}