# given something like 
#service tftp
#{
#	socket_type		= dgram
#	protocol		= udp
#	wait			= yes
#	user			= root
#	server			= /usr/sbin/in.tftpd
#	server_args		= -s /var/lib/tftpboot
#	disable			= yes
#	per_source		= 11
#	cps			= 100 2
#	flags			= IPv4
#}
# be able to change the value of the RHSs with the minimum amount of code
BEGIN           { FS="="; OFS="=";}
/server_args/   { print $1, " lol"; next;}
/disable/       { print $1, " nope"; next;}
                { print $0; }
