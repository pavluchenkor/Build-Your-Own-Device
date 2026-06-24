# Impresión 3D

Esta sección no es un curso de impresión 3D.

Tiene un propósito diferente: ayudar a entender qué partes impresas se pueden usar con seguridad en un dispositivo casero, y cuáles se convierten en un riesgo cerca de calentadores, electrónica, cableado y piezas móviles.

En proyectos tipo iDryer, la impresión 3D se usa típicamente para:

- carcasas;
- cubiertas;
- conductos de aire;
- soportes de ventiladores;
- soportes de sensores;
- guías;
- asas y clips;
- paneles decorativos o de servicio.

Imprimir una pieza es fácil. Hacerla funcionar con seguridad en una carcasa cálida durante meses es más difícil.

## Preguntas clave

Antes de imprimir una pieza para un dispositivo, debes responder no solo "¿el STL cabe en el cortador?", sino varias preguntas:

- dónde se ubicará la pieza;
- qué temperatura habrá allí;
- ¿hay un calentador cerca?
- ¿hay 110-230V AC cerca?
- ¿la pieza aguantará una carga?
- ¿entrará en contacto con cables?
- ¿dirigirá aire caliente?
- ¿se puede reemplazar o reparar?
- qué sucede si se deforma.

Si la deformación de una pieza puede desplazar un sensor, bloquear el flujo de aire, acercar un cable a una zona caliente o aflojar el montaje del calentador, ya no es solo un "defecto cosmético".

## STL no es una instrucción de montaje

STL describe la forma de una pieza, pero no te dice:

- de qué material imprimirla;
- en qué orientación imprimirla;
- cuántas paredes usar;
- qué relleno aplicar;
- dónde se necesitan soportes;
- qué tornillos usar;
- qué temperatura aguantará la pieza;
- en qué dirección será más débil.

El mismo modelo puede ser una cubierta normal o un mal soporte estructural dependiendo del material, la orientación y las condiciones de trabajo.

Por lo tanto, una pieza que funcione necesita no solo un STL, sino también contexto: material, configuración de impresión, ubicación de instalación, carga y régimen de temperatura.

## El material es más importante que la apariencia

Para un prototipo, PLA a menudo funciona. Se imprime fácilmente y produce una pieza de buen aspecto.

Pero para partes cerca del calor, PLA es una mala opción. El problema no es que se derrita inmediatamente, sino que puede perder gradualmente rigidez y forma a temperaturas encontradas en una carcasa cerrada o cerca de un calentador.

Para partes de trabajo alrededor de un secador, cámara o calentador, típicamente se consideran:

- ABS;
- ASA;
- materiales de ingeniería más resistentes al calor, si tienes experiencia y una impresora adecuada.

El material se elige según las condiciones:

- temperatura de trabajo;
- rigidez;
- resistencia al impacto;
- contracción y deformación;
- olor y emisiones durante la impresión;
- comportamiento cuando se calienta;
- documentación del fabricante.

## Temperatura dentro de una carcasa

La temperatura dentro de una carcasa cerrada difiere de la temperatura ambiente.

Incluso si el calentador no toca el plástico, una pieza puede estar:

- en la corriente de aire caliente;
- cerca del calentador;
- cerca de un disipador de calor;
- cerca de la fuente de alimentación;
- en un área con poca ventilación;
- en una pared que se calienta lentamente.

Por lo tanto, no puedes evaluar la seguridad solo con la frase "la pieza no toca el calentador". Necesitas entender qué temperatura habrá en esa ubicación durante la operación prolongada.

![Zonas en una carcasa impresa para un dispositivo calentado](../../img/07-3d-printing/01-printed-device-zones.svg)

## La resistencia depende de la dirección de las capas

Las partes FDM no tienen la misma resistencia en todas las direcciones.

La dirección de las capas afecta cómo se rompe una pieza:

- a lo largo de las líneas de plástico generalmente es más resistente;
- entre capas a menudo es más débil;
- los postes y clips delgados pueden romperse entre capas;
- los tornillos pueden delaminarse una pieza si la geometría no está diseñada para ello.

Para soportes estructurales, es importante pensar en dónde irá la carga.

Si un soporte de ventilador simplemente cuelga de una pared, eso es una cosa. Si un soporte sostiene un calentador o un eje de carrete, la orientación de impresión y el grosor de la pared se vuelven importantes.

## La carcasa debe ser reparable

Una buena carcasa no es solo una caja bonita.

Debe permitir:

- acceso a terminales;
- reemplazo de un ventilador;
- inspección de un sensor de temperatura;
- apriete de sujetadores;
- extracción de un controlador;
- reemplazo de un cable;
- ver si algo se ha sobrecalentado u oscurecido.

Si necesitas desmontar medio dispositivo para acceder a un fusible o terminal, será reparado menos a menudo. Esta es una mala práctica de ingeniería.

## La pieza impresa no debe comprometer la seguridad

Una carcasa impresa puede ser útil, pero no debe convertir un error pequeño en una situación peligrosa.

Malos escenarios:

- el soporte del calentador se ablandó;
- el conducto de aire se deformó y el flujo a través del calentador disminuyó;
- el soporte del termistor se desplazó;
- el cable se rozó contra un borde afilado;
- el terminal terminó apretado contra el plástico;
- la cubierta bloqueó la ventilación de la fuente de alimentación;

Para zonas calientes y que soporten carga, es mejor pensar de esta manera: si una pieza impresa se deforma, el dispositivo debe permanecer seguro o entrar en un estado de error, no continuar calentando ciegamente.

## Qué habrá en esta sección

La sección cubre varios temas prácticos:

- `02-what-is-stl.md` - por qué STL no contiene material, orientación, resistencia o instrucciones de montaje.
- `03-materials-petg-abs-asa.md` - opciones básicas entre PETG, ABS y ASA.
- `04-heat-resistant-materials.md` - cómo pensar en partes cerca del calor.
- `05-enclosure-design.md` - zonas de carcasa, ventilación, sujeción, acceso y cableado.
- `06-why-pla-is-risky.md` - por qué PLA es conveniente para prototipos pero arriesgado cerca del calor.

## Qué esta sección no hace

No habrá un curso completo de impresión 3D aquí.

No nos sumergiremos en:

- todos los plásticos del mundo;
- configuración de retracción;
- post-procesamiento decorativo;
- modelos artísticos;
- calibración perfecta de impresora;
- selección de marca específica de filamento.

El enfoque es simple: las partes para un dispositivo real deben ser suficientemente resistentes, resistentes al calor, reparables y seguras.

## Conclusiones clave

- STL es solo geometría, no instrucciones de montaje seguro.
- El material se elige según la temperatura de trabajo y la carga, no la apariencia.
- PLA es conveniente para prototipos pero arriesgado cerca del calor.
- La orientación de impresión afecta la resistencia.
- La carcasa debe separar la zona caliente, la electrónica, el cableado de potencia y la zona del usuario.
- Una pieza impresa no debe ser lo único que proteja la seguridad del dispositivo.

## Referencias

- [Base de conocimiento de Prusa: Guía de materiales](https://help.prusa3d.com/category/material-guide_220) - descripción general de materiales populares, condiciones de impresión y propiedades.
- [Base de conocimiento de Prusa: PLA](https://help.prusa3d.com/article/pla_2062) - descripción de PLA como material simple para prototipos y partes sin carga de temperatura alta.
- [Base de conocimiento de Prusa: Poste guía de carcasa](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - por qué se necesita una cámara de impresión cerrada y cómo la temperatura ambiente afecta la impresión y los materiales.
- [Bambu Lab: Guía de comparación de filamentos de impresora 3D](https://bambulab.com/en-us/filament-guide) - tabla comparativa de materiales, incluyendo PLA, PETG, ABS, ASA y plásticos de ingeniería.
- [Makelab: ¿Es la impresión 3D lo suficientemente fuerte para partes funcionales?](https://help.makelab.com/help/article/is-3d-printing-strong-enough-for-functional-parts) - notas prácticas sobre material, orientación de impresión, paredes, relleno y partes funcionales.
