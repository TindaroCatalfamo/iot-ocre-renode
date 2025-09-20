# IoT OCRE + Renode su LiteX VexRiscv

Questo progetto è una simulazione IoT in cui utilizzo **Renode** per emulare una board RISC-V (`litex_vexriscv`) ed eseguire il runtime **OCRE** su **Zephyr 3.7**.  
L’obiettivo è: ricevere moduli **.wasm** da un server tramite **TCP/UDP**, verificarne l’integrità (es. HMAC/SHA-256) ed eseguirli con OCRE.

---

## 🔹 Installazione e setup

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

## 🔹 Board emulata: LiteX VexRiscv

- Documentazione Zephyr: [LiteX VexRiscv board](https://docs.zephyrproject.org/3.7.0/boards/enjoydigital/litex_vexriscv/doc/index.html)  
- Documentazione OCRE board-support: [Adding board support](https://docs.project-ocre.org/board-support/adding-support/ocre-runtime/)

Renode fornisce già una descrizione della board `arty_litex_vexriscv.repl` che include:
- CPU VexRiscv
- Periferiche base LiteX
- Controller Ethernet (`sysbus.eth`)

---

## 🔹 Rete host ↔ board (TAP + switch Ethernet)

Per connettere la board emulata al mio host Linux ho usato:
1. **Creazione TAP sull’host:**
   ```bash
   sudo ip tuntap del dev tap0 mode tap 2>/dev/null || true
   sudo ip tuntap add dev tap0 mode tap user $USER
   sudo ip link set tap0 up
   sudo ip addr flush dev tap0
   sudo ip addr add 192.168.100.1/24 dev tap0
# IoT OCRE + Renode su LiteX VexRiscv

Questo progetto è una simulazione IoT in cui utilizzo **Renode** per emulare una board RISC-V (`litex_vexriscv`) ed eseguire il runtime **OCRE** su **Zephyr 3.7**.  
L’obiettivo è: ricevere moduli **.wasm** da un server tramite **TCP/UDP**, verificarne l’integrità (es. HMAC/SHA-256) ed eseguirli con OCRE.

---

## 🔹 Installazione e setup

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

## 🔹 Board emulata: LiteX VexRiscv

- Documentazione Zephyr: [LiteX VexRiscv board](https://docs.zephyrproject.org/3.7.0/boards/enjoydigital/litex_vexriscv/doc/index.html)  
- Documentazione OCRE board-support: [Adding board support](https://docs.project-ocre.org/board-support/adding-support/ocre-runtime/)

Renode fornisce già una descrizione della board `arty_litex_vexriscv.repl` che include:
- CPU VexRiscv
- Periferiche base LiteX
- Controller Ethernet (`sysbus.eth`)

---

## 🔹 Rete host ↔ board (TAP + switch Ethernet)

Per connettere la board emulata al mio host Linux ho usato:
1. **Creazione TAP sull’host:**
   ```bash
   sudo ip tuntap del dev tap0 mode tap 2>/dev/null || true
   sudo ip tuntap add dev tap0 mode tap user $USER
   sudo ip link set tap0 up
   sudo ip addr flush dev tap0
   sudo ip addr add 192.168.100.1/24 dev tap0

Switch virtuale in Renode + connessione NIC:

emulation CreateSwitch "sw0"
connector Connect sysbus.eth sw0
emulation CreateTap "tap0" "sw0"


Configurazione board (file .conf):

Indirizzo statico: 192.168.100.10/24

Gateway: 192.168.100.1

Auto-init rete abilitato (CONFIG_NET_CONFIG_AUTO_INIT=y)
