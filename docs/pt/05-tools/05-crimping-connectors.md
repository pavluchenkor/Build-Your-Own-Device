# Crimpagem de conectores

Crimpagem é um método para conectar um fio a um terminal ou contacto sem soldar.

Uma boa crimpagem fornece:

- contacto eléctrico;
- retenção mecânica do fio;
- suporte de isolamento;
- repetibilidade;
- montagem e manutenção convenientes.

Uma crimpagem pobre pode aquecer, separar-se, causar erros aleatórios e parecer quase normal.

## Por que a crimpagem é frequentemente melhor que a soldadura

Para conectores e terminais, a crimpagem é frequentemente melhor que a soldadura porque:

- o fio permanece flexível;
- o contacto é projectado pelo fabricante;
- o isolamento é retido;
- a junta melhor lida com vibração;
- o conector pode ser desmontado e reparado;
- sem risco de derreter o corpo do conector de plástico durante a soldadura.

A solda é boa para almofadas e fios, mas não deve substituir um contato protetor num conector se o fabricante pretender crimpagem.

## Tipos de terminais e conectores

Em dispositivos simples você frequentemente encontra:

- Dupont - conexões de sinal fraco para breadboards;
- JST-XH/JST-PH e similares - sensores, ventiladores, pequenos módulos;
- ferrules - pontas para fio multi-filamento em terminais de parafuso;
- Faston - terminais planos para algumas conexões de alimentação;
- terminais de anel e pá;
- terminais de parafuso;
- blocos de terminais montados em placa.

Cada tipo requer o seu próprio contacto, a sua própria bitola de fio e a sua própria ferramenta.

## Você precisa da ferramenta certa

Alicates não são uma ferramenta de crimpagem.

Você pode apertar um contacto para que pareça reter, mas não obterá uma crimpagem apropriada.

Para boa crimpagem, você precisa:

- um terminal para a bitola de fio correcta;
- comprimento de descascamento correcto;
- matriz de ferramenta correcta;
- posição de contacto correcta na matriz;
- zonas separadas para crimpagem de filamento e isolamento;
- sem filamentos danificados.

Os fabricantes profissionais de conectores fornecem especificações de crimpagem, altura de crimpagem, comprimento de descascamento e força de tração. Para montagem DIY você nem sempre tem controlo total, mas o princípio é o mesmo: contacto, fio e ferramenta devem corresponder um ao outro.

## Crimpagem de barril aberto

Muitos contactos pequenos, como JST ou Dupont, têm dois pares de "abas":

- um par crimpa o condutor nu;
- o outro par segura o isolamento.

Bom resultado:

- o condutor é visível na zona correcta;
- o isolamento é mantido pelas abas traseiras;
- o comprimento exposto não é demasiado longo;
- os filamentos do condutor não saem;
- o contacto não está enviesado;
- o contacto entra no corpo do conector e bloqueia no lugar.

Se o isolamento entrou na zona de crimpagem do condutor, o contacto eléctrico será pobre.

Se apenas o condutor for crimpado e o isolamento não for retido, o fio pode quebrar quando movido.

## Ferrules

Para fio multi-filamento num terminal de parafuso, ferrules são frequentemente úteis.

Elas:

- reúnem todos os filamentos juntos;
- impedem que os filamentos se separem;
- melhoram o assento no terminal;
- reduzem risco que alguns filamentos fiquem de fora;
- tornam a junta mais limpa.

Isto é especialmente útil para fios de alimentação, blocos de terminais e montagens que serão reparadas.

Mas ferrules também devem corresponder à bitola do fio e serem crimpadas com a matriz certa.

## Como verificar uma crimpagem

Após crimpagem, verifique:

- o contacto não se move no fio;
- o isolamento é retido;
- o condutor não se solta;
- nenhum filamento é cortado;
- o comprimento exposto não é demasiado longo;
- o contacto entra no corpo do conector;
- o bloqueio clica no lugar;
- o fio suporta puxão gentil.

Um teste de puxão gentil é útil: puxe cuidadosamente o fio. Não deve sair do contacto.

Não há necessidade de puxar com toda a sua força. O objectivo é encontrar crimpagens obviamente más antes da instalação.

## Por que crimpagens pobres aquecem

Uma crimpagem pobre cria alta resistência.

Sob corrente isto se torna calor.

Primeiro o terminal pode apenas estar morno. Depois o plástico escurece, o contacto fica pior, o calor aumenta.

Isto é especialmente perigoso para:

- aquecedores;
- ventiladores com corrente significativa;
- tiras LED;
- fontes de alimentação;
- circuitos SSR/MOSFET;
- conexões de rede.

Se um terminal fica quente, desligue a energia e refaça a conexão.

## Dupont não é para energia

Dupont é conveniente para breadboards e sinais fracos.

Mas não pode ser usado como um conector de energia apropriado para:

- um aquecedor;
- alimentação do dispositivo;
- uma tira LED poderosa;
- peças de rede;
- um motor ou servo com corrente grande.

Mesmo que o conector se encaixe fisicamente nos pinos, isso não significa que é classificado para a corrente, vibração e calor necessários.

## Erros comuns

- crimpado com alicates;
- escolheu o terminal de bitola errada;
- descascou isolamento demasiado;
- descascou isolamento demasiado pouco;
- crimpou isolamento em vez do condutor;
- não crimpou o suporte de isolamento;
- cortou alguns filamentos;
- o contacto não bloqueou no corpo;
- linha de energia mantida em Dupont;
- ferrule de bitola errada;
- não fez teste de puxão;
- terminal fica quente mas dispositivo continua funcionando.

## Os essenciais

- Crimpagem é tanto contacto eléctrico como retenção mecânica.
- Contacto, fio e ferramenta devem corresponder um ao outro.
- Alicates não substituem uma ferramenta de crimpagem.
- Para fio multi-filamento num terminal de parafuso, ferrules são frequentemente úteis.
- Crimpagens pobres podem aquecer e ser perigosas.
- Peças de energia não devem depender de conectores fracos de breadboard.

## Materiais de referência

- [Molex: Quality Crimp Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/commercialcrimpbookpdf/638/63800/TM-638000029-001.pdf?inline=) - referência detalhada de qualidade de crimpagem, força de tração, crimpagem de condutor e isolamento.
- [Molex: Industrial Crimp Quality Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/industrialcrimpbookpdf/640/64016/TM-640160065-001.pdf?inline=) - inspecção visual de crimpagem de barril aberto e fechado, comprimento de descascamento, escova de fio e defeitos comuns.
- [JST: Application Tooling Guide, Crimp Style](https://www.jst.com/resources/application-tooling-guide/crimp-style/) - exemplo de como contactos JST específicos precisam de ferramentas específicas, comprimento de descascamento e especificações de tensão.
- [American Electrical: Wire Ferrules](https://www.americanelectrical.com/wire-ferrules/) - por que ferrules são úteis para fio multi-filamento em blocos de terminais.
- [TE Connectivity: Wire Splices](https://www.te.com/en/products/terminals-splices/splices.html) - tipos de conexão industrial de crimpagem/emenda e por que crimpagem é projectada separadamente, não aleatoriamente.
