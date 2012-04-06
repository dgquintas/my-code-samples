# can only log from localhost
CREATE USER 'monty'@'localhost' IDENTIFIED BY 'some_pass';
GRANT ALL PRIVILEGES ON *.* TO 'monty'@'localhost' WITH GRANT OPTION;

# can log from anywhere
CREATE USER 'monty'@'%' IDENTIFIED BY 'some_pass';
GRANT ALL PRIVILEGES ON *.* TO 'monty'@'%' WITH GRANT OPTION;

# only from localhost. NB: no password
CREATE USER 'admin'@'localhost';
GRANT RELOAD,PROCESS ON *.* TO 'admin'@'localhost';
# These privileges enable the admin user to execute the mysqladmin reload,
# mysqladmin refresh, and mysqladmin flush-xxx commands, as well 
# as mysqladmin processlist 

#no pass, no privileges
CREATE USER 'dummy'@'localhost';
