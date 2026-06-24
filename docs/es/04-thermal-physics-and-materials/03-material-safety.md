# Materiales, Inflamabilidad y Emisiones Dañinas

El material para la cámara, secadora, filtro, carcasa o conducto de aire no se puede elegir solo por precio, espesor y facilidad de corte.

En un dispositivo calentado, el material debe resistir no solo la operación normal, sino también fallas razonables: detención del ventilador, error del sensor, interruptor atascado, mal contacto, terminal sobrecalentado o corriente de aire caliente localizado.

## Qué Significa "Adecuado para Calentamiento"

El material es adecuado no porque "no se derrita inmediatamente". Para un dispositivo calentado, importan varias propiedades diferentes:

- temperatura máxima de funcionamiento continuo;
- temperatura de reblandecimiento o temperatura de deformación térmica;
- inflamabilidad;
- generación de humo;
- toxicidad de los productos de combustión;
- resistencia del pegamento, lámina, recubrimiento o laminación;
- comportamiento en contacto con aire caliente;
- requisitos del fabricante para el ensamblaje.

La temperatura de fusión por sí sola es casi inútil. El plástico puede perder rigidez y forma mucho antes de fundirse. El aislamiento puede cambiar de dimensiones. El pegamento puede despegarse. Una pieza impresa puede deformarse bajo carga.

## Temperatura de Funcionamiento y Margen de Seguridad

Primero, necesita entender cuál será la temperatura no "en promedio en la cámara", sino en lugares específicos:

- cerca del calentador;
- en la salida de aire caliente;
- cerca de terminales y cables;
- en sujetadores de metal;
- en pared interior;
- en piezas impresas;
- bajo aislamiento;
- en la superficie exterior.

Si la cámara sostiene `45°C`, no significa que todas las partes interiores también estén a `45°C`. Cerca del calentador o en el conducto de aire puede ser significativamente más caliente.

Regla práctica: el material debe tener un margen de seguridad para la temperatura de funcionamiento continuo exactamente en el lugar donde se encuentra. Para la zona junto al calentador, el margen debe ser mayor que para el panel decorativo exterior.

## Inflamabilidad - No Es Una Sola Palabra

La documentación puede contener diferentes sistemas de clasificación.

Para plásticos, a menudo se indica UL 94:

- `HB` - la muestra horizontal se quema más lentamente que el límite especificado;
- `V-2`, `V-1`, `V-0` - la muestra vertical debe auto-extinguirse dentro del tiempo especificado, las diferencias incluyen comportamiento de goteo;
- `5VB`, `5VA` - pruebas más rigurosas para ciertas aplicaciones;
- `HBF`, `HF-1`, `HF-2` - clases para materiales de espuma.

Importante: UL 94 es una pequeña prueba de laboratorio en muestras. Ayuda a comparar materiales, pero no prueba que una cámara casera sea segura en cualquier falla.

En la documentación de materiales de construcción en ruso, es posible que encuentre:

- `НГ` - material no inflamable;
- `Г1-Г4` - grupos de inflamabilidad;
- `В1-В3` - ignitibilidad;
- `Д1-Д3` - capacidad de generar humo;
- `Т1-Т4` - toxicidad de los productos de combustión;
- `РП1-РП4` - propagación de llamas en la superficie.

Si un vendedor escribe "auto-extinguible", esto no reemplaza la hoja de datos. El material aún puede fumar, gotear, carbonizarse, deformarse o liberar productos peligrosos cuando se sobrecalienta.

## Ejemplo: XPS, EPS y PIR

Los materiales de aislamiento para construcción a menudo parecen convenientes para cámaras o secadoras: son ligeros, planos, baratos, se cortan bien y aíslan bien. Pero deben verse como materiales de construcción con sus propias limitaciones, no como partes universales para un calentador.

| Material | Donde Puede Ser Apropiado | Riesgos Principales | Qué Verificar |
| --- | --- | --- | --- |
| XPS, poliestireno extruido | aislamiento externo de zonas frías si se separa de la pieza caliente | temperatura de funcionamiento limitada, deformación, inflamabilidad, humo en fuego | descripción técnica, temperatura máxima, características de fuego, capa protectora |
| EPS, poliestireno expandido | solo con cautela y lejos de zonas calientes | baja resistencia térmica, inflamabilidad, deformación, humo | hoja de datos del material, sin calentamiento directo, cubierto con capa no inflamable |
| PIR / polisocianuro | aislamiento de tipo construcción, a veces mejor comportamiento al fuego que láminas de poliestireno | no automáticamente no inflamable, depende del revestimiento y producto específico | descripción técnica, temperatura de funcionamiento, clase de reacción al fuego, limitaciones del fabricante |
| Lana mineral | aislamiento térmico donde las fibras son permisibles y se necesita alta resistencia térmica | polvo, fibras, compresión, humedad, necesidad de sellar flujo de aire | temperatura permisible, aglutinante, protección facial, ensamblaje |
| Metal | pantalla, pared interior, disipador de calor | puentes térmicos, superficie exterior caliente, bordes afilados | conexión a tierra para sección de corriente alterna, temperatura, aislamiento de cables |
| Plástico impreso en 3D | sujetadores y protecciones fuera de la zona caliente | reblandecimiento, fluencia bajo carga, inflamabilidad | material, temperatura de deformación, temperatura real de la pieza |

Para XPS en datos técnicos del fabricante, a menudo se indica una temperatura máxima de servicio alrededor de `74°C` (`165°F`). Esto no significa que todos los XPS sean iguales, pero muestra el orden de limitación: este material no puede colocarse automáticamente junto a un calentador o aire caliente.

Para EPS, se encuentran recomendaciones para mantener temperaturas de funcionamiento alrededor de `75°C`; por encima de esto, el material puede perder estabilidad dimensional. Nuevamente, el valor exacto debe tomarse de la documentación del producto específico.

PIR/polisocianuro puede tener un rango permisible más alto en productos individuales, pero esto no elimina la verificación de propiedades de fuego, revestimiento, pegamento, humo y recomendaciones del fabricante.

## Pila de Materiales "Segura"

Para una cámara calentada, a menudo es mejor pensar no en un "material de pared" sino en capas.

![Ejemplo de capas de material junto al calor](../../img/04-thermal-physics-and-materials/03-safe-material-stack.svg)

Ejemplo de lógica más sólida:

- dentro de la zona caliente - metal, cerámica, vidrio u otro material que resiste la temperatura y no se incendia por sobrecalentamiento local;
- más allá - brecha de aire o aislamiento si es realmente necesario;
- exterior - carcasa que no se calienta a temperatura peligrosa;
- los cables y terminales no tocan el aislamiento y no se esconden en zonas donde el sobrecalentamiento pasaría desapercibido;
- hay protección de sobrecalentamiento independiente si la falla de control podría llevar a calentamiento peligroso.

El aislamiento no debe ser el primer material que vea el calentador.

## Piezas Impresas en 3D Cerca del Calor

El plástico impreso es conveniente para soportes, protecciones, portadores de sensores y conductos de aire. Pero en una cámara calentada puede comportarse peor de lo que parece de la bobina.

Riesgos típicos:

- PLA pierde rápidamente rigidez cuando se calienta y bajo carga;
- PETG es mejor que PLA, pero también puede fluir y deformarse;
- ABS/ASA generalmente tolera mejor la cámara caliente, pero requiere verificación de temperatura real;
- PC y materiales de ingeniería pueden resistir más, pero requieren impresión adecuada y aún no eliminan la evaluación de fuego.

Para piezas cerca del calentador, no se puede confiar solo en el nombre del plástico. Son importantes la marca del filamento, la configuración de impresión, el espesor, la carga, la dirección de la capa, la ventilación y la temperatura real de la pieza.

## Qué Leer Antes de Comprar

Busque documentos técnicos, no marketing:

- descripción técnica o hoja de datos del producto;
- SDS/MSDS si el material puede calentarse, cortarse, lijarse o quemarse;
- clasificación de fuego / reacción al fuego;
- clase UL 94 u otra inflamabilidad para plásticos;
- temperatura máxima de funcionamiento continuo;
- limitaciones de ensamblaje;
- limitaciones de contacto con fuentes de calor;
- requisitos para cubrir con revestimiento, metal, cartón yeso u otra capa.

Si el material se vende solo como "lámina de aislamiento" sin la hoja de datos adecuada, no debe colocarse en un dispositivo calentado casero.

## Qué Definitivamente No Es Normal

Soluciones malas:

- pegando espuma o XPS directamente junto al calentador;
- dirigiendo flujo caliente hacia plástico desconocido;
- cubriendo terminales y cables con aislamiento;
- colocando material inflamable junto a sección de corriente alterna `110-230V AC`;
- confiando en un solo sensor de temperatura;
- tratando material de construcción como seguro para cámara sin verificación;
- usando "auto-extinguible" como reemplazo para protección de sobrecalentamiento independiente;
- haciendo el primer calentamiento sin observación y mediciones.

## Conclusión Principal

La seguridad del material no es un parámetro. Necesita mirar la temperatura de funcionamiento, inflamabilidad, humo, toxicidad de los productos de combustión, pegamentos, revestimientos y escenarios de falla reales.

Si el material no tiene documentación clara, no puede colocarse cerca del calentador como protección primaria. Si el material es inflamable, debe ser removido de la zona caliente, cubierto con una capa apropiada y verificado por medición en modo de funcionamiento real.

## Materiales sobre el Tema

- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - explicación de UL 94, pruebas verticales/horizontales, clases para plásticos y materiales de espuma.
- [UL Solutions Code Authorities: UL 94 Rating Certifications and Limitations](https://code-authorities.ul.com/about/blog/understanding-ul-94-rating-certifications-and-limitations/) - limitaciones de la aplicación de UL 94 a productos reales y piezas grandes.
- [Russian Emergency Ministry: Federal Law No. 123-FZ, Technical Regulations on Fire Safety Requirements](https://mchs.gov.ru/uploads/document/2022-04-08/c907f456516c1f21009131cfdb944deb.pdf) - clasificación rusa de materiales por riesgo de incendio: inflamabilidad, ignitibilidad, humo, toxicidad, propagación de llamas.
- [DuPont: Styrofoam Brand XPS Product Information Sheet](https://www.dupont.com/content/dam/dupont/amer/us/en/performance-building-solutions/public/documents/en/styrofoam-brand-ultra-sl-pis-43-D100087-enUS.pdf) - ejemplo de descripción técnica de XPS con temperatura máxima de servicio `165°F`.
- [IKO: EPS Insulation in an IKO Roof System](https://www.iko.com/comm/documents/bulletin-eps-insulation-in-an-iko-roof-system/) - ejemplo de limitación de temperatura de funcionamiento de EPS y estabilidad dimensional.
- [Prusa Knowledge Base: Material table](https://help.prusa3d.com/materials) - referencia práctica para la resistencia térmica de materiales populares de impresión 3D.
