# Materiales resistentes al calor

Para partes cerca del calor, lo que importa no es la etiqueta "resistente al calor" sino el comportamiento real del material en tu diseño específico.

Una pieza puede no derretirse, pero ya puede:

- ablandarse;
- doblarse;
- arrastrarse bajo un tornillo;
- cambiar de tamaño;
- perder rigidez;
- aflojar sujetadores;
- desplazar un sensor;
- bloquear el flujo de aire.

Por lo tanto, "temperatura de fusión" casi nunca es el parámetro principal para una carcasa, soporte o conducto de aire.

## Qué se considera una zona caliente

Una zona caliente no es solo donde se sienta el calentador.

En un dispositivo casero, las áreas calientes pueden incluir:

- corriente de aire después del calentador;
- pared cerca del calentador;
- punto de montaje del termistor;
- conducto de aire;
- área sobre la fuente de alimentación;
- ubicación cerca de un SSR o MOSFET con disipador de calor;
- cámara cerrada que se calienta completamente.

Si una pieza está en tal zona, el material se elige con margen y se prueba en ensamblaje real.

## Temperatura de trabajo, no de fusión

La fusión ya es una etapa tardía del problema.

Para una pieza impresa, lo que es más importante:

- a qué temperatura pierde rigidez;
- si hay carga;
- cuántas horas funcionará;
- ¿hay flujo de aire caliente?
- ¿hay vibración?
- ¿sostiene un tornillo o clip?
- qué sucede si se deforma.

Un soporte de sensor puede volverse peligroso incluso antes de falla visible. Si el sensor se mueve lejos de la superficie, el controlador puede continuar calentando porque lee la temperatura incorrecta.

## Opciones básicas

Una jerarquía aproximada de materiales:

- PLA - para prototipos fríos y partes decorativas alejadas del calor.
- PETG - opción básica para temperaturas moderadas y partes funcionales simples.
- ABS/ASA - mejor para partes más cálidas y cargadas mecánicamente, si tienes condiciones de impresión.
- PA/nylon - material técnico resistente, pero altamente dependiente de humedad y condiciones de impresión.
- PC/policarbonato - material más resistente al calor y fuerte, pero difícil de imprimir.
- Compuestos con relleno de carbono o vidrio - pueden ser más rígidos y estables, pero requieren boquilla adecuada y entendimiento de propiedades.
- Metal, fibra de vidrio, cerámica o partes listas resistentes al calor - donde el plástico ya no es apropiado.

Esto no es un ranking "mejor-peor". Es una lista de opciones con diferentes complejidad, costo y riesgos.

## PETG

PETG funciona para muchas partes en una zona de temperatura moderada:

- cubiertas de electrónica;
- soportes de ventilador;
- soportes de sensor de temperatura alejados del calentador;
- conductos de aire para flujo moderado;
- elementos de carcasa sin seguridad crítica.

Pero PETG puede ablandarse y arrastrarse bajo carga. Si una pieza sostiene un calentador, terminal de potencia o sensor de seguridad, PETG debe usarse muy cuidadosamente.

## ABS y ASA

ABS y ASA típicamente funcionan mejor en zonas más calientes que PETG.

Se consideran para:

- carcasa de cámara;
- conductos de aire;
- soportes en ambiente cálido;
- partes técnicas;
- partes que deben retener forma más tiempo.

Pero tienen un precio:

- más difícil de imprimir;
- deformación;
- olor;
- posiblemente gases dañinos;
- preferentemente impreso en cámara cerrada;
- requiere ventilación.

ASA a menudo se prefiere para partes donde resistencia UV y durabilidad importan. ABS puede ser más barato y disponible.

## PA / Nylon

PA, o nylon, se usa para partes técnicas con carga mecánica.

Ventajas:

- alta resistencia al impacto;
- buena resistencia al desgaste;
- baja fricción;
- buena resistencia mecánica;
- algunas variantes tienen buena resistencia a la temperatura.

Desventajas:

- absorbe humedad fuertemente;
- requiere secado;
- puede deformarse;
- difícil de imprimir;
- requiere superficie y condiciones correctas.

El nylon mojado se imprime mal: burbujas, silbidos, mala superficie y baja resistencia resultan. Para una cubierta de carcasa simple, nylon es generalmente excesivo.

## PC / Policarbonato

El policarbonato se considera cuando necesitas alta resistencia e resistencia a la temperatura.

Ventajas:

- alta resistencia al impacto;
- alta resistencia a la temperatura;
- buena rigidez;
- adecuado para partes funcionales.

Desventajas:

- difícil de imprimir;
- temperatura alta de boquilla y cama;
- propenso a deformación;
- necesita ambiente cálido estable;
- no todas las impresoras son adecuadas.

PC no es un material "principiante". Si la impresión es inestable, una pieza puede verse normal pero tener pobre resistencia entre capas.

## Compuestos

Los filamentos compuestos contienen rellenos: fibra de carbono, fibra de vidrio, Kevlar u otro material.

Pueden proporcionar:

- mayor rigidez;
- menor deformación;
- mejor estabilidad dimensional;
- buena superficie técnica.

Pero no hacen el plástico base mágicamente no inflamable o completamente resistente al calor.

Importante:

- el relleno de carbono desgasta boquillas de latón;
- se necesita boquilla endurecida o adecuada;
- el compuesto puede ser más frágil;
- las propiedades dependen del material específico, no solo de las letras `CF` en el nombre.

## Cuándo el plástico no funciona

Para algunas ubicaciones, el material correcto no es plástico impreso.

Mejor considerar metal, fibra de vidrio, cerámica o partes industriales listas para:

- soporte del calentador;
- zona de calor directo;
- contacto con terminal de potencia;
- montaje de cable de mains;
- barrera mecánica entre 110-230V AC y usuario;
- lugar donde la deformación de pieza podría llevar a fuego o choque eléctrico.

Una pieza impresa puede sostener forma de carcasa, pero no debería ser la única protección de falla peligrosa.

## Cómo elegir material

Antes de elegir un material, responde:

1. ¿Cuál es la temperatura máxima en la ubicación de instalación?
2. ¿Cuánto tiempo funcionará la pieza a esta temperatura?
3. ¿Hay carga mecánica?
4. ¿Hay tornillos, clips o compresión constante?
5. ¿Hay calentador, SSR, MOSFET, fuente de alimentación o 110-230V AC cerca?
6. ¿Qué sucede si la pieza se deforma?
7. ¿Puedes reemplazar el plástico con metal o un soporte listo?

Si la consecuencia de falla es seria, no quieres "el plástico más conveniente" sino un diseño con margen y protección independiente.

## Errores comunes

- mirar solo temperatura de fusión;
- pensar que PETG es seguro al lado de cualquier calentador;
- usar PLA en una cámara cerrada caliente;
- imprimir PC/nylon sin impresora adecuada y obtener pieza débil;
- elegir compuesto solo por el marcado cool `CF`;
- colocar pieza de plástico directamente al lado de un terminal de potencia;
- no verificar la pieza después de calentamiento extendido;
- olvidar sobre carga de tornillo y fluencia de material;
- no contabilizar que una carcasa cerrada se calienta completamente.

## Conclusiones clave

- La temperatura de trabajo es más importante que la temperatura de fusión.
- Una pieza puede volverse peligrosa antes de falla visible.
- PETG es una opción básica para zona moderada, no protección universal de calor.
- ABS/ASA manejan mejor el calor pero requieren condiciones de impresión y ventilación.
- Nylon y PC son materiales técnicos para usuarios experimentados y equipamiento adecuado.
- En ubicaciones calientes y que soportan carga, metal o un soporte listo resistente al calor es a menudo mejor.

## Referencias

- [Base de conocimiento de Prusa: Guía de materiales](https://help.prusa3d.com/category/material-guide_220) - catálogo integral de Prusa de materiales con PLA, PETG, ABS, ASA, PC, Nylon y compuestos.
- [Base de conocimiento de Prusa: Policarbonato](https://help.prusa3d.com/article/polycarbonate-pc_165812) - propiedades PC, alta resistencia a la temperatura y dificultad de impresión.
- [Base de conocimiento de Prusa: Poliamida / Nylon](https://help.prusa3d.com/article/polyamide-nylon_167188) - nylon como material técnico, absorción de humedad, secado y requisitos de impresión.
- [Bambu Lab: Guía de comparación de filamentos de impresora 3D](https://bambulab.com/en-us/filament-guide) - comparación de materiales por resistencia al calor, resistencia, absorción de humedad y necesidades de secado.
- [Base de conocimiento de Prusa: Poste guía de carcasa](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - por qué una cámara cerrada es importante para materiales que se deforman durante enfriamiento.
