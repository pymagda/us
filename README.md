# Układy sterujące - sprawozdanie z laboratorium 2

## Program 1

Celem programu jest zliczanie wciśnięć przycisku na siedmiu diodach. Jedna z osmiu diód ma cały czas migać, służy do tego metoda blink().
Wciśnięcie przycisku generuje przerwanie i wywołanie metody count().

## Program 2

Celem programu jest sterowanie intenstywnością świecenia diody poprzez wciskanie jednego z dwóch przycisków w trybie Fast PWM.
Dioda podłączona jest do pinu OC0. Przy wciśnięciu jednego z przycisków wartość przechowywana w rejestrze OCR0 jest zwiększana,
natomiast przy wciśnięciu drugiego jest zmiejszana.
