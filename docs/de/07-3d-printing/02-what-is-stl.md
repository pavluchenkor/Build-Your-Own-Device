# Was ist STL

STL ist eine Datei, die die Geometrie eines 3D-Modells enthält.

In einfachen Worten: STL teilt dem Slicer mit, welche Form zu drucken ist. Aber STL sagt fast nichts darüber aus, wie man dieses Teil stark, wärmebeständig und sicher in einem echten Gerät macht.

Daher bedeutet die Aussage „Ich habe eine STL-Datei für ein Gehäuse", nicht dass du eine vollständige Montageanleinung zum Aufbau eines Geräts hast.

## Was STL speichert

STL beschreibt die Oberfläche eines Modells als eine Menge von Dreiecken.

Der Slicer übernimmt diese Geometrie und konvertiert sie in Druckpfade.

STL ist nützlich, weil:

- fast alle Slicer es verstehen;
- es aus den meisten CAD-Programmen exportiert werden kann;
- es einfach ist, ein Modell zu tauschen;
- es gut für ein fertiges Teil mit einfacher Geometrie geeignet ist.

Aber STLs Einfachheit ist auch seine Beschränkung.

## Was STL nicht speichert

Ein typisches STL speichert nicht:

- Material;
- Farbe;
- Druckausrichtung;
- Schichthöhe;
- Füllung;
- Anzahl der Wände;
- Temperatureinstellungen;
- Unterstützungstyp;
- Befestigungselemente;
- Montageanleitungen;
- Toleranzen;
- Teilzweck;
- Wärmewarnungen;
- Informationen darüber, wo das Teil schwächer wird.

Dies bedeutet, dass zwei Personen das gleiche STL drucken und unterschiedliche Teile erhalten können.

Eine Person könnte PLA schnell und schön drucken. Eine andere könnte ASA mit mehr Wänden und der richtigen Ausrichtung drucken. Die Teile sehen äußerlich ähnlich aus, aber neben Wärme werden sie sich unterschiedlich verhalten.

## Warum dies bei beheizten Geräten wichtig ist

Bei einer dekorativen Abdeckung ist STL oft ausreichend.

Bei einem Teil neben einem Heizer nicht.

Du musst wissen:

- aus welchem Material es zu drucken ist;
- welche Temperatur dort sein wird;
- wird das Teil eine Last halten;
- gibt es Drähte in der Nähe;
- wird der Sensor verschoben, wenn das Teil sich verformt;
- wird das Teil den Luftstrom blockieren;
- kommt das Kunststoff zu nah an eine Klemme oder einen Heizer.

Falls ein STL ohne Informationen über Material und Arbeitsbedingungen heruntergeladen wird, kann es nicht als fertige Lösung für einen Trockner, eine Druckerkammer oder ein Heizmodul angesehen werden.

## Druckausrichtung ändert die Festigkeit

FDM-Teile werden aus Schichten hergestellt.

Deswegen kann das gleiche Modell sein:

- stark bei einer Ausrichtung;
- schwach bei einer anderen;
- anfällig für Delamination unter Last;
- schlecht für Schraubenbefestigung;
- nur gut für dekorativen Gebrauch.

Zum Beispiel kann eine dünne Halterung eine Last gut halten, wenn Schichten in Kraftrichtung laufen. Aber die gleiche Halterung kann zwischen Schichten brechen, wenn die andere Weise gedruckt wird.

STL selbst sagt nicht, wie ein Teil korrekt ausgerichtet wird.

## Slicer-Einstellungen zählen auch

Auch mit dem richtigen Material und der richtigen Ausrichtung beeinflussen Druckeinstellungen das Ergebnis.

Bei einem funktionierenden Teil sind diese wichtig:

- Anzahl der Umfang;
- Wandstärke;
- oben und unten Schichten;
- Füllprozentsatz;
- Drucktemperatur;
- Kühlung;
- Unterstützungen;
- Linienbreite;
- Qualität der Schichthaftung.

Mehr Füllung löst nicht immer das Problem. Oft bei einem Gehäuse, einer Halterung oder einem Luftkanal sind Wände, Umfang, Teilform und Lastrichtung wichtiger.

## Was du brauchst, bevor du ein funktionierendes Teil druckst

Falls ein Teil Teil eines Geräts sein wird, brauchst du mehr als nur das STL. Du brauchst einen kurzen Satz von Anforderungen:

- Material;
- Ausrichtung auf dem Bett;
- empfohlene Wandstärke und Füllung;
- ob Unterstützungen erforderlich sind;
- welche Schrauben und Einsätze zu verwenden sind;
- wo das Teil nicht in der Nähe von Wärme platziert werden kann;
- maximale Betriebstemperatur der Zone;
- wie man die Anpassung nach dem Drucken überprüft;
- was zu tun ist, wenn sich das Teil verformt.

Dies ist besonders wichtig für:

- Heizer-Halterung;
- Luftkanal;
- Lüftermontage;
- Temperatursensor-Halter;
- Elektronik-Gehäuse;
- Terminal-Halterung;
- Teile in der Nähe von 110–230 V Wechselstrom.

## STL, 3MF und Projektdateien

STL ist das einfachste und kompatibilste Format, aber nicht das vollständigste.

Das 3MF-Format wurde als moderneres Format für 3D-Druck erstellt. Es kann mehr Daten speichern: nicht nur Geometrie, sondern auch Informationen über Materialien, Farben, Objekte und Herstellungseinstellungen.

Viele Slicer können auch eine Projektdatei speichern. Solch eine Datei ist nützlich, weil sie nicht nur das Modell, sondern auch die Ausrichtung, Druckeinstellungen, Modifizierer und Platzierung auf dem Bett speichert.

Eine praktische Regel:

- STL ist gut zum Übertragen einer Form;
- 3MF oder ein Slicer-Projekt ist besser zum Übergeben der Druckabsicht;
- Textanweisungen werden noch benötigt, wenn das Teil die Sicherheit beeinflusst.

## Wie man einen heruntergeladene STL bewertet

Bevor du ein heruntergeladenes Teil druckst, frag dich selbst:

1. Ist es klar, aus welchem Material es zu drucken ist?
2. Gibt es Temperaturwarnungen?
3. Kannst du sehen, in welcher Ausrichtung es gedruckt wurde?
4. Gibt es Fotos des echten Teils in der Baugruppe?
5. Sind Schrauben, Muttern, Einsätze und Toleranzen spezifiziert?
6. Ist es klar, welche Last es halten wird?
7. Besteht ein Risiko, dass Verformung eine gefährliche Situation schaffen könnte?

Falls du keine Antworten hast, kann das Teil als Idee oder Prototyp verwendet werden, aber nicht als garantiertes sicheres funktionierendes Komponente.

## Häufige Fehler

- Behandlung eines STL als vollständige Anweisung;
- Drucken eines funktionierenden Teils aus PLA nur weil es einfacher ist;
- Nicht Ändern der Druckausrichtung für Last;
- Verwendung von zu wenigen Wänden und hoffen hohe Füllung löst es;
- Nicht Berechnung der Temperatur im Gehäuse;
- Nicht Überprüfen von Lücken nach dem Drucken;
- Schrauben in dünnen Pfosten ohne Marge;
- Verwendung eines heruntergeladenen Gehäuses in der Nähe von Wärme, ohne das Material zu verstehen;
- Nicht Hinterlassung von Zugang für Wartung nach der Montage.

## Wichtigste Erkenntnisse

- STL speichert Form, nicht einen sicheren Weg zur Herstellung eines Teils.
- Für ein Gerät zählen Material, Ausrichtung, Wände, Befestigungselemente und Arbeitsbedingungen.
- Ein STL kann in einem schwachen oder starken Teil resultieren.
- Für Teile in der Nähe von Wärme benötigen Sie Informationen über Material und Temperaturgrenzen.
- 3MF oder Slicer-Projektdateien vermitteln besser Einstellungen, ersetzen aber nicht die Ingenieurs-Überprüfung.

## Referenzen

- [3MF Consortium: The File Format for 3D Printing](https://3mf.io/) - warum 3MF erstellt wurde und welche Grenzen der alten Formate es adressiert.
- [3MF Consortium FAQ: 3MF vs STL](https://3mf.io/resources/faq/) - kurzer Vergleich von STL und 3MF: Materialien, Eigenschaften, Topologie und Erweiterbarkeit.
- [Prusa Knowledge Base: Supported file formats](https://help.prusa3d.com/article/supported-file-formats_1772) - welche Formate PrusaSlicer unterstützt und warum 3MF als bevorzugtes Projektformat verwendet wird.
- [Xometry: STL File Format](https://www.xometry.com/resources/3d-printing/stl-file-format/) - praktische Beschreibung von STL und den Daten, die es nicht speichert: Material, Farbe, Druckprofil und CAD-Verlauf.
- [Xometry: 3MF File Format](https://www.xometry.com/resources/3d-printing/3mf-file-format/) - Übersicht über 3MF als moderneren Behälter für Fertigungsdaten.
