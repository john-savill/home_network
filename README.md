
# home_network
Notes for home NAS and any other home network applications. This page describes the my complete process from choosing and purchasing Raspberry Pi (RPi) hardware through to setting up network management software and network storage. Running local LLMs on my network is detailed on other pages.

## NAS

The goal for this is to create a lightweight, low-power, simple network storage.

The decision comes down to 2.5-inch SATA SSDs or M.2 NVME SSDs for storage. For 2.5-inch SATA SSDs there is really just the Radxa Penta SATA HAT for RPi 5, but:
 - this makes whole setup quite a lot bigger than M.2.
 - uses slightly less reliable, slightly slower, slightly more power req PC legacy SATA 2.5-inch SSDs, but cheaper.
 - wouldn't be PoE capable with all bays filled (max out at 2 2.5-inch SSDs according to radxa [here](https://docs.radxa.com/en/accessories/penta-sata-hat/penta-for-rpi5)) But easier to expand storage significantly with more bays.

Below I will compare prices (as of Nov/Dec 2025 UK) for 3 setups; using 2.5-inch SSD, M.2 without PoE, and M.2 with PoE.
### Item overview

***NOTE: Prices taken in mid-late 2025, there have been significant changes since then***

#### Base:
| Item | Price | Bought |
| --- | --- | --- |
| Pi-5 4GB | 56 | yes |
| Miro-SD | 7 | yes |
| Heatsink | 3.5 | yes |

__Subtotal: 66.5__

#### hat SATA 2.5-inch SSD setup/storage:
| Item | Price | note |
| --- | --- | --- |
| Radxa Penta SATA HAT | 45 | availability spotty |
| Storage (2 x 256GB SSD) | 60 | Integral |

__Subtotal: 105__

#### simple USB SATA 2.5-inch SSD setup/storage:
| USB to sata connection wires | (2 x 6) 12 | Pihut (UCTRONICS) |
| --- | --- | --- |
| NAS bracket enclosure | 12.50 | Pihut (UCTRONICS) |
| Storage (2 x 256GB SSD) | 60 | Integral |

__Subtotal: 84.50__

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
| PoE cable | N/A | N/A |

__Subtotal: 171.59__

### Decision for my use case

I'm leaning towards the simple SATA setup without PoE for the moment, I should be able to modify the setup later and add PoE if needed. Memory prices are currently fluctuating quite a bit but SATA hasn't skyrocketed as much as NVME. I won't need the higher speeds for mostly photo storage and the additional hardware is cheaper. I found a good deal on a couple of 256GB, Integral (UK) brand sata SSDs. 256GB is enough for my local storage in a RAID configuration, or 512GB without backups.

### Steps

Using the Pi-5 4GB version for the NAS. 4GB is fine for the simple NAS I'll be running. I've Flashed Pi-OS onto a 32GB Micro-SD card and connected the Pi to my home network.

I connect up the appropriate hardware, The two SSDs via USB and screwed them into the NAS enclosure base plate. Then I went through the following steps to make them usable memory:

Check the SSDs are viewed on the RPI (named something like sda and sdb).

    lsblk

Partition the drives individually (same for sdb).
    
    sudo fdisk /dev/sda

In prompt
 - Enter n to create a new partition.
 - Enter p for primary partition.
 - Use the default option for all other prompts

Format the drive (same for sdb).

    sudo mkfs.ext4 /dev/sda1

Mount the drive (same for sdb).

    sudo mount /dev/sda1

And ensure that the drives are mounted after each boot,

    sudo nano /etc/fstab

by adding the following lines at the end

    /dev/sda1 /mnt/sda1/ ext4 defaults,noatime 0 1
    /dev/sda1 /mnt/sdb1/ ext4 defaults,noatime 0 1

One drive is running [immich](https://immich.app) for local photo storage.

The other drive will either be shared across my network for other document storage or also used by immich, depending on the number of photos. To share the drive I would simply use SAMBA to make it networked driver for my local workstations.

***To be continued. Detail immich install and network storage setup with other drive***

## Network management

My network is managed using the RPi software [pi-hole](https://www.raspberrypi.com/tutorials/running-pi-hole-on-a-raspberry-pi/) that provides network ad-blocking and DNS. Specifically enabled for my phone, laptop and smart TV.

It is running on my RPi-5 along with the immich photo storage as it will have a high uptime. 

I followed the process described in the pihole linked webpage and reconfigured my Sky router to allow the DNS to happen externally. I will give a brief overview and note any specific challenges/changes to the followed tutorial. 

***To noet in here ...***

## 4B cluster

From an office closure I was lucky enough to get a few Pi 4Bs with 64GB SD cards. I plan to connect these up together for running other home network tools (AI-frontend, exo cluster etc).

### Steps 

I ordered a custom 3D printed 5u 10-inch mini rack and a for holding all the relevant hardware and a custom rack mount for holding the RPI 4bs.

![Initial rack setup](IMG_2867.HEIC)

The RPIs have been flashed, connected to my network via Ethernet and fitted into the rack mount.

## AI on CM5

I have a CM5 on a development board I have used for some initial learning, testing agents/LLMs, and hosting local AI. With the NVME SSD connected I am able to run a local LLM for my own benefit.

Since this is requires some complex setup I will dedicate a whole page to it at [AI_notes.md](AI_notes.md)


