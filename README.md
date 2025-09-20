# IoT OCRE Renode su LiteX VexRiscv

Questo progetto è una simulazione IoT in cui utilizzo **Renode** per emulare una board RISC-V (`litex_vexriscv`) ed eseguire il runtime **OCRE** su **Zephyr 3.7**.  
L’obiettivo è: ricevere moduli **.wasm** da un server tramite **TCP/UDP**, verificarne l’integrità (es. HMAC/SHA-256) ed eseguirli con OCRE.

---

##  Installazione e setup

### Renode
- Guida ufficiale: [Renode docs](https://renode.readthedocs.io)  
- Installato in modalità **portable** in `~/renode_portable`.

### Zephyr SDK
- Guida: [Zephyr SDK releases](https://github.com/zephyrproject-rtos/sdk-ng/releases)  
- Versione installata: **0.16.8**

### Zephyr RTOS
- Guida: [Zephyr getting started](https://docs.zephyrproject.org/3.7.0/getting_started/index.html)  
- Workspace separato `~/ocre-ws` con Zephyr **3.7.0** (LTS).

### OCRE Runtime
- Guida: [OCRE Quickstart (simulated)](https://docs.project-ocre.org/quickstart/firmware/simulated/)  
- Repo ufficiale: [project-ocre/ocre-runtime](https://github.com/project-ocre/ocre-runtime)  
- Verificato funzionante su `native_sim`.  
- Porting in corso su board `litex_vexriscv` in Renode.

---

##  Board emulata: LiteX VexRiscv

- Documentazione Zephyr: [LiteX VexRiscv board](https://docs.zephyrproject.org/3.7.0/boards/enjoydigital/litex_vexriscv/doc/index.html)  
- Documentazione OCRE board-support: [Adding board support](https://docs.project-ocre.org/board-support/adding-support/ocre-runtime/)

Renode fornisce già una descrizione della board `arty_litex_vexriscv.repl` che include:
- CPU VexRiscv
- Periferiche base LiteX
- Controller Ethernet (`sysbus.eth`)

---

## Configurazione rete host ↔ board

- 1) Creata interfaccia **TAP** sull’host:
  ```bash
  sudo ip tuntap add dev tap0 mode tap user $USER
  sudo ip link set tap0 up
  sudo ip addr add 192.168.100.1/24 dev tap0
  
- 2) Configurato renode con **switch virtuale**:
  ```bash
  emulation CreateSwitch "sw0"
  connector Connect sysbus.eth sw0
  emulation CreateTap "tap0" "sw0"

- 3) Assegnato IP statico alla board (192.168.100.10/24) tramite litex_vexriscv.conf.


### Test con Echo Server Zephyr

- Ho compilato e avviato il sample **echo_server** di Zephyr per la board `litex_vexriscv`.
- Ho configurato la rete con IP statico `192.168.100.10/24` (board) ↔ `192.168.100.1/24` (host).
- Lato host:
  - L’interfaccia **tap0** è visibile e attiva (`ip addr show tap0` → conferma indirizzo e stato UP).
  - I pacchetti ICMP/TCP vengono inviati correttamente (verificato con `ping` e `tcpdump`).
- Problema:
  - I pacchetti **non vengono ricevuti dalla board** in Renode.
  - Echo server non risponde, e i pacchetti risultano persi.
- Conclusione:
  - Lato host la configurazione TAP è corretta.
  - Il problema potrebbe essere lato **board**, ovvero nella configurazione della periferica Ethernet (`LiteX_Ethernet`).

