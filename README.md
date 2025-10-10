# IoT OCRE Renode su LiteX VexRiscv

Questo progetto è una simulazione IoT in cui utilizzo **Renode** per emulare una board RISC-V (`litex_vexriscv`) ed eseguire il runtime **OCRE** su **Zephyr 3.7**.  
L’obiettivo è ricevere moduli **.wasm** da un server tramite **TCP/UDP**, verificarne l’integrità (es. HMAC/SHA-256) ed eseguirli con OCRE.

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

---

## Scelta della board

Per questo progetto ho scelto la LiteX VexRiscv, una board RISC-V supportata sia da Zephyr che da Renode.

- Supporto Renode: ✔️ (presente in `platforms/boards/litex_vexriscv.repl`)
- Supporto Zephyr: ✔️ (`west build -b litex_vexriscv`)
- Supporto OCRE: ❌ *non ancora disponibile*

Attualmente, OCRE supporta solo due board ufficiali (come indicato nel sito e nel repository ufficiale):

- `native_sim`, usata solo per test
- `B-U585I-IOT02A`, discovery kit prodotto da STMicroelectronics (non supportata da Renode)

Tuttavia, OCRE fornisce una guida per aggiungere il supporto a nuove board:  
→ [Guida OCRE board support](https://docs.project-ocre.org/board-support/)

---

## Connessione tra host e board emulata (Renode)

L’obiettivo è permettere al server locale (host) di comunicare con la board emulata in Renode, per inviare moduli WebAssembly.  
Renode consente di simulare connessioni Ethernet tramite switch virtuali e interfacce TAP.  
→ [Guida Renode Networking](https://renode.readthedocs.io/en/latest/networking/wired.html)

### Configurazione TAP su host Linux

Creazione interfaccia TAP:
```bash
sudo ip tuntap add dev tap0 mode tap user $USER
sudo ip link set tap0 up
sudo ip addr add 192.168.100.1/24 dev tap0
```

Verifica stato:
```bash
ip addr show tap0
```

### Configurazione in Renode (.repl)

Nel file `.resc` personalizzato ho definito:

- Creazione di uno switch virtuale
- Aggiunta dell’interfaccia TAP allo switch
- Connessione della periferica Ethernet della board allo switch

Esempio semplificato:
```renode
emulation CreateSwitch "sw0"
emulation CreateTap "tap0" "sw0"
connector Connect sysbus.eth sw0
```

### Configurazione IP statico su Zephyr (.conf)

Nel file `litex_vexriscv.conf`:
```conf
CONFIG_NET_CONFIG_SETTINGS=y
CONFIG_NET_CONFIG_MY_IPV4_ADDR="192.168.100.10"
CONFIG_NET_CONFIG_MY_IPV4_NETMASK="255.255.255.0"
CONFIG_NET_CONFIG_MY_IPV4_GW="192.168.100.1"
```

**Riepilogo indirizzi:**

- Board → `192.168.100.10/24`  
- Host  → `192.168.100.1/24`

---

## Test di comunicazione con Echo Server (Zephyr)

Per verificare la connessione ho compilato e avviato il sample `echo_server` fornito da Zephyr per la board `litex_vexriscv`.

### Lato host

- Interfaccia `tap0` visibile e funzionante
- Pacchetti ICMP/TCP inviati correttamente (verificato con `ping` e `tcpdump`)

### Lato board (Renode)

- Echo server in esecuzione
- IP statico correttamente impostato

---

### Problema riscontrato

- I pacchetti inviati dall’host **non vengono ricevuti dalla board**
- L’echo server **non risponde**, e i pacchetti risultano **persi**

---

### Conclusione

- La configurazione TAP lato host sembra corretta
- Il problema sembra lato board, probabilmente nella configurazione della periferica Ethernet (`LiteX_Ethernet`)
- Potrebbe trattarsi di:
  - Mancata inizializzazione del driver
  - Problema di compatibilità tra Zephyr e il modello Ethernet di Renode

---
