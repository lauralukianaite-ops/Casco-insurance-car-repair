# Kasko draudimo / autoserviso simuliacija (3-as laboratorinis)

Simuliuojamas autoservisas su dviejų tipų klientais: VIP (frančizė A, servisas gauna A1 priedo) ir paprastais (frančizė B = A - A1). VIP klientai aptarnaujami pirmiausiai, prireikus dirbami viršvalandžiai (mokant darbuotojams dvigubai). Modeliuojama kuri strategija servisui naudingesnė — turėti bendradarbiavimo sutartis ar dirbti be jų.

## Panaudoti ADT

Darbe panaudoti du abstraktūs duomenų tipai:

- **Prioritetinė eilė** (`pqueue`) - paimta iš dėstytojo puslapio (1dogr2191). Rasta defektų: 0;
- **Ilgas sveikasis skaičius** (`BigInt`) — paimta iš dėstytojo puslapio (1aima2290). Rasta defektų: 0.

## Bendravimas ir bendradarbiavimas



## Algoritmo aprašymas

Kiekviena simuliacijos iteracija atitinka vieną valandą. Kiekvienos valandos eigoje:

1. Visiems `K` darbuotojams išskaičiuojamas valandinis atlyginimas `U`, sumažinamas likęs darbo laikas.
2. Atsitiktiniu skaičiumi nustatomas kliento tipas — VIP (tikimybė `T1`), paprastas (tikimybė `T2`), arba klientų nėra.
3. Automobilio taisymo laikas `TR` generuojamas atsitiktinai intervale `[1, 5*K]`.
4. VIP klientui — pelnas padidinamas `A + A1`, jei taisymas viršija 8 val., skaičiuojami viršvalandžiai (`2*U` už kiekvieną papildomą valandą). Ieškomas laisvas darbuotojas — jei nerastas, automobilis dedamas į eilę su prioritetu `0`.
5. Paprastam klientui — pelnas padidinamas `A - A1`, automobilis dedamas į eilę su prioritetu `1`.
6. Laisvi darbuotojai paima automobilius iš prioritetinės eilės (VIP visada pirmiau).

## Programos naudojimas

### Sukompiliuoti:
```cmd
make
```

### Paleisti su parametrų failu:
```cmd
simulation.exe params.txt -rnd 50
```

### Paleisti be parametrų failo (automatiškai ieško `simulation.cfg`):
```cmd
simulation.exe
```

Rezultatai išsaugomi į `result1.txt` ir `result2.txt` paleidus `Go.cmd`.

## Pastabos

- `BigInt` naudojamas pelno skaičiavimui, kad būtų išvengta sveikųjų skaičių perpildymo.
- **Darbuotojų skaičiaus įtaka:** Pastebėta, kad esant mažam darbuotojų skaičiui (K), VIP klientų viršvalandžiai mažina pelną, nes jų aptarnavimo laikas (iki 5*K valandų) dažnai viršija standartinę 8 valandų darbo dieną.
- **Sutarčių nauda:** Bendradarbiavimo sutartys (VIP) yra pelningos tik tada, kai A1 (priedas) yra didesnis už potencialias išlaidas viršvalandžiams. Jei vidutinis taisymo laikas ilgas, servisas patiria nuostolį dėl dvigubai didesnių algų darbuotojams už kiekvieną papildomą darbo valandą.
- **Eilės efektyvumas:** Prioritetinė eilė reikalinga, kad paprasti klientai (prioritetas 1) būtų aptarnaujami tik tada, kai nėra laukiančių VIP klientų, tačiau VIP klientai su prioritetu 0 vis tiek gali laukti, jei visi darbuotojai užimti.
