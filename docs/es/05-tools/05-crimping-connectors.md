# Crimping de Conectores

El crimping es un método para conectar un cable a una terminal o contacto sin soldar.

Un buen crimping proporciona:

- contacto eléctrico;
- retención mecánica del cable;
- soporte de aislamiento;
- repetibilidad;
- ensamblaje y mantenimiento convenientes.

Un prensado pobre puede calentarse, desmoronarse, causar errores aleatorios y casi normales.

## Por Qué el Crimping a Menudo es Mejor que Soldar

Para conectores y terminales, el crimping a menudo es mejor que soldar porque:

- el cable permanece flexible;
- el contacto está diseñado por el fabricante;
- el aislamiento se retiene;
- la junta maneja mejor la vibración;
- el conector se puede desensamblar y servir;
- sin riesgo de fundir el cuerpo del conector de plástico durante la soldadura.

La soldadura es buena para almohadillas y cables, pero no debe reemplazar un contacto adecuado en un conector si el fabricante tenía la intención de crimping.

## Tipos de Terminales y Conectores

En dispositivos simples a menudo encuentra:

- Dupont - conexiones de señal débil para breadboards;
- JST-XH/JST-PH y similares - sensores, ventiladores, módulos pequeños;
- ferrules - puntas para cable multihebra en terminales de tornillo;
- Faston - terminales planas para algunas conexiones de potencia;
- terminales de anillo y espada;
- terminales de tornillo;
- bloques de terminal montados en placa.

Cada tipo requiere su propio contacto, su propio calibre de cable y su propia herramienta.

## Necesita la Herramienta Correcta

Las pinzas no son una herramienta de crimping.

Puede apretar un contacto para que parezca sostener, pero no obtendrá un crimping adecuado.

Para un crimping adecuado, necesita:

- una terminal para el calibre de cable correcto;
- longitud de pelado correcta;
- matriz de herramienta correcta;
- posición de contacto correcta en la matriz;
- zonas separadas para crimping de hebra y aislamiento;
- sin hilos dañados.

Los fabricantes profesionales de conectores proporcionan especificaciones de crimping, altura de crimping, longitud de pelado y fuerza de tracción. Para ensamblaje DIY no siempre tiene control total, pero el principio es el mismo: contacto, cable y herramienta deben coincidir entre sí.

## Crimping de Barril Abierto

Muchos contactos pequeños, como JST o Dupont, tienen dos pares de "alas":

- un par crimpea el conductor desnudo;
- el otro par sostiene el aislamiento.

Buen resultado:

- el conductor es visible en la zona correcta;
- el aislamiento se sostiene por las alas traseras;
- la longitud expuesta no es demasiado larga;
- los hilos del conductor no sobresalen;
- el contacto no está sesgado;
- el contacto entra en el cuerpo del conector y se bloquea en su lugar.

Si el aislamiento entró en la zona de crimping del conductor, el contacto eléctrico será pobre.

Si solo se crimpea el conductor y el aislamiento no se sostiene, el cable puede romperse cuando se mueve.

## Ferrules

Para cable multihebra en una terminal de tornillo, las ferrules a menudo son útiles.

Ellas:

- reúnen todos los hilos juntos;
- evitan que los hilos se separen;
- mejoran la colocación en la terminal;
- reducen el riesgo de que algunos hilos queden afuera;
- hacen la junta más limpia.

Esto es especialmente útil para cables de potencia, bloques de terminal y ensamblajes que se van a servir.

Pero las ferrules también deben coincidir con el calibre del cable y ser crimpadas con la matriz correcta.

## Cómo Verificar un Crimping

Después de crimping, verifique:

- el contacto no se mueve en el cable;
- el aislamiento se sostiene;
- el conductor no se sale;
- no hay hilos cortados;
- la longitud expuesta no es demasiado larga;
- el contacto entra en el cuerpo del conector;
- el bloqueo hace clic en su lugar;
- el cable resiste el tirón suave.

Una prueba de tirón suave es útil: tire suavemente del cable. No debe salir del contacto.

No hay necesidad de tirar con toda su fuerza. El objetivo es encontrar crimps obviamente malos antes de la instalación.

## Por Qué los Crimpings Pobres Se Calientan

Un crimping pobre crea alta resistencia.

Bajo corriente se convierte en calor.

Primero la terminal podría estar tibia. Luego el plástico se oscurece, el contacto empeora, el calor aumenta.

Esto es especialmente peligroso para:

- calentadores;
- ventiladores con corriente significativa;
- tiras LED;
- fuentes de alimentación;
- circuitos SSR/MOSFET;
- conexiones de corriente alterna.

Si una terminal se calienta, apague la potencia y rehaga la conexión.

## Dupont No Es para Potencia

Dupont es conveniente para breadboards y señales débiles.

Pero no se puede usar como conector de potencia adecuado para:

- un calentador;
- potencia del dispositivo;
- una tira LED potente;
- piezas de corriente alterna;
- un motor o servo con corriente grande.

Incluso si el conector físicamente encaja en los pines, eso no significa que esté clasificado para la corriente, vibración y calor necesarios.

## Errores Comunes

- crimpado con pinzas;
- elegida terminal de calibre incorrecto;
- pelado demasiado aislamiento;
- pelado demasiado poco aislamiento;
- crimpado aislamiento en lugar del conductor;
- no crimpado el soporte de aislamiento;
- cortados algunos hilos;
- contacto no se bloquea en el cuerpo;
- línea de potencia sostenida en Dupont;
- ferrule de calibre incorrecto;
- no se realizó prueba de tirón;
- la terminal se calienta pero el dispositivo sigue funcionando.

## Lo Esencial

- El crimping es tanto contacto eléctrico como retención mecánica.
- Contacto, cable y herramienta deben coincidir entre sí.
- Las pinzas no reemplazan una herramienta de crimping.
- Para cable multihebra en una terminal de tornillo, las ferrules a menudo son útiles.
- Los crimpings pobres pueden calentarse y ser peligrosos.
- Las piezas de potencia no deben confiar en conectores de breadboard débiles.

## Materiales de Referencia

- [Molex: Quality Crimp Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/commercialcrimpbookpdf/638/63800/TM-638000029-001.pdf?inline=) - referencia detallada de calidad de crimping, fuerza de tracción, crimping de conductor y aislamiento.
- [Molex: Industrial Crimp Quality Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/industrialcrimpbookpdf/640/64016/TM-640160065-001.pdf?inline=) - inspección visual de crimping de barril abierto y cerrado, longitud de pelado, cepillo de alambre y defectos comunes.
- [JST: Application Tooling Guide, Crimp Style](https://www.jst.com/resources/application-tooling-guide/crimp-style/) - ejemplo de cómo los contactos JST específicos necesitan herramientas específicas, longitud de pelado y especificaciones de tracción.
- [American Electrical: Wire Ferrules](https://www.americanelectrical.com/wire-ferrules/) - por qué las ferrules son útiles para cable multihebra en bloques de terminales.
- [TE Connectivity: Wire Splices](https://www.te.com/en/products/terminals-splices/splices.html) - tipos de conexión de empalme/crimpado industrial y por qué el crimping está diseñado por separado, no apretado al azar.
