/*-=----=----=----=----=----=-*
 *   __   __                  *
 *  / /  /  \___  __          *
 * / /__/ / / _ \/ *\         *
 * \_____/ / /__/ /\/         *
 *  ULER \ \_____/            *
 *   GAME \___/ v1.0.0        *
 *                            *
 *        (c) 2019 NizhamPihe *
 *-=----=----=----=----=----=-*/

void uler (int, int, int) ;

int main (int   argc,
          char *argv[])
{
  uler (3, 9, 9) ;
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
  pause,
  gameover
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

void inisiasi ()
{ /*Awal Program*/
  CONSOLE_CURSOR_INFO cinfo ;
  
  GetConsoleCursorInfo (
    GetStdHandle (
      STD_OUTPUT_HANDLE
    ), &cinfo
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
}

void terminasi ()
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
  getch () ;
}

/*-=----=----=----=----=----=-*/

void cetak (ITM *papan,
            int  score,
            int  h,
            int  w,
            MDE  mode)
{ /*Menampilkan Layar*/
  int i, j, s = 4 ;
  ITM a, b ;
  
  char scr[] = "00000" ;
  printf ("Score : ") ;
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
          mode == gameover &&
          (i == h / 2 ||
          i == h / 2 - 1) &&
          j == w /2 - 4
        )
        {
          printf ("Game Over") ;
          j += 8 ;
        }
        else if (
          mode == pause &&
          (i == h / 2 ||
          i == h / 2 - 1) &&
          j == w / 2 - 2
        )
        {
          printf ("Pause") ;
          j += 4 ;
        }
        else printf (
          "%c",
          (a > 0) ? ((b > 0) ?
          219 : 223) : ((b > 0)
          ? 220 : 32)
        ) ;
      }
    }
    if (i % 2)
      printf ("\n") ;
    if (h % 2 && i == h -1)
    {
      for (j = 0 ; j < w ; j++)
      {
        a = papan [j + i * w] ;
        printf (
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
      printf ("Panah : Jalan") ;
      break ;
    case maen :
      printf ("P:Pause |") ;
      printf (" Esc:Keluar") ;
      break ;
    case pause :
    case gameover :
      printf (
        "Press any key . . . "
      ) ;
      break ;
  }
}

ITM jalan (int  a,
           LOC *loc,
           ITM *papan,
           int  w)
{ /*Gerak Ular*/
  ITM b ;
  LOC temp = *loc ;
  
  switch (
    papan [temp.x + temp.y * w]
  )
  {
    case kanan :
      loc->x++ ;
      break ;
    case kiri :
      loc->x-- ;
      break ;
    case atas :
      loc->y-- ;
      break ;
    case bawah :
      loc->y++ ;
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

void mulai (int u,
            int h,
            int w)
{
  int i, j ;
  ITM l ;
  
  MDE mode = awal ;
  int play = 1 ;
  int score = 0 ;
  int count = 0 ;
  
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
    papan, score, h, w, mode
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
        case 112 :
          up (
            (h % 2) ? h / 2 +
            2 : h / 2 + 1
          ) ;
          cetak ( 
            papan , score,
            h, w, pause
          ) ;
          getch () ;
          break ;
        case 27 :
          play = 0 ;
          mode = gameover ;
          break ;
      }
    }
    
    up (
      (h % 2) ? h / 2 + 2 :
      h / 2 + 1
    ) ;
    
    if (count)
    { /*Update*/
      l = jalan (
        1, &pala, papan, w
      ) ;
      
      if (l >= 1 && l <= 5)
      {
        play = 0 ;
        mode = gameover ;
      }
      else if (l == 6)
      {
        score += 10 ;
        berbuah (papan, h, w) ;
      }
      else jalan (
        0, &ekor, papan, w
      ) ;
      
      count = 0 ;
    }
    else count++ ;
    
    cetak (
      papan, score, h, w, mode
    ) ;
    Sleep (50) ; /*Delay*/
  }
  while (play) ;
  
  free (papan) ;
}

/*-=----=----=----=----=----=-*/

void uler (int u,
           int h,
           int w)
{
  inisiasi () ;
  mulai (u, h + 2, w + 2) ;
  terminasi () ;
}