# IR-Tracker
il progetto mira alla creazione di un sistema che permetta ad una webcam/microfono di tracciare un oggetto, montandolo sopra ad una base girevole.

## HW
per quanto riguarda l'hardware ho utilizzato un arduino UNO per la disponibilità di un numero adeguato di porte
Analogiche in ingresso (6 a cui ho collegato 6 sensori). avendo poi scelto di utilizzare un servomotore non alimentabile direttamente dall'alimentazione fornita dall'Arduino ho scelto di utilizzare un alimentatore da laptop in combinazione con uno step-down-converter che mi permette così di alimentare sia l'arduino che il servomotore senza problemi.

i sensori sono collegati in maniera molto semplice con il seguente schema (uno per sensore):

mentre l'emettitore è per questioni prototipali collegato a 5v e al ground della breadboard a cui è collegato il resto del circuito ma ovviamente si può alimentare con un'alimentazione esterna non avendo logica, come ad esempio una batteria.
## SW
per quanto riguarda il SW il programma è abbastanza semplice, viene fatta la lettura dei sei sensori ricevendo quindi sei valori che vanno da 0 a 1023 rappresentando 0 un perfetto allineamento del sensore alla sorgente IR mentre 1023 un disallineamento massimo (sorgente ostruita).

prese queste misurazioni allora calcolo l'offset da applicare al servomotore per centrare la sorgente tra i vari sensori.

per calcolare l'offset la strategia è la seguente:
- calcolo il sensore con la lettura minima
- se esiste un sensore con una lettura minore degli altri allora controllo che la differenza massima sia maggiore di 200
- a questo punto utilizzo la funzione map per mappare l'intervallo da 0 a 5 (rappresentante i 6 sensori) a -10, 10 (rappresentante invece gli offset massimi)

l'offset viene poi scritto sul servo e si aspetta un certo delay perchè arrivi in posizione.

ho inserito la soglia di 200 per fungere da "zona morta", ed evitare oscillazioni causate da fattori esterni o letture molto vicine.

## problematiche affrontate
ho affrontato soprattuto la problematica dell'evitare oscillazioni. per sistemare qusto problema mi sono in un primo momento andando a testare diverse funzioni per calcolare l'offset, tentando di utilizzare un sistema closed loop con il calcolo dell'errore. ho poi sviluppato una soluzione che si basava invece sulla modifica hardware, per avere un numero pari di sensori che fossero specchiati. in questo modo avrei potuto calcolare la differenza tra i due sensori gemelli ai due lati e tramite una formula ricavare l'offset da applicare. anche questa soluzione, nonostante i risultati fossero migliori di quella precedente, non ha dato i frutti sperati e le oscillazioni quando la sorgente era quasi centrata rimanevano e rendevano inutilizzabile alle volte il progetto ai fini preposti. ho quindi sviluppato la versione finale che è più semplice sia logicamente che a livello di calcoli basandosi sul calcolo del sensore con la lettura minima.

ho affrontato poi la problematica dell'alimentazione del servomotore, che è per scelte legate all'ambito applicativo sovradimensionato per il prototipo. non avendo mai provato personalmente ad affrontare questo tipo di problematiche è stato interessante capire come affrontare il problema. orginariamente mi ero deciso su una batteria agli ioni di litio per l'alimentazione ma dopo diversi test ho scelto lo schema di alimentazione finale con un alimentatore per PC portatili.

l'ultima problematica che ho affrontato riguarda il form factor del tutto, dato che deve essere nel mio immaginario trasportabile senza troppe problematiche la circuiteria deve essere protetta e non deve esserci nulla di troppo esposto. per questo ho cercato di realizzare riciclando un portapenne in legno un "case" nel quale inserire poi tutta la circuiteria e lasciare esternamente soltanto il servomotore e la piattaforma mobile. per poter accedere facilmente alla scheda e alla breadboard ho poi incollato un supporto di balsa che regge la scheda che si va ad incastrare all'interno del guscio di legno. 