# PETG, ABS y ASA

PETG, ABS y ASA son a menudo considerados los siguientes materiales después de PLA, cuando una pieza debe ser no solo bonita sino funcional.

En dispositivos alrededor de una secadora, cámara de impresora o calentador, la elección del material afecta la seguridad. Una pieza puede verse normal después de imprimir, pero después de una hora en una carcasa cálida puede empezar a ablandarse, deformar el conducto de aire, aflojar sujetadores o desplazar un sensor.

## PETG

PETG es a menudo un buen primer material funcional después de PLA.

Típicamente:

- se imprime más fácil que ABS y ASA;
- huele menos durante la impresión;
- se deforma menos;
- maneja la temperatura mejor que PLA;
- funciona bien para muchos soportes, cubiertas, soportes y conductos de aire en condiciones moderadas.

Para dispositivos tipo iDryer, PETG puede funcionar bien para:

- soporte de ventilador alejado del calentador;
- cubierta de electrónica;
- soporte de sensor en una zona de temperatura moderada;
- conducto de aire para aire no demasiado caliente;
- prototipo de carcasa.

Pero PETG no se vuelve automáticamente resistente al calor para cualquier zona caliente.

Si una pieza está cerca de un calentador, en una corriente de aire caliente o bajo carga constante, PETG puede perder gradualmente rigidez y deformarse.

## ABS

ABS es un material más técnico que PLA y PETG.

Típicamente funciona mejor para:

- partes con carga mecánica;
- carcasa en ambiente más cálido;
- soportes donde PETG ya es cuestionable;
- partes necesitando mejor resistencia a la temperatura.

Desventajas de ABS:

- se deforma más;
- requiere una cámara cerrada o ambiente cálido estable durante la impresión;
- huele notablemente;
- puede emitir gases potencialmente dañinos durante la impresión;
- no es adecuado para imprimir en un espacio habitable sin ventilación.

No elijas ABS solo porque "es más fuerte". Necesitas saber cómo imprimirlo. ABS mal impreso con delaminación y estrés interno puede resultar peor que PETG bien impreso.

## ASA

ASA es similar a ABS en propósito, pero a menudo mejor adaptado para partes técnicas y exteriores.

Ventajas de ASA:

- buena resistencia a la temperatura;
- resistencia UV;
- menos olor en comparación con ABS, pero el olor y los humos todavía están presentes;
- típicamente se deforma menos que ABS;
- adecuado para partes técnicas funcionales.

Desventajas:

- también requiere buenas condiciones de impresión;
- para partes grandes, se prefiere una cámara de impresión cerrada;
- posibles gases dañinos durante la impresión;
- material más caro y exigente que PETG.

ASA es a menudo más sensible que ABS para partes que vivirán mucho tiempo en un dispositivo o cerca de ventanas/luz solar. Pero para una pequeña cubierta de electrónica interna, ASA no siempre es necesario.

## Dónde usar cuál material

Una guía aproximada:

| Tarea | PETG | ABS/ASA |
| --- | --- | --- |
| Prototipo frío | funciona | funciona, pero a menudo excesivo |
| Cubierta de electrónica alejada del calor | funciona | funciona |
| Soporte de ventilador en zona moderada | funciona | funciona |
| Conducto de aire cerca de flujo de aire cálido | a veces funciona | a menudo mejor |
| Pieza dentro de cámara caliente | verificar temperatura | a menudo más sensible |
| Soporte cerca de calentador | arriesgado | también requiere verificación, a veces metal es necesario |
| Pieza bajo carga constante en calor | cautelosamente | mejor, pero no automáticamente seguro |
| Pieza cerca de 110-230V AC | el material no es la única respuesta | el material no es la única respuesta |

Esto no es una tabla de permiso. Es solo lógica de inicio.

La solución real depende de temperatura, distancia al calentador, flujo de aire, carga, tiempo de funcionamiento y consecuencias de falla.

## La temperatura de fusión no es el parámetro principal

Para carcasas y soportes, lo que importa no es la temperatura a la que se funde el material.

Más importante es cuándo:

- se ablandará;
- se arrastrará bajo carga;
- perderá forma;
- soltará un tornillo;
- se deformará;
- cambiará de tamaño.

Una pieza puede volverse peligrosa mucho antes de la fusión.

Por ejemplo, un soporte de sensor puede desplazarse solo unos pocos milímetros. Externamente esto parece menor, pero el controlador ya verá la temperatura incorrecta.

## Imprimir ABS/ASA requiere condiciones

ABS y ASA a menudo requieren:

- una cámara cerrada;
- temperatura de cama alta;
- temperatura estable alrededor de la pieza;
- buena adhesión de la cama;
- protección de corrientes de aire;
- ventilación de la sala;
- secado cuidadoso de filamento si es necesario.

Si imprimes ABS/ASA en una impresora abierta, una pieza grande puede deformarse, agrietarse o delaminarse.

Para partes pequeñas, a veces puedes arreglarte sin una cámara cerrada perfecta, pero para una carcasa, conducto de aire o pieza larga, planifica condiciones de impresión adecuadas desde el principio.

## No elijas material separado del diseño

El material es solo parte de la solución.

Incluso un buen material no salvará geometría pobre:

- paredes delgadas;
- postes pequeños para tornillos;
- esquinas internas agudas;
- carga perpendicular a capas;
- montaje pobre a carcasa;
- sin espacio a partes calientes;
- ventilación bloqueada.

Si una pieza sostiene un calentador, conector de potencia o sensor de temperatura, debes pensar no solo en plástico, sino también en soportes metálicos, blindaje, espacios y protección a prueba de fallos.

## Regla práctica

Para un dispositivo simple, puedes pensar así:

- PLA - prototipo, plantilla, pieza decorativa fría.
- PETG - mínimo básico para muchas partes funcionales a temperatura moderada.
- ABS/ASA - mejor para partes más calientes y cargadas mecánicamente, si puedes imprimirlas.
- Metal, fibra de vidrio, cerámica o partes no inflamables listas - donde el plástico cerca del calor ya no es apropiado.

Si la falla de una pieza puede llevar al sobrecalentamiento, cortocircuito o contacto entre cable y pieza caliente, el material debe elegirse con un margen de seguridad grande y probarse en ensamblaje real.

## Errores comunes

- pensar que PETG es completamente resistente al calor;
- imprimir ABS/ASA sin cámara cerrada y obtener delaminación;
- elegir material según consejo de internet sin conocer la temperatura dentro de la carcasa;
- colocar conducto de aire PETG demasiado cerca del calentador;
- usar ABS/ASA en un espacio habitable sin ventilación;
- pensar que cambiar PLA por ASA automáticamente hace el diseño seguro;
- no verificar la pieza después de una hora de operación a temperatura real;
- olvidar que los tornillos y carga pueden deformar plástico con el tiempo.

## Conclusiones clave

- PETG es a menudo un buen mínimo para partes funcionales, pero no para cualquier zona caliente.
- ABS y ASA manejan mejor la temperatura pero son más difíciles de imprimir y requieren ventilación.
- ASA usualmente vence a ABS en resistencia UV y a menudo huele menos, pero requiere cuidado.
- El material se elige según temperatura real, carga y consecuencias de falla.
- Para partes cerca de un calentador, a veces la respuesta correcta no es plástico sino metal o un soporte listo para usar.

## Referencias

- [Base de conocimiento de Prusa: PETG](https://help.prusa3d.com/article/petg_2059) - descripción PETG, impresión, resistencia, resistencia a la temperatura y límites.
- [Base de conocimiento de Prusa: ABS](https://cdn.help.prusa3d.com/article/abs_2058) - propiedades ABS, requisitos de impresión, deformación y advertencia de humos.
- [Base de conocimiento de Prusa: ASA](https://help.prusa3d.com/article/asa_5078) - ASA como material técnico con resistencia a temperatura y UV, más requisitos de cámara cerrada.
- [Bambu Lab: Guía de comparación de filamentos de impresora 3D](https://bambulab.com/en-us/filament-guide) - tabla comparativa de materiales: PLA, PETG, ABS, ASA, PC, PA y compuestos.
- [Bambu Lab: Guía de filamento ASA](https://bambulab.com/en-us/filament/asa) - breve descripción ASA, sus pros, contras y casos de uso.
