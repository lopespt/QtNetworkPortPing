QtNetworkPortPing
=================

This is a Network port tester. On one endpoint the program runs as a server and in the other endpoint the program runs as a client.

This program is usefull where you need to check if a firewall is blocking some ports.


Just run:
	./QtNetworkPortPing -s {port number}

in order to start listening on port {port number}

On the other endpoint:
	./QtNetworkPortPing -c {host}:{port number}





