
# home_network
Notes for home NAS and any other home network applications

## NAS

The goal for this is to create a lightweight, low-power, simple network storage.

The decision comes down to 2.5-inch SATA SSDs or M.2 NVME SSDs for storage. For 2.5-inch SATA SSDs there is really just the Radxa Penta SATA HAT for RPi 5, but:
 - this makes whole setup quite a lot bigger than M.2.
 - uses slightly less reliable, slightly slower, slightly more power req PC legacy SATA 2.5-inch SSDs, but cheaper.
 - wouldn't be PoE capable with all bays filled (max out at 2 2.5-inch SSDs according to radxa [here](https://docs.radxa.com/en/accessories/penta-sata-hat/penta-for-rpi5)) But easier to expand storage significantly with more bays.

Below I will compare prices (as of Nov/Dec 2025 UK) for 3 setups; using 2.5-inch SSD, M.2 without PoE, and M.2 with PoE.
### Item overview

#### Base:
| Item | Price | Bought |
| --- | --- | --- |
| Pi-5 4GB | 56 | yes |
| Miro-SD | 7 | yes |
| Heatsink | 3.5 | |

__Subtotal: 66.5__

#### SATA 2.5-inch SSD setup/storage:
| Item | Price | note |
| --- | --- | --- |
| Radxa Penta SATA HAT | 45 | availability spotty |
| Storage (2 x 500GB SSD) | 60 | Sandisk |

__Subtotal: 105__

#### M.2 setup/storage WO PoE:
| Item | Price | note |
| --- | --- | --- |
| Hat | 15.4 | Waveshare |
| Case | 8 | Layer |
| Storage (2 x 500GB) | 86.4 | from pihut website |

__Subtotal: 109.8__

#### M.2 setup/storage W PoE:
| Item | Price | Bought |
| --- | --- | --- |
| Hat | 30 | pimoroni base duo to ensure compatibility |
| Case | 8 | Layer |
| Storage (2 x 500GB) | 86.4 | from pihut website |
| PoE hat | 21.2 | Waveshare (H) |
| PoE injetor switch | 25.99 | Tp-Link |
| PoE cable |  |  |

__Subtotal: 171.59__

### Decision for my use case

I'm leaning towards the M.2 setup without PoE for the moment, I should be able to modify the setup later and add PoE if needed. Memory prices are currently fluctuating quite a bit.

### Steps

Using the Pi-5 4GB version for the NAS. 4GB is fine for the simple NAS I'll be running. I've Flashed Pi-OS onto a 32GB Micro-SD card and connected the Pi to my home network.

Next I connect up the appropriate hardware.
