DECLARE FUNCTION HilfeAllgemein$ (hilfeseite%)
DECLARE SUB speichern (m%)
DECLARE SUB spalteplus ()
DECLARE SUB spalteminus ()
DECLARE FUNCTION tonplus$ (t$)
DECLARE FUNCTION tonminus$ (t$)
DECLARE SUB tona (t$)
DECLARE SUB vorz ()
DECLARE SUB lw (l$)
DEFINT A-Z
DECLARE FUNCTION xmin% (x%, y%)
DECLARE FUNCTION ll$ (z%, l%)
DECLARE SUB codieren ()
DECLARE SUB decodieren ()
DECLARE SUB save ()
DECLARE SUB load ()
DECLARE SUB hals2 (y%, farbe%)
DECLARE SUB hals1 (y%, farbe%)
DECLARE SUB note (farbe%)
DECLARE SUB spielen ()
DECLARE SUB startinit ()
DECLARE SUB seite (s)
DECLARE SUB linien (z, farbe)
DEFINT A-Z
CONST xmax = 639, ymax = 479'349
CONST c = 1, d = 2, e = 3, f = 4, g = 5, a = 6, b = 7, liedende = 0, zeilenende = -2, pause = -1, null = -3
CONST nschluessel$ = "hu4euer3f2dfd2gdg3l4h3u4eu2eue2ue3ueue2ueu2h1l3dgd16fd13gl3hu2efdlu"
CONST halsoben$ = "f3dfd3lu3huh3", halsunten$ = "h3uhu3rd3fdf3"
CONST entwer$ = "u5r2d3lru5"
CONST linienabstand = 6, zeilenabstand = 7 * linienabstand, notenabstand = 40, radius = linienabstand / 2
CONST anzlinien% = ymax / zeilenabstand - 1
CONST anznoten% = xmax / notenabstand - 1
CONST halslaenge = 3 * linienabstand
CONST linienfarbe = 15, notenfarbe = 15, aktnotenfarbe = 4, vorzeichen = 8
CONST anztonarten = 22
CONST xton = 1, yton = 30
CONST seiten = 5
CONST bildschirmmodus = 12, lastzeile = 30, videogroesse = 38400
COMMON SHARED nwert, nlaenge, ntempo, noktave, npunkte, nkreuz, nbe, nart$, nentw, druckmodus, se
COMMON SHARED zeile, spalte, kreuz$, be$
COMMON SHARED laufwerk$, pfad$, ton$
DIM SHARED wert(anzlinien% * seiten, anznoten%), laenge(anzlinien% * seiten, anznoten%), tempo(anzlinien% * seiten, anznoten%)
DIM SHARED oktave(anzlinien% * seiten, anznoten%), kreuz(anzlinien% * seiten, anznoten%), be(anzlinien% * seiten, anznoten%)
DIM SHARED art$(anzlinien% * seiten, anznoten%), punkt(anzlinien% * seiten, anznoten%), entw(anzlinien% * seiten, anznoten%)
DIM SHARED vk(-3 TO 7), vb(-3 TO 7)
DIM SHARED musik$(10), zahl$(9)
DIM SHARED tonart$(25)
DATA "C-Dur","G-Dur","D-Dur","A-Dur","E-Dur","H-Dur","F-Dur","B-Dur","Es-Dur","As-Dur","Des-Dur"
DATA "a-Moll","e-Moll","h-Moll","fis-Moll","cis-Moll","gis-Moll","d-Moll","g-Moll","c-Moll","f-Moll","b-Moll"
lwtemp$ = ENVIRON$("TEMP")
IF LEN(lwtemp$) > 2 THEN
        laufwerk$ = LEFT$(lwtemp$, 2): pfad$ = MID$(lwtemp$, 3)
ELSE
        laufwerk$ = "C:": pfad$ = ""
END IF
zahl$(0) = "brhu4er2fd4glbr4"
zahl$(1) = "ru6gfd4rbr2"
zahl$(2) = "e4uhl2ger2fdg4r4br2"
zahl$(3) = "r3euhlreuhl3br6bd6"
zahl$(4) = "br3u6g3dr4bd2br2"
zahl$(5) = "bufr2euhl3u3r4br2bd6"
zahl$(6) = "buu3e2lrg2dr3fdgl2br5"
zahl$(7) = "br2u2e2u2l4br6bd6"
zahl$(8) = "brr2euhl2huer2fdgl2gdfr2br3"
zahl$(9) = "brre2u3hl2gdfr3bd3br2"
kreuz$ = "d" + MID$(STR$(linienabstand + 6), 2) + "u2l2r2ur" + MID$(STR$(linienabstand), 2) + "ur2l2u" + MID$(STR$(linienabstand), 2) + "d2l2r2dl" + MID$(STR$(linienabstand), 2) + "dr2"
be$ = "d" + MID$(STR$(linienabstand + 6), 2) + "r2euhl2"
startinit
tim$ = TIME$: LOCATE lastzeile, 1: PRINT TIME$;
LOCATE lastzeile, 20: PRINT "h = Hilfe  ESC = Beenden  s = Speichern  f = Laden";
DO
        tim2$ = TIME$: IF tim$ <> tim2$ THEN LOCATE lastzeile, 1: PRINT tim2$; : tim$ = tim2$
        z$ = INKEY$
        SELECT CASE z$
        CASE ""
        CASE CHR$(27)
                speichern 1
                END
        CASE "t"
                save
                t = 0
                DO
                        LOCATE 1, 20
                        INPUT "Tempo:", t
                        LOCATE 1, 20
                        PRINT SPACE$(20);
                LOOP UNTIL t >= 32 AND t <= 255
                note 0
                ntempo = t
                note aktnotenfarbe
                linien zeile, linienfarbe
        CASE "o", "O"
                'Optionen setzen
                l$ = laufwerk$
                lw l$
                DO
                        zz$ = INKEY$
                        SELECT CASE zz$
                        CASE "a" TO "z"
                                l$ = CHR$(ASC(zz$) - 32) + ":"
                                lw l$
                        CASE "A" TO "Z"
                                l$ = zz$ + ":"
                                lw l$
                        CASE CHR$(13)
                                laufwerk$ = l$
                                EXIT DO
                        CASE CHR$(27)
                                EXIT DO
                        CASE CHR$(0) + CHR$(77)
                                l = ASC(l$)
                                l = l + 1
                                IF l = ASC("Z") + 1 THEN l = ASC("A")
                                l$ = CHR$(l) + ":"
                                lw l$
                        CASE CHR$(0) + CHR$(75)
                                l = ASC(l$)
                                l = l - 1
                                IF l = ASC("A") - 1 THEN l = ASC("Z")
                                l$ = CHR$(l) + ":"
                                lw l$
                        END SELECT
                LOOP
                LOCATE 1, 1
                PRINT SPACE$(80)
                LOCATE 1, 20
                PRINT "Pfad:"; pfad$;
                LOCATE 1, 50
                INPUT "Neuer Pfad:", p$
                IF p$ <> SPACE$(LEN(p$)) THEN pfad$ = p$
                LOCATE 1, 1
                PRINT SPACE$(80);
        CASE "a"
                'Tonart setzen
                altseite = se
                t$ = ton$
                tona t$
                DO
                        zz$ = INKEY$
                        SELECT CASE zz$
                        CASE CHR$(13)
                                EXIT DO
                        CASE CHR$(27)
                                EXIT DO
                        CASE CHR$(0) + CHR$(77)
                                t$ = tonplus$(t$)
                                tona t$
                        CASE CHR$(0) + CHR$(75)
                                t$ = tonminus$(t$)
                                tona t$
                        END SELECT
                LOOP
                FOR j = 0 TO seiten - 1
                        seite j
                        FOR i = 1 TO anzlinien%
                                linien j * anzlinien% + i, 0
                        NEXT
                NEXT
                IF zz$ = CHR$(13) THEN
                        ton$ = t$
                        vorz
                END IF
                FOR j = 0 TO seiten - 1
                        seite j
                        FOR i = 1 TO anzlinien%
                                linien j * anzlinien% + i, linienfarbe
                        NEXT
                NEXT
                seite altseite
                note aktnotenfarbe
        CASE CHR$(13), CHR$(0) + CHR$(&H4D)
                'Note bestÑtigen, nach rechts
                note notenfarbe
                save
                spalteplus
                load
                IF nwert = liedende THEN
                        nwert = a
                        nlaenge = 4
                        ntempo = 0
                        noktave = 3
                        nkreuz = 0
                        nbe = 0
                        nart$ = ""
                END IF
                note aktnotenfarbe
        CASE "0"
                'Null-Note
                note 0
                nwert = null
                linien zeile, linienfarbe
                note aktnotenfarbe
        CASE ","
                'Entwertung des Vorzeichens
                note 0
                IF nentw = 1 THEN
                        nentw = 0
                ELSE
                        IF nkreuz + nbe + vb(nwert) + vk(nwert) > 0 THEN
                                nkreuz = 0
                                nbe = 0
                                IF nkreuz + nbe = 0 THEN nentw = 1
                        END IF
                END IF
                linien zeile, linienfarbe
                note aktnotenfarbe
        CASE CHR$(0) + CHR$(82)
                'EinfÅgen
                save
                note 0
                linien zeile, linienfarbe
                altspalte = spalte: altzeile = zeile: altseite = se
                seite seiten - 1
                FOR i = seiten * anzlinien% TO altzeile + 1 STEP -1
                        FOR j = anznoten% TO 1 STEP -1
                                zeile = i
                                spalte = j
                                sei = (zeile - 1) \ anzlinien%
                                seite sei
                                'IF zeile > anzlinien% THEN seite 1
                                'IF zeile <= anzlinien% THEN seite 0
                                note 0
                                spalteminus
                                load
                                spalteplus
                                save
                                note notenfarbe
                        NEXT
                NEXT
                i = altzeile
                FOR j = anznoten% TO altspalte + 1 STEP -1
                        zeile = i
                        spalte = j
                        sei = (zeile - 1) \ anzlinien%
                        seite sei
                        'IF zeile > anzlinien% AND se = 0 THEN seite 1
                        'IF zeile <= anzlinien% AND se = 1 THEN seite 0
                        note 0
                        spalteminus
                        load
                        spalteplus
                        save
                        note notenfarbe
                NEXT
                spalte = altspalte: zeile = altzeile
                'IF se <> altseite THEN seite altseite
                nwert = a
                nlaenge = 4
                ntempo = 0
                noktave = 3
                nkreuz = 0
                nbe = 0
                nart$ = ""
                npunkte = 0
                nentw = 0
                save
                note aktnotenfarbe
                FOR j = 0 TO seiten - 1
                        seite j
                        FOR i = 1 TO anzlinien%
                                linien j * anzlinien% + i, linienfarbe
                        NEXT
                NEXT
                seite altseite
                note aktnotenfarbe
        CASE CHR$(0) + CHR$(83)
                'Lîschen
                altzeile = zeile: altspalte = spalte: altseite = se
                DO
                        note 0
                        spalteplus
                        load
                        spalteminus
                        save
                        note notenfarbe
                        spalteplus
                LOOP UNTIL nwert = liedende
                spalte = altspalte: zeile = altzeile
                seite altseite
                load
                IF nwert = liedende THEN
                        IF spalte = 1 AND zeile = 1 THEN
                                nwert = a
                                nlaenge = 4
                                ntempo = 0
                                noktave = 3
                                nkreuz = 0
                                nbe = 0
                                nart$ = ""
                                nentw = 0
                        ELSE
                                spalteminus
                                load
                        END IF
                END IF
                FOR j = 0 TO seiten - 1
                        seite j
                        FOR i = 1 TO anzlinien%
                                linien j * anzlinien% + i, linienfarbe
                        NEXT
                NEXT
                seite altseite
                note aktnotenfarbe
        CASE CHR$(8), CHR$(0) + CHR$(&H4B)
                'nach links
                note notenfarbe
                save
                spalteminus
                load
                note aktnotenfarbe
        CASE CHR$(0) + CHR$(80)
                'nach unten
                note notenfarbe
                save
                zeile = zeile + 1
                'load
                IF nwert = liedende OR zeile > seiten * anzlinien% THEN
                        zeile = zeile - 1
                END IF
                load
                IF nwert = liedende THEN zeile = zeile - 1
                sei = (zeile - 1) \ anzlinien%
                seite sei
                'IF zeile > anzlinien% THEN seite 1
                load
                note aktnotenfarbe
        CASE CHR$(0) + CHR$(72)
                'nach oben
                note notenfarbe
                save
                IF zeile > 1 THEN zeile = zeile - 1
                'IF zeile <= anzlinien% AND se = 1 THEN seite 0
                sei = (zeile - 1) \ anzlinien%
                seite sei
                load
                note aktnotenfarbe
        CASE "+"
                'Note hîher
                IF nwert >= 0 THEN
                        note 0
                        nentw = 0
                        nwert = nwert + 1
                        IF nwert = b + 1 THEN
                                IF noktave < 6 THEN
                                        nwert = c
                                        noktave = noktave + 1
                                ELSE
                                        nwert = b
                                        noktave = 6
                                END IF
                        END IF
                        IF nwert = b OR nwert = e THEN
                                nkreuz = 0
                        ELSEIF nwert = c OR nwert = f THEN
                                nbe = 0
                        END IF
                        linien zeile, linienfarbe
                        note aktnotenfarbe
                END IF
        CASE "-"
                IF nwert >= 0 THEN
                        'Note tiefer
                        note 0
                        nentw = 0
                        nwert = nwert - 1
                        IF nwert = c - 1 THEN
                                IF noktave > 0 THEN
                                        nwert = b
                                        noktave = noktave - 1
                                ELSE
                                        nwert = c
                                        noktave = 0
                                END IF
                        END IF
                        IF nwert = b OR nwert = e THEN
                                nkreuz = 0
                        ELSEIF nwert = c OR nwert = f THEN
                                nbe = 0
                        END IF
                        linien zeile, linienfarbe
                        note aktnotenfarbe
                END IF
        CASE "<", ">"
                'Note eine Oktave hîher/tiefer
                IF nwert >= 0 THEN
                        note 0
                        IF z$ = ">" AND noktave < 6 THEN
                                noktave = noktave + 1
                                nentw = 0
                        ELSEIF z$ = "<" AND noktave > 0 THEN
                                noktave = noktave - 1
                                nentw = 0
                        END IF
                        linien zeile, linienfarbe
                        note aktnotenfarbe
                END IF
        CASE "n"
                'Umwandlung Pause in Note
                IF nwert <= 0 THEN
                        note 0
                        nwert = a
                        nlaenge = 4
                        ntempo = 0
                        noktave = 3
                        nkreuz = 0
                        nbe = 0
                        nart$ = ""
                        npunkte = 0
                        nentw = 0
                        linien zeile, linienfarbe
                        note aktnotenfarbe
                END IF
        CASE "p"
                'Umwandlung in Pause
                IF nwert <> pause THEN
                        note 0
                        nwert = pause
                        nlaenge = 4
                        ntempo = 0
                        noktave = 3
                        nkreuz = 0
                        nbe = 0
                        nart$ = ""
                        npunkte = 0
                        nentw = 0
                        linien zeile, linienfarbe
                        note aktnotenfarbe
                END IF
        CASE "m"
                'Spielart verÑndern
                save
                DO
                        zz$ = INKEY$
                LOOP UNTIL zz$ = "s" OR zz$ = "n" OR zz$ = "l"
                note 0
                SELECT CASE zz$
                CASE "s"
                        nart$ = "MS"
                CASE "n"
                        nart$ = "MN"
                CASE "l"
                        nart$ = "ML"
                END SELECT
                save
                note aktnotenfarbe
                linien zeile, linienfarbe
        CASE "A" TO "G"
                'Noten A bis G
                IF nwert >= 0 THEN
                        note 0
                        nentw = 0
                        SELECT CASE z$
                        CASE "A"
                                nwert = a
                        CASE "B"
                                nwert = b
                        CASE "C"
                                nwert = c
                        CASE "D"
                                nwert = d
                        CASE "E"
                                nwert = e
                        CASE "F"
                                nwert = f
                        CASE "G"
                                nwert = g
                        END SELECT
                        IF nwert = b OR nwert = e THEN
                                nkreuz = 0
                        ELSEIF nwert = c OR nwert = f THEN
                                nbe = 0
                        END IF
                        linien zeile, linienfarbe
                        note aktnotenfarbe
                END IF
        CASE "l"
                'Note kÅrzer
                note 0
                IF nlaenge < 64 THEN nlaenge = nlaenge * 2
                linien zeile, linienfarbe
                note aktnotenfarbe
        CASE "L"
                'Note lÑnger
                note 0
                IF nlaenge > 1 THEN nlaenge = nlaenge / 2
                linien zeile, linienfarbe
                note aktnotenfarbe
        CASE CHR$(12)   '^L
                'Note mit besonderer LÑnge (au·er Standard)
                DO
                        LOCATE 1, 20
                        INPUT "Extra-LÑnge:", l
                        LOCATE 1, 20
                        PRINT SPACE$(25);
                LOOP UNTIL l >= 1 AND l <= 64
                note 0
                nlaenge = l
                note aktnotenfarbe
                linien zeile, linienfarbe
        CASE "."
                note 0
                IF npunkte < 3 THEN npunkte = npunkte + 1
                linien zeile, linienfarbe
                note aktnotenfarbe
        CASE ":"
                note 0
                IF npunkte > 0 THEN npunkte = npunkte - 1
                linien zeile, linienfarbe
                note aktnotenfarbe
        CASE "#"
                note 0
                nentw = 0
                nkreuz = 1 - nkreuz
                IF nwert = b OR nwert = e OR nwert <= 0 OR vk(nwert) = 1 THEN
                        nkreuz = 0
                ELSE
                        nbe = 0
                END IF
                linien zeile, linienfarbe
                note aktnotenfarbe
        CASE "b"
                note 0
                nentw = 0
                nbe = 1 - nbe
                IF nwert = c OR nwert = f OR nwert <= 0 OR vb(nwert) = 1 THEN
                        nbe = 0
                ELSE
                        nkreuz = 0
                END IF
                linien zeile, linienfarbe
                note aktnotenfarbe
        CASE "s"
                speichern 0
        CASE "f"
                'seite 1
                'CLS
                SCREEN 0: SCREEN bildschirmmodus: OUT 968, 0: OUT 969, 0: OUT 969, 0: OUT 969, 63'PALETTE 0, 1
                seite 0
                CLS
                VIEW PRINT 2 TO 25
                FILES laufwerk$ + pfad$ + "\" + "*.mus"
                VIEW PRINT
                LOCATE 1, 1
                INPUT "Dateiname:", datei$
                IF INSTR(datei$, ".") = 0 THEN
                        datei$ = LEFT$(datei$, 8) + ".mus"
                END IF
                LOCATE 1, 1
                PRINT SPACE$(30);
                OPEN laufwerk$ + pfad$ + "\" + datei$ FOR INPUT AS #1
                INPUT #1, musik$(0)
                FOR i = 1 TO 10
                        LINE INPUT #1, musik$(i)
                NEXT
                CLOSE #1
                vorz
                decodieren
                'FOR i = 1 TO seiten * anzlinien%
                        'linien i, linienfarbe
                'NEXT
        CASE "y"
                'Spielen der Musik
                save
                codieren
                spielen
        CASE "h"
                'Hilfe
                DEF SEG = &HA000: BSAVE "Hilfe", 0, videogroesse: DEF SEG
                hilfeseite = 0
                DO
                        zzz$ = HilfeAllgemein(hilfeseite)
                        hilfeseite = hilfeseite + 1
                LOOP UNTIL zzz$ = CHR$(27)
                DEF SEG = &HA000: BLOAD "Hilfe", 0: DEF SEG
                note aktnotenfarbe
        END SELECT
LOOP

SUB codieren
FOR i = 1 TO 10
        musik$(i) = ""
NEXT
u = 1
la = -10
o = oktave(1, 1): t = tempo(1, 1): ar$ = art$(1, 1)
IF ar$ = "" THEN ar$ = "MN"
IF t = 0 THEN t = 120
musik$(u) = "MB" + "T" + MID$(STR$(t), 2) + ar$ + "O" + MID$(STR$(o), 2)
FOR i = 1 TO seiten * anzlinien%
        FOR j = 1 TO anznoten%
                IF LEN(musik$(u)) > 230 THEN u = u + 1
                SELECT CASE wert(i, j)
                CASE null
                        'musik$(u) = musik$(u) + "T255A64T" + MID$(STR$(t), 2)
                CASE liedende
                CASE zeilenende
                        EXIT FOR
                CASE pause
                        IF tempo(i, j) <> 0 THEN
                                t = tempo(i, j)
                                musik$(u) = musik$(u) + "T" + MID$(STR$(t), 2)
                        END IF
                        la = -1
                        IF art$(i, j) <> "" THEN
                                ar$ = art$(i, j)
                                musik$(u) = musik$(u) + ar$
                        END IF
                        musik$(u) = musik$(u) + "P" + MID$(STR$(laenge(i, j)), 2)
                        FOR k = 1 TO punkt(i, j)
                                musik$(u) = musik$(u) + "."
                        NEXT
                CASE c TO b
                        'Noten
                        IF tempo(i, j) <> 0 THEN
                                t = tempo(i, j)
                                musik$(u) = musik$(u) + "T" + MID$(STR$(t), 2)
                        END IF
                        IF oktave(i, j) <> o THEN
                                o = oktave(i, j)
                                musik$(u) = musik$(u) + "O" + MID$(STR$(o), 2)
                        END IF
                        IF laenge(i, j) <> la THEN
                                la = laenge(i, j)
                                musik$(u) = musik$(u) + "l" + MID$(STR$(la), 2)
                        END IF
                        IF art$(i, j) <> "" THEN
                                ar$ = art$(i, j)
                                musik$(u) = musik$(u) + ar$
                        END IF
                        SELECT CASE wert(i, j)
                        CASE a
                                musik$(u) = musik$(u) + "a"
                        CASE b
                                musik$(u) = musik$(u) + "b"
                        CASE c
                                musik$(u) = musik$(u) + "c"
                        CASE d
                                musik$(u) = musik$(u) + "d"
                        CASE e
                                musik$(u) = musik$(u) + "e"
                        CASE f
                                musik$(u) = musik$(u) + "f"
                        CASE g
                                musik$(u) = musik$(u) + "g"
                        END SELECT
                        IF kreuz(i, j) = 1 THEN
                                musik$(u) = musik$(u) + "#"
                        ELSEIF be(i, j) = 1 THEN musik$(u) = musik$(u) + "-"
                        ELSEIF wert(i, j) >= c AND wert(i, j) <= b AND entw(i, j) = 0 THEN
                                IF vk(wert(i, j)) = 1 THEN musik$(u) = musik$(u) + "#"
                                IF vb(wert(i, j)) = 1 THEN musik$(u) = musik$(u) + "-"
                        END IF
                        FOR k = 1 TO punkt(i, j)
                                musik$(u) = musik$(u) + "."
                        NEXT
                END SELECT
        NEXT
NEXT
END SUB

SUB decodieren
CLS
startinit
ton$ = musik$(0)
vorz
note 0
FOR j = 0 TO seiten - 1
        seite j
        FOR i = 1 TO anzlinien%
                linien i + anzlinien% * j, linienfarbe
        NEXT
NEXT
seite 0
FOR i = 1 TO anzlinien% * seiten
        'linien i, linienfarbe
        FOR j = 1 TO anznoten%
                wert(i, j) = liedende
                laenge(i, j) = 4
                tempo(i, j) = 0
                oktave(i, j) = 3
                kreuz(i, j) = 0
                be(i, j) = 0
                art$(i, j) = ""
                punkt(i, j) = 0
                entw(i, j) = 0
        NEXT
NEXT
FOR u = 1 TO 10
        z = 1
        m$ = musik$(u)
        DO
                IF z > LEN(m$) THEN EXIT DO
                x = 300
                x = xmin(x, INSTR(MID$(m$, z), "a"))
                x = xmin(x, INSTR(MID$(m$, z), "b"))
                x = xmin(x, INSTR(MID$(m$, z), "c"))
                x = xmin(x, INSTR(MID$(m$, z), "d"))
                x = xmin(x, INSTR(MID$(m$, z), "e"))
                x = xmin(x, INSTR(MID$(m$, z), "f"))
                x = xmin(x, INSTR(MID$(m$, z), "g"))
                x = xmin(x, INSTR(MID$(m$, z), "P"))
                p = INSTR(MID$(m$, z), "P")
                IF p <> 0 AND x = p THEN
                        z0$ = MID$(m$, z + p, 1)
                        z1$ = MID$(m$, z + p + 1, 1)
                        z2$ = MID$(m$, z + p + 2, 1)
                        IF z0$ >= "0" AND z0$ <= "9" THEN
                                IF z1$ >= "0" AND z1$ <= "9" THEN
                                        IF z2$ >= "0" AND z2$ <= "9" THEN
                                                x = x + 3
                                        ELSE
                                                x = x + 2
                                        END IF
                                ELSE
                                        x = x + 1
                                END IF
                        END IF
                END IF
                DO
                        IF MID$(m$, z + x, 1) = "." OR MID$(m$, z + x, 1) = "#" OR MID$(m$, z + x, 1) = "-" THEN
                                x = x + 1
                        ELSE
                                EXIT DO
                        END IF
                LOOP
                IF x = 0 THEN EXIT DO
                x$ = MID$(m$, z, x)
                'LPRINT x$ + ";"
                'x$ enthÑlt alle Informationen Åber die Note (zeile,spalte)
                'Hier Decodierung einfÅgen
                IF LEFT$(x$, 7) = "T255A64" THEN
                        wert(zeile, spalte) = null
                ELSE
                        IF INSTR(x$, "a") <> 0 THEN wert(zeile, spalte) = a
                        IF INSTR(x$, "b") <> 0 THEN wert(zeile, spalte) = b
                        IF INSTR(x$, "c") <> 0 THEN wert(zeile, spalte) = c
                        IF INSTR(x$, "d") <> 0 THEN wert(zeile, spalte) = d
                        IF INSTR(x$, "e") <> 0 THEN wert(zeile, spalte) = e
                        IF INSTR(x$, "f") <> 0 THEN wert(zeile, spalte) = f
                        IF INSTR(x$, "g") <> 0 THEN wert(zeile, spalte) = g
                        IF INSTR(x$, "P") <> 0 THEN wert(zeile, spalte) = pause
                        w = wert(zeile, spalte)
                        IF w >= c AND w <= b THEN
                                IF INSTR(x$, "#") <> 0 AND vk(w) = 0 THEN
                                        kreuz(zeile, spalte) = 1
                                ELSE
                                        kreuz(zeile, spalte) = 0
                                END IF
                                IF INSTR(x$, "-") <> 0 AND vb(w) = 0 THEN
                                        be(zeile, spalte) = 1
                                ELSE
                                        be(zeile, spalte) = 0
                                END IF
                                IF INSTR(x$, "-") = 0 AND INSTR(x$, "#") = 0 AND vk(w) = 1 THEN
                                        entw(zeile, spalte) = 1
                                END IF
                                IF INSTR(x$, "-") = 0 AND INSTR(x$, "-") = 0 AND vb(w) = 1 THEN
                                        entw(zeile, spalte) = 1
                                END IF
                        END IF
                        IF INSTR(x$, "O") <> 0 THEN
                                noktave = VAL(MID$(x$, INSTR(x$, "O") + 1, 1))
                                oktave(zeile, spalte) = noktave
                        ELSE
                                oktave(zeile, spalte) = noktave
                        END IF
                        IF INSTR(x$, "MN") <> 0 THEN
                                art$(zeile, spalte) = "MN"
                        ELSEIF INSTR(x$, "ML") <> 0 THEN
                                art$(zeile, spalte) = "ML"
                        ELSEIF INSTR(x$, "MS") <> 0 THEN
                                art$(zeile, spalte) = "MS"
                        ELSE
                                art$(zeile, spalte) = ""
                        END IF
                        IF INSTR(x$, "...") <> 0 THEN
                                punkt(zeile, spalte) = 3
                        ELSEIF INSTR(x$, "..") <> 0 THEN
                                punkt(zeile, spalte) = 2
                        ELSEIF INSTR(x$, ".") <> 0 THEN
                                punkt(zeile, spalte) = 1
                        ELSE
                                punkt(zeile, spalte) = 0
                        END IF
                        IF w = pause THEN
                                p = INSTR(x$, "P") + 1
                                z3$ = MID$(x$, p, 3)
                                z2$ = MID$(x$, p, 2)
                                z1$ = MID$(x$, p, 1)
                                IF VAL(z3$) <> 0 THEN
                                        laenge(zeile, spalte) = VAL(z3$)
                                ELSEIF VAL(z2$) <> 0 THEN
                                        laenge(zeile, spalte) = VAL(z2$)
                                ELSEIF VAL(z1$) <> 0 THEN
                                        laenge(zeile, spalte) = VAL(z1$)
                                END IF
                        END IF
                        IF INSTR(x$, "l") <> 0 THEN
                                p = INSTR(x$, "l") + 1
                                z3$ = MID$(x$, p, 3)
                                z2$ = MID$(x$, p, 2)
                                z1$ = MID$(x$, p, 1)
                                IF VAL(z3$) <> 0 THEN
                                        la = VAL(z3$)
                                        laenge(zeile, spalte) = la
                                ELSEIF VAL(z2$) <> 0 THEN
                                        la = VAL(z2$)
                                        laenge(zeile, spalte) = la
                                ELSEIF VAL(z1$) <> 0 THEN
                                        la = VAL(z1$)
                                        laenge(zeile, spalte) = la
                                ELSE
                                        laenge(zeile, spalte) = la
                                END IF
                        ELSEIF w <> pause THEN
                                laenge(zeile, spalte) = la
                        END IF
                        IF INSTR(x$, "T") <> 0 THEN
                                p = INSTR(x$, "T") + 1
                                z3$ = MID$(x$, p, 3)
                                z2$ = MID$(x$, p, 2)
                                z1$ = MID$(x$, p, 1)
                                IF VAL(z3$) <> 0 THEN
                                        tempo(zeile, spalte) = VAL(z3$)
                                ELSEIF VAL(z2$) <> 0 THEN
                                        tempo(zeile, spalte) = VAL(z2$)
                                ELSEIF VAL(z1$) <> 0 THEN
                                        tempo(zeile, spalte) = VAL(z1$)
                                END IF
                        END IF
                END IF
                load
                note notenfarbe
                spalteplus
                z = z + x
        LOOP
NEXT
zeile = 1: spalte = 1
seite 0
load
note aktnotenfarbe
END SUB

SUB hals1 (y, farbe)
PSET (spalte * notenabstand + radius + 2, y), farbe
DRAW halsoben$
END SUB

SUB hals2 (y, farbe)
PSET (spalte * notenabstand - radius - 2, y), farbe
DRAW halsunten$
END SUB

FUNCTION HilfeAllgemein$ (hilfeseite%)
    
        SELECT CASE hilfeseite%
        CASE 0
                CLS
                LOCATE 1, 1: PRINT "Hilfe zum Musikprogramm (Startseite)";
                LOCATE 2, 1: PRINT "************************************************************"
                LOCATE 3, 1: PRINT "Noten: A-G bzw. +/- fÅr hîher/tiefer, bestÑtigen mit ENTER"
                LOCATE 4, 1: PRINT "Sonderzeichen: . # b :(Punkt entfernen)"
                LOCATE 5, 1: PRINT "Weitere Tasten:"
                LOCATE 6, 1: PRINT "y - Abspielen"
                LOCATE 7, 1: PRINT "f - Laden einer gespeicherten Datei"
                LOCATE 8, 1: PRINT "s - Speichern"
                LOCATE 9, 1: PRINT "t - Tempo"
                LOCATE 10, 1: PRINT "o - Optionen (Laufwerk, Pfad usw.)"
                LOCATE 11, 1: PRINT "a - Tonart setzen"
                LOCATE 12, 1: PRINT "0 - 'Null-Note' (keine Wirkung)"
                LOCATE 13, 1: PRINT ", - Entwertung des Vorzeichens # bzw. b"
                LOCATE 14, 1: PRINT "Einf,Entf - Note einfÅgen/entfernen"
                LOCATE 15, 1: PRINT "Pfeiltasten - Bewegen im MusikstÅck"
                LOCATE 16, 1: PRINT "n - Pause in Note umwandeln"
                LOCATE 17, 1: PRINT "p - Note in Pause umwandeln"
                LOCATE 18, 1: PRINT "ml/ms/mn - Spielart Ñndern (ms=STACCATO, mn=NORMAL, ml=LEGATO"
                LOCATE 19, 1: PRINT "l/L - Note kÅrzer/lÑnger"
                LOCATE 20, 1: PRINT "^L - Note mit besonderer LÑnge (au·er Standard)"
                LOCATE 21, 1: PRINT
                LOCATE 22, 1: PRINT "DrÅcken Sie ESC zur RÅckkehr zum Programm"
                LOCATE 23, 1: PRINT "DrÅcken Sie eine beliebige fÅr die nÑchste Seite"
        CASE 1
                CLS
                LOCATE 1, 1: PRINT "Hilfe zum Musikprogramm (Seite 1)";
                LOCATE 2, 1: PRINT "************************************************************"
                LOCATE 3, 1: PRINT "Um eine Note zu setzen, betÑtigen Sie die '+'-"
                LOCATE 4, 1: PRINT "und '-'-Tasten, bis sich die Note an der richtigen"
                LOCATE 5, 1: PRINT "Position befindet."
                LOCATE 6, 1: PRINT "Sie kînnen auch 'A' bis 'G' eingeben, um eine Note direkt"
                LOCATE 7, 1: PRINT "anzuwÑhlen, die aktuelle Oktave wird dabei nicht geÑndert."
                LOCATE 8, 1: PRINT
                LOCATE 9, 1: PRINT "FÅr die NotenlÑngen stehen folgende Tasten zur VerfÅgung:"
                LOCATE 10, 1: PRINT "  l - Note kÅrzer spielen"
                LOCATE 11, 1: PRINT "  L - Note lÑnger spielen"
                LOCATE 12, 1: PRINT "  . - Note Åber 3/2 der Dauer spielen (zwei Punkte: 9/4 usw.)"
                LOCATE 13, 1: PRINT "  : - Einen gesetzten Punkt wieder entfernen"
                LOCATE 14, 1: PRINT "  Ctrl+L - Spezielle NotenlÑnge (manuell einzugeben)"
                LOCATE 15, 1: PRINT
                LOCATE 16, 1: PRINT "Spezielle Zeichen:"
                LOCATE 17, 1: PRINT "  # - Note einen Halbton hîher spielen"
                LOCATE 18, 1: PRINT "  b - Note einen Halbton niedriger spielen"
                LOCATE 19, 1: PRINT "  , - Ein impliziter Kreuz oder 'b' durch die spezifizierte Tonart aufheben"
                LOCATE 20, 1: PRINT
                LOCATE 21, 1: PRINT
                LOCATE 22, 1: PRINT "DrÅcken Sie ESC zur RÅckkehr zum Programm"
                LOCATE 23, 1: PRINT "DrÅcken Sie eine beliebige fÅr die nÑchste Seite"
        CASE 2
                CLS
                LOCATE 1, 1: PRINT "Hilfe zum Musikprogramm (Seite 2)";
                LOCATE 2, 1: PRINT "************************************************************"
                LOCATE 3, 1: PRINT "Eine Pause erzeugen Sie durch die Taste 'P'."
                LOCATE 4, 1: PRINT "Die LÑnge einer Pause wird wie bei einer Note bestimmt."
                LOCATE 5, 1: PRINT "Es besteht auch hier die Mîglichkeit, die Dauer durch AnfÅgen eines"
                LOCATE 6, 1: PRINT "Punktes zu verlÑngern."
                LOCATE 7, 1: PRINT "Durch drÅcken von 'n' wandeln Sie die Pause wieder in eine Note um."
                LOCATE 8, 1: PRINT
                LOCATE 9, 1: PRINT "Wenn Sie zwischen zwei Noten einen Zwischenraum erzeugen mîchten, geben Sie"
                LOCATE 10, 1: PRINT "eine '0' ein, und die Note bzw. die Pause verschwindet. Durch 'n' oder 'P'"
                LOCATE 11, 1: PRINT "kînnen Sie diesen Zwischenraum wieder in eine Note bzw. Pause verwandeln."

                LOCATE 21, 1: PRINT
                LOCATE 22, 1: PRINT "DrÅcken Sie ESC zur RÅckkehr zum Programm"
                LOCATE 23, 1: PRINT "DrÅcken Sie eine beliebige fÅr die nÑchste Seite"
        CASE 3
                CLS
                LOCATE 1, 1: PRINT "Hilfe zum Musikprogramm (Seite 3)";
                LOCATE 2, 1: PRINT "************************************************************"
                LOCATE 3, 1: PRINT "Die Dateioperationen sind zugegebenerma·en rudimentÑr sowie"
                LOCATE 4, 1: PRINT "sehr fehleranfÑllig. Daher ist gerade beim Speichern Vorsicht"
                LOCATE 5, 1: PRINT "geboten!"
                LOCATE 6, 1: PRINT "Es stehen folgende Tasten zur VerfÅgung:"
                LOCATE 7, 1: PRINT "  o - Optionen (Laufwerk und Pfad) - Standard = TEMP-Verzeichnis"
                LOCATE 8, 1: PRINT "  s - Speichern"
                LOCATE 9, 1: PRINT "  f - File von Platte laden"
                LOCATE 10, 1: PRINT ""
                LOCATE 11, 1: PRINT "Achtung! Das eingestellte Laufwerk und der Pfad mÅssen existieren,"
                LOCATE 12, 1: PRINT "da sonst beim nÑchsten Laden oder Speichern ein Fehler auftritt."
                LOCATE 13, 1: PRINT "Beim Laden und Speichern kann dann nur noch der Dateiname, nicht"
                LOCATE 14, 1: PRINT "jedoch das Laufwerk oder das Verzeichnis angegeben werden."
                LOCATE 15, 1: PRINT "Beim Laden mu· eine existierende Datei angegeben werden!"
                LOCATE 16, 1: PRINT
                LOCATE 17, 1: PRINT "Es ist zu beachten, da· zu Beginn als Pfad der Inhalt der TEMP-Umgebungs-"
                LOCATE 18, 1: PRINT "variablen eingestellt ist!"
                LOCATE 19, 1: PRINT "In der ersten Zeile der gespeicherten Datei steht die Tonart, in weiteren Zeilen"
                LOCATE 20, 1: PRINT "Zeichenketten, die als Argument der Funktion 'PLAY' dienen kînnen."
               
                LOCATE 21, 1: PRINT
                LOCATE 22, 1: PRINT "DrÅcken Sie ESC zur RÅckkehr zum Programm"
                LOCATE 23, 1: PRINT "DrÅcken Sie eine beliebige fÅr die nÑchste Seite"
        CASE 4
                CLS
                LOCATE 1, 1: PRINT "Hilfe zum Musikprogramm (Seite 4)";
                LOCATE 2, 1: PRINT "************************************************************"
                LOCATE 3, 1: PRINT "Durch Eingabe von 't' kînnen Sie das Tempo der Musik"
                LOCATE 4, 1: PRINT "bestimmen, Standard ist 120."
                LOCATE 5, 1: PRINT "Dur Eingabe von 'a' kînnen Sie die Tonart wÑhlen, es werden"
                LOCATE 6, 1: PRINT "dann hinter dem NotenschlÅssel die entsprechenden Symbole angezeigt."
                LOCATE 7, 1: PRINT "Durch Eingabe von 'mn', 'ms' oder 'ml' kînnen Sie die Spielart der"
                LOCATE 8, 1: PRINT "nachfolgenden Noten wÑhlen. Diese KÅrzel haben folgende Bedeutung:"
                LOCATE 9, 1: PRINT "  mn - Normale Musik    - jede Note wird Åber 7/8 der LÑnge gespielt."
                LOCATE 10, 1: PRINT "  ms - Musik Staccato   - jede Note wird Åber 3/4 der LÑnge gespielt."
                LOCATE 11, 1: PRINT "  ml - Musik Legato     - jede Note wird Åber die volle LÑnge gespielt."
                LOCATE 12, 1: PRINT "Dadurch kînnen 'verbundene' Noten realisiert werden, indem eine Note"
                LOCATE 13, 1: PRINT "als 'ml' deklariert wird und die folgende als 'mn'."
                LOCATE 21, 1: PRINT
                LOCATE 22, 1: PRINT "DrÅcken Sie ESC zur RÅckkehr zum Programm"
                LOCATE 23, 1: PRINT "DrÅcken Sie eine beliebige fÅr die nÑchste Seite"
        CASE 5
                CLS
                LOCATE 1, 1: PRINT "Hilfe zum Musikprogramm (Seite 5)";
                LOCATE 2, 1: PRINT "************************************************************"
                LOCATE 3, 1: PRINT "Durch Eingabe von 'y' kînnen Sie die Musik schlie·lich"
                LOCATE 4, 1: PRINT "abspielen."
             
                LOCATE 21, 1: PRINT
                LOCATE 22, 1: PRINT "DrÅcken Sie ESC zur RÅckkehr zum Programm"
                LOCATE 23, 1: PRINT "DrÅcken Sie eine beliebige fÅr die nÑchste Seite"
        CASE ELSE
                HilfeAllgemein$ = CHR$(27)
                EXIT FUNCTION
        END SELECT
        DO
                zzzz$ = INKEY$
        LOOP UNTIL zzzz$ <> ""
        HilfeAllgemein = zzzz$
END FUNCTION

SUB linien (z, farbe)
q = z
altseite = se
q = (z - 1) MOD anzlinien% + 1
sei = (z - 1) \ anzlinien%
seite sei
'IF q > anzlinien% THEN
'        q = q - anzlinien%
'        seite 1
'ELSE
'        seite 0
'END IF
FOR i = 0 TO 4
        LINE (1, q * zeilenabstand + i * linienabstand)-(xmax, q * zeilenabstand + i * linienabstand), farbe
NEXT
PSET (5, q * zeilenabstand + 20), notenfarbe
DRAW nschluessel$
LOCATE xton, yton
COLOR 15
PRINT USING "\      \"; ton$;
SELECT CASE ton$
CASE "C-Dur", "a-Moll"
CASE "G-Dur", "e-Moll"
        j! = .5 * (b - 10) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
CASE "D-Dur", "h-Moll"
        j! = .5 * (b - 10) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 7) + 2
        PSET (20, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
CASE "A-Dur", "fis-Moll"
        j! = .5 * (b - 10) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 7) + 2
        PSET (20, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 11) + 2
        PSET (26, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
CASE "E-Dur", "cis-Moll"
        j! = .5 * (b - 10) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 7) + 2
        PSET (20, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 11) + 2
        PSET (26, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 8) + 2
        PSET (32, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
CASE "H-Dur", "gis-Moll"
        j! = .5 * (b - 10) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 7) + 2
        PSET (20, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 11) + 2
        PSET (26, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 8) + 2
        PSET (32, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
        j! = .5 * (b - 5) + 2
        PSET (12, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 4), 2) + kreuz$
CASE "F-Dur", "d-Moll"
        j! = .5 * (b - 6) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
CASE "B-Dur", "g-Moll"
        j! = .5 * (b - 6) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 9) + 2
        PSET (18, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
CASE "Es-Dur", "c-Moll"
        j! = .5 * (b - 6) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 9) + 2
        PSET (18, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 5) + 2
        PSET (22, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
CASE "As-Dur", "f-Moll"
        j! = .5 * (b - 6) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 9) + 2
        PSET (18, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 5) + 2
        PSET (22, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 8) + 2
        PSET (26, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
CASE "Des-Dur", "b-Moll"
        j! = .5 * (b - 6) + 2
        PSET (14, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 9) + 2
        PSET (18, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 5) + 2
        PSET (22, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 8) + 2
        PSET (26, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
        j! = .5 * (b - 11) + 2
        PSET (30, q * zeilenabstand + j! * linienabstand), farbe
        DRAW "bu" + MID$(STR$(linienabstand + 7), 2) + be$
END SELECT
seite altseite
END SUB

SUB load
nwert = wert(zeile, spalte)
nlaenge = laenge(zeile, spalte)
ntempo = tempo(zeile, spalte)
noktave = oktave(zeile, spalte)
nkreuz = kreuz(zeile, spalte)
nbe = be(zeile, spalte)
nart$ = art$(zeile, spalte)
npunkte = punkt(zeile, spalte)
nentw = entw(zeile, spalte)
END SUB

SUB lw (l$)
LOCATE 1, 1
FOR i = 0 TO 25
        IF l$ = CHR$(65 + i) + ":" THEN
                COLOR 4
        ELSE
                COLOR 15
        END IF
        PRINT CHR$(65 + i) + ":" + " ";
NEXT
COLOR 15
END SUB

SUB note (farbe)
DRAW "c" + MID$(STR$(farbe), 2)
'z = zeile
'IF zeile > anzlinien% THEN z = z - anzlinien%
z = (zeile - 1) MOD anzlinien% + 1
SELECT CASE nwert
CASE null
CASE liedende
CASE zeilenende
CASE pause
        y = z * zeilenabstand
        SELECT CASE nlaenge
        CASE 1
                LINE (spalte * notenabstand, y + 2 * linienabstand)-(spalte * notenabstand - 8, y + 2 * linienabstand + 3), farbe, BF
        CASE 2
                LINE (spalte * notenabstand, y + 2 * linienabstand)-(spalte * notenabstand - 8, y + 2 * linienabstand - 3), farbe, BF
        CASE 4
                PSET (spalte * notenabstand, y + 2), farbe
                DRAW "f3g3e3fg3f5hlhlgdf2"
        CASE 8
                PSET (spalte * notenabstand, y + 1.5 * linienabstand), farbe
                DRAW "ldr2fr2er2g2dg2dgd2"
        CASE 16
                PSET (spalte * notenabstand, y + 1.5 * linienabstand), farbe
                DRAW "ldr2fr2er2g2dg2dgd2"
                PSET (spalte * notenabstand - 2, y + 1.5 * linienabstand + 4), farbe
                DRAW "ldr2fr2er2"
        CASE 32
                PSET (spalte * notenabstand, y + 1.5 * linienabstand), farbe
                DRAW "ldr2fr2er2g2dg2dgd2gd2"
                PSET (spalte * notenabstand - 2, y + 1.5 * linienabstand + 3), farbe
                DRAW "ldr2fr2er2"
                PSET (spalte * notenabstand - 4, y + 1.5 * linienabstand + 6), farbe
                DRAW "ldr2fr2er2"
        CASE 64
                PSET (spalte * notenabstand, y + 1.5 * linienabstand), farbe
                DRAW "ldr2fr2er2g2dg2dgd2gd2gd2"
                PSET (spalte * notenabstand - 2, y + 1.5 * linienabstand + 3), farbe
                DRAW "ldr2fr2er2"
                PSET (spalte * notenabstand - 4, y + 1.5 * linienabstand + 6), farbe
                DRAW "ldr2fr2er2"
                PSET (spalte * notenabstand - 6, y + 1.5 * linienabstand + 9), farbe
                DRAW "ldr2fr2er2"
        CASE ELSE
                'Hier andere PausenlÑngen
                PSET (spalte * notenabstand, z * zeilenabstand - 3), farbe
                DRAW "u6r3fdgl3d3br6"
                t$ = MID$(STR$(nlaenge), 2)
                FOR i = 1 TO LEN(t$)
                        DRAW zahl$(VAL(MID$(t$, i, 1)))
                NEXT
        END SELECT
        FOR i = 1 TO npunkte
                LINE (spalte * notenabstand + 5 * i + 2 * radius, y + 14)-(spalte * notenabstand + 5 * i + 2 * radius + 1, y + 15), farbe, BF
        NEXT
        SELECT CASE nart$
        CASE ""
        CASE "MN"
                PSET (spalte * notenabstand - 16, z * zeilenabstand - 3), farbe
                DRAW "u6f2df2du6"
        CASE "MS"
                PSET (spalte * notenabstand - 16, z * zeilenabstand - 3), farbe
                DRAW "r3euhl2huer3"
        CASE "ML"
                PSET (spalte * notenabstand - 16, z * zeilenabstand - 3), farbe
                DRAW "u6d6r4"
        END SELECT
        IF ntempo <> 0 THEN
                t$ = MID$(STR$(ntempo), 2)
                PSET (spalte * notenabstand - 16, z * zeilenabstand - 12), farbe
                FOR i = 1 TO LEN(t$)
                        DRAW zahl$(VAL(MID$(t$, i, 1)))
                NEXT
        END IF
CASE c TO b
        y = z * zeilenabstand + (3.5 * (3 - noktave) + 5 + .5 - nwert / 2) * linienabstand
        SELECT CASE nlaenge
        CASE 1, 2, 4, 8, 16, 32, 64
                CIRCLE (spalte * notenabstand, y), radius, farbe
        CASE ELSE
                'Hier andere NotenlÑngen
                FOR r = 1 TO radius
                        CIRCLE (spalte * notenabstand, y), r, farbe
                NEXT
                LINE (spalte * notenabstand - 1, y - 1)-(spalte * notenabstand + 1, y + 1), farbe, BF
                'PAINT (spalte * notenabstand, y), farbe, farbe
                IF noktave < 4 THEN
                        PSET (spalte * notenabstand, z * zeilenabstand - 3), farbe
                ELSE
                        PSET (spalte * notenabstand, z * zeilenabstand + 5 * linienabstand + 2), farbe
                END IF
                DRAW "u6f2df2du6d6br2"
                t$ = MID$(STR$(nlaenge), 2)
                FOR i = 1 TO LEN(t$)
                        DRAW zahl$(VAL(MID$(t$, i, 1)))
                NEXT
        END SELECT
        SELECT CASE nlaenge
        CASE 4, 8, 16, 32, 64
                FOR r = 1 TO radius
                        'paint (spalte * notenabstand, y), farbe, farbe
                        CIRCLE (spalte * notenabstand, y), r, farbe
                NEXT
                LINE (spalte * notenabstand - 1, y - 1)-(spalte * notenabstand + 1, y + 1), farbe, BF
        END SELECT
        SELECT CASE nlaenge
        CASE 2, 4, 8, 16, 32, 64
                IF noktave < 4 THEN
                        LINE (spalte * notenabstand + radius, y)-(spalte * notenabstand + radius + 1, y - halslaenge), farbe, BF
                ELSE
                        LINE (spalte * notenabstand - radius, y)-(spalte * notenabstand - radius - 1, y + halslaenge), farbe, BF
                END IF
        END SELECT
        IF noktave < 4 THEN
                SELECT CASE nlaenge
                CASE 8
                        hals1 y - halslaenge + 2, farbe
                CASE 16
                        hals1 y - halslaenge + 2, farbe
                        hals1 y - halslaenge + 7, farbe
                CASE 32
                        hals1 y - halslaenge + 2, farbe
                        hals1 y - halslaenge + 6, farbe
                        hals1 y - halslaenge + 10, farbe
                CASE 64
                        hals1 y - halslaenge + 2, farbe
                        hals1 y - halslaenge + 5, farbe
                        hals1 y - halslaenge + 8, farbe
                        hals1 y - halslaenge + 11, farbe
                END SELECT
        ELSE
                SELECT CASE nlaenge
                CASE 8
                        hals2 y + halslaenge - 2, farbe
                CASE 16
                        hals2 y + halslaenge - 2, farbe
                        hals2 y + halslaenge - 7, farbe
                CASE 32
                        hals2 y + halslaenge - 2, farbe
                        hals2 y + halslaenge - 6, farbe
                        hals2 y + halslaenge - 10, farbe
                CASE 64
                        hals2 y + halslaenge - 2, farbe
                        hals2 y + halslaenge - 5, farbe
                        hals2 y + halslaenge - 8, farbe
                        hals2 y + halslaenge - 11, farbe
                END SELECT
        END IF
        IF farbe = 0 THEN
                fa = 0
        ELSE
                fa = linienfarbe
        END IF
        FOR i = z * zeilenabstand TO y STEP linienabstand
                LINE (spalte * notenabstand - 5, i)-(spalte * notenabstand + 7, i), fa
        NEXT
        FOR i = z * zeilenabstand TO y STEP -linienabstand
                LINE (spalte * notenabstand - 5, i)-(spalte * notenabstand + 7, i), fa
        NEXT
        FOR i = 1 TO npunkte
                LINE (spalte * notenabstand + 5 * i + 2 * radius, y + 1)-(spalte * notenabstand + 5 * i + 2 * radius + 1, y + 2), farbe, BF
        NEXT
        IF nkreuz = 1 THEN
                PSET (spalte * notenabstand - 12, y - linienabstand), farbe
                DRAW kreuz$
        END IF
        IF nentw = 1 AND vb(nwert) + vk(nwert) > 0 THEN
                PSET (spalte * notenabstand - 12, y + 4), farbe
                DRAW entwer$
        END IF
        IF nbe = 1 THEN
                PSET (spalte * notenabstand - 10, y - 5 - linienabstand), farbe
                DRAW be$
        END IF
        SELECT CASE nart$
        CASE ""
        CASE "MN"
                PSET (spalte * notenabstand - 16, z * zeilenabstand - 3), farbe
                DRAW "u6f2df2du6"
        CASE "MS"
                PSET (spalte * notenabstand - 16, z * zeilenabstand - 3), farbe
                DRAW "r3euhl2huer3"
        CASE "ML"
                PSET (spalte * notenabstand - 16, z * zeilenabstand - 3), farbe
                DRAW "u6d6r4"
        END SELECT
        IF ntempo <> 0 THEN
                t$ = MID$(STR$(ntempo), 2)
                PSET (spalte * notenabstand - 16, z * zeilenabstand - 12), farbe
                FOR i = 1 TO LEN(t$)
                        DRAW zahl$(VAL(MID$(t$, i, 1)))
                NEXT
        END IF
CASE ELSE
        BEEP
END SELECT
END SUB

SUB save
wert(zeile, spalte) = nwert
laenge(zeile, spalte) = nlaenge
tempo(zeile, spalte) = ntempo
oktave(zeile, spalte) = noktave
kreuz(zeile, spalte) = nkreuz
be(zeile, spalte) = nbe
art$(zeile, spalte) = nart$
punkt(zeile, spalte) = npunkte
entw(zeile, spalte) = nentw
END SUB

SUB seite (s)
IF s <> se THEN
        DEF SEG = &HA000: BSAVE "noten" + MID$(STR$(se), 2), 0, videogroesse: DEF SEG
'        SCREEN , , s, s
        DEF SEG = &HA000: BLOAD "noten" + MID$(STR$(s), 2): DEF SEG
        se = s
END IF
END SUB

SUB spalteminus
spalte = spalte - 1
IF spalte = 0 THEN
        spalte = anznoten%
        zeile = zeile - 1
        'IF zeile <= anzlinien% AND se = 1 THEN
        IF zeile MOD anzlinien% = 0 AND se > 0 THEN
                seite se - 1
                'zeile = anzlinien%
                'spalte = anznoten%
                'seite 0
        ELSEIF zeile = 0 THEN
                zeile = 1
                spalte = 1
        END IF

END IF
END SUB

SUB spalteplus
spalte = spalte + 1
IF spalte > anznoten% THEN
        spalte = 1
        zeile = zeile + 1
        'IF zeile > anzlinien% AND se = 0 THEN
        IF zeile MOD anzlinien% = 1 AND se < seiten - 1 THEN
                seite se + 1
                'spalte = 1
                'seite 1
        ELSEIF zeile > seiten * anzlinien% THEN
                zeile = seiten * anzlinien%
                spalte = anznoten%
        END IF
END IF
END SUB

SUB speichern (m)
save
COLOR 15
LOCATE 1, 1
IF m = 0 THEN INPUT "Dateiname:", datei$ ELSE datei$ = "sicher.mus"
LOCATE 1, 1
PRINT SPACE$(28);
IF INSTR(datei$, ".") = 0 THEN datei$ = LEFT$(datei$, 8) + ".mus"
codieren
OPEN laufwerk$ + pfad$ + "\" + datei$ FOR OUTPUT AS #1
PRINT #1, ton$
FOR i = 1 TO 10
        PRINT #1, musik$(i)
NEXT
CLOSE #1
END SUB

SUB spielen
FOR i = 1 TO 10
        PLAY musik$(i)
NEXT
END SUB

SUB startinit
RESTORE
FOR i = 1 TO anztonarten
        READ tonart$(i)
NEXT
ton$ = tonart$(1)
SCREEN bildschirmmodus: OUT 968, 0: OUT 969, 0: OUT 969, 0: OUT 969, 63' PALETTE 0, 1'SCREEN 12
se = 0
'seite 0
druckmodus = 38
'FOR i = 1 TO seiten * anzlinien%
'        linien i, linienfarbe
'NEXT
FOR i = 1 TO anzlinien
        linien i, linienfarbe
NEXT
FOR i = 1 TO seiten
        DEF SEG = &HA000: BSAVE "noten" + MID$(STR$(i), 2), 0, videogroesse: DEF SEG
NEXT
'seite 1
'FOR i = 1 TO anzlinien%
'        linien i, linienfarbe
'NEXT
'seite 0
zeile = 1: spalte = 1: nwert = a: nlaenge = 4: ntempo = 0: noktave = 3: nkreuz = 0: nbe = 0: art$ = "": npunkte = 0: nentw = 0
note aktnotenfarbe
END SUB

SUB tona (t$)
LOCATE xton, yton
PRINT USING "\      \"; t$;
END SUB

FUNCTION tonminus$ (t$)
FOR i = 1 TO anztonarten
        IF t$ = tonart$(i) THEN
                IF i > 1 THEN
                        tonminus$ = tonart$(i - 1)
                ELSE
                        tonminus$ = tonart$(anztonarten)
                END IF
                EXIT FOR
        END IF
NEXT
END FUNCTION

FUNCTION tonplus$ (t$)
FOR i = 1 TO anztonarten
        IF t$ = tonart$(i) THEN
                IF i < anztonarten THEN
                        tonplus$ = tonart$(i + 1)
                ELSE
                        tonplus$ = tonart$(1)
                END IF
                EXIT FOR
        END IF
NEXT
END FUNCTION

SUB vorz
FOR i = c TO b
        vk(i) = 0
        vb(i) = 0
NEXT
SELECT CASE ton$
CASE "C-Dur", "a-Moll"
CASE "G-Dur", "e-Moll"
        vk(f) = 1
CASE "D-Dur", "h-Moll"
        vk(c) = 1
        vk(f) = 1
CASE "A-Dur", "fis-Moll"
        vk(c) = 1
        vk(g) = 1
        vk(f) = 1
CASE "E-Dur", "cis-Moll"
        vk(c) = 1
        vk(g) = 1
        vk(f) = 1
        vk(d) = 1
CASE "H-Dur", "gis-Moll"
        vk(c) = 1
        vk(g) = 1
        vk(f) = 1
        vk(d) = 1
        vk(a) = 1
CASE "F-Dur", "d-Moll"
        vb(b) = 1
CASE "B-Dur", "g-Moll"
        vb(b) = 1
        vb(e) = 1
CASE "Es-Dur", "c-Moll"
        vb(e) = 1
        vb(a) = 1
        vb(b) = 1
CASE "As-Dur", "f-Moll"
        vb(e) = 1
        vb(a) = 1
        vb(b) = 1
        vb(d) = 1
CASE "Des-Dur", "b-Moll"
        vb(e) = 1
        vb(a) = 1
        vb(b) = 1
        vb(d) = 1
        vb(g) = 1
END SELECT
END SUB

FUNCTION xmin (x, y)
IF y = 0 THEN
        xmin = x
ELSEIF x < y THEN
        xmin = x
ELSE
        xmin = y
END IF
END FUNCTION

