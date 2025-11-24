# ft_malcolm
You are not the boss of me now. Learning how to do ARP spoofing in C.

## Description
Ft_malcolm is a program that works in two steps:
1. It listens to ARP requests on the network and records the IP and MAC addresses of devices that send these requests.
2. Upon intercepting an ARP request, it sends a forged ARP reply to the requester via broadcast, claiming that the IP address being requested is associated with a different MAC address than the legitimate one.

## Glossary
- **ARP (Address Resolution Protocol)**: A protocol used to map an IP address to a MAC address within a local network.
- **MAC Address (Media Access Control Address)**: A unique identifier assigned to network interfaces for communications on the physical network segment.
- **IP Address (Internet Protocol Address)**: A numerical label assigned to each device connected to a computer network that uses the Internet Protocol for communication.

## What is the difference between an IP and a MAC address?
An IP address is a logical address assigned to a device on a network, allowing it to communicate with other devices over the internet or local network. It is not fixed, and can be changed based on the network configuration. A MAC address, on the other hand, is a physical address assigned to a network interface card (NIC) by the manufacturer. It is unique to each device and remains constant regardless of the network it is connected to.

## What is the ARP and how does it work?
The Address Resolution Protocol (ARP) is a network protocol used to map an IP address to a MAC address within a local network. When a device wants to communicate with another device on the same network, it needs to know the MAC address associated with the target device's IP address. Let's say we have a local network consisting in three devices: A, B and C.
If A want to communicate with B to send a ping request for instance, it will first look into its ARP cache (think of it as a contact list) to see if it already has the MAC address of B associated with its IP address. If it doesn't find it, it will send a broadcast ARP request asking to all devides on the network "Who has this IP address?".
When B receives this request and sees that the IP address matches its own, it will respond with an ARP reply "This IP is mine!", providing its MAC address to A. A can then use this MAC address to send the ping request directly to B, without having to broadcast an ARP request again.

## How does ARP spoofing work?
ARP spoofing, also known as ARP poisoning, is a technique used to manipulate the ARP cache of devices on a local network. When A sends an ARP request to find out what the MAC address of B is, all the devices on the network receive the request. This means that C may decide to claim the requested IP as its own: when B replies to A, C can send a fake ARP reply to A at the same time, saying "This IP is mine!". The ARP protocol does not have a confirmation mechanism to verify the authenticity of ARP replies and prevent any device to claim an IP as its own, so A will update its ARP cache with the MAC address provided by C instead of B. As a result, any subsequent communication from A intended for B will be sent to C instead, allowing C to intercept, modify, or block the traffic between A and B.

## Usage
You need to have Docker and Make installed on your system to run this program.

To compile the program, use the following command:<br>
```bash make```
To try out the program, set up the Docker environment by running:<br>
```bash make up```
This will start three Docker containers, each representing a device on a local network. The containers are named `containerA` (the target), `containerB` (the source), and `malcolm` (the Man-in-the-middle).

## Example of a MITM Attack

Follow these steps to simulate a Man-in-the-Middle (MITM) attack using the `ft_malcolm` program:

1. **Access `containerA`:**
	Open a terminal and run:
	```bash
	docker exec -it containerA sh
	```

2. **Check the IP and MAC address of `containerA`:**
	Inside the terminal, execute:
	```bash
	ip a
	```

3. **Access `malcolm`:**
	Open another terminal and run:
	```bash
	docker exec -it malcolm /bin/bash
	```

4. **Check the IP and MAC address of `malcolm`:**
	Inside the terminal, execute:
	```bash
	ip a
	```

5. **Start the `ft_malcolm` program:**
	In the `malcolm` terminal, run the program with the source and target IPs and MACs:
	```bash
	./ft_malcolm 172.18.0.3 <MAC from malcolm> 172.18.0.2 <MAC from containerA>
	```
	The program will begin listening for ARP traffic on the network.

6. **Send a ping request from `containerA` to `containerB`:**
	In the `containerA` terminal, execute:
	```bash
	ping -c 1 172.18.0.3
	```
	Since `containerA` does not have `containerB`'s MAC address in its ARP cache, it will broadcast an ARP request, triggering the spoofing by `malcolm`.

7. **Observe the output in `malcolm`:**
	Check the `malcolm` terminal to see the intercepted ARP request from `containerA` and the forged ARP reply sent by `malcolm`, associating `containerB`'s IP address with `malcolm`'s MAC address.

8. **Verify the ARP spoofing in `containerA`:**
	In the `containerA` terminal, check the ARP cache to confirm the spoofing:
	```bash
	arp
	```
	You should see that `containerB`'s IP address is now associated with `malcolm`'s MAC address.
