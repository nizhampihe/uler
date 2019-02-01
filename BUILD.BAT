::-=----=----=----=----=----=-::
:: BUILD.BAT                  ::
::   Program untuk mengcompile::
:: agar lebih mudah           ::
::                            ::
::        (c) 2019 NizhamPihe ::
::-=----=----=----=----=----=-::

@ECHO OFF

FOR %%I IN (%PATH%) DO (
  IF EXIST %%I\GCC.EXE (
    SET TEMU=1
  )
)
IF NOT DEFINED TEMU (
  ECHO Compiler tidak di temukan
  GOTO exit
)

::-=----=----=----=----=----=-::

FOR /R %%S IN (*.C) DO (
  IF EXIST %%~nS.O DEL %%~nS.O
  IF EXIST %%~nS.EXE DEL %%~nS.EXE
  GCC -Ofast -Wall -g -o %%~nS.O -c %%~nS.C
  IF NOT EXIST %%~nS.O (
    ECHO Program Gagal Dibuat
    GOTO exit
  )
  GCC -o %%~nS.EXE %%~nS.O -mconsole
  IF NOT EXIST %%~nS.EXE (
    ECHO Program Gagal Dibuat
    GOTO exit
  )
  DEL %%~nS.O
  FOR %%F IN (%%~nS.EXE) DO (
    ECHO Program Berhasil Dibuat
    ECHO Ukuran = %%~zF byte
  )
)

::-=----=----=----=----=----=-::

:exit