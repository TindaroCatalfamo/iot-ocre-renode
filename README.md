# IoT OCRE Renode su LiteX VexRiscv

Questo progetto è una simulazione IoT in cui utilizzo **Renode** per emulare una board RISC-V (`litex_vexriscv`) ed eseguire il runtime **OCRE** su **Zephyr 3.7**.  
L’obiettivo è: ricevere moduli **.wasm** da un server tramite **TCP/UDP**, verificarne l’integrità (es. HMAC/SHA-256) ed eseguirli con OCRE.

---

## Preparazione dell’ambiente

Per poter avviare l’ambiente completo servono i seguenti tools:

- **Renode**  
  → Guida ufficiale: [Renode docs](https://renode.readthedocs.io)  

- **Zephyr RTOS**  
  → Guida: [Zephyr getting started](https://docs.zephyrproject.org/3.7.0/getting_started/index.html)

- **Zephyr SDK**  
  → [Guida installazione Zephyr SDK](https://docs.zephyrproject.org/3.7.0/develop/getting_started/index.html)

- **OCRE Runtime**  
  → [Guida ufficiale OCRE](https://docs.project-ocre.org/overview/) 
  → [Repository GitHub ufficiale OCRE](https://github.com/project-ocre/ocre-runtime) 
  
  
## Scelta della board

Per questo progetto ho scelto la LiteX VexRiscv, una board RISC-V supportata sia da Zephyr che da Renode.

- Supporto Renode: ✔️ (presente in platforms/boards/litex_vexriscv.repl)

- Supporto Zephyr: ✔️ (west build -b litex_vexriscv)

- Supporto OCRE: ❌ non ancora disponibile

OCRE attualmente supporta solo due board ufficiali ( esplicitamente citato nel sito ufficiale e nel repo), tra queste due board troviamo:
- native_sim, usata solo per test.

- board B-U585I-IOT02A è una scheda di sviluppo/valutazione (discovery kit) prodotta da STMicroelectronics, non supportata per Renode.

Tuttavia, il progetto OCRE fornisce una guida su come aggiungere il supporto per una nuova board:

→ Guida: https://docs.project-ocre.org/board-support/

## Connessione tra host e board emulata (Renode)

L’obiettivo è permettere al server locale (host) di comunicare con la board emulata in Renode, per inviare moduli WebAssembly.
Renode consente di simulare connessioni Ethernet tramite switch virtuali e interfacce TAP (https://renode.readthedocs.io/en/latest/networking/wired.html)


Ho creato un’interfaccia TAP sul mio host Linux con indirizzo statico:

Ho creato un interfaccia **TAP** sull’host:
  ```bash
  sudo ip tuntap add dev tap0 mode tap user $USER
  sudo ip link set tap0 up
  sudo ip addr add 192.168.100.1/24 dev tap0
 
Successivamente ho subito controllato se fosse attiva e funzioante

  ```bash ip addr show tap0` → conferma indirizzo e stato UP
  
Ho creato un file .repl personalizzato per la board LiteX VexRiscv, in cui ho definito:

- Creazione di uno switch virtuale

- Aggiunta di un’interfaccia TAP collegata allo switch

- Connessione della periferica Ethernet della board allo switch

Esempio semplificato del mio file .repl:

 ```bash emulation CreateSwitch "sw0"
    emulation CreateTap "tap0" "sw0"
    connector Connect sysbus.eth sw0

Inoltre, nel file di configurazione .conf (litex_vexriscv.conf), ho assegnato un IP statico alla board:

 ```bash CONFIG_NET_CONFIG_SETTINGS=y
         CONFIG_NET_CONFIG_MY_IPV4_ADDR="192.168.100.10"
         CONFIG_NET_CONFIG_MY_IPV4_NETMASK="255.255.255.0"
         CONFIG_NET_CONFIG_MY_IPV4_GW="192.168.100.1"


In questo modo:

Board → 192.168.100.10/24

Host → 192.168.100.1/24
  
  

## Test di comunicazione con Echo Server (Zephyr)

Per verificare la connessione ho compilato e avviato il sample “echo_server” fornito da Zephyr per la board litex_vexriscv.

**Lato host**

- Interfaccia tap0 visibile e funzionante

- Pacchetti ICMP/TCP inviati correttamente (verificato con ping e tcpdump)

**Lato board (Renode)**

- Echo server in esecuzione

- IP statico correttamente impostato

**Problema riscontrato**

- I pacchetti inviati dal host vengono spediti ma non ricevuti dalla board.

- L’echo server non risponde, e i pacchetti risultano persi.

**Conclusione**

- Lato host, la configurazione TAP sembra essere corretta.

- Il problema sembra essere lato board, probabilmente nella configurazione della periferica Ethernet (LiteX_Ethernet).
Potrebbe trattarsi di una mancata inizializzazione del driver o di un problema di compatibilità tra Zephyr e il modello Renode.
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

